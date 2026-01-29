#include "vfest.h"
#include <filter_funs.h>
#include <options.h>

static nomask int do_invite(string str);

static nomask int
do_invite(string str)
{
    object player;

    notify_fail("Invite whom?\n");
    if (!str)
     return 0;

    str = lower_case(str);
    if (present(str,ENV(TP)))
	return 0;
    player = find_player(str);
    if (player)
    {
	if (!present("_vfest_invite_",player))
	{
	    if (player->query_prop(LIVE_O_ROOM_BEFORE_VFEST))
	    {
		write("But "+CAP(str)+" is already at the Vinasfest!\n");
		return 1;
	    }
	    setuid(); seteuid(getuid());
	    clone_object(INVITATION)->move(player,1);
	    write("You have just invited "+CAP(str)+" to the Vinasfest.\n");
	    return 1;
	}
	else
	{
	    write(CAP(str)+" has already been invited to this Vinasfest!\n");
	    return 1;
	}
    }
    write(CAP(str)+" was not found.\n");
    return 1;
}

