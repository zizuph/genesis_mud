
 /*    A Triton for the Thalassian City citadel guard house

    coder(s):    Digit

    history:    21.7.95    header added          Digit
                08.7.03    randomized stats      Jaacar
                           added more actions
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "/d/Genesis/gems/gem.h"
#include "defs.h"
#include GLYKDEF
#include RANDOM_HEADER
inherit SEA_CREATURES+"triton";

void
equip_me()
{
    object this, gem;
    string type;

    this = THIS;
    seteuid(getuid(this));
    clone_object(SEA_WEAPONS+"ori_trident")->move(this);
    command("wield trident");
    clone_object(SEA_ARMOURS+"triton_armour")->move(this);
    clone_object(SEA_ARMOURS+"triton_helmet")->move(this);
    command("wear all");
    MONEY_MAKE_GC((random(8)))->move(this);
    gem=RANDOM_GEM_BY_RARITY(GEM_SOMEWHAT_RARE);
    gem->move(this);
}

void
create_triton()
{
    if (!IS_CLONE)
	return;

    ::create_triton();
    set_long("He is a strikingly beautiful creature with long "+
        "black hair.  He is human in appearance above the waist, "+
        "but has a large fish-like tail instead of legs.  He is "+
        "covered in dark green scales, and has long, sharp claws on "+
        "his webbed fingers.  His friendly smile reveals what look "+
        "like very sharp fish teeth.\n");
    set_race_name("triton");
    set_base_stat(SS_INT, (90+random(30)));
    set_base_stat(SS_WIS, (90+random(30)));
    set_base_stat(SS_DIS, (90+random(30)));
    set_base_stat(SS_STR, (90+random(30)));
    set_base_stat(SS_DEX, (90+random(30)));
    set_base_stat(SS_CON, (90+random(30)));
    set_skill(SS_WEP_POLEARM, (90+random(10)));
    set_skill(SS_PARRY, (90+random(10)));
    set_skill(SS_DEFENCE, (90+random(10)));
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    set_act_time(3);
    add_act("emote adjusts his armour.");
    add_act("emote bubbles: Don't be starting any trouble in here.");
    add_act("emote twirls his trident around skillfully.");
    add_act("emote bubbles: I'm tougher than I look.");
    add_act("emote bubbles: Thalassia is a grand city indeed.");
    add_act("emote bubbles: We've got our eyes on you, be careful.");
    set_random_move(10);
    set_restrain_path(({(THALC)}));
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"job","guard"}),
        "say My job is to guard this city from people who cause trouble.",1);
    add_ask(({"thalassia","Thalassia","city"}),
        "say Thalassia is my home. Do NOT start trouble here, or else.",1);
}

public string
default_answer()
{
    command("say Move along! I don't know what you are talking about!");
    return "";
}