 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("You are in a part of the camp that you find "+
           "obviously evil. "+
           "Usualy there are many barbarians here, who don't "+
           "like other people in his camp. Don't wonder if you "+
           "get attacked!\n"+
           "You also notice fence, blocking movement "+
           "in every direction except small path.\n");
  set_short("Usualy looking part of the camp");
  add_exit(CAMPDIR+"camp5","north","@@trygo");
  add_exit(CAMPDIR+"camp13","south",0);
  add_item("fence","A plain-looking green painted fence,"+
           " about 2 meters high.\n");
  add_item("path","A small winding path inside the camp.\n");
 
  maxbar=0;
 
#include "resetcamp.o"
 
