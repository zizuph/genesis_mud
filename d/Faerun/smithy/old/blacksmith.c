/*
 * Sample blacksmith
 *
 * browse weapon    - displays list of weapons
 * browse <weapon>  - shows info abt <weapon>
 * order <item>     - starts order process
 * mend <item>      - will mend a broken item
 * repair <wep/arm> - repairs armours, sharpens weps
 *
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/smithy/base_smithy";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define METALS ({"bronze", "iron", "silver", "steel", "high-steel" })

object
hook_smithy_select_create_weapon(mapping design)
{
    object  weapon;
    weapon= ::hook_smithy_select_create_weapon(design);
    weapon->set_long("This is a " + LANG_ASHORT(weapon) + " that "+
    "has been forged in the small town of Bliss. A mark has been placed "+
    "on the edge that reads:\n"+
    "Rodney Realli Master Craftsman.\n"+
    "Domain of Raumdor.\n");
    return weapon;
}


nomask void create_faerun_npc()
{

    string type, phys;
    int i;

    seteuid(getuid());

    add_adj("swarthy");
    add_adj("muscular");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name("smithy");

    set_short("swarthy muscular human");
    set_long("This is a " + short() + ". He is a master blacksmith and knows much about smithing. He's strong and has practiced his craft for many years, and has developed a reputation for forging the best weapons and armours around.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
// allows the npc to see in rooms up to 10 levels of darkness
    add_prop(LIVE_I_SEE_DARK,10);
// randomly sets the base stats of the npc
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 120 + random(25));
    set_base_stat(5, 100);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

    set_act_time(5);
    add_act("listen attent");
    add_act("watch");

    set_alarm(1.0,0.0,"arm_me");

// Weapons
   add_smithy_weapon("sword", "construction", ({"falchion", "scimitar",
       "gladius", "longsword", "courtelas", "bastard sword", "estoc",
       "broadsword", "rapier"}));
    add_smithy_weapon("sword", "metal", ({"bronze", "iron", "silver", "steel", "high-steel"}));

    add_smithy_weapon("knife", "construction", ({"dagger","rondel dagger",
       "dirk", "swiss dagger", "main gauche", "cinquedea", "stilleto",
       "misericord", "bodkin"}));
    add_smithy_weapon("knife", "metal", ({"bronze", "iron", "silver", "steel", "high-steel"}));
       
    add_smithy_weapon("axe", "construction", ({"battle axe", "waraxe",
    "broad axe", "bardiche", "lochaber axe", "double-headed axe", "mattock"}));
    add_smithy_weapon("axe", "metal", ({"bronze", "iron", "silver", "steel", "high-steel"}));

    
    config_default_trade();


}

void
arm_me()
{
    object arm, wep, gem;

    make_gems(1);

}

void
init_living()
{
    ::init_living();
    init_smithy();

}
