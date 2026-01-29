/* /d/Ansalon/goodlund/nethosak/docks/room/cargo01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Cargo hold of the Storm Seeker");
    set_long(
      "A few pallets still have some small crates scattered about " +
      "on top of them.  However, most of the pallets in this hold " +
      "have nothing on them.  A set of doors are up above " +
      "in the ceiling, large enough to allow cargo to be lowered " +
      "down through them.  The floor slightly slants to the aft, " +
      "where water collects in the bilge room.  To the fore, " +
      "hatchways lead back up to the main deck.\n");

    add_item("pallets",
      "Pallets are layed about the floor of the hold, a few still " +
      "with crates on them.   All the pallets are of different " +
      "sizes, and are arranged in such a way to allow a walkway " +
      "through the middle of the hold.\n");
    add_item(({"crates","cargo"}),
      "A few small wooden crates sitting on pallets are all that is " +
      "left in the hold.  Each crate is covered in markings.\n");
    add_item("markings",
      "Each crate has burned into it various markings, you could " +
      "try and read them.\n");
    add_item("hold",
      "The section of the ship you stand in now, appears to be a " +
      "cargo hold.\n");
    add_item("doors",
      "A large set of wooden doors up in the ceiling (which is actually " +
      "just the main deck) are closed and sealed tightly.  There " +
      "appears to be no way to open them from down here.\n");
    add_item("floor",
      "Scrubbed clean, the wooden floor is in perfect condition.  It " +
      "has a slight slant to the left, so that water from above may " +
      "collect in the bilge room, to later be pumped out of the " +
      "ship.\n");
    add_item("bilge",
      "All the way in the back of the ship the bilge pumps sit.  " +
      "Water that manages to find its way below deck collects in " +
      "the bilge room to be pumped back out.\n");
    add_item("main deck",
      "Being below deck and all makes it hard to check out the main " +
      "deck.\n");
    add_item(({"hatch","hatchway","hatches","hatchways"}),
      "Large and bulky, the hatches lead back up to the main deck.\n"); 

    add_exit(DROOM + "bdeck01.c","fore",0);
    add_exit(DROOM + "bilge01.c","aft",0);
} 