/*
 * Council Chambers for the Elemental Worshippers of Calia
 *
 * Created by Petros, April 2014
 * Added Seeker code - Jaacar, July 2016
 */
#pragma strict_types
#pragma save_binary

#include <files.h>
#include <stdproperties.h>
#include <composite.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define WOR_OBJECTS "/d/Calia/worshippers/objects/"

/*
 * Function:    my_time
 * Description: Returns the time format used for logs.
 */
public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public void
load_board()
{
    clone_object(WOR_OBJECTS + "council_board")->move(THIS);
}

public void
load_book()
{
    clone_object(ELEMENTALIST_OBJS + "council_log_book")->move(THIS);
}

public int
query_prevent_snoop()
{
    return 1;
}

void 
create_temple_room()
{
    set_short("Elemental Worshippers Council Chambers");
    set_long("You are standing in the council chambers of the "+
        "Elemental Worshippers of Calia. This chamber is lit "+
        "by glowing rocks set into the walls. There is a large "+
        "banner hanging on the western wall, and a scroll hanging "+
        "below it. Beside the scroll you notice a tasklist. In one "+
        "corner you see a small table.\n");

    add_item(({"rocks","glowing rocks"}),"The rocks are all different "+
        "sizes, and seem to be magical in nature. They must be a gift "+
        "from the Elementals to light this chamber.\n");
    add_item(({"table","small table"}),"In the corner of the room "+
        "there is a small wooden table. On top of the table is "+
        "a brown book which the council records its actions in "+
        "and a transparent scroll that you can <borrow> in order "+
        "to review the rack logs.\n");
    add_item("scroll","There is writing on the scroll that you can read.\n");

    add_item("banner", "@@describe_banner@@");
    add_item("tasklist", "@@describe_tasklist@@");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(ELEMENTALIST_TEMPLE + "ew_lounge", "down");
    add_exit(ELEMENTALIST_TEMPLE + "wc_post", "west");
    add_exit(ELEMENTALIST_TEMPLE + "joint", "east");
   
    load_book();
    load_board();   

    setuid();
    seteuid(getuid());
}

public string
describe_banner()
{
    return "On the banner you see:\n\n"+
        "Council Management Commands:\n" +
        "  council               - check Council members.\n" +
        "  addmem <player>       - add <player> to the Worshipper Council.\n" + 
        "  remmem <player>       - remove <player> from the Worshipper Council.\n"+
        "  focus                 - check the current Elementalist Focus.\n"+
//        "  setfocus <player>     - set <player> as Focus of the Elements.\n"+
//        "  remfocus <player>     - remove <player> as Focus of the Elements.\n"+
        "  seekers               - check the current Seekers.\n"+
        "  worshippers           - check the current Worshippers.\n"+
        "\n"+
        "Member Punishment Commands:\n" +
        "  trainban <player>     - ban <player> from training.\n" +
        "  prayerban <player>    - ban <player> from using prayers.\n"+
        "  resourceban <player>  - ban <player> from using Temple resources.\n"+
        "  templeban <player>    - ban <player> from entering the Temple.\n"+
        "  expel <player>        - expel <player> from the Worshippers guild.\n" +
        "  rempunish <player>    - remove all punishments from <player>.\n"+
        "  punishments <player>  - check <player>'s punishments.\n"+
        "  allowswitch <player>  - allow <player> to switch Elemental worshipped.\n"+
        "\n" +
        "Membership Management Commands:\n" +
        "  anote <player> <note> - add <note> about <player>.\n" +
        "                          (NOTE: This will replace any previous note.)\n"+
        "  vnote <player>        - view note about <player> if there is one.\n"+
        "  task <player> <#>     - Allow <player> to start task <#>.\n"+
        "                          Current Tasks:\n"+
        "                          1 - Introduction (Tahla)\n"+
        "                          2 - Faith (Tiashe)\n"+
        "                          3 - Family (Arial)\n"+
        "                          4 - Secrecy (Jardeth)\n"+
        "  reset1 <player>       - Reset <player>'s task 1 status so they can\n"+
        "                          re-answer.\n"+
        "  reset2 <player>       - Reset <player>'s task 2 status so they can\n"+
        "                          re-answer.\n"+
        "  reset3 <player>       - Reset <player>'s task 3 status so they can\n"+
        "                          re-answer.\n"+
        "  reset4 <player>       - Reset <player>'s task 4 status so they can\n"+
        "                          re-answer.\n"+
        "  allow <player>        - This will allow <player> to join. Once they have\n"+
        "                          done this, they need only 'worship <diety>' to\n"+
        "                          enter their service. NOTE: This command can also\n"+
        "                          be done in the Chapel itself.\n"+
        "\n"+
        "Task Answer Review Commands:\n"+
        "  view <player> <#> <#> - View <player>'s answer to task <#>, question <#>\n"+
        "                          ie. 'view jaacar 2 1' would view the answer\n"+
        "                          Jaacar gave for task 2, question 1.\n"+
        "                          Current Viewable Tasks and Number of Answers:\n"+
        "                          Task 2 has 8 answers.\n"+
        "                          Task 3 has 2 answers.\n"+
        "\n";
}

