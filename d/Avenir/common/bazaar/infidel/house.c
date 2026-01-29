// file name: house
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: House that enters the Infidel Hideout
// note:
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

object door, trapdoor;
int alarm_id;

void
create_room()
{
   set_long("This is a very small and sparsely furnished "
           +"house, with little of interest. A couple "
           +"of chairs rest on the hardwood floor, and "
           +"there is a small table in the center of the room. ");
   set_short("house");
   AI(({"chair","chairs"}),"The chairs are of simple "
           +"design, and are situated around the table.\n");
   AI(({"table"}),"The table is small and made from pine, or "
           +"some such soft wood. There is nothing on it.\n");
   AI(({"floor"}),"@@exa_floor");

   door = clone_object(OBJ+"housedoor_n");
   door->move(TO);
   trapdoor = clone_object(OBJ+"trapdoor_u");
   trapdoor->move(TO);

}

string exa_floor()
{
   if(TP->query_skill(SS_AWARENESS) > 35)
     return "The floor is made from hardwood slats laid "
       +"lengthwise along the room.\nYou notice a trapdoor "
       +"in the center of the floor.\n";
   else
    return "The floor is made from hardwood slats laid "
       +"lengthwise along the room.\n";
}

int close_up_shop()
{
   object other_door, other_trapdoor;

   if(door->query_open())
   {
   door->do_close_door("");
   other_door = door->query_other_door();
   other_door->do_close_door("The door swings closed.\n");
   door->do_lock_door("The lock on the door clicks as it closes.\n");
   other_door->do_lock_door("The lock on the door clicks faintly.\n");
   }
   if(!door->query_locked())
   {
   door->do_lock_door("The lock on the door clicks as the latch falls.\n");
   other_door->do_lock_door("The lock on the door clicks faintly.\n");
   }


   if(trapdoor->query_open())
   {
   trapdoor->do_close_door("The trapdoor slams shut.\n");
   other_trapdoor = trapdoor->query_other_door();
   other_trapdoor->do_close_door("The trapdoor slams shut from above.\n");
   }

   alarm_id = 0;
   return 1;
}

leave_inv(object to, object from)
{
   if(!alarm_id)
   alarm_id = set_alarm(60.0, 0.0, &close_up_shop());
   ::leave_inv(to,from);
}
