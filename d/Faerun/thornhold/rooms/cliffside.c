/*
 * Thornhold Cliffside
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

int tin_found = 0;
object tin;

void
create_road()
{
    add_cliff();
	add_extra_string_end("You are teetering precariously on a " +
	"cliffside on the western edge of Thornhold. The curved " +
	"stone wall of the west tower looms high above you. Due to " +
	"years of weathering and erosion, only a thin, rocky ledge " +
	"hugs the perimeter of the tower. Large, cracked rocks jut " +
	"up along the cliffside to the east, and the Sea of Swords " +
	"expands to the western horizon. Climbing the thin ledge back " +
	"east to the road appears to be the only route to safety.");
	
	add_item(({ "ledge", "east", "cliff" }),
             "The rocky ledge of the cliffside is narrow and precarious. "+
             "Rocks jut up from the ledge against the cliff, marred by " +
             "deep cracks. You can climb back down to the road to the " +
             "east.\n");

	add_item(({ "sea", "ocean", "horizon", "western horizon" }),
             "The Sea of Swords extends off west into the horizon. The " +
             "blue expanse is dizzying to behold as you keep your " +
             "balance on the narrow ledge.\n");

	add_item(({ "tower" }),
             "Looking up causes a dizzying moment of vertigo, allowing " +
             "only a brief glimpse of a plain stone tower reaching up " +
             "to the sky.\n");          
	
    add_item(({ "rock", "rocks", "crack", "cracks" }),
             "Large rocks are jutted up against the cliffside, leaving " +
             "the accessible ledge very narrow. The rocks appear to be " +
             "a variety of granite. Large cracks marr the surface, some " + 
             "of them cutting quite deeply into the stone.\n");
	
	add_cmd_item(({"east", "cliff", "ledge"}),"climb","@@climb");

    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");

    set_no_exit_msg(({"west"}),
    "YIKES! You peek out over the edge of the cliff and nearly " +
    "plummet into the Sea of Swords. After recovering from a moment of " +
    "vertigo, you regain your footing.\n");
    
    set_no_exit_msg(({"southwest"}),
    "You step towards the edge of the cliff and look down. Waves crash " +
    "on jagged rocks below, making you momentarily dizzy. You back " + 
    "away back and regain more secure footing.\n");

    set_no_exit_msg(({"south"}),
    "Your arms spin wildly as your body attempts to regain its balance " +
    "as you foolishly nearly step out into the open air above the " +
    "churning waters of the Sea of Swords far below.\n");

    set_no_exit_msg(({"southeast"}),
    "You step around for a bit, looking for a way to climb down to the " +
    "jagged coast below. You quickly realize that you'd have to have a " +
    "death wish to pursue this course further.\n");
    
    set_no_exit_msg(({"northwest"}),
    "WHOOSH! You suck in salten air with a sudden gasp " +
    "invoked by instinctive fear as you nearly step off the cliff and " +
    "into the crashing waves below.\n");
    
    set_no_exit_msg(({"north"}),
    "You inch your way along the ledge around the tower and find it " +
    "narrows until your foot slips, sending dirt and pebbles from the " + 
    "cliffside tumbling down frighteningly to the sea far below. Taking " +
    "a deep breath, you turn back.\n");
    
    set_no_exit_msg(({"northeast"}),
    "Unerved by your predicament, you attempt to find any way to gain " +
    "purchase on the west tower wall to regain entry into Thornhold. " +
    "Alas, climbing the ledge east back to the gates is your only " + 
    "route to safety.\n");
    
    set_no_exit_msg(({"east"}),
    "Eager to return to safety, you attempt to make your way east " +
    "along the ledge, but a deliberate climbing effort is required for " +
    "such difficult footing.\n");
    
    set_no_exit_msg(({"up"}),
    "You desperately look to see if there is any way to climb up the " +
    "west tower of Thornhold, but no such luck.\n");
    
    add_item(({"ledge","western ledge", "thin ledge"}),
    "You stand at the precipice overlooking the Sword Coast. " +
    "You might be able to climb east to the gates of the fortress.\n");
    
    reset_faerun_room();
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}

int climb()
{
    if(TP->query_skill(SS_CLIMB)>10)
    {
        TP->catch_msg("You carefully climb back east along the ledge " +
        "and return to the road in front of the gate.\n");
        TP->move_living("climbing along the precarious ledge that " +
        "leads back down towards the gate", 
        "/d/Faerun/thornhold/rooms/gate");
        return 1;
    }

    TP->catch_msg("You are not skilled enough to climb the ledge.\n");
    return 1;
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
    if(str=="rock" || str=="rocks" || str=="crack" || str=="cracks")
    {
        if(tin_found == 1)
        {
            return "You found nothing among the rocks, though it appears" +         
            "someone already searched here recently.\n";
        }
        else
        {
            if(!QUEST_MASTER->check_tin(searcher))
            {
                seteuid(getuid(TO));
                tin = clone_object("/d/Faerun/thornhold/obj/spice_tin.c");
                tin->move(searcher,1);
                say(QCTNAME(searcher)+ 
                " finds something among the rocks.\n");
                tin_found = 1;
                return "You find a " + tin->short() + 
                " lodged in a crack between the rocks!\n";
            }
            else
            {
                return "You find nothing else among the rocks.\n";
            }
        }            
        
      return "You find nothing among the rocks.\n";
    }
    else
    {
        return ;
    }
}
