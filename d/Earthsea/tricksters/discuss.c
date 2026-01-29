#include "defs.h"

inherit TRICKSTER_STD_ROOM;

object board;

void create_room()
{
 set_short("Discussion board room");
 set_long(BS(
   "This moist, poorly lit room is where fellow Tricksters come from "+
   "all over the land to discuss their ideas and share some of the "+
   "mischeivous pranks which they have played on some poor soul. "+
   "  The main feature of the room would have to be the bulletin "+
   "board, though, if you are indeed able to read.  You can leave this "+
   "room by either going northest, through a medium-sized hole or head "+
   "west towards a dim, dark room.\n"));

 add_exit(TRICKSTERS+"start","west");
 add_exit(TRICKSTERS+"train","northeast");
 add_exit(TRICKSTERS+"po","south");
 add_exit(TRICKSTERS+"bank","northwest");

 board=clone_object(TRICKSTERS+"obj/board");
 board->move(TO);
}

