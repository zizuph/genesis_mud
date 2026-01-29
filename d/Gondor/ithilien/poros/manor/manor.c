/*
 *   /d/Gondor/ithilien/poros/manor/manor.c
 *
 *   The master room for the manor in the poros river area.
 *
 *   Talisan,  January 1996
 *
 *   Revision History:
 */

#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"


static string  Area = "room",
               Extraline = "";

public void set_area(string s) { Area = s; }
public void set_extraline(string s) { Extraline = s; }

public void
create_manor()
{
}

nomask void
create_room()
{
    string  long;

    create_manor();

    set_short(Area);

    long = CAP(LANG_ADDART(Area))+" inside the ruins of an old manor house.";
    if (strlen(Extraline))
        long += " " + Extraline;
    set_long(BSN(long));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_HIDE, 80);

}

static void
add_weeds(string extra = 0)
{
    string  desc =
        "Weeds and scrub grow unabated all throughout the area";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"weeds", "scrub", "scrub brush", "brush"}),
        BSN(desc));
}

static void
add_house(string extra = 0)
{
    string  desc =

        "Over time the elements have taken their on the old manor house, "
          + "causing the collapse of the structure in many areas. The manor "
          + "once home to a Dunadan Lord, seems to have been uninhabited "
          + "for centuries.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"manor", "manor house", "ruins"}),
        BSN(desc));
}

static void
add_door(string extra = 0)
{
    string  desc =

        "The once sturdy doors now lie broken, and fragmented at the "
          + "entrance to the manor, at the top of the stairs.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"door", "doors", "broken doors"}),
        BSN(desc));
}

static void
add_rubble(string extra = 0)
{
    string  desc =

        "Rubble from collapsed areas of the manor lie on the floor here.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"rubble"}),
        BSN(desc));
}

static void
add_furniture(string extra = 0)
{
    string  desc =
        "A few pieces of what was once finely crafted furniture lies "
          + "on the floor here. You notice that the pieces were broken "
          + "long ago, and are now quite rotted.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"furniture", "broken furniture"}),
        BSN(desc));
}

static void
add_carpet(string extra = 0)
{
    string desc =
        "You figure the carpet was once crafted from fine threads, but "
      + "now it lies rotting and musty on the floor.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"carpet"}),
        BSN(desc));
}

static void
add_hallway(string extra = 0)
{
    string  desc =
        "The hallway, as with the rest of the manor is old, and "
      + "smells of mildew.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"hallway", "floor", "ground", "hall"}),
        BSN(desc));
}

static void
add_passage(string extra = 0)
{
    string  desc =
        "This section of the manor is completely collapsed with rubble, "
      + "making further travel in that direction impossible.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"passage", "passageways", "north passageway",
        "east passageway", "west passage"}),
        BSN(desc));
}

static void
add_hallwayb(string extra = 0)
{
    string  desc =
        "It is evident that someone has been in this area recently. "
      + "Rubble and broken furniture have been moved and placed in piles.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"hallway", "floor", "ground", "hall"}),
        BSN(desc));
}

static void
add_stairs(string extra = 0)
{
    string  desc =
        "You notice the stairs are old and worn, much so like the "
      + "rest of the manor.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"stairs", "stairway"}),
        BSN(desc));
}

static void
add_engravings(string extra = 0)
{
    string  desc =
        "The engravings picture scenes from a hunt in which nobles "
      + "are chasing down large beasts.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"engravings"}),
        BSN(desc));
}
