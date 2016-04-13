#ifndef __RUBIK_H_
#define __RUBIK_H_

#include <cstring>
#include <map>

using namespace std;

/* How smooth the animation of rotation. makin kecil, putarannya makin halus. ANGLE in degree */
float ANGLE = 10;
const int inf = -1e9;

struct Color {
  Color() : r(0), g(0), b(0) {}
  Color(float r, float g, float b) : r(r), g(g), b(b) {}
  Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}
  void operator=(const Color& c) {
    r = c.r; g = c.g; b = c.b;
  }
  float r, g, b;
};

const Color RED     = Color(1, 0, 0);
const Color BLUE    = Color(0, 0, 1);
const Color WHITE   = Color(1, 1, 1);
const Color YELLOW  = Color(1, 1, 0);
const Color ORANGE  = Color(1, 0.5, 0);
const Color GREEN   = Color(0, 1, 0);
const Color BLACK   = Color(0, 0, 0);

/* Constant for side */
float c[54][3];  // bottom left
float d[54][3];  // bottom right
float p[54][3];  // top right
float q[54][3];  // top left

/* Constant for sceleton */
float ci[54][3];  // bottom left
float di[54][3];  // bottom right
float pi[54][3];  // top right
float qi[54][3];  // top left

Color a[54];

float sumbu[3], pusat[3];
bool isRotated[54];
float sudut;

map<unsigned char, unsigned char> vs;

void pairing(unsigned char e, unsigned char f) {
  vs[e] = f;
  vs[f] = e;
}

void bind(unsigned char e, unsigned char f) {
  pairing(e, f);
  pairing(e - 'a' + 'A', f - 'a' + 'A');
}

