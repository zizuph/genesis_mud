/* created by Aridor 06/19/93 */

#include "../local.h";

inherit LIV + "clerk_base.c";


void
create_clerk()
{
    set_name("uland");
    set_race_name("elf");
    set_adj("pointy-eared");

    set_long("This elf is busy writing and sorting through his files.\n");

    set_stats(({50, 74, 65, 70, 81, 50}));
    set_hp(3000);

    set_my_signature("Uland (Office A-M)");
    set_invalid_signature("Erland (Office N-Z)");

}


