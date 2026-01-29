#include "../defs.h"

inherit ALT_STD + "room.c";

static int   hole_open;

private int         push_stone(string str);
private string      hole();

void
reset_room()
{
    hole_open = 0;
    remove_item("hole");
    remove_exit("down");
}


void
create_street()
{
    short_name("a busy street in Altaruk.");
    street_name("Giant");
    last_line("There are some bushes along the wall here.");
    
    add_item("wall", " a large portion of the wall is hidden" +
        " behind the bushes.\n");
    add_item("bushes", "The bushes covers a large portion of" +
        " the wall here.\n");
    add_cmd_item("behind bushes","look",&hole());
    
    add_exit("24.c", "west", 0,1,0);
    add_exit("26.c", "northeast", 0,1,0);

    reset_room();
}

void
init()
{
    ::init();
    add_action ("push_stone", "push");
}

private int
push_stone(string str)
{
    notify_fail("Push what?\n");
    if(str == "stone")
    {
    	if(hole_open == 1)
	{
    	    notify_fail("Push what? The hole is already open.\n");
	    return 0;
    	}
    	
    	write("You push the stone inside leaving a hole big" +
    	    " enough to move through. There is a thud as the" +
    	    " stone drops onto the ground inside.\n");
        hole_open = 1;
        add_item("hole", "The hole seems to lead down into a" +
            " dark room inside.\n");
        add_exit(ALT_ALL + "07.c", "down", 0,4,1);
        return 1;
    }
    return 0;
}

private string
hole()
{
    if(hole_open == 1)
    {
    	return("There is a gaping hole in the wall behind" +
    	    " the bushes. Like if a stone of the wall has" +
    	    " pushed inside.\n");
    }
    return("One of the stones in the wall behind the bushes" +
        " seems loose.\n");
}