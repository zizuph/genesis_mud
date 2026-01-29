/* 	A water kroug in the Calian sea.

    coder(s):   Glykron, Digit

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron
                23. 5.95    adapted to water kroug          Digit

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
#include GLYKDEF
#include RANDOM_HEADER
inherit SEA_CREATURES+"wkroug";

void
equip_me()
{
    object this;
    string type;

    this = THIS;
    seteuid(getuid(this));
    clone_object(SEA_WEAPONS+"obsid_halberd")->move(this);
    command("wield halberd");
    clone_object(SEA_ARMOURS+"platemail")->move(this);
    clone_object(SEA_ARMOURS+"gauntlets")->move(this);
    clone_object(SEA_ARMOURS+"cloak")->move(this);
    command("wear all");

    type = RANDOM_ELEMENT( ({ "boots", "helmet", "shield" }) );
    clone_object(SEA_ARMOURS+type)->move(this);
    command("wear " + type);

    MONEY_MAKE_CC(40)->move(this_object());
}

void
create_wkroug()
{
    if (!IS_CLONE)
	return;

    ::create_wkroug();
    set_long("He is a blackened, scaly creature which appears "+
        "to be covered in a dripping slime of some sorts. He "+
        "appears to have been human at one time, but has undergone "+
        "drastic changes.\n");
    set_race_name("water-kroug");
    add_name("kroug");
    set_base_stat(SS_INT, 40);
    set_base_stat(SS_WIS, 40);
    set_base_stat(SS_DIS, 40);
    set_base_stat(SS_STR, 40);
    set_base_stat(SS_DEX, 40);
    set_base_stat(SS_CON, 40);
    set_skill(SS_WEP_POLEARM, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(10000);
    set_alignment(-50);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    set_act_time(3);
    add_act("emote drips slime on the ground.");
    add_act("emote adjusts his armour.");
    add_act("emote plays with the scales on his body.");
    add_act("emote bangs his head on the ground.");
    add_act("emote spits in your face.");
    add_act("emote snarls: If I got ahold of that Caliana witch, "+
        "I'd teach her a few things!");
    add_act("emote growls: I hear those Calian Warriors are a bunch "+
        "of wimps!");
    add_act("emote screams: Those Thalassian Gods will pay for what "+
        "they have done to us!");
    add_act("emote cackles with glee.");
    add_act("emote grins evilly, slime dripping from his face.");
    add_act("emote throws slime at you.");
    add_act("emote adjusts his armour.");
    add_act("emote taunts you to fight him.");
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
