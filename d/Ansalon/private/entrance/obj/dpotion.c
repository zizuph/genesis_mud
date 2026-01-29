inherit "/std/potion.c";

public void
create_potion()
{
    set_potion_name("dragon potion");
    set_name(({ "potion", "_dragon_potion_" }));
    set_id_long("Quaffing this potion won't have any effect " + 
        "unless you're a dragon.\n");
    set_unid_long("Quaffing this potion doesn't look very fun.\n");
    set_short("frothy potion");
    set_adj("frothy");
    set_id_taste("The potion tastes bitter.\n");
    set_unid_taste("The potion tastes bitter.\n");
    set_id_smell("The potion smells rotten.\n");
    set_unid_smell("The potion smells rotten.\n");
    set_id_diff(0);
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(10);
}

