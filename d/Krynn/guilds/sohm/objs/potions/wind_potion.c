#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("suaco potion");
    set_id_diff(40);
    set_id_long("This brilliant yellow potion is a suaco potion. Wizards "
        + "can use it to cast the scouring wind spell. The potion is made from "
        + "the seaside grass and lots of alcohol.\n");
    set_adj("yellow");
    set_unid_long("This is a strange yellow potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion has a salty smell of the sea. You also "
        + "notice fumes of alcohol, and the smell of the pollen from the " +
          "flowers of seaside grass.\n");
    set_id_taste("The potion tastes strongly of salty alcohol, but you also "
        + "notice the revitalising taste of seaside grass.\n");
    set_unid_smell("The potion has the salty smell of the sea.\n");
    set_unid_taste("The potion tastes strongly of warm alcohol and something a bit " +
        "sandy.\n");

    setup_spell_effect(({"iniksuaco"}), "_suaco_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
