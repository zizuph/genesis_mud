/* Marlin, the weapon master */

#include "../knight/guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit M_FILE

#include "killer.h"

int query_knight_level() { return 3; }

int soul_id;
void get_me_soul();

public void
create_krynn_monster()
{
    int i;

    set_name("marlin");
    set_living_name("marlin");
    set_adj(({"slender","long-haired"}));
    set_title("of Vingaard, the Master Warrior of Solamnia");
    set_gender(0);
    set_introduce(1);
    set_long("This young man seems to enjoy what he's doing very much, as "+
      "he is almost always smiling. Long hair falls around his shoulders, "+
      "from under his helmet. Unlike most Knights, he wears no moustache, "+
      "but is clean shaven. His brown eyes sparkle with life as he takes "+
      "in the many battles raging in the courtyard.\n"+
      "His tunic is decorated with the symbol of the Order of the Crown.\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
	set_base_stat(i, 140 + random(50));

    set_knight_prestige(-9);
    set_alignment(1200);

    set_skill(SS_KATTACK, 130);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 90);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);
    soul_id = set_alarm(1.0, 0.0, &get_me_soul());
    set_alarm(1.0,0.0,"arm_me");

    set_act_time(5);
    add_act("ksmooth h");
    add_act("emote grins in a lopsided, cynical way.");
    add_act("say Constance and her defence, defence, defence! No one has "+
      "ever won a fight by sitting on their hands!\n");
    add_act("tend swords");
    add_act("say Make sure you hang on to your weapons in a fight, without them "+
      "you will surely lose.");
    add_act("kfaith");
    add_act("emote suddenly twirls his blade with a display " +
      "of proficiency.\n");
    add_act("say You must not fight foolishly, but if you see a chance to strike "+
      "a deciding blow, do not hesitate!");
    add_act("emote says: We'll see who's Squires end up "+
      "as the real warriors, eh? Mine, or that boring Constance's...");
    add_act("emote shouts: Ah, the joy of battle! Wait "+
      "until you feel the thrill of fighting! You will never "+
      "be so excited as that, it is truly an amazing feeling.");
    add_act("say I never have time for challenges anymore, I do miss a good "+
      "duel.");
    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'sword'","say It is the duty of a Knight of " +
      "Solamnia to learn how to fight with the sword!",1);
    add_ask(" [about] 'polearm'","say Many a Knight has fallen in " +
      "battle when all they had to depend upon was their lance! It is " +
      "necessary for you to know how to fight with polearms in all " +
      "manners!",1);
    add_ask(" [about] 'club'","say A club is the fallback " +
      "weapon of a Knight, used when nothing else is available.",1);
    add_ask(" [about] 'kattack'","say Watch as your foes fall before "+
      "you with this special technique of fighting!",1);
}

void
get_me_soul()
{
    TO->add_cmdsoul(KOBJ + "solamnian_soul");
    TO->add_cmdsoul(VOBJ + "kattack_special");
    TO->update_hooks();
    remove_alarm(soul_id);
}

int
special_attack(object enemy)
{
	TO->command("sp "+enemy->query_real_name());
    return 0;
}

void
arm_me()
{
    clone_object(VARM + "s_helm")->move(TO);
    clone_object(VARM + "full_armour")->move(TO);
    clone_object(VARM + "s_gauntlets")->move(TO);
    clone_object(VWEP + "s_sword")->move(TO);
    clone_object(VWEP + "s_sword")->move(TO);
    command("wield all");
    command("wear all");
}

void
attacked_by(object ob)
{
    TO->command("shout For Vingaard, and the Orders! You will not get away "+
      "with this attack!");
    TO->command("say I hope you enjoy learning firsthand the superior training "+
      "of the Knights of Solamnia!");
    ::attacked_by();
}
