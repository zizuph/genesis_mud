/* /d/Ansalon/goodlund/nethosak/docks/room/barracks02.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_IN;

void create_nethosak_room()
{
    set_short("Officer barracks on the Storm Seeker");
    set_long(
      "On each side of the wall a lone bunk is secured.  At the " +
      "foot of both bunks there is a large metal foot locker, " +
      "locked securely.  Against the fore wall charts and maps " +
      "have been secured to a board.  Below these is a table, " +
      "also covered with papers, and various instruments.  The " +
      "floor is slightly slanted to the aft so that water may " +
      "collect in the bilge room.  The stench coming from the many " +
      "bunks crammed together to the aft is almost to much to bear.\n");

    add_item("table",
      "Maps and charts cover the top of this table, held down by " +
      "various nautical instruments.  The legs of the table have " +
      "been crudely nailed into the floor.\n");
    add_item("instruments",
      "Scattered about the table are various nautical " +
      "instruments.  Included are a astrolabe, a backstaff, a " +
      "compass, a lead, and a log.\n");
    add_item("board",
      "A small thin board that has been nailed onto the fore wall.  " +
      "Maps and charts have been put up all over the board, many " +
      "have ship routes inked on then.  The wood is strangely soft, " +
      "allowing all the maps and charts to be up by small tacks.\n");  
    add_item(({"charts","maps","papers"}),
      "Navigation charts and maps cover the wall and surface of the " +
      "table.  Maps are here for the whole of Ansalon, some very " +
      "detailed and others less so.  One of the maps shows a route " +
      "from a small peninsula on the mainland to here that has been " +
      "recently inked in.\n");
    add_item(({"bunk","bunks"}),
      "Each of these bunks are exempt of any padding and covers " +
      "leaving nothing more then a bare wooden slab to sleep on.  " +
      "At the foot of each bunk is a large metal foot locker, each " +
      "locked securely with a sturdy metal lock.\n");
    add_item("floor",
      "Scrubbed clean, the wooden floor is in perfect condition.  It " +
      "has a slight slant to the left, so that water from above may " +
      "collect in the bilge room, to later be pumped out of the " +
      "ship.\n");
    add_item("bilge room",
      "All the way in the back of the ship the bilge pumps sit.  " +
      "Water that manages to find its way below deck collects in " +
      "the bilge room to be pumped back out.\n");
    add_item("deck",
      "Being below deck and all makes it hard to check out the " +
      "deck above.\n");
    add_item("stench",
      "The stench coming from the bunks brings back memories of " +
      "growing up on the farm.\n"); 
    add_item(({"wall","walls"}),
      "These 'walls' appear to just be the sides of the hull of the " +
      "ship.  They are curved outwards mimicing the outside of the " +
      "hull.\n");

    add_exit(DROOM + "barracks01.c","aft",0);
} 