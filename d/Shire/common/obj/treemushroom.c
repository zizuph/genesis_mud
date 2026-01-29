/*
 *  The rare tree mushroom
 *                          Tricky, 6-7-92
 */

inherit "/std/herb.c";

#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
   set_name(({"_stop_spell_mushroom_","mushroom"}));
   set_adj(({"brown","tree"}));
   set_short("brown tree mushroom");
   set_herb_name("fungiarbo");
   set_id_long(break_string(
      "This is a rare tree mushroom, which herbalists call fungiarbo. "
    + "It has a spungy brownish roof, which "
    + "is white underneath, and has a thin beige stem. Fungiarbo "
    + "is often used as a magical ingredient.\n",60));
   set_unid_long(break_string(
      "This is some kind of mushroom that grows on trees. "
    + "It has a spungy brownish roof, which "
    + "is white underneath, and has a thin beige stem.\n",70));
   set_ingest_verb("eat");
   set_id_diff(35);
   set_find_diff(4);
   set_effect(HERB_HEALING,"hp",-13); /* Don't eat it! */
   set_decay_time(1800);
   set_herb_value(325);
   add_prop(OBJ_I_WEIGHT, 96);
   add_prop(OBJ_I_VOLUME, 131);
}
