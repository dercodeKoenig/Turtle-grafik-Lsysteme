#pragma comment(lib, "GL/freeglut/lib/freeglut.lib")
#include "Gl/freeglut/include/GL/freeglut.h"

#include<fstream>
#include<string>
#include<iostream>
#include<vector>
#include<math.h>

#include"argparse.cpp"
#include"lsys.cpp"


std::string text,t2;
bool x = 0;
std::string zahl;
float zahli = 1;
bool schreiben=1;
float st = 0;
int i2 = 0;
float sc = 100;
float winkel=0;
float pos_x=0;
float pos_y=0;

struct speicher{
float winkel=0;
float posx=0;
float posy=0;
};
std::vector<speicher>stack;
float breitew=0;
float breiteh=0;
float max_x=0,max_y=0;
float min_x=0,min_y=0;
int i=0;
bool first=0;
float tfx=0;
float tfy=0;
int schnelles_zeichnen=1;
int n=0;
void display() {
	if(!first){
		first=1;
		text = t2;
		pos_x=0;
		pos_y=0;
		::glLoadIdentity();
		winkel=0;
		glScalef(sc / 100, sc / 100, sc / 100);
		glClear(GL_COLOR_BUFFER_BIT);
		glTranslatef(tfx/100.0,tfy/100.0,0);
		i = 0;
	}
	

	
		if (text[i] == 'r') {
			i++;
			std::string zahl;
			
				for (; i < text.size(); i++) {
					if (text[i] >= '0' && text[i] <= '9'||t2[i]=='.'||t2[i]=='-') {
						zahl += text[i];
					}
					else { i--; break; }
				}
				zahli = ::atof(zahl.c_str());
			
			zahl.clear();
			winkel+=zahli;
		}
		if(text[i]=='['){
			speicher b;
			b.winkel=winkel;
			b.posx=pos_x;
			b.posy=pos_y;
			stack.push_back(b);
		}
		if(text[i]==']'){
			speicher b=stack[stack.size()-1];
			winkel=b.winkel;
			pos_x=b.posx;
			pos_y=b.posy;
			stack.erase(stack.begin()+stack.size()-1);
		}
		if (text[i] == 'd') { schreiben = 1; }
		if (text[i] == 'u') { schreiben = 0; }
		if (text[i] == 'f') {
			i++;
			std::string zahl;
			
				for (; i < text.size(); i++) {
					if (text[i] >= '0' && text[i] <= '9' ||t2[i]=='.') {
						zahl += text[i];
					}
					else { i--; break; }
				}
				zahli = ::atof(zahl.c_str());
			zahl.clear();
			float nposx=pos_x+cos(winkel*3.14159265359/180.0)*zahli;
			float nposy=pos_y+sin(winkel*3.14159265359/180.0)*zahli;
			if (schreiben) {
				::glBegin(GL_LINE_STRIP);
				::glVertex2f(pos_x/100.0, pos_y/100.0);
				::glVertex2f(nposx/100.0,nposy/100.0);
				::glEnd();
			}

			
			pos_x=nposx;
			pos_y=nposy;
			if(max_x<pos_x)max_x=pos_x;
			if(max_y<pos_y)max_y=pos_y;
			if(min_x>pos_x)min_x=pos_x;
			if(min_y>pos_y)min_y=pos_y;
		}
	

	if(i+1<text.size()){
		i++;
		n++;

		if(sc!=0){
			if(n==schnelles_zeichnen){	
				glFlush();
				n=0;
			}
		}else n=0;
		
		glutPostRedisplay();
	}else {glFlush();
		if(sc==0){
			first=0;
			float scnx=breitew/(max_x-min_x)*100;
			float scny=breiteh/(max_y-min_y)*100;

			scnx>scny?sc=scny/5.0:sc=scnx/5.0;

			float mx=(max_x-(max_x-min_x)/2.0);
			float my=(max_y-(max_y-min_y)/2.0);
			tfx=-mx;
			tfy=-my;
			
		glutPostRedisplay();
		}
	}
}
void ersetzen(std::string& text, std::string alt, std::string neu) {
	for (size_t x = text.find(alt); x != std::string::npos; x = text.find(alt, x + neu.length()))
		text.replace(x, alt.length(), neu);
}
int main(int argc, char* argv[]) {
  std::string inname;

  argparse::ArgumentParser parser(argv[0], "Argument parser example");

  parser.add_argument("-i", "--input", "input", true);
  parser.add_argument("-s", "--speed", "speed", false);
  parser.add_argument("-r", "--iterations", "iterations", false);

  parser.enable_help();
  auto err = parser.parse(argc, (const char**)argv);
  if (err) {
    std::cout << err << std::endl;
    return -1;
  }

  int n=0;
  if (parser.exists("help")) {
    parser.print_help();
    return 0;
  }

  if (parser.exists("input")) {
	inname = parser.get<std::string>("input");
  }

  if (parser.exists("speed")) {
	schnelles_zeichnen = parser.get<int>("speed");
  }
  if (parser.exists("iterations")) {
	n = parser.get<int>("iterations");
  }





	std::ifstream in(inname,std::ios::binary);
	if (in){
	char x;
		while (in.get(x)) {
			t2 += x;
		}
	}
	in.close();
	if (t2[t2.size() - 1] != '\n')t2 += "\n";
	t2=lsys::mainfunc(t2,n);
	std::string w, h, lw, s;
	float wi, hi, lwi, si;
	int f = 0;
	for (int i = 0; i < t2.size(); i++) {
		if (t2[i] == 'x') { f++; continue; }
		if (t2[i] == '\n')break;
		(f == 0) ? w += t2[i] : (f == 1) ? h += t2[i] : (f == 2) ? lw += t2[i] : s += t2[i];
	}
	lwi = atoi(lw.c_str());
	wi = atoi(w.c_str());
	hi = atoi(h.c_str());
	si = atof(s.c_str());
	sc = si;
	std::string zeile;
	std::string tc;
	bool k = 0;
	int clpos=0;
	int r = 0;
	bool rn = 1;


	while (rn) {
		for (int m = 0; m < t2.size(); m++) {
			if (k)tc += t2[m];
			if (t2[m] == '\n') {
				if (zeile.size() > 0) {
					if (zeile[0] == 'L') {
						clpos = m - zeile.size();
						k = 1;
						tc.clear();
						zeile.replace(0, 1, "");
						r = atoi(zeile.c_str());
					}
					if (zeile[0] == 'E') {
						zeile.replace(0, 1, "");
						k = 0;
						std::string nst;
						for (int q = 0; q < r; q++) {
							nst += tc;
						}
						t2.replace(clpos, tc.size()+4	, nst);
						zeile.clear();
						tc.clear();
						continue;
					}
				}
				zeile.clear();
			}
			else zeile += t2[m];
		}
		if (!strstr(t2.c_str(), "l"))rn = 0;
	}

	::glutInit(&argc, argv);
	::glutInitDisplayMode(GLUT_RGB);
	::glutInitWindowSize(wi, hi);	
	breitew=wi;
	breiteh=hi;
	::glutCreateWindow("");
	::glClearColor(0.2, 0.2, 0.2, 1);
	::glutDisplayFunc(display);
	::glLineWidth(lwi);
	::glColor3f(1, 1, 1);
	::glutMainLoop();
}
