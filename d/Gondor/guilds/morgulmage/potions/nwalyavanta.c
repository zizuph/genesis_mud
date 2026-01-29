#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("nwalyavanta");
    set_adj("purple");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1596);

    set_id_long("You mark this mixture as having the unmistakable"
        + " colour of a nwalyavanta potion. The originally brightly"
        + " hued foxglove blossoms have been bruised and then melted"
        + " with a mixture of mushrooms and strong drink. The result"
        + " is like a dull purple soup.\n");
    set_unid_long("This is a dull purple potion.\n");
    set_id_smell("The potion has almost no smell at all. Persistent"
        + " exposure, however, does reveal a mild swampy aroma.\n");
    set_id_taste("The potion tastes bland, with a very slight"
        + " sweetness reminiscent of rotten vegetation.\n");
    set_unid_smell("The potion has almost no smell.\n");
    set_unid_taste("The potion is extremely bland to taste.\n");

    setup_spell_effect("gostangwedh", "_nwalyavanta_charge", 6);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 2);
}
