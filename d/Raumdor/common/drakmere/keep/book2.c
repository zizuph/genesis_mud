#include "defs.h"
inherit "/std/object";

/* by Sarr */

void
create_object()
{
    set_name("_raumdorbook_");
    add_name("book");
    set_adj("black");
    set_short("black book");
    set_long("It is a large black book. On the cover, writen in red "+
    "letters is: The History of Raumdor.\n");
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
    add_prop(OBJ_I_VALUE,2);
}

void
init()
{
    ::init();
    add_action("do_read", "read");
}

int
do_read(string str)
{
    string fn;
    NF("Read what?\n");
    if(!str)
       return 0;
    if(str == "black book" || str == "book")
    {
        seteuid(getuid());
        fn = read_file("/d/Raumdor/common/drakmere/keep/BOOK2");
        TP->more(fn,0);
        return 1;    
    }
    return 0;
}

