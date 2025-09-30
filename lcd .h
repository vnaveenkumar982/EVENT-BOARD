#include"types.h"
void Writelcd(u8 byte);
void Cmdlcd(u8 cmd);
void Initlcd(void);
void Charlcd(u8 asciival);
void Strlcd(s8 *);
void U32lcd(u32);
void S32lcd(s32);
void F32lcd(f32,u32);
