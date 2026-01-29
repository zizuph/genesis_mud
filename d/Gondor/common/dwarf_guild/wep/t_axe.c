/*
 * /d/Gondor/common/dwarf_guild/wep/t_axe.c
 *
 * It is the axe that is wielded by the trainer in the guild.
 *
 * /Mercade 7 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define WEAPON_HIT 27
#define WEAPON_PEN 34

void
create_weapon()
{
    set_name("axe");
    set_pname("axes");

    set_adj("alloy");
    add_adj("magnificent");
    add_adj("black");
    add_adj("dwarven");
    add_adj("sharp");
    add_adj("strong");

    set_short("magnificent black axe");
    set_pshort("black axes");

    set_long(BSN("This magnificent black axe is a real masterpiece, " +
        "especially crafted for a real master in the art of combat with " +
        "axes. Its haft is made of solid oak and the blade is made from " +
        "special alloy that makes it very strong and sharp."));

    add_item( ({ "haft", "hilt", "handle", "grip", "helve" }),
        BSN("The haft of this magnificent black axe is made of solid oak, " +
        "a very strong type of wood."));
    add_item( ({ "blade", "black blade" }),
        BSN("The black blade of this magnificent black axe is made of a " +
        "special type of alloy that makes it very strong and sharp. It is " +
        "the alloy that gives the blade its black colour, even though it " +
        "it is shiny."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        random(200) - 100);
}

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
