/* 
 * /d/Kalad/common/wild/pass/goblin/guild/f_dagger.c
 * Purpose    : A dagger used by the goblin fang guards
 * Located    : f_guard.c
 * Created By : Sarr ??.??.??
 * Modified By: Toby,970918 (fixed plural desc. plus a random hit/pen.)
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_pname("daggers");
    set_adj("jagged");
    add_adj("black");
    set_short("jagged black dagger");
    set_pshort("jagged black daggers");
    set_long("This is a wicked looking dagger made of black steel. It "+
    "has a nasty looking jagged edge and looks razor sharp.\n");
    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_KNIFE);
    set_hit(17+random(3));
    set_pen(14+random(3));
}

