#ifndef HEHEprint_h_
#define HEHEprint_h_
void printheheA();
void printheheB();
#endif//HEHEprint_h_

#ifndef ABCE
#define ABCE abcE
#define ABCE_Extern int ABCE
__declspec(selectany) ABCE_Extern = 1;
#else
extern ABCE_Extern
#endif//ABCE
