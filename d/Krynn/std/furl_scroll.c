/*
 * Furlable scroll by Teth Feb 1997
 * Made into a /std/ file by Aridor 06/98
 *
 */

inherit "/std/scroll";
inherit "/lib/keep";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>

int gFurled = 1;


void
set_furled()
{
    gFurled = 1;
    TO->remove_adj("unfurled");
    TO->set_short(0);
    TO->add_adj("furled");
}

void
set_unfurled()
{
    gFurled = 0;
    TO->remove_adj("furled");
    TO->set_short(0);
    TO->add_adj("unfurled");
}

int
query_furled()
{
    return gFurled;
}

string
long()
{
    return (::long() +
	    "It is currently " +
	    (query_furled() ? "" : "un") +
	    "furled.\n");
}

init()
{
    ADA("furl");
    ADA("unfurl");
    ::init();
}

int
furl(string str)
{
    if(id(str))
    {
        if (query_furled())
        {
            write("The " + short() + " is already furled!\n");
            return 1;
        }
        write("You furl the " + short() + ".\n");
        say(QCTNAME(TP) + " furls the " + QSHORT(TO) + ".\n");
        set_furled();
        return 1;
    }
    NF("Furl what?\n");
    return 0;
}

int 
unfurl(string str)
{
    if(id(str))
    {
        if (!query_furled())
        {
            write("The " + short() + " is already unfurled!\n");
            return 1;
        }
        write("You unfurl the " + short() + ".\n");
        say(QCTNAME(TP) + " unfurls the " + QSHORT(TO) + ".\n");
        set_unfurled();
        return 1;
    }
    NF("Unfurl what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (ob->query_furled())
    {
        NF("You can only read unfurled scrolls!\n");
        return 0;
    }
    NF("You must be holding the scroll to read it properly!\n");
    return ((E(ob) == TP) &&
      (function_exists("create_object", ob) == SCROLL_OBJECT));
}

/*
 * Function name: read_it
 * Description  : Perform the actual read. This function prints the text
 *                to the player and displays a message to the people in
 *                the room.
 * Arguments    : string - the command the player executed, only 'read'
 */
void
read_it(string str)
{
    int taskcheck;
    seteuid(getuid(TO));

    if (!scroll_file)
    {
        write("There was nothing to read on the " + QSHORT(TO) + ".\n");
        return;
    }

    if ((str == "read") &&
      (file_size(scroll_file) < 4000))
    {
        write("You read the " + short() + ".\n");
        say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");
        cat(scroll_file);
    }
    else
    {
        if (file_size(scroll_file) >= 50000)
        {
            write("The scroll is too large to be read.\n");
            return;
        }
        TP->more(read_file(scroll_file));
    }
}
