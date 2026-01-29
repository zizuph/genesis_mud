/* Bernard of Daltigoth, Trainer of the Knights by Morrigan */

#include "../knight/guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit M_FILE

#include "killer.h"

int query_knight_level() { return 5; }

int soul_id;
void get_me_soul();

string query_race_name()
{
    return(calling_function() == "query_presentation" ? "Ergothian" :
      "human");
}

public void
create_krynn_monster()
{
    int i;

    set_name("bernard");
    set_living_name("bernard");
    set_adj(({"dark-haired","middle-aged"}));
    set_title("of Daltigoth, the Knight of Mind");
    set_gender(0);
    set_introduce(1);
    set_long("An aged veteran of battle, this man looks like the Knight "+
      "children's stories sing praises of. He has a grand flowing moustache "+
      "with only a touch of grey in the otherwise auburn hair. His eyes are "+
      "a keen, but gentle, chestnut. His hair is cut short around his ears, "+
      "and he studies his surroundings calmly.\n"+
      "His tunic is decorated with the symbol of the Order of the Rose.\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 130 + random(50));

    set_knight_prestige(-9);
    set_alignment(1200);

    set_skill(SS_KATTACK, 120);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 70);
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
    add_act("ksmooth");
    add_act("kstudy");
    add_act("smile thoughtfully");
    add_act("say My family was scorned by our relatives, after we left Ergoth "+
      "to serve under Vinas Solamnus in the Rose Rebellion.");
    add_act("emote studies a few of the training Squires, giving them hints " +
      "on how to move in combat.");
    add_act("say It's not always a sword that wins a battle. You must study "+
      "your opponent, learn their weaknesses, and then use it against them.");
    add_act("ksage");
    add_act("emote throws his cloak over his shoulder as he paces.");
    add_act("emote claps briefly, saying: Well done, well done.");
    add_act("emote demonstrates on techniques of maneuvering in combat, and "+
      "you are mildly surprised to see a man of his age moving with such grace.");
    add_act("say Just maneuvering one's self in combat can be a dominating force "+
      "in a fight. With the proper technique, you can protect others, or even "+
      "force your opponents to fight you.");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'maneuver' / 'maneuvers' / 'technique' / 'techniques'",
      "say As you can see, Knights are trained not only in conventional " +
      "warfare, but also in military tactics and strategy.",1);
    add_ask(" [about] [rose] 'rebellion'",
      "say Aye, the Rose Rebellion was a "+
      "hard, but necessary, event to withstand. Vinas Solamnus broke with "+
      "the Emperor of Ergoth to form the Knights of Solamnia.",1);
    add_ask(" [about] 'rescue'", "say The ability to " +
      "save those in need is very important to a Knight.",1);
    add_ask(" [about] 'block'", "say Being able to mete out " +
      "justice to an unjust and evil opponent who has no hope for " +
      "redemption requires that they have no avenue for escape.",1);
    add_ask(" [about] 'awareness'","say The ability of being " +
      "aware of your surroundings can save your life.", 1);
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
    clone_object(VWEP + "two_handed_sword")->move(TO);
    command("wear all");
}

void
attacked_by(object ob)
{
    TO->command("emote drops his hand to the hilt of his sword as his face darkens "+
      "into a frown.");
    TO->command("emote draws his two handed sword.");
    TO->command("wield all");
    ::attacked_by();
}



