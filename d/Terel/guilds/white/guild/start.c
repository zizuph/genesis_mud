/*
 *  start.c, Start room
 *  Coded by Shinto 120798
 *
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/guilds/white/guild.h"

inherit WHITE + "guild/keep_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */

object door;

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("Start room");
    set_long("start room description\n");

    door=clone_object(WHITE + "guild/start_door")->move(TO);

    reset_room ();

}

public void
init()
{
    ::init();
    add_action("start", "start");
}


public int
start(string str)
{
   if (str != "here") return 0;
   
   if (!MEMBER(TP)) {
      write("You are not of the Order.\n");
      return 1;
   }
   
    TP->set_default_start_location(WHITE + "guild/start");
   write("Protect these halls that you now dwell.\n");
   return 1;
}




