/**
 * @file graph.h
 * @brief Header file for graph data structure and functions.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-03-30
 */

/**
 * lang.c – Minimal JSON‑based i18n loader for Phase 2
 * -------------------------------------------------------
 *  Keeps a tiny in‑memory dictionary so that the UI can
 *  print messages in the user‑selected language without
 *  sprinkling conditionals everywhere.
 *
 *  Design notes
 *  ------------
 *   • No dynamic hash map to keep things lightweight; we map
 *     keys to enum indices via a fixed lookup table.
 *   • If parsing fails or a key is missing, we silently fall
 *     back to the baked‑in English string – the program must
 *     never crash because of translation issues.
 *   • Thread‑safety is not a goal for this academic project –
 *     call lang_init() once at startup.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lang.h"

/* ---------------------------------------------------------------- */
/*  Static English fallback                                          */
/* ---------------------------------------------------------------- */

static const char *EN_DICT[MSG_COUNT] = {
        [MSG_MENU_TITLE]    = "============================\n        MAIN MENU\n============================\n",
        [MSG_MENU_OPTIONS]  = "1. Load matrix\n"
                               "2. DFS traversal\n"
                               "3. BFS traversal\n"
                               "4. All paths\n"
                               "5. Intersections\n"
                               "6. Insert antenna\n"
                               "7. Remove antenna\n"
                               "8. Print antennas\n"
                               "9. Clear antennas\n"
                               "0. Quit\n",
        [MSG_PROMPT_CHOICE] = "Enter your choice (1‑10): ",
        [MSG_ERR_IO]        = "I/O error – cannot open file\n",
        [MSG_ERR_MEM]       = "Memory allocation failed\n",
        [MSG_SUCCESS_LOAD]  = "Matrix loaded successfully\n",
        [MSG_SUCCESS_QUIT]  = "Good‑bye!\n"
};

/* ---------------------------------------------------------------- */
/*  Current dictionary (points to EN by default)                     */
/* ---------------------------------------------------------------- */

static char  *dyn_dict[MSG_COUNT] = { NULL };   /* malloc’d strings */
static const char **curr = EN_DICT;             /* active lookup */

/* ---------------------------------------------------------------- */
/*  Helper – map JSON key → MsgId                                    */
/* ---------------------------------------------------------------- */

typedef struct { const char *key; MsgId id; } KeyMap;

static const KeyMap MAP[] = {
        { "MSG_MENU_TITLE",    MSG_MENU_TITLE    },
        { "MSG_MENU_OPTIONS",  MSG_MENU_OPTIONS  },
        { "MSG_PROMPT_CHOICE", MSG_PROMPT_CHOICE },
        { "ERR_IO",            MSG_ERR_IO        },
        { "ERR_MEM",           MSG_ERR_MEM       },
        { "SUCCESS_LOAD",      MSG_SUCCESS_LOAD  },
        { "SUCCESS_QUIT",      MSG_SUCCESS_QUIT  },
};
static const size_t MAP_LEN = sizeof(MAP)/sizeof(MAP[0]);

static MsgId key_to_id(const char *key)
{
    for (size_t i = 0; i < MAP_LEN; ++i)
        if (strcmp(MAP[i].key, key) == 0) return MAP[i].id;
    return (MsgId)-1; /* invalid */
}

static void clear_dyn_dict(void)
{
    for (size_t i = 0; i < MSG_COUNT; ++i) {
        free(dyn_dict[i]);
        dyn_dict[i] = NULL;
    }
}

/* ---------------------------------------------------------------- */
/*  Public API                                                      */
/* ---------------------------------------------------------------- */

Status lang_init(const char *code)
{
    clear_dyn_dict();
    curr = EN_DICT;           /* reset to English */

    if (!code || strcmp(code, "en") == 0) return STATUS_OK;

    char path[64];
    snprintf(path, sizeof(path), "../lang/messages_%s.json", code);

    FILE *fp = fopen(path, "r");
    if (!fp) return STATUS_IO;    /* will keep English */

    char *line = NULL; size_t len = 0;
    while (custom_getlines(&line, &len, fp) != -1) {
        char *key_start = strchr(line, '"');
        if (!key_start) continue;
        char *key_end = strchr(key_start + 1, '"');
        if (!key_end) continue;
        *key_end = '\0';

        MsgId id = key_to_id(key_start + 1);
        if (id == (MsgId)-1) continue;  /* unknown key */

        char *val_start = strchr(key_end + 1, '"');
        if (!val_start) continue;
        char *val_end = strchr(val_start + 1, '"');
        if (!val_end) continue;
        *val_end = '\0';

        dyn_dict[id] = strdup(val_start + 1);
    }
    free(line);
    fclose(fp);

    /* Build pointer array: if entry missing –> fallback English. */
    static const char *local[MSG_COUNT];
    for (size_t i = 0; i < MSG_COUNT; ++i)
        local[i] = dyn_dict[i] ? dyn_dict[i] : EN_DICT[i];
    curr = local;

    return STATUS_OK;
}

void lang_close(void)
{
    clear_dyn_dict();
    curr = EN_DICT;
}

const char *tr(MsgId id)
{
    return (id < MSG_COUNT) ? curr[id] : "?";
}

