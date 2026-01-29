#include "../morgulmage.h"
#include <macros.h>

inherit MORGUL_POTION_DIR + "base_potion";

public void
create_morgul_potion()
{
    set_potion_name("nenamarth");
    set_id_long("This yellowish potion is a nenamarth potion, "
      + "the 'Water of Doom'. Mages can use it to cast poison spells. "
      + "The potion is made from the morgurth herb, a part of a corpse, "
      + "and lots of alcohol.\n");
    set_adj(({"yellowish"}));
    set_unid_long("This is a strange yellowish herb poison.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion smells pungently of decay and death. You also " +
        "notice fumes of alcohol and the morgurth herb.\n");
    set_id_taste("The potion tastes pungently of decay and death. You also " +
        "notice fumes of alcohol and the morgurth herb.\n");
    set_unid_smell("The potion smells pungently of death.\n");
    set_unid_taste("The potion tastes pungently of death.\n");

    setup_spell_effect("sulambar", "_nenamarth_charge", 1);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
