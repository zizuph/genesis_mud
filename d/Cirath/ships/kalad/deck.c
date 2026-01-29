 /* /d/Cirath/ships/kalad/deck.c
  * Inside a crowded wagon.
  * Decius, November 1996
  */

#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/ships/kalad/std/deck";

#include <stdproperties.h>
#include "ship.h"
#include "defs.h"

void
create_deck()
{
  set_deck_sound("The wagon rumbles along noisily.\n");
  set_bump_sound("The wagon slowly grinds to a halt.\n");
  set_short("Inside a crowded wagon");
  set_long("Wooden crates and passengers share the limited "+
    "space inside this caravan wagon. Huge parcels of cargo "+
    "fill most of the wagon, leaving little room for anyone "+
    "to stand, and even less room for any luxuries such as "+
    "chairs.  A dozen heavily armed guards occupy the windows, "+
    "keeping watch for raiders, and a dozen more stand "+
    "guard in front of the crates, watching you.\n");

  add_item(({"crates","wooden crates","boxes","parcels","crate","box","cargo"}),
    "Head-high stacks of crates fill two-thirds "+
    "of the wagon. The guards prevent you from a closer "+
    "inspection of their contents.\n");

  add_item("passengers","The few passengers taking this "+
    "voyage all seem to be keeping to themselves, avoiding "+
    "eye contact with anyone.\n");

  add_item("wagon","This is the dark and dusty interior "+
    "of the mekillot wagon.\n");

  add_item("guards","Well trained human guards keep "+
    "wary watch at their posts.\n");

  add_item("windows","Bright sunlight filters into the "+
    "wagon through thin windows. Looking outside reveals "+
    "bleak terrain. Or if you happen to be looking out "+
    "a front window, the rear end of a mekillot.\n");

  add_item(({"mekillot","lizard"}),
    "The lizard's rear end which graces your view out the "+
    "front windows is a singularly unpleasant sight.\n");

  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_IS,1);
  add_prop(ROOM_I_LIGHT,1);
  add_prop(ROOM_I_NO_TELEPORT,1);
  add_prop(ROOM_I_HIDE,-1);

}
