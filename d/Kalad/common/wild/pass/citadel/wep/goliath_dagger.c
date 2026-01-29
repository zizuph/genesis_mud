/*
* Made by Korat
* September 1996
* 
* A dagger wielded by Goliath
* 
* modified by Valen, 20011015, fixed a typo
*
*/

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

create_weapon()
{
    ::create_weapon();

    set_name("cinquedea");
    add_name("dagger");
    set_adj("black");
    add_adj("steel");
    set_pname("daggers");
    set_short("black steel cinquedea");
    set_pshort("black steel cinquedeas");

    set_long("The steel of this large dagger shines strongly in the light, "+
      "even though it seems to be made of some black metal. Curving "+
      "slightly, the blade seems perfect for stabbing, but will do also "+
      "well when slashing it against the enemy.\n");

    set_hit(20);  /* added +4 bc. the owner is tough. A reward */
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_wf(TO);
    add_prop(OBJ_I_VALUE,800);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
}