public string
describe_tasklist()
{
    return "On the tasklist you see:\n\n"+
        "Task One (Introduction):\n"+
        "The Seeker should be instructed to go see Tahla (in the Library).\n"+
        "They will be asked the following questions (answers in brackets).\n"+
        "What is the name of the Lord of the Flames? (Lord Pyros or Pyros)\n"+
        "What is the name of the Lady of the Winds? (Lady Aeria or Aeria)\n"+
        "What is the name of the Lord of the Seas? (Lord Diabrecho or Diabrecho)\n"+
        "What is the name of the Lady of the Earth? (Lady Gu or Gu)\n"+
        "What is the name of the Ruler of Souls and Shadows? (Psuchae)\n"+
        "What are the Elementals greatest doing? (Creation, World, Genesis, Everything, Life)\n"+
        "\n"+
        "Task Two (Faith):\n"+
        "The Seeker should be instructed to go see Tiashe (in the Refectory).\n"+
        "They will be asked the following questions.\n"+
        "What does the Lord of the Flames and his Element of Fire define for you?\n"+
        "What does the Lady of the Winds and her Element of Air define for you?\n"+
        "What does the Lord of the Seas and his Element of Water define for you?\n"+
        "What does the Lady of the Earth and her Element of Earth define for you?\n"+
        "What does Psuchae and the Element of Spirit define for you?\n"+
        "Name me the places in the Realms where you personally, clearly perceive\n"+
        "  the Five, and why this is significant for you.\n"+
        "Explain which of the Five you would dedicate yourself to, should you be\n"+
        "  accepted into the Circle, and why that is so.\n"+
        "What do you feel the Five want from us?\n"+
        "\n"+
        "Task Three (Family):\n"+
        "The Seeker should be instructed to go see Arial (in Earths Beholden).\n"+
        "They will be asked the following questions.\n"+
        "Define family for me and what it means to you.\n"+
        "Why do we ask for this definition of family and why is it so vital?\n"+
        "\n"+
        "Task Four (Secrecy):\n"+
        "The Seeker should be instructed to go see Jardeth (in the Herb Garden).\n"+
        "They will be asked to follow a series of clues provided by pressing\n"+
        "buttons in certain rooms, ultimately seeking a word written in the\n"+
        "statue chamber.\n"+
        "Tell me the answer I am seeking. (Secrecy)\n"+
        "\n";
}

public int
can_use_council_commands()
{
    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_ew_council(this_player(), 1))
    {
        return 1;
    }
    return 0;
}

public int
see_council(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    string message = "";

    string * council = GUILD_MANAGER->query_ew_council();
    if (sizeof(council) == 0)
    {
        message = "The Elemental Worshippers Council does not currently have any members.\n";
    }
    else if (sizeof(council) == 1) 
    {
        message = "The Elemental Worshippers Council currently has the following member: " 
            + capitalize(council[0]) + ".\n";
    }
    else
    {
        message = "The Elemental Worshippers Council currently has the following members: ";
        message += (COMPOSITE_WORDS(map(council, capitalize)) + ".\n"); 
    }
        
    write(message);
    return 1;
}

public int
add_council_member(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to add to the Elemental Worshippers Council?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_ew_council(str, 1))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers "
              + "Council!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (!GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " isn't a member of the Elemental Worshippers and "
              + "cannot become a Council member here.\n");
        return 1;
    }

    GUILD_MANAGER->set_ew_council(str, 1);
    string log_message = capitalize(str)
        + " has been added to the Elemental Worshippers Council "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
remove_council_member(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to remove from the Elemental Worshippers Council?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_ew_council(str, 0))
    {
        if (GUILD_MANAGER->query_is_ew_council(str, 1))
        {
            write(capitalize(str) + " is technically on the Elemental Worshippers "
                  + "Council, but not someone can be removed because they aren't part "
                  + "of the Elemental Worshippers guild.\n");
        }
        else
        {
            write(capitalize(str) + " is not a member of the Elemental Worshippers "
                  + "Council!\n");
        }
        return 1;
    }

    GUILD_MANAGER->set_ew_council(str, 0);
    string log_message = capitalize(str)
        + " has been removed from the Elemental Worshippers Council "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

