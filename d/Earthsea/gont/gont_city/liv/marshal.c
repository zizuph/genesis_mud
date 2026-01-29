/*  updated by Amelia 7/13/97
 *  so that Alexander doesn't accept gifts from
 *  players (to fix a bug...they have been loading
 *  him down so as to make him easier to fight)
 *  
 *  Vladimir's Alexander of Cove:
 *  Imported from Roke, for use in the jailhouse in Gont Port
 *  and adapted as an Earthsea monster
 *  (for old times' sake)
 *  By Amelia, 3/23/98
 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/basic_special";
inherit "/lib/unique";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

public void
create_earthsea_monster()
{
    string hitmsg = "You are backhanded ";

    set_name("alexander");
    set_adj(({"middle-aged", "scarred"}));
    set_living_name("alexander");
    add_name("marshal");
    set_title("Marshal of Gont");
    set_race_name("human");
    set_long("This is the marshal of Gont. Like the other "+
        "mercenaries, he was hired from a far-away city. He looks "+
        "grey and middle-aged, yet very experienced. He was "+
        "hired to keep the law and maintain order in the city.\n"+
        "He has scars on his left leg, nose, right arm, left hand "+
        "forehead, big toe, little toe, right thigh, left knee, "+
        "left cheek, and left buttock.\n");
    set_height("tall");
    set_width("normal");
    set_gender(G_MALE);
    set_stats(({ 135,150,150, 75, 75, 120}));
    set_exp_factor(150);
    set_hp(10000);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_2H_COMBAT, 85);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_SWORD, 90);

    add_chat("I may be getting old, but I can still beat the "+
        "crap out of anyone around here!");
    add_act("flex");
    add_act("emote looks like he is longing for the "+
        "good old days.");
    add_act("emote signs some important papers.");
    add_act("emote coughs noisily");
    add_act("emote snarls: Who let you in here?");
    add_act("growl");
    add_act("grumble");
    add_cchat("I shall see to it that you are hanged!");
    add_cchat("You shall regret your decision to attack me.");
    add_cchat("I will cut you into so many pieces your own mother "+
        "won't recognize you!");
    add_chat("They say my fists are harder than stone.");
    add_chat("I can break five stone slabs with my bare hands!");
    add_chat("And those criminals that do not leave find themselves "+
        "either dead or locked in jail.");
    set_act_time(3);
    set_chat_time(80);
    set_cact_time(60);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " says:  Hmm, trying to "+
        "bribe an officer of the law, eh?? You better get out "+
        "of here before I throw you in jail!!\n");
    add_prop("_ranger_i_not_disarm", 1);

    equip(({ 
            clone_unique(ARM + "gplatemail", 18, ARM + "g_elite_platemail"),
            ARM + "ghelm", 
            ARM + "gbracers",
            ARM + "ggreaves", 
            WEP + "msword", 
            clone_unique(WEP + "edagger", 5, WEP + "m_dagger")
            }));

    set_special_attack_percent(20);
    add_special_attack(&basic_special(this_object(), 900, W_BLUDGEON), 100, "backhand");
    set_target_message(" backhands you!");
    set_watcher_message(" backhands", "!");
    set_result_messages(([
        5 : hitmsg + "lightly.", 10 : hitmsg + "savagely.",
        15 : hitmsg + "dangerously.", 20 : hitmsg + "wickedly."
    ]));
}
