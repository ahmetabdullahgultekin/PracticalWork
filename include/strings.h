#ifndef PRACTICALWORK_STRINGS_H
#define PRACTICALWORK_STRINGS_H

/**
 * @file strings.h
 * @brief Header file for string constants used in the program.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-05-18
 */

/**
 * @enum STR
 * @brief Enumeration of string constants used in the program.
 * @details This enumeration defines the string constants used in the program.
 *          The strings are used for displaying messages to the user and for
 *          error handling. The strings are defined in different languages
 *          (English, Portuguese, Turkish) based on the compilation flags.
 */
enum {
    STR_INFO_MENU_TITLE = 0,
    STR_INFO_MENU_OPTIONS,
    STR_INFO_PROMPT_CHOICE,
    STR_INFO_INDEX,
    STR_INFO_FREQUENCY,
    STR_INFO_COORDINATES,
    STR_INFO_SUCCESS_LOAD,
    STR_INFO_SUCCESS_SAVE,
    STR_INFO_SUCCESS_QUIT,
    STR_INFO_PROMPT_PATH,
    STR_INFO_PATH,
    STR_INFO_PATHS_FOUND,
    STR_INFO_VERTEX_INDEX,
    STR_INFO_SOURCE_INDEX,
    STR_INFO_DEST_INDEX,
    STR_INFO_FREQUENCY_A,
    STR_INFO_FREQUENCY_B,
    STR_INFO_PROMPT_AVAILABLE_FILES,
    STR_INFO_PROMPT_FILE_CHOICE,
    STR_INFO_LISTS_CLEARED,
    STR_INFO_DANGER_POINTS,
    STR_INFO_DANGER_OVERLAPS,
    STR_ERR_IO,
    STR_ERR_GRAPH_COULD_NOT_FIND,
    STR_ERR_GRAPH_COULD_NOT_CLEARED,
    STR_ERR_FILE_NOT_FOUND,
    STR_ERR_FILE_NOT_LOADED,
    STR_ERR_NOT_IMPLEMENTED,
    STR_ERR_INVALID_CHOICE,
    STR_ERR_FREQUENCY_NOT_EQUAL,
    STR_ERR_INTERSECTIONS_NOT_FOUND,
    STR_COUNT               /* number of strings */
};

/**
 * @brief String constants for different languages.
    * @details The strings are defined in different languages (English, Portuguese, Turkish)
    * based on the compilation flags. The strings are used for displaying messages to the user
    * and for error handling.
    *
    * @note The strings are defined in the following languages:
    * - LANG_EN: English (default)
    * - LANG_PT: Portuguese
    * - LANG_TR: Turkish
    *
    * @warning The strings are defined in different languages based on the compilation flags.
    * Make sure to define the appropriate language flag before compiling the program.
    * @see STR_INFO_MENU_TITLE, STR_INFO_MENU_OPTIONS, STR_INFO_PROMPT_CHOICE, STR_INFO_INDEX,
    * STR_INFO_FREQUENCY, STR_INFO_COORDINATES, STR_INFO_SUCCESS_LOAD,
    * STR_INFO_SUCCESS_SAVE, STR_INFO_SUCCESS_QUIT,
    * STR_INFO_PROMPT_PATH, STR_INFO_PATH,
    * STR_INFO_PATHS_FOUND, STR_INFO_VERTEX_INDEX,
    * STR_INFO_SOURCE_INDEX, STR_INFO_DEST_INDEX,
    * STR_INFO_FREQUENCY_A, STR_INFO_FREQUENCY_B,
    * STR_INFO_PROMPT_AVAILABLE_FILES,
    * STR_INFO_PROMPT_FILE_CHOICE,
    * STR_INFO_LISTS_CLEARED,
    * STR_ERR_IO,
    * STR_ERR_GRAPH_COULD_NOT_FIND,
    * STR_ERR_GRAPH_COULD_NOT_CLEARED,
    * STR_ERR_FILE_NOT_FOUND,
    * STR_ERR_FILE_NOT_LOADED,
    * STR_ERR_NOT_IMPLEMENTED,
    * STR_ERR_INVALID_CHOICE,
    * STR_ERR_FREQUENCY_NOT_EQUAL,
    * STR_ERR_INTERSECTIONS_NOT_FOUND
    * @see STR_COUNT
    * @note The strings are used for displaying messages to the user and for error handling.
    */
