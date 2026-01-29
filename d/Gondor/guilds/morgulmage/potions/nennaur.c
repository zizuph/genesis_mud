#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("nennaur");
    set_adj("ash-grey");
    set_id_long("This ash-grey potion is a nennaur potion, the "
        + "'Water of Fire'. Mages can use it to cast fire spells. "
        + "The potion is made from some ashes, a red pepper, "
        + "and lots of alcohol.\n");
    set_unid_long("This is a strange ash-grey herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(2016);
    set_id_smell("The potion smells pungently of ashes. You also " 
        + "notice fumes of alcohol and the smell of red pepper.\n");
    set_id_taste("The potion tastes pungently of ashes. You also "
        + "notice fumes of alcohol and the smell of red pepper.\n");
    set_unid_smell("The potion smells pungently of ashes.\n");
    set_unid_taste("The potion tastes pungently of ashes.\n");

    setup_spell_effect(({"thunaur","narusse"}), "_nennaur_charge", 30);
}

int
query_strength() 
{
    if (query_alco_strength() < 44)
        return 0;

    return min(100, 50 + (query_alco_strength() - 44) * 10);
}
