/*
 *  Parsley: An annual or biennial herb of the
 *  carrot family widely cultivated for its leaves which are used as a
 *  culinary herb or garnish. Damn, "webster" is handy... ;-)
 *
 *  Oh yeah, you can use it for the clairvoyance spell. :-)
 *
 *                          Tricky, 17-9-92
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
   set_name("parsley");
   add_name("leaf");
   add_name("_clv_spell_ingr_");
   set_adj(({"green"}));
   set_short("green leaf");
   set_pshort("green leaves");
   set_herb_name("parsley");
   set_id_long("This green leaf is known as parsley. It is an " +
        "annual or biennial herb and looks very similar to carrot " +
        "tops. The plant is widely cultivated for its leaves which " +
        "are used as a culinary herb or garnish.\n");
   set_unid_long("This is a strange, strong-smelling leaf.\n");
   set_ingest_verb("eat");
   set_id_diff(10);
   set_find_diff(1);
   set_effect(HERB_HEALING,"hp", 3); /* Sure you can eat it */
   set_decay_time(1800);
   set_herb_value(96);
}
query_recover() { return MASTER + ":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