#if defined(LANG_PT)
static const char *const STR[STR_COUNT] = {
        "\n============================\n       MENU PRINCIPAL\n============================\n",
        "1. Carregar matriz\n2. Busca em profundidade (DFS)\n3. Busca em largura (BFS)\n4. Todos os caminhos\n5. Interseccao de frequencias\n6. Interseccao de pontos perigosos\n7. Inserir\n8. Remover\n9. Imprimir antenas\n10. Imprimir arestas\n11. Imprimir pontos perigosos\n12. Limpar listas\n13. Salvar matriz\n0. Sair\n",
        "Escolha uma opcao",
        "Indice: ",
        "Frequencia: ",
        "Coordenadas (x,y): ",
        "Matriz carregada com sucesso\n",
        "\nMatriz salva com sucesso!\n",
        "Adeus!\n",
        "Caminho do ficheiro: ",
        "Caminho",
        "Todos os caminhos encontrados",
        "Indice do vertice",
        "Indice de origem",
        "Indice de destino",
        "Frequencia A: ",
        "Frequencia B: ",
        "Ficheiros disponiveis",
        "Escolha um ficheiro pelo numero: ",
        "Listas limpas com sucesso.\n",
        "Pontos perigosos para a frequencia",
        "Interseccao de pontos perigosos para as frequencias",
        "Erro E/S - nao foi possivel abrir o ficheiro\n",
        "Erro - o grafo nao foi encontrado\n",
        "Erro - o grafo nao pode ser limpo\n",
        "Erro - ficheiro nao encontrado\n",
        "Erro - ficheiro nao carregado\n",
        "Erro - funcionalidade nao implementada\n",
        "Opcao invalida, tente novamente\n",
        "Frequencias diferentes, tente novamente.\n",
        "Interseccao nao encontrada.\n"
};

/**
 * @brief String constants for Turkish language.
 * @details The strings are defined in Turkish language.
 * The strings are used for displaying messages to the user
 * and for error handling.
 */
#elif defined(LANG_TR)
static const char *const STR[STR_COUNT] = {
        "\n============================\n          ANA MENU\n============================\n",
        "1. Matris yukle\n2. Derinlik Onceli Arama (DFS)\n3. Genislik Onceli Arama (BFS)\n4. Tum Rotalar\n5. Frekans Kesismeleri\n6. Zararli Nokta Kesismeleri\n7. Ekle\n8. Cikar\n9. Antenleri Yazdir\n10. Kenarlari Yazdir\n11. Tehlikeli Noktalari Yazdir\n12. Listeyi Temizle\n13. Matris Kaydet\n0. Cikis\n",
        "Seciminizi giriniz",
        "Indeks: ",
        "Frekans: ",
        "Koordinatlar (x,y): ",
        "\nMatris basariyla yuklendi!",
        "Matris basariyla kaydedildi!\n",
        "Hosca kal!\n",
        "Dosya yolu giriniz: ",
        "Yol",
        "Bulunan Tum Yollar",
        "Dugum indeksi giriniz",
        "Kaynak indeksi giriniz",
        "Hedef indeksi giriniz",
        "Frekans A giriniz: ",
        "Frekans B giriniz: ",
        "Bulunan dosyalar:",
        "Dosya numarasini seciniz",
        "Listeler basariyla temizlendi.\n",
        "Frekansi icin tehlike noktaları",
        "Frekanslar icin tehlike kesisimleri",
        "G/C hatasi - dosya acilamadi!\n",
        "Hata - Graf bulunamadi.\n",
        "Hata - Graf temizlenemedi.\n",
        "Hata - dosya bulunamadi.\n",
        "Hata - dosya yuklu degil.\n",
        "Hata - ozellik uygulanamadi.\n",
        "Gecersiz secim, tekrar deneyiniz.\n",
        "Frekanslar esit degil, lutfen tekrar deneyin.\n",
        "Kesisim bulunamadi.\n"
};

/**
 * @brief String constants for English language.
 * @details The strings are defined in English language.
 * The strings are used for displaying messages to the user
 * and for error handling.
 */
#else /* LANG_EN (default) */
static const char *const STR[STR_COUNT] = {
        "\n============================\n         MAIN MENU\n============================\n",
        "1. Load matrix\n2. Depth-First Search (DFS)\n3. Breadth-First Search (BFS)\n4. All Paths\n5. Frequency Intersections\n6. Danger Point Intersections\n7. Insert\n8. Remove\n9. Print antennas\n10. Print edges\n11. Print Danger Points\n12. Clear lists\n13. Save matrix\n0. Exit\n",
        "Enter your choice",
        "Index: ",
        "Frequency: ",
        "Coordinates (x,y): ",
        "\nMatrix loaded successfully\n",
        "Matrix saved successfully!\n",
        "Good-bye!\n",
        "Enter file path: ",
        "Path",
        "All paths found",
        "Enter vertex index",
        "Enter source index",
        "Enter destination index",
        "Enter frequency A: ",
        "Enter frequency B: ",
        "Available files",
        "Select a file by number: ",
        "Lists cleared successfully.\n",
        "Danger points for frequency",
        "Danger overlaps for frequencies",
        "I/O error - cannot open file\n",
        "Error - graph could not be found\n",
        "Error - graph could not be cleared\n",
        "Error - file not found\n",
        "Error - no file loaded\n",
        "Error - feature not implemented\n",
        "Invalid choice, try again\n",
        "Frequencies are not equal, please try again.\n",
        "Intersections not found.\n"
};
#endif

/**
 * @brief Macro to convert enum value to string.
 * @param id The enum value to convert.
 * @return The string representation of the enum value.
 */
#define TR(id) (STR[(id)])

#endif // PRACTICALWORK_STRINGS_H