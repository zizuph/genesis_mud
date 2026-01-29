/**
* Rack room
* Louie  2004
*/

#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GUILD_IR;

/** prototypes **/
int check_member();
int check_rank();

void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    setuid();
    seteuid(getuid());
    set_short("storage room of the Templar Knights");
    
    set_long("This space is used by the Templar Knights "+
        "to store any gear or equipment they wish to "+
        "leave for other Knights.  "+
        "The barracks can be found to the west.\n");
    
    clone_object(OBJ+"rack")->move(TO);
    
    add_exit(ROOM+"barracks","west",check_member);
    add_exit(ROOM+"knight_storage","north",check_rank);
    reset_guild_room();

}

int check_rank()
{
    if(!TP->query_wiz_level() && !TP->query_templar_rank())
    {
        write("You are not worthy to enter that room.\n");
        return 1;
    }
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
