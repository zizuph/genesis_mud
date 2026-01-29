#include "/d/Krynn/guilds/sohm/defs.h"
#include <macros.h>

inherit SOHM_OBJS + "potions/base_potion";

public void
create_sohm_potion()
{
    set_potion_name("vistoma potion");
    set_id_diff(40);
    set_id_long("This deep purple potion is a vistoma potion. Diviners "
        + "can use it to cast the true sight spell. The potion is made from "
        + "the crocus flower and lots of alcohol.\n");
    set_adj("deep");
    add_adj("purple");
    set_unid_long("This is a strange deep purple potion, flecked with yellow petals.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("You notice the faint smell of the crocus flower.\n");
    set_id_taste("The potion is largely tasteless, although leaves a tingling " +
        "sensation on the tongue.\n");
    set_unid_smell("The potion smells faintly of flowers.\n");
    set_unid_taste("The potion tastes strongly of alcohol.\n");

    setup_spell_effect("vistoma", "_vistoma_charge", 1);
}

int
query_strength() 
{
    if (query_alco_strength() < 40)
        return 0;

    return min(100, 50 + (query_alco_strength() - 40) * 5);
}
