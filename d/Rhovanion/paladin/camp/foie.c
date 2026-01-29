inherit "/std/room";
#include "/d/Rhovanion/defs.h"
#include "campdef.h"
#include "trygo.o"
 
int maxbar;
 
void create_room()
{
   maxbar=0;
   set_long("Very simply looking room.\n"+
            "But you just notice huge door to the south!\n");
   set_short("Just room");
   add_exit(CAMPDIR+"gcamp2","west");
   add_item("door","Very strong looking door. "+
            "You wonder how to open it.\n");
}
 
 
int allow_dest_door()
{
   return 1;
}
 
 
void dest_door()
{
   add_exit(CAMPDIR+"chiefroom","south",0);
   set_long("Very simply looking room.\n"+
            "But you just notice broken door, leading south !\n");
   remove_item("door");
   add_item("door","Crashed door.\n");
 
}
 
 
#include "filter_funs.h"
 
 
void reset_room()
{
 
  object *list;
  object dummy;
  int i,friends;
 
  friends=0;
  list=FILTER_LIVE(all_inventory(TO));
  for(i=0;i<sizeof(list);i++)
    if ((list[i]->query_name()=="Barbarian")||
         (list[i]->query_name()=="Chief"))
           friends++;
  for(i=friends;i<maxbar;i++)
    {
      dummy=clone_object("/d/Rhovanion/paladin/camp/est");
      dummy->move(TO);
    }
  remove_exit("south");
  remove_item("door");
  set_long("Very simply looking room.\n"+
           "But you just notice huge door to the south!\n");
  add_item("door","Very strong looking door. "+
            "You wonder how to open it.\n");
}
