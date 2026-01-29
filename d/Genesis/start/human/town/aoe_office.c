/* 

   /d/Genesis/start/human/town/aoe_office.c

   Place where mortals post event ideas

   Stern and Gwyneth, 10-jan-2001
   
   Todo: wizard info.
*/ 

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <cmdparse.h>
#include <files.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "../defs.h"

#define AOE_IDEA_BOARD "/w/postmaster/private/arch_boards/aoe_idea"
#define AOE_HELPSCROLL "/d/Genesis/start/human/town/aoe_scroll"
#define AOE_DIR        "/d/Genesis/AoE/events/"
mapping gExp_rewards = ([]);
mapping gObj_rewards = ([]);

nomask string
poster_description()
{

    write("The poster states: \n\n" +
         "Mortals can <claim> their event rewards here, if " +
         "so notified by the Event Team.\n\n");

    if  (!(this_player()->query_wiz_level()))
    {
        return ("The rest of the script on this poster is wizardly " +
            "writing and thus unreadable for you.\n");

    }
    return ("Event Team Wizard commands:\n\n" +
        "add <object/exp> reward for <name>    - to reward a mortal.\n" +
        "subtract <object/exp> reward for <name> - to undo a pending reward.\n" +
        "list rewards                          - to see pending rewards.\n\n" +
        "Please see man events and help events for rules of conduct.\n\n");
}

/*
nomask string
scroll_description()
{

    write("This text is also available using <help events>. \n\n");
    "/d/Genesis/cmd/misc"->genesis_help("events");
    return ("\n");
}
*/

void
create_room() 
{
    set_short("In the Abyss");
    set_long("\nThis is the Abyss of the Tower, which has been " +
      "confiscated by the Arch of Events and his team as office space. " +
      "A sturdy wooden table stands in the middle of the room. On top " +
      "of it lies a scroll. A  poster and a note are nailed to the wall. " +
      "There is a board here that you can use to submit ideas for events." +
      " Looking at the paintings on the walls you realize events are " +
      "special one-time mostly in-theme quests " +
      "that are controlled by wizards. It is rumoured that in rare cases " +
      "a superb event idea is rewarded by the Events Team. " +
      "To protect the ideas, this board can only be read by the " +
      "Administration, Lieges, and Event Wizards of Genesis, " +
      "not by other wizards or mortal players. " +
      "If you have an idea for an event, please write the idea down " +
      "as clearly and detailed as possible, and who knows, maybe it will " +
      "find its way into the lives of the inhabitants of this realm.\n\n");

    add_item( ({ "table", "sturdy table", "sturdy wooden table", 
        "wooden table" }),
        ("The table is a square smooth flat slab fixed on legs, as " +
         "most tables are. It's empty, except for a scroll.\n"));
    add_item( ({ "painting", "paintings"  }),
        ("You see three paintings, describing different events.\n"));
    add_item( ({ "first painting" }),
        ("This painting shows a dishevelled maiden of noble blood " +
         "being released from her chains by a pair of brave adventurers. " +
         "A clever gleam shines in their eyes, and you notice two " +
         "villains lying inert on the ground behind them.\n"));
    add_item( ({ "second painting" }),
        ("An injured man is the center of this painting, his face contorted " +
         "with pain. A man and " +
         "woman kneel next to him surrounded by the darkness. The woman " +
         "is binding his wounds, as the man prepares to carry him to a " +
         "safer place.\n"));
    add_item( ({ "third painting" }),
        ("The last painting seems to leap from its frame with movement. " +
         "A large number of people run to and fro, throwing and dodging " +
         "eggs! From the sticky hair and clothing, it seems that not " +
         "all are dodging successfully. But the smiles on their faces " +
         "show that they don't mind too much.\n"));
    add_item( ({ "nail", "nails"  }),
        ("Everything in this room, even the board, seems to be nailed " +
         "or bolted to discourage theft and borrowing.\n"));
    add_item( ({ "wall", "walls"  }),
        ("The walls are uninteresting except for a few paintings and " +
         "a poster, and, perhaps, that tiny hole near the ground.\n"));
    add_item( ({"ground", "floor"}),
        ("The floor is bare and uninteresting. \n"));
    add_item( ({"ceiling"}),
        ("The ceiling is rather high up for a basement. \n"));
    add_item( ({"stairs", "wooden stairs"}),
        ("The wooden stairs allow you to go up to the ground floor. \n"));
    add_item( ({ "hole", "tiny hole" }),
        ("You walk towards the tiny hole and lower yourself to peer in. " +
        "Rodent housing?\n"));
    add_item( ({"note"}),
        ("The note states: NO PICKNICKING!\n"));
    add_item( ({ "poster" }), poster_description); 

    /*    add_item( ({ "scroll"  }), scroll_description); */

    add_exit(TOWN_DIR + "tower", "up");
    add_exit(AOE_DIR + "poem/submit_room", "west");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "This is a room for writing, " +
      "not fighting.\n");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    setuid(); 
    seteuid(getuid()); 
    restore_object(MASTER);
    clone_object(AOE_IDEA_BOARD)->move(TO);
    clone_object(AOE_HELPSCROLL)->move(TO);
}

