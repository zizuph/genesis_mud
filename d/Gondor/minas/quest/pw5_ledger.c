inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h";

#define NO_OF_SUSPECTS  8

void
create_object()
{
    set_name("book");
    add_name("ledger");
    set_short("neat book");
    set_adj("neat");
    add_adj("small");
    set_long("This a small and neat book. Try to read it.\n");

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 650);
    add_prop(OBJ_I_VALUE,   10);
}

void
init()
{
    ::init();
    add_action("do_read", "read");
    add_action("do_read", "open");
}

int
do_read(string str)
{
    int		i;
    string	*suspects,
		book_owner,
		name,
		tmpstr;

    if (!interactive(TP))
    {
        return 1;
    }

    if(!strlen(str) || !id(str))
    {
        NFN0(CAP(query_verb())+" what?");
    }

    book_owner = query_prop(MT_PW5_S_OWNER);
    name = TP->query_real_name();
    if (strlen(book_owner) &&
	book_owner != name)
    {
	if (sscanf(file_name(ENV(TP)), MINAS_DIR+"houses/%s", tmpstr))
	{
	     
	    log_file("murder", ctime(time())+" "+name+
		" tried to read "+
		(strlen(book_owner) ? book_owner : "nobody" )+"'s book.\n");
	}
	write("You cannot decipher the crabbed handwriting.\n");
	return 1;
    }

    FIX_EUID

    suspects = allocate(NO_OF_SUSPECTS);
    MT_PW5_SUSPECT->load_me();
    suspects = MT_PW5_SUSPECT->query_suspect_name(-1);

    write("In the book are a list of names, dates and some numbers. ");
    write("You guess it is some sort of ledger, where transactions ");
    write("are kept. There are several IOU's in here with recent ");
    write("dates. You find some interesting names. ");
    write("Here is a list of them : \n");
    TP->add_prop(MT_PW5_I_FOUND_MOTIVE,
	TP->query_prop(MT_PW5_I_FOUND_MOTIVE) | 2);
    for (i = 0; i < NO_OF_SUSPECTS; i++)   
            write("\t" + suspects[i] + "\n");

    return 1;
}
