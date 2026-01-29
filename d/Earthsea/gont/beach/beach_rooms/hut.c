inherit "/std/room";

object fisherman;

#include "default.h"

void create_room()
{
 set_short("Inside hut");
 set_long("Inside of simple humble fisherman hut. There's nothing "+
   "here besides of bed , table and some fishing nets on the walls.\n");

 add_item("bed","Simple wooden bed , it looks very messy.\n");
 add_item(({"nets","net"}),"Nets look old and are full of holes.\n");

 add_exit(BEACH_DIR+"outside","out");

 setuid();
 seteuid(getuid());

 fisherman=clone_object(BEACH+"npc/fisherman");
 fisherman->move(TO);
 (OUTSIDE)->i_am_the_fisherman(fisherman);
}

