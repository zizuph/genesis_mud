#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("canwa");
    set_adj("brown");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1164);

    set_id_long("You recognize this mixture as a canwa potion. Brown,"
        + " and smelling mildly of vinnegar, its liquid has a smooth"
        + " and velvety quality that leaves a film on anything it might"
        + " touch.\n");
    set_unid_long("This is a thick brown potion.\n");
    set_id_smell("Beneath the strong acidic fumes of the vinnegar-like"
        + " alcohol, there is an earthy smell to this potion, as of"
        + " certain kinds of fungi.\n");
    set_id_taste("The potion coats your tongue as you taste it, leaving"
        + " behind hints of mushroom once the fumes of vinnegar"
        + " disperse.\n");
    set_unid_smell("The potion smells strongly of vinnegar.\n");
    set_unid_taste("The potion tastes strongly of vinnegar.\n");

    setup_spell_effect("naro", "_canwa_charge", 10);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 2);
}
