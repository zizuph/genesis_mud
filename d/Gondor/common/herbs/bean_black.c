/*
 *  /d/Gondor/common/herbs/bean_black.c
 *
 *  A bean which can be found in the Gondor lands.
 *
 *  Coder and creation date: unknown
 *
 *  Revision History:
 *    Sept-21-98 (Gorboth) - Typo fix and general revision
 *    Sept 18 17. Removed reference to plant genus species. 
*                 This is a 20th century innovation,
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 * Function name:        create_herb
 * Description  :        set up the herb
 */
void
create_herb()
{
    set_name("bean");
    set_short("tiny black bean");
    set_pshort("tiny black beans");
    set_adj(({"tiny","black","round" }));

    set_herb_name("black bean");
    set_id_long(BSN("This is a black bean. It is said to have been brought " +
        "to Eriador by the "
      + "Nandoran Green Elves of the Host of Lenwe in the Elder Days, "
      + "but it now may be found under cultivation in many lands."));
    set_unid_long("This looks like an tiny black, round bean.\n");

    set_ingest_verb("eat");
    set_id_diff(6);
    set_find_diff(2);
    set_effect(HERB_HEALING, "fatigue", 4);
    set_dryable();
    set_decay_time(5400);
    set_herb_value(36);
    set_amount(5);

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 4);
} /* create_herb */
