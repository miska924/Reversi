#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

int myc;

bool normal(int x, int y) {
	return (0 <= x && x < 8) && (0 <= y && y < 8);
}

bool get(int a[8][8], int c, int x, int y, int dx, int dy, bool paint) {
	bool flag = false;
	bool was = false;
    for (int i = 1; normal(x + dx * i, y + dy * i); ++i) {
        if (a[x + dx * i][y + dy * i] == -1) break;
		if (a[x + dx * i][y + dy * i] == !c) was = true;
        if (a[x + dx * i][y + dy * i] == c) {
			flag = true;
			break;
		}
    }
	if (paint && flag && was) {
		for (int i = 1; normal(x + dx * i, y + dy * i); ++i) {
			if (a[x + dx * i][y + dy * i] == -1) break;
			if (a[x + dx * i][y + dy * i] == !c) was = true;
			if (a[x + dx * i][y + dy * i] == c) {
				flag = true;
				break;
			}
			a[x + dx * i][y + dy * i] = c;
		}
	} 
	return flag && was;
}

bool check(int a[8][8], int c, int x, int y) {
	if (a[x][y] != -1) return false;
	bool flag = false;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (i | j) {
				if (get(a, c, x, y, i, j, false)) {
					flag = true;
					break;
				}
			}
		}
	}
	return flag;
}

vector<pair<int, int> > can(int a[8][8], int c) {
	vector<pair<int, int> > res;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (check(a, c, i, j)) res.push_back({i, j});
		}
	}
	return res;
}

void f1(int& cnt, int i, int j, int b[8][8][3][3][2]) {
	if (b[i][j][1 + 1][1 + 1][0] == min(8 - i, 8 - j) ||
		b[i][j][-1 + 1][-1 + 1][0] == min(i + 1, j + 1) ||
		(b[i][j][1 + 1][1 + 1][1] == min(8 - i, 8 - j) + 1 &&
		b[i][j][-1 + 1][-1 + 1][1] == min(i + 1, j + 1) + 1))
			++cnt;
	if (b[i][j][-1 + 1][1 + 1][0] == min(i + 1, 8 - j) ||
		b[i][j][1 + 1][-1 + 1][0] == min(8 - i, j + 1) ||
		(b[i][j][-1 +1][1 + 1][1] == min(i + 1, 8 - j) + 1 &&
		b[i][j][1 + 1][-1 + 1][1] == min(8 - i, j + 1) + 1))
			++cnt;
	if (b[i][j][0 + 1][1 + 1][0] == 8 - j ||
		b[i][j][0 + 1][-1 + 1][0] == j + 1 ||
		(b[i][j][0 + 1][1 + 1][1] == 8 - j + 1 &&
		b[i][j][0 + 1][-1 + 1][1] == j + 1 + 1))
			++cnt;
	if (b[i][j][1 + 1][0 + 1][0] == 8 - i ||
		b[i][j][-1 + 1][0 + 1][0] == i + 1 ||
		(b[i][j][1 + 1][0 + 1][1] == 8 - i + 1 &&
		b[i][j][-1 + 1][0 + 1][1] == i + 1 + 1))
			++cnt;
}

void f2(int& cnt, int i, int j, int b[8][8][3][3][2]) {
	if (b[i][j][1 + 1][1 + 1][0] == min(8 - i, 8 - j) ||
		b[i][j][-1 + 1][-1 + 1][0] == min(i + 1, j + 1))
			++cnt;
	if (b[i][j][-1 + 1][1 + 1][0] == min(i + 1, 8 - j) ||
		b[i][j][1 + 1][-1 + 1][0] == min(8 - i, j + 1))
			++cnt;
	if (b[i][j][0 + 1][1 + 1][0] == 8 - j ||
		b[i][j][0 + 1][-1 + 1][0] == j + 1)
			++cnt;
	if (b[i][j][1 + 1][0 + 1][0] == 8 - i ||
		b[i][j][-1 + 1][0 + 1][0] == i + 1)
			++cnt;
}

void put(int a[8][8], int c, int x, int y) {
    a[x][y] = c;
    for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (i | j) {
				get(a, c, x, y, i, j, true);
			}
		}
	}
}

