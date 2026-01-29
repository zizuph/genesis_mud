#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("ramal");
    set_adj("teal"); 
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(498);

    set_id_long("The smell of this ramal potion is almost too much"
        + " to bear. There is a kind of bubbling movement within the"
        + " teal-coloured liquid, as if the ingredients are working"
        + " almost against one another.\n");
    set_unid_long("This is a reeking teal potion.\n");
    set_id_smell("The potion smells of hideously rotten meat, probably"
        + " due to the pieces of snake skin used to"
        + " make it.\n");
    set_id_taste("The taste of this potion is something like a"
        + " rotten fish stew.\n");
    set_unid_smell("The potion smells profoundly horrible!\n");
    set_unid_taste("The potion tastes sickening.\n");

    setup_spell_effect("yalarochrama", "_ramal_charge", 3);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
