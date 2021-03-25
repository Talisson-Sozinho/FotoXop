#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"
#include "Filtros.h"

void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   - v) >= 0 ? (pixel.cor[RED]   - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? (pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  - v) >= 0 ? (pixel.cor[BLUE]  - v) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void clarearImagem(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'clarearImagem'); //Retire esssa mensagem ao implementar a fução
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   + v) <= 255 ? (pixel.cor[RED]  + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? (pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  + v) <= 255 ? (pixel.cor[BLUE]  + v) : 255);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void escalaDeCinzaImagem(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'escalaDeCinzaImagem'); //Retire esssa mensagem ao implementar a fução
    int media = 0;
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);

            media = (int)(( (int)pixel.cor[RED] + (int)pixel.cor[GREEN] + (int)pixel.cor[BLUE])/3);

            pixel.cor[RED]   = media;
            pixel.cor[GREEN] = media;
            pixel.cor[BLUE]  = media;
            recolorePixel(img, h, w, pixel);
        }
    }
}

void filtroSobel(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'filtroSobel'); //Retire esssa mensagem ao implementar a fução

    /* Dicas:
     * 1) Se quiser, pode ignorar as bordas das imagens
     * 2) Para o pixel na posição (h, w), obtenha os outros 8 pixels vizinhos e aplique a matriz gx e gy
     *    em cada banda de cor do pixel. Combine o valor obtido por gx e gy e modifique o pixel de img.
     *    Lembre-se que a obtenção dos pixels deve ser a partir de uma cópia da imagem.
     * 3) Verifique se o novo valor obtido para a banda de cor é um valor válido (entre 0 e 255).
    */
    Imagem *copiaImg = copiaImagem(img);

    int resultadoR, resultadoG, resultadoB , resultadoRy, resultadoGy,resultadoBy, resultadoRx, resultadoGx, resultadoBx;
    Pixel pixelOrig[8];

    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            pixelOrig[0] = obtemPixel(copiaImg, h-1, w-1);
            pixelOrig[1] = obtemPixel(copiaImg, h-1, w);
            pixelOrig[2] = obtemPixel(copiaImg, h-1, w+1);
            pixelOrig[3] = obtemPixel(copiaImg, h, w-1);
            pixelOrig[4] = obtemPixel(copiaImg, h, w+1);
            pixelOrig[5] = obtemPixel(copiaImg, h+1, w-1);
            pixelOrig[6] = obtemPixel(copiaImg, h+1, w);
            pixelOrig[7] = obtemPixel(copiaImg, h+1, w+1);

            Pixel pixelFiltro = obtemPixel(img, h, w);


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            resultadoRy = (int)( (int)pixelOrig[0].cor[RED]*1 + (int)pixelOrig[1].cor[RED]*2 + (int)pixelOrig[2].cor[RED]*1 +
                                 (int)pixelOrig[5].cor[RED]*(-1) + (int)pixelOrig[6].cor[RED]*(-2) + (int)pixelOrig[7].cor[RED]*(-1) );

            resultadoGy = (int)( (int)pixelOrig[0].cor[GREEN]*1 + (int)pixelOrig[1].cor[GREEN]*2 + (int)pixelOrig[2].cor[GREEN]*1 +
                                 (int)pixelOrig[5].cor[GREEN]*(-1) + (int)pixelOrig[6].cor[GREEN]*(-2) + (int)pixelOrig[7].cor[GREEN]*(-1) );

            resultadoBy = (int)( (int)pixelOrig[0].cor[BLUE]*1 + (int)pixelOrig[1].cor[BLUE]*2 + (int)pixelOrig[2].cor[BLUE]*1 +
                                 (int)pixelOrig[5].cor[BLUE]*(-1) + (int)pixelOrig[6].cor[BLUE]*(-2) + (int)pixelOrig[7].cor[BLUE]*(-1) );

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            resultadoRx = (int)( (int)pixelOrig[0].cor[RED]*1 + (int)pixelOrig[2].cor[RED]*(-1) +
                                 (int)pixelOrig[3].cor[RED]*2 + (int)pixelOrig[4].cor[RED]*(-2) +
                                 (int)pixelOrig[5].cor[RED]*1 + (int)pixelOrig[7].cor[RED]*(-1) );

            resultadoGx =  (int)( (int)pixelOrig[0].cor[GREEN]*1 + (int)pixelOrig[2].cor[GREEN]*(-1) +
                                  (int)pixelOrig[3].cor[GREEN]*2 + (int)pixelOrig[4].cor[GREEN]*(-2) +
                                  (int)pixelOrig[5].cor[GREEN]*1 + (int)pixelOrig[7].cor[GREEN]*(-1) );

            resultadoBx =  (int)( (int)pixelOrig[0].cor[GREEN]*1 + (int)pixelOrig[2].cor[GREEN]*(-1) +
                                  (int)pixelOrig[3].cor[GREEN]*2 + (int)pixelOrig[4].cor[GREEN]*(-2) +
                                  (int)pixelOrig[5].cor[GREEN]*1 + (int)pixelOrig[7].cor[GREEN]*(-1) );


            resultadoR = (int)( ((int)resultadoRy + (int)resultadoRx)/2);
            resultadoG = (int)( ((int)resultadoGy + (int)resultadoGx)/2);
            resultadoB = (int)( ((int)resultadoBy + (int)resultadoBx)/2);

            pixelFiltro.cor[RED]   = ( resultadoR >= 0 && resultadoR <= 255 ? resultadoR : ( resultadoR > 255 ? 255 : 0));
            pixelFiltro.cor[GREEN] = ( resultadoG >= 0 && resultadoG <= 255 ? resultadoG : ( resultadoG > 255 ? 255 : 0));
            pixelFiltro.cor[BLUE]  = ( resultadoB >= 0 && resultadoB <= 255 ? resultadoB : ( resultadoB > 255 ? 255 : 0));
            recolorePixel(img, h, w, pixelFiltro);
        }
    }
    liberaImagem(copiaImg);
}

