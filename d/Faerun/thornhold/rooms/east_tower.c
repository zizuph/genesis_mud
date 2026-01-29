/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;
object guard_npc;

int thimble_found = 0;
object thimble;

void
create_house()
{
    set_short("The East Tower");
    set_long("You are in the East Tower of Thornhold. The tower room is " +
             "a spartan stone room, with no furnishings or decor. Narrow " +
             "arrow slits encircle the tower, allowing one to view the " +
             "courtyard, the road, and the Mere of Dead Men. To the west, "+
             "a narrow door leads back out onto the battlement.\n");

    add_item(({ "slit", "slits", "narrow slits" }),
		"You can look through the slits towards the road, the " +
		"courtyard, or the Mere of Dead Men.\n");

	add_item(({ "mere", "mere of dead men", "dead men" }),
		"The name 'Mere of Dead Men' referred to the thousands " +
		"of dwarves, elves, and humans of the Fallen Kingdom " +
		"who were slain here during the invasion of an orc army.\n");

    add_item(({ "mere", "east", "swamp" }),
		"Peering through the slits in the east wall, you can see " +
		"the expansive swampland known as the Mere of Dead " + 
		"Men. Twisted dark trees loom over the swamp.\n");      

    add_item(({ "courtyard", "north" }),
		"Peering through the slits in the north wall, you can " +
		"see the courtyard. It bustles with activity. You also " +
		"notice an old, abandoned bird's nest here. \n");
                 
    add_item(({ "road", "gate", "gates", "south" }),
		"Peering through the slits in the south wall, you can see " +
		"the gates of the hold and part of the road as it winds " + 
		"down a ridge on the edge of the Mere of Dead Men.\n");
                
    add_item(({ "nest" }),
		"The nest is an old collection of fiber, twigs, and " +
		"random materials. You spot some shiny threads and " +
		"beads, suggesting it may be the nest of a magpie. \n");
                 
   add_item(({ "thornhold", "Thornhold", "hold", 
		"fortress", "fort" }),
		"You are standing in the east tower of " +
		"Thornhold.\n");

	add_item(({ "door", "narrow door" }),
		"A narrow door leads to the west.\n");

	

// this sets up the search routine to find something in the nest

    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");

    reset_room();
    
    add_exit(ROOM_DIR + "battlement",  "west");

    reset_room();
}

void
reset_room()
{
    ::reset_room();
    thimble_found = 0;  
    
    if ((!guard_npc))
    {
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
    } 
}

mixed
my_search(object searcher , string str)
{
    int awareness;
    
    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < 13) 
    {
        return 0;
    }
    if(str=="nest" || str=="magpie nest" || str=="twigs" || str=="collection")
    {
        if(thimble_found == 1)
        {
            return "You found nothing in the nest, though it appears " +         
            "to have been recently tampered with.\n";
        }
        else
        {
            if(!QUEST_MASTER->check_thimble(searcher))
            {
                seteuid(getuid(TO));
                thimble = clone_object("/d/Faerun/thornhold/obj/thimble.c");
                thimble->move(searcher,1);
                say(QCTNAME(searcher)+ 
                " finds something in one of the slits.\n");
                thimble_found = 1;
                return "You find a " + thimble->short() + 
                " inside the nest!\n";
            }
            else
            {
                return "You found nothing inside the nest.\n";
            }
        }            
        
      return "You found nothing inside the nest.\n";
    }
    else
    {
        return ;
    }
}