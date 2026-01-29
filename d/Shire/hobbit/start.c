#pragma save_binary

inherit "/d/Shire/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/hobbit/hobbit.h"
#include "/d/Shire/bits.h"


int okay_to_start;

create_room()
{
  set_short("Lazy room");

  set_long("You have arrived in a warm, quiet room. Large fluffy"
        + " beds can be seen from wall to wall. A happy little"
        + " fire is burning away in the corner, providing heat"
        + " for the whole room. There is a small sign hanging"
        + " just above one of the walls. Most of the beds are"
        + " full at the moment, but if you look hard enough you"
     + " just might be able to find one for yourself.\n"
     + "A small alcove is west and some curtains lead east.\n");


  add_item(({"beds","fluffy beds","bed","large fluffy beds"}),
             "They look extremely comfortable. You see some sleeping "+
             "hobbits in each bed, you had better not disturb them.\n");
  add_item(({"fire","happy fire"}),
             "It is not very large, yet it seems to do its job very "+
             "well.\n");
  add_item(({"corner","walls"}), "There are four of them.");
   add_item("sign","It has words written on it.\n");
    add_item(({"alcove","small alcove"}),
   "It has a desk for writing in it.\n");


  add_cmd_item("sign","read",
               "You may sleep here after your long and arduous journeys,\n"
             + "to do so, you must 'rest here'.\n");

  add_exit(HOBGLD_DIR + "trainroom","southeast");
   add_exit(HOBGLD_DIR + "hall","northeast");
   add_exit(HOBGLD_DIR + "po","west");
   add_exit(HOBGLD_DIR + "bath","east");

  add_prop(ROOM_I_INSIDE, 1);
}


init()
{
  ::init();

    add_action("start","rest");
}



start(str)
{
   if(str == "here" && (IS_MEMBER(this_player())))
     {
       TP->set_default_start_location("/d/Shire/hobbit/start");
       write("You will awaken here when next you sleep.\n");
       return 1;

     }

  write("Either you are an idiot and cannot type properly "+
        "or you are not a Adventuresome hobbit. Please try again.\n");
  return 1;
}
