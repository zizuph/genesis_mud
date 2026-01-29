/* File:          /d/Khalakhor/ship/macdunn/shire/mast.c
 * Creator:       Teth
 * Date:          December 3, 1997
 * Modifications: December 8, 1997, Teth, added ability to exa view
 * Purpose:       The mast is a room on the Khalakhor to
 *                Shire ship, actually the crow's nest.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/shire/telescope.c
 * Comments:      This room also used the flight prop.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/cabin";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"

object telescope, room;
string deck1;

public void
create_cabin()
{
    set_short("in the crow's nest, on the Corran");
    set_long("   This is the crow's nest on the ship Corran. " +
      "It is used as a lookout, since it allows more distant " +
      "objects to be seen. A mastpole supports it from below. " +
      "A view of the lower deck is possible by looking down. " +
      "Wooden slats surround the platform, as a guard against " +
      "falling.\n");
    add_item(({"nest","crow's nest","lookout"}),"@@query_long");
    add_item(({"ship","vessel","boat","Corran","corran"}),
      "This the vessel you are currently sailing on. It is " +
      "sickle-shaped, with a series of sails propelling it on the " +
      "water.\n");
    add_item(({"deck","lower deck","deck below","down","below"}),
      "@@look_down");
    add_item(({"mastpole","pole","mast"}),"The white pine mastpole " +
      "supports the crow's nest. Knotted ropes line its length.\n");
    add_item(({"pine","white pine"}),"White pine is a straight-grained " +
      "wood often used for ship-building.\n");
    add_item(({"horizon","surrounding waters","waters","water"}),
      "Water stretches out as far as the eye can see into " +
      "the horizon.\n");
    add_item(({"slats","wooden slats"}),"The wooden slats surrounding " +
      "the platform are made of white pine, and guard against " +
      "falling.\n");
    add_item(({"up","sky"}),"The sky is cloudless, and a bright blue.\n");
    add_item("platform","The platform is made of white pine, " +
      "and appears to be oft used.\n");
    add_item(({"sails","series of sails","sail"}),"The sails are " +
      "made of layered linen, and easily capture the wind.\n");
    add_item(({"linen","layered linen"}),"Woven together, it is " +
      "an excellent system of capturing the air.\n");
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
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_CONFOUTART | TERRAIN_ONBOAT |
      TERRAIN_HUMID);

    add_exit(THIS_DIR + "deck","ghlskjg",1,1,1);

    set_bump_sound("The ship sails into a port, and halts.\n");
    set_cabin_sound("@@sounds");

    telescope = clone_object(OBJ_DIR + "telescope");
    telescope->move(this_object(), 1);

}

public string
sounds()
{
    if(random(2))
        return "The mast sways only slightly as the ship " +
        "sails through smooth waters below.\n";

    return "A fresh breeze caresses your face.\n";
}

public string
go_climb()
{
    if((this_player()->query_skill(SS_CLIMB) <= 15))
    {
        write("You find that despite the relative easiness of " +
          "the climb, you are unable to maneuver yourself " +
          "properly down the pole.\n");
        say(QCTNAME(this_player()) + " attempts to climb down the " +
          "mastpole, but fails.\n");
        return "";
    }

    write("You climb down the mastpole easily, using the handholds.\n");
    set_dircmd("down");
    this_player()->move_living("climbing down the mastpole",
      THIS_DIR + "deck", 0, 0);
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
      THIS_DIR + "deck", 0, 0);
    return "";
}

public string
go_jump()
{
    write("You jump over the edge, plummeting to the deck below!\n");
    set_dircmd("down");
    this_player()->move_living("jumping over the edge",THIS_DIR + "deck",
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
    room = find_object(THIS_DIR + "deck");
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
    object *inv, *live, *dead;
    string live_desc, dead_desc, add_desc;

    if (!ship || !environment(ship))
        return "It seems like you are sailing around in a void!\n";

    inv = all_inventory(environment(ship));
    live = FILTER_LIVE(inv);
    dead = filter(inv, "other_dead_than_this", this_object(), ship);

    live_desc = (live && sizeof(live) ? capitalize(COMPOSITE_LIVE(live)) : 0);
    dead_desc = (dead && sizeof(dead) ? capitalize(COMPOSITE_DEAD(dead)) : 0);
    add_desc  = ((live_desc ? break_string(live_desc + ".", 76) + "\n" : "") +
                 (dead_desc ? break_string(dead_desc + ".", 76) + "\n" : ""));

    if (this_player()->query_option(OPT_BRIEF))
        return capitalize(environment(ship)->short()) + ".\n" + add_desc ;
    else
        return environment(ship)->long() + add_desc ;
}

public int
other_dead_than_this(object obj, object ref)
{
  if (obj == ref || living(obj))
    return 0;
  else
    return 1;
}

