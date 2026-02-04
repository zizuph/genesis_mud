/*
 * moosho mushroom coded by Shinto
 * 101599
 * mana recovering herb
 */

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
    set_name("mushroom");
    add_name("herb");

    set_pname("mushrooms");
    add_pname("herbs");
    set_adj("small");
    add_adj("blue");
    set_short("blue mushroom");
    set_herb_name("moosho");
    set_id_long("This mushroom is called a moosho mushroom. They "+
         "are only found underwater, in fresh bodies of water."+
         "They are known to return mental strength to those that "+
         "consume them.\n");
    set_unid_long("About the size of a strawberry, this herb has a "+
         "blue tint.\n");
    set_ingest_verb("eat");
    set_id_diff(30);     //not difficult to id
    set_find_diff(3);
    set_decay_time(600);  //will decay quickly if not preserved.
    set_effect(HERB_HEALING,"mana",50);
    set_herb_value(800);
}

