#include <pngwriter.h>
#include <cstdlib>

using namespace std;

/*
NAME: Deron Barker
ID: 400014686
THEME: Sunny Beach Day
/*
Functions Used: plot, plot_blend, circle, circle_blend, filledcircle, filledcircle_blend,
square, square_blend, filledsquare, filledsquare_blend, triangle, filledtriangle,
filledtriangle_blend, diamond, filleddiamond, line, line_blend, cross, arrow,
filledarrow, maltesecross, bezier, bezier_blend, plot_text, plotHSV, plotHSV_blend,
flood_fill, flood_fill_blend, readHSV, plotCMYK, plotCMYK_blend, getwidth, getheight,
setcompressionlevel, write_png, close, polygon, polygon_blend
*/


int main() {

    const int WIDTH = 700;
    const int HEIGHT = 600;

    pngwriter png(WIDTH, HEIGHT, 1.0, "400014686.png");

    png.plot(100, 50, 65000, 50000, 20000);

    // ---------------- SKY ----------------
    for (int y = HEIGHT; y >= 300; y -= 10) {
        png.filledsquare(1, y - 10, WIDTH, y, 20000 + y * 5, 20000 + y * 10, 60000);
    }
    for (int y = 300; y < HEIGHT; y += 20) {
        png.filledsquare_blend(1, y, WIDTH, y + 10, 0.2, 30000, 40000, 60000);
    }

    // ---------------- SUN ----------------
    png.filledcircle(600, 500, 50, 65000, 60000, 10000);
    double glow = 0.05;
    for (int r = 50; r <= 80; r++) {
        png.circle_blend(600, 500, r, glow, 65000, 60000, 10000);
        glow += 0.03;
    }

    // Sun rays
    for (int a = 0; a < 360; a += 15) {
        double rad = a * 3.14159265 / 180.0;
        int x1 = 600 + cos(rad) * 55;
        int y1 = 500 + sin(rad) * 55;
        int x2 = 600 + cos(rad) * 85;
        int y2 = 500 + sin(rad) * 85;
        png.line_blend(x1, y1, x2, y2, 0.3, 65000, 60000, 10000);
    }

    // ---------------- CLOUDS ----------------
    png.filledcircle_blend(100, 520, 30, 0.3, 1.0, 1.0, 1.0);
    png.filledcircle_blend(150, 540, 25, 0.3, 1.0, 1.0, 1.0);
    png.filledcircle_blend(500, 570, 35, 0.3, 0.9, 0.9, 0.9);
    png.filledcircle_blend(550, 590, 28, 0.3, 0.9, 0.9, 0.9);
    png.filledcircle_blend(320, 510, 28, 0.3, 0.9, 0.9, 0.9);
    png.filledcircle_blend(300, 530, 28, 0.3, 0.9, 0.9, 0.9);

    // ---------------- OCEAN ----------------
    png.filledsquare(1, 1, WIDTH, 300, 0, 30000, 60000);
    for (int i = 0; i < 6000; i++) {
        int x = rand() % WIDTH + 1;
        int y = rand() % 300 + 1;
        png.plot_blend(x, y, 0.4, 0.3, 0.5, 1.0);
    }

    // ---------------- SAND ---------------
    png.filledsquare(1, 1, WIDTH, 150, 65000, 50000, 20000);
    for (int i = 0; i < 2000; i++) {
        int x = rand() % WIDTH + 1;
        int y = rand() % 150 + 1;
        png.plot_blend(x, y, 0.5, 0.95, 0.85, 0.5);
    }

    //Tiny sparkeles on the sand just for a clean effect
    //Optional to be honest
    for (int i = 0; i < 300; i++) {
        int x = rand() % WIDTH + 1;
        int y = rand() % 150 + 1;
        double opacity = 0.7;
        int cyan = rand() % 20000;
        int magenta = rand() % 20000;
        int yellow = 45000 + rand() % 20000;
        int black = 0; 
        png.plotCMYK_blend(x, y, opacity, cyan, magenta, yellow, black);

        //Extra
        int C = 0 + rand() % 2000;
        int M = 0 + rand() % 2000;
        int Y = 45000 + rand() % 20000;
        int K = 0;
        png.plotCMYK(x, y, C, M, Y, K);
    }


    // ---------------- BEACH ROCKS ----------------
    for (int t = 0; t < 6; t++) {
        int baseX = 50 + t * 100;
        int baseY = 150;

        int rockWidth = 20 + rand() % 15;
        int rockHeight = 10 + rand() % 10;
        png.filledcircle(baseX + rockWidth / 2, baseY + rockHeight / 2, 5 + rand() % 5, 35000, 35000, 35000);
        png.filledcircle(baseX + rockWidth / 2, baseY + rockHeight / 2, 5 + rand() % 3, 35000, 35000, 35000);
        png.filledcircle(baseX + rockWidth / 2, baseY + rockHeight / 2, 5 + rand() % 6, 35000, 35000, 35000);

        png.triangle(baseX, baseY, baseX + 10, baseY + 5, baseX - 5, baseY + 8, 0.6, 0.6, 0.6);
        png.filledtriangle(baseX, baseY, baseX + 10, baseY + 5, baseX - 5, baseY + 8, 0.6, 0.6, 0.6);
        png.filledtriangle_blend(baseX, baseY, baseX + 10, baseY + 5, baseX - 5, baseY + 8, 0.4, 0.6, 0.8, 0.6);
    }

    // ---------------- SEA SHELLS ----------------
    for (int i = 0; i < 8; i++) {
        int baseX = rand() % WIDTH + 1;
        int baseY = rand() % 150 + 1;

        int shellPoints[] = {
            baseX, baseY,
            baseX + 8, baseY + 4,
            baseX + 5, baseY + 12,
            baseX - 5, baseY + 12,
            baseX - 8, baseY + 4,
            baseX, baseY
        };

        //Random color for the shell
        double r = 0.8 + (rand() % 20) / 100.0; 
        double g = 0.7 + (rand() % 30) / 100.0; 
        double b = 0.6 + (rand() % 30) / 100.0;

        png.polygon(shellPoints, 6, r * 0.6, g * 0.6, b * 0.6);
        png.polygon_blend(shellPoints, 6, 0.8, r, g, b);
    }

    // ---------------- BIRDS ----------------
    for (int i = 0; i < 15; i++) {
        int x = rand() % WIDTH;
        int y = rand() % 300 + 350;
        png.line(x, y, x + 10, y - 5, 0.0, 0.0, 0.0);
        png.line(x + 10, y - 5, x + 20, y, 0.0, 0.0, 0.0);
    }

    // ---------------- LIGHT SPARKLES ON WATER ----------------
    for (int i = 0; i < 30; i++) {
        int x = rand() % WIDTH;
        int y = rand() % 150 + 150;
        png.filledcircle_blend(x, y, 2, 0.6, 1.0, 1.0, 0.8);
        png.plotHSV_blend(x + 5, y + 3, 0.5, 45, 255, 255);
    }

    // ---------------- BEACH BALL ----------------
    int ballX = 500;
    int ballY = 80;
    int ballR = 20;
    png.circle(ballX, ballY, ballR, 0.0, 0.0, 0.0);
    png.filledcircle(ballX, ballY, ballR, 1.0, 1.0, 0.2);
    png.filledcircle(ballX - 5, ballY, ballR - 5, 1.0, 0.2, 0.2);
    png.filledcircle(ballX + 5, ballY, ballR - 5, 0.2, 0.2, 1.0);
    png.filledcircle_blend(ballX - 7, ballY + 7, 5, 0.4, 1.0, 1.0, 1.0);

    // ---------------- SAND CASTLE ----------------
    int baseX = 180;
    int baseY = 50;
    int castleW = 120;
    int castleH = 60;

    png.square(baseX, baseY, baseX + castleW, baseY + castleH, 0.4, 0.3, 0.2);
    png.filledsquare(baseX, baseY, baseX + castleW, baseY + castleH, 0.85, 0.7, 0.4);
    png.filledsquare_blend(baseX, baseY + castleH / 2, baseX + castleW, baseY + castleH, 0.3, 0.9, 0.8, 0.5);

    for (int i = 0; i < 200; i++) {
        int x = baseX + rand() % castleW;
        int y = baseY + rand() % castleH;
        png.plot_blend(x, y, 0.4, 0.75, 0.6, 0.35);
    }

    for (int i = 0; i < castleW; i += 15) {
        png.filledsquare(baseX + i, baseY + castleH, baseX + i + 8, baseY + castleH + 10, 0.85, 0.7, 0.4);
    }

    int doorW = 25, doorH = 35;
    int doorX = baseX + castleW / 2 - doorW / 2;
    png.filledsquare(doorX, baseY, doorX + doorW, baseY + doorH, 0.55, 0.4, 0.25);
    png.filledcircle(doorX + doorW / 2, baseY + doorH, doorW / 2, 0.55, 0.4, 0.25);
    png.circle(doorX + doorW / 2, baseY + doorH, doorW / 2, 0.3, 0.2, 0.1);

    int towerW = 25, towerH = 90;
    png.filledsquare(baseX - towerW + 5, baseY, baseX + 5, baseY + towerH, 0.85, 0.7, 0.4);
    png.filledsquare_blend(baseX - towerW + 5, baseY + towerH / 2, baseX + 5, baseY + towerH, 0.3, 0.9, 0.8, 0.5);
    png.square(baseX - towerW + 5, baseY, baseX + 5, baseY + towerH, 0.4, 0.3, 0.2);

    png.filledsquare(baseX + castleW - 5, baseY, baseX + castleW + towerW - 5, baseY + towerH, 0.85, 0.7, 0.4);
    png.filledsquare_blend(baseX + castleW - 5, baseY + towerH / 2, baseX + castleW + towerW - 5, baseY + towerH, 0.3, 0.9, 0.8, 0.5);
    png.square(baseX + castleW - 5, baseY, baseX + castleW + towerW - 5, baseY + towerH, 0.4, 0.3, 0.2);

    // Flags with arrows
    png.line(baseX - 5, baseY + towerH, baseX - 5, baseY + towerH + 20, 0.3, 0.2, 0.1);
    png.line_blend(baseX - 4, baseY + towerH, baseX - 4, baseY + towerH + 20, 0.2, 0.3, 0.2, 0.1);
    png.filledtriangle(baseX - 5, baseY + towerH + 20, baseX + 15, baseY + towerH + 15, baseX - 5, baseY + towerH + 10, 1.0, 0.2, 0.2);
    png.line_blend(baseX - 5, baseY + towerH + 10, baseX - 5, baseY + towerH + 20, 0.4, 1.0, 0.2, 0.2);

    png.line(baseX + castleW + towerW - 5, baseY + towerH, baseX + castleW + towerW - 5, baseY + towerH + 20, 0.3, 0.2, 0.1);
    png.line_blend(baseX + castleW + towerW - 4, baseY + towerH, baseX + castleW + towerW - 4, baseY + towerH + 20, 0.2, 0.3, 0.2, 0.1);
    png.filledtriangle(baseX + castleW + towerW - 5, baseY + towerH + 20, baseX + castleW + towerW + 15, baseY + towerH + 15, baseX + castleW + towerW - 5, baseY + towerH + 10, 1.0, 0.2, 0.2);
    png.line_blend(baseX + castleW + towerW - 5, baseY + towerH + 10, baseX + castleW + towerW - 5, baseY + towerH + 20, 0.4, 1.0, 0.2, 0.2);

    // Get image dimensions
    int imgW = png.getwidth();
    int imgH = png.getheight();

    // ---------------- LIFEGUARD SIGN ----------------
    int signX = imgW * 0.12;     
    int signY = imgH * 0.18;    
    int DH = 36;
    int DW = 36;

    // Sign outline
    png.diamond(signX, signY, DH, DW, 0.0, 0.0, 0.0);

    // Pole
    png.filledsquare(signX - 2, signY - 40, signX + 2, signY, 0.5, 0.3, 0.1);

    // Sign fill
    png.filleddiamond(signX, signY, DH, DW, 1.0, 0.2, 0.2);

    png.arrow(signX, signY - 10, signX, signY + 10, 5, 0.5, 1.0, 1.0, 1.0);
    png.filledarrow(signX - 1, signY - 10, signX + 1, signY + 10, 4, 0.5, 1.0, 1.0, 1.0);


    // ---------------- KITE ----------------
    png.filleddiamond(500, 350, 70, 80, 1.0, 0.3, 0.3);
    png.flood_fill(500, 350, 1.0, 0.3, 0.3);
    png.flood_fill_blend(500, 350, 0.5, 1.0, 0.3, 0.3);

    // Kite outline
    for (int i = 0; i <= 10; i++) {
        png.diamond(500, 350, 70 + i, 80 + i, 1.0, 0.0, 0.0);
    }

    // Design on kite
    png.cross(500, 350, 70, 5, 0.6, 0.3, 0.1);
    png.cross(500, 350, 5, 80, 0.6, 0.3, 0.1);
    png.maltesecross(500, 350, 20, 20, 6, 6, 1.0, 0.2, 0.2);

    int h = png.readHSV(500, 350, 1);
    int s = png.readHSV(500, 350, 2);
    int v = png.readHSV(500, 350, 3);
    if (s > 1000) {
        png.bezier(500, 310, 485, 270, 500, 220, 515, 240, 0.0, 0.0, 0.0);
        png.bezier_blend(500, 310, 485, 270, 500, 220, 515, 240, 0.4, 0.0, 0.0, 0.0);
    }


    // ---------------- TEXT ----------------
    char fontPath[] = "Simplisicky Fill.ttf";
    char nameLine[] = "Name: Deron Barker || ID: 400014686";
    char themeLine[] = "Theme: Sunny Beach Day";
    int fontSize = 15, xPos = 10, yPos = 10, lineGap = 10;
    png.plot_text(fontPath, fontSize, xPos, yPos, 0.0, nameLine, 1.0, 0.0, 0.0);
    png.plot_text(fontPath, fontSize, xPos, yPos + 2 * lineGap, 0.0, themeLine, 1.0, 0.0, 0.0);


    // ---------------- FINISH ----------------
    png.setcompressionlevel(-1);
    png.write_png();
    png.close();

    //Show image after code has been compiled
    system("start 400014686.png");

    return 0;
}
