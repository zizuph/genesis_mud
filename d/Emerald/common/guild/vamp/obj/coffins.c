inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>

void
create_object()
{
    set_name(({ "coffin", "coffins" }));
    set_long("A plain, black coffin.\n");
}

varargs public mixed
long(string str, object for_obj)
{
    string who, desc, coven;

    setuid();
    seteuid(getuid());
  
    /* check to see if we're looking for a coffin description */
    if (strlen(str) && (sscanf(str, "%s's coffin", who) ||
        sscanf(str, "%s' coffin", who)))
    {
    	if ((MANAGER->query_coven(who) != LAIR_MANAGER->query_coven(file_name(this_object()))) ||
            !strlen(desc = COFFIN_MANAGER->query_coffin_desc(who)))
    	{
	    return "You examine the distinct coffins, but don't " +
	        "recognize the one you are looking for.\n" +
	        "Looking around, you realize it would be almost " +
	        "impossible to find a particular coffin among the " +
	        "other, virtually identical coffins.\n";
    	}
    
    	return desc + "\n";
    }
  
    return ::long(str, for_obj);
}

int
item_id(string str)
{
    string beans;
 
    if (sscanf(str, "%s's coffin", beans))
    {
	setuid();
	seteuid(getuid());

	if (!LAIR_MANAGER->query_coven(file_name(this_object())))
	{
	    return 0;
	}
 
        return 1;
    }
  
    return ::item_id(str);
}

static int
coffin_enter(object who)
{
    object coffin;
    int ret;
  
    if (!present(who, environment()))
    {
        return 0;
    }
  
    if (!(coffin = present(who->query_real_name() + "'s coffin")))
    {
    	setuid();
    	seteuid(getuid());
    
    	if (!(coffin = clone_object(VAMP_ROOM_DIR + "coffin")))
    	{
	    return 0;
    	}
    	else if (coffin->move(environment(), 1))
    	{
	    coffin->remove_object();
	    return 0;
    	}
    }
  
    coffin->set_owner(who);
    coffin->open();
  
    ret = who->move_living("M", coffin, 1, 1);
  
    coffin->close();
  
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
            tell_room(env, ({ this_player()->query_name()  + " lies down in " + POS(this_player()) + 
	    	" coffin, closing the lid securely.\n",
	    	this_player()->query_nonmet_name()  + " lies down in " + POS(this_player()) + 
	    	" coffin,  closing the lid securely.\n", "" }));
	}
    }
    else
    {
        write("You can't seem to get the lid open!\nPlease leave a bug report\n");
    }
  
    return 1;
}

void
init()
{
    ::init();

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
