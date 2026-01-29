/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/barbarians/bcr.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("Middle of Barbarian Camp");
  set_long("You stand in the middle of the barbarian camp. There are "+
           "many tents around you. Two paths meets here, one in "+
           "north-south direction, and the other in east-west "+
           "direction. The air is full of dust and sand, making it "+
           "hard to breathe and the heat is almost unbearable.\n");

  add_item("tents","The tents are large and made of leather./n");
  add_item("tent","There's a lot of them you know...\n");
  add_item("dust","The wind is whirling it up from the ground.\n");
  add_item("sand","Of course it's sand in a desert, what did you think?\n");
  add_item(({"path","paths"}),"They are well-travelled...\n");
  add_item("camp","You in the middle of it...The mighty Barbarian Camp!\n");

 // add_exit(BARB + "br3","east");
 // add_exit(BARB + "br2","west");
 // add_exit(BARB + "br5","north");
  add_exit(BARB_ROOM  + "br3","south");

}
