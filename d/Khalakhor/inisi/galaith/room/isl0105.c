/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"
#include "/d/Khalakhor/sys/basic.h"
#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */
#define GUILD_NAME      "Eil-Galaith"
#define GUILD_MIN_ALIGN 189
#define IS_MEMBER(x)    (x->query_guild_member(GUILD_NAME))
#define PIER2 "/d/Khalakhor/inisi/galaith/pier/pier2"
#define ENTRANCE "/d/Khalakhor/guilds/eilgalaith/room/entrance"
inherit ISLEBASE;

//public int
//acceptable_only()
//{
//    if( this_player()->query_wiz_level() || IS_MEMBER(this_player()) || //(this_player()->query_alignment() >= GUILD_MIN_ALIGN && //(this_player()->query_race_name() == "elf" || //this_player()->query_race_name() == "half-elf") )  )
//    {
//	/* Is a member, pass through as normal */
//
//	return 0;
//    }
//
//    write("A magical force prevents you from entering.\nYou are not "+
//      "welcome within the Sanctuary Tower!\n");
//    return 1;
//}

public void
create_khalakhor_room()
{
    proxim = (["harbour":({0, "south"}),
               "forest":({1, "northwest"}),
               "tower":({0, "north"})
                  ]);
  path = ({"west","east"});
  extra = "A soft breeze carries the sweet scent of the sea. ";
  create_meadow();
 
  add_exit(ENTRANCE, "north"); 
  add_exit("isl0104", "west");
  add_exit("isl0106", "east");
  add_exit(PIER2, "south");
   add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");
}
 
int
do_lay(string str)
{

    if((str == "down") || (str == "path") || (str == "honeysuckle"))
    {
	write("The path isn't a good place to lay down so you "+
	  "change your mind.\n");
	say(QCTNAME(TP)+" examines the path carefully.\n");
	  
    return 1;
    }
    else
   {
    notify_fail("Lay down?\n");
    return 0;
   }
}

void
init()
{
    ::init();

   add_action(do_lay, "lay");
}
