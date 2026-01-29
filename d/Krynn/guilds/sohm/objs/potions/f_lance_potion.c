#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("ixenner potion");
    set_id_diff(40);
    set_id_long("This golden potion is an ixenner potion. Wizards "
        + "can use it to cast the flame lance spell. The potion is made from "
        + "the hawthorn herb and lots of alcohol.\n");
    set_adj("golden");
    set_unid_long("This is a strange golden potion that is warm to touch.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion has a warm scent of mulled berries. You also "
        + "notice fumes of alcohol, and the smell of the hawthorn herb.\n");
    set_id_taste("The potion tastes strongly of warm alcohol, but you also "
        + "notice the taste of the hawthorn herb.\n");
    set_unid_smell("The potion has a warm scent of mulled berries.\n");
    set_unid_taste("The potion tastes strongly of warm alcohol.\n");

    setup_spell_effect(({"ixenner","ixengarmth","virednith"}), "_ixenner_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
