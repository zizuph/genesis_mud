#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("ricindenthanus potion");
    set_id_diff(40);
    set_id_long("This purple potion is a ricindenthanus potion. Enchanters "
        + "can use it to cast the psychic blast spell. The potion is made from "
        + "the locoweed herb and lots of alcohol.\n");
    set_adj("purple");
    add_adj("gold-flecked");
    set_unid_long("This is a strange purple potion flecked with gold.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("This potion smells of the hoary flower locoweed and the " +
        "strong fumes of alcohol.\n");
    set_id_taste("The potion tastes strongly of alcohol, but you also "
        + "notice the taste of the locoweed herb.\n");
    set_unid_smell("Alcoholic fumes from the potion burn your nostrils.\n");
    set_unid_taste("The potion tastes strongly of alcohol, and gives you " +
          "a mild headache.\n");

    setup_spell_effect("ricindenthanus", "_ricindenthanus_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
