inherit "/std/key";
#include "/d/Shire/common/annuminas/key.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("thin");
    set_pshort("small thin keys");

    set_long("It's a small key in the semblance of a leaf.\n");

    set_key(LEAF);
}
