/* This is the main Traveller guild room. Here you can join, leave and list.  */

#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include <ss_types.h>
#include <macros.h>

int
north()
{
     if (COUNCIL_MEMBER(this_player()->query_real_name()))
         return 0;

     if (this_player()->query_wiz_level())
         return 0;

     write("A strong forcefield blocks the way.\n");
     return 1;
}

void
create_traveller_room()
{
    string sign;

    set_short("Travellers Room");
    set_long("This is a large room, well lit by torches" +
	" and a huge fire against the far wall. A number of" +
	" chairs rest against the walls, and look very comfy." +
	" A large sign hangs above the fireplace.\n");

    add_exit("balcony", "south");
    add_exit("councilrm", "north", north);

    sign = "Here you can <join> or <leave guild> the Travellers guild.  " +
           "You may also <list> to see what guilds you are already " +
           "a part of.  Members can receive a <badge> to allow others " +
           "to join.\n";

    add_item("sign", sign);

    add_cmd_item("sign", "read", sign);
}


int
join(string str)
{
    object sh, *badges;
    mixed why;

    if (strlen(str))
    {
        return 0;
    }

    if (!this_player()->query_wiz_level() &&
        !sizeof(badges = filter(deep_inventory(this_player()), 
        &wildmatch(TRAVELLERS_BADGE + "*") @ file_name)))
    {
        write("You have not been authorized, and cannot join.\n");
	return 1;
    }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(TRAVELLERS_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
	switch (sh->add_race_shadow(this_player()))
	{
	    case 1:
	        /* We have successfully shadowed the player, so we're set */

		this_player()->clear_guild_stat(SS_RACE);
	
        	badges[0]->remove_object();
	
		write("You are now a Traveller.\n");
        	write("You receive the Traveller walking stick, which "+
        	      "magically adjusts to fit you.\n");
        	say(QCTNAME(this_player()) + " joins the Travellers Guild.\n");
	
		log_file("travellers", 
                    capitalize(this_player()->query_real_name()) +
                    " joined " + ctime(time()) + "\n");

		return 1;
    
	    case -4:
	        /* The player has a race guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
		write("Your other guilds don't want you in this one!\n");
		break;
    
	    default:
	        /* Some error in shadowing */
		write("An error has prevented you from joining.\n");
		break;
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
leave(string str)
{
    if (str != "guild")
    {
	notify_fail("Leave what? The guild??\n");
        return 0;
    }
    
    if (!IS_MEMBER(this_player()))
    {
        write("You aren't a member!\n");
        return 1;
    }

    this_player()->leave_travellers();
    return 1;
}

int
list(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    str = this_player()->list_major_guilds();
    if (str)
        write("You are a member of the following guilds.\n" + str);
    else
        write("You are not a member of any important guilds.\n");
    
    return 1;
}

int
badge(string str)
{
    if (IS_MEMBER(this_player()))
    {
	clone_object(TRAVELLERS_OBJ_DIR + "badge")->move(this_player(), 1);
	write("You receive a badge of authorization.\n");
	return 1;
    }

    write("You are not a member.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(join, "join");
    add_action(leave, "leave");
    add_action(list, "list");
    add_action(badge, "badge");
}
