#include <bits/stdc++.h>
using namespace std;

#define db double

const db eps = 1e-9;
const db pi = acos(-1);

int sgn(db x){
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}

struct pt{
    db x,y;

    pt(){}

    pt(db x,db y):x(x),y(y){}

    //加法
    pt operator + (const pt &o) const{
        return pt(x+o.x,y+o.y);
    }

    // 减法
    pt operator - (const pt &o) const{
        return pt(x-o.x,y-o.y);
    }

    // 数乘
    pt operator * (db k) const{
        return pt(x*k,y*k);
    }

    // 除法
    pt operator / (db k) const{
        return pt(x/k,y/k);
    }
    
    // 判断相等
    bool operator == (const pt &o)const{
    return sgn(x-o.x)==0&&sgn(y-o.y)==0;
}

    // 长度
    db len() const{
        return sqrt(x*x+y*y);
    }

    // 长度平方
    db len2() const{
        return x*x+y*y;
    }

    // 极角
    db angle() const{
        return atan2(y,x);
    }

    // 旋转
    pt rot(db a) const{
        return {
            x*cos(a)-y*sin(a),
            x*sin(a)+y*cos(a)
        };
    }
    pt perp() const{
        return {-y,x};
    }
};


// 点积
db dot(pt a,pt b){
    return a.x*b.x+a.y*b.y;
}


// 叉积
db cross(pt a,pt b){
    return a.x*b.y-a.y*b.x;
}


// 三点方向
// >0 左侧
// <0 右侧
// =0 共线
db cross(pt a,pt b,pt c){
    return cross(b-a,c-a);
}


// 两点距离
db dis(pt a,pt b){
    return (a-b).len();
}


// 向量是否垂直
bool isPerp(pt a,pt b){
    return sgn(dot(a,b))==0;
}


// 是否平行
bool isParallel(pt a,pt b){
    return sgn(cross(a,b))==0;
}


// 两向量夹角
db angle(pt a,pt b){
    db c=dot(a,b)/a.len()/b.len();
    c=max(-1.0,min(1.0,c));
    return acos(c);
}


// 点在线段上
bool onSegment(pt p,pt a,pt b){
    return sgn(cross(a,b,p))==0 &&
           sgn(dot(p-a,p-b))<=0;
}

//判断两线段是否有交点
bool segmentIntersect(pt a,pt b,pt c,pt d){
    int c1=sgn(cross(a,b,c));
    int c2=sgn(cross(a,b,d));
    int c3=sgn(cross(c,d,a));
    int c4=sgn(cross(c,d,b));
    if(c1*c2<0 && c3*c4<0) return true;
    if(c1==0 && onSegment(c,a,b)) return true;
    if(c2==0 && onSegment(d,a,b)) return true;
    if(c3==0 && onSegment(a,c,d)) return true;
    if(c4==0 && onSegment(b,c,d)) return true;
    return false;
}



struct line{
    pt v; db c;  //c表示偏移量
    //方向向量v 偏移量c
    line(pt v, db c) : v(v),c(c) {}
    //方程ax+by=c
    line(db a, db b, db c) : v({b,-a}),c(c) {}
    //两点式
    line(pt p,pt q): v(q-p),c(cross(v,p)) {}
};

db side(line ln,pt p){
    return cross(ln.v,p)-ln.c;
}

db dis(line ln,pt p){
    return abs(side(ln,p))/ln.v.len();
}

//直线交点
bool inter(line l1,line l2,pt &out){
    db d=cross(l1.v,l2.v);
    if(sgn(d)==0) return false;
    out=(l2.v*l1.c-l1.v*l2.c)/d;
    return true;
}

pt proj(line ln,pt p) {return p-ln.v.perp()*side(ln,p)/ln.v.len2();}
pt refl(line ln,pt p) {return p-ln.v.perp()*2*side(ln,p)/ln.v.len2();}

line perpThrough(line ln,pt p){
    return {p,p+ln.v.perp()};
}
db disSeg(pt p,pt a,pt b){  //点到线段的距离
    line ln =line (a,b);
    pt t=proj(ln,p);
    if(onSegment(t,a,b)) return dis(ln,p);
    else return min(dis(p,a),dis(p,b));
}
db segdisSeg(pt a,pt b,pt c,pt d){
    if(segmentIntersect(a,b,c,d)) return 0;
    else{
        return min({disSeg(c,a,b),disSeg(d,a,b),disSeg(a,c,d),disSeg(b,c,d)});
    }
}
signed main(){
    int q; cin >> q;
    while(q--){
    pt a,b,c,d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    cout<<fixed<<setprecision(10)<<segdisSeg(a,b,c,d)<<endl;
}
return 0;
}

