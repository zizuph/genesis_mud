// file name: Deck   
// creator(s): Ilyian, Oct 1995
// last update: 
// purpose: Deck of the ship to the Isle of Dead
// note:
// bug(s): 
// revisions:  Lilith Jan 2022: Added the missing room inside prop.
// to-do: 

inherit "/d/Genesis/ship/deck";

#include "/d/Avenir/common/ships/dead/deadship.h"

private int no_crew=0;
object *coffins = ({ });

void
create_deck()
{
   object coffin;
   
   add_prop(ROOM_I_INSIDE, 1);

   set_short("deck of a long barge");
   set_long("The deck of this barge is long and wide, "
           +"its weathered wooden floorboards creaking "
           +"underfoot. Both the prow and the stern "
           +"arch upwards to a point, and the sides "
           +"curve up at a sharp angle. There does not "
           +"seem to be any means of propulsion for the "
           +"vessel.\n");
   AI(({"prow","bow"}),"The prow arches upwards to a sharp "
           +"point, curving along the front of the "
           +"barge.\n");
   AI(({"stern"}),"The prow arches upwards to a sharp "
           +"point, curving along the back of the "
           +"barge.\n");
   AI(({"wood","floor","boards","side","sides"}),"The "
           +"ship is made from sturdy yet heavily "
           +"weathered wood that angles up from "
           +"the darp water.\n");

    set_deck_sound("The barge glides quietly over the "
                  +"still black waters.\n");
    set_bump_sound("The barge pulls into a landing with "
                  +"a heavy thud.\n");

   coffin = clone_object(COFFIN);
     coffin->move(TO);
     coffin->set_id_name("ship1");
   coffin = clone_object(COFFIN);
     coffin->move(TO);
     coffin->set_id_name("ship2");
   coffin = clone_object(COFFIN);
     coffin->move(TO);
     coffin->set_id_name("ship3");
}

lets_get_going()
{
  ship->lets_get_going();
  tell_room(TO, "The barge creaks as it pulls away from the "
               +"landing.\n");
}

/*
 * Function name: ship_arrived
 * Description  : Give a description about where we currently got to
 * Arguments    : A string or object pointing to the current room
 */
public void
ship_arrived(mixed where)
{
    ship = previous_object();
    if (where->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER) {
        tell_room(this_object(), check_call(bump_sound));

        if (ship->query_captain())

        ship->set_board_enable(1);
        exit_enabled = 1;
    }
    else {
        exit_enabled = 0;
        tell_room(this_object(), check_call(deck_sounds));
    }
}

object query_coffins(int number)
{
   if(number+1 > sizeof(coffins))
       return 0;
   else
       return coffins[number];
}

enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(!ob->id(COFFNAME))
    return;
   else
    coffins += ({ob});
    return;
}

leave_inv(object ob, object where)
{
   ::leave_inv(ob, where);

   if(!ob->id(COFFNAME))
    return;
   else
    coffins -= ({ob});
    return;
}
