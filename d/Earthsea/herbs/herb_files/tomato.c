/*
 * coded by Amelia 4/12/97
 *  for use in Roke Ten Alders area 
 *  herb with possible medicinal uses
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>

public void
create_herb()
{
    set_name("fruit");
    add_name(({"herb", "tomato"}));
    add_adj(({"bright red", "bright", "red"}));
    add_pname("herbs");
    set_short("bright red fruit");
    set_pshort("bright red fruits");
    set_herb_name("tomato");
    set_unid_long("A bright red fruit, about " +
        "the size of a small apple, but it is not an apple.\n");
    set_id_long("A bright red, ripe tomato, " +
        "or Lycopersicon esculentum. Sometimes referred to " +
        "as a love apple, it is rumoured to inflame the " +
        "passions. A common ingredient in love potions.\n");
    set_id_diff(25);
    set_find_diff(6);
    set_effect(HERB_HEALING, "mana", 15);
    set_ingest_verb("eat");
    set_herb_value((5 * 15) + (15 * 15)/4);
    set_decay_time(3000);
}
