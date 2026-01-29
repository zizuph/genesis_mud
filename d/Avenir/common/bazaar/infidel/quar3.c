// file name: quar3
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object guard, guard1, guard2;

void
create_room()
{
   quar_long("This large room had about a dozen bunks "
            +"scattered against the walls. The beds are "
            +"low and look uncomfortable, but the room "
            +"is fairly clean and pleasant.");

   set_short("dormitory");
   AI(({"chair","chairs"}),"The chairs in the room are hard "
            +"wooden frames, with some thin cloth placed over "
            +"them to make them a bit more comfortable.\n");
   AI(({"bunk","bunks","bed","beds"}),"The beds are low "
            +"and uncomfortable, but they are clean and "
            +"freshly made with blankets of thick wool.\n");
   AI(({"blanket","blankets","wool"}),"The blankets on the "
            +"bed are thick and warm.\n");

   hall_exit("7","southeast");

   reset_room();
}

void
reset_room()
{
   if(!guard)
     {
        guard = clone_object(MON+"guard");
        guard->arm_me();
        guard->move(TO);
        guard->add_act("yawn");
        guard->add_act("stretch");
        guard->add_act("emote sits on the bed and begins to "
                      +"take "+ guard->query_possessive() +" boots off.");
     }
   if(!guard1)
     {
        guard1 = clone_object(MON+"guard");
        guard1->arm_me();
        guard1->move(TO);
        guard1->add_act("hmm");
        guard1->add_act("yawn");
        guard1->add_act("stretch");
        guard1->add_act("emote sits on the bed and begins to "
                      +"take "+ guard1->query_possessive() +" boots off.");

     }
   if(!guard2)
     {
        guard2 = clone_object(MON+"guard");
        guard2->arm_me();
        guard2->move(TO);
        guard2->add_act("hmm");
        guard2->add_act("yawn");
        guard2->add_act("stretch");
        guard2->add_act("emote sits on the bed and begins to "
                      +"take "+ guard2->query_possessive() +" boots off.");

     }
 
}
