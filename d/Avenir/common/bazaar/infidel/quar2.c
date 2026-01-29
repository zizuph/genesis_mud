// file name: quar2
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object guard, guard1, female;

void
create_room()
{
   quar_long("A long wooden table extends down the middle "
            +"of this large room, scarred and stained. This "
            +"seems to be a mess hall. The walls are of bare "
            +"stone, and do not make for a very pleasant "
            +"eating experience.");
 
   set_short("mess hall");
   AI(({"table"}),"The table is very long, and has dozens "
            +"of scars along its mahogany surface. There "
            +"are also stains on it from when people were "
            +"eating in a rush.\n");
   AI(({"chair","chairs"}),"The chairs in the room are hard "
            +"wooden frames, with some thin cloth placed over "
            +"them to make them a bit more comfortable.\n");
   AI(({"wall","walls","stone"}),"The walls in the room are "
            +"of bare, roughly carven stone. They emanate "
            +"cold.\n");

   hall_exit("6","northwest");

   reset_room();
}

void
reset_room()
{
   if(!guard1)
     {
        guard = clone_object(MON+"guard");
        guard->arm_me();
        guard->move(TO);
        guard->add_act("hmm");
        guard->add_act("emote sits at the table and "
                      +"starts to gnaw on a stick of "
                      +"jerky.");
        guard->add_act("burp quiet");

     }
   if(!guard1)
     {
        guard1 = clone_object(MON+"guard");
        guard1->arm_me();
        guard1->move(TO);
        guard1->add_act("hmm");
        guard1->add_act("smile hung");
        guard1->add_act("say I wish we could get some "
                       +"decent food around here.");
     }
   if(!female)
     {
        female = clone_object(MON+"g_infidel");
        female->arm_me();
        female->move(TO);
        female->add_act("emote carries some dishes from the "
                       +"table.");
     }
 
}