void deteccaoBordasLaplace(Imagem *img) {
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'deteccaoBordasLaplace'); //Retire esssa mensagem ao implementar a fução

    /* Siga as mesmas dicas do filtro de Sobel */
    Imagem *copiaImg = copiaImagem(img);

    int resultadoR, resultadoG, resultadoB;
    Pixel pixelOrig[9];

    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            pixelOrig[0] = obtemPixel(copiaImg, h-1, w-1);
            pixelOrig[1] = obtemPixel(copiaImg, h-1, w);
            pixelOrig[2] = obtemPixel(copiaImg, h-1, w+1);
            pixelOrig[3] = obtemPixel(copiaImg, h, w-1);
            pixelOrig[4] = obtemPixel(copiaImg, h, w);
            pixelOrig[5] = obtemPixel(copiaImg, h, w+1);
            pixelOrig[6] = obtemPixel(copiaImg, h+1, w-1);
            pixelOrig[7] = obtemPixel(copiaImg, h+1, w);
            pixelOrig[8] = obtemPixel(copiaImg, h+1, w+1);


            Pixel pixelFiltro = obtemPixel(img, h, w);


            resultadoR = (int)( (int)pixelOrig[1].cor[RED]*(-1) +
                                (int)pixelOrig[3].cor[RED]*(-1) +
                                (int)pixelOrig[4].cor[RED]*4 +
                                (int)pixelOrig[5].cor[RED]*(-1) +
                                (int)pixelOrig[7].cor[RED]*(-1) );

            resultadoG = (int)( (int)pixelOrig[1].cor[GREEN]*(-1) +
                                (int)pixelOrig[3].cor[GREEN]*(-1) +
                                (int)pixelOrig[4].cor[GREEN]*4 +
                                (int)pixelOrig[5].cor[GREEN]*(-1) +
                                (int)pixelOrig[7].cor[GREEN]*(-1) );

            resultadoB = (int)( (int)pixelOrig[1].cor[BLUE]*(-1) +
                                (int)pixelOrig[3].cor[BLUE]*(-1) +
                                (int)pixelOrig[4].cor[BLUE]*4 +
                                (int)pixelOrig[5].cor[BLUE]*(-1) +
                                (int)pixelOrig[7].cor[BLUE]*(-1) );


            pixelFiltro.cor[RED]   = ( resultadoR >= 0 && resultadoR <= 255 ? resultadoR : ( resultadoR > 255 ? 255 : 0));
            pixelFiltro.cor[GREEN] = ( resultadoG >= 0 && resultadoG <= 255 ? resultadoG : ( resultadoG > 255 ? 255 : 0));
            pixelFiltro.cor[BLUE]  = ( resultadoB >= 0 && resultadoB <= 255 ? resultadoB : ( resultadoB > 255 ? 255 : 0));
            recolorePixel(img, h, w, pixelFiltro);
        }
    }
    liberaImagem(copiaImg);
}

void meuFiltro(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'meuFiltro'); //Retire esssa mensagem ao implementar a fução
    /*tentei fazer umas implementações pra redução de ruidos usando moda, média e mediana porém não gostei dos resultado,
        então resolvi deixar esse mais simples, porém com um resultado mt bom */
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = ((255 - (int)pixel.cor[RED] ) >= 0 ? (255 - (int)pixel.cor[RED] ) : 0);
            pixel.cor[GREEN] = ((255 - (int)pixel.cor[GREEN] ) >= 0 ? (255 - (int)pixel.cor[GREEN] ) : 0);
            pixel.cor[BLUE]  = ((255 - (int)pixel.cor[BLUE] ) >= 0 ? (255 - (int)pixel.cor[BLUE] ) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}
