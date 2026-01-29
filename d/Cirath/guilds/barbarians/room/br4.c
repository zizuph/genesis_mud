/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/barbarians/bc1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("Road in Barbarian Camp");
  set_long("east-west direction. To the west it leads further into the "+
           "camp and east out of it. South lies a large stone building, "+
           "belonging to the elder barbarians. North lies an entrance "+
           "to a tent.\n");

  add_item((("tents")),"The tents belongs to two of the barbarian clans./n");
  add_item((("tent")),"There's a lot of them you know...\n");
  add_item(({"north tent","northern tent"}),"This tent is closed for the "+
             "time being.\n");
  add_item((("dust")),"The wind is whirling it up from the ground.\n");
  add_item((("sand")),"Of course it's sand in a desert, what did you think?\n");
  add_item(({"path","paths"}),"They are well-travelled...\n");
  add_item((("camp")),"You're standing in it...The mighty Barbarian Camp!\n");

  add_exit(BARB_ROOM + "btr", "east");
  add_exit(BARB_ROOM + "br3", "west");
  add_exit(BARB_ROOM + "bbk", "north");
  add_exit(BARB_ROOM + "startspot.c", "south");
}

