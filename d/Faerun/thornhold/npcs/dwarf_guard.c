/*
 * Thornhold guard (based on halfling guard)
 * by Twire, September 2016
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define WEAPON  ({"battleaxe"})
#define SHIELD  ({"shield"})
#define BOD_ARM ({"chainmail"})
#define BRACERS ({"bracers"})
#define GREAVES ({"greaves"})
#define HELMET  ({"helmet"})
#define TYPE    ({"brave", "fierce", "determined", "stalwart", "grumbling", "coarse",  "loyal", "grumpy", "cantankerous", "bold"})
#define PHYS    ({"grey-bearded", "long-bearded", "calloused", "muscular", "red-bearded", "stout",  "thick-armed", "bulbous-nosed", "broad-chested", "black-bearded"})

void arm_me();
nomask void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

    npc_name = "dwarf_guard";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("dwarf");
    add_name("guard");
    add_name(npc_name);

    set_short(phys + " " + type + " dwarven guard");
    set_long("This is a " + query_short() + ". He is a loyal dwarf of the " + 
    "Stoneshaft Clan, trained to protect the Thornhold. He patrols the " +
    "fortress, keeping it secure from monsters and thieves.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);

    default_config_npc(70 + random(10));
    set_base_stat(SS_DEX, (60 + random(25)));

    set_alignment(110 + random(50));


    set_alignment(300 + random(100));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_chat_time(150);
    add_chat("Greetings, traveller.");
    add_chat("Cause no trouble in Thornhold.");
    add_chat("Do not even think of stealing from visiting caravans.");
    add_chat("The dwarves of Clan Stoneshaft are a fierce and loyal lot.");
 
    set_act_time(150);
    add_act("emote inspects his armours.");
    add_act("emote peers at you, watching your every move.");
    add_act("emote places a hand on the hilt of his weapon.");
    add_act("emote greets a passing traveller with prefunctory nod.");

    set_cchat_time(25);
    add_cchat("Ye'll regret crossing the Stoneshaft Clan!");
    add_cchat("Thornhold's no place fer fightin'! Ye'll pay fer this!'");
    add_cchat("Yer bein' a damn fool, ya know.");
    add_cchat("You will not defeat me!");
    add_cchat("Moridin's curse be upon ye, foul one!");

    set_cact_time(10);
    add_cact("shout Axes high, guards! Thornhold is under attack!");
    add_cact("emote steps back, then charges forward.");
    add_cact("emote attacks you with renewed vigor.");
    add_cact("emote circles you carefully then charges forward.");
    add_cact("emote deftly parries your attack.");

    arm_me();

    set_pick_up_team(({"dwarf_guard"}));
}



void
arm_me()
{
    object arm, wep, gem;

    arm ->move(this_object());
    arm = clone_object(ARM_DIR + ONE_OF_LIST(HELMET));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + ONE_OF_LIST(BOD_ARM));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + ONE_OF_LIST(BRACERS));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + ONE_OF_LIST(GREAVES));
    arm -> move(TO);
//    arm = clone_object(ARM_DIR + ONE_OF_LIST(SHIELD));
//    arm -> move(TO);

    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);

    command("wear armours");
    command("wield weapon");

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
