#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dwarf/guild.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit DWARF_IN;

#define SPONSOR_ONE "_clan_sponsor_one"
#define SPONSOR_TWO "_clan_sponsor_two"
#define SAVEFILE ("/d/Ansalon/estwilde/iron_delving/elder")
#define RETIRED_FILE "/d/Ansalon/guild/dwarf/log/elder_retired"
#define MORE_OBJ "/std/board/board_more"

string *retiredlist = ({ });

string whose_thane;

string paper_desc = 0;

/* prototype */
public string read_book();


void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    seteuid(getuid());

    add_item(({"chamber","chamber of elders"}),
      "@@long_descr");
    add_item(({"curtain","sky-blue curtain"}),
      "To the north a sky-blue curtain covers the exit " +
      "out.\n");
    add_item(({"plaque","silver plaque"}),
      "A silver plaque has been attached to the wall here. It has words " +
      "written on it in dwarven that you can read.\n");

    add_item(({ "scrolls", "scroll" }), "There are two scrolls here. " +
        "Which one you want to examine? The ancient or the new one?\n");
    add_item("ancient scroll", "@@read_ancient_scroll@@");
    add_item("new scroll", "@@read_new_scroll@@");
    
    add_cmd_item(({"plaque","silver plaque","words"}),"read","@@read_plaque");

    add_item("book","This dusty old book contains the list of the Warriors of the "+
                    "Neidar Clan. You might want to read it.\n");

    add_cmd_parse("[the] [dusty] 'book'", "read", "@@read_book");

    add_exit(IRON + "board","north",0);

    clone_object(EOBJ + "council_board")->move(TO);

    reset_dwarf_room();
}

string
read_new_scroll()
{
    
    TP->catch_msg("Someone continues recording the most important events " +
        "of the Clan on this scroll.\n\n");
    TP->more(read_file("/d/Ansalon/log/clan/elder_list",1));
    return "";
}

string
read_ancient_scroll()
{
    
    TP->catch_msg("An ancient scroll, with events within the clan " +
		  "recorded on it in the old dwarven tongue:\n\n");
    TP->more(read_file("/d/Ansalon/log/clan/elder_list.old",1));
    return "";
}

int
read_plaque()
{
    write("\n" +
      "     Here you may 'vote for' an Elder to become Thane\n" +
      "     of the Hill Dwarves.\n\n" +
      "     The Elder must be present in the Chambers to receive\n" +
      "     the vote.\n\n" +
      "     The Elder must receive three votes in an armageddon\n" +
      "     period by three different Elders to receive the title\n" +
      "     of Thane.\n\n" +
      "     If you wish to step down from your position as\n" +
      "     Elder or Thane, simply type 'retire'.\n"+
      "     The Thane may also 'retire <elder name>' if so desired.\n\n");
    return 1;
}

string
short_descr()
{
    return "Chamber of the Elders";
}

string
long_descr()
{
    return "You stand in the Chamber of the Elders, the " +
    "council room where the Thane and dwarven Elders " +
    "discuss clan matters. A sky-blue curtain to the north " +
    "covers the exit to the north. A silver plaque has been " +
    "attached to a wall here. There are also two scrolls, " +
    "one ancient and one that looks new, that you can examine. " +
    "A dusty old book lies next to them.\n";
}

int
resign(string str)
{
    if(str)
    {
	if(TP->test_bit("Ansalon",3,3))
	{
	    if(member_array(str, retiredlist) >= 0)
	    {
		write("You have already retired "+
		  "that elder.\n");
		return 1;
	    }
	    if(!find_player(str))
	    {
		write("The Elder is not in the realms, but will "+
		  "be retirned when they next log in.\n");
		retiredlist += ({str});
		save_object(RETIRED_FILE);
		return 1;
	    }
	    if(BANISHED(find_player(str)))
	    {
		write("You cannot retire someone who is banished!\n");
		return 1;
	    }
	    if(!find_player(str)->test_bit("Ansalon",3,4))
	    {
		write("You cannot retire someone who isn't an Elder!\n");
		return 1;
	    }
	    if(find_player(str)->test_bit("Ansalon",3,3))
	    {
		write("If you wish to retire, simply type 'retire'.\n");
		return 1;
	    }
	    write(capitalize(str) + " is retired from the position of "+
	      "Elder.\n");
	    find_player(str)->clear_bit(3,4);
	    return 1;
	}
	return 0;
    }

    if(TP->test_bit("Ansalon",3,3))
    {
	write("You step down as Thane of the Hill Dwarves.\n");
	TP->clear_bit(3,3);
	TP->set_bit(3,4);
	whose_thane = "";
	save_object(SAVEFILE);
	return 1;
    }

    if(!TP->test_bit("Ansalon",3,4))
    {
	write("You are no longer a member of the council of the Thane, "+
	  "so cannot do that.\n");
	return 1;
    }

    write("You step down from your position as Dwarven Elder " +
      "of the Hill Dwarves.\n");
    TP->clear_bit(3,4);
    return 1;
}


