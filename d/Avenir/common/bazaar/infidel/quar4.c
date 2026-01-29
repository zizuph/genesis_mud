// file name: quar4
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object female, female1, female2;

void
create_room()
{
   quar_long("There are long rows of beds along the west and "
            +"east walls, sweet smelling and warm. A couple "
            +"of small tables rest against the south "
            +"wall.");

   set_short("dormitory");
   AI(({"chair","chairs"}),"The chairs in the room are hard "
            +"wooden frames, with some thin cloth placed over "
            +"them to make them a bit more comfortable.\n");
   AI(({"bunk","bunks","bed","beds"}),"The beds are low "
            +"and quite comfortable, with sweet-smelling "
            +"blankets of soft wool.\n");
   AI(({"blanket","blankets","wool"}),"The blankets on the "
            +"bed are thick and warm.\n");
   AI(({"table","tables"}),"There are a couple of small night "
            +"tables against the south wall, where people "
            +"can put their possessions while they rest.\n");

   hall_exit("7", "north");

   reset_room();
}

void
reset_room()
{
   if(!female)
     {
        female = clone_object(MON+"g_infidel");
        female->arm_me();
        female->move(TO);
        female->add_act("yawn");
        female->add_act("smile sleep");
        female->add_act("smile tired");
        female->add_act("emote starts to loosen her "
                       +"woven shirt.");
     }
   if(!female2)
     {
        female2 = clone_object(MON+"g_infidel");
        female2->arm_me();
        female2->move(TO);
        female2->add_act("yawn");
        female2->add_act("smile sleep");
        female2->add_act("smile tired");
        female2->add_act("emote starts to loosen her "
                       +"woven shirt.");
     }
   if(!female1)
     {
        female1 = clone_object(MON+"g_infidel");
        female1->arm_me();
        female1->move(TO);
        female1->add_act("yawn");
        female1->add_act("smile sleep");
        female1->add_act("smile tired");
        female1->add_act("emote starts to loosen her "
                       +"woven shirt.");
     }
 
}
