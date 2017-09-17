#include "sprite.h"

Sprite::Sprite() {
	_alive = 1;
	_direction = 1;
	_animDir = 1;
	_animColumns = 0;
	_width = 0;
	_height = 0;
	_xDelay = 0;
	_yDelay = 0;
	_xCount = 0;
	_yCount = 0;
	_curFrame = 0;
	_totalFrames = 1;
	_frameCount = 0;
	_frameDelay = 1;
	_animStartX = 0;
	_animStartY = 0;
	_framesStart = 0;
	_framesEnd = 0;
	
	_x = 0.0f;
	_y = 0.0f;
	_velX = 0.0;
	_velY = 0.0;

	_image = NULL;
}

Sprite::~Sprite() {
	if (_image != NULL) {
		destroy_bitmap(_image);
	}
}

int Sprite::Load(const char *filename) {
	_image = load_bitmap(filename, NULL);
	if (_image == NULL) {
		return 0;
	}
	_width = _image->w;
	_height = _image->h;
	return 1;
}

void Sprite::Draw(BITMAP *dest) {
	draw_sprite(dest, _image, (int) _x, (int) _y);
}

void Sprite::DrawFrame(BITMAP *dest) {
	int frameX = _animStartX + (_curFrame % _animColumns) * _width;
	int frameY = _animStartY + (_curFrame / _animColumns) * _height;
	masked_blit(_image, dest, frameX, frameY, (int) _x, (int) _y, _width, _height); 
}


void Sprite::UpdatePosition() {
	
	if (++_xCount > _xDelay) {
		_xCount = 0;
		_x += _direction * _velX;
	}
	
	if (++_yCount > _yDelay) {
		_yCount = 0;
		_y += _direction * _velY;
	}
}

void Sprite::UpdateAnimation() {
	if (++_frameCount > _frameDelay) {
		_frameCount = 0;
		_curFrame += _animDir;
		
		if (_curFrame < 0) {
			_curFrame = _totalFrames - 1;
		}
		
		if (_curFrame > _totalFrames - 1) {
			_curFrame = 0;
		}
	}
}

int Sprite::Inside(int x, int y, int left, int top, int right, int bottom) {
	return (x > left && x < right && y < bottom && y > top) ? 1 : 0;
}

int Sprite::PointInside(int px, int py) {
	return Inside(px, py, (int) _x, (int) _y, (int) _x + _width, (int) _y + _height);
}

int Sprite::Collided(Sprite *other, int shrink) {
	int widthA = (int) _x + _width;
	int heightA = (int) _y + _height;
	int widthB = (int) other->getX() + (int) other->getWidth();
	int heightB = (int) other->getY() + (int) other->getHeight();
	
	if (Inside((int) _x, (int) _y, (int) other->getX() + shrink, (int) other->getY() + shrink, widthB - shrink, heightB - shrink) ||
		Inside((int) _x, heightA, (int) other->getX() + shrink, (int) other->getY() + shrink, widthB - shrink, heightB - shrink) ||
        Inside(widthA, (int) _y, (int) other->getX() + shrink, (int) other->getY() + shrink, widthB - shrink, heightB - shrink) ||
        Inside(widthA, heightA, (int) other->getX() + shrink, (int) other->getY() + shrink, widthB - shrink, heightB - shrink)) {
        	return 1;
	}
	else {
		return 0;
	}
}

int Sprite::CollideWithBlock(int x, int y)
{
    BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

double Sprite::CenterX() {
	return _x + (_width / 2);
}

double Sprite::CenterY() {
	return _y + (_height / 2);
}

void Sprite::PlayerControls() {
	if (key[KEY_LEFT]) {
		_direction = 1;
		_framesStart = 4;
		_framesEnd = 7;
		if (++_xCount > _xDelay) {
			_xCount = 0;
			_x += _direction * _velX;
		}
	}
	if (key[KEY_RIGHT]) {
		_direction = -1;
		_framesStart = 0;
		_framesEnd = 3;
		if (++_xCount > _xDelay) {
			_xCount = 0;
			if (!CollideWithBlock(_x + _direction * _velX, _y)) {
				_x += _direction * _velX;				
			}
		}
	}
	if (key[KEY_SPACE]) {
		_framesStart = 8;
		_framesEnd = 10;
		if (++_yCount < _yDelay) {
			_x += _direction * _velX;				
		}
	}
}

int Sprite::getAlive() {
	return _alive;
}
void Sprite::setAlive(int alive){
	_alive = alive;
}
int Sprite::getDirection(){
	return _direction;
}
void Sprite::setDirection(int direction){
	_direction = direction;
}
int Sprite::getAnimDir(){
	return _animDir;
}
void Sprite::setAnimDir(int animDir){
	_animDir = animDir;
}
int Sprite::getAnimColumns(){
	return _animColumns;
}
void Sprite::setAnimColumns(int animColumns){
	_animColumns = animColumns;
}
int Sprite::getWidth(){
	return _width;
}
void Sprite::setWidth(int width){
	_width = width;
}
int Sprite::getHeight(){
	return _height;
}
void Sprite::setHeight(int height){
	_height = height;
}
int Sprite::getXDelay(){
	return _xDelay;
}
void Sprite::setXDelay(int xDelay){
	_xDelay = xDelay;
}
int Sprite::getYDelay(){
	return _yDelay;
}
void Sprite::setYDelay(int yDelay){
	_yDelay = yDelay;
}
int Sprite::getXCount(){
	return _xCount;
}
void Sprite::setXCount(int xCount){
	_xCount = xCount;
}
int Sprite::getYCount(){
	return _yCount;
}
void Sprite::setYCount(int yCount){
	_yCount = yCount;
}
int Sprite::getCurFrame(){
	return _curFrame;
}
void Sprite::setCurFrame(int curFrame){
	_curFrame = curFrame;
}
int Sprite::getTotalFrames(){
	return _totalFrames;
}
void Sprite::setTotalFrames(int totalFrames){
	_totalFrames = totalFrames;
}
int Sprite::getFrameCount(){
	return _frameCount;
}
void Sprite::setFrameCount(int frameCount){
	_frameCount = frameCount;
}
int Sprite::getFrameDelay(){
	return _frameDelay;
}
void Sprite::setFrameDelay(int frameDelay){
	_frameDelay = frameDelay;
}
int Sprite::getAnimStartX(){
	return _animStartX;
}
void Sprite::setAnimStartX(int animStartX){
	_animStartX = animStartX;
}
int Sprite::getAnimStartY(){
	return _animStartY;
}
void Sprite::setAnimStartY(int animStartY){
	_animStartY = animStartY;
}
int Sprite::getFramesStart() {
	return _framesStart;
}
void Sprite::setFramesStart(int framesStart) {
	_framesStart = framesStart;
}
int Sprite::getFramesEnd() {
	return _framesEnd;
}
void Sprite::setFramesEnd(int framesEnd) {
	_framesEnd = framesEnd;
}
double Sprite::getX(){
	return _x;
}
void Sprite::setX(double x){
	_x = x;
}
double Sprite::getY(){
	return _y;
}
void Sprite::setY(double y){
	_y = y;
}
double Sprite::getVelX(){
	return _velX;
}
void Sprite::setVelX(double velX){
	_velX = velX;
}
double Sprite::getVelY(){
	return _velY;
}
void Sprite::setVelY(double velY){
	_velY = velY;
}
BITMAP *Sprite::getImage(){
	return _image;
}
void Sprite::setImage(BITMAP *image){
	_image = image;
}
