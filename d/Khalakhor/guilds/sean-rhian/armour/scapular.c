/*
** Scapular - distinctive vestment of a manach
** Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/5/97   Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
 
int    folded=0;
string color="purple";  /* default color purple */
 
void set_color(string col) {
    color=col;
    set_adj(color);
    set_short(color+" scapular");
    set_long("It is a long sleeveless and sideless religious garment, "+
             "composed of two rectangular pieces of "+color+" material, "+
             "neck to ankle length and a bit narrower than the shoulders. "+
             "One piece hangs down the front of the wearer and the other "+
             "down the back, linked together over each shoulder. It is "+
             "embroidered with three interlocking gold circles.\n");
}
 
void create_armour() {
    set_name("scapular");
    set_color(color);
    set_ac(5);
    set_at(TS_NECK);
}