int score(int a[8][8], int c) {
	int res = 0;
	int b[8][8][3][3][2];
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			for (int k = -1; k < 1; ++k) {
				for (int l = -1; l < 1; ++l) {
					b[i][j][k + 1][l + 1][0] = 1;
					if (normal(i + k, j + l) && a[i][j] == a[i + k][j + l])
						b[i][j][k + 1][l + 1][0] = b[i + k][j + l][k + 1][l + 1][0] + 1;

					b[i][j][k + 1][l + 1][1] = 1;
					if (normal(i + k, j + l) && a[i + k][j + k] != -1)
						b[i][j][k + 1][l + 1][1] = b[i + k][j + l][k + 1][l + 1][1] + 1;

					if (a[i][j] == -1) {
						b[i][j][k + 1][l + 1][0] = 0;
						b[i][j][k + 1][l + 1][1] = 0;
					}
				}
			}
		}
	}

	for (int i = 7; i >= 0; --i) {
		for (int j = 7; j >= 0; --j) {
			for (int k = 0; k < 2; ++k) {
				for (int l = 0; l < 2; ++l) {
					b[i][j][k + 1][l + 1][0] = 1;
					if (normal(i + k, j + l) && a[i][j] == a[i + k][j + l])
						b[i][j][k + 1][l + 1][0] = b[i + k][j + l][k + 1][l + 1][0] + 1;

					b[i][j][k + 1][l + 1][1] = 1;
					if (normal(i + k, j + l) && a[i + k][j + k] != -1)
						b[i][j][k + 1][l + 1][1] = b[i + k][j + l][k + 1][l + 1][1] + 1;

					if (a[i][j] == -1) {
						b[i][j][k + 1][l + 1][0] = 0;
						b[i][j][k + 1][l + 1][1] = 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 7; j >= 0; --j) {
			int k = -1, l = 1;
			b[i][j][k + 1][l + 1][0] = 1;
			if (normal(i + k, j + l) && a[i][j] == a[i + k][j + l])
				b[i][j][k + 1][l + 1][0] = b[i + k][j + l][k + 1][l + 1][0] + 1;
			
			b[i][j][k + 1][l + 1][1] = 1;
			if (normal(i + k, j + l) && a[i + k][j + k] != -1)
				b[i][j][k + 1][l + 1][1] = b[i + k][j + l][k + 1][l + 1][1] + 1;
			
			if (a[i][j] == -1) {
				b[i][j][k + 1][l + 1][0] = 0;
				b[i][j][k + 1][l + 1][1] = 0;
			}
		}
	}

	for (int i = 7; i >= 0; --i) {
		for (int j = 0; j < 8; ++j) {
			int k = 1, l = -1;
			b[i][j][k + 1][l + 1][0] = 1;
			if (normal(i + k, j + l) && a[i][j] == a[i + k][j + l])
				b[i][j][k + 1][l + 1][0] = b[i + k][j + l][k + 1][l + 1][0] + 1;

			b[i][j][k + 1][l + 1][1] = 1;
			if (normal(i + k, j + l) && a[i + k][j + k] != -1)
				b[i][j][k + 1][l + 1][1] = b[i + k][j + l][k + 1][l + 1][1] + 1;
			if (a[i][j] == -1) {
				b[i][j][k + 1][l + 1][0] = 0;
				b[i][j][k + 1][l + 1][1] = 0;
			}
		}
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int cnt = 0;
			f1(cnt, i, j, b);
			if (cnt == 4) {
				if (a[i][j] == c) res += 100;
				else if (a[i][j] == !c) res -= 100;
			} else {
				if (a[i][j] == c) res++;
				else if (a[i][j] == !c) res--;
			}
		}
	}

	return res;
}

int calc(int a[8][8], int c, int x, int y, int h, int alpha, int beta) {
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (i | j) {
				get(a, c, x, y, i, j, true);
			}
		}
	}
	a[x][y] = c;
	c = !c;
	vector<pair<int, int> > s = can(a, c);
	if (s.empty()) {
		c = !c;
		s = can(a, c);
	}
	if (h >= 5 || s.empty()) {
		return score(a, myc);
	}
	int optimal;
	if (c == myc) optimal = -100000;
	else optimal = 100000;
	for (size_t i = 0; i < s.size(); ++i) {
		int was[8][8];
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				was[i][j] = a[i][j];
			}
		}
		int now = calc(a, c, s[i].first, s[i].second, h + 1, alpha, beta);
		if (c == myc && now > optimal) optimal = now;
		else if (c != myc && now < optimal) optimal = now;
		if (c == myc) {
			alpha = max(alpha, optimal);
			if (beta <= alpha) return optimal;
		} else {
			beta = min(beta, optimal);
			if (beta <= alpha) return optimal;
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				a[i][j] = was[i][j];
			}
		}
	}
	return optimal;
}

void move(int a[8][8], int c, int& x, int& y) {
	myc = c;
	int was[8][8];
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			was[i][j] = a[i][j];
		}
	}
	vector<pair<int, int> > s = can(was, c);
	int maxres = -1000000;
	int alpha = -100000, beta = 100000;
	int ansx = 0, ansy = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				was[i][j] = a[i][j];
			}
		}
		int now = calc(was, c, s[i].first, s[i].second, 0, alpha, beta);
		if (now > maxres) {
			ansx = s[i].first;
			ansy = s[i].second;
			maxres = now;
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				was[i][j] = a[i][j];
			}
		}
	}

	//cerr << "score : " << score(was, myc) << "  will : " << maxres << endl;
    //cerr << *x << " " << *y << endl;
	x = ansx;
	y = ansy;
}

