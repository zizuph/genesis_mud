/*  This is a house.  Coded by Vader on 7/28/92 for the town of Calathin.

    This basic house will be standard for all in the northeast region
    of town (see ~common/town/town_map_draft3)
    
    changed call_out to set_alarm, Mortricia, May 1996
    changed momma.c location and add_exits for new Calathin code, Tomas 11/19/1999
*/

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/include/quest_bits.h"

#include "/d/Terel/include/Terel.h"

object citizen = 0;
object door;


public void
create_room()
{
  
  INSIDE;
  set_short("A house");
  set_long("You are in the house of a hearty Calathin " +
   "townsman.  This house is his prize possession, and represents " +
   "years of hard work.  The walls are made from fine pine logs, " +
   "and have been meticulously cared for over the years.  There are " +
   "various pieces of furniture around, and the floor is covered by an " +
   "imported draconian rug from their Imperial era. There is another " +
   "room to the north, and an exit is to the south.\n");

  add_item(({"furniture", "furnishings"}), "You see a chair, a desk, " +
   "a table, and a shelf filled with books.\n");

  add_item(({"shelf"}), "Several old books sit upon this shelf, including " +
   "a Bible, a couple of novels, and a song book.\n");

  add_item(({"chair", "seat"}), "This chair is quite sturdy.  It is " +
   "covered in plush cushions, and looks quite comfortable.\n");

  add_item(({"desk"}), "This desk is lined with fine leathers, and has " +
   "a leather writing surface too.\n");

  add_item(({"table"}), "A fine table.  It is covered by a tablecloth.\n");

  add_item(({"tablecloth"}), "It is decorated with small figures that " +
   "look like musical notes.\n");

  add_item(({"floor", "rug"}), "This rug has several different pictorials " +
   "resembling dragon men, and looks quite old.\n");

  add_item(({"wall", "pine logs"}), "These logs were taken from the " +
   "area that is now the Calathin town square.\n");

  
  add_exit(CALATHIN_DIR + "houses/house5a.c","north",0,1);

  door = clone_object(CALATHIN_DIR + "houses/obj/house5a_door");
  door->move(TO);

  add_npc(CALATHIN_DIR + "npc/std_citizen", 2);
}

public int
do_sit(string str)
{
   if (str == "in chair" || str == "chair") {
       write("You settle into the chair.\n");
       write("You sigh.\n");
       say(QCTNAME(this_player()) + " sits in the chair.\n");
       say(QCTNAME(this_player()) + " sighs.\n");
       return 1;
   }
   return 0;
}

public int
do_stand(string str)
{
   if (!str || str == "from chair") {
       write("You get out of the chair.\n");
       say(QCTNAME(this_player()) + " gets out of the chair.\n");
       return 1;
   }
   return 0;
}

public void
init()
{
   ::init();
   add_action(do_sit,   "sit");
   add_action(do_stand, "stand");
   add_action(do_stand, "rise");
}

