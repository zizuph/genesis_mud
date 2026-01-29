/* 
 * /d/Kalad/common/wild/pass/goblin/guild/f_sword.c
 * Purpose    : Sword of the fang
 * Located    : Brutakis
 * Created By : Sarr ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_adj("jagged");
    add_adj("black");
    set_short("jagged black sword");
    set_long("This is a wicked looking dagger made of black steel. It "+
    "has a nasty looking jagged edge and looks razor sharp.\n");
    set_dt(W_IMPALE | W_SLASH);
   set_hit(25);
   set_pen(29);
}

