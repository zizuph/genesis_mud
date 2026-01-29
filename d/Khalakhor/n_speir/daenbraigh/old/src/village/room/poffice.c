/*
 * Daenbraigh post office
 * TAPAKAH, 04/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "../../daenbraigh.h";
#include "../../village/village.h";

inherit "/d/Khalakhor/std/room";
inherit "/d/Genesis/lib/post";
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_khalakhor_room();
  set_short("Daenbraigh Post Office");
  set_long("The post office was the last institution set in Daenbraigh " +
	   "as the army and the elder realized the importance of "       +
	   "communications with other goblin tribes of the world. It is "+
	   "built from thick wooden planks. Wooden crates are scattered "+
	   "on the floor. " + get_std_use());

  add_item(({"plank", "planks"}),
	   "The planks look to be collected from shipwrecks.\n");
  add_item(({"floor", "crates", "crate"}),
	   "The crates used for transporting mail are scattered all around.\n");
  add_prop(ROOM_I_INSIDE, 1);
  
  add_exit("we_2","north");
}

void
init()
{
  ::init();
  post_init();
}

void
leave_inv(object ob, mixed to)
{
  ::leave_inv(ob, to);
  post_leave_inv(ob, to);
}

int *
query_local_coords()
{
  return ({-6,1});
}
