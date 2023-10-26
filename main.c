#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "image.c"
int main() {
    Image* loaded_image = NULL;
    Image* grayscale_image = NULL;

    char input_filename[256];
    char output_filename[256];
    int choice;

    while (1) {
        printf("Menu:\n");
        printf("1. Carregar imagem\n");
        printf("2. Converter para tons de cinza\n");
        printf("3. Gravar imagem\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Informe o caminho da imagem a ser carregada (ou pressione Enter para usar a imagem padrao): ");
                getchar(); // Limpa o buffer de entrada
                fgets(input_filename, sizeof(input_filename), stdin);
                input_filename[strcspn(input_filename, "\n")] = '\0'; // Remove a quebra de linha

                if (strlen(input_filename) == 0) {
                    // Carregar uma imagem padrão ou pré-definida
                    if (loaded_image) {
                        free_image(loaded_image);
                    }
                    loaded_image = load_from_ppm("sample.ppm");
                    if (loaded_image) {
                        printf("Imagem carregada com sucesso.\n");
                    } else {
                        printf("Erro ao carregar a imagem.\n");
                    }
                } else {
                    // Carregar a imagem especificada pelo usuário
                    if (loaded_image) {
                        free_image(loaded_image);
                    }
                    loaded_image = load_from_ppm(input_filename);
                    if (loaded_image) {
                        printf("Imagem carregada com sucesso.\n");
                    } else {
                        printf("Erro ao carregar a imagem.\n");
                    }
                }
                break;

            case 2:
                if (loaded_image) {
                    if (grayscale_image) {
                        free_image(grayscale_image);
                    }
                    grayscale_image = create(loaded_image->rows, loaded_image->cols, "P2");
                    rgb_to_gray(loaded_image, grayscale_image);
                    printf("Imagem convertida para tons de cinza.\n");
                } else {
                    printf("Nenhuma imagem carregada.\n");
                }
                break;

            case 3:
                if (grayscale_image) {
                    printf("Informe o caminho para salvar a imagem em tons de cinza (ou pressione Enter para usar o caminho padrao): ");
                    getchar(); // Limpa o buffer de entrada
                    fgets(output_filename, sizeof(output_filename), stdin);
                    output_filename[strcspn(output_filename, "\n")] = '\0'; // Remove a quebra de linha

                    if (strlen(output_filename) == 0) {
                        // Salvar a imagem em um caminho padrão
                        write_to_ppm(grayscale_image, "output.ppm");
                        printf("Imagem gravada com sucesso.\n");
                    } else {
                        // Salvar a imagem no caminho especificado pelo usuário
                        write_to_ppm(grayscale_image, output_filename);
                        printf("Imagem gravada com sucesso.\n");
                    }
                } else {
                    printf("Nenhuma imagem em tons de cinza disponível para gravacao.\n");
                }
                break;

            case 4:
                // Liberar memória e sair
                if (loaded_image) {
                    free_image(loaded_image);
                }
                if (grayscale_image) {
                    free_image(grayscale_image);
                }
                return 0;

            default:
                printf("Opção invalida. Escolha uma opcao valida do menu.\n");
                break;
        }
    }

    return 0;
}