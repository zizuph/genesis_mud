/*
 * Private meeting chamber of the Elemental Temple of Calia
 * 
 * Created by Leia, 2/24/2016
 *  
 */
 

#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

inherit TEMPLE_ROOM_BASE;

// Defines
#define SITTING_ON_COUCH  "_sitting_on_couch"

// Prototypes

// Global Variables
int door_open = 0;
int circle_phase = 0;
string circle_room_desc = "";

public int
can_use_council_commands()
{
    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_ew_council(this_player(), 1))
    {
        return 1;
    }
    if (GUILD_MANAGER->query_is_ec_council(this_player(), 1))
    {
        return 1;
    }
    
    if (GUILD_MANAGER->query_is_elder_cleric(this_player()))
    {
        return 1;
    }
    
    return 0;
}

public string
walldesc()
{
	if(door_open == 1)
	{
		return "The wall is made of smooth stone, and set in the middle of it is an open door, with an indentation just to the right of it.\n";
	}
	
	else
	{
		return "The wall is made of smooth stone. Near the middle there is an indentation.\n";
	}
}

public string
instructions()
{
    if (!can_use_council_commands())
    {
        return "You find no instructions.\n";
    }
    
    write("view <player> <#> <#> - View <player>'s answer to task <#>, question <#>\n"+
        "                        ie. 'view jaacar 2 1' would view the answer\n"+
        "                        Jaacar gave for task 2, question 1.\n"+
        "                        Current Viewable Tasks and Number of Answers:\n"+
        "                        Task 2 has 8 answers.\n"+
        "                        Task 3 has 2 answers.\n"+
        "                        Task 6 has 6 answers.\n"+
        "ebirth                - Raise your finger to an invisible point in the air.\n"+
        "elife                 - Draw a half-circle in the air.\n"+
        "edeath                - Complete drawing the circle in the air.\n"+
        "\n");
    return "";
}

public string
fireplace()
{
    if (!can_use_council_commands())
    {
        return "There is a small fireplace on the eastern wall. Burning in it is a bright orange fire.\n";
    }

    return "There is a small fireplace on the eastern wall. Burning in it is a bright orange fire. On "+
        "the fireplace you see task instructions.\n";
}

public string
circle_desc()
{
    if (!circle_phase)
        return "You find no circle.\n";
    
    switch(circle_phase)
    {
        case 1:
            return "You find no circle.\n";
            break;
        case 2:
            return "It's a silver illuminated half-circle floating in the air.\n";
            break;
        case 3:
            return "It's a silver illuminated circle floating in the air.\n";
            break;
        default:
            return "You find no circle.\n";
            break;
    }
}

public string
half_circle_desc()
{
    if (!circle_phase)
        return "You find no half-circle.\n";
    
    switch(circle_phase)
    {
        case 1:
            return "You find no half-circle.\n";
            break;
        case 2:
            return "It's a silver illuminated half-circle floating in the air.\n";
            break;
        case 3:
            return "You find no half-circle.\n";
            break;
        default:
            return "You find no half-circle.\n";
            break;
    }
}

public string
long_desc()
{
    return "This is a small meeting chamber in the Elemental Temple. On the eastern wall "+
        "there is a small fireplace. On the floor are two very comfortable looking "+
        "couches. " + circle_room_desc + "\n";
}

