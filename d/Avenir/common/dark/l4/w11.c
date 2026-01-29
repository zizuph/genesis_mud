/*
w10.c is S
w12.c is E
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

static int trap_here;

void
reset_room()
{
 
    trap_here = 1;  
}

void
create_room()
{
    set_short("large cavern");
    set_long(
      "You stand at the east end of a large stone cavern. Burnt-down\n" +
      "torches hang on the walls.  High overhead is a vaulted ceiling.\n" +
      "There is little dust here; in fact, this chamber appears to be\n" +
      "fairly clean. The western wall has niches carved in it, used as\n" +
      "shelves. You notice an odd-looking food processing facility in the\n" +
      "corner. A stone doorway leads south, and the cavern continues to "+
	  "the west.\n");    

    add_exit(L4 + "w10","south",0);
    add_exit(L4 + "w12","west",0);

    add_item("doorway", "The doorway is arched and carved from stone. "+
       "It leads south, into a clean passageway.\n");

    add_item(({"torch","torches"}),
      "The torches are well-used, although not very old.\n");

    add_item("ceiling",
      "The vaulted ceiling is very high, so it is hard to make out details.\n");

    add_item ("facility",
      "Strange smelling steam is rising from that pot" +
      " twice as big as yourself.\n");
    add_item (({"shelf", "shelves", "niches", "niche"}),
      "Niches carved out of rock serve as shelves to store supplies.\n");
    add_item ("supplies",
      "A pile of crap, you note nothing of interest upon the first glance.\n");

    IN;
    add_prop(ROOM_I_LIGHT, 0);
    add_prop (OBJ_S_SEARCH_FUN, "search_fun");
	 
	add_npc(MON + "ogre_mom", 1, &->equip_me());
	add_npc(MON + "ogre_kid", 2, &->equip_me());
	add_npc(MON + "rat", 1);
	
    reset_room();
}

string
search_fun(object tp, string what)
{
    if (trap_here && (what == "supplies" || what == "shelf" || what == "niche"))
    {
	clone_object(OBJ + "rat_trap")->move(this_object());
	trap_here = 0;
	tell_room (environment(tp),
	  QCTNAME(tp) + " discovers a rat trap on the shelf.\n", tp);
	return "You find a rat trap on the shelf!\n";
    }

    return "Your search reveals nothing.\n";
}
