#pragma once  
class XY  
{  
public:  
     int x = 0,  
         y = 0;  
     XY() {}
     XY(int x, int y) : x(x), y(y) {}
     void add(int ix, int iy)  
     {  
         x += ix;  
         y += iy;  
     }  
};  
class XYZ : public XY  
{  
public:  
      int z = 0;  
     XYZ() {}  
     XYZ(int x, int y, int z) : XY(x, y), z(z) {}  
     XYZ(XY xy) :XY(xy.x, xy.y) {}
     void add(int ix, int iy, int iz)  
     {  
         x += ix;  
         y += iy;  
         z += iz;  
     }  
};  
class WXYZ : public XYZ  
{  
public:  
      int w = 0;  
      WXYZ() {}
      WXYZ(int w, int x, int y, int z) :w(w), XYZ(x, y, z) {}  
      WXYZ(XYZ xyz) :XYZ(xyz.x, xyz.y, xyz.z) {}
      void add(int iw, int ix, int iy, int iz)  
      {  
          w += iw;  
          x += ix;  
          y += iy;  
          z += iz;  
      }  
};
