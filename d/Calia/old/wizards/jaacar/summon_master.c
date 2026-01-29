
inherit "/std/object";

#include <macros.h>
#define SUMMONER "/d/Calia/jaacar/summoner"

create_object()
{
    set_short("meeting summoner");
    set_long("It's a meeting summoner.  Just do 'summon <player>'"+
        "to summon them.\n");
}

do_meeting(string str)
{
    object player;

    if (!str || !strlen(str))
    {
        notify_fail("Summon who?\n");
        return 0;
    }

    if (!objectp(player=find_player(str)))
    {
        notify_fail(capitalize(str)+" is not in the game.\n");
        return 0;
    }

    if (player->query_linkdead())
    {
        notify_fail("They are linkdead.\n");
        return 0;
    }

    write("Summoning "+capitalize(str)+".\n");
    if (clone_object(SUMMONER)->move(player))
        write(capitalize(str)+" could not be summoned.\n");
    else
        write(capitalize(str)+" has been summoned.\n");
    return 1;
}
    
init()
{
    ::init();
    add_action(do_meeting,"summon");
}
