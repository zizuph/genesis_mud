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
    clone_object(SEA_WEAPONS + "br_trident")->move(this);
    command("wield all");
    clone_object(SEA_ARMOURS + "cloak")->move(this);
    command("wear all");
    MONEY_MAKE_CC(45)->move(this_object());
}

void
create_wkroug()
{
    if (!IS_CLONE)
	return;

    ::create_wkroug();
    set_long("He is a blackened, scaly creature who appears "+
        "to be covered in a dripping slime of some sort.  He "+
        "almost looks like a kroug, but one that lives in water, "+
        "not on land.\n");
    set_race_name("water-kroug");
    set_base_stat(SS_INT, 30);
    set_base_stat(SS_WIS, 30);
    set_base_stat(SS_DIS, 30);
    set_base_stat(SS_STR, 30);
    set_base_stat(SS_DEX, 30);
    set_base_stat(SS_CON, 30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 30);
    set_hp(10000);
    set_alignment(-50);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    set_act_time(3);
    add_act("emote drips slime on the ground.");
    add_act("emote adjusts his armour.");
    add_act("emote plays with the scales on his body.");
    add_act("emote dunks his head in the water.");
    add_act("emote bangs his head on the wall.");
    add_act("emote spits in your face.");
    add_act("emote growls: Those Knights of Bolognia are next, or "+
        "whatever they are called!");
    add_act("emote screams: Those Rangers will bow down and worship us!");
    add_act("emote snarls: Move behind?  More like hide behind if "+
        "you ask me.");
    add_act("emote screams: Bash?  You call that a BASH? Mwhahahah!");
    add_act("emote snarls: If I got ahold of that Caliana witch, "+
        "I'd teach her a few things!");
    add_act("emote growls: I hear those Calian Warriors are a bunch "+
        "of wimps!  They always hide behind each other!");
    add_act("emote snarls: Praise your false Gods!  Lord Kroug "+
        "will rule again one day!");
    add_act("emote screams: Those Thalassian Gods will pay for what "+
        "they have done to us!");
    add_act("emote cackles with glee.");
    add_act("emote grins evilly, slime dripping from his face.");
    add_act("emote throws slime at you.");
    add_act("emote adjusts his armour.");
    add_act("emote taunts you to fight him.");
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