private void
aoe_log(string file, string message)
{
    "/secure/aoe_logger_relay"->aoe_write_file("/d/Wiz/AoE/logs/" + file, 
        extract(ctime(time()), 4, 15) + " " + message);
}

private void
aoe_message(string message)
{
    int index, size;
    object aoe_member;
    string *aoe_team = SECURITY->query_team_list("aoe");

    for (index = 0, size = sizeof(aoe_team); index < size; index++)
    {
        if (objectp(aoe_member = find_player(aoe_team[index])))
        {
            aoe_member->catch_tell("AOE: " + message + "\n");
        }
    }
}

private void
reward_exp(object who, string name)
{
    int *exp, combat, quest, general;
    string message;

    exp = gExp_rewards[name];
    message = capitalize(name) + " rewarded with";
    
    if (exp[0] > 0)
    {
        who->add_exp_combat(exp[0]);
        message += " combat(" + (exp[0]) + ")";
    }
    if (exp[1] > 0)
    {
        who->add_exp_quest(exp[1]);
        message += " quest(" + (exp[1]) + ")";
    }
    if (exp[2] > 0)
    {
        who->add_exp_general(exp[2]);
        message += " general(" + (exp[2]) + ")";
    }

    aoe_message(message);
    aoe_log("claimed", message + "\n");
    who->catch_tell("You claim your reward, and feel more experienced.\n");
    say(QCTNAME(who) + " claims " + who->query_possessive() + " reward.\n");
    gExp_rewards = m_delete(gExp_rewards, name);
    save_object(MASTER);
}

private void
reward_obj(object who, string name)
{
    int size, index;
    object item;
    string message = "";

    for (index = 0, size = sizeof(gObj_rewards[name]); index < size; index++)
    {
        item = clone_object(gObj_rewards[name][index]);

        if (objectp(item))
        {
            item->move(who, 1);
            who->catch_tell("You claim your reward, and " + LANG_ASHORT(item) +
                " materializes in your hands.\n");
            say(QCTNAME(who) + " claims " + who->query_possessive() + 
                " reward.\n");
            message += (capitalize(name) + " rewarded with " +
                gObj_rewards[name][index] + ".\n");
        }
        else
        {
            who->catch_tell("You claim your reward, but there was a problem. " +
                "Please 'mail aoe'.\n");
            message = ("Error in rewarding " + capitalize(name) +
                " with " + gObj_rewards[name] + ".\n");
        } 
    }

    if (strlen(message))
    {
        aoe_log("claimed", message);
        aoe_message(message);
    }

    gObj_rewards = m_delete(gObj_rewards, name);
    save_object(MASTER);
}

public int
claim_reward(string str)
{
    int reward = 0;
    object ob = this_player();
    string name;

    name = ob->query_real_name();

    if (member_array(name, m_indexes(gExp_rewards)) != -1) 
    {
        reward_exp(ob, name);
        reward = 1;
    }

    if (member_array(name, m_indexes(gObj_rewards)) != -1)
    {
        reward_obj(ob, name);
        reward = 1;
    }

    if (!reward)
    {
        write("There is no reward for you to claim. If you think " +
            "there has been an oversight, please 'mail aoe'.\n");
        return 1;
    }

    return 1;
}

