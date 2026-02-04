inherit "/std/herb";
#include <macros.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <herb.h>

create_herb(){

set_name("mushroom");
set_adj("grey");
set_short("grey mushroom");
set_herb_name("ylpoe");

set_id_long(
"A grey mushroom, not as clean or fresh as its close relative the Ylpi,\n" +
"The Ylpoe mushroom is nevertheless believed to be enchanted like its\n" +
"white countertpart.\n"
);
set_unid_long(
"A dull grey mushroom, a bit dirty but somewhat fresh.\n");
set_decay_time(1000);
set_find_diff(8);
set_id_diff(25);
}
