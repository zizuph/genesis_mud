#include <stdproperties.h>

#include "defs.h"

inherit STD_STRHOLD;

object leader;
object admiral;
object *guards=allocate(4);
object chest;

void create_stronghold_room()
{
 set_short("Admiral's room in the stronghold");
 set_long("This room looks very wierd after the semi-wrecked "+
   "corridor that leads into it. Apparently kargs tried to trick "+
   "you, so you won't find this place. The room contains some beds, "+
   "on the walls you see racks with weapons and armours , as on the "+
   "floor you see rich, colourfull carpets, In the corner you see "+
   "large chest with massive lock. To the west you see wracked "+
   "corridor.\n");

 add_item(({"bed","beds"}),"On these beds admiral and his guards "+
   "sleep. One of them looks larger and better then others. You "+
   "guess it's admiral's one.\n");
 add_item(({"rack","racks"}),"Large metal racks contain spare "+
   "weapons and armours for guards, in case they break their once.\n");
 add_item(({"carpet","carpets"}),"Carpets cover most of the floor, "+
   "they look rich and colourfull, and decorated with good taste.\n");

 add_exit(STRHOLD_LVL1+"cor34","west");

 admiral=clone_object(STRHOLD_NPC+"admiral");
 admiral->set_auto_reteam(1);
 admiral->set_help(1);
 admiral->set_calm(1);
 admiral->set_stil(1);
 admiral->add_prop(LIVE_I_SEE_DARK,10);
 admiral->add_prop(LIVE_I_SEE_INVIS,10);
 admiral->move(TO);
 leader=admiral;

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
       case 0: to_clone="lieutenant"; break;
       case 1: to_clone="lieutenant"; break;
       case 2: to_clone="lieutenant"; break;
       case 3: to_clone="captain"; break;
      }

     guards[i]=clone_object(STRHOLD_NPC+to_clone);
     guards[i]->set_auto_reteam(1);
     guards[i]->set_calm(1);
     guards[i]->set_stil(1);
     guards[i]->add_prop(LIVE_I_SEE_DARK,10);
     guards[i]->add_prop(LIVE_I_SEE_INVIS,10);
     guards[i]->move(TO);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
     if(to_clone="captain") 
       clone_object(STRHOLD_OBJ+"key")->move(guards[i]);
    }
  }

 if(chest) chest->remove_object();
 chest=clone_object(STRHOLD_OBJ+"chest");
 chest->move(TO);
}

