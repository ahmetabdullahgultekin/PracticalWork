#ifndef PRACTICALWORK_LANG_H
#define PRACTICALWORK_LANG_H

/*
 * lang.h – Lightweight internationalisation helper (Phase 2)
 * ----------------------------------------------------------------
 *  Provides a minimal dictionary‑lookup mechanism so that the UI
 *  can present messages in English, Portuguese, or any additional
 *  language the user supplies as a JSON file.
 *
 *  Design goals
 *  ------------
 *  • Zero console I/O inside – the UI layer chooses when to print.
 *  • Thread‑safe read‑only access after initialisation.
 *  • Tiny dependency footprint – only uses libc and our Status enum.
 *  • Re‑entrant: `lang_init()` may be called again to switch language
 *    at runtime; previous dictionary is freed automatically.
 *
 *  File format
 *  -----------
 *  Each language file lives in `lang/messages_<code>.json` and maps a
 *  symbolic key (the enum MsgId below) to a string. Example (English):
 *
 *      {
 *          "MSG_MENU_TITLE"      : "============================\n        MAIN MENU\n============================",
 *          "MSG_PROMPT_CHOICE"   : "Enter your choice (1‑10): ",
 *          "ERR_IO"              : "I/O error – cannot open file\n",
 *          ...
 *      }
 *
 *  If a key is missing, `tr()` falls back to the English dictionary.
 * ----------------------------------------------------------------
 */

#include "graph.h"   /* pulls in Status enum */

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------- */
/*  Enumerated message identifiers – add as needed.                  */
/* ---------------------------------------------------------------- */

typedef enum {
    MSG_MENU_TITLE = 0,
    MSG_MENU_OPTIONS,
    MSG_PROMPT_CHOICE,
    MSG_ERR_IO,
    MSG_ERR_MEM,
    MSG_SUCCESS_LOAD,
    MSG_SUCCESS_QUIT,

    /*  Add new keys *above* this line. */
    MSG_COUNT
} MsgId;

/* ---------------------------------------------------------------- */
/*  Public API                                                      */
/* ---------------------------------------------------------------- */

/* Load the dictionary for the given ISO code ("en", "pt", …).
   On success returns STATUS_OK.  On failure, falls back to English
   so that the program remains usable. */
Status lang_init(const char *iso_code);

/* Release the current dictionary.  Safe to call with no prior init. */
void   lang_close(void);

/* Translate: returns read‑only pointer to UTF‑8 string. */
const char *tr(MsgId id);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif //PRACTICALWORK_LANG_H
