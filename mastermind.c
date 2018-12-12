/* Mastermind with Turbo C
 *  Sylvain Saurel (sylvain.saurel@gmail.com) - 1999
 */

#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

typedef int code[4];
typedef int coul[6];

int noire(code t, code tab) {
  int a, nbre;
  a = 0;
  nbre = 0;

  while (a < 4) {
    if (t[a] == tab[a]) {
      nbre = nbre + 1;
    }
    
    a = a + 1;
  }

  return nbre;

}

int blanche(code t, code tab) {
  int a, b, nbre, occ, occ1;
  a = 0;
  nbre = 0;

  while (a < 4) {
    b = 0;
    occ = 0;
    occ1 = 0;

    while (b < 4) {
      if (a == b && t[a] == tab[b]) {
        occ = 0;
        occ1 = occ1 + 1;

      } else if (t[a] == tab[b] && a != b && occ < 1 && occ1 < 1) {
        occ = occ + 1;
      }
      b = b + 1;
    }
    nbre = nbre + occ;
    a = a + 1;
  }

  return nbre;

}

main() {

  int pilote, mode, t, i, j, k, z, mouv, x1, y1, cle_b, cle_n, color, cel, essai, diff, x2, y2;
  code code_secret;
  code proposition;
  coul couleur={0,1,2,15,4,14};

  char g[5];
  char h[5];

  srand(time(0));

  clrscr();

  code_secret[0] = rand() % 6 + 1;
  i = 1;

  while (i < 4) {
    code_secret[i] = rand() % 6 + 1;
    j = 0;

    while (j < i) {
      if (code_secret[i] == code_secret[j]) {
        code_secret[i] = rand() % 6 + 1;
        j = 0;

      } else {
        j = j + 1;

      }
    }
    i = i + 1;

  }

  detectgraph( & pilote, & mode);
  initgraph( & pilote, & mode, "c:\\tc");

  t = 30;

  setfillstyle(1, 9);
  floodfill(0, 0, 9);

  setcolor(15);
  outtextxy(270, 20, "Mastermind");
  outtextxy(20, 100, "Touches :");
  outtextxy(20, 115, "0 -> Valider");
  outtextxy(20, 125, "1 -> Noir");
  outtextxy(20, 135, "2 -> Bleu");
  outtextxy(20, 145, "3 -> Vert");
  outtextxy(20, 155, "4 -> Blanc");
  outtextxy(20, 165, "5 -> Rouge");
  outtextxy(20, 175, "6 -> Jaune");
  outtextxy(20, 185, "7 -> Gauche");
  outtextxy(20, 195, "8 -> Droite");
  outtextxy(20, 205, "9 -> Sortie");

  setcolor(15);

  rectangle(200, 400, 200 + 4 * t, 400 - 10 * t);

  for (k = 1; k < 4; k = k + 1) {
    line(200 + k * t, 400, 200 + k * t, 400 - 10 * t);
  }

  for (z = 1; z < 10; z = z + 1) {
    line(200, 400 - z * t, 200 + 4 * t, 400 - z * t);
  }

  rectangle(4 * t + 250, 400, 6 * t + 250, 400 - 10 * t);
  line(5 * t + 250, 400, 5 * t + 250, 400 - 10 * t);

  for (k = 1; k < 10; k = k + 1) {
    line(4 * t + 250, 400 - k * t, 6 * t + 250, 400 - k * t);
  }

  rectangle(200, 460, 200 + 4 * t, 460 - t);

  for (k = 1; k < 4; k = k + 1) {
    line(200 + k * t, 460, 200 + k * t, 460 - t);
  }

  setcolor(7);
  x1 = 200 + t / 2;
  y1 = 400 - 10 * t + t / 2;
  circle(x1, y1, t / 4);

  cel = 0;
  essai = 0;
  cle_n = 0;

  mouv = getch();

  while (mouv != '9' && essai <= 10 && cle_n != 4) {
    switch (mouv) {
    case '1':
      setfillstyle(1, 0);
      floodfill(x1, y1, 7);
      proposition[cel] = 1;
      break;

    case '2':
      setfillstyle(1, 1);
      floodfill(x1, y1, 7);
      proposition[cel] = 2;
      break;

    case '3':
      setfillstyle(1, 2);
      floodfill(x1, y1, 7);
      proposition[cel] = 3;
      break;

    case '4':
      setfillstyle(1, 15);
      floodfill(x1, y1, 7);
      proposition[cel] = 4;
      break;

    case '5':
      setfillstyle(1, 4);
      floodfill(x1, y1, 7);
      proposition[cel] = 5;
      break;

    case '6':
      setfillstyle(1, 14);
      floodfill(x1, y1, 7);
      proposition[cel] = 6;
      break;

    case '7':
      if (x1 > 200 + t / 2) {
        setcolor(9);
        circle(x1, y1, t / 4);
        setcolor(7);
        x1 = x1 - t;
        circle(x1, y1, t / 4);
        cel = cel - 1;
      }
      break;

    case '8':
      if (x1 < 200 + 4 * t - t / 2) {
        setcolor(9);
        circle(x1, y1, t / 4);
        x1 = x1 + t;
        setcolor(7);
        circle(x1, y1, t / 4);
        cel = cel + 1;
      }
      break;

    case '0':

      i = 0;
      diff = 0;
      while (i < 4 && diff == 0) {
        j = 1;
        while (j <= 6 && proposition[i] != j) {
          j = j + 1;

        }

        if (j == 7) {
          diff = 1;
        } else {
          diff = 0;
        }

        i = i + 1;
      }

      if (diff == 0) {
        cle_b = blanche(code_secret, proposition);
        cle_n = noire(code_secret, proposition);

        sprintf(g, "%d", cle_n);
        sprintf(h, "%d", cle_b);

        setcolor(15);

        outtextxy(382, y1, g);
        outtextxy(412, y1, h);

      }

      setcolor(9);
      circle(x1, y1, t / 4);

      if (cle_n != 4 && essai < 10 && diff == 0) {
        x1 = 200 + t / 2;
        y1 = y1 + t;
        essai = essai + 1;
        cel = 0;

        k = 0;
        while (k < 4) {
          proposition[k] = 0;
          k = k + 1;
        }
      }

      if (cle_n == 4 || essai == 10) {
        k = 0;

        while (k < 4) {
          x2 = 200 + t / 2 + k * t;
          y2 = 460 - 30 + t / 2;
          color = code_secret[k] - 1;
          setcolor(7);
          circle(x2, y2, t / 4);
          setfillstyle(1, couleur[color]);
          floodfill(x2 + 1, y2 - 1, 7);
          k = k + 1;
        }

        if (cle_n == 4) {
          setcolor(15);
          outtextxy(250, 60, "Vous avez gagné !");

        } else {
          setcolor(15);
          outtextxy(250, 60, "Vous avez perdu !");

        }

      }

      if (essai != 10) {
        setcolor(7);
        circle(x1, y1, t / 4);
      }

      break;

    }

    mouv = getch();

  }

  closegraph();

}