void draw_field(int a[8][8], string s) {
    system("clear");
    cout << "you are " << s << endl;
    cout << "  ";
    for (int i = 1; i < 9; ++i) cout << i << " ";
    cout << endl;
    for (int i = 0; i < 8; ++i) {
        cout << i + 1 << " ";
        for (int j = 0;j < 8; ++j) {
            if (a[i][j] == -1) cout << ". ";
            if (a[i][j] == 0) cout << "W ";
            if (a[i][j] == 1) cout << "B ";
        }
        cout << endl;
    }
    cout << endl;
}

void copy(int a[8][8], int b[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            a[i][j] = b[i][j];
        }
    }
}

void sleep(double t) {
    double tim = time(0);
    while(time(0) - tim < t) {}
}


float WinWid = 400.0;
float WinHei = 400.0;
float Angle = 0.0, Scale = 1.0;

float mx, my;
bool pressed = false;

int a[8][8];
int now, color;
vector<pair<int, int> > c;
string s;

void MouseMove(int ax, int ay)
{
	mx = ax;
	my = ay;
	//glutSetWindowTitle("MouseMove called");
}

void MousePressed(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON: 
		switch(state)
		{
		case GLUT_UP: 
			//glutSetWindowTitle("Left button released");
			break;
		case GLUT_DOWN:
			//glutSetWindowTitle("Left button pressed");
			pressed = true;
			break;
		}
		break;
	case GLUT_MIDDLE_BUTTON: 
		switch(state)
		{
		case GLUT_UP: 
			//glutSetWindowTitle("Middle button released");
			break;
		case GLUT_DOWN: 
			//glutSetWindowTitle("Middle button pressed");
			break;
		}
		break;
	case GLUT_RIGHT_BUTTON: 
		switch(state)
		{
		case GLUT_UP: 
			//glutSetWindowTitle("Right button released");
			break;
		case GLUT_DOWN:
			//glutSetWindowTitle("Right button pressed");
			break;
		}
	}
}

void MousePressedMove(int ax, int ay)
{
	mx = ax;
	my = ay;
	//glutSetWindowTitle("MousePressedMove called");
}

bool was = false;

void Textout(string str, GLfloat red, GLfloat green, GLfloat blue, int y)
{
	int x = -20.0 * (double(str.size()) / 2.0);
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    int i = 0;
    while (i < str.size())
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
        glRasterPos2f(x + ++i * 20, y);
    }
}

