// box_key
//grace aug 1994

inherit "/std/key";
#include "../local.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("dusty");
    set_pshort("small dusty keys");

    set_long("It's a small and dusty key.\n");

    set_key(LOCK_1);
}           


