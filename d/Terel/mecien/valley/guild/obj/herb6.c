/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/herb";
#include <macros.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <herb.h>

create_herb(){

set_name("frond");
set_adj("purple");
set_short("purple frond");
set_herb_name("lukilvor");

set_id_long(
"The Lukilvor is a lovely plant, rather like a fern, growing in ancient " +
"woodlands, often near ponds and streams. Its fronds are purple. It is said " +
"that they are magical and loved by the fairy people, who use them as " +
"decorations on their tables and doors.\n"
);
set_unid_long(
"It is a delightfully beautiful purple frond, crisp and radiant.\n");
set_herb_value(160);
set_decay_time(1200);
set_find_diff(5);
set_id_diff(5);
set_effect(HERB_HEALING, "mana", 18);


}

