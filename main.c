#include <stdio.h>

typedef struct _pixel {
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
} Pixel;

typedef struct _image {
    // [width][height][rgb]
    // 0 -> r
    // 1 -> g
    // 2 -> b
    //Pixel pixel [512][512]  <<< fazer isso e ver se roda;
    unsigned short int pixel[512][512][3];
    unsigned int w;
    unsigned int h;
} Image;


int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int pixel_igual(Pixel p1, Pixel p2) {
    if (p1.r == p2.r &&
        p1.g == p2.g &&
        p1.b == p2.b)
        return 1;
    return 0;
}


Image escala_de_cinza(Image img) {
  
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            int media = img.pixel[i][j][0] +
                        img.pixel[i][j][1] +
                        img.pixel[i][j][2];
            media /= 3;
            img.pixel[i][j][0] = media;
            img.pixel[i][j][1] = media;
            img.pixel[i][j][2] = media;
        }
    }

    return img;
}
Image filtro_sepia(Image img) {
 for (unsigned int x = 0; x < img.h; ++x) {
                    for (unsigned int j = 0; j < img.w; ++j) {
                        unsigned short int pixel[3];
                        pixel[0] = img.pixel[x][j][0];
                        pixel[1] = img.pixel[x][j][1];
                        pixel[2] = img.pixel[x][j][2];

                        int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
                        int menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][0] = menor_r;

                        p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
                        menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][1] = menor_r;

                        p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
                        menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][2] = menor_r;
                    }
                }
	return img;
}
Image espelhamento(Image img) {
 int horizontal = 0;
                scanf("%d", &horizontal);

                int w = img.w, h = img.h;

                if (horizontal == 1) w /= 2;
                else h /= 2;

                for (int i = 0; i < h; ++i) {
                    for (int j = 0; j < w; ++j) {
                        int x = i, y = j;

                        if (horizontal == 1) y = img.w - 1 - j;
                        else x = img.h - 1 - i;

                        Pixel aux1;
                        aux1.r = img.pixel[i][j][0];
                        aux1.g = img.pixel[i][j][1];
                        aux1.b = img.pixel[i][j][2];

                        img.pixel[i][j][0] = img.pixel[x][y][0];
                        img.pixel[i][j][1] = img.pixel[x][y][1];
                        img.pixel[i][j][2] = img.pixel[x][y][2];

                        img.pixel[x][y][0] = aux1.r;
                        img.pixel[x][y][1] = aux1.g;
                        img.pixel[x][y][2] = aux1.b;
                    }
                }
	return img;
}
// TA QUEBRADO ='(

Image blur(Image img) {

     /*unsigned int h; 
     unsigned short int pixel[512][512][3];
     unsigned int tamanho;
     unsigned int w;*/

     int tamanho = 0;
     unsigned int w = img.w;
     unsigned int h= img.h;
     //img.pixel[512][512][3];

     scanf("%d", &tamanho);

   for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            Pixel media = {0, 0, 0};

            unsigned int menor_h = (img.h - 1 > i + tamanho/2) ? i + tamanho/2 : img.h - 1;
            unsigned int min_w = (img.w - 1 > j + tamanho/2) ? j + tamanho/2 : img.w - 1;
            for(unsigned int x = (0 > i - tamanho/2 ? 0 : i - tamanho/2); x <= menor_h; ++x) {
                for(unsigned int y = (0 > j - tamanho/2 ? 0 : j - tamanho/2); y <= min_w; ++y) {
                    media.r += img.pixel[x][y][0];
                    media.g += img.pixel[x][y][1];
                    media.b += img.pixel[x][y][2];
                }
            }

            // printf("%u", media.r)
            media.r /= tamanho * tamanho;
            media.g /= tamanho * tamanho;
            media.b /= tamanho * tamanho;

            img.pixel[i][j][0] = media.r;
            img.pixel[i][j][1] = media.g;
            img.pixel[i][j][2] = media.b;
        }
    }
	return img;
}

Image rotacionar90direita(Image img) {
    Image rotacionada;

    rotacionada.w = img.h;
    rotacionada.h = img.w;

    int quantas_vezes = 0;
    scanf("%d", &quantas_vezes);
    quantas_vezes %= 4;
    for (int j = 0; j < quantas_vezes; ++j) {

	    for (unsigned int i = 0, y = 0; i < rotacionada.h; ++i, ++y) {
		for (int j = rotacionada.w - 1, x = 0; j >= 0; --j, ++x) {
		    rotacionada.pixel[i][j][0] = img.pixel[x][y][0];
		    rotacionada.pixel[i][j][1] = img.pixel[x][y][1];
		    rotacionada.pixel[i][j][2] = img.pixel[x][y][2];
                }
            }

    return rotacionada;
    }
}

void inverter_cores(unsigned short int pixel[512][512][3],
                    unsigned int w, unsigned int h) {
    for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            pixel[i][j][0] = 255 - pixel[i][j][0];
            pixel[i][j][1] = 255 - pixel[i][j][1];
            pixel[i][j][2] = 255 - pixel[i][j][2];
        }
    }
}

Image cortar_imagem(Image img) {
    Image cortada;
    int x, y;
    int w, h; 
    scanf("%d %d", &x, &y);         
    scanf("%d %d", &w, &h);    

    cortada.w = w;
    cortada.h = h;

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cortada.pixel[i][j][0] = img.pixel[i + y][j + x][0];
            cortada.pixel[i][j][1] = img.pixel[i + y][j + x][1];
            cortada.pixel[i][j][2] = img.pixel[i + y][j + x][2];
        }
    }

    return cortada;
}

Image ler_imagem() {
	Image img;
	char p3[4];
	int max_color;

	//substituir p3 por tipo_imagem.
	scanf("%s", p3);
	scanf("%u %u %d", &img.w, &img.h, &max_color);
	
	for (unsigned int i = 0; i < img.h; ++i) {
	        for (unsigned int j = 0; j < img.w; ++j) {
	            scanf("%hu %hu %hu", &img.pixel[i][j][0],
                               		 &img.pixel[i][j][1],
                                	 &img.pixel[i][j][2]);
        }
    }
    return img;
}

void imprimir_imagem(Image img){

    printf("P3\n");
    printf("%u %u\n255\n", img.w, img.h);

    for (unsigned int i = 0; i < img.h; ++i) 
    {
        for (unsigned int j = 0; j < img.w; ++j) 
        {
            printf("%hu %hu %hu ", img.pixel[i][j][0],
                                   img.pixel[i][j][1],
                                   img.pixel[i][j][2]);
        }
        printf("\n");
    }
}
 

int main() {
    Image img;
 
    img = ler_imagem();


    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) {
        int opcao;
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: { 
                img = escala_de_cinza(img);
                break;
            }
            case 2: {
                img = filtro_sepia(img);
                break;
            }
            case 3: {
		img = blur(img);
              
                break;
            }
            case 4: {
                img = rotacionar90direita(img);
                break;
            }
            case 5: {
                img = espelhamento(img);
                break;
            }
            case 6: {
                inverter_cores(img.pixel, img.w, img.h);
                break;
            }
            case 7: { 
                img = cortar_imagem(img);
                break;
            }
        }

    }

   imprimir_imagem(img);
    return 0;
}
