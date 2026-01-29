/**
* Hallway
* Louie  2004
*/

#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GUILD_IR;

/** prototypes **/
int check_member();

void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    set_short("hallway in the guild of the Templar Knights");
    
    set_long("This is a plain hallway in the home of the Templar "+
    	"Knights of Takhisis.  "+
    	"To the south is the entrance of the building, as well "+
    	"as the location where people can join or leave the "+
    	"guild.  "+
    	"To the east is the training room of the Templar Knights, "+
    	"and to the west is the board room.  "+
    	"The north is where the barracks are located.  "+
    	"\n");
    	
    add_exit(ROOM+"barracks","north",check_member);
    add_exit(ROOM+"train","east",check_member);
    add_exit(ROOM+"boardroom","west",check_member);
    add_exit(ROOM+"joinroom","south",0);
    
    reset_guild_room();

}

int
check_member()
{
	
	if (TP->query_wiz_level())
	{
		return 0;
	}
	
    if (!ADMIN->query_member(TP)
        && !TP->query_pot_member())
	{
		write("Several guards suddenly appear and throw "+
			"you out of the building!\n");
		tell_room("Several guards suddenly appear "+
			"and throw "+QTNAME(TP)+
			" out of the room!\n", TP, TP);
		TP->move_living("M",ROOM+"joinroom",1,0);
		return 1;
	}
	
	return 0;
}
