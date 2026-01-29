/* created by Aridor 06/19/93 */

#include "../local.h";

inherit LIV + "clerk_base.c";

void
create_clerk()
{
    set_name("erland");
    set_race_name("dwarf");
    set_adj("long-bearded");

    set_long("This dwarf is busy writing and sorting through his files.\n");

    set_stats(({80, 54, 85, 50, 51, 70}));
    set_hp(4000);

    set_my_signature("Erland (Office N-Z)");
    set_invalid_signature("Uland (Office A-M)");
}