void rubik_init() {
  bind('a', 's');
  bind('d', 'f');
  bind('c', 'v');
  bind('y', 'u');
  bind('h', 'j');
  bind('k', 'l');
  pairing(']', '\'');
  pairing('.', '/');
  pairing('p', ';');
  pairing('P', ';');

  memset(sumbu, 0, sizeof(sumbu));
  memset(isRotated, 0, sizeof(isRotated));
  int pt = 0;

  // face
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 3; i++) {
      c[pt][0] = i + 0.1; c[pt][1] = j + 0.1; c[pt][2] = 0;
      d[pt][0] = i + 0.9; d[pt][1] = j + 0.1; d[pt][2] = 0;
      p[pt][0] = i + 0.9; p[pt][1] = j + 0.9; p[pt][2] = 0;
      q[pt][0] = i + 0.1; q[pt][1] = j + 0.9; q[pt][2] = 0;
      a[pt] = RED;
      ci[pt][0] = i + 0; ci[pt][1] = j + 0; ci[pt][2] = -0.1;
      di[pt][0] = i + 1; di[pt][1] = j + 0; di[pt][2] = -0.1;
      pi[pt][0] = i + 1; pi[pt][1] = j + 1; pi[pt][2] = -0.1;
      qi[pt][0] = i + 0; qi[pt][1] = j + 1; qi[pt][2] = -0.1;
      pt++;
    }
  }

  // right
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 3; i++) {
      c[pt][0] = 3; c[pt][1] = j + 0.1; c[pt][2] = -i - 0.1;
      d[pt][0] = 3; d[pt][1] = j + 0.1; d[pt][2] = -i - 0.9;
      p[pt][0] = 3; p[pt][1] = j + 0.9; p[pt][2] = -i - 0.9;
      q[pt][0] = 3; q[pt][1] = j + 0.9; q[pt][2] = -i - 0.1;
      a[pt] = BLUE;
      ci[pt][0] = 2.9; ci[pt][1] = j + 0; ci[pt][2] = -i;
      di[pt][0] = 2.9; di[pt][1] = j + 0; di[pt][2] = -i - 1;
      pi[pt][0] = 2.9; pi[pt][1] = j + 1; pi[pt][2] = -i - 1;
      qi[pt][0] = 2.9; qi[pt][1] = j + 1; qi[pt][2] = -i;
      pt++;
    }
  }

  // top
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 3; i++) {
      c[pt][0] = i + 0.1; c[pt][1] = 3; c[pt][2] = -j - 0.1;
      d[pt][0] = i + 0.9; d[pt][1] = 3; d[pt][2] = -j - 0.1;
      p[pt][0] = i + 0.9; p[pt][1] = 3; p[pt][2] = -j - 0.9;
      q[pt][0] = i + 0.1; q[pt][1] = 3; q[pt][2] = -j - 0.9;
      a[pt] = WHITE;
      ci[pt][0] = i + 0; ci[pt][1] = 2.9; ci[pt][2] = -j;
      di[pt][0] = i + 1; di[pt][1] = 2.9; di[pt][2] = -j;
      pi[pt][0] = i + 1; pi[pt][1] = 2.9; pi[pt][2] = -j - 1;
      qi[pt][0] = i + 0; qi[pt][1] = 2.9; qi[pt][2] = -j - 1;
      pt++;
    }
  }

  // back
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 3; i++) {
      c[pt][0] = i + 0.1; c[pt][1] = j + 0.1; c[pt][2] = -3;
      d[pt][0] = i + 0.9; d[pt][1] = j + 0.1; d[pt][2] = -3;
      p[pt][0] = i + 0.9; p[pt][1] = j + 0.9; p[pt][2] = -3;
      q[pt][0] = i + 0.1; q[pt][1] = j + 0.9; q[pt][2] = -3;
      a[pt] = ORANGE;
      ci[pt][0] = i + 0; ci[pt][1] = j + 0; ci[pt][2] = -2.9;
      di[pt][0] = i + 1; di[pt][1] = j + 0; di[pt][2] = -2.9;
      pi[pt][0] = i + 1; pi[pt][1] = j + 1; pi[pt][2] = -2.9;
      qi[pt][0] = i + 0; qi[pt][1] = j + 1; qi[pt][2] = -2.9;
      pt++;
    }
  }

  // left
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 3; i++) {
      c[pt][0] = 0; c[pt][1] = j + 0.1; c[pt][2] = -i - 0.1;
      d[pt][0] = 0; d[pt][1] = j + 0.1; d[pt][2] = -i - 0.9;
      p[pt][0] = 0; p[pt][1] = j + 0.9; p[pt][2] = -i - 0.9;
      q[pt][0] = 0; q[pt][1] = j + 0.9; q[pt][2] = -i - 0.1;
      a[pt] = GREEN;
      ci[pt][0] = 0.1; ci[pt][1] = j + 0; ci[pt][2] = -i;
      di[pt][0] = 0.1; di[pt][1] = j + 0; di[pt][2] = -i - 1;
      pi[pt][0] = 0.1; pi[pt][1] = j + 1; pi[pt][2] = -i - 1;
      qi[pt][0] = 0.1; qi[pt][1] = j + 1; qi[pt][2] = -i;
      pt++;
    }
  }

  // bottom
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 3; i++) {
      c[pt][0] = i + 0.1; c[pt][1] = 0; c[pt][2] = -j - 0.1;
      d[pt][0] = i + 0.9; d[pt][1] = 0; d[pt][2] = -j - 0.1;
      p[pt][0] = i + 0.9; p[pt][1] = 0; p[pt][2] = -j - 0.9;
      q[pt][0] = i + 0.1; q[pt][1] = 0; q[pt][2] = -j - 0.9;
      a[pt] = YELLOW;
      ci[pt][0] = i + 0; ci[pt][1] = 0.1; ci[pt][2] = -j;
      di[pt][0] = i + 1; di[pt][1] = 0.1; di[pt][2] = -j;
      pi[pt][0] = i + 1; pi[pt][1] = 0.1; pi[pt][2] = -j - 1;
      qi[pt][0] = i + 0; qi[pt][1] = 0.1; qi[pt][2] = -j - 1;
      pt++;
    }
  }
}

