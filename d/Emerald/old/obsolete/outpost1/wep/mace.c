/*mace.c
*By Mhyrkhaan, November 1998.
*/
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
void
create_weapon()
{
    set_name("mace");
    add_name("steel");
    set_short("flanged steel mace");
    add_adj( ({"flanged" , "steel"}) );
    set_long("flanged, heavy, and steel. This mace looks like it could cause " +
        "one serious headache. The flanges on it's head are quite sharp.\n");
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 1500); 
    add_prop(OBJ_I_VOLUME,  550);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}
