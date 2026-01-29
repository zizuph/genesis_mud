/* A stiletto - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/.c */
/* This is the very first item that the original Tulix coded. */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("stiletto");
    set_pname("stilettoes");
    add_pname("weapons");
    set_short("sharp stiletto");
    set_pshort("sharp stilettoes");
    set_adj("sharp"); 
    set_long("It's a long, thin, dagger-like weapon.  It's very sharp.\n");
    
    set_hit(10);
    set_pen(15);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 120);

}
