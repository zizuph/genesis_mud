/*
 *    tree4.c  
 *
 * Board room for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    object board;
    
    set_short("In the west part of a camouflaged treehouse");
    set_long("In the west part of a camouflaged treehouse. This "+
      "section of the gigantic treetop is mostly covered by a "+
      "big board, nailed to the branched west wall. Directly to "+
      "the south lies some bunks and northeast you spot an Amazon "+
      "warrior, training some younger women. East will take you "+
      "to the center of the establishment.\n");

    add_item(({"treehouse","treetop","hut"}), "This fairly large treehouse "+
      "has been constructed in what seems to be one of the largest trees "+
      "in the whole forest. It can easily hold a large group of people.\n");
    add_item(({"wall","walls"}), "The walls are made from branches, "+
      "twined together, forming a wall. In some places it has been "+
      "reinforced by some planks, making it sturdy.\n");
    add_item("amazon warrior", "She is training some younger women "+
      "in the art of spearing.\n");
      
    if(!objectp(board))
    {
	board = clone_object(OBJ + "board");
	board->move(this_object(), 1);
    }
            
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOMS + "tree3","east");
    add_exit(ROOMS + "tree2","northeast");
    add_exit(ROOMS + "tree1","south");
}

int
handle_vote(string str)
{
    int i, votenumber;
    string argument, votevalue, desc, ret_check,
           name = TP->query_real_name();
    
    str = lower_case(str);
	notify_fail("Vote what? 'vote help' for instructions.\n");

    if (!strlen(str))
        return 0;   

    if (str == "list")
    {
    	VOTING->list_votes();
        return 1;
    }
    
    if (str == "help")
    {
        write("Ooo--- -- -           -- - --           - -- ---ooO\n");
        write("o                   Voting Help                   o\n");
        write("o                   -----------                   o\n\n\n");
		write("  vote list -\n");
		write("      Will list all active votes.\n\n");
	    write("  vote info <vote number> -\n");
		write("      Will display some information about\n");
		write("      the vote.\n\n");
		write("  vote <vote number> for <yes/no/abstain> -\n");
		write("      Will cast a vote.\n\n");
		write("  vote change <vote number> for <yes/no/abstain> -\n");
		write("      Will change your vote for another value.\n");
		write("o                                                 o\n");
        write("o                                                 o\n");
        write("Ooo--- -- -           -- - --           - -- ---ooO\n");


        return 1;
    }

	if (parse_command(str, ({ }), "'info' %s", argument))
    {
    
        if (parse_command(argument, ({ }), "%d", votenumber))
            if (VOTING->vote_info(votenumber, name))
            {
                return 1;
            }        

        notify_fail("Syntax: vote info <votenumber>.\n");
        return 0; 
     }
    
	if (parse_command(str, ({ }), "'change' %d %s", votenumber, argument))
    {
        if (parse_command(argument, ({ }), "'for' %s", votevalue))
        {
            ret_check = VOTING->validate_vote(votenumber, votevalue, name, 0);
            if (strlen(ret_check))
            {
                notify_fail(ret_check);
                return 0;
            }
            VOTING->change_voting(votenumber, votevalue, name);            
            write("You change your vote to '"+votevalue+"' on the "+
              LANG_WORD(votenumber)+" vote.\n");
            say(QCTNAME(TP)+" casts a vote for the "+
              LANG_WORD(votenumber)+" vote.\n");
            return 1;           
        }
        notify_fail("Syntax: vote change <votenumber> for <value>.\n");
        return 0; 
     }

    if (parse_command(str, ({ }), "%d %s", votenumber, argument))
    {
        if (parse_command(argument, ({ }), "'for' %s", votevalue))
        {
            ret_check = VOTING->validate_vote(votenumber, votevalue, name);
            if (strlen(ret_check))
            {
                notify_fail(ret_check);
                return 0;
            }            
            VOTING->add_voting(votenumber, votevalue, name);            
            write("You vote '"+votevalue+"' on the "+
              LANG_WORD(votenumber)+" vote.\n");
            say(QCTNAME(TP)+" casts a vote for the "+
              LANG_WORD(votenumber)+" vote.\n");
            return 1;           
        }
        notify_fail("Syntax: vote <votenumber> for <value>.\n");
        return 0; 
     }
    return 0;     
}

void
init()
{
    ::init();
    add_action(handle_vote, "vote");
}