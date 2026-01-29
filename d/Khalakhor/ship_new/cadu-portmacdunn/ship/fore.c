/* File:          /d/Khalakhor/ship/macdunn/shire/fore.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications:
 * Purpose:       The fore is a room on the Khalakhor to
 *                Shire ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;
public string sounds();

public void
create_room()
{
  ::create_shiproom();
    set_short("on the fore deck of the Corran");
    set_long("   This is the fore deck of the Corran. The nose of the " +
      "ship is angled upright at a forty-five degree angle. " +
      "Ropes reach from the nose to the mastpole, supporting it. " +
      "Fresh sea air surrounds you. Barrels line the edges " +
      "of the deck.\n");
    add_item(({"deck","fore deck"}),"@@query_long");
    add_item(({"ship","boat","Corran","corran"}),"You are standing " +
      "on the ship, able to explore it as you please.\n");
    add_item("nose","The nose of the ship is angled upright, " +
      "causing the ship to look somewhat odd. However, " +
      "the design does yield a smooth ride.\n");
    add_item("ropes","The ropes are oiled, to resist the ravages of " +
      "the salty air. They criss-cross in many places, and " +
      "many seem to tether the mastpole.\n");
    add_cmd_item(({"ropes","the ropes"}),"climb","Climbing the ropes " +
      "would get you nowhere in particular. It's not worth the risk.\n");
    add_item("rope","No one particular rope stands out.\n");
    add_item(({"pole","mast","mastpole"}),"The mastpole of the ship " +
      "supports the sails. It is made of straight pine.\n");
    add_item(({"pine","straight pine"}),"Pine is a favoured wood " +
      "because of its straight grain.\n");
    add_cmd_item(({"pole","mast","mastpole"}),"climb","The mastpole " +
      "can only be reached from the main deck.\n");
    add_item("sails","The sails are woven with layers of linen, and " +
      "are quite effective in their task.\n");
    add_item(({"linen","layers of linen","layers"}),"The layers of " +
      "linen capture air effectively.\n");
    add_item("sky","The sky is sunny, reminding you of peaceful times.\n");
    add_item(({"air","sea air","fresh air","fresh sea air"}),"The " +
      "fresh sea air bites at your olfactory senses, leaving " +
      "a tingling feeling with every breath you take.\n");
    add_cmd_item(({"air","sea air","fresh air","fresh sea air"}),
      ({"smell","inhale"}),"Ahhhhhh!\n");
    add_item(({"barrels","barrel"}),"The barrels which line the " +
      "deck are all empty, suggesting that a shipment of freight was " +
      "recently unloaded.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK);

    add_exit("deck", "aft", 0);
    //    set_no_disembark();

    set_deck_sound(sounds());
    set_is_deck(1);
}

public string
sounds()
{
    if (random(2))
        return "The ship sails through smooth waters.\n";

    return "A few drops of sea water splash onto your face.\n";
}

