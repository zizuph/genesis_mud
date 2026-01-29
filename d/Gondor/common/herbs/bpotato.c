#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("potato");
    add_name("mortirio_ingr1");
    set_adj(({"little", "black"}));
    set_short("little black potato");
    add_pname(({"herbs", "potatoes"}));
    add_adj("unwholesome-looking");
    set_pshort("little black potatoes");
    set_herb_name("black potato");
    set_id_long(BSN("The Dunland black potato is a member of the "
      + "Tuberosum species of the genus Solanum. It is a small, lumpy, "
      + "unwholesome-looking wrinkled mass. The black potato is said "
      + "to have been introduced into the Gwathlo valley by the orcs and "
      + "servants of the Witch-King of Angmar."));
    set_unid_long("This black potato looks like an ordinary potato.\n");
    set_ingest_verb("eat");
    set_effect(HERB_POISONING, "black potato", 25);
    set_poison_damage( ({ POISON_HP, 20 }) );
    set_id_diff(25);
    set_find_diff(1);
    set_decay_time(4800);
    set_herb_value(72);
    set_amount(60);
    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 65);
    set_dryable();
}

