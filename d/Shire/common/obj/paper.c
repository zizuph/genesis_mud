/*
 * paper.c
 *
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>

inherit "/std/object";

string msg_text;
string msg_header;

create_object()
{
    set_name("paper");
    add_name("piece");
    add_name("_piece_of_paper_");
    add_adj("piece of");

    set_pname("papers");
    add_pname("pieces");

    set_short("@@my_short");
    set_pshort("pieces of paper");
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_VOLUME, 4);
}

string
query_header()
{
    return msg_header;
}

string
set_header(string str)
{
    msg_header = str;
}

string
query_text()
{
    return msg_text;
}

string
set_text(string str)
{
    msg_text = str;
}

string
my_short()
{
    if (!strlen(msg_text))
	return "piece of paper";
    else
	return "piece of paper with words written on it";
}

string
my_long()
{
    if (!strlen(msg_text))
	return "This is a clear piece of paper.\n";
    else
	return "This is a piece of paper with words written on it.\n"
	    +  "You might read the paper.\n";
}

init()
{
    ::init();
    add_action("do_write", "write");
    add_action("do_write", "inscribe");
/*
    add_action("do_wipe", "wipe");
    add_action("do_wipe", "erase");
*/
    add_action("do_read", "read");
    add_action("do_tear", "tear");
}

int
filter_quill(object ob)
{
    return ob->id("_quill_");
}

int
filter_paper(object ob)
{
    return ob->id("_piece_of_paper_");
}

int
filter_clear(object ob)
{
    return !strlen(ob->query_header());
}

int
do_write(string arg)
{
    string header;
    mixed *obs;
    object ob;
    object *quills;
    object quill;

    notify_fail("Write what?\nSyntax: write <header> on paper\n");

    if (!strlen(arg))
	return 0;

    if (!parse_command(arg, all_inventory(TP), "%s 'on' [the] %i", header, obs))
	return 0;

    obs = NORMAL_ACCESS(obs, "filter_paper", TO);

    if (!sizeof(obs))
	return notify_fail("You must hold a clear paper to write on it.\n");

    obs = filter(obs, "filter_clear", TO);

    if (!sizeof(obs))
	return notify_fail("You can't write over an old note. You might erase "+
	    "the text if you have means for that though.\n");

    ob = obs[0];

    quills = filter(all_inventory(TP), "filter_quill", TO);

    if (!sizeof(quills))
	return notify_fail("You need a quill to write anything on the paper.\n");

    quill = quills[0];

    if (!quill->query_wet())
	return notify_fail("You need to wet the quill in ink first.\n");

    quill->add_dry(1);

    ob->start_writing(header);
    return 1;
}

void
start_writing(string header)
{
    msg_header = header;

    say(QCTNAME(TP) + " starts writing on " + HIS_HER(TP) + " piece of paper.\n");

    write("You start writing on a blank piece of paper.\n");

    write("]");
    msg_text = "";

    input_to("input_text");
}

input_text(string line)
{
    if (line == "~l")
    {
	write("A piece of paper with the header: '" + msg_header + "'.\n");
	write(msg_text);
	write("]");
	input_to("input_text");
	return;
    }

    if (line == "~q")
    {
	write("Writing aborted.\n");
	msg_text = 0;
	msg_header = 0;
	return;
    }

    if (line == "**")
    {
	write("Writing mode ended.\n");
	say(QCTNAME(TP) + " stops writing on " + HIS_HER(TP)
	  + " piece of paper.\n");
	return;
    }

    msg_text += line + "\n";

    write("]");
    input_to("input_text");
}

int
do_read(string arg)
{
    mixed *obs;
    object ob;

    if (!strlen(arg) || !parse_command(arg, ENV(TP), "[the] %i", obs))
	return notify_fail("Read what?\n");

    obs = NORMAL_ACCESS(obs, "filter_paper", TO);

    if (!sizeof(obs))
	return notify_fail("Read what?\n");

    obs->read_text();
    return 1;
}

void
read_text()
{
    if (TP->query_skill(SS_LANGUAGE) < 5 &&
	TP->query_stat(SS_WIS) < 10)
    {
	write("You simply can't comprehend what the paper reads.\n\n");
	say(QCTNAME(TP) + " fails to read the piece of paper.\n");
	return;
    }

    say(QCTNAME(TP) + " reads a piece of paper.\n");

    if (!strlen(msg_header) && !strlen(msg_text))
    {
	write("You see that the paper is not written upon.\n\n");
	return;
    }

    write("You read the piece of paper:\n");
    write("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
    write(sprintf("\\ %-70s /\n", msg_header));
    if (strlen(msg_text)) {
	string *lines = explode(msg_text, "\n");
	int i;
	for (i = 0; i < sizeof(lines); i++)
	{
	    if (i%2) 
		write(sprintf("\\ %-70s /\n", lines[i]));
	    else
		write(sprintf("/ %-70s \\\n", lines[i]));
	}
	if (i % 2 == 0)
	    write(sprintf("/ %-70s \\\n", ""));
    }
    write("\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
}

int
do_tear(string arg)
{
    mixed *what;
    notify_fail("Tear the paper perhaps?\n");

    if (!strlen(arg) || !parse_command(arg, all_inventory(TP), "[the] %i", what))
	return 0;

    what = NORMAL_ACCESS(what, 0, 0);
    what = filter(what, "filter_paper", TO);

    if (!sizeof(what))
	return 0;

    write("You tear apart " + COMPOSITE_DEAD(what) + ".\n");
    say(QCTNAME(TP) + " tears apart " + QCOMPDEAD + ".\n");
    what->remove_object();
    return 1;
}
