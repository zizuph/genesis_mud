/* Fixed some typos -- Amelia 5-28-98 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>

inherit TRAVELLERS_STD_DIR + "room_base";

#define ONE_DAY 43200

public void
create_traveller_room()
{
    add_prop(ROOM_S_MAP_FILE, "trav_map.txt");
    object board;

    set_short("The Travellers Council Chambers");
    set_long("These are the council chambers of the infamous Traveller " +
        "guild. The room is fairly large in size. In the center " +
        "of the room is a large round table with three chairs set " +
        "around it. This is the place where all important decisions " +
        "are made concerning the guild and its members. There are " +
        "many rugs, figurines and other memorabilia that have " +
        "accumulated over many years of adventuring. There is also a " +
        "large bookshelf on the east wall containing the stories of " +
        "many Travellers' journeys. Hanging from the north wall is " +
        "a medium sized elaborate rug that seems to have something " +
        "woven in it. You may exit through the door from which you " +
        "entered, or go north through the rugs.\n");
    add_item(({ "rug", "wall rug" }),
        "This is an ornately woven rug. It looks brilliantly " +
        "crafted. It covers most of the wall with the following " +
        "sewn in in platinum directly in the middle:\n" +
        "These are the few that are masters of travelling.\n");
    add_item(({ "bookshelf", "shelf" }),
        "This is a large redwood shelf that serves to hold books. " +
        "This is where all books from the Traveller library come to " +
        "be accepted. The bookshelf looks _extremely_ interesting, " +
        "maybe you should 'study' it?\n");
    add_item(({ "table", "round table" }),
        "This is a large oak table.\n");
    add_item(({ "chairs" }), "These chairs are made of hard wood " +
        "and do not look extremely comfortable.\n");
    add_cmd_item("bookshelf", "study",
        "Welcome to the Traveller council room. In this room\n" +
        "you can:\n" +
        "\n" +
        "-'add' another Traveller to the council-\n" +
        "-'exile' a council member from the council-\n" +
        "-'step down' to remove yourself from the council-\n" +
        "-List council-\n" +
        "\n" +
        "Note: Adding and removing council members should\n" +
        "not be done without one other council member's\n" +
        "support.\n");
    add_exit("joinroom", "south");
    add_exit("po", "north");

    if((board = clone_object(BOARD_OBJECT)))
    {
        board->set_board_name(TRAVELLERS_LOG_DIR + "council_board_data");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str(
            "Sorry but that is for high-level wizards only !\n");
        board->move(this_object(), 1);
    }
}

public int
do_list(string str)
{
    string *names;
    int i;
    object tp = this_player();

    if(lower_case(str) != "council")
    {
        return notify_fail("List what? Council?\n");
    }

    setuid();
    seteuid(getuid());

    if(!EARTHSEA_WIZ(tp) && !(COUNCIL_MEMBER(tp->query_real_name())) &&
        !IS_ARCH(tp))
    {
        write("You are not permitted to do that.\n");
        return 1;
    }

    if(!sizeof(names = TRAVELLERS_MANAGER->query_council_members()))
    {
        write("There are no members of the council right now.\n");
        return 1;
    }

    write("Members of the council are:\n");

    for(i = 0; i < sizeof(names); i++)
    {
        write(capitalize(names[i]) + " : " +
            COUNCIL_MEMBER(names[i]) + "\n");
    }

    return 1;
}

public int
do_add(string str)
{
    string name;
    int typ, t, age_days, race_stat, avg_stat;
    object who, tp = this_player();

    if(!str)
    {
        return notify_fail("Add whom?\n");
    }

    if(!EARTHSEA_WIZ(tp) && !(COUNCIL_MEMBER(tp->query_real_name())) &&
        !IS_ARCH(tp))
    {
        write("You are not allowed to do that.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    if(sscanf(str, "%s %d", name, typ) != 2 ||
        COUNCIL_MEMBER(tp->query_real_name()))
    {
        name = str;
        typ = 1;
    }

    if(!typ)
    {
        write("I don't really understand the type.\n");
        return 1;
    }

    if(!(who = find_player(name)))
    {
        write("The player needs to be in the game.\n");
        return 1;
    }

    if(!IS_MEMBER(who))
    {
        write("But that player is not a Traveller.\n");
        return 1;
    }

    age_days = (who->query_age() / ONE_DAY);
    race_stat = who->query_base_stat(SS_RACE);
    avg_stat = who->query_average_stat();

    if(!tp->query_wiz_level() && (age_days < 50 || race_stat < 50 ||
        avg_stat < 90 || (age_days + race_stat) < 150))
    {
        return notify_fail("That person does not seem well-travelled " +
            "enough to join the council!\n");
    }

    if(!(t = COUNCIL_MEMBER(name)))
    {
        if(!TRAVELLERS_MANAGER->add_council_member(name, typ))
        {
            write("Failed to make " + capitalize(name) + " a member of " +
                "the council.\n");
            return 1;
        }

        write(capitalize(name) + " is now member of the council.\n");
        who->catch_msg("You are now member of the Traveller council.\n");

        return 1;
    }

    if(t == typ)
    {
        write("That player is already a member of the Council.\n");
    } else {
        if(!TRAVELLERS_MANAGER->add_council_member(name, typ))
        {
            write("Failed to change type.\n");
            return 1;
        }

        write("You change the type of that Council member.\n");
    }

    return 1;
}

public int
do_remove(string str)
{
    object who, tp = this_player();

    if(!strlen(str)) 
    {
        return notify_fail("Exile whom?\n");
    }

    str = lower_case(str);

    if(!EARTHSEA_WIZ(this_player()) &&
        !COUNCIL_MEMBER(tp->query_real_name()) &&
        !IS_ARCH(tp))
    {
        write("You are not allowed to do that.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    if(!tp->query_wiz_level() &&
        COUNCIL_MEMBER(str) >= COUNCIL_MEMBER(tp->query_real_name()))
    {
        write("You are not allowed to remove that councillor.\n");
        return 1;
    }

    if(COUNCIL_MEMBER(str))
    {
        TRAVELLERS_MANAGER->remove_council_member(str);
        write(capitalize(str) + " is removed from the council.\n");

        if(who = find_player(str))
        {
            tell_object(who, "You have been removed from the Traveller " +
              "council.\n");
        }
    } else {
        write(capitalize(str) + " is not a member of the council.\n");
    }

    return 1;
}

public int
do_step(string str)
{
    string name = this_player()->query_real_name();

    if(!str || str != "down")
    {
        return notify_fail("Step what? Step down?\n");
    }

    setuid();
    seteuid(getuid());

    if(!TRAVELLERS_MANAGER->query_council_member(name))
    {
        return notify_fail("You are not a member of the council!\n");
    }

    TRAVELLERS_MANAGER->remove_council_member(name);
    write("You step down from council.\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action(do_list, "list");
    add_action(do_add, "add");
    add_action(do_remove, "exile");
    add_action(do_step, "step");
}
