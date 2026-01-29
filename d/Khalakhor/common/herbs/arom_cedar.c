/* File:          /d/Khalakhor/common/herbs/arom_cedar.c
 * Creator:       Teth
 * Date:          January 27, 1998
 * Modifications:
 * Added consistent singular and plural names - Tapakah, 04/2021
 * Purpose:       This herb is a generic herb for the domain,
 *                and also used in one of the tours.
 * Related Files: 
 * Comments:      This is a Khalakhor only herb.
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
    add_name(({"peeling", "herb", "strip", "cedar", "aromatic cedar"}));
    set_adj("strip");
    add_adj(({"of","grey"}));
    set_herb_name("aromatic cedar");
    set_short("strip of grey bark");
    set_pshort("strips of grey bark");
    set_pname("barks");
    add_pname(({"peelings","herbs","strips", "cedars", "aromatic cedars"}));
    set_ingest_verb("eat");
    set_unid_long("This strip of grey bark resembles those which " +
      "can often be found on some coniferous trees. However, this " +
      "peeling is highly aromatic.\n");
    set_id_long("This strip of grey bark is from the aromatic cedar " +
      "tree. Aromatic cedar is a four meter high evergreen tree " +
      "that is rare throughout Khalakhor. It is occasionally " +
      "cultivated, as it is only otherwise found in the darkest of " +
      "swamps. Cedar, unlike more common evergreens, does not have " +
      "needles for leaves, but instead has green over-lapping scales. " +
      "Its bark often peels off in long strips, and is used in some " +
      "herbal remedies.\n");
    add_cmd_item(({"bark","peeling","strip","strip of bark",
      "strip of grey bark","grey bark","grey peeling","aromatic bark",
      "aromatic herb","aromatic grey bark","the bark","the peeling",
      "the strip","the strip of bark","the strip of grey bark",
      "the grey bark","the grey peeling","the aromatic bark",
      "the aromatic herb","the aromatic grey bark"}),"smell",
      "The resinous scent of the aromatic grey bark is intoxicating " +
      "in its purity and clarity. It is the rich earthy scent of wet " +
      "forest floors, perfect for meditative thought.\n");
    set_herb_value(90);
    set_id_diff(25);
    set_find_diff(6);
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