void reset() {
  memset(isRotated, 0, sizeof(isRotated));
  memset(sumbu, 0, sizeof(sumbu));
  sudut = 0;
}

void chain(int e, int f, int g, int h) {
  Color temp;
  temp = a[e]; a[e] = a[f]; a[f] = a[g]; a[g] = a[h]; a[h] = temp;
}

void R_before() {
  for(int i = 9; i <= 17; i++) {
    isRotated[i] = 1;
  }
  isRotated[2] = isRotated[5] = isRotated[8] = 1;
  isRotated[29] = isRotated[32] = isRotated[35] = 1;
  isRotated[20] = isRotated[23] = isRotated[26] = 1;
  isRotated[47] = isRotated[50] = isRotated[53] = 1;
  pusat[0] = 2.5; pusat[1] = 1.5; pusat[2] = -1.5;
  sumbu[0] = 1; sumbu[1] = 0; sumbu[2] = 0;
}

void R_after() {
  chain(9, 15, 17, 11);
  chain(10, 12, 16, 14);
  chain(2, 20, 35, 53);
  chain(5, 23, 32, 50);
  chain(8, 26, 29, 47);
  reset();
}

void L_before() {
  for(int i = 36; i <= 44; i++) {
    isRotated[i] = 1;
  }
  isRotated[0] = isRotated[3] = isRotated[6] = 1;
  isRotated[18] = isRotated[21] = isRotated[24] = 1;
  isRotated[27] = isRotated[30] = isRotated[33] = 1;
  isRotated[45] = isRotated[48] = isRotated[51] = 1;
  pusat[0] = 0; pusat[1] = 1.5; pusat[2] = -1.5;
  sumbu[0] = 1; sumbu[1] = 0; sumbu[2] = 0;
}

void L_after() {
  chain(9+27, 15+27, 17+27, 11+27);
  chain(10+27, 12+27, 16+27, 14+27);
  chain(0, 18, 33, 51);
  chain(3, 21, 30, 48);
  chain(6, 24, 27, 45);
  reset();
}

void U_before() {
  for(int i = 18; i <= 26; i++) {
    isRotated[i] = 1;
  }
  isRotated[6] = isRotated[7] = isRotated[8] = 1;
  isRotated[15] = isRotated[16] = isRotated[17] = 1;
  isRotated[33] = isRotated[34] = isRotated[35] = 1;
  isRotated[42] = isRotated[43] = isRotated[44] = 1;
  pusat[0] = 1.5; pusat[1] = 2.5; pusat[2] = -1.5;
  sumbu[0] = 0; sumbu[1] = 1; sumbu[2] = 0;
}

void U_after() {
  chain(26, 20, 18, 24);
  chain(23, 19, 21, 25);
  chain(17, 8, 42, 33);
  chain(16, 7, 43, 34);
  chain(15, 6, 44, 35);
  reset();
}

void D_before() {
  for(int i = 18+27; i <= 26+27; i++) {
    isRotated[i] = 1;
  }
  isRotated[0] = isRotated[1] = isRotated[2] = 1;
  isRotated[9] = isRotated[10] = isRotated[11] = 1;
  isRotated[27] = isRotated[28] = isRotated[29] = 1;
  isRotated[36] = isRotated[37] = isRotated[38] = 1;
  pusat[0] = 1.5; pusat[1] = 0.5; pusat[2] = -1.5;
  sumbu[0] = 0; sumbu[1] = 1; sumbu[2] = 0;
}

void D_after() {
  chain(26+27, 20+27, 18+27, 24+27);
  chain(23+27, 19+27, 21+27, 25+27);
  chain(11, 2, 36, 27);
  chain(10, 1, 37, 28);
  chain(9, 0, 38, 29);
  reset();
}

void F_before() {
  for(int i = 0; i <= 8; i++) {
    isRotated[i] = 1;
  }
  isRotated[9] = isRotated[12] = isRotated[15] = 1;
  isRotated[18] = isRotated[19] = isRotated[20] = 1;
  isRotated[36] = isRotated[39] = isRotated[42] = 1;
  isRotated[45] = isRotated[46] = isRotated[47] = 1;
  pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -0.5;
  sumbu[0] = 0; sumbu[1] = 0; sumbu[2] = 1;
}

