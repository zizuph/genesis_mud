/* The securetool is needed to secure notes on the bulletin boards.
 * Questitem.
 * Created by Dajala    19.06.1995
 * 
 * Cotillion - 2018-10-22
 * - Fixed runtime in switsch
 */

inherit "/std/object";

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/gnome/local.h"

/* defines *BOARD_NAMES which consists of the set_board_name() of
 * five different boards the player has to visit.
 */
#include "/d/Krynn/gnome/schorsch/schorsch.h"


/* Global variables */

int     abort_alarm, pass, add_board_to_list_flag, *board_list,
	*done_flags = allocate(BOARD_NUMBER), break_alarm;
object  owner;

/* Prototypes */

void msg_out(string what);


void
create_object()
{
	set_name("securetool");
	add_name("tool");
	set_adj("handy");
	add_adj("weird");
	add_adj("gnomish");
	set_short("@@sec_adj@@ gnomish securetool");
	set_long("The tool consists of a bulky box with several levers, "
		+ "switches, wheels and buttons arrayed in a seemingly "
		+ "random fashion.\nThere is a label attached to it.\n");
	add_item("label", "There is something written on it.\n");
	add_item(({"button", "buttons", "lever", "levers", "switch", 
		"switches", "wheel", "wheels"}),
		"Although differently coloured, their use it not "
		+ "immidiately apparent.\n");

	add_prop(OBJ_I_WEIGHT, 10000);
	add_prop(OBJ_I_VOLUME, 5000);
	add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
	ADD("switsch", "press");
	ADD("switsch", "pull");
	ADD("switsch", "turn");
	ADD("switsch", "push");
	ADD("switsch", "switch");
	ADD("read_label", "read");
}


int
read_label(string str)
{
	NF("Read what?\n");
	if(str != "label" && str != "label on securetool")
		return 0;
	write("This product of gnomish industries is needed to secure "
		+ "loose notes on bulletin boards.\nUse the following "
		+ "sequence:\n1. Press red button.\n2. Pull blue "
		+ "lever.\n3. Turn yellow wheel.\n4. Switch green switch.\n"
		+ "5. Push green lever.\n6. Switch green switch.\n7. Turn blue "
		+ "wheel.\n8. Pull green lever.\n9. Switch green switch.\n"
		+ "10. Turn yellow wheel.\n");
	return 1;       
}

/* You did the wrong thing.
 */
void
abort(string str)
{
	write("You " + query_verb() + " the " + str + ".\n");
	msg_out(".\n");
	pass = 0;
	tell_room(E(TP), "A bell rings but nothing else happens.\n");
	if(abort_alarm)
		remove_alarm(abort_alarm);
}


/* If you fail to execute the 3 last commands in time you loose the item.
 */
void
break_tool()
{
	write("Oh no!!! You did not reset the tool in time and strained "
		+ "the material too hard. Some parts fell off causing the "
		+ "whole structure to desintegrate to a worthless "
		+ "heap of junk.\n");
	seteuid(getuid());
	clone_object("/d/Krynn/gnome/guild/obj/junk")->move(E(TO), 1);
	remove_object();
}

/* Be quick or start over again. :)
 */
void
too_slow()
{
	E(TO)->catch_msg("A bell rings alarmingly. Something went "
		+ "wrong definitively. Perhaps you worked too slowly?\n");
	tell_room(E(E(TO)), "A bell rings alarmingly.\n", E(TO));
	pass = 0;
}

/* Notes a board as done
 */
void
add_board_to_list(object board)
{
	int i;

	for(i=0;i<BOARD_NUMBER;i++)
	    if(board->query_board_name() == BOARD_NAMES[board_list[i]]) 
	    {
		done_flags[i] = 1;
		return;
	    }
	write("This board wasn't on the list the old gnome had given to "
		+ "you, but never mind...\n");
}

