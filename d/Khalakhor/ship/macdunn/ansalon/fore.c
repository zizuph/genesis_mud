/* File:          /d/Khalakhor/ship/macdunn/ansalon/fore.c
 * Creator:       Teth
 * Date:          April 2, 1997
 * Modifications: Teth - added terrain types, Sept 7 1997
 * Purpose:       The fore is a room on the Khalakhor to
 *                Ansalon ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrain.h"

public void
create_deck()
{
    set_short("on the fore deck of the Bonnie Lass");
    set_long("   This is the fore deck of the Bonnie Lass. A statue " +
      "thrusts proudly from the prow of the ship, challenging the " +
      "sea. Ropes tether the mastpole to the deck. Fresh sea air " +
      "surrounds you. A wheel stands in the middle of the fore " +
      "deck, an odd place for it.\n");
    add_item(({"deck","fore deck"}),"@@query_long");
    add_item(({"ship","Lass","lass","Bonnie Lass","bonnie lass"}),
      "You are standing on the ship, able to explore it as you " +
      "please.\n");
    add_item(({"wooden statue","statue"}),"The statue is of a " +
      "human female, clad in a robe. Her arms are outstretched, " +
      "as if welcoming the sea.\n");
    add_cmd_item(({"wooden statue","statue","the wooden statue",
        "the statue"}),({"grope","fondle","french","kiss","hug"}),
      "The statue does not respond to your affections.\n");
    add_item("prow","The prow of the ship is decorated with a wooden " +
      "statue of a female human.\n");
    add_item("ropes","The ropes are oiled, to resist the ravages of " +
      "the salty air. They criss-cross in many places, and " +
      "many seem to tether the mastpole.\n");
    add_cmd_item(({"ropes","the ropes"}),"climb","Climbing the ropes " +
      "would get you nowhere in particular.\n");
    add_item(({"pole","mast","mastpole"}),"The mastpole of the ship " +
      "supports the sail. It is made of cured oak.\n");
    add_cmd_item(({"pole","mast","mastpole"}),"climb","There are no " +
      "handholds that would make climbing the mastpole possible.\n");
    add_item("sail","The sail is made of canvas, and is used to propel " +
      "the ship on windy days.\n");
    add_item(({"oak","cured oak"}),"It is the favoured wood of " +
      "shipwrights.\n");
    add_item("canvas","Tightly woven canvas is a standard material for " +
      "sails.\n");
    add_item("sky","The sky is slightly cloudy, lending the atmosphere " +
      "a mood of unease.\n");
    add_item(({"air","sea air","fresh air","fresh sea air"}),"The " +
      "fresh sea air bites at your olfactory senses, leaving " +
      "a tingling feeling with every breath you take.\n");
    add_cmd_item(({"air","sea air","fresh air","fresh sea air"}),
      ({"smell","inhale"}),"Ahhhhhh!\n");
    add_item(({"wheel","steering wheel"}),"Upon closer " +
      "inspection, the steering wheel seems to be only " +
      "ornamental, but it is indeed finely crafted.\n");
    add_cmd_item(({"rudder","the rudder","steering rudder",
        "the steering rudder","wheel","the wheel","steering wheel",
        "the steering wheel"}),({"turn","twist","steer","guide"}),
      "The wheel rotates easily, as it is not connected to any " +
      "useful mechanism.\n");

    set_terrain(TERRAIN_SHIPDECK);

    add_exit(THIS_DIR + "deck", "aft", 0);
    set_no_disembark();

    set_deck_sound("@@sounds");
}

public string
sounds()
{
    if (random(2))
        return "Sea water splashes onto the deck of the ship as the boat " +
        "crashes into a high wave.\n";

    return "Sea foam covers the statue on the prow of the ship.\n";
}

public void
hook_smelled(string str)
{
        this_player()->command("$think the sea.");
        return;
}
