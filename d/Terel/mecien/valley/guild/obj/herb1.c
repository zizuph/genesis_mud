/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/herb";
#include <macros.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <herb.h>

create_herb(){

set_name("root");
set_adj("white");
set_short("white root");
set_herb_name("tilhiyin");

set_id_long(
 "A radiant white root, it has a very sweet and aromatic smell\n" +
"that is very good. It is rather crisp.\n" +
"The Tilhiyin root is a mystical root that is ingested to restore\n"
+"magical powers. It is an ancient root that is held sacred\n"
+"by the Order of Mystics, for it is said in legend that the roots\n"
+"were blessed by some divine power.\n"
);
set_unid_long(
"It is a radiant white root, it has a very sweet smell\n"
+"and is very crisp.\n"
);
set_herb_value(1500);
set_decay_time(600);
set_find_diff(3);
set_id_diff(65);
set_effect(HERB_HEALING, "mana", 78);
add_prop(OBJ_I_VALUE, query_herb_value());


}

