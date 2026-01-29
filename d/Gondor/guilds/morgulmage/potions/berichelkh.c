#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("berichelkh");
    set_id_long("This white potion is a berichelkh potion. Mages can "
        + "use it to protect themselves. The potion is made from the "
        + "frostheal herb and some liquid with a little alcohol in it.\n");
    set_adj("white");
    set_unid_long("This is a strange white herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(864);
    set_id_smell("The potion smells slightly of frostheal.\n");
    set_id_taste("The potion tastes slightly of frostheal.\n");
    set_unid_smell("The potion smells of nothing.\n");
    set_unid_taste("The potion tastes of nothing.\n");

    setup_spell_effect(({"ringurth", "turniawath"}), "_berichelkh_charge", 4);
}

int
query_strength() 
{
    if (query_alco_strength() < 10)
        return 0;

    return min(100, 50 + (query_alco_strength() - 10) * 2);
}
