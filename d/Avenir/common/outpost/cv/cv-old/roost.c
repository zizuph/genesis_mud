/* 
 * /cv/roost.c
 * This is where the bats roost.
 *
 * Nerull 2021
 * Lilith Nov 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";

inherit VAMPIRES_STD_ROOM;


/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.	
    set_short("Roost for bats");   
    set_long("The air is fresh and cool here, and smells of the sea. "
        +"The bats seem to enjoy their roost, which has been carved "
		+"out of the stone of the mountain to resemble a little cave "
		+"where dozens of them crowd together in their sleep. An iron "
		+"door with gilded metal mesh keeps them safely contained so "
		+"there will always be a bat available if you need one.\n");
    
	add_exit("room11", "east");
	
    add_item(({"recess", "cave", "little cave", "roost", "wall" }),
        "Set into the northern wall, this concave area houses a colony "
        +"of vampire bats just waiting to deliver messages for you. "
        +"You can <borrow bat> if you need one.\n");
    add_item(({"cage", "door", "iron door", "gilded mesh" }),
        "This an iron door with gilded mesh. Behind it is a colony "
        +"of bats that can deliver messages for you.\nYou can "
        +"<borrow bat> if you need one.\n");
    add_item(({"bat", "bats" }),
	    "These are the coven's messenger bats. They are the size of your "
        +"hand, with dark brown fur and wide, nearly translucent wings. "
        +"These bats have long ears and even longer fangs.\nYou can "
        +"<borrow bat> if you need one.\n");
    add_item(({"floor", "ground", "basalt"}),
        "The basalt floor is chiseled level and polished to a high gloss that "
        +"accentuates the sparkle of the microcrystals within it.\n");    
    reset_faerun_room();
}


public int
do_borrow(string str) 
{
   setuid();
   seteuid(getuid());
    
   object bat;
  
   if ((str != "bat") && (str != "vampire bat"))
   {
      notify_fail("Borrow what?\n");
      
      return 0;
   }
   
   bat = clone_object(VAMPIRES_GUILD_DIR + "obj/vampire_bat");
   
   if(bat->move(this_player()))
   {
      notify_fail("You cannot carry that much!\n");
      
      bat->remove_object();
      
      return 0;
   }
   
   write("You open the cage and borrow one of the coven's "
    +"vampire bats.\n");
   
   say(QCTNAME(this_player()) + " opens the cage and "
    +"borrows a vampire bat.\n");
   
   return 1;
}


public void
init()
{
    ::init();
    add_action(do_borrow, "borrow",0);
}