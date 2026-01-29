/*
 *  The rare tree mushroom
 *                          Tricky, 6-7-92
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
    set_name("fungiarbo");
    add_name("mushroom");
    add_name("_stop_spell_mushroom_");
    set_adj(({"brown","tree"}));
    set_short("brown tree mushroom");
    set_herb_name("fungiarbo");
    set_id_long("This is a rare tree mushroom, which herbalists " +
        "call fungiarbo. It has a spongy brownish roof, which is " +
        "white underneath with a thin beige stem. Fungiarbo is " +
        "often used as a magical ingredient.\n");
    set_unid_long("This is a meaty-looking rare brown mushroom.\n");
    set_ingest_verb("eat");
    set_id_diff(35);
    set_find_diff(4);
    set_effect(HERB_HEALING,"hp",-13); /* Don't eat it! */
    set_decay_time(1800);
    set_herb_value(325);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