int
record_stop_train(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to prevent from training in the guild hall?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_cleric(str))
    {
        if (!GUILD_MANAGER->query_is_worshipper(str))
        {
            if (!GUILD_MANAGER->query_is_seeker(str))
            {
                write(capitalize(str) + " is not a member of the Elemental Circle!\n");
                return 1;
            }
        }
    }

    if (GUILD_MANAGER->query_is_ew_council(str, 0)
        && !this_player()->query_wiz_level())
    {
        write(capitalize(str) + " is a member of the Elemental Worshippers Council. "
              + "You will not be able to ban their use of the training facilities.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_punish_train_banned(str))
    {
        write(capitalize(str) + " is already banned from using the guild's training "
              + "facilities!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_punish_train_banned(str, 1);
    object player = find_player(str);
    if (objectp(player))
    {
        // They are currently in the game.
        player->catch_tell("You have been banned by the Elemental Council "
                           + "from using the guild's training facilities.\n");
    }
    string log_message = capitalize(str)
        + " has been banned from using the guild's training facilities "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
record_spell_banned(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to ban from using their prayers?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_cleric(str))
    {
        if (!GUILD_MANAGER->query_is_worshipper(str))
        {
            if (!GUILD_MANAGER->query_is_seeker(str))
            {
                write(capitalize(str) + " is not a member of the Elemental Circle!\n");
                return 1;
            }
        }
    }

    if (GUILD_MANAGER->query_is_ew_council(str, 0)
        && !this_player()->query_wiz_level())
    {
        write(capitalize(str) + " is a member of the Elemental Worshippers Council. "
              + "You will not be able to ban their use of their prayers.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_punish_spell_banned(str))
    {
        write(capitalize(str) + " is already banned from using the gifts of the "
              + "Elementals through prayers!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_punish_spell_banned(str, 1);
    object player = find_player(str);
    if (objectp(player))
    {
        // They are currently in the game.
        player->catch_tell("You have been banned by the Elemental Council "
                           + "from using the gifts of the Elementals through "
                           + "prayers.\n");
    }
    string log_message = capitalize(str)
        + " has been banned from using the guild's prayers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
record_temple_banned(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to ban from entering the Temple?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());

    if (GUILD_MANAGER->query_is_ew_council(str, 0)
        && !this_player()->query_wiz_level())
    {
        write(capitalize(str) + " is a member of the Elemental Worshippers Council. "
              + "You will not be able to ban them from the Temple.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_punish_temple_banned(str))
    {
        write(capitalize(str) + " is already banned from entering the Temple!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_punish_temple_banned(str, 1);
    object player = find_player(str);
    if (objectp(player))
    {
        // They are currently in the game.
        player->catch_tell("You have been banned by the Elemental Council "
                           + "from entering the Elemental Temple.\n");
        string loc = file_name(environment(player));
        string * path = explode(loc, "/");
        if ((sizeof(path) >=3) && (path[2] == "Calia") &&
        	(path[5] == "temple"))
        	player->move(player->query_def_start());
    }
    string log_message = capitalize(str)
        + " has been banned from entering the Elemental Temple "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
record_resource_banned(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to ban from using Temple resources?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_cleric(str))
    {
        if (!GUILD_MANAGER->query_is_worshipper(str))
        {
            if (!GUILD_MANAGER->query_is_seeker(str))
            {
                write(capitalize(str) + " is not a member of the Elemental Circle!\n");
                return 1;
            }
        }
    }

    if (GUILD_MANAGER->query_is_ew_council(str, 0)
        && !this_player()->query_wiz_level())
    {
        write(capitalize(str) + " is a member of the Elemental Worshippers Council. "
              + "You will not be able to ban them using Temple resources.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_punish_resource_banned(str))
    {
        write(capitalize(str) + " is already banned from using the Temple resources!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_punish_resource_banned(str, 1);
    object player = find_player(str);
    if (objectp(player))
    {
        // They are currently in the game.
        player->catch_tell("You have been banned by the Elemental Council "
                           + "from using the Elemental Temple resources.\n");        
    }
    string log_message = capitalize(str)
        + " has been banned from using the Elemental Temple resources "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
record_player_expelled(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to expel from the guild?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_worshipper(str) && !GUILD_MANAGER->query_is_seeker(str))
    {
        write(capitalize(str) + " is not a member of the Elemental Seekers or Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_ew_council(str, 0)
        && !this_player()->query_wiz_level())
    {
        write(capitalize(str) + " is a member of the Elemental Worshippers Council. "
              + "You will not be able to expel them from the guild.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " has already been expelled from the guild.\n");
        return 1;
    }
    
    GUILD_MANAGER->set_guild_expelled(str, 1);
    
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        GUILD_MANAGER->remove_worshipper(str);
    }
    
    if (GUILD_MANAGER->query_is_seeker(str))
    {
        GUILD_MANAGER->remove_seeker(str);
    }
    
    object player = find_player(str);
    if (objectp(player))
    {
        // They are currently in the game.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "EXPELLED"));
        if (GUILD_MANAGER->query_is_worshipper(str))
        	player->catch_tell(sprintf("\n%=-75s\n\n", "You have been expelled from the Elemental Worshippers "
                + "guild by the Worshippers Council."));
        else if (GUILD_MANAGER->query_is_seeker(str))
        	player->catch_tell(sprintf("\n%=-75s\n\n", "You have been expelled from the Elemental Seekers "
                + "guild by the Worshippers Council."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_guild(str);
    }
    string log_message = capitalize(str)
        + " has been expelled from the guild "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
record_remove_punishments(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to remove punishments for?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_worshipper(str) && !GUILD_MANAGER->query_is_seeker(str))
    {
    	if (GUILD_MANAGER->query_is_guild_expelled(str))
	    {
	        GUILD_MANAGER->set_guild_expelled(str, 0);
	        write("You remove the guild expulsion on " + capitalize(str) + ".\n");
	        string log_message = capitalize(str)
	            + "'s guild expulsion has been removed "
	            + "by " + capitalize(this_player()->query_real_name())
	            + ".\n";
	        send_debug_message("ew_council", log_message);
	        COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
	        object player = find_player(str);
		    if (objectp(player))
		    {
		        player->catch_tell("The Worshipper Council has accepted your atonement.\n");
		    }
		    return 1;
	    }
    	
        write(capitalize(str) + " is not a member of the Elemental Seekers or Worshippers and "+
            "has no punishments to remove!\n");
        return 1;
    }

    int bPunishmentRemoved = 0;
    if (GUILD_MANAGER->query_is_punish_resource_banned(str))
    {
        GUILD_MANAGER->set_punish_resource_banned(str, 0);
        write("You remove the resource ban on " + capitalize(str) + ".\n");
        bPunishmentRemoved = 1;
        string log_message = capitalize(str)
            + "'s resource ban has been removed "
            + "by " + capitalize(this_player()->query_real_name())
            + ".\n";
        send_debug_message("ew_council", log_message);
        COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    }
    if (GUILD_MANAGER->query_is_punish_train_banned(str))
    {
        GUILD_MANAGER->set_punish_train_banned(str, 0);
        write("You remove the training ban on " + capitalize(str) + ".\n");
        bPunishmentRemoved = 1;
        string log_message = capitalize(str)
            + "'s training ban has been removed "
            + "by " + capitalize(this_player()->query_real_name())
            + ".\n";
        send_debug_message("ew_council", log_message);
        COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    }
    if (GUILD_MANAGER->query_is_punish_spell_banned(str))
    {
        GUILD_MANAGER->set_punish_spell_banned(str, 0);
        write("You remove the prayer ban on " + capitalize(str) + ".\n");
        bPunishmentRemoved = 1;
        string log_message = capitalize(str)
            + "'s prayer ban has been removed "
            + "by " + capitalize(this_player()->query_real_name())
            + ".\n";
        send_debug_message("ew_council", log_message);
        COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    }
    if (GUILD_MANAGER->query_is_punish_temple_banned(str))
    {
        GUILD_MANAGER->set_punish_temple_banned(str, 0);
        write("You remove the Temple ban on " + capitalize(str) + ".\n");
        bPunishmentRemoved = 1;
        string log_message = capitalize(str)
            + "'s Temple ban has been removed "
            + "by " + capitalize(this_player()->query_real_name())
            + ".\n";
        send_debug_message("ew_council", log_message);
        COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    }
    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        GUILD_MANAGER->set_guild_expelled(str, 0);
        write("You remove the guild expulsion on " + capitalize(str) + ".\n");
        bPunishmentRemoved = 1;
        string log_message = capitalize(str)
            + "'s guild expulsion has been removed "
            + "by " + capitalize(this_player()->query_real_name())
            + ".\n";
        send_debug_message("ew_council", log_message);
        COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    }
    if (!bPunishmentRemoved)
    {
        write(capitalize(str) + " has no punishments to remove.\n");
        return 1;
    }

    object player = find_player(str);
    if (objectp(player))
    {
        player->catch_tell("The Worshipper Council has removed all of your "
                           + "guild punishments.\n");
    }
    write("Ok.\n");    
    return 1;

}

public int
check_punishments(string str)
{
	if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to check punishments for?\n");
        return 0;
    }

    str = lower_case(str);
    int bPunishments = 0;

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_punish_resource_banned(str))
    {
        write(capitalize(str) + " has been banned from using Temple resources.\n");
        bPunishments = 1;
    }
    
    if (GUILD_MANAGER->query_is_punish_train_banned(str))
    {
        write(capitalize(str) + " has been banned from training.\n");
        bPunishments = 1;
    }
        
    if (GUILD_MANAGER->query_is_punish_spell_banned(str))
    {
        write(capitalize(str) + " has been banned from using prayers.\n");
        bPunishments = 1;
    }

    if (GUILD_MANAGER->query_is_punish_temple_banned(str))
    {
        write(capitalize(str) + " has been banned from the Temple.\n");
        bPunishments = 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " has been expelled from the Elementalists.\n");
        bPunishments = 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has betrayed the Elementals.\n");
        bPunishments = 1;
    }
    
    if (!bPunishments)
    {
    	write(capitalize(str) + " has no punishments.\n");
    }

	return 1;
}

public int
do_allowswitch(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to allow to switch Elements?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (!GUILD_MANAGER->query_is_worshipper(str))
    {
    	write(capitalize(str) + " is not a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (!GUILD_MANAGER->query_has_changed_element(str))
    {
    	write(capitalize(str) + " has not changed Elements already.\n");
        return 1;
    }
    
    string log_message = capitalize(str)
            + " has been permitted to change Elements "
            + "by " + capitalize(this_player()->query_real_name())
            + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    
    GUILD_MANAGER->set_has_changed_element(str,0);
    write("Ok.\n");    
    return 1;

}

public int
read_item(string str)
{
    setuid();
    seteuid(getuid());

    if (!strlen(str))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    str = lower_case(str);
    switch (str)
    {
    case "scroll":
        tail(CONSTRUCTION_LOG);
        break;
    case "banner":
        write(describe_banner());
        break;
    default:
        notify_fail("Read what?\n");
        return 0;
    }

    return 1;
}

/*
 * Function: enter_inv
 * Description: block unwanted people from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from && !living(ob) && IS_PLAYER_OBJECT(from))
    {
        // Player is attempting to drop something. We prevent this
        from->catch_msg("Something is preventing you from dropping "
                        + "this item.\n");
        ob->move(from);
        return;
    }

    // Otherwise, allow non-living objects to enter this room
    if (!living(ob)) 
    {
        return;
    }

    // Only Council Members (defined in Guild Manager) are allowed
    // to enter this chamber.
    if (!GUILD_MANAGER->query_is_ew_council(ob, 1))
    {
        ob->move(from);
        ob->catch_msg("You're not coming into the Worshippers Council " +
            "chambers without special permission!\n");
        return;
    }
}

/*
 * Function:    no_drop
 * Description: Prevent members from using the Council Chambers
 *              as their own personal storage room.
 */
public int
no_drop(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    write("You cannot drop things in this room.\n");
    return 1;
}

public int
do_allow(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to allow to join the Elemental Worshippers?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_cleric(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Clerics and cannot "
              + "join the Elemental Worshippers!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has already betrayed the Elementals before and "
              + "is not allowed to join ever again.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " was expelled from the Elementals before. To "
              + "allow them to join, please <rempunish> them first.\n");
        return 1;
    }

/*    
    if (!GUILD_MANAGER->query_is_seeker(str))
    {
        write(capitalize(str) + " is not a member of the Elemental Seekers and cannot "
              + "join the Elemental Worshippers!\n");
        return 1;
    }
*/
    
    GUILD_MANAGER->set_can_join_worshippers(str, 1);
    string log_message = capitalize(str)
        + " has been given permission to join the Elemental Worshippers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
do_task(string str)
{
	string player, log_message;
	int task;
	
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to allow to do a task?\n");
        return 0;
    }
    if (sscanf(str, "%s %i", player, task) != 2)
    {
    	notify_fail("Who would you like to allow to do a task? task <player> <task#>\n");
    	return 0;
    }
    
    if (sscanf(str, "%s %i", player, task) == 2)
    {
    	player = lower_case(player);
    	setuid();
	    seteuid(getuid());
	    if (GUILD_MANAGER->query_is_worshipper(player))
	    {
	        write(capitalize(player) + " is already a member of the Elemental Worshippers!\n");
	        return 1;
	    }
	
	    if (GUILD_MANAGER->query_is_cleric(player))
	    {
	        write(capitalize(player) + " is already a member of the Elemental Clerics!\n");
	        return 1;
	    }
	    
	    if (!(GUILD_MANAGER->query_is_seeker(player)))
	    {
	        write(capitalize(player) + " is not a member of the Elemental Seekers!\n");
	        return 1;
	    }
	
	    if (!SECURITY->exist_player(player))
	    {
	        write(capitalize(player) + " doesn't appear to have ever walked the Realms.\n");
	        return 1;
	    }
	
	    if (GUILD_MANAGER->query_is_guild_betrayed(player))
	    {
	        write(capitalize(player) + " has already betrayed the Elementals before and "
	              + "is not allowed to join ever again.\n");
	        return 1;
	    }
	
	    if (GUILD_MANAGER->query_is_guild_expelled(player))
	    {
	        write(capitalize(player) + " was expelled from the Elementals before. To "
	              + "allow them to join, please <rempunish> them first.\n");
	        return 1;
	    }
	    
    	switch(task)
    	{
    		case 1:
    			if (GUILD_MANAGER->query_can_do_wor_task_four(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 4!\n");
			        return 1;
			    }
    
			    if (GUILD_MANAGER->query_can_do_wor_task_three(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 3!\n");
			        return 1;
			    }
			    
			    if (GUILD_MANAGER->query_can_do_wor_task_two(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 2!\n");
			        return 1;
			    }
			    
			    if (GUILD_MANAGER->query_can_do_wor_task_one(player))
			    {
			        write(capitalize(player) + " has already been assigned task 1!\n");
			        return 1;
			    }
    
			    GUILD_MANAGER->set_can_do_wor_task_one(player, 1);
			    log_message = capitalize(player)
			        + " has been given permission to do task 1 for the Elemental Worshippers "
			        + "by " + capitalize(this_player()->query_real_name())
			        + ".\n";
			    send_debug_message("ew_council", log_message);
			    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
			    write("Ok.\n");
			    return 1;
			    break;
			case 2:
				if (GUILD_MANAGER->query_can_do_wor_task_four(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 4!\n");
			        return 1;
			    }
			    
			    if (GUILD_MANAGER->query_can_do_wor_task_three(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 3!\n");
			        return 1;
			    }
			    
			    if (GUILD_MANAGER->query_can_do_wor_task_two(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 2!\n");
			        return 1;
			    }
			    
			    // Five questions in task one so it would need to be set to 7 (1 + 6 correct answers)
			    if ((GUILD_MANAGER->query_can_do_wor_task_one(player)) != 7)
			    {
			        write(capitalize(player) + " has not completed task 1 yet!\n");
			        return 1;
			    }
			    
			    GUILD_MANAGER->set_can_do_wor_task_two(player, 1);
			    log_message = capitalize(player)
			        + " has been given permission to do task 2 for the Elemental Worshippers "
			        + "by " + capitalize(this_player()->query_real_name())
			        + ".\n";
			    send_debug_message("ew_council", log_message);
			    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
			    write("Ok.\n");
			    return 1;
			    break;
			case 3:
				if (GUILD_MANAGER->query_can_do_wor_task_four(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 4!\n");
			        return 1;
			    }
			    
			    if (GUILD_MANAGER->query_can_do_wor_task_three(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 3!\n");
			        return 1;
			    }
			    
			    // Five questions in task one so it would need to be set to 7 (1 + 6 correct answers)
			    if ((GUILD_MANAGER->query_can_do_wor_task_one(player)) != 7)
			    {
			        write(capitalize(player) + " has not completed task 1 yet!\n");
			        return 1;
			    }
			    
			    // Seven questions in task two so it would need to be set to 9 (1 + 8 correct answers)
			    if ((GUILD_MANAGER->query_can_do_wor_task_two(player)) != 9)
			    {
			        write(capitalize(player) + " has not completed task 2 yet!\n");
			        return 1;
			    }
			    
			    GUILD_MANAGER->set_can_do_wor_task_three(player, 1);
			    log_message = capitalize(player)
			        + " has been given permission to do task 3 for the Elemental Worshippers "
			        + "by " + capitalize(this_player()->query_real_name())
			        + ".\n";
			    send_debug_message("ew_council", log_message);
			    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
			    write("Ok.\n");
			    return 1;
			    break;
			case 4:
				if (GUILD_MANAGER->query_can_do_wor_task_four(player))
			    {
			    	write(capitalize(player) + " has already been assigned task 4!\n");
			        return 1;
			    }
			    
			    // Five questions in task one so it would need to be set to 7 (1 + 6 correct answers)
			    if ((GUILD_MANAGER->query_can_do_wor_task_one(player)) != 7)
			    {
			        write(capitalize(player) + " has not completed task 1 yet!\n");
			        return 1;
			    }
			    
			    // Seven questions in task two so it would need to be set to 9 (1 + 8 correct answers)
			    if ((GUILD_MANAGER->query_can_do_wor_task_two(player)) != 9)
			    {
			        write(capitalize(player) + " has not completed task 2 yet!\n");
			        return 1;
			    }
			    
			    // One question in task three so it would need to be set to 3 (1 + 2 correct answers)
			    if ((GUILD_MANAGER->query_can_do_wor_task_three(player)) != 3)
			    {
			        write(capitalize(player) + " has not completed task 3 yet!\n");
			        return 1;
			    }
			    
			    GUILD_MANAGER->set_can_do_wor_task_four(player, 1);
			    log_message = capitalize(player)
			        + " has been given permission to do task 4 for the Elemental Worshippers "
			        + "by " + capitalize(this_player()->query_real_name())
			        + ".\n";
			    send_debug_message("ew_council", log_message);
			    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
			    write("Ok.\n");
			    return 1;
			    break;
			default:
				notify_fail("Who would you like to allow to do a task? task <player> <task#>\n");
    			return 0;
    			break;
    	}
    }
}

public int
do_resetone(string str)
{
	if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to reset and allow to do task 1 again?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_cleric(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Clerics!\n");
        return 1;
    }
    
    if (!(GUILD_MANAGER->query_is_seeker(str)))
    {
        write(capitalize(str) + " is not a member of the Elemental Seekers!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has already betrayed the Elementals before and "
              + "is not allowed to join ever again.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " was expelled from the Elementals before. To "
              + "allow them to join, please <rempunish> them first.\n");
        return 1;
    }
    
    if (GUILD_MANAGER->query_can_do_wor_task_two(str))
    {
    	write(capitalize(str) + " has already been assigned task 2!\n");
        return 1;
    }
    
    if (GUILD_MANAGER->query_can_do_wor_task_three(str))
    {
    	write(capitalize(str) + " has already been assigned task 3!\n");
        return 1;
    }
    
    if (GUILD_MANAGER->query_can_do_wor_task_four(str))
    {
    	write(capitalize(str) + " has already been assigned task 4!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_can_do_wor_task_one(str, 1);

    string log_message = capitalize(str)
        + " has been given permission to re-answer task 1 for the Elemental Worshippers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
do_resettwo(string str)
{
	if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to reset and allow to do task 2 again?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_cleric(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Clerics!\n");
        return 1;
    }
    
    if (!(GUILD_MANAGER->query_is_seeker(str)))
    {
        write(capitalize(str) + " is not a member of the Elemental Seekers!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has already betrayed the Elementals before and "
              + "is not allowed to join ever again.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " was expelled from the Elementals before. To "
              + "allow them to join, please <rempunish> them first.\n");
        return 1;
    }
    
    if (GUILD_MANAGER->query_can_do_wor_task_three(str))
    {
    	write(capitalize(str) + " has already been assigned task 3!\n");
        return 1;
    }
    
    if (GUILD_MANAGER->query_can_do_wor_task_four(str))
    {
    	write(capitalize(str) + " has already been assigned task 4!\n");
        return 1;
    }
    
    // 5 questions in task 1 so it would need to be set to 7 (1 + 6 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_one(str)) != 7)
    {
        write(capitalize(str) + " has not completed task 1 yet!\n");
        return 1;
    }
    
    // 7 questions in task 2 so it would need to be set to 9 (1 + 8 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_two(str)) != 9)
    {
        write(capitalize(str) + " has not completed task 2 yet!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_can_do_wor_task_two(str, 1);
    GUILD_MANAGER->set_task_two_answer_one(str, 0);
    GUILD_MANAGER->set_task_two_answer_two(str, 0);
    GUILD_MANAGER->set_task_two_answer_three(str, 0);
    GUILD_MANAGER->set_task_two_answer_four(str, 0);
    GUILD_MANAGER->set_task_two_answer_five(str, 0);
    GUILD_MANAGER->set_task_two_answer_six(str, 0);
    GUILD_MANAGER->set_task_two_answer_seven(str, 0);
    GUILD_MANAGER->set_task_two_answer_eight(str, 0);
    string log_message = capitalize(str)
        + " has been given permission to re-answer task 2 for the Elemental Worshippers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
do_resetthree(string str)
{
	if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to reset and allow to do task 3 again?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_cleric(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Clerics!\n");
        return 1;
    }
    
    if (!(GUILD_MANAGER->query_is_seeker(str)))
    {
        write(capitalize(str) + " is not a member of the Elemental Seekers!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has already betrayed the Elementals before and "
              + "is not allowed to join ever again.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " was expelled from the Elementals before. To "
              + "allow them to join, please <rempunish> them first.\n");
        return 1;
    }
    
    if (GUILD_MANAGER->query_can_do_wor_task_four(str))
    {
    	write(capitalize(str) + " has already been assigned task 4!\n");
        return 1;
    }    
    
    // 5 questions in task 1 so it would need to be set to 7 (1 + 6 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_one(str)) != 7)
    {
        write(capitalize(str) + " has not completed task 1 yet!\n");
        return 1;
    }
    
    // 7 questions in task 2 so it would need to be set to 9 (1 + 8 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_two(str)) != 9)
    {
        write(capitalize(str) + " has not completed task 2 yet!\n");
        return 1;
    }
       
    GUILD_MANAGER->set_can_do_wor_task_three(str, 1);
    GUILD_MANAGER->set_task_three_answer_one(str, 0);
    GUILD_MANAGER->set_task_three_answer_two(str, 0);
    string log_message = capitalize(str)
        + " has been given permission to re-answer task 3 for the Elemental Worshippers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
do_resetfour(string str)
{
	if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to reset and allow to do task 4 again?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_cleric(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Clerics!\n");
        return 1;
    }
    
    if (!(GUILD_MANAGER->query_is_seeker(str)))
    {
        write(capitalize(str) + " is not a member of the Elemental Seekers!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has already betrayed the Elementals before and "
              + "is not allowed to join ever again.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " was expelled from the Elementals before. To "
              + "allow them to join, please <rempunish> them first.\n");
        return 1;
    }    
    
    // 5 questions in task 1 so it would need to be set to 7 (1 + 6 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_one(str)) != 7)
    {
        write(capitalize(str) + " has not completed task 1 yet!\n");
        return 1;
    }
    
    // 7 questions in task 2 so it would need to be set to 9 (1 + 8 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_two(str)) != 9)
    {
        write(capitalize(str) + " has not completed task 2 yet!\n");
        return 1;
    }

    // 2 questions in task 3 so it would need to be set to 3 (1 + 2 correct answers)
    if ((GUILD_MANAGER->query_can_do_wor_task_three(str)) != 3)
    {
        write(capitalize(str) + " has not completed task 3 yet!\n");
        return 1;
    }
           
    GUILD_MANAGER->set_can_do_wor_task_four(str, 1);
    string log_message = capitalize(str)
        + " has been given permission to re-answer task 4 for the Elemental Worshippers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public int
do_view(string str)
{
	string player;
	int task, answer;
	
	if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who's task answers would you like to see?\n");
        return 0;
    }
    
    if (sscanf(str, "%s %i %i", player, task, answer) != 3)
    {
    	notify_fail("Who's task answers would you like to see? view <player> <task#> <answer#>\n");
    	return 0;
    }
    
    if (sscanf(str, "%s %i %i", player, task, answer) == 3)
    {
    	switch(task)
    	{
    		case 1:
    			write("There are no answers in task 1 to review.\n");
    			return 1;
    			break;
    		case 2:
    			switch(answer)
    			{
    				case 1:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 1:\n"+
    					    "What does the Lord of the Flames and his Element of Fire "+
    					    "define for you?\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_one(player)+"\n");
    					return 1;
    					break;
    				case 2:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 2:\n"+
    					    "What does the Lady of the Winds and her Element of Air "+
    					    "define for you?\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_two(player)+"\n");
    					return 1;
    					break;
    				case 3:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 3:\n"+
    					    "What does the Lord of the Seas and his Element of Water "+
    					    "define for you?\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_three(player)+"\n");
    					return 1;
    					break;
    				case 4:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 4:\n"+
    					    "What does the Lady of the Earth and her Element of Earth "+
    					    "define for you?\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_four(player)+"\n");
    					return 1;
    					break;
    				case 5:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 5:\n"+
    					    "What does Psuchae and the Element of Spirit "+
    					    "define for you?\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_five(player)+"\n");
    					return 1;
    					break;
    				case 6:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 6:\n"+
    					    "Name me the places in the Realms where you personally, "+
    					    "clearly perceive the Five, and why this is significant "+
    					    "for you.\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_six(player)+"\n");
    					return 1;
    					break;
    				case 7:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 7:\n"+
    					    "Explain which of the Five you would dedicate yourself "+
    					    "to, should you be accepted into the Circle, and why "+
    					    "that is so.\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_seven(player)+"\n");
    					return 1;
    					break;
    				case 8:
    					write(capitalize(player)+" gave the following "+
    					    "answer to task 2, question 8:\n"+
    					    "What do you feel the Five want from us?\n\n"+
    					    GUILD_MANAGER->query_task_two_answer_eight(player)+"\n");
    					return 1;
    					break;
    				default:
    					notify_fail("There are only 8 answers for you to view in task 2.\n");
		    			return 0;
		    			break;
		    	}
    			break;
    		case 3:
    			switch(answer)
    			{
    				case 1:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 3, question 1:\n"+
    			    		"Define family for me and what it means to you.\n"+
    			    		GUILD_MANAGER->query_task_three_answer_one(player)+"\n");
    					return 1;
    					break;
    				case 2:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 3, question 2:\n"+
    			    		"Why do we ask for this definition of family and why is "+
    			    		"it so vital?\n"+
    			    		GUILD_MANAGER->query_task_three_answer_two(player)+"\n");
    					return 1;
    					break;
    				default:
    					notify_fail("There are only 2 answers for you to view in task 3.\n");
		    			return 0;
		    			break;
		    	}
    		case 4:
    			write("There are no answers in task 4 to review.\n");
    			return 1;
    			break;
    		default:
    			notify_fail("Who's task answers would you like to see? view <player> <task#> <answer#>\n");
    			return 0;
    			break;
    	}
    }          
}

public int
do_anote(string str)
{
	string player, note;
	
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to add a note to?\n");
        return 0;
    }
    if (sscanf(str, "%s %s", player, note) != 2)
    {
    	notify_fail("Who would you like to add a note to? anote <player> <note>\n");
    	return 0;
    }
    
    setuid();
    seteuid(getuid());
    sscanf(str, "%s %s", player, note);
    player = lower_case(player);

    if (!SECURITY->exist_player(player))
    {
        write(capitalize(player) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }
    
	GUILD_MANAGER->set_guild_notes(player, note);
	write("You have added a note about "+capitalize(player)+".\n");
	return 1;
}

public int
do_vnote(string str)
{
	string player, note;
	
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to view the note of?\n");
        return 0;
    }
   
    player = lower_case(str);
	setuid();
    seteuid(getuid());

    if (!SECURITY->exist_player(player))
    {
        write(capitalize(player) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }
    
	note = GUILD_MANAGER->query_guild_notes(player);
	if (note)
		write("The following note has been added about "+capitalize(player)+":\n"+note+"\n");
	else
		write("There is no note about "+capitalize(player)+".\n");
		
	return 1;
}

public int
query_focus()
{
    string message = GUILD_MANAGER->query_ec_focus();
    write("The current Elementalist Focus is: "+capitalize(message)+"\n");
    return 1;
}

/*
public int
set_focus(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }
    
    if (!str)
    {
        notify_fail("Set who as the Focus?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    str = lower_case(str);

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }
    
	string message = GUILD_MANAGER->set_ew_focus(str,TP->query_real_name());
	write(message);
    return 1;
}

public int
rem_focus()
{
    if (!can_use_council_commands())
    {
        return 0;
    }
    
    string message = GUILD_MANAGER->remove_ew_focus(TP->query_real_name());
    write(message);
    return 1;
}
*/

public int
query_seekers()
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    string message = "";

    string * seekers = GUILD_MANAGER->query_all_seekers();
    if (sizeof(seekers) == 0)
    {
        message = "There are currently no Elemental Seekers.\n";
    }
    else if (sizeof(seekers) == 1) 
    {
        message = "There is currently one Elemental Seeker: " 
            + capitalize(seekers[0]) + ".\n";
    }
    else
    {
        message = "There are currently the following Elemental Seekers: ";
        message += (COMPOSITE_WORDS(map(seekers, capitalize)) + ".\n"); 
    }
        
    write(message);
    return 1;
}

public int
query_worshippers()
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    string message = "";

    string * worshippers = GUILD_MANAGER->query_all_worshippers();
    if (sizeof(worshippers) == 0)
    {
        message = "There are currently no Elemental Worshippers.\n";
    }
    else if (sizeof(worshippers) == 1) 
    {
        message = "There is currently one Elemental Worshipper: " 
            + capitalize(worshippers[0]) + ".\n";
    }
    else
    {
        message = "There are currently the following Elemental Worshippers: ";
        message += (COMPOSITE_WORDS(map(worshippers, capitalize)) + ".\n"); 
    }
        
    write(message);
    return 1;
}

public int
do_borrow (string str)
{
	if (!str)
	{
		NF("Borrow what? A scroll perhaps? <borrow scroll>\n");
		return 0;
	}
	
	if (str != "scroll")
	{
		NF("Borrow what? A scroll perhaps? <borrow scroll>\n");
		return 0;
	}
	
	if (present("_elementalist_transparent_scroll_",TP))
	{
		write("You already have a transparent scroll.\n");
		return 1;
	}
	
	object scroll = clone_object(ELEMENTALIST_OBJS + "transparent_scroll");
	scroll->move(TP,1);
	write("You pick up the transparent scroll from the table. As you do "+
	    "so, another one appears in it's place.\n");
	say(QCTNAME(TP) + " reaches down and takes the transparent scroll "+
	    "from the table. As soon as " + TP->query_pronoun() + " grabs "+
	    "the scroll, another one appears in it's place.\n");
	return 1;
}
    
public void 
init()
{
    ::init();

    add_action(see_council, "council");
    add_action(add_council_member, "addmem");
    add_action(remove_council_member, "remmem");
    add_action(record_stop_train, "trainban");
    add_action(record_spell_banned, "prayerban");
    add_action(record_resource_banned, "resourceban");
    add_action(record_temple_banned, "templeban");
    add_action(record_player_expelled, "expel");
    add_action(record_remove_punishments, "rempunish");
    add_action(check_punishments, "punishments");
    add_action(do_allowswitch, "allowswitch");
    add_action(read_item, "read");
    add_action(do_allow, "allow");
    add_action(do_task, "task");
    add_action(do_resetone, "reset1");
    add_action(do_resettwo, "reset2");
    add_action(do_resetthree, "reset3");
    add_action(do_resetfour, "reset4");
    add_action(do_view, "view");
    add_action(do_anote, "anote");
    add_action(do_vnote, "vnote");
    add_action(query_focus, "focus");
//    add_action(set_focus, "setfocus");
//    add_action(rem_focus, "remfocus");
    add_action(query_seekers, "seekers");
    add_action(query_worshippers, "worshippers");
    add_action(do_borrow, "borrow");

    add_action(no_drop, "drop");
    add_action(no_drop, "put");
}

