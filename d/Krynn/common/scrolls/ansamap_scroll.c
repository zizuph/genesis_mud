/* Ansalon map done by Rastlin
 * added as a scroll available by Teth Feb 1997
 */

inherit "/std/scroll";
inherit "/lib/keep";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>

#define SCROLLFILE KRSCROLL + "ansalon.map"
#define SCROLL_I_FURLED "_scroll_i_furled"

void
create_scroll()
{
    set_name("map");
    add_name("scroll");
    set_pname("maps");
    add_pname("scrolls");
    set_adj("aged");
    set_short("furled aged map");
    add_adj("furled");
    set_pshort("aged maps");
    set_long("This aged map is currently furled.\n");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 50 + (random(50)));
    add_prop(SCROLL_I_FURLED, 1);

    set_file(SCROLLFILE);
}

init()
{
    ADA("furl");
    ADA("unfurl");
    ::init();
}

int furl(string str)
{
    if((str=="map")||(str=="aged map")||
      (str=="scroll")||(str=="aged scroll"))
    {
        if (TO->query_prop(SCROLL_I_FURLED))
        {
            write("The " + query_short() + " is already furled!\n");
            return 1;
        }
        write("You furl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " furls the " + QSHORT(TO) + ".\n");
        TO->add_prop(SCROLL_I_FURLED, 1);
        TO->remove_adj("unfurled");
        TO->set_short("furled aged map");
        TO->add_adj("furled");
        TO->set_long("This aged map is currently furled.\n");
        return 1;
    }
    NF("Furl what?\n");
    return 0;
}

int unfurl(string str)
{
    if((str=="map")||(str=="aged map")||
      (str=="scroll")||(str=="aged scroll"))
    {
        if (!(TO->query_prop(SCROLL_I_FURLED)))
        {
            write("The " + query_short() + " is already unfurled!\n");
            return 1;
        }
        write("You unfurl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " unfurls the " + QSHORT(TO) + ".\n");
        TO->remove_prop(SCROLL_I_FURLED);
        TO->remove_adj("furled");
        TO->set_short("unfurled aged map");
        TO->add_adj("unfurled");
        TO->set_long("This unfurled map is a map of Ansalon!\n");
        return 1;
    }
    NF("Unfurl what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (ob->query_prop(SCROLL_I_FURLED))
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
        write("You read the " + query_short() + ".\n");
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
