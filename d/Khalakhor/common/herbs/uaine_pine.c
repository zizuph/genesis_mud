/* File:          /d/Khalakhor/common/herbs/uaine_pine.c
 * Creator:       Teth
 * Date:          January 27, 1998
 * Modifications:  
 * Added consistent singular and plural names - Tapakah, 04/2021
 * Purpose:       This herb is a generic herb for the domain.
 *                It gives a bonus to SS_PICK_POCKET skill.
 *                It is also used in one of the tours.
 * Related Files: 
 * Comments:      This herb is for Khalakhor use only.
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
    add_name(({"resin", "pitch", "herb", "pine", "uaine pine"}));
    set_adj("amber");
    add_adj("resinous");
    set_herb_name("uaine pine");
    set_short("resinous amber sap");
    set_pshort("resinous amber saps");
    set_pname("saps");
    add_pname(({"resins","herbs","pitches", "pines", "uaine pines"}));
    set_ingest_verb("chew");
    set_unid_long("This is a resinous amber sap. It was probably " +
      "scraped from a coniferous, or evergreen, tree. It is " +
      "highly aromatic.\n");
    set_id_long("This resinous amber sap is the pitch of a species of " +
      "pine known as Uaine Pine. It flows from the tree wherever there " +
      "is a wound, typically a broken branch. The sap is strongly " +
      "scented, moreso than the saps of other pine species. When chewed, " +
      "the resin of this tree provokes deep thought. The Uaine Pine " +
      "often grows along the edge of a forest and a plain, or is " +
      "cultivated.\n");
    set_herb_value(150);
    set_id_diff(25);
    set_find_diff(7);
    set_decay_time(4800); /* 80 minutes */
    set_amount(1);
    set_effect(HERB_HEALING, "mana", 2);
    add_effect(HERB_HEALING, "fatigue", 1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_cmd_item(({"sap","resin","pitch","the sap","the resin",
      "the pitch","the amber sap","the resinous amber sap",
      "amber sap","resinous amber sap","sap herb","the sap herb",
      "the amber resin","amber resin","the amber pitch","amber pitch"}),
      ({"smell","inhale"}),"As you breathe in the scent of the amber " +
      "resin, you realize a clarity of thought akin to that of a " +
      "state of deep meditation.\n");
    add_cmd_item(({"sap","resin","pitch","the sap","the resin",
      "the pitch","the amber sap","the resinous amber sap",
      "amber sap","resinous amber sap","sap herb","the sap herb",
      "the amber resin","amber resin","the amber pitch","amber pitch"}),
      ({"squeeze","squish","crush"}),"@@skill_effect");

    seteuid(getuid());
}

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


