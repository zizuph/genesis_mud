#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("hexlith potion");
    set_id_diff(40);
    set_id_long("This roiling black potion is a hexlith potion. Wizards "
        + "can use it to cast Doom Blast spells. The potion is made from "
        + "the skullcap mushroom and lots of alcohol.\n");
    set_adj("black");
    set_unid_long("This is a strange roiling black potion that looks like it could " +
        "explode out of the vial like a volcano.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion has the foul, toxic smell of sulfur. You also "
        + "notice fumes of alcohol, and the decaying smell of skullcap mushroom.\n");
    set_id_taste("The potion tastes toxic and foul. You also "
        + "notice fumes of alcohol and the rotting taste blackcap mushroom.\n");
    set_unid_smell("The potion has the foul, toxic smell of sulfur.\n");
    set_unid_taste("The potion tastes toxic and foul.\n");

    setup_spell_effect(({"hexlithdrevab"}), "_hexlith_charge", 12);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