int
vote(string str)
{
    object *ob;
    object obj;
    string who = TP->query_real_name();

    restore_object(SAVEFILE);

    if(whose_thane != "")
    {
	TP->catch_msg("The Clan already has a Thane.\n");
	return 1;
    }
    if(!strlen(str))
    {
	notify_fail("Who do you wish to vote for Thane?\n");
	return 0;
    }

    if(str == who || str == "for " +who)
    {
	notify_fail("You cannot vote for yourself.\n");
	return 0;
    }

    ob = PARSE_THIS(str, "[for] %l");

    if(!sizeof(ob))
    {
	notify_fail("That person is not here.\n");
	return 0;
    }

    obj = ob[0];

    if(obj->query_prop("_" +who+ "_has_voted"))
    {
	TP->catch_msg("You have already voted for " +
	  QTNAME(obj)+ ".\n");
	return 1;
    }

    if(obj->query_prop(SPONSOR_TWO))
    {
	TP->catch_msg("You vote for "+ QTNAME(obj)+
	  " to be the Thane of the Neidar dwarves!\n");
	obj->catch_msg("You have been voted in as Thane " +
	  "of the Neidar Clan by your fellow Elders!\n\n" +
	  "    Lead well and wisely!\n\n");
	obj->tell_watcher(QCTNAME(obj)+ " solemnly " +
	  "accepts the position of Thane of the " +
	  "Neidar Clan!\n", obj);

	obj->clear_bit(3,4);
	obj->set_bit(3,3);
	obj->remove_prop(SPONSOR_TWO);
	whose_thane = obj->query_real_name();
	save_object(SAVEFILE);
	return 1;
    }

    if(obj->query_prop(SPONSOR_ONE))
    {
	TP->catch_msg("You vote for " +QTNAME(obj)+ " to " +
	  "lead the Neidar dwarves as Thane of the Clan!\n");
	obj->catch_msg(QCTNAME(TP)+ " votes for you " +
	  "to be Thane of the Clan.\n");

	obj->remove_prop(SPONSOR_ONE);
	obj->add_prop(SPONSOR_TWO, 1);
	obj->add_prop("_" +who+ "_has_voted", 1);
	return 1;
    }

    TP->catch_msg("You vote for " +QTNAME(obj)+
      " to lead the Neidar dwarves as Thane of the Clan!\n");
    obj->catch_msg(QCTNAME(TP)+ " votes for you to be " +
      "Thane of the Clan.\n");

    /*
    Removed for the time being, as there are too
    few elders to vote in a new Thane.
	obj->add_prop(SPONSOR_ONE, 1);
    */
    obj->add_prop(SPONSOR_TWO, 1);
    obj->add_prop("_" +who + "_has_voted", 1);
    return 1;
}

public string
read_book()
{
    mixed names, names_tmp = ({});
    string output = "", name, t, outputw = "";
    int size, i = -1, pos;

    if (paper_desc)
      return paper_desc;

    names = explode(read_file("/d/Ansalon/log/clan/members"), "\n");

    size = sizeof(names);
    while(++i < size)
    {
	if ((pos = sscanf(names[i], "%s left %s", name, t)) == 2)
	{
	    if ((pos = member_array(name, names_tmp)) != -1)
		names_tmp = exclude_array(names_tmp, pos, pos);
	}
	else
	{
	    if (sscanf(names[i], "%s joined %s", name, t) == 2)
		if (member_array(name, names_tmp) == -1)
		    names_tmp += ({ name });
	}
    }

    size = sizeof(names_tmp);
    i = -1;

    while(++i < size)
    {
        output += names_tmp[i] + "\n";
    }
    output = sprintf("%#-79s",output);
    paper_desc = "These are the Dwarven Warriors of the Neidar Clan:\n" +
      "------------------------------------------------------------------------------\n" +
      output + "\n\n"+
      "------------------------------------------------------------------------------\n";
    return paper_desc;
}

void
init()
{
    ::init();
    add_action(resign, "retire");
    add_action(vote, "vote");
}
