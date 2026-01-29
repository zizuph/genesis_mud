// herb rack key  
// creator(s):     Lilith  1/29/97
// last update: 
// purpose:       for opening the lock on the herb-rack
// bug(s):
// to-do:


inherit "/std/key";

#include "../holm.h"

void
create_key()
{

    set_short("small steel key");
    set_adj(({"small", "steel"}));
    set_name("key");
    set_long("This is a small steel key. It is very shiny "+
        "and slippery with herbal-scented oil.\n");
    add_item("oil", "The oil smells like herbs.\n");

    set_key(HERB_KEY);
}
