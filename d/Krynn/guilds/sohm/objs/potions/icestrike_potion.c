#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("xarzithnar potion");
    set_id_diff(40);
    set_id_long("This frosty white potion is a xarzithnar potion. Wizards "
        + "can use it to cast the ice strike spell. The potion is made from "
        + "the salt wort herb and lots of alcohol.\n");
    set_adj("white");
    add_adj("frosty");
    set_unid_long("This is a strange frosty white potion that is cool to touch.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("Icy alcoholic fumes from the potion freeze your nostrils, "
        + "although you also notice the smell of the salt wort herb.\n");
    set_id_taste("The potion tastes cold and strongly of alcohol, but you also "
        + "notice the taste of the salt wort herb.\n");
    set_unid_smell("Icy alcoholic fumes from the potion freeze your nostrils.\n");
    set_unid_taste("The potion tastes cold and strongly of alcohol.\n");

    setup_spell_effect(({"xarzithnar","kepeskwiivai"}), "_xarzithnar_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