void
receive_exp()
{
	int i, delete_line;
	string *names, *lines;

	for(i=0;i<BOARD_NUMBER;i++)
	    if(!done_flags[i])
		    return;
	write("Well done! That was the last board. You finished "
		+ "your work.\n");
	if(!(TP->test_bit("Krynn", SCHORSCH_GROUP, SCHORSCH_BIT)) 
		&& (owner == E(TO)))
	{
	    write("You feel more experienced.\n");
	    TP->set_bit(SCHORSCH_GROUP, SCHORSCH_BIT);
	    TP->add_exp(SCHORSCH_EXP, 0);
	    write_file(DONE_LOG, extract(ctime(time()), 4, 15) + " "
		+ TP->query_real_name() + ".\n");
	}
	else
	    write("You feel glad having again helped an old fellow in need.\n");
	
	add_prop(OBJ_I_VALUE, 500);

/* The rest is for gnomes only:        
 * If you attacked a gnome, this way you can redeem yourself.
 */
	if(TP->query_race_name() != "gnome")
		return;
	seteuid(getuid());
	lines = explode(read_file(TDIR + "log/fight.log"), "\n");
	for(i=0;i<sizeof(lines);i++)
	{
	    names = explode(lines[i], " ");
	    if(names[0] == TP->short())   /* Attacked a gnome lately */
		delete_line = i + 1;
	}
	if(delete_line)                   /* Lets clear the name */
	{
	    seteuid(getuid());
	    rm(TDIR + "log/fight.log");
	    for(i=0;i<sizeof(lines);i++)
		if(i + 1 != delete_line)
			write_file(TDIR + "log/fight.log", lines[i] + "\n");
	    write("\nToday you have proven yourself "
		+ "worthy of the community of gnomes.\nDespite of your "
		+ "despicable deeds of the past you are granted access "
		+ "to the home of your ancestors again.\n\n");
	}
}

int
board_done(object board)
{
	int i;
	for (i=0;i<BOARD_NUMBER;i++)
	    if(board->query_board_name() == BOARD_NAMES[board_list[i]])
		return done_flags[i];
}

