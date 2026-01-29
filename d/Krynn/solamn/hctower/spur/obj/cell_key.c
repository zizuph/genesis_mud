// cell_key
//grace may 1996

inherit "/std/key";
#include "../local.h"

create_key() {
    ::create_key();

    set_name("cell key");
    add_name("key");
    add_name("_cell_key");
    set_adj("small");
    add_adj("iron");
    add_adj("cell");
    set_short("small iron key");
    set_pshort("small iron keys");

    set_long("It's a small iron key.\n");

    set_key(CELL);
}           


