/* key for temple entrance in xak by percy id 0232619232 */


inherit "/std/key";
#include "/d/Krynn/xak/xlocal.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("blue");
    set_pshort("small blue keys");

    set_long("It's a small key made out of steel and plated in platinum!\n");

    set_key(K_TEMPLE);
}
