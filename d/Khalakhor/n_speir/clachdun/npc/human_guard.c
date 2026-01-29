#include "local.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/random.h"

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <language.h>
#include <const.h>

inherit "/d/Khalakhor/std/npc/human";
inherit INFO;
inherit HELPER;

// Prototypes
void arm_me();

void create_guard() {}

nomask void
create_khalakhor_human()
{
    int ran = random(21) - random(21);

    add_name("guard");
    set_gender((!random(10) ? G_FEMALE : G_MALE));
    add_adj(RANDOM_DETAILED_ADJS(this_object()));
    // set_random_size();

    set_long("The "+query_nonmet_name()+" is one of the many "+
      "guards charged with the duty of protecting the streets "+
      "of Clach Dun and making sure that its laws are upheld.\n");

    set_alignment(600 + (ran * 15));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_helper();

    set_base_stat(SS_STR, 80 + ran);
    set_base_stat(SS_DEX, 80 + ran);
    set_base_stat(SS_CON, 80 + ran);
    set_base_stat(SS_INT, 70 + ran);
    set_base_stat(SS_WIS, 70 + ran);
    set_base_stat(SS_DIS, 90 + ran);

    set_skill(SS_WEP_SWORD, 70 + (ran / 2));
    set_skill(SS_WEP_POLEARM, 65 + (ran / 2));
    set_skill(SS_DEFENCE, 60 + (ran / 2));
    set_skill(SS_PARRY, 70 + (ran / 2));
    set_skill(SS_BLIND_COMBAT, 65 + (ran / 2));

    set_skill(SS_APPR_MON, 75 + (ran / 2));
    set_skill(SS_AWARENESS, 70 + (ran / 2));

    create_guard();
    arm_me();
}

void
arm_me()
{
    object weapon;

    setuid(); seteuid(getuid());
    weapon = clone_object(WEP_DIR + ONE_OF(({"spear","halberd", "claymore"})));
    weapon->move(this_object());

    if (weapon->query_hands() != W_BOTH)
	clone_object(ARM_DIR + "twrshield")->move(this_object());
    clone_object(ARM_DIR + "chshirt")->move(this_object());
    clone_object(ARM_DIR + "boots")->move(this_object());
    clone_object("/d/Khalakhor/common/kilts/"+
      ONE_OF(get_dir("/d/Khalakhor/common/kilts/")))->move(this_object());

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
