#include "stack_template.h"

class position{
	public:
		int x,y;
		position(int a,int b):x(a),y(b){}
		position(const position& a){ x=a.x; y=a.y; }
		bool isSame(const position& b) const{
			if(b.x==x && b.y==y ) return true;
			return false;
		}
		position operator = (const position& a){
			x=a.x; 
			y=a.y;
			return *this;
		}
		void display(){
			cout<<x<<","<<y;
		}
};

typedef stack_template<position> stack_position;
