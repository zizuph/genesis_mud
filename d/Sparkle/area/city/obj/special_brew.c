/*
 *  /d/Sparkle/area/city/obj/special_brew.c
 *
 *  This is the medium level drink item from the Boar's Head Tavern
 *  in Sparkle. It is also the quest object needed by Carlsan for
 *  one of the tours he gives.
 *
 *  Sold at : /d/Sparkle/area/city/rooms/inside/sparkle_pub.c
 *  Quest at: /d/Sparkle/area/city/npc/town_crier.c
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

/* Prototypes */
public void        create_drink();

/*
 * Function name:        create_drink
 * Description  :        set up the drink object
 */
public void
create_drink()
{
    set_name("brew");
    add_name( ({ "special", "_sparkle_tour_quest_drink" }) );
    add_adj( ({ "special" }) );

    set_short("special brew");
    set_long("This is the so-called \"special brew\" from the"
      + " Boar's Head Tavern in Sparkle. Other than a reasonable"
      + " amount of alcohol, it isn't clear what is so special"
      + " about it. In fact, it smells a bit sulfuric!\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(200);
    set_alco_amount(24);
    add_prop(OBJ_I_WEIGHT, 170);
    add_prop(OBJ_I_VOLUME, 170);
} /* create_drink */