/* key for crypt entrance by percy id 0232773270 */


inherit "/std/key";
#include "/d/Krynn/solace/graves/local.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("black");
    set_pshort("small black keys");

    set_long("It's a small key made out of black bone.\n");

    set_key(K_HOLE1);
}
