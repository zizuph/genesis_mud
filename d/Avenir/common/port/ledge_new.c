// ledge           (/d/Avenir/common/port/ledge.c)
// creator(s):       Glinda june -95
// purpose:          A small ledge for noise. Draws attention from
//                   the real thing, the diving.
/*
 * Revisions:
 * 	Lilith, Aug 2014: Added cloning of the watch for quest.
 * 	Lucius, Jul 2017: Clone the watch if haven't done quest.
 *  Lilith, Nov 2021: Bumping up # of clones since item doesn't
 *    recover and it breaks.  
 *
 */
#include "port.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit "/std/room";
inherit "/lib/unique";


public void
create_room(void)
{
     set_short("On a small ledge");
     set_long("You are standing on a very small and very narrow ledge. " +
 "The cavern wall looms above you to the north. To the west you can " +
"barely catch a glimpse of the great rift which leads out of the cavern. " +
"South of you is the water. You don't really feel like entering it, but " +
"it seems to be your only option if you don't want to stay here the rest " +
"of your life.\n");

     add_item(({"water","currents","lake","ledge"}),
"This narrow ledge, barely big enough for you to stand on, is the only " +
"thing separating you from the dark murky water of the lake.\n");

     add_item(({"wall","crack"}),
"The wall seems to have been smoothened by the water. A small crack " +
"which seems to be man-made is visible in the wall.\n");

   add_prop(OBJ_I_SEARCH_TIME, 2);
   add_prop(OBJ_S_SEARCH_FUN, "do_search");
   enable_reset(200); // 45 mins

}

public void
reset_room(void)
{
    searched = 0;
}

public int
do_dive(void)
{
    TP->move_living("into the water", PORT + "water1", 1);
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(do_dive,"dive");
}


public mixed
do_search(object searcher, string str)
{
   object ob;
   
    notify_fail("Your search reveals nothing special.\n");
    if (searched)
      return 0;

    if (searcher->query_skill(SS_AWARENESS) < 24)
      return 0;

    if (str != "crack" && str != "wall")
      return 0;
  
    searched = 1; // Once per reset.
  //Starting to track search attempts.
    STATSERV_LOG_EVENT("port", "Searches for watch");  
	
   // Players are having trouble getting this in order to finish the quest so 
   // 1-Raised the # of clones to 15. It looks like the 'new' clone_unique 
   //   tracks # of clones via /d/Genesis/sys/global/unique.c and assumes that 
   //   50% of number of allowed clones is already assigned after each 
   //   Armageddon because of item recovery. Problem is, this item doesn't 
   //   recover, so 50% of the allowed clones may not be happening.   
   // 2-added a limit to the number of times the watch can be used and then
   //    it falls apart. This doesn't help with the allowed # of clones, 
   //    it seems, because the 'new' clone_unique system doesn't remove 
   //    broken/removed clones from its database of clones to free up new 
   //    ones.
   
   ob = clone_unique(DEAD + "obj/watch", 20, ({ PORT +"obj/oilskin_cloak", 
          "/d/Avenir/common/herbs/nethra", "/d/Genesis/gems/obj/sea_agate" }),
		  1, 50);
 

    if (!ob)
      return "Your search reveals nothing special.\n";
  
  	if (ob->id("_avenir_hours_amulet_"))	  
	   STATSERV_LOG_EVENT("port", "Watch found");
    
    ob->move(searcher);		

    return "You find "+ ob->short() +" hidden in the crack.\n";

}

