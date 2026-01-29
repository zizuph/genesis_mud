/* File:          /d/Khalakhor/ship/macdunn/ansalon/mast.c
 * Creator:       Teth
 * Date:          December 4, 1997
 * Modifications: December 9, 1997, Teth, added ability to view surroundings
 * Purpose:       The mast is a room on the Khalakhor to
 *                Kalaman ship, actually the crow's nest.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/ansalon/telescope.c
 * Comments:      This room also used the flight prop.
 * Ported to the new ship system by Tapakah, 03/2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

object telescope, room;
string deck1;
public string sounds();

public void
create_room()
{
  ::create_shiproom();
    set_short("in the crow's nest, on the Bonnie Lass");
    set_long("   This is the crow's nest on the ship Bonnie Lass. " +
      "It is used as a lookout, since it allows more distant " +
      "objects to be seen. A mastpole supports it from below. " +
      "A view of the lower deck is possible by looking down. " +
      "Wooden slats surround the platform, as a guard against " +
      "falling.\n");
    add_item(({"nest","crow's nest","lookout"}),"@@query_long");
    add_item(({"ship","vessel","boat","lass","bonnie lass"}),
      "This the vessel you are currently sailing on. It is " +
      "an imposing wooden galley, that sails from Khalakhor to " +
      "Ansalon.\n");
    add_item(({"deck","lower deck","deck below","down","below"}),
      "@@look_down");
    add_item(({"mastpole","pole","mast"}),"The cured oak mastpole " +
      "supports the crow's nest. Knotted ropes line its length.\n");
    add_item(({"oak","cured oak"}),"Cured oak is a sturdy straight " +
      "wood often used for ship-building.\n");
    add_item(({"horizon","surrounding waters","waters","water"}),
      "Water stretches out as far as the eye can see into " +
      "the horizon.\n");
    add_item(({"slats","wooden slats"}),"The wooden slats surrounding " +
      "the platform are made of oak, and guard against " +
      "falling.\n");
    add_item(({"up","sky"}),"The sky is cloudless, and a bright blue.\n");
    add_item("platform","The platform is made of cured oak, " +
      "and appears to be oft used.\n");
    add_item(({"canvas sail","sail"}),"The canvas sail performs " +
      "its duty of capturing the wind extremely well.\n");
    add_item("canvas","It is a sturdy fabric that does not often rip.\n");
    add_item(({"rope","ropes","knotted ropes","knotted rope"}),
      "The ropes which line the mastpole can be used to climb up and " +
      "down its length.\n");
    add_item(({"view","surroundings"}),"@@see_view");
    add_cmd_item(({"mastpole","pole","mast","the mast","the pole",
        "the mastpole","rope","ropes","the ropes","the knotted ropes",
        "down the mast","down","down the mastpole","down the pole",
        "down the ropes","down the knotted ropes","down the mast"}),
      "climb","@@go_climb");
    add_cmd_item(({"mastpole","pole","mast","down the mast",
        "down the pole","down the mastpole","down","to the deck",
        "down to the deck"}),({"levitate","fly"}),"@@go_fly");
    add_cmd_item(({"down","over the edge","over the slats","off",
        "off the platform","over the side"}),"jump","@@go_jump");

    add_prop(ROOM_I_INSIDE, 0);
    set_terrain(TERRAIN_CONFOUTART | TERRAIN_ONVEHICLE | TERRAIN_COOL);

    set_bump_sound("The ship sails into a port, and halts.\n");
    set_cabin_sound(sounds());

    telescope = clone_object(SHIP_OBJS_DIR + "/telescope");
    telescope->move(this_object(), 1);

}

public string
sounds()
{
    if(random(2))
        return "The mast is jogged slightly as the ship " +
        "sails through an area of rough water.\n";

    return "Streaks of fog pass by below you, at water level.\n";
}

public string
go_climb()
{
    TP->add_fatigue(-15);
    if((this_player()->query_skill(SS_CLIMB) <= 15))
    {
        write("You find that despite the relative ease of " +
          "the climb, you are unable to maneuver yourself " +
          "properly down the pole.\n");
        say(QCTNAME(this_player()) + " attempts to climb down the " +
          "mastpole, but fails.\n");
        return "";
    }

    write("You climb down the mastpole easily, using the handholds.\n");
    set_dircmd("down");
    this_player()->move_living("climbing down the mastpole",
      DECK, 0, 0);
    return "";
}

public string
go_fly()
{
    if(!(this_player()->query_prop(LIVE_I_FLYING)))
    {
        write("You are not able to fly down at the moment.\n");
        say(QCTNAME(this_player()) + " attempts to fly downwards, " +
          "but fails miserably and is forced to stay in the platform.\n");
        return "";
    }

    write("You easily fly down from the crow's nest to the ship deck.\n");
    set_dircmd("down");
    this_player()->move_living("flying downwards",
      DECK, 0, 0);
    return "";
}

public string
go_jump()
{
    write("You jump over the edge, plummeting to the deck below!\n");
    set_dircmd("down");
    this_player()->move_living("jumping over the edge", DECK,
      0, 0);
    this_player()->heal_hp(-500);
    write("You crunch onto the deck!\n");
    say(QCTNAME(this_player()) + " crunches into the deck, falling " +
      "from above!\n");
    if (this_player()->query_hp() <= 0)
    {
        this_player()->do_die();
    }
    return "";
}

public string
look_down()
{
    room = find_object(DECK);
    deck1 = (capitalize(COMPOSITE_LIVE(all_inventory(room)))) + ".\n";
    if (!sizeof(all_inventory(room))) 
    {
        deck1 = "";
    }
    return (room->query_long() + deck1);
}

public string
see_view()
{
  if(! ship) return "";
  return NAVIGATION_MANAGER->examine_sea(ship, 2);
}