bool end_ = false;
int sc[2];

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
  double brightness = 1; 
	if (end_ == true) {
    brightness = 0.3;
	}
  if (was == false) {
		glBegin(GL_QUADS);
			glColor4f(brightness, brightness, brightness, 1);
			glVertex2f(-200, -200);
			glVertex2f(-200, 200);
			glVertex2f(0, 200);
			glVertex2f(0, -200);

			glColor4f(0, 0, 0, 1);
			glVertex2f(0, -200);
			glVertex2f(0, 200);
			glVertex2f(200, 200);
			glVertex2f(200, -200);
		glEnd();
	} else {
		glBegin(GL_LINES);
		glColor4f(brightness, brightness, brightness, 1);
			for (int i = -160; i <= 160; i += 40) {
				glVertex2f(i, -160);
				glVertex2f(i, 160);
			}
			for (int i = -160; i <= 160; i += 40) {
				glVertex2f(-160, i);
				glVertex2f(160, i);
			}
		glEnd();
		glBegin(GL_QUADS);
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					float delta = 0;
					for (int k = 0; k < c.size(); ++k) {
						if (c[k] == pair<int, int>{i, j}) {
							delta = 9;
							break;
						}
					}
					if (a[i][j] == -1) glColor4f(brightness * !now, brightness * !now, brightness * !now, 1);
					else if (a[i][j] == 1) glColor4f(0, 0, 0, 1);
					else glColor4f(brightness, brightness, brightness, 1);

					float lol1 = rand() % 3 - 1;
					float lol2 = rand() % 3 - 1;
					lol1 /= 2.0;
					lol2 /= 2.0;
					lol1 = 0;
					lol2 = 0;
					if (delta == 9) {
						glVertex2f(float(j * 40 - 160 + 5) + delta + lol1, -(float(i * 40 - 160 + 5) + delta) + lol2);
						glVertex2f(float(j * 40 - 160 + 40 - 5) - delta + lol1, -(float(i * 40 - 160 + 5) + delta) + lol2);
						glVertex2f(float(j * 40 - 160 + 40 - 5) - delta + lol1, -(float(i * 40 - 160 + 40 - 5) - delta) + lol2);
						glVertex2f(float(j * 40 - 160 + 5) + delta + lol1, -(float(i * 40 - 160 + 40 - 5) - delta) + lol2);
					} else if (a[i][j] != -1) {
						glVertex2f(float(j * 40 - 160 + 5) + delta, -(float(i * 40 - 160 + 5) + delta));
						glVertex2f(float(j * 40 - 160 + 40 - 5) - delta, -(float(i * 40 - 160 + 5) + delta));
						glVertex2f(float(j * 40 - 160 + 40 - 5) - delta, -(float(i * 40 - 160 + 40 - 5) - delta));
						glVertex2f(float(j * 40 - 160 + 5) + delta, -(float(i * 40 - 160 + 40 - 5) - delta));
					}
				}
			}
		glEnd();
	}

	if (end_ == true) {
		for (int i = 0; i < 100000000; ++i);
    	Textout(string("BLACK : ") + to_string(sc[1]), 1, 1, 1, 40);
    	Textout(string("WHITE : ") + to_string(sc[0]), 1, 1, 1, 0);
		if (sc[color] < sc[!color]) Textout("YOU LOST", 1, 1, 1, -40);
		if (sc[color] == sc[!color]) Textout("IT IS DRAW", 1, 1, 1, -40);
		if (sc[color] > sc[!color]) Textout("YOU WIN", 1, 1, 1, -40);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Timer(int value) {
	if (was == false) {
		Draw();
		int x = -1, y = -1;
        while (true) {
            if (!pressed) {
				//now = !now;
				glutTimerFunc(50, Timer, 1);
				return;
			}
			x = mx;
			y = my;
			pressed = false;
            if (x < 0 || WinHei < x) continue;
			if (y < 0 || WinWid < y) continue;
			if (x < WinWid / 2) color = 0;
			else color = 1;
			break;
        }
		was = true;
		glutTimerFunc(50, Timer, 1);
	}
	if (!(!can(a, 0).empty() || !can(a, 1).empty())) {
		c.resize(0);
		Draw();
		sc[0] = sc[1] = 0;
    	for (int i = 0; i < 8; ++i) {
    	    for (int j = 0; j < 8; ++j) {
    	        if (a[i][j] == -1) continue;
    	        sc[a[i][j]]++;
    	    }
    	}
		end_ = true;
		Draw();
    	/*cout << "black : " << sc[1] << endl;
    	cout << "white : " << sc[0] << endl;
    	if (sc[color] > sc[!color]) cout << "<<<<<YOU WON>>>>>" << endl;
    	else if (sc[color] < sc[!color]) cout << "<<<<<YOU LOST>>>>>" << endl;
    	else cout << "<<<IT IS A DRAW>>>" << endl;*/
		return;
	};
	now = !now;
    c = can(a, now);
    if (c.empty()) {
		glutTimerFunc(50, Timer, 1);
		return;
	}
	Draw();
    if (now == color) {
        int x = -1, y = -1;
        bool flag = false;
        while (!flag) {
            if (!pressed) {
				now = !now;
				glutTimerFunc(50, Timer, 1);
				return;
			}
			x = int(my / 40) - 1;
			y = int(mx / 40) - 1;
			pressed = false;
            for (size_t  i = 0; i < c.size(); ++i) {
                if (c[i].first == x && c[i].second == y) {
                    flag = true;
                    break;
                }
            }
        }
		//cout << "your turn: " << x + 1 << " " << y + 1 << endl;
        put(a, now, x, y);
    } else {
        int was[8][8];
        copy(was, a);
        int x, y;
        move(a, now, x, y);
        copy(a, was);
        put(a, now, x, y);
        //cout << "AI : " << x + 1 << " " << y + 1 << endl;
    }
    //draw_field(a, s);
	glutTimerFunc(50, Timer, 1);
}

void Initialize() {
	glClearColor(0.0, 0.4, 0.2, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWid/2, WinWid/2, -WinHei/2, WinHei/2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	//system("clear");
    //cout << "<<<<<REVERSI>>>>>" << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            a[i][j] = -1;
        }
    }
    a[3][3] = a[4][4] = 0;
    a[3][4] = a[4][3] = 1;
    /*while (true) {
        cout << "color : ";
        cin >> s;
        if (s == "black") {
            color = 1;
            break;
        } else if (s == "white") {
            color = 0;
            break;
        }
    }*/
	now = 0;
    //draw_field(a, s);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(WinWid, WinHei);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("reversi");
	glutDisplayFunc(Draw);
	glutTimerFunc(50, Timer, 0);//Анимация
	glutMotionFunc(MousePressedMove);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MousePressed);
	Initialize();
	glutMainLoop();
	return 0;
}
