#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("arhal");
    set_unid_long("This is a strange clear herb potion.\n");
    set_id_long("This clear potion is an arhal potion. Mages "
        + "can use it to cast reveal spells. The potion is made from "
        + "the sage herb and a little alcohol.\n");
    set_adj("clear");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(144);
    set_id_smell("The potion smells pungently of sage. You also " 
        + "notice fumes of alcohol.\n");
    set_id_taste("The potion tastes pungently of sage. You also "
        + "notice fumes of alcohol.\n");
    set_unid_smell("The potion smells pungently of herbs.\n");
    set_unid_taste("The potion tastes pungently of herbs.\n");

    setup_spell_effect("arhalgul", "_arhal_charge", 1);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 20 + (query_alco_strength() - 10) * 4);
}
