inherit "/std/object";
#include "/d/Raumdor/defs.h"

/* The Necronomicon */

void
create_object()
{
    set_name("book");
    set_adj(({"black","worm-ridden"}));
    set_long("This is an old, falling apart book. Its pages are torn "+
    "and yellow with decay. Upon its black over you see printed in "+
    "archaic writing, 'The Necronomicon'.\n");
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,40);
}

int
read_book(string str)
{
    NF("Read what?\n");
    if(str != "book")
        return 0;
    write("You do not understand the archaic writing in the "+short()+".\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(read_book,"read");
}

