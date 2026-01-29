/* File         : /d/Khalakhor/n_speir/daenbraigh/camp/rooms/camp_path_5.c
 * Creator      : Serpine@Genesis * Copyright    : All rights given to Genesis
 * Date         : 12 July 2008
 * Purpose      : 
 * Related files:
 * Comments     : 
 * Modifications:
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
create_khalakhor_room()
{
  mapping path_config;

  path_config = ([
    "tower"     : 1,
    "tent"      : 0,
    "barricade" : 0,
    "spike"     : 0,
    "path"      : 0,
    "pole"      : 0,
    "hound"     : 1
  ]);
  ::create_path_room(path_config);

  set_short("Eastern section of northern camp path\n");
  set_long("* Long description *\n");

  add_exit("tent_o5", "north");
  add_exit("watch_1", "east");
  add_exit("path_en", "southeast");
  add_exit("tent_s1", "south");
  add_exit("path_nm", "west");

  reset_room();
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
  return ({0,-6});
}
