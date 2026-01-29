/**
* Barracks
* Louie  2004
*/

#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GUILD_IR;
inherit "/lib/guild_support";

/** prototypes **/
int check_member();
int start(string str);


void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    set_short("barracks of the Templar Knights");
    
    set_long("This room contains row after row of bunks.  "+
        "This is the barracks of the Templar Knights of "+
        "Takhisis, and any member who desires to <start here> "+
        "may do so.  "+
        "To the east is the storage room.  "+
        "\n");
    
    add_item(({"bunk","bunks","row","row of bunks","bed","beds"}),
        "These bunks are where Templar Knights sleep when "+
        "they decide to <start> their day here.\n");
        
    add_exit(ROOM+"hallway1","south",check_member);
    add_exit(ROOM+"storage","east",check_member);
    
    reset_guild_room();

}

void
init()
{
    ::init();
    
    add_action(start, "start");
    init_guild_support();
}

int
start(string str)
{
    if (!strlen(str) || !(str == "here"))
    {
        write("Start here?\n");
        return 1;
    }
    
    if (!ADMIN->query_member(TP) &&
        !(TP->query_wiz_level()))
    {
        write("Only Templar Knights may start here.\n");
        return 1;
    }
    
    /*
    write("This function is temporarily disabled.\n");
    return 1;
    */
    
    if(TP->set_default_start_location(ROOM+"barracks"))
    {
        write("You will now wake here.\n");
    } else
    {
        write("Some error kept you from starting here.\n");
    }
    
    return 1;
    
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
