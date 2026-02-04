/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/herb";
#include <macros.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <herb.h>

create_herb(){

set_name("flower");
set_adj("blue");
set_short("blue flower");
set_herb_name("sebre");

set_id_long(
"The Sebre flower grows in the cool shade of evergreens. It is " +
"usually found hiding its beauty under the brambles and canopies " +
"of other plants. Its strength comes from its power to sharpen " +
"the mind with its sweet pollen.\n"
);
set_unid_long(
"An aromatic tiny blue flower.\n");
set_herb_value(80);
set_decay_time(1200);
set_find_diff(5);
set_id_diff(5);
set_effect(HERB_HEALING, "mana", 9);
add_prop(OBJ_I_VALUE, query_herb_value());


}