public void
create_temple_room()
{
	setuid();
    seteuid(getuid());
	set_short("Temple Meeting Chamber");
	set_long(VBFC_ME("long_desc"));
			
	try_item( ({"fireplace", "fire place"}),"@@fireplace@@");
	try_item( ({"circle","silver circle","illuminated circle",
	    "silver illuminated circle"}), "@@circle_desc@@");
	try_item( ({"half-circle","silver half-circle",
	"illuminated half-circle","silver illuminated half-circle"}), "@@half_circle_desc@@");

	try_item( ({"fire","burning fire"}), 
		"A bright orange fire crackles in the fireplace. It gives off just enough heat and light "
		+ "to make this room very comfortable both in temperature and lighting.\n");
		
	try_item( ({"couches", "couch", "pair of couches"}),
		"These couches are very comfortable looking and made from an opulent leather. You could probably sit "
		+ "on one of them if you wished. <sit on couch>\n");
		
	try_item( ({"indentation", "wall indentation", "indentation on wall"}),
		"On the west wall there is a small indentation the shape of a hand. \n");
		
	try_item( ({"west wall","western wall"}),"@@walldesc@@");
	try_item( ({"task instructions","instructions"}),"@@instructions@@");
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
        player = lower_case(player);
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
    	    case 5:
    	        write("There are no answers in task 5 to review.\n");
    	        return 1;
    	        break;
    	    case 6:
    			switch(answer)
    			{
    				case 1:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 6, question 1:\n"+
    			    		"Given that we are both Elemental Servants and "+
    			    		"Kyrullians, explain to me who the Clerics of this "+
    			    		"Temple are.\n"+
    			    		GUILD_MANAGER->query_task_six_answer_one(player)+"\n");
    					return 1;
    					break;
    				case 2:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 6, question 2:\n"+
    			    		"What behaviour would you expect from such a Cleric?\n"+
    			    		GUILD_MANAGER->query_task_six_answer_two(player)+"\n");
    					return 1;
    					break;
    			    case 3:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 6, question 3:\n"+
    			    		"How do the Clerics handle conflicts internally and "+
    			    		"externally?\n"+
    			    		GUILD_MANAGER->query_task_six_answer_three(player)+"\n");
    					return 1;
    					break;
    				case 4:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 6, question 4:\n"+
    			    		"How do the Clerics approach outsiders?\n"+
    			    		GUILD_MANAGER->query_task_six_answer_four(player)+"\n");
    					return 1;
    					break;
    				case 5:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 6, question 5:\n"+
    			    		"How do the Clerics stand in regards to the moral strifes "+
    			    		"of good and evil?\n"+
    			    		GUILD_MANAGER->query_task_six_answer_five(player)+"\n");
    					return 1;
    					break;
    				case 6:
    					write(capitalize(player)+" gave the following "+
    			    		"answer to task 6, question 6:\n"+
    			    		"How do the Clerics view wars of dominion?\n"+
    			    		GUILD_MANAGER->query_task_six_answer_six(player)+"\n");
    					return 1;
    					break;
    				default:
    					notify_fail("There are only 6 answers for you to view in task 6.\n");
		    			return 0;
		    			break;
		    	}
    		default:
    			notify_fail("Who's task answers would you like to see? view <player> <task#> <answer#>\n");
    			return 0;
    			break;
    	}
    }          
}

public void
init()
{
    ::init();

    add_action("do_sit", "sit");
    add_action("do_stand", "stand");
	add_action("do_open","place");
	add_action("do_ebirth","ebirth");
	add_action("do_elife","elife");
	add_action("do_edeath","edeath");
	add_action("do_view", "view");
}

public int
setroom(int DOOR_STATUS)
{
	door_open = DOOR_STATUS;
}

public int
remex(object THIS_PLAYER)
{
	tell_room(ELEMENTALIST_TEMPLE + "meeting","The door in the western wall slides "
		+ "shut and vanishes from sight.\n");
	tell_room(ELEMENTALIST_TEMPLE + "outer9","The door in the eastern wall slides shut "
			+ "and vanishes from sight.\n");
	remove_exit("west");
	setroom(0);
	(ELEMENTALIST_TEMPLE + "outer9")->remove_exit("east");
	(ELEMENTALIST_TEMPLE + "outer9")->setroom(0);
	return 0;
}

public int
adex(object THIS_PLAYER)
{
	add_exit(ELEMENTALIST_TEMPLE + "outer9","west","@@check_sitting",1);
	setroom(1);
	(ELEMENTALIST_TEMPLE + "outer9")->add_exit(ELEMENTALIST_TEMPLE + "meeting","east");
	(ELEMENTALIST_TEMPLE + "outer9")->setroom(1);
	tell_room(ELEMENTALIST_TEMPLE + "outer9","A door materializes in the eastern wall "
			+ "and slides open.\n");
	set_alarm(6.0,0.0,"remex",THIS_PLAYER);
	return 1;
}

public int
do_open(string arg)
{
	if(door_open)
	{
		write("You put your hand in the indentation on the wall, "
			+ "however the door is already open.\n");
		say(QCTNAME(this_player()) + " places " + TP->query_possessive()
			+ " hand in an indentation on the wall, however the "
			+ "door is already open.\n");
		return 1;
	}

	
	if (!strlen(arg))
	{
		notify_fail("Place what in where?\n");
		return 0;
	}
	
	arg = lower_case(arg);
	
	if (arg != "hand in indentation")
	{
		write("Place what in where?\n");
		return 0;
	}
	else
	{
		if((IS_MEMBER(this_player())) || (GUILD_MANAGER->query_is_ew_council(this_player(), 1)))
		{
			write("You place your hand in the indentation on the wall. There is "
				+ "a surge of energy and a rumble from the wall. A hidden door "
				+ "materializes in the west wall and slides open, allowing "
				+ "passage westwards.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in the indentation on the wall. There is a surge of "
				+ "energy and a rumble from the wall. A hidden door materializes "
				+ "in the west wall and slides open, allowing passage westwards.\n");
			adex(this_player());
			return 1;
		}
		else
		{
			write("You place your hand in the indentation. Nothing happens.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in an indentation on the wall. Nothing happens.\n");
			return 0;
		}
	}
}

