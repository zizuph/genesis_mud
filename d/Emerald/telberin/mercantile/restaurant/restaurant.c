inherit "/d/Emerald/std/room";

#include "/d/Emerald/telberin/defs.h"
#include <subloc.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>

#define BUSY "_emerald_i_waiter_busy"
#define TABLE_SUBL1 "one"
#define TABLE_SUBL2 "two"
#define ACTION "_waiter_given_task"

object waiter;

public void sit_down(string str);

void
reset_room()
{
    if (!waiter)
    {
    	setuid();
        seteuid(getuid());
	
        waiter = clone_object(TELBERIN_RESTAURANT_DIR + "waiter");
        
        waiter->move(this_object(), 1);
        tell_room(this_object(), "A waiter arrives.\n");
    }
}    

public object
add_table(string subloc, int size)
{
    object table;

    add_subloc(subloc, this_object());
 
    table = clone_object(TELBERIN_RESTAURANT_DIR + "table");
    table->move(this_object(), subloc);
    table->set_table_size(size);

    return table;
}

public object
query_table(string subloc)
{
    object *inv = all_inventory(this_object());
    int i;

    // The tables will typically be the last items in the room, so 
    // we search in reverse.
    for (i = sizeof(inv) - 1; i >= 0; i--)
    {
        // Perhaps there's a faster check to see if the item is a table?
        if ((inv[i]->query_subloc() == subloc) &&
            wildmatch(TELBERIN_RESTAURANT_DIR + "table#*", file_name(inv[i])))
	{
	    return inv[i];
	}
    }

    return 0;
}

void
create_emerald_room()
{
    set_short("A restaurant");
    set_em_long("A little restaurant\n");

    add_exit("/d/Emerald/azim/workroom", "azim", 0);

    // It's important to clone the tables in reverse order so that table
    // one can be referred to as "first table" for regular commands.
    add_table(TABLE_SUBL2, 3);
    add_table(TABLE_SUBL1, 3);

    clone_object(TELBERIN_RESTAURANT_DIR + "absentee_waiter")->move(this_object(), 1);
    reset_room();
}


public int
sit(string str)
{
    mixed *oblist;

    if (!parse_command(str, all_inventory(), "[down] [at] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        if (!parse_command(str, ({}), "[down] [at] 'table' %w", str) ||
            (member_array(str, query_sublocs()) < 0))
	{
            notify_fail("Sit where?\n");
	    return 0;
	}
    }
    else if (sizeof(oblist) > 1)
    {
        notify_fail("You can only sit at one table at a time.\n");
        return 0;
    }
    else
    {
        str = oblist[0]->query_subloc();
    }

    sit_down(str);
    return 1;
}

public int
stand(string str)
{
    string subloc;

    if (subloc = this_player()->query_subloc())
    {
        write("You stand up from " + (this_player()->query_subloc()) + ".\n");
        say(QCTNAME(this_player()) + " stands up from " +
            (this_player()->query_subloc()) + ".\n");

        this_player()->move(this_object());
	query_table(subloc)->remove_diner(this_player());
	return 1;
    }

    notify_fail("You are not sitting!\n");
    return 0;
}


void
sit_down(string str)
{
    if ((this_player()->query_subloc()) == str)
    {
        write("You are already sitting at "+ str +".\n");
    }
    else
    {
        if (this_player()->query_subloc())
        {
            write("You stand up from " + (this_player()->query_subloc()) +
                " and walk over to " + str + ".\n");
            say(QCTNAME(this_player())+ " stands up from "+
            (this_player()->query_subloc()) +" and walks over to "+str+" .\n");

            this_player()->move(this_object());
        }

	if (query_table(str)->add_diner(this_player()))
	{
            this_player()->move(this_object(), str);
            write("You sit down at " +str+".\n");
            say(QCTNAME(this_player()) +" sits down at " +str+ ".\n");
        }
        else
        {
            write("All the seats around this table are occupied.\n");
	}
    }
}

public string
show_subloc(string subloc, object ob, object for_obj)
{
    object *livings = FILTER_LIVE(subinventory(subloc));

    if (sizeof(livings))
    {
        return capitalize(COMPOSITE_LIVE(livings)) +
            ((sizeof(livings) == 1) ? " is " : " are ") + "sitting " +
            "at "+subloc+".\n";
    }

    return "";
}


public int
subloc_access(string sloc, object ob, string acs, object for_obj)
{
    return 0;
}

int
table_talk(string str)
{
    if (this_player()->query_subloc())
    {
    	int i;
        string subloc = this_player()->query_subloc();
        object *others = subinventory(subloc) - ({ this_player() });

        for(i = 0; i < sizeof(others); i++)
        {
           others[i]->catch_tell((this_player()->query_The_name(others[i])) +
               " quietly says: " + str + "\n");
        }

        write("You quietly say: " + str + "\n");
    }
    else
    {
        write("You are not sitting at a table.\n");
    }

    return 1;
}

void
init()
{
    ::init();
    add_action(sit, "sit");
    add_action(stand, "stand");
    add_action(table_talk, "tsay");
}
