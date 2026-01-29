#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("vial of minotaur blood");
    set_id_diff(30);
    set_id_long("This dark-red potion is a vial of minotaur blood. Wizards "
        + "can use it to cast the mage strength spell.\n");
    set_adj("dark-red");
    set_unid_long("This dark-red potion is a vial of minotaur blood.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(200);
    set_id_smell("This potion smells strongly of iron and blood. And a little bit " +
         "like cow.\n");
    set_id_taste("The potion tastes of blood, with strong flavours of iron and salt.\n");
    set_unid_smell("This potion smells strongly of iron and blood.\n");
    set_unid_taste("The potion tastes like blood.\n");

    setup_spell_effect("hewavers", "_hewavers_charge", 1);

}

int
query_strength() 
{
    return 100;
}
