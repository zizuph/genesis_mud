/*
 * Spruced up description and gave it a reasonable key name.
 *
 * Mortis 9.2014
 */

inherit "/std/key";

#include "../local.h"

create_key() {
    ::create_key();

    set_adj("bar-motif");
    add_adj(({"bar", "motif", "iron"}));
    set_short("bar-motif iron key");
    set_long("Flat with an ornate, bar-motif handle, this iron key is of "
    + "high quality and construction. It reminds you of jail cell bars.\n");

    set_key("palanthas_jail_key");
}
