/* File         : /d/Khalakhor/n_speir/daenbraigh/camp/rooms/camp_path_1.c
 * Creator      : Serpine@Genesis * Copyright    : All rights given to Genesis
 * Date         : 12 July 2008
 * Taken over by Tapakah, March 2009
 */

/* ------------------------------------------------------------------------- */

#pragma strict_types;
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "/d/Khalakhor/sys/terrain.h";
#include "../../daenbraigh.h";
#include "../../camp/camp.h";

inherit DAENBRAIGH_BASE;
inherit DAENBRAIGH_CAMP_PATH;

void
create_khalakhor_room ()
{
  mapping path_config;

  path_config = ([
    "tower"     : 0,
    "tent"      : 0,
    "barricade" : 1,
    "spike"     : 0,
    "path"      : 0,
    "pole"      : 0,
    "hound"     : 1
  ]);
  ::create_path_room(path_config);
  
  set_short("Middle section of western camp path\n");
  set_long(
    "You stand on the perimeter of a goblin war camp, west of a small "
   +"hill  surrounded by wooden spikes and capped with large command "
   +"tents, and east of a crudely constructed barricade.  Poles with heads "
   +"from various races have been erected here as a warning to "
   +"interlopers, and the baying of what are hopefully just hounds echoes "
   +"in the distance.  The path runs north and south around the camp.\n");

  add_exit("path_2", "north");
  add_exit("path_c", "south");
  add_exit("entry",  "west");

}

void
init()
{
  ::init();
}

void
reset_room()
{
  ::reset_room();
}

int *
query_local_coords()
{
  return ({-3,-4});
}
