#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("corcosunk");
    set_id_long("This green potion is a corcosunk potion. When quaffed by "
        + "mages who are learnt in the proper spells, it can be used to "
        + "summon birds from the realm of the shadows. It can be mixed "
        + "using an eye, a tuo lichen, a myrtle berry and some alcohol.\n");
    set_adj("green");
    set_unid_long("This is a strange green herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1296);
    set_id_smell("The potion smells slightly of lichen and myrtle berries.\n");
    set_id_taste("The potion tastes slightly of lichen and myrtle berries.\n");
    set_unid_smell("The potion smells of nothing.\n");
    set_unid_taste("The potion tastes of nothing.\n");

    setup_spell_effect("crabandir", "_corcosunk_charge", 2);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 4);
}
