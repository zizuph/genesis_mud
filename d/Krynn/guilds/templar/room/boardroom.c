/**
* Board room
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
    set_short("information room of the Templar Knights");
    
    set_long("This small room is used by the Templar Knights "+
        "to share information with each other.  "+
        "The only object in the room is a notice board "+
        "where notes may be posted.  "+
        "\n");
    
    
    clone_object(OBJ+"templar_board")->move(TO);
    
    
    add_exit(ROOM+"hallway1","east",check_member);
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
