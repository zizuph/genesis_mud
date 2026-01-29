/*
 * ATOME.c
 * Tome resting on the top of the coffin in the tomb in
 * the emerald graveyard. (atomb.c)
 * 
 * by Alaron July 30, 1996
 */

#include "../default.h"

#define TOME_FILENAME "/d/Emerald/kroad/graveyard/TOME_TEXT"

inherit "/std/object";

int open = 0;

string
open_desc()
{
    if (open) 
	return "The ancient tome lies open to a bloody, crinkled page.\n";
    else
	return "The ancient tome is closed.\n";
}

void
create_object()
{
    set_name("tome");
    set_adj("ancient");
    add_adj("blood-encrusted");

    set_short("ancient, blood-encrusted tome");

    set_long("It is an ancient book, the tough hide binding coming "+
	     "off at the seams. It is covered with several layers "+
	     "of crusted blood, each having a different shade "+
	     "of crimson than the others, possibly meaning that "+
	     "more than one race spilled blood onto the cover "+
	     "of this text. In the center of the front of the tome there "+
	     "is a large silver symbol sewn onto it. On either side "+
	     "of the silver symbol are the thick, black tusks of some "+
             "kind of wild boar.\n@@open_desc@@\n");

    add_item( ({"symbol", "silver symbol"}),
	     "It is a large silver symbol. It forms a winding circle "+
	     "with a large, curved shape through the middle that "+
	     "looks almost like a fang or a tooth of some kind.\n");

    add_item( ({"pages", "page"}),
	     "The pages are made out of a strange material... It is "+
	     "very dry and brittle and very, very flaky... Unusually "+
	     "flaky even for an ancient tome... You then realize that "+
	     "the material the dried skin of a human. The words upon "+
             "the pages have been written in blood!\n");


    add_prop(OBJ_M_NO_GET,"You consider taking it, but it would probably "+
	     "crumble in your hands if you picked it up.\n");

    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 1000);

}

init()
{
    ::init();
    add_action("open_tome", "open");
    add_action("read_tome", "read");
    add_action("close_tome", "close");
}

int
close_tome(string str)
{
    if (!str) return 0;

    if ( (str!="tome") && (str!="blood-encrusted tome")
	&& (str!="ancient tome"))
    {
	notify_fail("Close what?\n");
	return 0;
    }

    if (!open)
    {
	notify_fail("The tome is not open.\n");
	return 0;
    }

    open = 0;

    write("You carefully shut the blood-stained cover of the tome.\n");
    say(QCTNAME(this_player())+" carefully shuts the blood-stained "+
	"cover of the tome.\n");

    return 1;
}

int
open_tome(string str)
{
    if (!str) return 0;

    if ( (str!="tome") && (str!="blood-encrusted tome")
	&& (str!="ancient tome"))
    {
	notify_fail("Open what?\n");
	return 0;
    }

    if (open)
    {
	notify_fail("The ancient tome is already open.\n");
	return 0;
    }

    open = 1;

    write("You carefully pull back the bloody cover of the ancient "+
	  "tome and open it to the first page.\n");
    say(QCTNAME(this_player())+" carefully pulls back the bloody cover "+
       "of the ancient tome and opens it to the first page.\n");
    return 1;
}

int
read_tome(string str)
{
    if (!str) return 0;

    if ( (str!="tome") && (str!="ancient tome") &&
	(str!="blood-encrusted tome"))
    {
	notify_fail("Read what?\n");
	return 0;
    }

    if (!open)
    {
        write("The tome needs to be opened to be read.\n");
	return 1;
    }

    write("It looks like the writing in the tome is wavering, fading "+
          "from sight, as if it is resisting being read ... Perhaps "+
          "it may re-appear sometime in the future?\n");
      return 1;
    seteuid(getuid());
    this_player()->more(read_file(TOME_FILENAME));
    say(QCTNAME(this_player())+" examines the words in the ancient "+
	"tome, reading closely.\n");

    return 1;
}





