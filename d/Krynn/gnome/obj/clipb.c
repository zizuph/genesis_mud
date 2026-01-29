inherit "/std/object";
 
#include <stdproperties.h> 	/* All prop definitions */
#include <cmdparse.h>		/* The FIND_STR_IN_OBJECT macro */
#include <macros.h>		/* QCTNAME and QTNAME macro */
#include "/d/Krynn/common/defs.h"
#include "../local.h"

int count;
create_object()
{
    set_name("clipboard");
    add_name("board");
    set_adj("gnomish");
    set_short("gnomish clipboard");
    set_long("@@mylong");
    add_item("label", "@@read");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 100);
    count = random(10) + 1;
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("note", "write");
}

note(str)
{
    object ob;

    seteuid(getuid());
    if (strlen(str) > 80)
    {
    	write("You wouldn't be able to fit all that on the paper.\n");
    	return 1;
    }
    if (!count)
    {
    	write("No paper left!  Too bad, it was so useful, too...\n");
    	return 1;
    }
    write("You jot the note and tear the piece of paper off the clipboard.\n");
    say(QCTNAME(TP) + " writes a note on " + TP->query_possessive() +
	" clipboard.\n");
    count--;
    ob = clone_object(OBJ + "note");
    ob->set_long(str + "\n");
    ob->move(TP);
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    	"This product can: 'write'" +
    	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on clipboard")
    {
    	write(read());
	return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}

mylong()
{
    return BS("A remarkably simple device for a gnome to have built.  " +
      	"It consists of a flat piece or hard leather that sheets of paper " +
      	"can be clipped to.  There are currently " + count + " sheets left." +
      	"  A label is stamped onto the clipboard.", 70);
}
