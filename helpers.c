#include "helpers.h"
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            float av = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            int round_av = (int) roundf(av);
            image[i][j].rgbtBlue = round_av;
            image[i][j].rgbtGreen = round_av;
            image[i][j].rgbtRed = round_av;
        }
        
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width/2; j++){
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE (*copy)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int total_blue = 0;
            int total_green = 0;
            int total_red = 0;
            int pixels = 0;
            for(int x = i-4; x < i+5; x++){
                for(int y = j-4; y < j+5; y++){
                    if(x < 0 || y < 0 || x > height-1 || y > width-1){
                        continue;
                    }
                    total_blue += copy[x][y].rgbtBlue;
                    total_green += copy[x][y].rgbtGreen;
                    total_red += copy[x][y].rgbtRed;                   
                    pixels++;
                }
            }
            float av_b = total_blue/(float) pixels;
            float av_g = total_green/(float) pixels;
            float av_r = total_red/(float) pixels;

            image[i][j].rgbtBlue = round(av_b);
            image[i][j].rgbtGreen = round(av_g);
            image[i][j].rgbtRed = round(av_r);
        }
    }
    free(copy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

    RGBTRIPLE (*copy)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int gx_blue = 0;
            int gx_green = 0;
            int gx_red = 0;
            int gy_blue = 0;
            int gy_green = 0;
            int gy_red = 0;
            
            int a = 0;
            for(int x = i-1; x < i+2; x++){
                int b = 0;
                for(int y = j-1; y < j+2; y++){
                    if(x < 0 || y < 0 || x > height-1 || y > width-1){
                        b++;
                        continue;
                    }
                    gx_blue += Gx[a][b] * copy[x][y].rgbtBlue;
                    gx_green += Gx[a][b] * copy[x][y].rgbtGreen;
                    gx_red += Gx[a][b] * copy[x][y].rgbtRed;
                    gy_blue += Gy[a][b] * copy[x][y].rgbtBlue;
                    gy_green += Gy[a][b] * copy[x][y].rgbtGreen;
                    gy_red += Gy[a][b] * copy[x][y].rgbtRed;
                    b++;

                }
                a++;
            }
            
            int G_blue = round(pow((pow(gx_blue, 2)+pow(gy_blue, 2)), 0.5));
            int G_green = round(pow((pow(gx_green, 2)+pow(gy_green, 2)), 0.5));
            int G_red = round(pow((pow(gx_red, 2)+pow(gy_red, 2)), 0.5));

            if (G_blue > 255) G_blue = 255;
            if (G_green > 255) G_green = 255;
            if (G_red > 255) G_red = 255;
            
            image[i][j].rgbtBlue = G_blue;
            image[i][j].rgbtGreen = G_green;
            image[i][j].rgbtRed = G_red;
        }
    }
    free(copy);
    return;
}


// Sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            
            if(sepiaBlue > 255) sepiaBlue = 255;
            if(sepiaRed > 255) sepiaRed = 255;
            if(sepiaGreen > 255) sepiaGreen = 255;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }   
}