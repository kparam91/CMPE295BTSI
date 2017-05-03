#ifndef _detect_header
#define _detect_header

#define R_min_B 39
#define R_max_B 84
#define G_min_B 58
#define G_max_B 84
#define B_min_B 52
#define B_max_B 84
#define R_min_R 181
#define R_max_R 201
#define G_min_R 63
#define G_max_R 79
#define B_min_R 76
#define B_max_R 103
#define R_min_W 125
#define R_max_W 255
#define G_min_W 130
#define G_max_W 255
#define B_min_W 130
#define B_max_W 255
#define R_min_Bl 44
#define R_max_Bl 86
#define G_min_Bl 48
#define G_max_Bl 78
#define B_min_Bl 108
#define B_max_Bl 145



int Image_Segment_Function(int, int);
void createTrackbars();
void MouseCallBackCropFunc(int, int, int, int, void*);
void MouseCallBackFunc(int, int, int, int, void*);
void onMouse(int, int, int, int, void*);

int flag = 0,H, S, V, R, G, B, R_MIN = 0, R_MAX = 255, G_MIN = 0, G_MAX = 255, B_MIN = 0, B_MAX = 255, rectcount = 0, ROIcount = 0, pos, R_high =0, R_low =0, G_high =0, G_low =0, B_high =0, B_low =0; 
int R_low1 =0 , R_high1 =0, G_low1 =0, G_high1 =0, B_low1 =0, B_high1 =0;



#endif 
