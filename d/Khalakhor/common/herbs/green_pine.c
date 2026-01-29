/* File:          /d/Khalakhor/common/herbs/green_pine.c
 * Creator:       Teth
 * Date:          January 26, 1998
 * Modifications:  
 * Added more consistent names - Tapakah, 04/2021
 * Purpose:       This herb is a generic herb for the domain.
 *                It gives a bonus to SS_PICK_POCKET skill.
 * Related Files: 
 * Comments:
 * The pickpocket bonus seems to have been commented out. When - unknown.
 * - Tapakah, 04/2021
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

public void
create_herb()
{
    set_name("sap");
    add_name(({"resin", "pitch", "herb", "pine", "green pine"}));
    set_adj("amber");
    add_adj("resinous");
    set_herb_name("green pine");
    set_short("resinous amber sap");
    set_pshort("resinous amber saps");
    set_pname("saps");
    add_pname(({"resins", "herbs", "pitches", "pines", "green pines"}));
    set_ingest_verb("chew");
    set_unid_long("This is a resinous amber sap. It was probably " +
      "scraped from a coniferous, or evergreen, tree.\n");
    set_id_long("This resinous amber sap is the pitch of a species of " +
      "pine known commonly as green pine. The sap flows from the tree " +
      "wherever there is a wound, typically a broken branch. When " +
      "chewed, the resin of this tree provokes deep thought. The " +
      "green pine grows in coniferous and mixed woods forests, although " +
      "it can sometimes be found along the boundary of a forest and a " +
      "plain.\n");
    set_herb_value(148);
    set_id_diff(19);
    set_find_diff(3);
    set_decay_time(4800); /* 80 minutes */
    set_amount(1);
    set_effect(HERB_HEALING, "mana", 2);
    add_effect(HERB_HEALING, "fatigue", 1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
/*
    add_cmd_item(({"sap","resin","pitch","the sap","the resin",
      "the pitch"}),({"squeeze","squish","crush"}),"@@skill_effect");
*/

    seteuid(getuid());
}

/*
public string
skill_effect()
{
    object shadow;

    write("As you squish the sap in your hands, it emits a " +
      "chlorophyllic scent. It covers your hands, disappearing into " +
      "your skin, but also leaves your hands feeling sticky.\n");

    shadow = clone_object(COM_HERBS + "skill_enhance");
    shadow->set_enhance_effect(SS_PICK_POCKET,"pick pockets",5);
    shadow->move(this_player(),1);
    remove_object();

    return "";
}
*/

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


