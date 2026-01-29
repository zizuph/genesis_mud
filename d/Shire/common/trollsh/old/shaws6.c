/* File: /d/Shire/common/shaws/shaws6.c */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#define BUSH_PROP "_have_found_the_tunnel"

create_shawrom()
{

    set_short("North of a small ridge in the Trollshaws.");
    set_extraline("You are situated north of the northeast "
	+"edge of one of the ridges here in the Shaws. "
	+"This place is very dense with pines and bushes. "
	+"To the northeast a small opening will let you through, "
	+"while to the south you see a small slope. "
	+"The pine forest is a lot more dense to the west.");
    
    remove_item("bush");
    remove_item("bushes");
    add_item(({"slope","small slope"}),"The slope leads south.\n");
    add_item(({"bush","bushes"}),"@@exa_bush");
    
    
    NORTHEAST("shaws8");
    WEST("shaws3");
    SOUTH("shaws5");

    add_call("enter", "[into] [the] [hidden] 'tunnel' / 'bushes' / 'bush'", "enter_tunnel");
    
}

void
init()
{   
    ::init();
 
    add_action("enter_tunnel", "enter");
}

string
exa_bush()
{
    if(TP->query_skill(SS_AWARENESS)>15)
    {   
       TP->add_prop(BUSH_PROP,1);
       write("As you examine the bushes more closely, you discover a hidden tunnel "
            +"leading into the ground underneath the shaws.\n");
    return "";
    }
    else
       write("The bushes seems to be dense right here, as if they were hiding something.\n");
       return "";
}

int
enter_tunnel(string str)
{
    if(str)
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            write("You enter the hidden tunnel.\n");
            say(QCTNAME(TP)+" vanishes into a hidden exit somewhere.\n");
            tell_room(TROLLSH_DIR +"tunnel1",QCTNAME(TP) + " arrives.\n");
	    TP->move_living("M", TROLLSH_DIR +"tunnel1",1);
	   
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 0;
    }
    notify_fail("Enter what?\n");
    return 0;
}
