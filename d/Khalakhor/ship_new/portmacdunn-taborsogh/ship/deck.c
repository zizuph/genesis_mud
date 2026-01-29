/* File:          /d/Khalakhor/ship/macdunn/ansalon/deck.c
 * Creator:       Teth
 * Date:          April 12, 1997
 * Modifications: December 5, 1997, added a mast.
 *              : Teth - Feb 10 2002
 *                Switched to new mudlib terrain types.
 * Purpose:       The deck is a room on the Khalakhor to
 *                Ansalon ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/ansalon/barrel.c
 * Comments:      This room also uses the flight prop.
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;
public string sounds();

object barrel;

public void
create_room()
{
	::create_shiproom();
    set_short("on the deck of the Bonnie Lass");
    set_long("   This is the ship Bonnie Lass, a small vessel used " +
      "to ferry passengers. A mastpole stands tall in the fore " +
      "of the ship, while a cabin rests near the stern. The " +
      "swooping lines of the deck allow an excellent view of the " +
      "ship's surroundings. A salty tang in the air doesn't seem " +
      "to come from the ocean.\n");
    add_item(({"deck","area"}),"@@query_long");
    add_item(({"ship","vessel","small vessel","Bonnie Lass","lass",
        "Lass","bonnie lass"}),"This is the ship that ferries " +
      "passengers between the towns of Port Macdunn and Tabor Sogh.\n");
    add_item(({"mastpole","pole","mast","up"}),"The cured oak mastpole " +
      "supports the canvas sail used to propel the ship on windy " +
      "days. Knotted ropes allow passage to the crow's nest above.\n");
    add_item(({"ropes","knotted ropes","rope"}),"The ropes " +
      "are knotted and tied around the wood, acting as handholds " +
      "and footholds for climbers.\n");
    add_item(({"knots","knot"}),"The knots are made of rope, and " +
      "can support a fair weight.\n");
    add_item(({"nest","crow's nest"}),"The crow's nest above is a " +
      "small wooden landing where observations of distant realms " +
      "and objects can be made.\n");
    add_item(({"landing","wooden landing","small landing",
        "small wooden landing"}),"It is the crow's nest, above your " +
      "head.\n");
    add_cmd_item(({"mastpole","pole","mast","the mast","the pole",
        "the mastpole","rope","ropes","the ropes","the knotted ropes",
        "up the mast","up","up the mastpole","up the pole","up the ropes",
        "up the knotted ropes","up the mast"}),"climb","@@go_climb");
    add_cmd_item(({"mastpole","pole","mast","up the mast","up the pole",
        "up the mastpole","up","to the crow's nest","to the nest",
        "to the lookout","to crow's nest","to lookout"}),({"levitate",
        "fly"}),"@@go_fly");
    add_item(({"oak","cured oak"}),"This is a typical wood used to " +
      "build ships.\n");
    add_item(({"sail","canvas sail"}),"The sail is decorated with " +
      "the emblem of a set of bagpipes.\n");
    add_item(({"emblem","set","bagpipes"}),"The bagpipes represent " +
      "the spirit of Khalakhor.\n");
    add_item("cabin","A small cabin sits toward the stern of the " +
      "ship, most likely the dwelling of the captain.\n");

    add_exit(CABIN, "cabin", 0);
    add_exit(FORE,  "fore", 0);

    set_terrain(TERRAIN_SHIPDECK);

    set_deck_sound(sounds());
    set_is_deck(1);

    barrel = clone_object(SHIP_OBJS_DIR + "barrel");
    barrel->move(this_object(), 1);
}

public string
sounds()
{
    if(random(2))
        return "The ship sails through a foggy patch of the ocean.\n";

    return "The ship rocks gently with the waves.\n";
}

public string
go_climb()
{
  TP->add_fatigue(-15);
    if((this_player()->query_skill(SS_CLIMB) <= 15))
    {
        write("Despite the relative ease of " +
          "the climb, you are unable to maneuver yourself " +
          "properly up the pole.\n");
        say(QCTNAME(this_player()) + " attempts to climb the mastpole, " +
          "but fails.\n");
        return "";
    }

    write("You climb the mastpole easily, using the handholds.\n");
    set_dircmd("up");
    this_player()->move_living("climbing the mastpole", MAST,
                               0, 0);
    return "";
}

public string
go_fly()
{
    if(!(this_player()->query_prop(LIVE_I_FLYING)))
    {
        write("You are not able to fly up at the moment.\n");
        say(QCTNAME(this_player()) + " attempts to fly upwards, " +
          "but fails miserably.\n");
        return "";
    }

    write("You easily fly from the ship deck to the crow's nest.\n");
    set_dircmd("up");
    this_player()->move_living("flying upwards",
      MAST, 0, 0);
    return "";
}

public void
hook_smelled(string str)
{
      if(CAN_SEE_IN_ROOM(this_player()))
      {
        write("A strong salty scent emanates from a single, prominent " +
          "barrel.\n");
        return;
      }
        write("A strong salty scent emanates from somewhere around you.\n");
        return;
}

