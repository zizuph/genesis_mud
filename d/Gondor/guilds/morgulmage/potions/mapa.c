#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("mapa");
    set_adj("green-yellow");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1145);

    set_id_long("This mapa potion has been brewed using the mashed"
        + " remains of handasse mushrooms and some strong liquid."
        + " The result is somewhat oily and unpleasant,"
        + " yet powerful in the right hands.\n");
    set_unid_long("This is a watery green-yellow potion.\n");
    set_id_smell("The potion smells tangy and slightly rotten.\n");
    set_id_taste("The potion tastes somewhat briney, and there"
        + " are small pieces of slimy mushroom in it.\n");
    set_unid_smell("The potion smells unpleasant.\n");
    set_unid_taste("The potion tastes terrible.\n");

    setup_spell_effect("nifarist", "_mapa_charge", 6);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 2);
}
