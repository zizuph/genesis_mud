/*
 * /d/Gondor/mordor/obj/wep/dagger.c
 *
 * It is an ornamented dagger. You can find it is the Tower at Cirith Ungol.
 * You'd better sell it for it won't do you much good in combat.
 *
 * /Mercade, 28 November 1993
 *
 * Revision history:
 */

inherit "/std/weapon";

#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("dagger");
    add_name("_ornamented_dagger_at_cirith_ungol_");
    add_adj("decorated");
    add_adj("richly");
    add_adj("silver");
    add_adh("mithril");

    set_short("ornamtented dagger");
    set_long("It is a richly decorated and ornamented dagger, made of " +
        "pure silver. It must be a valuable weapon, worn by someone of " +
        "high office.");
    add_item( ({ "decoration", "decorations", "ornamtent", "ornaments" }),
        BSN("The decorations were crafted by a real master. The heft is " +
        "decorated with a picture of a noble dwarf in mithril. This dwarf " +
        "probably owned it a long time ago. The picture is surrounded by " +
        "jewels."));
    add_item( ({ "picture" }),
        BSN("It is a picture of a fair and noble dwarf. There is no " +
        "inscription of any name. Dwarves are very secretive about their " +
        "true name."));
    add_item( ({ "jewel", "jewels", "sapphire", "sapphires" }),
        BSN("Examining the jewels closely you see that they are some " +
        "sapphires, coloured deep red and."));

    set_hit(5 + random(5));
    set_pen(5 + random(5));

    set_wt(W_KNIFE);
    set_dt( (W_IMPALE | W_SLASH) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE,  400 + random(400));
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