private void
add_exp_reward(string str, string name)
{
    int combat, quest, general, num;
    string message = "";

    if (!strlen(str))
    {
        write("Invalid input. Enter exp to reward " + 
            " (combat quest general) or ~q to quit: ");
        input_to(&add_exp_reward(, name));
        return;
    }

    if (str == "~q")
    {
        write("Aborting experience reward addition.\n");
        return;
    }

    num = sscanf(str, "%d %d %d", combat, quest, general);
    if (num != 3)
    {
        write("Invalid input. Enter exp to reward " + 
            " (combat quest general) or ~q to quit: ");
        input_to(&add_exp_reward(, name));
        return;
    }

    if (member_array(name, m_indexes(gExp_rewards)) != -1)
    {
        combat  += gExp_rewards[name][0];
        quest   += gExp_rewards[name][1];
        general += gExp_rewards[name][2];

        if (!combat && !quest && !general)
        {
            gExp_rewards = m_delete(gExp_rewards, name);
            message = capitalize(this_player()->query_real_name()) +
                " removed set exp reward for " + capitalize(name) + ".\n";
        }
        else
        {
            gExp_rewards[name] = ({ combat, quest, general, time() });
            message = capitalize(this_player()->query_real_name()) +
                " altered set exp reward for " + capitalize(name) + ". " +
                "Reward now " +
                (gExp_rewards[name][0] != 0 ? 
                "combat(" + gExp_rewards[name][0] + ")" : "") +  
                (gExp_rewards[name][1] != 0 ? 
                "quest(" + gExp_rewards[name][1] + ")" : "") +  
                (gExp_rewards[name][2] != 0 ? 
                "general(" + gExp_rewards[name][2] + ")" : "") +  
                ".\n";
        }

        aoe_log("rewards", message);
        write(capitalize(name) + " reward altered: combat(" + combat +
            "), " + "quest(" + quest + ") and general(" + general + ") " +
            "experience set.\n");
        save_object(MASTER);
        return;
    }
    else
    {
        gExp_rewards += ([ name: ({ combat, quest, general, time() }) ]);
        aoe_log("rewards", capitalize(this_player()->query_real_name()) +
            " added reward for " + capitalize(name) + " of " +
            (combat != 0 ?  "combat(" + combat + ")" : "") +  
            (quest != 0 ?  "quest(" + quest + ")" : "") +  
            (general != 0 ?  "general(" + general + ")" : "") +  
            ".\n");
        write(capitalize(name) + ": reward of combat(" + combat + "), " +
            "quest(" + quest + ") and general(" + general + ") experience " +
            "set.\n");
        save_object(MASTER);
        return;
    }
}

private void
add_obj_reward(string str, string name)
{
    if (!strlen(str))
    {
        write("Invalid object. Enter path of obj to reward " + 
            " or ~q to quit: ");
        input_to(&add_obj_reward(, name));
        return;
    }

    if (str == "~q")
    {
        write("Aborting object reward addition.\n");
        return;
    }

    if (member_array(name, m_indexes(gObj_rewards)) != -1)
    {
        if (extract(str, 0, 0) != "/")
            str = "/" + str;
        if (extract(str, -2, -1) != ".c")
            str += ".c";

        if (file_size(str) < 1)
        {
            write("No such file: " + str + ". Enter the exact " +
                "path or ~q to quit: " );
            input_to(&add_obj_reward(, name));
            return;
        }
        else if (member_array(str, gObj_rewards[name]) != -1)
        {
            write("That object is already set to be rewarded to " +
                capitalize(name) + ".\n");
            return;
        }
        else
        {
            gObj_rewards[name] += ({str});
            write(capitalize(name) + ": reward of " + str + " added.\n");
            save_object(MASTER);
        }
    }
    else
    {
        if (extract(str, 0, 0) != "/")
            str = "/" + str;
        if (extract(str, -2, -1) != ".c")
            str += ".c";

        if (file_size(str) < 1)
        {
            write("No such file: " + str + ". Enter the exact " +
                "path or ~q to quit: ");
            input_to(&add_obj_reward(, name));
            return;
        }
        else
        {
            gObj_rewards += ([ name: ({str}) ]);
            write(capitalize(name) + ": reward of " + str + " set.\n");
            save_object(MASTER);
        }
    }

    aoe_log("rewards", capitalize(this_player()->query_real_name()) +
        " added object reward for " + capitalize(name) + " of: " +
        str + ".\n");
    return;
}

