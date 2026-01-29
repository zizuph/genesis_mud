/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 * Revision:
 * Added block so players have to examine the rubble. Grouthaur is 
 * in the room north of here
 * Finwe, January 2018
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;
int clone_trolls = random(2);

#define RUBBLE_PROP "_trollshaw_hidden_rubble"


void
create_tunnel_room()
{
    set_short("A collapsed tunnel");
    set_long("The tunnel opens to a large room full of bones " +
        "scattered about the room. Fallen rubble and stones block the " +
        "tunnel to the north.\n");
    set_add_bones();
    add_item(({"rubble","stones"}),"@@exa_rubble");


//    add_exit(TUN_DIR + "tcg02", "north","@@exa_bush");
    add_exit(TUN_DIR + "tb28", "south");
    add_exit(TUN_DIR + "tc14", "northwest");
    reset_shire_room();
}

void reset_shire_room()
{
    if (clone_trolls == 1) // if 1 make trolls, else no trolls
    {
        make_trolls();     
    }
    clone_trolls = random(2);

}
void
init()
{   
    ::init();
 
    add_action("enter_tunnel", "enter");
}

string
exa_rubble()
{
    if(TP->query_skill(SS_AWARENESS)>25)
    {   
       TP->add_prop(RUBBLE_PROP,1);
       write("It is full of fallen rocks, boulders, and earth. As you " +
        "examine the rubble, you see an opening leading through the rubble.\n");
    return "";
    }
    else
       write("it is full of fallen rocks, boulders and earth. The rubble " +
        "is thick and dense, blocking you from going north.\n");
       return "";
}

int
enter_tunnel(string str)
{
    if(str=="hidden opening" ||
       str=="opening" || 
       str=="rubble")
    {
        if(TP->query_prop(RUBBLE_PROP))
        {    
            write("You enter the hidden opening.\n");
            say(QCTNAME(TP)+" vanishes into a hidden exit somewhere.\n");
            tell_room(TUN_DIR +"tcg02",QCTNAME(TP) + " arrives.\n");
	    TP->move_living("M", TUN_DIR +"tcg02",1);
	   
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 0;
    }
    notify_fail("Enter what?\n");
    return 0;
}

