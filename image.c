#include "image.h"
#include <stdio.h>
#include <stdlib.h>
// load_from_ppm é projetada para ler arquivos PPM nos formatos "P2" e "P3" (tons de cinza e RGB)
// e carregar os dados em uma estrutura Image. Certifique-se de incluir essa função no seu código e chamar 
//free_image(image) quando terminar de usar a imagem para evitar vazamentos de memória.
Image* create(int rows, int cols, const char type[]) {
    Image* image = (Image*)malloc(sizeof(Image));
    image->rows = rows;
    image->cols = cols;
    snprintf(image->type, 3, "%s", type);
    
    image->data = (unsigned char**)malloc(rows * sizeof(unsigned char*));
    for (int i = 0; i < rows; i++) {
        image->data[i] = (unsigned char*)malloc(cols * sizeof(unsigned char));
    }
    
    return image;
}
// write_to_ppm escreverá uma imagem em formato PPM, seja em tons de cinza ("P2") ou colorida 
// ("P3"), dependendo do valor do campo type na estrutura Image.
Image* load_from_ppm(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char magic[3];
    if (fscanf(file, "%2s", magic) != 1) {
        perror("Erro ao ler o cabeçalho do arquivo");
        fclose(file);
        return NULL;
    }

    if (strcmp(magic, "P3") != 0 && strcmp(magic, "P2") != 0) {
        printf("Este programa suporta apenas arquivos P2 e P3.\n");
        fclose(file);
        return NULL;
    }

    int rows, cols, maxval;
    if (fscanf(file, "%d %d %d", &cols, &rows, &maxval) != 3) {
        perror("Erro ao ler as dimensões e o valor máximo");
        fclose(file);
        return NULL;
    }

    Image* image = create(rows, cols, magic);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (strcmp(magic, "P3") == 0) {
                int r, g, b;
                if (fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                    perror("Erro ao ler os valores RGB");
                    free_image(image);
                    fclose(file);
                    return NULL;
                }
                image->data[i][j] = (unsigned char)((r + g + b) / 3);
            } else if (strcmp(magic, "P2") == 0) {
                int gray;
                if (fscanf(file, "%d", &gray) != 1) {
                    perror("Erro ao ler o valor de cinza");
                    free_image(image);
                    fclose(file);
                    return NULL;
                }
                image->data[i][j] = (unsigned char)gray;
            }
        }
    }

    fclose(file);
    return image;
}

void write_to_ppm(Image* image, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    fprintf(file, "%s\n", image->type);
    fprintf(file, "%d %d\n", image->cols, image->rows);
    fprintf(file, "255\n"); // Valor máximo de pixel

    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
            fprintf(file, "%d", image->data[i][j]);
            if (j < image->cols - 1) {
                fprintf(file, " ");
            } else {
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
}
// Esta função iterará pelos pixels da imagem RGB, calculará o valor em tons de cinza para cada pixel e 
//armazenará o resultado na imagem de tons de cinza (image_gray).

//Depois de executar esta função, a imagem em image_gray conterá a versão em tons de cinza da imagem original 
//em image_rgb.
void rgb_to_gray(Image* image_rgb, Image* image_gray) {
     if (strcmp(image_rgb->type, "P3") != 0) {
        printf("Esta função suporta apenas imagens RGB (P3).\n");
        return;
    }

    if (strcmp(image_gray->type, "P2") != 0) {
        printf("A imagem de saída deve ser em tons de cinza (P2).\n");
        return;
    }

    for (int i = 0; i < image_rgb->rows; i++) {
        for (int j = 0; j < image_rgb->cols; j++) {
            int r = image_rgb->data[i][3 * j];
            int g = image_rgb->data[i][3 * j + 1];
            int b = image_rgb->data[i][3 * j + 2];

            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            image_gray->data[i][j] = gray;
        }
    }
}

void free_image(Image* image) {
     if (image) {
        for (int i = 0; i < image->rows; i++) {
            free(image->data[i]);
        }
        free(image->data);
        free(image);
    }
}