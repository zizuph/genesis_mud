/* Lauren, the Solamnian shopkeeper */

#include "../../guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit M_FILE

#include "./std/killer.h"

int query_knight_level() { return 2; }

int soul_id;
void get_me_soul();

public void
create_krynn_monster()
{
    int i;

    set_name("lauren");
    set_living_name("lauren");
    set_adj(({"young","blonde-haired"}));
    set_title("of the Royal House of Caerleth in Palanthus, the Loyal "+
      "Squire of Solamnia");
    set_gender(1);
    set_introduce(1);
    set_long("This young lady works at the shop here, handing out the "+
      "armours and weapons that her fellow Knights and Squires come here "+
      "to purchase. Long, curly hair falls around her shoulders, and she "+
      "looks around with an obvious expression of boredom. She is fairly "+
      "tall for a lady, and seems to be quite accustomed to the weight "+
      "of the armour she is wearing, for she moves as freely in it as "+
      "she would in regular clothes.\n"+
      "Her tunic is decorated with the symbol of the Knighthood.\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 60 + random(25));

    set_knight_prestige(-7);
    set_alignment(700);

    set_skill(SS_KATTACK, 100);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 60);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(5) + 5)->move(TO);
    soul_id = set_alarm(1.0, 0.0, &get_me_soul());
    set_alarm(1.0,0.0,"arm_me");

    set_act_time(5);
    add_act("ksmooth h");
    add_act("yawn");
    add_act("say They probably stuck me in here because I'm a girl!");
    add_act("tend chainmail");
    add_act("kaspire");
    add_act("emote expresses her desire to be like her sponsor, Lady Constance "+
      "of the Crown, some day.");
    add_act("emote twists her fingers in her hair in boredom.");
    add_act("smile charm");
    add_act("say The boys here are so funny, they are too worried about the "+
      "'proper' way to treat a lady that they refuse to even spar with me.");
    add_act("say One day I will be as powerful a warrior as Lady Constance!");
    add_act("sigh softly");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'constance' / 'lady'","say Yes! The " +
      "trainer of defence and parry! She's a very wise woman.",1);
    add_ask(" [about] 'boys'","say They " +
      "all look so silly trying to grow moustaches!",1);
    add_ask(" [about] 'palanthus'","say Palanthus is " +
      "my home! When I was young, I would run errands for the Innkeeper " +
      "there, his name was Leiden!",1);
    add_ask(" [about] 'leiden' / 'innkeeper'", "say He still " +
      "lives there! You should visit him!",1);
}

void
get_me_soul()
{
    TO->add_cmdsoul(SOULS + "solamnian_soul");
    TO->update_hooks();
    remove_alarm(soul_id);
}

int
special_attack(object enemy)
{
    TO->command("kattack "+enemy->query_real_name());
    return 0;
}

void
arm_me()
{
    object sword;

    clone_object(VARM + "s_helm")->move(TO);
    clone_object(VARM + "s_armour")->move(TO);
    clone_object(VARM + "s_gauntlets")->move(TO);
    clone_object(VARM + "s_shield")->move(TO);
    clone_object(VARM + "cloak")->move(TO);
    sword = clone_object(VWEP + "s_sword");
    sword->set_pen(30);
    sword->set_hit(35);
    sword->move(TO);
    command("wear all");
    command("wield all");
}

void
attacked_by(object ob)
{
    TO->command("shout You fool, you openly assault a member of the Knighthood "+
      "in her own Keep?");
    TO->command("emote casually draws her longsword from her scabbard, shaking "+
      "her head in disbelief.");
    TO->command("wield all");
    ::attacked_by();
}

