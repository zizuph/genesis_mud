#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("morgurth");
    set_id_long("This black potion is a morgurth potion. Mages "
        + "can use it to cast poison spells. The potion is made from "
        + "the angurth herb, a body part, and lots of alcohol.\n");
    set_adj("black");
    set_unid_long("This is a strange black herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion smells pungently of decay. You also "
        + "notice fumes of alcohol, the smell of rotten flesh and of "
        + "an angurth herb.\n");
    set_id_taste("The potion tastes pungently of decay. You also "
        + "notice fumes of alcohol, the taste of rotten flesh and of " 
        + "an angurth herb.\n");
    set_unid_smell("The potion smells pungently of decay.\n");
    set_unid_taste("The potion tastes pungently of decay.\n");

    setup_spell_effect("morthul", "_morgurth_charge", 30);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
