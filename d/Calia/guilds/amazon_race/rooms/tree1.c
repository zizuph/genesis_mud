/*
 *    tree1.c  
 *
 * Starting room for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

string *gMembers = ({});
string list_all();

void
create_room()
{
    set_short("In the south part of a camouflaged treehouse");
    set_long("In the south part of a camouflaged treehouse. In this "+
      "section of the treetop the hut has been furnished with "+
      "some bunks, most of them are occupied, save the ones closest "+
      "to the wall. Going northeast will take you directly to the "+
      "center of the treehouse and north will take you to the big "+
      "board, used to place notes on. A small plaque and a piece "+
	  "of parchment has been nailed to the wall here.\n");
    
    add_item(({"plaque","small plaque"}), "It got some writing, you "+
      "should try reading it.\n");
    add_item(({"treehouse","treetop","hut"}), "This fairly large treehouse "+
      "has been constructed in what seems to be one of the largest trees "+
      "in the whole forest. It can easily hold a large group of people.\n");
    add_item("bunks","They don't seem to comfortable, most of them "+
      "are occupied anyway.\n");
    add_item(({"wall","walls"}), "The walls are made from branches, "+
      "twined together, forming a wall. In some places it has been "+
      "reinforced by some planks, making it sturdy.\n");
    add_item(({"board", "big board"}), "It is the board the Amazons "+
      "use to communicate with eachother.\n");
	add_item(({"parchment", "piece of parchment"}), list_all);
    
    add_cmd_item(({"plaque","small plaque"}),
        "read","@@read_sign");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOMS + "tree3","northeast");
    add_exit(ROOMS + "tree4","north");
}

int
read_sign()
{     
    write(" ------------------------------------- \n"+
          "|                                     |\n"+
          "| Amazons may choose to 'sleep here'. |\n"+
          "| It is also possible to 'rest here'  |\n"+
          "| if you only want to stay over the   |\n"+
          "| night.                              |\n"+
          "|                                     |\n"+
          " ------------------------------------- \n");
    return 1;
}

int
sleep(string str)
{
    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Sleep here?\n");
        return 0;
    }

    if (!IS_MEMBER(TP))
    {
        notify_fail("Only amazons may sleep here!\n");
        return 0;
    }   
    else if (TP->set_default_start_location(START_ROOM))
    {
        write("You claim one of the bunks and decide to start "+
          "your day out here.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
          "Please contact the guildmaster or make a bug report.\n");
        return 0;
    }
}

int
rest(string str)
{
    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Rest here?\n");
        return 0;
    }

    if (!IS_MEMBER(TP))
    {
        notify_fail("Only amazons may rest here!\n");
        return 0;
    }   
    else if (TP->set_temp_start_location(START_ROOM))
    {
        write("You claim one of the bunks and decide to rest "+
          "here for the night.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
          "Please contact the guildmaster or make a bug report.\n");
        return 0;
    }
}

string
list_all()
{
	string *members = ({});
	int i;

    restore_object(SERVER_SAVE);

    if (!IS_MEMBER(this_player()))
    {
		return ("It is nothing of interest for you.\n");
    }  

    write("Ooo--- -- -          -- - --          - -- ---ooO\n");
    write("o                                               o\n");
    write("o                                               o\n");
    if (sizeof(gMembers) < 1)
	    write("  There are currently no Amazons listed.\n");
    else
    {
        for (i=0;i < sizeof(gMembers);i++)
		{
			members += ({ capitalize(gMembers[i]) });
		}
        sort_array(members);
	    write("   These are our current Amazon members:     \n");
	    write("\n");
	    write(break_string(implode(members, ", "),40,5)+"\n");
    }
    write("\n");
    write("\n"); 
    write("o                                 Azealia,      o\n");
    write("o                                  The Trainer. o\n");
    write("Ooo--- -- -          -- - --          - -- ---ooO\n");
    return "";
}

void
init()
{
    ::init();

    add_action(sleep, "sleep");
    add_action(rest, "rest");
}
