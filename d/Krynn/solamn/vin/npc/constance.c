/* Constance by Morrigan Jan 97 */

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

    set_name("constance");
    set_living_name("constance");
    set_adj(({"graceful","commanding"}));
    set_title("the Lady Warrior of Solamnia");
    set_gender(1);
    set_introduce(1);
    set_long("Stern but attractive, this woman likes to bark out orders to "+
      "Squires training in the area. Her bright blue eyes take in the goings "+
      "on of the trainees, and her long blonde hair is tied back to keep "+
      "from hindering her movement. She notices you with disinterest, seemingly "+
      "intent on any Squires she is training presently. She moves with a grace "+
      "that makes you wonder if she has elven blood.\n"+
      "Her tunic is decorated with the symbol of the Order of the Crown.\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 150 + random(50));

    set_knight_prestige(-9);
    set_alignment(1200);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_KATTACK, 130);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 60);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);
    soul_id = set_alarm(1.0, 0.0, &get_me_soul());
    set_alarm(1.0,0.0,"arm_me");

    set_act_time(5);
    add_act("ksmooth");
    add_act("kstudy");
    add_act("smile briefly");
    add_act("emote shakes her head, saying: Like this.\n"+
      "She steps forward, effortlessly parrying away an imagined blow.\n");
    add_act("say Blasted Marlin is going to get these Squires killed, "+
      "teaching them to be reckless!");
    add_act("say And he's always dueling, too. Sometimes I wonder how "+
      "sane Marlin really is.");
    add_act("say Calm yourself, and fight with caution! Don't be like that "+
      "hothead, Marlin...");
    add_act("tend shield");
    add_act("say In my opinion, the best way to win a fight is to keep your "+
      "head, to fight defensively. Wait for the other to make a mistake, and "+
      "then capitalize on it.");
    add_act("ksomber");
    add_act("say Here, watch. Advance on me, and watch how I defend. And don't "+
      "you dare 'go easy' on me.");
    add_act("emote says in a reprimanding tone: It is best to learn "+
      "to fight blind. Make each swing count, don't tire yourself with "+
      "needless swings.");
    add_act("emote shouts: I realize you are eager, "+
      "but you must learn to fight with patience, not desperation.");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'defence' / 'parry'",
      "say Do you prefer the defensive style of fighting as well?",1);
    add_ask(" [about] 'blindfighting'","say Learning to fight " +
      "when all around you is dark can save your life.",1);
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
    clone_object(VARM + "cloak")->move(TO);
    clone_object(VARM + "s_shield")->move(TO);
    clone_object(VARM + "s_helm")->move(TO);
    clone_object(VARM + "full_armour")->move(TO);
    clone_object(VARM + "s_gauntlets")->move(TO);
    clone_object(VWEP + "s_sword")->move(TO);
    command("wield all");
    command("wear all");
}

void
attacked_by(object ob)
{
    TO->command("kstudy "+ob->query_real_name());
    TO->command("say Have you lost your mind? Attacking a Knight inside the "+
      "Keep? Apparently so.");
    ::attacked_by();
}
