 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("This is entrance to the evil camp.You also notice many "+
           "guards to the north! They definetely will "+
           "attack you! You'd better leave now, while you're "+
           "alive!\n");
  set_short("Entrance to the camp");
  add_exit(CAMPDIR+"entrance","north","@@testdd");
 
  maxbar=0;
 
}
 
#include "resetcamp.o"
#include "trygo.o"
 
int testdd ()
{
  if (TP->query_stat(SS_DIS)>100)
    {
     write("These places gives you creeps, but you brave continue..\n");
     return 0;
    }
  write("Umm.. No! You don't dare to continue in this direction.. \n");
  return 1;
}