void F_after() {
  chain(6, 8, 2, 0);
  chain(7, 5, 1, 3);
  chain(18, 15, 47, 36);
  chain(19, 12, 46, 39);
  chain(20, 9, 45, 42);
  reset();
}

void B_before() {
  for(int i = 0+27; i <= 8+27; i++) {
    isRotated[i] = 1;
  }
  isRotated[11] = isRotated[14] = isRotated[17] = 1;
  isRotated[24] = isRotated[25] = isRotated[26] = 1;
  isRotated[38] = isRotated[41] = isRotated[44] = 1;
  isRotated[51] = isRotated[52] = isRotated[53] = 1;
  pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -2.5;
  sumbu[0] = 0; sumbu[1] = 0; sumbu[2] = 1;
}

void B_after() {
  chain(6+27, 8+27, 2+27, 0+27);
  chain(7+27, 5+27, 1+27, 3+27);
  chain(24, 17, 53, 38);
  chain(25, 14, 52, 41);
  chain(26, 11, 51, 44);
  reset();
}

void down_before() {
  for(int i = 0; i < 54; i++) isRotated[i] = 1;
  pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -1.5;
  sumbu[0] = 1; sumbu[1] = 0; sumbu[2] = 0;
}

void down_after() {
  chain(9, 15, 17, 11);
  chain(12, 16, 14, 10);
  chain(9+27, 15+27, 17+27, 11+27);
  chain(12+27, 16+27, 14+27, 10+27);
  chain(0, 18, 6+27, 24+27);
  chain(1, 19, 7+27, 25+27);
  chain(2, 20, 8+27, 26+27);
  chain(3, 21, 3+27, 21+27);
  chain(4, 22, 4+27, 22+27);
  chain(5, 23, 5+27, 23+27);
  chain(6, 24, 0+27, 18+27);
  chain(7, 25, 1+27, 19+27);
  chain(8, 26, 2+27, 20+27);
  reset();
}

void right_before() {
  for(int i = 0; i < 54; i++) isRotated[i] = 1;
  pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -1.5;
  sumbu[0] = 0; sumbu[1] = 1; sumbu[2] = 0;
}

void right_after() {
  chain(20, 18, 24, 26);
  chain(19, 21, 25, 23);
  chain(20+27, 18+27, 24+27, 26+27);
  chain(19+27, 21+27, 25+27, 23+27);
  chain(9, 0, 11+27, 2+27);
  chain(10, 1, 10+27, 1+27);
  chain(11, 2, 9+27, 0+27);
  chain(12, 3, 14+27, 5+27);
  chain(13, 4, 13+27, 4+27);
  chain(14, 5, 12+27, 3+27);
  chain(15, 6, 17+27, 8+27);
  chain(16, 7, 16+27, 7+27);
  chain(17, 8, 15+27, 6+27);
  reset();
}

void through_before() {
  for(int i = 0; i < 54; i++) isRotated[i] = 1;
  pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -1.5;
  sumbu[0] = 0; sumbu[1] = 0; sumbu[2] = 1;
}

void through_after() {
  chain(6, 8, 2, 0);
  chain(7, 5, 1, 3);
  chain(6+27, 8+27, 2+27, 0+27);
  chain(7+27, 5+27, 1+27, 3+27);
  chain(18, 15, 20+27, 9+27);
  chain(19, 12, 19+27, 12+27);
  chain(20, 9, 18+27, 15+27);
  chain(21, 16, 23+27, 10+27);
  chain(22, 13, 22+27, 13+27);
  chain(23, 10, 21+27, 16+27);
  chain(24, 17, 26+27, 11+27);
  chain(25, 14, 25+27, 14+27);
  chain(26, 11, 24+27, 17+27);
  reset();
}

#endif