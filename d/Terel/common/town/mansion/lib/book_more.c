/*	An object for reading the books in the Terelian library.
 *	Copied from /std/board_more.c (anonymous) and only 
 *	slightly altered.
 *				Cedric  10-14-92
 */



#define PAGESIZE  20
#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
string *lines;
int lineno, sz, pagesize;

int
get() {
    return 0;
}

int
drop() {
    return 1;
}

int
query_weight()
{
    set_name("bookreader");
    add_prop(OBJ_I_WEIGHT, 1); /* 1 g */
    add_prop(OBJ_I_VOLUME, 1); /* 1 ml */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
    add_prop(OBJ_M_NO_DROP, 1); /* Call drop when property tested */
    set_short("foobar object");
    set_long("The hidden tool for doing 'more' on books.\n");
    set_no_show();
}

int
qmore(string answer) {
    int i, cnt;
    
    answer = lower_case(answer);
    if (answer == "q") {
	remove_object();
	return 1;
    }
    
    if (answer == "?" || answer == "help") {
	tell_object(environment(this_object()),
		    "Available commands:\n<cr>, t(op), b(ack one page), r(edisplay page), <line number>, q(uit)\n");
	input_to("qmore");
	return 1;
    }
    switch (answer)
    {
    case "t":
    case "top":
	lineno = pagesize;
	break;
    case "":
	lineno += pagesize;
	break;
    case "b":
    case "back":
    case "p": 
	lineno -= pagesize;
    }	
    if (answer && sscanf(answer, "%d", cnt) == 1) 
	lineno = cnt - 1 + pagesize;
    
    if (lineno < pagesize)
	lineno = pagesize;
    
    for (i = lineno - pagesize; i < lineno && i < sz; i++)
	write(lines[i] + "\n");
    if (lineno > sz)
    {
	remove_object();
	return 1;
    }
    else
    {
	tell_object(environment(this_object()), "More: --" + lineno + "-- (<cr>,t,b,r,<num>,q,?)");
	input_to("qmore");
    }
    return 1;
}

int
more(string arg) {
    pagesize = PAGESIZE;
    lines = explode(arg, "\n");
    sz = sizeof(lines);
    lineno = 0;

    qmore("");
    return 1;
}
