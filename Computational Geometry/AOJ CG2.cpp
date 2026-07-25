// #include <bits/stdc++.h>
// using namespace std;

// #define db double

// const db eps = 1e-9;
// const db pi = acos(-1);

// int sgn(db x){
//     if(fabs(x)<eps) return 0;
//     return x>0?1:-1;
// }

// struct Pt{
//     db x,y;

//     Pt(){}

//     Pt(db x,db y):x(x),y(y){}

//     //加法
//     Pt operator + (const Pt &o) const{
//         return Pt(x+o.x,y+o.y);
//     }

//     // 减法
//     Pt operator - (const Pt &o) const{
//         return Pt(x-o.x,y-o.y);
//     }

//     // 数乘
//     Pt operator * (db k) const{
//         return Pt(x*k,y*k);
//     }

//     // 除法
//     Pt operator / (db k) const{
//         return Pt(x/k,y/k);
//     }

//     // 长度
//     db len() const{
//         return sqrt(x*x+y*y);
//     }

//     // 长度平方
//     db len2() const{
//         return x*x+y*y;
//     }

//     // 极角
//     db angle() const{
//         return atan2(y,x);
//     }

//     // 旋转
//     Pt rot(db a) const{
//         return {
//             x*cos(a)-y*sin(a),
//             x*sin(a)+y*cos(a)
//         };
//     }
// };


// // 点积
// db dot(Pt a,Pt b){
//     return a.x*b.x+a.y*b.y;
// }


// // 叉积
// db cross(Pt a,Pt b){
//     return a.x*b.y-a.y*b.x;
// }


// // 三点方向
// // >0 左侧
// // <0 右侧
// // =0 共线
// db cross(Pt a,Pt b,Pt c){
//     return cross(b-a,c-a);
// }


// // 两点距离
// db dis(Pt a,Pt b){
//     return (a-b).len();
// }


// // 是否垂直
// bool isPerp(Pt a,Pt b){
//     return sgn(dot(a,b))==0;
// }


// // 是否平行
// bool isParallel(Pt a,Pt b){
//     return sgn(cross(a,b))==0;
// }


// // 两向量夹角
// db angle(Pt a,Pt b){
//     return acos(dot(a,b)/a.len()/b.len());
// }


// // 点在线段上
// bool onSegment(Pt p,Pt a,Pt b){
//     return sgn(cross(a,b,p))==0 &&
//            sgn(dot(p-a,p-b))<=0;
// }


// // 直线交点 点向式
// // a+tu
// // b+sv
// Pt getIntersection(Pt a,Pt u,Pt b,Pt v){

//     db t=cross(b-a,v)/cross(u,v);

//     return a+u*t;
// }


// // 投影点
// Pt projection(Pt p,Pt a,Pt b){

//     Pt v=b-a;

//     return a+v*(dot(p-a,v)/v.len2());
// }


// // 对称点
// Pt reflect(Pt p,Pt a,Pt b){

//     Pt q=projection(p,a,b);

//     return q*2-p;
// }

// signed main(){
//     int q; cin >> q;
//     while(q--){
//     Pt a,b,c,d;
//     cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
//     Pt u=b-a;
//     Pt v=d-c;
//     if(cross(u,v)==0) cout<<"2"<<endl;
//     else if(dot(u,v)==0) cout<<"1"<<endl;
//     else cout<<"0"<<endl;
// }
// return 0;
// }

#include <bits/stdc++.h>
using namespace std;

#define db double

const db eps = 1e-9;
const db pi = acos(-1);

int sgn(db x){
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}

struct Pt{
    db x,y;

    Pt(){}

    Pt(db x,db y):x(x),y(y){}

    //加法
    Pt operator + (const Pt &o) const{
        return Pt(x+o.x,y+o.y);
    }

    // 减法
    Pt operator - (const Pt &o) const{
        return Pt(x-o.x,y-o.y);
    }

    // 数乘
    Pt operator * (db k) const{
        return Pt(x*k,y*k);
    }

    // 除法
    Pt operator / (db k) const{
        return Pt(x/k,y/k);
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
    Pt rot(db a) const{
        return {
            x*cos(a)-y*sin(a),
            x*sin(a)+y*cos(a)
        };
    }
};


// 点积
db dot(Pt a,Pt b){
    return a.x*b.x+a.y*b.y;
}


// 叉积
db cross(Pt a,Pt b){
    return a.x*b.y-a.y*b.x;
}


// 三点方向
// >0 左侧
// <0 右侧
// =0 共线
db cross(Pt a,Pt b,Pt c){
    return cross(b-a,c-a);
}


// 两点距离
db dis(Pt a,Pt b){
    return (a-b).len();
}


// 是否垂直
bool isPerp(Pt a,Pt b){
    return sgn(dot(a,b))==0;
}


// 是否平行
bool isParallel(Pt a,Pt b){
    return sgn(cross(a,b))==0;
}


// 两向量夹角
db angle(Pt a,Pt b){
    return acos(dot(a,b)/a.len()/b.len());
}


// 点在线段上
bool onSegment(Pt p,Pt a,Pt b){
    return sgn(cross(a,b,p))==0 &&
           sgn(dot(p-a,p-b))<=0;
}


// 直线交点 点向式
// a+tu
// b+sv
Pt getIntersection(Pt a,Pt u,Pt b,Pt v){

    db t=cross(b-a,v)/cross(u,v);

    return a+u*t;
}


// 投影点
Pt projection(Pt p,Pt a,Pt b){

    Pt v=b-a;

    return a+v*(dot(p-a,v)/v.len2());
}


// 对称点
Pt reflect(Pt p,Pt a,Pt b){

    Pt q=projection(p,a,b);

    return q*2-p;
}
//判断两线段是否有交点
bool Segmentintersect(Pt a,Pt b,Pt c,Pt d){
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

signed main(){
    int q; cin >> q;
    while(q--){
    Pt a,b,c,d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    Pt i=getIntersection(a,a-b,c,c-d);
    cout<<fixed<<setprecision(10)<<i.x<<" "<<fixed<<setprecision(10)<<i.y<<endl;
}
return 0;
}

