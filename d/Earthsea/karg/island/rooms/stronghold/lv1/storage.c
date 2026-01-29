#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(3);
object leader;

void create_stronghold_room()
{
 set_short("Storage room");
 set_long("This is storage room , used by kargs to store different "+
   "items. You see boxes thrown all around the room. Some baskets "+
   "with food are set on the boxes.\n");

 add_item("boxes","They contain all kind of things , starting with "+
   "building materials , ending with books.\n");
 add_item("baskets","It contains food for all the guards in the "+
   "stronghold.\n");

 add_exit(STRHOLD_LVL1+"cor37","northeast");
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
       case 0: to_clone="eguard"; break;
       case 1: to_clone="eguard"; break;
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


