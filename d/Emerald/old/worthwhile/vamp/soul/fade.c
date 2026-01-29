#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

int fade(string str)
{
    int hiding, val, bval;
    
    if (strlen(str))
    {
        return 0;
    }

    hiding = environment(this_player())->query_prop(ROOM_I_HIDE);
    bval = this_player()->query_skill(SS_HIDE);
    if (hiding < 0 || hiding > bval)
    {
	notify_fail("It's far too hard to hide anything here.\n");
	return 0;
    }

    bval = (bval - hiding) / 2;
    val = bval + random(bval);

    if (this_player()->query_attack())
    {
        notify_fail("You can't hide yourself while in combat!\n");
        return 0;
    }

    if (this_player()->query_prop(OBJ_I_HIDE))
    {
        notify_fail("You can't hide any better than this!\n");
        return 0;
    }

    say(({ METNAME + " fades into the shadows.\n",
           ART_NONMETNAME + " fades into the shadows.\n",
           "" }));
    write("You fade into the shadows.\n");

    if (this_player()->query_prop(OBJ_I_INVIS))
    {
        this_player()->add_prop(OBJ_I_HIDE, val / 2);
    }
    else
    {
	this_player()->add_prop(OBJ_I_HIDE, val);
    }

    return 1;
}	