public int
add_reward(string str)
{
    string type, name, *allowed;

    allowed = SECURITY->query_team_list("aoe");

    if ((member_array(this_interactive()->query_real_name(), allowed) == -1) &&
      (SECURITY->query_wiz_rank(geteuid(this_interactive())) < WIZ_LORD))
    {
        return 0;
    }

    notify_fail("The syntax is: add <object/exp> reward for <name>.\n");

    if (!strlen(str))
        return 0;

    if (!parse_command(str, ({}), "%w [reward] [for] %w", type, name))
    {
        return 0;
    }
    if (!strlen(type) || !strlen(name))
    {
        return 0;
    }

    if (!SECURITY->exist_player(name))
    {
        notify_fail(capitalize(name) + " does not exist.\n");
        return 0;
    }

    switch(lower_case(type))
    {
        case "exp":
        case "experience":
            name = lower_case(name);
            write("Enter exp to reward " + capitalize(name) +
                " (combat quest general) or ~q to quit: ");
            input_to(&add_exp_reward(, name));
            break;
        case "obj":
        case "object":
        case "item":
            name = lower_case(name);
            write("Enter path of obj to reward " + capitalize(name) +
                " or ~q to quit: ");
            input_to(&add_obj_reward(, name));
            break;
        default:
            return 0;
    }

    return 1;
}

public int
list_things(string str)
{
    int index, size, index2, size2;
    string *allowed, name,
           list = "The following rewards have been prepared:\n";

    allowed = SECURITY->query_team_list("aoe");

    if ((member_array(this_interactive()->query_real_name(), allowed) == -1) &&
      (SECURITY->query_wiz_rank(geteuid(this_interactive())) < WIZ_LORD))
    {
        return 0;
    }

    if (!strlen(str) || 
      lower_case(str) != "rewards")
    {
        notify_fail("List rewards?\n");
        return 0;
    }

    size = m_sizeof(gExp_rewards);
    if (!size)
    {
        list += "There are no experience rewards pending.\n";
    }
    else
    {
        for (index = 0; index < size; index++)
        {
            name = m_indexes(gExp_rewards)[index];
            list += capitalize(name) + " pending exp rewards: ";
            list += "combat(" + gExp_rewards[name][0] + ") ";
            list += "quest(" + gExp_rewards[name][1] + ") ";
            list += "general(" + gExp_rewards[name][2] + ").\n";
            list += "time(" + ctime(gExp_rewards[name][3]) + ").\n";
        }
    }

    size = m_sizeof(gObj_rewards);
    if (!size)
    {
        list += "There are no object rewards pending.\n";
    }
    else
    {
        for (index = 0; index < size; index++)
        {
            name = m_indexes(gObj_rewards)[index];
            list += capitalize(name) + " pending obj reward:\n";
            size2 = sizeof(gObj_rewards[name]);
            for (index2 = 0; index2 < size2; index2++)
            {
                list += gObj_rewards[name][index2] + ".\n";
            }
        }
    }

    write(list);
    return 1;
}

public void
list_obj_rewards(string name)
{
    int index, size;
    string *oblist = gObj_rewards[name], list = "";

    if (!sizeof(oblist))
    {
        list = ("No object rewards pending for " + capitalize(name) + ".\n");
    }
    for (index = 0, size = sizeof(oblist); index < size; index++)
    {
        list = ((index + 1) + "");
        list += (") " + oblist[index] + "\n");
    }

    write(list);
    return;
}

