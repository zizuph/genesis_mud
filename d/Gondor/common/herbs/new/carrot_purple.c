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
    set_short("green-topped purple carrot");
    add_pname(({"herbs", "carrots"}));
    set_pshort("green-topped purple carrots");
    set_adj(({"green-topped","light","small","purple","slightly","bitter","woody"}));
    set_herb_name("purple carrot");
    set_id_long(BSN("This purple carrot is a member of the "
      + "Carrota species of the genus Daucus. The carrot is a tasty "
      + "crunchy purple root.  Varying widely in size, the domestic. "
      + "carrot was first bred by the dwarves of the Blue Mountains "
      + "in the days before the Sun and Moon first rose over Middle-Earth. "
      + "The common purple carrot is ubiquitous thourghout Eriador and "
      + "Beleriand.  The rare purple carrot, or 'Yavekemenel' or 'Kemen' "
      + "root, was cultivated by the dwarves of the White Mountains before the "
      + "War of the Elves and Sauron devastated the lands.  It now grows "
      + "natively in the wide lands between the Adorn and the Gwathlo."));
    set_unid_long(BSN("This carrot looks like a small woody light purple carrot. " 
      + "It had a slightly bitter smell to it. \n"));
    set_ingest_verb("eat");
    set_id_diff(22);
    set_find_diff(12);
    set_effect(HERB_HEALING,"mana",4);
    set_decay_time(8000);
    set_herb_value(636);
    set_amount(1);
    add_prop(OBJ_I_WEIGHT,30);
    add_prop(OBJ_I_VOLUME,36);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }