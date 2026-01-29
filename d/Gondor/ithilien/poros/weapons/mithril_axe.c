/*
 *   /d/Gondor/ithilien/poros/obj/mithril_axe.c
 *
 *   This is the weapon of the corsair captain.
 *
 *   Talisan,  January 1996
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define MY_HIT    50
#define MY_PEN    55

void
create_weapon()
{
    set_name(({"axe", "battleaxe"}));
    add_name("_mithril_axe");
    set_short("mithril-bladed battleaxe");
    set_pshort("battleaxes");
    set_long("The great mithril axe seems to almost have a life of "
      + "its own. To the touch it has an unnatural, nearly pulsating "
      + "warmth. Its ancient blades, crafted from moria silver by "
      + "Dwarven smiths long ago, are "
      + "flawless in their design.\n");

    set_adj(({"great", "battle", "mithril", "dwarven", "grey", "gray",
        "silver", "silvery", "silvery-grey", "silvery-gray", "ancient",
        "mithril-bladed", "mithril"}));

    set_default_weapon(MY_HIT,MY_PEN,W_AXE,W_SLASH|W_BLUDGEON,W_BOTH, TO);

    // mithril!
    set_likely_dull(0);
    set_likely_corr(0);
    set_likely_break(1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

    add_prop(OBJ_S_WIZINFO, BSN(
        "This weapon is wielded by Gaerhir the corsair captain in " 
      + "directory /d/Gondor/ithilien/poros/npcs/captain.c. It is "
      + "a magical axe of great quality forged by Dwarves in Moria "
      + "long ago, and enchanted to produce light when wielded. "
      + "The hit/pen is: " + MY_HIT +"/"+ MY_PEN + "."));


    add_prop(MAGIC_AM_ID_INFO, ({ "The great axe was forged in Moria "
      + "long ago.\n", 5,
      "A weapon far superior to others of its kind, a faint magical "
      + "glimmer radiates from its blade.\n", 15,
      "When wielded, the weapon will begin to glow with a pale, "
      + "mysterious light.\n", 30,
      }));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(MY_HIT, MY_PEN) 
                                           + random(1000) + 1000);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(35, W_AXE) - 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
}

int
wield()
{
    object room;

    if (TP->query_real_name() == "gaerhir")
    {
        say("You step back in terror as the axe is wielded.\n");
        set_hit(70);
        set_pen(75);
        TP->update_weapon(TO);
    }
    else
    {
        
    }
    write("As you grip the ancient battle axe, a pale silvery-grey "
      + "glow begins to envelope the weapon.\n");
    add_prop(OBJ_I_LIGHT, 1);

    room = TO;
    while(objectp(ENV(room)))
        room = ENV(room);

    room->update_light(1);

    LSAY("As ", " wields the ancient battle axe, a pale silvery-grey glow "
      + "begins to envelope the weapon.\n");
    return 1;
}

int 
unwield()
{
    object room;
    
    if (query_hit() > MY_HIT)
        set_hit(MY_HIT);
    if (query_pen() > MY_PEN)
        set_pen(MY_PEN);
    query_wielded()->update_weapon(TO);
    query_wielded()->catch_msg("As you release your grip on the ancient "
      + "battle axe, the pale glow surrounding the weapon fades.\n");
    remove_prop(OBJ_I_LIGHT);

    room = TO;
    while(objectp(ENV(room)))
        room = ENV(room);

    room->update_light(1);

    say("As " + QTNAME(query_wielded()) + " unwields the ancient battle "
      + "axe, the pale glow surrounding the weapon fades.\n",
        ({ TP, query_wielded() }));

    return 1;
}
