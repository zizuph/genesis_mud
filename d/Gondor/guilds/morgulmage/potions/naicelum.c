#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("naicelum");
    set_adj("red");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(714);

    set_id_long("The slick and oily consistency of this bright"
        + " red naicelum potion shines almost like polished glass.\n");
    set_unid_long("This is a glistening red potion.\n");
    set_id_smell("The potion smells tart, almost like rhubarb, but"
        + " with a dizzying effect on the brain.\n");
    set_id_taste("The potion stings your tongue terribly as you"
        + " taste it, leaving you feeling almost as if you'd placed"
        + " poisoned oak in your mouth.\n");
    set_unid_smell("The potion smells rather tart.\n");
    set_unid_taste("The potion is painful to taste!\n");

    setup_spell_effect("mordru", "_naicelum_charge", 30);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
