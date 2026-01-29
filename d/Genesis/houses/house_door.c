
#include "./defs.h"
#include <composite.h>
#include <macros.h>

inherit "/std/door";

private string house_name;

public void set_house_name(string name)
{
	house_name = name;
}

public string query_house_name()
{
	return house_name;
}


public int is_owner()
{
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
  
    if (mappingp(details))
    {
        if (details[KEY_OWNER] == this_player()->query_real_name())
	    {
		    return 1;
        }
    }
    return 0;
}

public int can_enter_house()
{
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
  
    if (mappingp(details))
    {
        if (details[KEY_OWNER] == this_player()->query_real_name())
	    {
		    return 1;
        }
		object leader = this_player()->query_leader();
        if (leader && details[KEY_OWNER] == leader->query_real_name())
		{
		    return 1;
		}
        if (member_array(this_player()->query_real_name(), details[KEY_INVITED]) != -1)
		{
			return 1;
		}
  }
  if (this_player()->query_wiz_level())
  {
      write("You should be blocked, but as a wizard you have access.\n");
	  return 1;
  }
  return 0;
}

/*
 * Function name: open_door
 * Description:   Open the door.
 * Arguments:     arg - arguments given
 */

int
open_door(string arg)
{

    if (!can_enter_house())
    {
        write(check_call(fail_open[1]));
        return 1;
    }
    return ::open_door(arg);
}

int
pass_door(string arg)
{
    if (!this_player()->query_relaxed_from_combat())
    {
        write("You are still too excited from combat to enter.\n");
        return 1;
    }

    if (!can_enter_house())
    {
        write(check_call(fail_pass));
        return 1;
    }

    int result = ::pass_door(arg);

	if (is_owner() && environment(this_player()) != environment(this_object()))
    {
	    write("Welcome home.\n");
    }
    return result;
}

int do_show_invite(string arg)
{
    if (!is_owner())
    {
        return 0;
    }
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
    if (!mappingp(details))
    {
       write("Strange, the doorman doesn't know who is invited.\n");
       return 1;
    }
    if (!sizeof(details[KEY_INVITED]))
    {
        write("Nobody has been invited into your home.\n");
        return 1;
    }
    write("The doorman informs you that the following players are " +
      "allowed entry when the house is unlocked:\n");
    write(COMPOSITE_WORDS(details[KEY_INVITED]) + "\n");
    return 1;
}

int do_invite(string arg)
{
    if (!is_owner())
    {
        return 0;
    }
    notify_fail("Invite who?\n");
    
    if (!strlen(arg))
    {
        return 0;
    }
    
    object player = find_player(arg);
    if (!objectp(player))
    {
        return 0;
    }
    if (environment(player) != environment(this_object()) ||
        !CAN_SEE(this_player(), player))
    {
        write("The doorman needs to see the player in order to know who " +
        "you wish to let in.\n");
        return 1;
    }

    if (HOUSE_MANAGER->add_invitee(house_name, arg))
    {
        write("You notify the doorman to allow " +
          capitalize(arg) + " access into your home.\n");    
        return 1;
    }
    write("You have already given that player access to your house.\n");
    return 1;
}

int do_uninvite(string arg)
{
    if (!is_owner())
    {
        return 0;
    }
    notify_fail("Uninvite who?\n");
    
    if (!HOUSE_MANAGER->remove_invitee(house_name, arg))
    {
        return 0;
    }
    write("You notify the doorman to no longer allow " +
      capitalize(arg) + " into your home.\n");
    return 1;
}

void init()
{
    ::init();
    add_action(do_invite, "hinvite");
    add_action(do_uninvite, "huninvite");
    add_action(do_show_invite, "hinvited");
}