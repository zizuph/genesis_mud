 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("You are in the usually looking part of evil camp. "+
           "Usualy there are many barbarians here, who don't "+
           "like other people in his camp. Don't wonder if you "+
           "get attacked!\n"+
           "You also notice fence, blocking movement "+
           "to the north and south.\n");
  set_short("Usualy looking part of the camp");
  add_exit(CAMPDIR+"gcamp2","northeast","@@trygo");
  add_exit(CAMPDIR+"camp19","southwest",0);
 
  maxbar=0;
 
}
 
#include "resetcamp.o"
 
 
