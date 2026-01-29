/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (random hit/pen)
 */

inherit "/std/weapon";
#include "/d/Raumdor/defs.h"

void
create_weapon()
{
    ::create_weapon();
    set_name("naginata");
    set_adj("long");
    add_adj("rusty");
    set_short("long rusty naginata");
    set_long("This polearm consits of a pole with a nasty looking blade "+
    "set on top. Looking much like a guisarme, you think you could do "+
    "some ok damage with it, considering its corroded condition.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_hit(26+random(3));
    set_pen(27+random(3));
    add_prop(OBJ_I_WEIGHT,6200);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,400+random(200));
}
