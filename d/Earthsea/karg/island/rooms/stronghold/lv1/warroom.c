#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(4);
object leader;

void create_stronghold_room()
{
 set_short("In the war room.");
 set_long("This large hall is used by kargs as a war room. Kargs "+
   "officers discuss the tactics before the battle using large oak "+
   "table , in the middle of the room. Around the hall you see flags "+
   "of Karg Empire and portrait of Karg Emperor on the wall.\n");

 add_item("table","On this table karg officers simulate the combat to "+
   "discuss and approve tactics for future combats. You see maps all "+
   "over the table.\n");
 add_item(({"map","maps"}),"You see maps of Gont , Karg Empire and "+
   "Earthsea. On the maps you see positions of karg warships around "+
   "Gont shores.\n");
 add_item(({"flag","flags"}),"Flags of Karg Empire flow slightly in "+
   "gusts of sudden wind that breaks into the room through open "+
   "windows.\n");
 add_item("portrait","This is portret of Emperor of Karg Empire. He "+
    "sits on golden throne , holding scepter in his right hand.\n");
 add_item(({"window","windows"}),"Beautiful view of sea is available "+
    "through open windows. You look out and see karg warships patroling "+
   "around.\n");

 add_exit(STRHOLD_LVL1+"cor32","southwest");

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
       case 0: to_clone="captain"; break;
       case 1: to_clone="lieutenant"; break;
       case 2: to_clone="lieutenant"; break;
       case 3: to_clone="lieutenant"; break;
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


