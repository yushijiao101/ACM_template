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
//     Pt a,b;
//     cin >> a.x >> a.y >> b.x >> b.y; 
//     int q; cin >> q;
//     while(q--){
//     Pt t;
//     cin >> t.x >> t.y;
//     Pt ans=projection(t,a,b);
//     cout<<fixed<<setprecision(10)<<ans.x<<" "<<fixed<<setprecision(10)<<ans.y<<endl;//注意精度
//     }
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

signed main(){
    Pt a,b;
    cin >> a.x >> a.y >> b.x >> b.y; 
    int q; cin >> q;
    while(q--){
    Pt t;
    cin >> t.x >> t.y;
    int ans=cross(t,a,b);
    if(ans>0){
cout<<"COUNTER_CLOCKWISE"<<endl;
}
    else if(ans<0) cout<<"CLOCKWISE"<<endl;
    else{
    Pt u=t-a;  //vec at
    Pt v=t-b;  //vec bt
    Pt ab=a-b;  //vec ab
    if(dot(u,v)<=0) cout<<"ON_SEGMENT"<<endl;
    else{
        if(dot(ab,u)>0) cout<<"ONLINE_BACK"<<endl; 
        else cout<<"ONLINE_FRONT"<<endl;
    }
    }
}
return 0;
}

