
/* This is an object that allows people to choose attributes from a
 * structured list contained in the PATH + check_attrib object.
 */

#define PATH "/d/Genesis/login/"

inherit "/std/object";
#include "/sys/stdproperties.h"

string *adj;
int adj_count;

void
create_object()
{
    set_name("selector");
    set_short("attribute selector");
    set_long(
"This book allows you to select the TWO most noticeable features of your\n" + 
"person. It hears your commands and acts accordingly. Available commands are:\n\n" +
"list                lists all available attributes\n" +
"list categories     lists the available categories\n" +
"list <category>     lists the available attributes in a certain category\n" +
"show                Shows your current attributes\n" +
"select <attribute>  selects an attribute\n" +
"Examples:\n" +
"    list eyes\n" +
"    select long-legged\n");
    add_prop(OBJ_I_NO_GET, 1);
    set_no_show();
}

void
init()
{
    add_action("list", "list");
    add_action("select", "select");
    add_action("show", "show");
    add_action("read", "read");

    adj_count = 0;
    
    adj = this_player()->query_adj(1);
    this_player() -> remove_adj(adj);
    if (!adj)
	adj = ({ });
    adj += ({ "", "" });
    adj = slice_array(adj, 0, 1);
}

int
read(string str)
{
    write(long());
    return 1;
}

int
list(string str)
{
    call_other(PATH + "check_attrib", "list", str);
    return 1;
}

int
no_leave()
{
    return (adj_count >= 2) ? 0 : 1;
}

int
select(string str)
{
    string *tmp;

    if(call_other(PATH + "check_attrib", "select", str))
    {
	write("You set " + str + " as a personal attribute.\n");
	tmp = this_player()->query_adj(1);
	this_player()->remove_adj(tmp);
	adj[1] = adj[0];
	adj[0] = str;
	if (adj[1] == "")
	    adj[1] = "plain";
	this_player() -> set_adj(adj);
	adj_count++;
    }
    else
	write("Unknown attribute.\n");
    return 1;
}

public int 
show(string str)
{
    write("This is how you look:\n");
    write(this_player()->long() + "\n");
    return 1;
}
