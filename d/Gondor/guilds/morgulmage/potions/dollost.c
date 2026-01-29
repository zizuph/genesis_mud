#include <poison_types.h>
#include <ss_types.h>
#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("dollost");
    set_adj("golden");
    set_unid_long("This is a strange golden herb wine.\n");
    set_id_long("This is a dollost potion, a poisonous golden wine made "
        + "from madwort.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(432);
    set_id_smell("The potion smells pungently of madwort.\n");
    set_id_taste("The potion tastes pungently of madwort.\n");
    set_unid_smell("The potion smells rather pungent.\n");
    set_unid_taste("The potion tastes rather pungent.\n");

    setup_spell_effect("morsikil", "_dollost_charge", 1);
}

int
query_strength() 
{
    if (query_alco_strength() < 25)
        return 0;

    return min(100, 50 + (query_alco_strength() - 25) * 2);
}
