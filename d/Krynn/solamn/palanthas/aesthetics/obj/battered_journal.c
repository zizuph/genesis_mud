/* Battered journal that provides hints to WoHS or SoHM spell locations
 */

inherit "/std/scroll";
inherit "/lib/keep";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

#define SCROLLFILE "/d/Krynn/solamn/palanthas/aesthetics/obj/journal.txt"
#define SCROLL_I_FURLED "_scroll_i_furled"


void
create_scroll()
{
    set_name("journal");
    add_name("_wohs_battered_journal");
    set_pname("journals");
    add_adj("battered");
    set_short("battered journal");
    add_adj("closed");
    set_long("A small battered journal. It is currently closed, " +
        "although you could always open it if you wanted to read it.\n");
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 50 + (random(50)));
    add_prop(SCROLL_I_FURLED, 1);

    set_file(SCROLLFILE);
}

init()
{
    ADA("open");
    ADA("close");
    ::init();
}

int close(string str)
{
    if((str=="journal")||(str=="battered journal"))
    {
        if (TO->query_prop(SCROLL_I_FURLED))
        {
            write("The " + query_short() + " is already closed!\n");
            return 1;
        }
        write("You close the " + query_short() + ".\n");
        say(QCTNAME(TP) + " closes the " + QSHORT(TO) + ".\n");
        TO->add_prop(SCROLL_I_FURLED, 1);
        TO->remove_adj("open");
        TO->add_adj("closed");
        TO->set_long("A small battered journal. It is currently closed, " +
            "although you could always open it if you wanted to read it.\n");
        return 1;
    }
    NF("Close what?\n");
    return 0;
}

int open(string str)
{
    if((str=="journal")||(str=="battered journal"))
    {
        if (!(TO->query_prop(SCROLL_I_FURLED)))
        {
            write("The " + query_short() + " is already open!\n");
            return 1;
        }
        write("You open the " + query_short() + ".\n");
        say(QCTNAME(TP) + " opens the " + QSHORT(TO) + ".\n");
        TO->remove_prop(SCROLL_I_FURLED);
        TO->remove_adj("closed");
        TO->add_adj("open");
        TO->set_long("A small battered journal, currently open. You " +
            "notice only one page remains with any notes on it that " +
            "you could read.\n");
        return 1;
    }
    NF("Open what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (ob->query_prop(SCROLL_I_FURLED))
    {
        NF("You can only read the battered journal when it is open!\n");
        return 0;
    }
    NF("You must be holding the journal to read it properly!\n");
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
            write("The battered journal is too large to be read.\n");
            return;
        }
        TP->more(read_file(scroll_file));
    }
}
