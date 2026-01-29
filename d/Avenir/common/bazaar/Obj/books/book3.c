 // Parchment     (/d/Avenir/common/bazaar/NPC/waiter.c)
 // creator(s):    Glinda
 // last update:
 // purpose:       An old piece of parchment
 //
 // note:
 // bug(s):
 // to-do:

inherit "/std/scroll";

#define FILE "/d/Avenir/common/bazaar/Obj/books/B3/page"

#include <stdproperties.h>

void
create_scroll()
{
    set_name("parchment");
    add_name(({"log","paper","glinda_parchment"}));
    set_adj("ancient");
    set_short("ancient parchment");
    set_long("It looks like a page from a logbook.\n");

    add_prop(OBJ_I_VALUE, 88);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 79);

   seteuid(getuid());
    set_file(FILE);
}
