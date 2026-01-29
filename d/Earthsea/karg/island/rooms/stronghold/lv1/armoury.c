#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(3);
object leader;

void create_stronghold_room()
{
 set_short("Armoury");
 set_long("This room is used by kargs as armoury. You see racks with "+
   "finished armours near the wall and big metal forge near it.\n");

 add_item("rack","It contains armours that smith has already "+
   "finished.\n");
 add_item("forge","Massive metal and very heavy forge. Near it you "+
   "see large hammer , which armourmaster uses to make armours.\n");
 add_item("hammer","It looks very heavy. Armourmaster must be very "+
   "strong man to wield it.\n");

 add_exit(STRHOLD_LVL1+"cor39","north");

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
     to_clone="guard";
     guards[i]=clone_object(STRHOLD_NPC+to_clone);
     guards[i]->set_help(1);
     guards[i]->set_auto_reteam(1);
     guards[i]->move(TO);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
    }
  }
}


