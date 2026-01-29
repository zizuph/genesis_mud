/* File         : /d/Khalakhor/n_speir/daenbraigh/camp/rooms/camp_path_4.c
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

string
describe_mess_hall ()
{
  string desc, my_race;

  my_race = TP->query_race_name();
  desc =
    "You see a large, crudely constructed wooden building to your " +
    "north. ";
  if(my_race == "goblin" || my_race == "orc" || my_race == "ogre")
    desc += "Pleasant smells of cooked food emit from the entrance.";
  else
    desc += "Nasty smells of goblin cooking emit from the entrance.";
  desc += "\n";
  return desc;  
}

void
create_khalakhor_room ()
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

  set_short("Middle section of northern camp path\n");
  set_long("* Long description * + messhall\n");

  add_exit("messhall", "north");
  add_exit("path_ne",   "east");
  add_exit("path_nw",   "west");

  add_item(({"barrack", "wooden building", "building", "hall"}),
           describe_mess_hall);
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
  return ({-1,-6});
}
