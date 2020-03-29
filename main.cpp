#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct punto {
	int x;
	int y;
};

int N;
int capa;
punto p;
vector<punto> puntos;
vector<punto> capsula;

float productoCruz(punto p0, punto p1, punto p2) {
	return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

float alfa(punto p0, punto p1) {
	float t;
	int dx;
	int dy;
	int ax;
	int ay;
	dx = p1.x - p0.x;
	ax = abs((float) dx);
	dy = p1.y - p0.y;
	ay = abs((float) dy);
	if(ax == 0 && ay == 0)
		t = 0.0;
	else
		t = ((float) dy / (ax + ay));
	if(dx < 0)
		t = 2 - t;
	else if(dy < 0)
		t = 2 + t;
	return (t * 90.0);
}

bool menorAlfa(punto p0, punto p1) {
	if(alfa(puntos[0], p0) < alfa(puntos[0], p1))
		return true;
	if(alfa(puntos[0], p0) == alfa(puntos[0], p1) &&
		(((puntos[0].x - p0.x) * (puntos[0].x - p0.x) + (puntos[0].y - p0.y) * (puntos[0].y - p0.y))
		<
		((puntos[0].x - p1.x) * (puntos[0].x - p1.x) + (puntos[0].y - p1.y) * (puntos[0].y - p1.y)))
	)
		return true;
	return false;
}

bool menorY(punto p0, punto p1) {
	if(p0.y < p1.y)
		return true;
	if(p0.y == p1.y && p0.x < p1.x)
		return true;
	return false;
}

bool esRecta() {
	for(int a = 2; a < puntos.size(); ++a)
		if(productoCruz(puntos[a - 2], puntos[a - 1], puntos[a]) != 0)
			return false;
	return true;
}

void grahamScan() {
	sort(puntos.begin(), puntos.end(), menorY);
	sort(puntos.begin() + 1, puntos.end(), menorAlfa);
	capsula.push_back(puntos[0]);
	capsula.push_back(puntos[1]);
	for(int a = 2; a < puntos.size(); ++a) {
		if(productoCruz(capsula[capsula.size() - 2], capsula[capsula.size() - 1], puntos[a]) >= 0) {
			capsula.push_back(puntos[a]);
		} else {
			capsula.pop_back();
			a--;
		}
	}
}

int main() {
	while(true) {
		cin >> N;
		if(N == 0)
			break;
		for(int a = 0; a < N; ++a) {
			cin >> p.x;
			cin >> p.y;
			puntos.push_back(p);
		}
		capa = 0;
		while(puntos.size() > 2) {
			if(!esRecta()) {
				grahamScan();
				int a = 0;
				for(int b = 0; b < puntos.size(); ++b) {
					if(capsula[a].x == puntos[b].x && capsula[a].y == puntos[b].y) {
						puntos.erase(puntos.begin() + b);
						a++;
						b--;
					}
				}
				capa++;
			} else {
				puntos.clear();
			}
			capsula.clear();
		}
		if(capa % 2 == 0)
			cout << "Do not take this onion to the lab!" << endl;
		else
			cout << "Take this onion to the lab!" << endl;
		puntos.clear();
	}
	return 0;
}

