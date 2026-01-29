/* A large hunting knife - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/mon/.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
                               
public void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    add_pname("weapons");
    set_short("large hunting knife");
    set_pshort("large hunting knives");
    set_adj("large");
    set_adj("hunting");
    set_long(
        "You have seen a lot of knives in you time, but this one " +
        "must rate as one of the biggest. It has a sharp steel blade, " +
        "and has a wooden handle.\n");

    set_hit(10);
    set_pen(16); /* steel blade, after all. */

    set_wt(W_KNIFE);
    set_dt(W_SLASH);

    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 3000); /* 3kg sounds heavy to me! */
    add_prop(OBJ_I_VOLUME, 500);
}
