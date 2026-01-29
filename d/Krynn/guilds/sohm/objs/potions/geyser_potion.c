#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("skaer potion");
    set_id_diff(40);
    set_id_long("This red-brown potion is a skaer potion. Wizards "
        + "can use it to cast the geyser spell. The potion is made from "
        + "the sargassum alga and lots of alcohol.\n");
    set_adj("red-brown");
    set_unid_long("This is a strange red-brown potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion has a salty smell of the sea. You also "
        + "notice fumes of alcohol, and the smell of the sargassum alga.\n");
    set_id_taste("The potion tastes strongly of salty alcohol, but you also "
        + "notice the stringy taste of the sargassum alga.\n");
    set_unid_smell("The potion has the salty smell of the sea.\n");
    set_unid_taste("The potion tastes strongly of warm alcohol and something stringy, " +
        "like seaweed.\n");

    setup_spell_effect(({"skaerenpab"}), "_skaer_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
