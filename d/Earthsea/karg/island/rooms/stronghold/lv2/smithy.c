#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(3);
object leader;

void create_stronghold_room()
{
 set_short("Small smithy");
 set_long("This small room is used by kargs as an improvised smithy. "+
   "You see racks around on the walls, and massive forge in the "+
   "middle of the room.\n");

 add_item(({"rack","racks"}),"Racks are full with all kind of weapons, "+
   "You see swords , axes and clubs inside of racks.\n");
 add_item("forge","It is used by karg smith to make all kind of "+
   "weapons for guards. It looks massive , you see large hammer "+
   "on the top of the forge.\n");
 add_item("hammer","Massive and very heavy hammer, used to make "+
   "weapons.\n");

 add_exit(STRHOLD_LVL2+"cor26","east");

 reset_room();
}

void reset_room()
{
 int i;
 string to_clone;

 for(i=0;i<sizeof(guards);i++)
  {
   if(!guards[i])
    {
     switch(i)
      {
       case 0: to_clone="guard"; break;
       case 1: to_clone="mercenary"; break;
       case 2: to_clone="mercenary"; break;
      }
     guards[i]=clone_object(STRHOLD_NPC+to_clone);
     guards[i]->set_help(1);
     guards[i]->set_auto_reteam(1);
     guards[i]->move(TO);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
    }
  }
}

