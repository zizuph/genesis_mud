#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("lominen");
    set_id_long("This silvery potion is a lominen potion. Mages can "
        + "use it to enter the realm of shadows. The potion is made from "
        + "some liquid with some alcohol in it, a curugwath herb, and a "
        + "mushroom.\n");
    set_adj("silvery");
    set_unid_long("This is a strange silvery herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(720);
    set_id_smell("The potion smells like a mushroom.\n");
    set_id_taste("The potion tastes like a mushroom.\n");
    set_unid_smell("The potion smells of nothing.\n");
    set_unid_taste("The potion tastes of nothing.\n");

    setup_spell_effect("artirith", "_lominen_charge", 5);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 2);
}
