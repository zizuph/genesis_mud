/* A giant axe - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/npc/giantgob.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>

void
create_weapon()
{
    set_name("axe");
    set_pname("axes");
    add_pname("weapons");
    set_adj("giant");
    add_adj("right");
    set_short("giant axe");
    set_pshort("giant axes");
    set_long(
        "This axe in large and very heavy. It has been made in such a way " +
        "that you can only hold it in your right hand. The blade is steel, " +
        "and the handle in made of hardwood.\n");

    set_hit(26);
    set_pen(36);
    set_wt(W_AXE);
    set_dt(W_SLASH|W_BLUDGEON);
    set_hands(TS_RWEAPON);

    add_prop(OBJ_I_WEIGHT, 25000);
    add_prop(OBJ_I_VOLUME, 8000);
    /* This is one big, heavy axe!!! */
}

public int
wield(object wep)
{
    if (this_player()->query_stat(SS_STR) < 80)
    {
        write("The battleaxe is far too heavy for you to wield.\n");
        return -1;
    }

    return 0;
}
