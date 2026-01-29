/* File:          /d/Khalakhor/common/herbs/cedar_bark.c
 * Creator:       Teth
 * Date:          January 26, 1998
 * Modifications:
 * Added more consistent names - Tapakah, 04/2021
 * Purpose:       This herb is a generic herb for the domain.
 * Related Files: 
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_herb()
{
    set_name("bark");
    add_name(({"peeling", "herb", "strip", "cedar", "white cedar"}));
    set_adj("strip");
    add_adj(({"of","grey"}));
    set_herb_name("white cedar");
    set_short("strip of grey bark");
    set_pshort("strips of grey bark");
    set_pname("barks");
    add_pname(({"peelings","herbs","strips", "cedars", "white cedars"}));
    set_ingest_verb("eat");
    set_unid_long("This strip of grey bark resembles those which " +
      "can often be found on some coniferous trees.\n");
    set_id_long("This strip of grey bark is from the white cedar " +
      "tree. Cedar, also known as Thuja, is a tall evergreen tree " +
      "that often grows in wet dark forests, bogs, and swamps, " +
      "although it also grows well when cultivated. The cedar, " +
      "unlike more common evergreens, does not have needles for leaves, " +
      "but instead has green over-lapping scales. Its bark often " +
      "peels off in long strips, and is used in some herbal remedies.\n");
    set_herb_value(74);
    set_id_diff(16);
    set_find_diff(4);
    set_decay_time(4800); /* 80 minutes */
    set_dryable();
    set_amount(10); /* Talk about roughage! */
    set_effect(HERB_HEALING, "fatigue", -5); /* Ever try to chew on this? */
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

public string
query_recover() 
{
    return MASTER+":"+query_herb_recover();
}

public void
init_recover(string arg) 
{ 
    init_herb_recover(arg); 
}


