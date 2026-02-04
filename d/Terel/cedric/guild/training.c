#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define NUMCUBICLES	2

/*
 * The Minstrel Guild Headquarters: The Training Hall.  
 * Here Minstrels can train and improve their vocal and 
 * instrumental skills.
 * Jorl 2/93
 */

string
which_cubicle()
{
    int i;
    object room;
    string hack;
    
    seteuid(getuid(TO()));
    i=1;
    while(i<=NUMCUBICLES)
    {
	hack = GUILD+"cubicle_"+i;
	room = hack->this_room();
	if (!room->query_occupied())
	    return "cubicle_"+i;
	i++;
    }
}

void
create_room()
{
    set_short("The Training Hall");
    set_long(BS("This long hall is where the minstrels come to improve "
    + "their natural talents.  Several practice cubicles line the west wall. "
    + "Head that way if you wish to improve your minstrel abilities.\n"));
    
    add_exit(GUILD+"banquet", "northeast");
    add_exit(GUILD+"checkout", "south");   
    add_exit(GUILD+"@@which_cubicle", "west", "@@check_enter");
    add_prop(ROOM_I_INSIDE, 1);
}

int 
check_enter()
{
    if (!MEMBER(TP()) && !TP()->query_wiz_level())
    {
	TP()->catch_msg(("Only members of " +GUILD_NAME+" may train here.\n"));
	return 1; 
    }
    if (which_cubicle())
	return 0; 
    write("All the training cubicles are occupied right "
    + "now. Come back later.\n"); 
    return 1; 
}
