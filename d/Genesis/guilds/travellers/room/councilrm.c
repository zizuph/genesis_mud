/*  Fixed some typos -- Amelia 5-28-98
 */
#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include "/d/Earthsea/sys/macros.h"
#include <std.h>
#include <files.h>

void
create_traveller_room()
{
    object board;

    set_short("The Traveller council chambers.");

    set_long("These are the council chambers of the infamous Traveller\n"
      + "guild. The room is fairly large in size. In the center\n"
      + "of the room is a large round table with three chairs set\n"
      + "around it. This is the place where all important decisions\n"
      + "are made concerning the guild and its members. There are\n"
      + "many rugs, figurines and other memorabilia that have accumulated\n"
      + "over many years of adventuring. There is also a large \n"
      + "bookshelf on the east wall containing the stories of many\n"
      + "Travellers' journeys. Hanging from the north wall is a medium\n"
      + "sized elaborate rug that seems to have something woven in\n"
      + "it. You may exit through the door from which you\n"
      + "entered, or go north through the rugs.\n");

    add_item(({"rug", "wall rug"}),
      "This is an ornately woven rug. It looks brilliantly "+
      "crafted. It covers most of the wall with the following sewn in "+
      "in platinum directly in the middle:\n"
      + "These are the few that are masters of travelling.\n");
    add_item(({"bookshelf", "shelf"}), "This is a large redwood "+
      "shelf that serves to hold books. This is where all books "+
      "from the Traveller library come to be accepted. "+
      "The bookshelf looks _extremely_ interesting, maybe you "+
      "should 'study' it?\n");
    add_item(({"table", "round table"}), "This is a large oak table.\n");
    add_item(({"chairs"}), "These chairs are made of hard wood "+
      "and do not look extremely comfortable.\n");


    add_cmd_item("bookshelf", "study", 
      "Welcome to the Traveller council room. In this room\n"
      + "you can:\n"
      + "\n"
      + "-'add' another Traveller to the council-\n"
      + "-'exile' a council member from the council-\n"
      + "-List council-\n"
      + "\n"
      + "Note: Adding and removing council members should\n"
      + "not be done without one other council member's\n"
      + "support.\n");

    add_exit("joinroom", "south");
    add_exit("po", "north");

    if ((board = clone_object(BOARD_OBJECT)))
    {
	board->set_board_name(TRAVELLERS_LOG_DIR + "council_board_data");
	board->set_num_notes(30);
	board->set_silent(1);
	board->set_show_lvl(1);
	board->set_remove_rank(WIZ_NORMAL);
	board->set_remove_str(
	  "Sorry but that is for high-level wizards only !\n");
	board->move(TO, 1);
    }

}

int
do_list(string str)
{
    string *names;
    int i;

    notify_fail("List what? Council?\n");
    if (str != "council" && str != "Council")
	return 0;

    setuid();
    seteuid(getuid());

/* only Earthsea wizzes, council members and arches */
    if (!IS_WIZ(this_player()) &&
      !(COUNCIL_MEMBER(TP->query_real_name())))
    {
	write("You are not permitted to do that.\n");
	return 1;
    }

    if (!sizeof(names = TRAVELLERS_MANAGER->query_council_members()))
    {
	write("There are no members of the council right now.\n");
	return 1;
    }

    write("Members of the council are:\n");
    for (i = 0; i < sizeof(names); i++)
    {
	write(capitalize(names[i]) + " : " + COUNCIL_MEMBER(names[i]) + "\n");
    }

    return 1;
}

int
do_add(string str)
{
    string name;
    int typ, t;
    object who;

    if (!str)
    {
	notify_fail("Add whom?\n");
	return 0;
    }

    if (!EARTHSEA_WIZ(this_player()) &&
      !(COUNCIL_MEMBER(TP->query_real_name())) &&
      (SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_ARCH))
    {
	write("You are not allowed to do that.\n");
	return 1;
    }

    setuid();
    seteuid(getuid());

    if ((sscanf(str,"%s %d", name, typ) != 2) ||
      (COUNCIL_MEMBER(TP->query_real_name())))
    {
	name = str;
	typ = 1;
    }

    if (!typ)
    {
	write("I don't really understand the type.\n");
	return 1;
    }

    if (!(who = find_player(name)))
    {
	write("The player needs to be in the game.\n");
	return 1;
    }

    if (!IS_MEMBER(who))
    {
	write("But that player is not a Traveller.\n");
	return 1;
    }

    t = COUNCIL_MEMBER(name);

    if (!t)
    {
	if (!TRAVELLERS_MANAGER->add_council_member(name, typ))
	{
	    write("Failed to make " + capitalize(name) + " a member of " +
	      "the council.\n");
	    return 1;
	}

	write(capitalize(name) + " is now member of the council.\n");
	who->catch_msg("You are now member of the Traveller council.\n");

	return 1;
    }

    if (t == typ)
    {
	write("That player is already a member of the Council.\n");
    }
    else
    {
	if (!TRAVELLERS_MANAGER->add_council_member(name, typ))
	{
	    write("Failed to change type.\n");
	    return 1;
	}

	write("You change the type of that Council member.\n");
    }

    return 1;
}

int
do_remove(string str)
{
    object who;

    if (!strlen(str)) 
    {
	return 0;
    }

    str = lower_case(str);

    if (!EARTHSEA_WIZ(this_player()) &&
      !COUNCIL_MEMBER(TP->query_real_name()) &&
      (SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_ARCH))
    {
	write("You are not allowed to do that.\n");
	return 1;
    }

    setuid();
    seteuid(getuid());

    if (COUNCIL_MEMBER(str))
    {
	TRAVELLERS_MANAGER->remove_council_member(str);
	write(capitalize(str) + " is removed from the council.\n");

	if (who = find_player(str))
	{
	    tell_object(who, "You have been removed from the Traveller " +
	      "council.\n");
	}
    }
    else
    {
	write(capitalize(str) + " is not a member of the council.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(do_list, "list");
    add_action(do_add, "add");
    add_action(do_remove, "exile");
}
