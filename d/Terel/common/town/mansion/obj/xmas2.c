/*
 * 122392 by dust. A Christmas tree for fun.
 */
inherit "std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/dust/button_signatures.h"

#define BSN(s)		break_string(s,70)
#define BSNN(s)		break_string((s)+"\n",70)

#define MAX_ITEMS 20
#define FNAME "/d/Terel/common/town/mansion/obj/xmas2"

string	*items;
int	first,last;

string
decoration()
{
    string temp;
    int i,nexti,nextnexti;

    temp = "This is a green Christmas tree, free for decoration. Read the " +
	"sign next to it to get to know how to do so. ";
    if (first == last)
	return(break_string(temp + 
	    "There's no decoration on the tree. Would you like to " +
	    "add some?\n",70));
    temp = temp + "The tree is decorated with ";
    i = first; nexti = i+1;
    if (nexti == MAX_ITEMS) nexti = 0;
    while (i != last)
    {
	nextnexti = nexti+1;
	if (nextnexti == MAX_ITEMS) nextnexti = 0;
	temp = temp + items[i];
	if (nexti == last)
	    ;
	else if (nextnexti == last)
	    temp = temp + " and ";
	else
	    temp = temp + ", ";
	i = nexti; nexti = nextnexti;
    }
    return (temp + ".\n");
}

add_decoration(string str)
{
    items[last] = str;
    last++;
    if (last == MAX_ITEMS) last = 0;
    if (last == first)
    {
	first++;
	if (first == MAX_ITEMS) first = 0;
    }
}

do_decorate(string str)
{
    int i;

    seteuid(getuid());
    if (strlen(str) > 80) return 0;
    add_decoration(str);
    if (this_player())
    {
	write(break_string("You add " + str + 
	   " to the tree. How nice!\n",70));
	say(break_string(QCTNAME(this_player()) + " adds " + str +
	    " to the tree. How nice!\n",70));
    }
    rm(FNAME);
    i = first;
    while (i != last)
    {
	write_file(FNAME,items[i] + "\n");
	i++;
	if (i == MAX_ITEMS) i=0;
    }
    return 1;
}

start_decoration()
{
    string temp;
    int i;

    seteuid(getuid());
    for (i=0; i<MAX_ITEMS; i++)
    {
	temp = read_file(FNAME,i,1);
	if (strlen(temp) < 4) continue;
	temp = (explode(temp,"\n"))[0];
	add_decoration(temp);
    }
    if (first == last)
    {
	add_decoration("a terellian greeting ball");
	add_decoration("dusty angels hair");
	add_decoration("a request to add more");
    }
}

create_object()
{
    int i;

    items = allocate(MAX_ITEMS);
    first = last = 0;
    set_name("tree");
    add_adj(({"green", "christmas"}));
    set_short("green Christmas tree");
    set_long("@@decoration");
    add_prop(OBJ_I_NO_GET,1);
    start_decoration();
}

init()
{
    ::init();
    add_action("do_decorate","decorate");
    add_action("do_decorate","add");
    add_action("instructions","read");
}

int
instructions(string str)
{
    notify_fail("What you try to read? Maybe the sign?\n");
    if (str != "sign" && str != "instructions" && str != "instruction")
	return 0;
    write(break_string("This Christmas tree is a gift to all mortals " +
	"from the wizards of the Terel domain. Everybody can add any " +
	"decoration he, she or it likes by entering for example " +
	"'add a blue ball' or 'decorate a blue ball'. Everything " +
	"appearing behind the word 'add' or 'decorate' is taken as " +
	"decoration, so don't include anything like 'add tree with ...'. " +
	"Also, don't forget to include an article 'a' or 'an' where " +
	"it's needed, as shown in the examples above. It is not " +
	"possible to remove any decorations added.\n",70));
    return 1;
}

