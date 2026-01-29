#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define WRITING		(SAVINGS + "tablet_writing")

public int num_pages = 50;


public string
writing(void)
{
    if (file_size(WRITING) <= 0)
	return 0;

    return read_file(WRITING);
}

public string
tablet_writing(void)
{
    if (file_size(WRITING) <= 0)
	return "The top page of the tablet is blank.\n";

    return "The top page of the tablet reads:\n\n" + writing() + "\n";
}

public string
tablet_long(void)
{
    if (num_pages <= 0)
	return "It is a tablet from which all the pages have been torn.\n";

    return "It is a tablet of soft white vellum, perfectly square.\n"+
	tablet_writing();
}

public void
create_object(void)
{
    reset_euid();

    set_name(({"tablet", "pad"}));
    set_short("tablet of soft vellum");
    set_pshort("tablet of soft vellum");

    set_long(tablet_long);

    add_cmd_item(({"tablet","pad","paper","writing","vellum"}),
	"read", writing);
}

public int
write_message(string str)
{
    string wrt;

    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    NF(CAP(query_verb()) + " on what?\n");
    if (!parse_command(str, TP, "[on] [the] 'tablet' / 'pad'"))
	return 0;

    NF("There are no pages left on the tablet.\n");
    if (num_pages <= 0)
	return 0;

    NF("You would need a pen before you can write anything.\n");
    if (!present("pen", TP))
	return 0;

    NF("There is already writing on the top page of the tablet.\n"+
	"You would need to tear it off before you can write "+
	"something new.\n");
    if (writing())
	return 0;

    say(QCTNAME(TP) +" begins writing something on the tablet.\n");
    write("Enter your message (** to finish):\n");
    write("]");
    input_to("write_page");

    return 1;
}

public void
write_page(string str)
{
    if (str == "**")
    {
	write("You finish writing upon the tablet.\n");
	say(QCTNAME(TP) +" finishes writing upon the tablet.\n");
	return;
    }

    if (str == "~l")
    {
	write(read_file(WRITING) + "\n]");
	input_to("write_page");
	return;
    }

    write("]");
    write_file(WRITING, str + "\n");
    input_to("write_page");
}

public int
tear_page(string str)
{
    string wrt;
    object paper;

    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    NF(CAP(query_verb()) + " what from the tablet?\n");
    if (!parse_command(str, TP, "[a] / [the] 'page' / 'piece' / "+
	    "'paper' / 'vellum' [of] [paper] / [vellum] [from] "+
	    "[the] [tablet] / [pad]"))
	return 0;

    if (num_pages <= 0)
    {
	notify_fail("There are no pages left in the pad.\n");
	return 0;
    }

    wrt = writing();

    paper = clone_object("/std/object");
    paper->set_name(({ "paper", "piece", "vellum", "page" }));
    paper->set_adj(({ "soft", "white", "vellum", "writing", "union" }));
    paper->add_prop(OBJ_I_WEIGHT, 10);
    paper->add_prop(OBJ_I_VOLUME, 10);
    paper->add_prop(OBJ_I_VALUE, 1);

    if (!strlen(wrt))
    {
	paper->set_short("piece of blank vellum");
	paper->set_pshort("pieces of blank vellum");
	paper->set_long("It is a blank piece of soft white vellum, "+
	    "torn from a tablet.\n");
	paper->add_cmd_item(({"paper","writing","vellum","piece","page"}),
	    "read", "The piece of vellum is blank.\n");
    }
    else
    {
	paper->set_short("piece of soft white vellum");
	paper->set_pshort("pieces of soft white vellum");
	paper->set_long("It is a piece of soft white vellum, torn from "+
	    "a tablet. There is some writing on the page.\n");
	paper->add_cmd_item(({"paper","writing","vellum","piece","page"}),
	    "read", "The page of vellum reads:\n" + wrt + "\n");
	//
	// delete the writing file, so someone else can write on the tablet
	rm(WRITING);
    }

    paper->move(TP);
    num_pages--;

    write("You tear "+ LANG_ASHORT(paper) +" from the tablet.\n");
    say(QCTNAME(TP) +" tears "+ LANG_ASHORT(paper) +" from a tablet.\n");
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(write_message, "write");
    add_action(tear_page,     "tear");
}
