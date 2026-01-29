/*
 * A simple demonstration of a resistance potion
 *
 * DISCLAIMER: This is ONLY a demonstration potion!!
 */

inherit "/std/potion";

#include <ss_types.h>
#include <herb.h>
#include <macros.h>
#include <poison_types.h>

public void
create_potion()
{
    set_short("large black potion"); 
    set_adj("black"); add_adj("large");
    set_unid_long("It is a large flask filled with red liquid.\n");
    set_potion_name("fire resistance potion");
    set_id_long("This is a fire resistance potion.\n");
    set_id_diff(20);
    set_soft_amount(10);
    set_alco_amount(1);
    set_potion_value(42000);

    set_id_smell("The potion smells somewhat spicy.\n");
    set_id_taste("The potion tastes somewhat spicy.\n");
    set_unid_smell("Hmm. You don't smell anything.\n");
    set_unid_taste("Hmm. Tastes rather bland.\n");

    set_effect(HERB_ENHANCING, "fire", 10);

}









