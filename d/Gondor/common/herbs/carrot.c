#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("carrot");
    set_short("green-topped orange carrot");
    add_pname(({"herbs", "carrots"}));
    set_pshort("green-topped orange carrots");
    set_adj(({"green-topped", "orange", "tasty", "crunchy"}));
    set_herb_name("orange carrot");
    set_id_long(BSN("This orange carrot is a member of the "
      + "Carrota species of the genus Daucus. The carrot is a tasty "
      + "crunchy orange root.  Varying widely in size, the domestic. "
      + "carrot was first bred by the dwarves of the Blue Mountains "
      + "in the days before the Sun and Moon first rose over Middle-Earth. "
      + "The common orange carrot is ubiquitous thourghout Eriador and "
      + "Beleriand.  The most common variety was brought from Numenor "
      + "by Tar Aldarion."));
    set_unid_long("This orange carrot looks like an ordinary carrot.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "fatigue", 4);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(36);
    set_amount(60);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 54);
    set_dryable();
}

