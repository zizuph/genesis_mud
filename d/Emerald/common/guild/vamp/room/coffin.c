/* coffin.c created by Shiva@Genesis
 */

#pragma save_binary

inherit "/std/container";

#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>

#define COFFIN_OWNER(x) (id(LANG_POSS(x->query_real_name()) + " coffin"))

static object inside;

void
mkinside()
{
    setuid();
    seteuid(getuid());
    inside = clone_object(VAMP_ROOM_DIR + "inside_coffin");
    inside->set_outside(this_object());
}

void
create_container()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name( ({ "coffin", "vamp_coffin" }) );
    set_adj(({ "plain", "black" }));
    set_short("coffin");
    set_long("A plain, black coffin.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_S_WIZINFO, "If a coffin is buggy and preventing a " +
        "player from logging in, simply remove it.  The player should " +
        "then be able to log in successfully.  Please notify the " +
        "guildmaster and domain liege of any such bugs.\n");

    mkinside();
}

void
set_owner(string who)
{
    string posname = LANG_POSS(who);

    if (posname != (who + "'s"))
    {
        // This is probably a common misspelling, so we'll add it.
        add_name(who + "'s coffin");
    }

    add_name(posname + " coffin");
}

static int
coffin_enter(object who)
{
    int ret;
  
    if (!present(who, environment()) || !inside)
    {
        return 0;
    }

    inside->set_owner(this_player());

    ret =  who->move_living("M", inside, 1, 1);
    return !ret;
}

int
enter(string str)
{
    object env;
    string enter_msg;
  
    if (!strlen(str) ||
        !parse_command(str, ({ }), "[into] [my] / [the] / [" +
        this_player()->query_real_name() + "'s] 'coffin'"))
    {
    	NF("Enter what?\n");
    	return 0;
    }

    setuid();
    seteuid(getuid());

    if (this_player()->query_vamp_coven() != 
        LAIR_MANAGER->query_coven(file_name(environment())))
    {  
        write("You have no coffin here.\n");
        return 1;
    }

    env = environment(this_player());
    if (coffin_enter(this_player()))
    {
        setuid();
        seteuid(getuid());
        enter_msg = COFFIN_MANAGER->query_enter_msg(this_player());
 
        write("You lie down inside your coffin and close the lid " +
	    "above you.\n");

        if (strlen(enter_msg))
	{
            tell_room(env, enter_msg + "\n");
	}
        else
	{
            tell_room(env, ({ this_player()->query_name()  + " lies down in " +
                POS(this_player()) + " coffin, closing the lid securely.\n",
	    	this_player()->query_nonmet_name()  + " lies down in " + 
                POS(this_player()) + " coffin, closing the lid securely.\n",
                "" }));
	}
    }
    else
    {
        write("You can't seem to get the lid open!\n" +
            "Please leave a bug report\n");
    }
  
    return 1;
}

void
init()
{
    ::init();

    if (!COFFIN_OWNER(this_player()))
    {  
        return;
    }

    // move this_player() to his/her/its coffin, if appropriate
    if (QP(this_player(), VAMP_I_MOVING_TO_COFFIN))
    {
    	RP(this_player(), VAMP_I_MOVING_TO_COFFIN);
    
    	if (coffin_enter(this_player()))
    	{
	    AP(this_player(), LIVE_I_ENTERED_VAMP_STARTLOC, 1);
	    return;
    	}
    }
  
    if (!QP(this_player(), LIVE_O_LAST_ROOM) &&
	!QP(this_player(), LIVE_I_ENTERED_VAMP_STARTLOC) &&
	coffin_enter(this_player()))
    {
    	AP(this_player(), LIVE_I_ENTERED_VAMP_STARTLOC, 1);
    	return;
    }
  
    AP(this_player(), LIVE_I_ENTERED_VAMP_STARTLOC, 1);

    add_action(enter, "enter");
}
