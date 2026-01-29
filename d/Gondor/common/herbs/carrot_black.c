#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name(({"carrot","morinave"}));
    set_adj(({"green-topped","wizened","wrinkled","fleshy","astringent","grey-speckled","black"}));
    set_short("green-topped black carrot");
    set_pshort("green-topped black carrots");
    set_herb_name("black carrot");
    set_id_long(BSN("This black carrot is a member of the "
          + "Carrota species of the genus Daucus. This carrot is a fleshy "
          + "astringent black root.  Varying widely in size, the domestic. "
          + "carrot was first bred by the dwarves of the Blue Mountains "
          + "in the days before the Sun and Moon first rose over Middle-Earth. "
          + "The common orange carrot is ubiquitous throughout Eriador and "
          + "Beleriand.  The stupifying black carrot, or Moridoriave, was bred "
          + "in Eregion in the sixteenth century of the Second Age."));                                    
    set_unid_long("This looks like a wizened, wrinkled, grey-speckled black carrot.\n");
    set_ingest_verb("eat");

    set_effect(HERB_POISONING, "morinave", 50);
    set_poison_damage( ({ POISON_STAT, SS_INT }) );
    set_id_diff(33);
    set_find_diff(1);
    set_decay_time(3000);
    set_herb_value(72);
    set_amount(60);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 54);
    set_dryable();
}

