#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("carrot");
    set_short("green-topped yellow carrot");
    add_pname(({"herbs", "carrots"}));
    set_pshort("green-topped yellow carrots");
    set_adj(({"green-topped", "yellow", "tasty", "crunchy"}));
    set_herb_name("yellow carrot");
    set_id_long(BSN("This yellow carrot is a member of the "
      + "Carrota species of the genus Daucus. The carrot is a tasty "
      + "crunchy yellow root.  Varying widly in size, the domestic. "
      + "carrot was first bred by the dwarves of the Blue Mountains "
      + "in the days before the Sun and Moon first rose over Middle-Earth. "
      + "According to the Herblore of Gundobald, the yellow carrot, "
      + " or 'Laurenkemenyavie' or 'Lork', was brought to the Vales of the "
:      + " Gwathlo by the Stoor Hobbits when they emigrated from the Gladden "
      + " Fields to Eriador in the 12th Century of the Third Age."));
    set_unid_long("This carrot looks normal, except for being bright yellow.\n");
    set_ingest_verb("eat");
    set_id_diff(2);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue",5);
    set_dryable();
    set_decay_time(4000);
    set_herb_value(36);
    set_amount(3);
    add_prop(OBJ_I_WEIGHT,40);
    add_prop(OBJ_I_VOLUME,45);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }