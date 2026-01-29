/*
 *  /d/Sparkle/guilds/new_merc/event/colossus_fullplate.c
 *
 *  Elite armour for the orc raid event to open the Merc Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour() 
{
    set_name("suit");
    add_name( ({ "mail", "deathmail" }) );
    set_adj( ({ "complete", "death", "of", "suit" }) );

    set_short("complete suit of deathmail");
    set_long("Can this be armour? If, so, it is beyond protection. Huge"
      + " spikes protrude from every inch of the thick black metal,"
      + " forcing anyone who wanted to close on the wearer to brave"
      + " the deadly points. The metal positively hums with malevolent"
      + " energy as if the anger of a Dark God is upon it somehow.\n");

    set_ac(60);
    set_am( ({-2,-1,3}) );
    set_at(A_TORSO|A_L_ARM|A_R_ARM|A_LEGS);

    add_prop(OBJ_I_WEIGHT, 30000); /* this sucker is heavy */
    add_prop(OBJ_I_VOLUME, 3000);  /* not to mention massive */
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(60)
                        + random(1000) + 500);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "abjuration" }) );
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_ID_INFO, ({
        "Crafted by gifted smiths and then later enchanted by the"
      + " prayers of goblin shaman, this dreadful armour has been"
      + " bestowed with the powers of the Dark God Kalach. It"
      + " protects beyond nearly anything else of this world.\n", 30, }) );

    add_prop(OBJ_S_WIZINFO,
        "Special note: This armour is only available from a special event"
      + " in which Sparkle is beseiged by attacking goblins. It is a very"
      + " powerful armour, and therefore not to be given out"
      + " under normal circumstances. But for such a rare event as this,"
      + " we need a few fun things!\n");
} /* create_armour */