public int
rem_obj_reward(string str, string name)
{
    int i, num, index, index2;
    string message;

    if (!strlen(str))
    {
        write("Invalid option. Subtract which object reward(s) (ex: 2-4), " +
            "'all' or ~q to quit.\n");
        list_obj_rewards(name);
        input_to(&rem_obj_reward(, name));
        return 1;
    }

    if (str == "~q")
    {
        write("Aborting reward removal.\n");
        return 1;
    }

    if (lower_case(str) == "all")
    {
        gObj_rewards = m_delete(gObj_rewards, name);
        aoe_log("rewards", capitalize(this_player()->query_real_name()) + 
            " removed all object rewards for " + capitalize(name) + ".\n");
        write("All object rewards for " + capitalize(name) + " removed.\n");
        save_object(MASTER);
        return 1;
    }

    num = sscanf(str, "%d-%d", index, index2);
    if (index)
        index--;
    if (index2)
        index2--;
    else
        index2 = index;

    if (!num || 
      index < 0 || 
      index > sizeof(gObj_rewards[name]) ||
      index2 < index ||
      index2 < 0 ||
      index2 > sizeof(gObj_rewards[name]))
    {
        write("Invalid option. Subtract which object reward(s) (ex: 2-4), " +
            "'all' or ~q to quit.\n");
        list_obj_rewards(name);
        input_to(&rem_obj_reward(, name));
        return 1;
    }
    else
    {
        message = capitalize(this_player()->query_real_name()) + 
            " removed object rewards for " + capitalize(name) + " of: ";
        for(i = index; i < index2 + 1; i++)
        {
            message += gObj_rewards[name][i];
        }

        gObj_rewards[name] = exclude_array(gObj_rewards[name], index, index2);
        if (!sizeof(gObj_rewards[name]))
        {
            gObj_rewards = m_delete(gObj_rewards, name);
        }

        aoe_log("rewards", message + ".\n");
        write("Object reward(s) for " + capitalize(name) + " removed.\n");
        list_obj_rewards(name);
        save_object(MASTER);
        return 1;
    }
}

public int
remove_reward(string str)
{
    string type, name, *allowed;

    allowed = SECURITY->query_team_list("aoe");

    if ((member_array(this_interactive()->query_real_name(), allowed) == -1) &&
      (SECURITY->query_wiz_rank(geteuid(this_interactive())) < WIZ_LORD))
    {
        return 0;
    }

    notify_fail("The syntax is: subtract <object/exp> reward for <name>.\n");

    if (!strlen(str))
        return 0;

    if (!parse_command(str, ({}), "%w [reward] [for] [from] %w", type, name))
    {
        return 0;
    }

    if (!strlen(type) || !strlen(name))
    {
        return 0;
    }

    switch(lower_case(type))
    {
        case "exp":
        case "experience":
            name = lower_case(name);
            if (member_array(name, m_indexes(gExp_rewards)) == -1)
            {
                write(capitalize(name) + " has no experience reward set.\n");
                return 1;
            }
            else
            {
                gExp_rewards = m_delete(gExp_rewards, name);
                aoe_log("rewards", 
                    capitalize(this_player()->query_real_name()) +
                    " removed experience reward for " + capitalize(name) + 
                    ".\n");
                write("Experience reward for " + capitalize(name) +
                    " removed.\n");
                save_object(MASTER);
                return 1;
            }
        case "obj":
        case "object":
        case "item":
            name = lower_case(name);
            if (member_array(name, m_indexes(gObj_rewards)) == -1)
            {
                write(capitalize(name) + " has no object reward set.\n");
                return 1;
            }
            else
            {
                write("Subtract which object reward(s) (ex: 2-4), 'all' " +
                    "or ~q to quit.\n");
                list_obj_rewards(name);
                input_to(&rem_obj_reward(, name));
                return 1;
            }
        default:
            return 0;
    }
}

public void
init()
{
    ::init();

    add_action(remove_reward, "subtract");
    add_action(add_reward, "add");
    add_action(claim_reward, "claim");
    add_action(list_things, "list");
}
