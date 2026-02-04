/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/herb";
#include <macros.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <herb.h>

public void
create_herb()
{

    set_name("leaf");
    set_adj("orange");
    set_short("orange leaf");
    set_herb_name("aravelis");

    set_id_long(
        "The Aravelis is a rare shrub that grows in warm areas, especially in " +
        "places where fruits and highly nutrient soils are. It is said to contain "
        + "mysterious properties from the sun, whereas it is often called " +
        " 'the Life of the Sun'.\n");
    set_unid_long(
        "A tiny fiery orange leaf, speckled with gold.\n");
    set_herb_value(1200);
    set_decay_time(1200);
    set_find_diff(8);
    set_id_diff(75);
    set_effect(HERB_HEALING, "mana", 57);


}