int
switsch(string str)
{
	NF(C(query_verb()) + " what?\n");
	if (!str || !environment(this_player()))
            return 0;

	NF("There is no bulletin board here. Execution automatically "
		+ "aborted.\n");

        object board = present("bulletinboard", environment(this_player()));
        if (!objectp(board))
            return 0;

	NF("You already fixed this board.\n");
	if (board_done(board))
            return 0;

	pass++;
	if(pass == 1)
	{
	    if(str != "red button" || query_verb() != "press")
	    {
		abort(str);
		return 1;
	    }
	    write("You press the red button.\nThe levers, wheels and "
		+ "everything clicks or moves to reset condition.\n");
	    msg_out(".\n");
	    remove_alarm(abort_alarm);
	    abort_alarm = set_alarm(8.0, -1.0, "too_slow");
	}

	if(pass == 2)
	{
	    if(str != "blue lever" || query_verb() != "pull")
	    {
		abort(str);
		return 1;
	    }
	    write("You pull the blue lever.\nSomething inside the "
		+ "securetool moves.\n");
	    msg_out(".\n");
	    remove_alarm(abort_alarm);
	    abort_alarm = set_alarm(8.0, -1.0, "too_slow");
	}
	if(pass == 3)
	{
	    if(str != "yellow wheel" || query_verb() != "turn")
	    {
		abort(str);
		return 1;
	    }
	    write("You turn the yellow wheel and a shutter opens.\n");
	    msg_out(" and a shutter opens.\n");
	    remove_alarm(abort_alarm);
	    abort_alarm = set_alarm(8.0, -1.0, "too_slow");
	}
	if(pass == 4)
	{
	    if(str != "green switch" || query_verb() != "switch")
	    {
		abort(str);
		return 1;
	    }
	    write("Click!\n");
	    msg_out(".\n");
	    remove_alarm(abort_alarm);
	    abort_alarm = set_alarm(8.0, -1.0, "too_slow");
	}
	if(pass == 5)
	{
	    if(str != "green lever" || query_verb() != "push")
	    {
		abort(str);
		return 1;
	    }
	    write("You push the green lever and the tool produces a "
		+ "flexible arm.\n");
	    msg_out(" and a flexible arm appears.\n");
	    remove_alarm(abort_alarm);
	    abort_alarm = set_alarm(8.0, -1.0, "too_slow");
	}
	if(pass == 6)
	{
	    if(str != "green switch" || query_verb() != "switch")
	    {
		abort(str);
		return 1;
	    }
	    write("Click!\n");
	    msg_out(".\n");
	    remove_alarm(abort_alarm);
	    abort_alarm = set_alarm(8.0, -1.0, "too_slow");
	}
	if(pass == 7)
	{
	    if(str != "blue wheel" || query_verb() != "turn")
	    {
		abort(str);
		return 1;
	    }
	    write("You turn the blue wheel.\nThe arm moves and hits the "
		+ "nail of a note which was about to fall from the "
		+ "board.\n");
	    msg_out(".\nSuddenly the flexible arm hits the nail of a note "
		+ "which has come loose.\n");
	    remove_alarm(abort_alarm);
	    break_alarm = set_alarm(30.0, -1.0, "break_tool");
	    if(random(3))
	    {
		write("Good job! There are no more notes which are loose "
			+ "on this board.\n");
		add_board_to_list_flag = 1;
	    }
	    else
		write("Good job so far, but there are still some loose notes on this "
			+ "board. You should fix them as well.\n");
	}
	if(pass == 8)
	{
	    if(str != "green lever" || query_verb() != "pull")
	    {
		abort(str);
		return 1;
	    }
	    write("You push the green lever.\n"
		+ "The flexible arm retracts.\n");
	    msg_out(" and the flexible arm retracts.\n");
	    remove_alarm(break_alarm);
	    break_alarm = set_alarm(30.0, -1.0, "break_tool");
	}
	if(pass == 9)
	{
	    if(str != "green switch" || query_verb() != "switch")
	    {
		abort(str);
		return 1;
	    }
	    write("Click!\n");
	    msg_out(".\n");
	    remove_alarm(break_alarm);
	    break_alarm = set_alarm(30.0, -1.0, "break_tool");
	}
	if(pass == 10)
	{
	    if(str != "yellow wheel" || query_verb() != "turn")
	    {
		abort(str);
		return 1;
	    }
	    write("You turn the yellow wheel.\nThe shutter closes "
		+ "again and a buzzing sound indicates successful "
		+ "completion.\n");
	    if(!random(3))
		write("Isn't science wonderful?\n");
	    msg_out(" causing a shutter to close and a buzzer to sound.\n");
	    if(add_board_to_list_flag)
	    {
		add_board_to_list(board);
		add_board_to_list_flag = 0;
	    }
	    remove_alarm(break_alarm);
	    pass = 0;
	    receive_exp();
	}
	return 1;
}

string
sec_adj()
{
	if(TP->query_race_name() == "gnome")
		return "handy";
	return "weird";
}

/* What others see.
 * Gnomes like the tool: 'handy' others see 'weird' :)
 */
void
msg_out(string what)
{
	int i;
	object *player;

	player = all_inventory(E(TP));
	for(i=0;i<sizeof(player);i++)
	{
	    if(living(player[i]) && player[i] != TP)
	    {
		player[i]->catch_msg(QCTNAME(TP) + " does something to a "); 
		if(player[i]->query_race_name() == "gnome")
			player[i]->catch_msg("handy");
		else
			player[i]->catch_msg("weird");
		player[i]->catch_msg(" tool" + what); 
	    }
	}
}

void
set_owner(int *list)
{
	owner = E(TO);
	board_list = list;
}

void
pat_tool()
{
	int i;
	for(i=0;i<BOARD_NUMBER;i++)
	  done_flags[i] = 1;
}
