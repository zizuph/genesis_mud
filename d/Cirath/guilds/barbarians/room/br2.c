/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/barbarians/bc2.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("Road in Barbarian Camp");
  set_long("the camp. You can see many tents around you, but there's "+
           "no entrance to any here. East lies a crossroad.\n");

  add_item((("tents")),"The tents are quite big./n");
  add_item((("tent")),"There's a lot of them you know...\n");
  add_item((("dust")),"The wind is whirling it up from the ground.\n");
  add_item((("sand")),"Of course it's sand in a desert, what did you think?\n");
  add_item(({"path","paths"}),"They are well-travelled...\n");
  add_item((("camp")),"You're standing in it...The mighty Barbarian Camp!\n");
  add_item("entrance","There is no...\n");
  add_item("crossroad","It's east of you, in the middle of the camp.\n");

  add_exit(BARB_ROOM +"br3","east");
  add_exit(BARB_ROOM +"br1","west");
}

