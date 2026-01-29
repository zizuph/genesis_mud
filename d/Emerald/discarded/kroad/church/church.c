/*
 * CHURCH.c
 * Redescribed and updated.
 * This room no longer contains any mention of anything that
 * might have existed behind the altar.
 *
 * By Alaron August 5, 1996
 */

inherit "/std/room";
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

static object sitting;
 
public string
altar_desc()
{
    string str = 
    	"This huge, dull-gray marble slab looks as though it "+
    	"could have been staggeringly beautiful when it was "+
    	"first placed here at the head of this church. Now it "+
    	"is nothing but a broken relic of a long forgotten time "+
    	"and place.\n";
    

    if (this_player() == sitting)
    {
        str += "From your position, you notice a small, circular " +
            "indentation on this side of the altar.\n";
    }

    return str;
}

void
create_room()
{
    set_short("Inside a small, ruined church");
    set_long("   You are surrounded by death and decay. The once white "+
	     "stone walls of the ancient church are now blackened with "+
	     "cracks and pieces of missing stone in them. The roof "+
	     "has long since begun to fall apart; resting far off to "+
	     "the side of the walls, leaving a large open space. Through "+
	     "the opening in the roof a thick, gray mist drifts into "+
	     "the church, blanketing everything in moisture and "+
	     "mildew. Foul, rank smells of putrescence and death "+
	     "fill the entire square chamber.\n"+
	     "   The center of the church is dominated by a gigantic, "+
	     "broken marble slab which may have at one point been "+
	     "the altar. Behind the altar sits an ancient, decaying "+
	     "stone chair.\n\n");

    add_prop(ROOM_I_INSIDE,1);
    
    add_item( ({"altar", "marble altar", "broken altar",
		"broken marble altar", "slab", "marble slab"}), altar_desc);
    add_item("floor", "It is too dirty to see what it is made of.\n");
   
    add_item( ({"chair", "stone chair", "large stone chair"}),
	     "The large stone chair has obviously been neglected for "+
	     "the centuries that it has sat in this desolate, foul-"+
	     "smelling place. The fine red oak scrollwork which surrounded "+
	     "the stone base of the chair now lies in an insect-chewed "+
	     "heap behind the cracked stone slabs which used to be "+
	     "an extravagant, throne-like seat.\n");
    
    add_item ( ({"openening", "up", "open space"}),
              "The large open space through the ceiling allows the ominous mist to "+
              "drift into the chamber, filling it with dampness and a musty "+
              "smell.\n");

    add_item( ({"wall", "walls"}),
             "The walls are rotting, cracked and in terrible shape. It "+
             "is a wonder that everything is still standing.\n");

    add_item( ({"mist", "eerie mist", "ominous mist"}),
             "The dark mist pours through the opening in the roof, "+
             "filling the chamber with dampness and a musty "+
             "smell, adding to the smell of rot and decay.\n");

    add_item(({ "indentation", "button", "small indentation",
		  "circular indentation", "small circular indentation", }),
        "It appears to be a button set into the stone.\n");

    add_exit("steps", "north");
    
}

public varargs mixed
long(string str, object for_obj)
{
    if (!for_obj)
    {
        for_obj = this_player();
    }

    if ((for_obj != sitting) &&
        (member_array(str, ({ "indentation", "button", "small indentation",
        "circular indentation", "small circular indentation", })) >= 0))
    {
        return 0;
    }

    return ::long(str, for_obj);
}

public int
item_id(string str)
{
    if ((this_player() != sitting) && 
        (member_array(str, ({ "indentation", "button", "small indentation",
        "circular indentation", "small circular indentation", })) >= 0))
    {
        return 0;
    }

    return ::item_id(str);
}

public int
sit(string str)
{
    if (!strlen(str) ||
        !parse_command(str, ({}), 
        "[down] 'in' / 'on' [the] [large] [stone] 'chair'"))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (sitting)
    {
        if (!present(sitting, this_object()))
	{
            sitting = 0;
	}
        else
        {
            write("There is already someone sitting there.\n");
            return 1;
	}
    }

    write("You sit on the large, stone chair.\n");
    say(({ METNAME + " sits on the large, stone chair.\n",
           NONMETNAME + " sits on the large, stone chair.\n",
           "" }));

    sitting = this_player();
    return 1;
}

public int
stand(string str)
{
    if (strlen(str) && 
        !parse_command(str, ({}), "[up] [from] [the] [large] [stone] 'chair'"))
    {
        return 0;
    }

    if (this_player() != sitting)
    {
        write("You are not sitting in the chair.\n");
        return 1;
    }

    write("You stand up.\n");
    say(({ METNAME + " rises from the chair.\n",
           NONMETNAME + " rises from the chair.\n",
           "" }));

    sitting = 0;
    return 1;
}

public int
push(string str)
{
    if (this_player() != sitting)
    {
        return 0;
    }

    if (!strlen(str) ||
        !parse_command(str, ({}), 
        "[the] [small] [circular] 'button' / 'indentation'"))
    {
      /* Should give a notify fail, but I don't want to give any hints
       * about what to do
       */
        return 0;
    }
        
    write("You press the small indentation.\n\nThe chair receeds into " +
        "the wall behind you and quickly drops down a floor.  As soon " +
        "as you stand up, it rises back up into place.\n");
    say(({METNAME + " suddenly disappears into the wall behind the altar!\n",
        NONMETNAME + " suddenly disappears into the wall behind the altar!\n",
        "" }));

    this_player()->move_living("M", GRAVEYARD_DIR + "under_church01", 1, 1);

    return 1;
}

void
init()
{
    ::init();
    add_action(sit, "sit");
    add_action(stand, "stand");
    add_action(stand, "rise");
    add_action(push, "push");
    add_action(push, "press");
}
