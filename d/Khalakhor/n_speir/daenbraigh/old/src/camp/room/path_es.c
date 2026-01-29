/* File         : /d/Khalakhor/n_speir/daenbraigh/camp/rooms/camp_path_8.c
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
    "hound"     : 0
  ]);
  ::create_path_room(path_config);

  set_short("Southern section of eastern camp path\n");
  set_long("* Long description *\n");

  add_exit("path_em", "north");
  add_exit("watch_2", "south");
  add_exit("path_se", "southwest");
  add_exit("kennel", "east");

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
  return ({1,-3});
}
