/* The young knight in the Library. */

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit M_FILE

create_monster()
{
    set_name("grook");
    add_name("pig_gnome");
    set_extra_long("He has a pigeon on his shoulder. He looks very happy.\n");
    set_race_name("gnome");
    set_adj("small");
    default_config_mobile(50);
    set_all_attack_unarmed(50, 50);
    set_all_hitloc_unarmed(50);

    set_alignment(300);
    set_knight_prestige(-6);

    add_item("pigeon", "It looks like if it is talking to the gnome.\n");

    ALWAYSKNOWN;
    ::create_monster();
}


