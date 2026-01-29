#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("taltambar");
    set_adj(({ "pale", "green" }));
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1410);

    set_id_long("Suspended remnants of pulverized lichen and the"
        + " skins of small berries float lightly in the otherwise"
        + " clear fluid of this taltambar potion, giving it"
        + " its pale green hue.\n");
    set_unid_long("This is fragrant pale green potion.\n");
    set_id_smell("The potion, at first, has a sweet fragrance. It"
        + " quickly turns to a dreadful burning sensation within"
        + " the nose that erases all pleasant thoughts.\n");
    set_id_taste("The potion tastes tart, almost like an apple, but"
        + " has the sting of a strong raw onion.\n");
    set_unid_smell("The potion smells confusing.\n");
    set_unid_taste("The potion tastes strong.\n");

    setup_spell_effect("faugoroth", "_taltambar_charge", 20);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 2);
}
