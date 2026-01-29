#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("shochraos potion");
    set_id_diff(40);
    set_id_long("This azure blue potion is a shochraos potion. Wizards "
        + "can use it to cast lightning bolt spells. The potion is made from "
        + "the bur reed herb and lots of alcohol.\n");
    set_adj("azure");
    set_unid_long("This is a strange azure blue potion that buzzes with latent energy.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion has the sharp, fresh aroma of the air " +
       "just before a storm. You also "
        + "notice fumes of alcohol, and of the bur reed herb.\n");
    set_id_taste("The potion zings on your tongue with electrical energy. You also "
        + "notice fumes of alcohol and the taste of a bur reed herb.\n");
    set_unid_smell("The potion has the sharp, fresh aroma of the air just before a storm.\n");
    set_unid_taste("The potion zings on your tongue with electrical energy.\n");

    setup_spell_effect(({"shochraos", "ganimshochraos", "suacodrevab" }), 
        "_shochraos_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
