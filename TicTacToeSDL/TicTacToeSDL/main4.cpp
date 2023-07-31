//#include <sdl.h>
//#include <sdl_image.h>
//#include <stdio.h>
//#include <string>
//#include <iostream>
//#include <windows.h>
//using namespace std;
//const int screen_width = 640;
//const int screen_height = 480;
//class ltexture{
//public:
//	ltexture();
//	~ltexture();
//	bool loadfromfile(std::string path);
//	void free();
//	void setcolor(uint8 red, uint8 green, uint8 blue);
//	void setblendmode(sdl_blendmode blending);
//	void setalpha(uint8 alpha);
//	void render(int x, int y, sdl_rect* clip = null, double angle = 0.0, sdl_point* center = null, sdl_rendererflip flip = sdl_flip_none);
//	int getwidth();
//	int getheight();
//
//private:
//	sdl_texture* mtexture;
//	int mwidth;
//	int mheight;
//};
//class ltimer{
//public:
//	ltimer();
//	void start();
//	void stop();
//	void pause();
//	void unpause();
//	uint32 getticks();
//	bool isstarted();
//	bool ispaused();
//
//private:
//	uint32 mstartticks;
//	uint32 mpausedticks;
//	bool mpaused;
//	bool mstarted;
//};
//class dot{
//public:
//	static const int dot_width = 20;
//	static const int dot_height = 20;
// int dot_vel = 15;
//	dot();
//	int velocity(int &n);
//	void handleevent(sdl_event& e);
//	void move();
//	void render();
//
//private:
//	int mposx, mposy;
//	int mvelx, mvely;
//};
//bool init();
//bool loadmedia();
//void close();
//sdl_window* gwindow = null;
//sdl_renderer* grenderer = null;
//ltexture gdottexture;
//ltexture::ltexture(){
//	mtexture = null;
//	mwidth = 0;
//	mheight = 0;
//}
//
//ltexture::~ltexture(){
//	free();
//}
//
//bool ltexture::loadfromfile(std::string path){
//	free();
//	sdl_texture* newtexture = null;
//	sdl_surface* loadedsurface = img_load(path.c_str());
//	if (loadedsurface == null){
//		printf("unable to load image %s! sdl_image error: %s\n", path.c_str(), img_geterror());
//	}else{
//		sdl_setcolorkey(loadedsurface, sdl_true, sdl_maprgb(loadedsurface->format, 0, 0xff, 0xff));
//		newtexture = sdl_createtexturefromsurface(grenderer, loadedsurface);
//		if (newtexture == null){
//			printf("unable to create texture from %s! sdl error: %s\n", path.c_str(), sdl_geterror());
//		}else{
//			mwidth = loadedsurface->w;
//			mheight = loadedsurface->h;
//		}
//		sdl_freesurface(loadedsurface);
//	}
//	mtexture = newtexture;
//	return mtexture != null;
//}
//
//void ltexture::free(){
//	if (mtexture != null){
//		sdl_destroytexture(mtexture);
//		mtexture = null;
//		mwidth = 0;
//		mheight = 0;
//	}
//}
//
//void ltexture::setcolor(uint8 red, uint8 green, uint8 blue){
//	sdl_settexturecolormod(mtexture, red, green, blue);
//}
//
//void ltexture::setblendmode(sdl_blendmode blending){
//	sdl_settextureblendmode(mtexture, blending);
//}
//
//void ltexture::setalpha(uint8 alpha){
//	sdl_settexturealphamod(mtexture, alpha);
//}
//
//void ltexture::render(int x, int y, sdl_rect* clip, double angle, sdl_point* center, sdl_rendererflip flip){
//	sdl_rect renderquad = { x, y, mwidth, mheight };
//	sdl_rendercopyex(grenderer, mtexture, clip, &renderquad, angle, center, flip);
//}
//
//int ltexture::getwidth(){
//	return mwidth;
//}
//
//int ltexture::getheight() {
//	return mheight;
//};
//
//
//dot::dot() {
//	mposx = 10;
//	mposy = 0;
//	mvelx = 0;
//	mvely = 0;
//};
//int countrt = 0;
//void dot::handleevent(sdl_event& e)
//{
//	if (e.type == sdl_keydown && e.key.repeat == 0)
//	{
//		cout << "key down";
//		switch (e.key.keysym.sym)
//		{
//		case sdlk_up:
//
//			mvely -= dot_vel;
//			break;
//		case sdlk_down: mvely += dot_vel; break;
//		case sdlk_left: mvelx -= dot_vel; break;
//		case sdlk_right: mvelx += dot_vel; break;
//		default: dot_vel = 0;
//		}
//	}else if (e.type == sdl_keyup && e.key.repeat == 0){
//		cout << "key up";
//		switch (e.key.keysym.sym){
//		case sdlk_up: mvely += dot_vel; break;
//		case sdlk_down: mvely -= dot_vel; break;
//		case sdlk_left: mvelx += dot_vel; break;
//		case sdlk_right: mvelx -= dot_vel; break;
//		}
//	}
//}
//void gotoxy(int x, int y)
//{
//	static handle h = null;
//	if (!h)
//		h = getstdhandle(std_output_handle);
//	coord c = { x, y };
//	setconsolecursorposition(h, c);
//}
//int _mvelx = 0;
//void dot::move(){
//	if (mvelx > 0) {
//		sdl_delay(27);
//		countrt+=2;
//		if (countrt > 8) {
//			countrt = 8;
//		}
//		gotoxy(0, 0);
//		cout << "pixel/s: " << countrt << endl;
//		_mvelx = countrt;
//	}
//	else { countrt = 3; _mvelx = 0; gotoxy(0, 0);
//	cout << "pixel/s: " << _mvelx << endl;
//	}
//	mposx += _mvelx;
//	if (mposx + dot_width > screen_width){
//		mposx = 0;
//	}
//	else if (mposx < 0) {
//		mposx = screen_width-dot_width;
//		}
//	mposy += mvely;
//	if (mposy + dot_height > screen_height){
//		mposy = 0;
//	}
//	else if (mposy < 0) {
//		mposy = screen_height-dot_height;
//	}
//}
//
//void dot::render(){
//	gdottexture.render(mposx, mposy);
//}
//
//bool init(){
//	bool success = true;
//	if (sdl_init(sdl_init_video) < 0){
//		printf("sdl could not initialize! sdl error: %s\n", sdl_geterror());
//		success = false;
//	}else{
//		if (!sdl_sethint(sdl_hint_render_scale_quality, "1")){
//			printf("warning: linear texture filtering not enabled!");
//		}
//		gwindow = sdl_createwindow("sdl tutorial", sdl_windowpos_undefined, sdl_windowpos_undefined, screen_width, screen_height, sdl_window_shown);
//		if (gwindow == null)	{
//			printf("window could not be created! sdl error: %s\n", sdl_geterror());
//			success = false;
//		}else{
//			grenderer = sdl_createrenderer(gwindow, -1, sdl_renderer_accelerated | sdl_renderer_presentvsync);
//			if (grenderer == null){
//				printf("renderer could not be created! sdl error: %s\n", sdl_geterror());
//				success = false;
//			}else{
//				sdl_setrenderdrawcolor(grenderer, 0xff, 0xff, 0xff, 0xff);
//				int imgflags = img_init_png;
//				if (!(img_init(imgflags) & imgflags))
//				{
//					printf("sdl_image could not initialize! sdl_image error: %s\n", img_geterror());
//					success = false;
//				}
//			}
//		}
//	}
//
//	return success;
//}
//
//bool loadmedia()
//{
//	loading success flag
//	bool success = true;
//
//	load dot texture
//	if (!gdottexture.loadfromfile("d:/project/project_img/dot.bmp"))
//	{
//		printf("failed to load dot texture!\n");
//		success = false;
//	}
//
//	return success;
//}
//
//void close()
//{
//	free loaded images
//	gdottexture.free();
//
//	destroy window	
//	sdl_destroyrenderer(grenderer);
//	sdl_destroywindow(gwindow);
//	gwindow = null;
//	grenderer = null;
//	img_quit();
//	sdl_quit();
//}
//
//int main(int argc, char* args[]){
//	if (!init()){
//		printf("failed to initialize!\n");
//	}else{
//		if (!loadmedia())
//		{
//			printf("failed to load media!\n");
//		}else{
//			bool quit = false;
//			sdl_event e;
//			dot dot;
//			while (!quit){
//				while (sdl_pollevent(&e) != 0)	{
//					if (e.type == sdl_quit){
//						quit = true;
//					}
//					dot.handleevent(e);
//				}
//				dot.move();
//				sdl_renderclear(grenderer);
//				dot.render();
//				sdl_renderpresent(grenderer);
//			}
//		}
//	}
//	close();
//
//	return 0;
//}
