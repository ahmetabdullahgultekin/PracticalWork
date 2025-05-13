#ifndef PRACTICALWORK_STRINGS_H
#define PRACTICALWORK_STRINGS_H

/** strings.h – compile-time language table
 *
 *   Pass -DLANG_EN or -DLANG_PT or -DLANG_TR when you compile.
 *   Default is English if no macro is supplied.
 */

/** ---------- message indexes (keep in sync across langs) ---------- */
enum {
    STR_INFO_MENU_TITLE = 0,
    STR_INFO_MENU_OPTIONS,
    STR_INFO_PROMPT_CHOICE,
    STR_INFO_SUCCESS_LOAD,
    STR_INFO_SUCCESS_SAVE,
    STR_INFO_SUCCESS_QUIT,
    STR_INFO_PROMPT_PATH,
    STR_INFO_VERTEX_INDEX,
    STR_INFO_SOURCE_INDEX,
    STR_INFO_DEST_INDEX,
    STR_INFO_FREQUENCY_A,
    STR_INFO_FREQUENCY_B,
    STR_INFO_PROMPT_AVAILABLE_FILES,
    STR_INFO_PROMPT_FILE_CHOICE,
    STR_INFO_LISTS_CLEARED,
    STR_ERR_IO,
    STR_ERR_GRAPH_COULD_NOT_FIND,
    STR_ERR_GRAPH_COULD_NOT_CLEARED,
    STR_ERR_FILE_NOT_FOUND,
    STR_ERR_FILE_NOT_LOADED,
    STR_ERR_NOT_IMPLEMENTED,
    STR_ERR_INVALID_CHOICE,
    STR_COUNT               /* number of strings */
};

/**
 * strings.h – compile‑time dictionary (ASCII‑only)
 * --------------------------------------------------
 *  Select language at build time with
 *      -DLANG_PT   -DLANG_TR   (default is English)
 *  All text has been stripped of 8‑bit/Unicode characters so the
 *  source remains pure 7‑bit ASCII and safe for any compiler/terminal.
 */

/** --------------------------------------------------
*  Portuguese (LANG_PT) – ASCII transliteration
* -------------------------------------------------- */
#if defined(LANG_PT)
static const char *const STR[STR_COUNT] = {
        "\n============================\n       MENU PRINCIPAL\n============================\n",
        "1. Carregar matriz\n2. DFS\n3. BFS\n4. Intersecoes\n5. Inserir\n6. Remover\n7. Imprimir antenas\n8. Limpar listas\n9. Salvar matriz\n0. Sair\n",
        "Escolha (0-10): ",
        "Matriz carregada com sucesso\n",
        "Matriz salva com sucesso!\n",
        "Adeus!\n",
        "Caminho do ficheiro: ",
        "Indice do vertice: ",
        "Indice de origem: ",
        "Indice de destino: ",
        "Frequencia A: ",
        "Frequencia B: ",
        "Ficheiros disponiveis:",
        "Escolha um ficheiro pelo numero: ",
        "Listas limpas com sucesso.\n",
        "Erro E/S - nao foi possivel abrir o ficheiro\n",
        "Erro - o grafo nao foi encontrado\n",
        "Erro - o grafo nao pode ser limpo\n",
        "Erro - ficheiro nao encontrado\n",
        "Erro - ficheiro nao carregado\n",
        "Erro - funcionalidade nao implementada\n",
        "Opcao invalida, tente novamente\n"
};

/** --------------------------------------------------
*  Turkish (LANG_TR) – ASCII transliteration
* -------------------------------------------------- */
#elif defined(LANG_TR)
static const char *const STR[STR_COUNT] = {
        "\n============================\n       ANA MENU\n============================\n",
        "1. Matris yukle\n2. DFS\n3. BFS\n4. Tum Rotalar\n5. Kesisimler\n6. Ekle\n7. Sil\n8. Antenleri yazdir\n9. Listeyi temizle\n10. Matris kaydet\n0. Cikis\n",
        "Seciminizi giriniz (0-10): ",
        "Matris basariyla yuklendi!",
        "Matris basariyla kaydedildi!\n",
        "Hosca kal!\n",
        "Dosya yolu giriniz: ",
        "Dugum indeksi giriniz: ",
        "Kaynak indeksi giriniz: ",
        "Hedef indeksi giriniz: ",
        "Frekans A giriniz: ",
        "Frekans B giriniz: ",
        "Bulunan dosyalar:",
        "Dosya numarasini seciniz: ",
        "Listeler basariyla temizlendi.\n",
        "G/C hatasi - dosya acilamadi!\n",
        "Hata - graf bulunamadi.\n",
        "Hata - Graf temizlenemedi.\n",
        "Hata - dosya bulunamadi.\n",
        "Hata - dosya yuklu degil.\n",
        "Hata - ozellik uygulanamadi.\n",
        "Gecersiz secim, tekrar deneyiniz.\n"
};

/** --------------------------------------------------
*  English default
* -------------------------------------------------- */
#else /* LANG_EN (default) */
static const char *const STR[STR_COUNT] = {
    "\n============================\n       MAIN MENU\n============================\n",
    "1. Load matrix\n2. DFS\n3. BFS\n4. All paths\n5. Intersections\n6. Insert\n7. Remove\n8. Print antennas\n9. Clear lists\n10. Save matrix\n0. Quit\n",
    "Enter your choice (0-10): ",
    "Matrix loaded successfully\n",
    "Matrix saved successfully!\n",
    "Good-bye!\n",
    "Enter file path: ",
    "Enter vertex index: ",
    "Enter source index: ",
    "Enter destination index: ",
    "Enter frequency A: ",
    "Enter frequency B: ",
    "Available files:",
    "Select a file by number: ",
    "Lists cleared successfully.\n",
    "I/O error - cannot open file\n",
    "Error - graph could not be found\n",
    "Error - graph could not be cleared\n",
    "Error - file not found\n",
    "Error - no file loaded\n",
    "Error - feature not implemented\n",
    "Invalid choice, try again\n"
};
#endif

#define TR(id) (STR[(id)])

#endif // PRACTICALWORK_STRINGS_H