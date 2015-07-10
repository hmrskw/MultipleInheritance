#include "lib/framework.hpp"

class App{
public:
	static AppEnv& get(){
		static AppEnv env(640, 480);
		return env;
	}
private:
	App(){};
};

class Actor{
protected://サブクラスでは見れるけど、他では見れない
	Vec2f pos;
	float speed;
private:
public:	
	Actor(){
		pos = Vec2f(0.0f, 0.0f);
		speed = 0.0f;
	}
	virtual ~Actor(){}//これがないとサブクラスをdeleteしても親がdeleteされない
	virtual void draw() = 0;//純粋仮想関数（オーバーライドしなかったらエラー）
//	virtual void draw(){}//仮想関数
	virtual void move(){}
};

class Player:public Actor{
private:
public:
	virtual ~Player(){};
	void getInput(){
		
	};
};

class P1 :public Player{
private:
public:
	P1(){
		speed = 5.0f;
	}
	void draw(){
		drawFillBox(pos.x(), pos.y(), 100.0f, 100.0f, Color::red, 0, Vec2f(1.0f, 1.0f), Vec2f(50.0f, 50.0f));
	}
	void getInput(){
		if (App::get().isPressKey('A')){
			pos.x() += -speed;
		}
		if (App::get().isPressKey('D')){
			pos.x() += speed;
		}
	}
};

class P2 :public Player{
private:
public:
	P2(){
		speed = 10.0f;
	}
	void draw(){
		drawFillBox(pos.x(), pos.y(), 80.0f, 80.0f, Color::white, 0.0f, Vec2f(1.0f, 1.0f), Vec2f(50.0f, 50.0f));
	}
	void getInput(){
		if (App::get().isPressKey(GLFW_KEY_LEFT)){
			pos.x() += -speed;
		}
		if (App::get().isPressKey(GLFW_KEY_RIGHT)){
			pos.x() += speed;
		}
	}
};


int main() {
	App::get();

	P1 p1;
	P2 p2;

	while (App::get().isOpen()) {
		App::get().begin();
    
		p1.move();
		p1.getInput();
		p1.draw();

		p2.move();
		p2.getInput();
		p2.draw();

		App::get().end();
	}
}