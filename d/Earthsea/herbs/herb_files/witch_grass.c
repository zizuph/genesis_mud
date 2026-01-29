/*
 * coded by Amelia, 5/15/97
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>

public void
create_herb()
{
    set_name(({"blade of grass", "blade of witch grass", "grass", "herb"}));
    add_name("blade");
    add_adj(({"witch", "purple", "tangled"}));
    set_short("purple blade of grass");
    set_pshort("purple blades of grass");
    set_herb_name("witch grass");
    set_pname(({"blades of witch grass", "blades of grass"}));
    add_pname(({"herbs", "grasses"}));
    set_unid_long("A long blade of purple grass.\n");
    set_id_long("Purple long-bladed grass, or " +
        "Panicum capilare, commonly known as witch grass. " +
        "There is a superstition that this grass is " +
        "an ingredient in witches' potions.\n");
    set_id_diff(25);
    set_herb_value((5 * 20) + (20 * 20)/4);
    set_find_diff(4);
    set_decay_time(5000);
    set_effect(HERB_POISONING, "herb", 20);
}
