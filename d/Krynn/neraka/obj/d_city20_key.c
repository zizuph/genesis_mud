inherit "/std/key";
#include "../local.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("rusty");
    set_pshort("small rusty keys");

    set_long("It's a small and rusty key made of steel.\n");

    set_key(K_CITY20);
}
