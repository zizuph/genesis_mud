/*
 *  The hotel room of the Sleeping Stallion
 *  
 *  copied from the hotel room in Re Albi 
 *
 *  created by unknown 
 *  modified for The Sleeping Stallion by Olorin on 6-jan-93
 */

inherit "/d/Gondor/common/room";
#include "/d/Gondor/common/lib/gs_include.c"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("Small room in the Sleeping Stallion in Edoras");
  set_long(BS("This is a small room on the first floor of "
  	+ "the Sleeping Stallion in Edoras. If you have bought a key from the "
    + "innkeeper downstairs, you can spend the night here by typing "
    + "'start here'. You will then start here the next time you enter "
    + "the game.\n"));

  add_exit(EDORAS_DIR + "hotel_hall", "east", 0, 2);

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

init()
{
  ::init();

    add_action("start","start");
}
int start(string s)
{
  object ob;

  if(!(ob=present("_the_key_to_the_sleeping_stallion_",TP)))
     {
       write("You don't have the key you need!\n");
       return 1;
     }
  NF("start where?\n");
  if(s!="here") return 0;

  ob->remove_object();

     TP->set_temp_start_location(EDORAS_DIR + "hotelr");

     write(BS("You notice that the small wooden key crumbles to dust in your "
     	+ "hand. Suddenly you are confident that you will start here the next "
        + "time you enter the game.\n"));
  return 1;
}
