/* key for Vkeep tower entrance by percy id 02321111 */


inherit "/std/key";
#include "../local.h"
#include "../guild.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("iron");
    set_pshort("small iron keys");

    set_long("It's a small key made out of iron.\n");

    set_key(KEEPKEY);
}
