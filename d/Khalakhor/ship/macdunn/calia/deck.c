/* File:          /d/Khalakhor/ship/macdunn/calia/deck.c
 * Creator:       Teth
 * Date:          April 21, 1997
 * Modifications: November 11, 1997, Teth, added rocking feature
 * Purpose:       The deck is a room on the Khalakhor to
 *                Calia ship. It clones a net to the room.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/calia/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/calia/net.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"

object net;

public void
create_deck()
{
    set_short("on the deck of the Cuinnsear");
    set_long("   This is the ship, Cuinnsear, so named because of its " +
      "dagger-shaped design. It is a small fishing boat, " +
      "occasionally used to transport passengers. A small sail is " +
      "aloft on a pole. At the stern of the boat is a wooden " +
      "rudder, used to steer the ship. The planks of wood " +
      "forming the hull are white in colour. The boat rides " +
      "low in the water, and looks like it could be rocked " +
      "easily.\n");
    add_item(({"ship","cuinnsear","boat","small boat","small ship",
        "fishing boat","fishing boat"}),"@@query_long");
    add_item("design","The design of the boat is a dagger shape. " +
      "It has a narrow prow, then widens for the most part to the " +
      "stern of the ship.\n");
    add_item(({"prow","narrow prow"}),"The front of the boat, it is " +
      "quite narrow, so it cuts well through waves.\n");
    add_item("stern","The stern of the ship is fairly wide, to lend " +
      "some stability to the ship.\n");
    add_item("sail","The sail is made of ragged cloth, but it appears " +
      "to get the job done.\n");
    add_item(({"cloth","ragged cloth"}),"The ragged cloth of the sail " +
      "is a hodge podge of fabrics and patterns.\n");
    add_item("fabrics","The fabrics range from silk to canvas.\n");
    add_item("silk","Multi-layered, it is light and catches the wind " +
      "marvelously.\n");
    add_item("canvas","The canvas is heavy, but it is sturdy.\n");
    add_item("patterns","There are as many patterns as fabrics.\n");
    add_cmd_item(({"canvas","silk","fabrics","sail","cloth"}),
      "cut","You quickly realize that cutting the cloth may " +
      "prevent further sailing on this boat, and thus a possible " +
      "escape route! Not a good idea!\n");
    add_item("pole","The pole is made of a straight-grained wood.\n");
    add_cmd_item("pole","climb","Climbing this pole might " +
      "unbalance the ship, and tip it.\n");
    add_item(({"grained wood","wood","straight-grained wood",
        "straight wood"}),"The wood is most likely ash.\n");
    add_item("ash","The ash wood has no knots in it, nor any " +
      "twists in the grain.\n");
    add_item("hull","The hull of the ship looks sturdy enough to " +
      "withstand some of the abuse that the ocean would throw at " +
      "it.\n");
    add_item(({"wooden rudder","rudder"}),"The wooden rudder is " +
      "used to steer the ship. Due to the twists and pulls on a " +
      "rudder, it is made of oak.\n");
    add_item("oak","The oak of the rudder is heavy, but sturdy.\n");
    add_cmd_item(({"rudder","wooder rudder"}),"steer","That's the " +
      "captain's job!\n");
    add_item(({"planks","wooden planks","white planks",
        "painted planks"}),"The planks of the hull are firmly " +
      "and snugly fit together.\n");
    add_item("sky","The sky is blue, although a little bit cloudy.\n");
    add_item(({"cloud","clouds"}),"None of the clouds are " +
      "spectacular in any way.\n");
    add_item("water","The water is a green-blue hue.\n");
    add_cmd_item(({"hand in water"}),({"place","trace","put"}),
      "You place your hand in the water, and relax while it cools " +
      "your hand and calms your soul.\n");
    add_cmd_item(({"boat","the boat","ship","the ship"}),
      ({"rock","sway"}),"@@do_rock");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ROWBOAT | TERRAIN_SALTYWTR);
    set_deck_sound("@@sounds");

    net = clone_object(OBJ_DIR + "net");
    net->move(this_object(), 1);
}

public string
sounds()
{
    if(random(2))
        return "The boat wobbles while it is caught in a trough, between " +
        "two waves!\n";

    return "The ship nearly tips over, cresting on a high wave!\n";
}

public int
do_rock()
{
    write("You rock the boat, almost capsizing it!\n");
    say(QCTNAME(this_player()) + " rocks the boat, nearly capsizing " +
      "it!\n");
    if(present("cian"))
    {
        this_player()->add_prop(LIVE_I_ROCK_BOATS, 1);
        find_living("cian")->command("glare");
    }
    return 1;
}
