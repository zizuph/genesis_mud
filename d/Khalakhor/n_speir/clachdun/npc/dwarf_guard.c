#include "local.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/random.h"

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <language.h>
#include <const.h>

inherit "/d/Khalakhor/std/npc/dwarf";
inherit HELPER;
inherit INFO;

// Prototypes
void arm_me();

void create_guard() {}

nomask void
create_khalakhor_dwarf()
{
    int ran = random(21) - random(21);

    add_name("guard");
    set_gender((!random(15) ? G_FEMALE : G_MALE));
    // set_random_size();
    add_adj(RANDOM_DETAILED_ADJS(this_object()));

    set_long("The "+query_nonmet_name()+" is one of the many guards "+
      "charged with the duty of protecting the streets of Clach Dun "+
      "and making sure that its laws are upheld.\n");

    set_alignment(600 + (ran * 10));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_helper();

    // Vary the stats by +/- 20
    set_base_stat(SS_STR, 80 + ran);
    set_base_stat(SS_DEX, 60 + ran);
    set_base_stat(SS_CON, 85 + ran);
    set_base_stat(SS_INT, 40 + ran);
    set_base_stat(SS_WIS, 40 + ran);
    set_base_stat(SS_DIS, 100 + ran);

    // Vary the skills by +/- 10
    set_skill(SS_DEFENCE, 65 + (ran / 2));
    set_skill(SS_PARRY, 45 + (ran / 2));
    set_skill(SS_BLIND_COMBAT, 70 + (ran / 2));
    set_skill(SS_WEP_AXE, 75 + (ran / 2));
    set_skill(SS_WEP_CLUB, 60 + (ran / 2));
    set_skill(SS_WEP_POLEARM, 70 + (ran / 2));

    set_skill(SS_APPR_MON, 80 + (ran / 2));
    set_skill(SS_APPR_OBJ, 65 + (ran /2));
    set_skill(SS_AWARENESS, 55 + (ran / 2));
    create_guard();
    arm_me();

    // Make him a little talkative
    set_chat_time(8 + random(5));
    if (!random(2))
	add_chat("I hope this shift ends soon, me legs are killing me!");
    if (!random(3))
	add_chat("I should of had another wiskey before I started this shift.");

    add_chat("Bloody "+ONE_OF(({"goblins", "gobbers", "gobs"}))+
      " are supposed to be massing nearby. If they thinks "+
      "they can topple the Walls of Clach Dun they're nuts!");
    add_chat("I can't wait till we hangs onther murderer.  When "+
      "dat last one pleeded for mercy, then was hung, that "+
      "made the whole event that much more memorable.");

    set_act_time(10 + random(10));
    add_act("grumble");
    add_act("yawn");
    add_act("strokes "+HIS_HER(TO)+" beard.");
    add_act("hiccup");
    add_act("burp loudly");

    set_cchat_time(4 + random(5));
    add_cchat("Bloody murderer!!  We'll catch you and get "+
      "Ye hanged for this crime!");
    add_cchat("For Clach Dun!!!!");
    add_cchat("You'll pay for this crime!");

    set_cact_time(5 + random(5));
    add_cact("emote 's eyes rage in bloodlust");
    add_cact("shout Attacker in Clach Dun!");
    add_cact("emote works "+HIM_HER(TO)+"self into a battle rage.");
    add_cact("growl");


    add_ask(({"whiskey","booze","drink"}), "say We dwarves drink "+
      "nothing but the finest whiskey in Khalakhor, which of "+
      "course we brew ourselves.", 1);
}

void
arm_me()
{
    object weapon;

    setuid(); seteuid(getuid());
    weapon = clone_object(WEP_DIR + ONE_OF(({"spear","battleaxe","warhammer"})));
    weapon->move(this_object());

    if (weapon->query_hands() != W_BOTH)
	clone_object(ARM_DIR + "twrshield")->move(this_object());
    clone_object(ARM_DIR + "chshirt")->move(this_object());
    clone_object(ARM_DIR + "coif")->move(this_object());
    clone_object(ARM_DIR + "boots")->move(this_object());

    command("wield all");
    command("wear armours");
    command("wear all");
}

void
attacked_by(object ob)
{
    if (!query_attack())
	cry_for_assistance(ob, 0);

    ::attacked_by(ob);
}

void
attack_object(object ob)
{
    if (!query_attack())
	cry_for_assistance(ob, 1);

    ::attack_object(ob);
}


public void
add_introduced(string str)
{
    kb_add_introduced(str);
}

public void
init_living()
{
    ::init_living();
    kb_init_living();
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    kb_enter_env(env, from);
}
int
hook_return_intro(string str)
{
    return 1;
}