public int
do_sit(string str)
{
    if ((!strlen(str)) && (str != "down") && (str != "on couch"))
    {
        notify_fail("Sit where? On the couch? <sit on couch>\n");
        return 0;
    }

    if (this_player()->query_prop(SITTING_ON_COUCH))
    {
        notify_fail("You are already sitting on the couch.\n");
        return 0;
    }

    this_player()->add_prop(SITTING_ON_COUCH, 1);
    write("You sit down on one of the couches. It is so comfortable "+
        "that you just do not want to <stand up>. You think "
          + "it's made out of fur.\n");
    say(QCTNAME(this_player()) + " sits down on one of the couches.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT," is sitting on one of the couches");
    return 1;
}

public int
do_stand(string str)
{
    if ((!strlen(str)) && (str != "up"))
    {
        notify_fail("Stand what? Up? <stand up>\n");
        return 0;
    }

    if (!this_player()->query_prop(SITTING_ON_COUCH))
    {
        notify_fail("You are already standing.\n");
        return 0;
    }

    this_player()->remove_prop(SITTING_ON_COUCH);
    write("It takes every ounce of willpower that you have to stand "+
        "up from the amazingly comfortable couch.\n");
    say(QCTNAME(this_player()) + " stands up.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

public int
check_sitting()
{
    if (!this_player()->query_prop(SITTING_ON_COUCH))
    {
        return 0;
    }
    
    write("You attempt to leave but realize that you are still "+
        "sitting on the couch. You are quickly sucked back into "+
        "the most comfortable couch you have ever sat on.\n");
    say(QCTNAME(this_player()) + " attempts to leave while still sitting on "+
        "the couch but is quickly sucked back into it!\n");
    
    return 1;
}

public int
query_circle_phase()
{
    return circle_phase;
}

public void
remove_circle()
{
    write("The silver illuminated circle glows brightly then explodes into "+
        "tiny particles of light and disappears from view.\n");
    say("The silver illuminated circle glows brightly then explodes into "+
        "tiny particles of light and disappears from view.\n");
    circle_phase = 0;
    circle_room_desc = "";
    return;
}

public int
do_ebirth()
{
    if (!can_use_council_commands())
    {
        return 0;
    }
    
    if (circle_phase)
    {
        write("You cannot use this command while there is an existing circle.\n");
        return 1;
    }
    
    write("You raise your finger to an invisible point in the air.\n");
    say(QCTNAME(TP)+" raises a finger to an invisible point in the air.\n");
    circle_room_desc = ""; 
    circle_phase = 1;
    return 1;
}

public int
do_elife()
{
    if (!can_use_council_commands())
    {
        return 0;
    }
    
    if (!circle_phase)
    {
        write("You cannot use this command when there is not an existing circle. "+
            "(Use <ebirth> to start one)\n");
        return 1;
    }
    
    if (circle_phase != 1)
    {
        write("The circle must be in the <ebirth> phase to use this command.\n");
        return 1;
    }
    
    write("You draw a silver illuminated half-circle with your finger in the air.\n");
    say(QCTNAME(TP)+" draws a silver illuminated half-circle with "+
        TP->query_possessive()+" finger in the air.\n");
    circle_room_desc = "There is a silver illuminated half-circle floating in the air.";
    circle_phase = 2;
    return 1;
}

public int
do_edeath()
{
    if (!can_use_council_commands())
    {
        return 0;
    }
    
    if (!circle_phase)
    {
        write("You cannot use this command when there is not an existing circle. "+
            "(Use <ebirth> to start one)\n");
        return 1;
    }
    
    if (circle_phase != 2)
    {
        write("The circle must be in the <elife> phase to use this command.\n");
        return 1;
    }
    
    write("You complete drawing the silver illuminated circle in the air with your "+
        "finger.\n");
    say(QCTNAME(TP)+" completes drawing the silver illuminated circle in the air with "+
        TP->query_possessive()+" finger.\n");
    circle_room_desc = "There is a silver illuminated circle floating in the air.";
    circle_phase = 3;
    set_alarm(10.0,0.0,&remove_circle());
    return 1;
}
