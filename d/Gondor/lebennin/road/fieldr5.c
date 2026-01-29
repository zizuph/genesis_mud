/*
 * /d/Gondor/lebennin/road/fieldr5.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_RAB 1
#define MIN_AWARE 10


static object  Rabbit,
               Sword;

public void
create_area_room()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");
   
    add_exit(LEB_DIR + "road/fieldr6", "east", 0, 2);
    add_exit(LEB_DIR + "road/fieldr4", "west", 0, 2);
   
    add_item(({"river","anduin"}), BSN(
         "You get a pretty good idea of how wide the Anduin is from here, you can't"+
         " quite see the other bank from here."));
    add_item(({"field","ground"}), BSN(
         "The ground reveals rabbit tracks to you."));
    add_item(({"tracks","track","rabbit tracks"}), BSN(
         "They lead in all directions, making it impossible to follow a single track."));
    add_item(({"haystack","hay"}), BSN(
         "A large stack of hay, someone must have piled it here."));
   
    set_extraline("You are in a beautiful green field in the south of Lebennin."+
        " The field goes east and west, wildlife abounds."+
        " The river is to the east, and someone has piled a haystack here.");
   

   set_up_herbs( ({ HERB_DIR + "foxglove", HERB_DIR + "lothore",
		    HERB_DIR + "curugwath"}), 
                 ({ "bushes","bush","plain","ground","grass"}), 6);

    reset_room();
}

public string
herb_search(object searcher, string str)
{
   int     awareness;
   string  dummy;

   if (sscanf(str, "%s for %s", dummy, dummy) == 2)
       return ::herb_search(searcher, str);

   awareness = searcher->query_skill(SS_AWARENESS);
   if (awareness < (MIN_AWARE + random (MIN_AWARE)))
       return 0;
   if (!str || (str!= "haystack" && str != "hay")) 
       return 0;
   if (Sword) 
       return 0;

   Sword = clone_object(WEP_DIR + "fssword");
   if (Sword->move(searcher))
       if (Sword->move(TO))
           Sword->move(TO, 1);
   say(QCTNAME(searcher)+ " finds something in the haystack.\n");
   return "You find a shortsword in the haystack.\n";
}

public void
reset_room()
{
    ::reset_room();
    Sword = 0;
    Rabbit = clone_npc(Rabbit, NPC_DIR + "wrabbit", LEB_DIR);
    Rabbit->set_random_move(5);
}
