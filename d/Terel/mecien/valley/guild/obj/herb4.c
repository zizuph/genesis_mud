/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* Value nerefed from 5000 -> 1200 */
inherit "/std/herb";
#include <macros.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <herb.h>

create_herb(){

set_name("moss");
set_adj("strange");
set_short("bit of strange moss");
set_herb_name("wilcol");

set_id_long(
"Legends abound about the power of the Wilcol moss. Myth tells " +
"us that long ago it grew out of the tears from the weeping spirits " +
"who mourned the evil that was done to the world. It is said that the moss " +
"has the power to reduce or destroy poisons of any kind.\n"
);
set_unid_long(
"A strange bit of moss. Vibrant green with tiny white flowers.\n");
set_herb_value(12000);
set_decay_time(1200);
set_find_diff(7);
set_id_diff(75);
set_effect(HERB_CURING, "all", 98);
add_prop(OBJ_I_VALUE, query_herb_value());


}

