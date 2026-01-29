#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("reelojawa potion");
    set_id_diff(40);
    set_id_long("This misty white potion is a reelojawa potion. Enchanters "
        + "can use it to cast the domination spell. The potion is made from "
        + "a hemlock herb, lady slipper orchid and lots of alcohol.\n");
    set_adj("misty");
    add_adj("white");
    set_unid_long("This is a strange misty white potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(2000);
    set_id_smell("This potion has a strong cloying scent of the lady slipper " +
         "orchard.\n");
    set_id_taste("The potion tastes painfully sweet, reminding you of the " +
       "lady slipper orchard. You can also taste traces of the deadly hemlock " +
       "berries.\n");
    set_unid_smell("Alcoholic fumes from the potion burn your nostrils.\n");
    set_unid_taste("The potion tastes strongly of sweet alcohol, and gives you " +
          "a mild headache.\n");

    setup_spell_effect("reelojawa", "_reelojawa_charge", 6);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
