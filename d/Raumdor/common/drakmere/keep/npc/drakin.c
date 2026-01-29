/* Lord of Drakmere by Sarr
 * Modified by Toby, 971014 (added random stats *grin*)
 * Repaired typo, Damaris 12/07/2002
 * 2017-05-24 Malus: Changed alignment to enable him to wield his sceptre
 */
#include "defs.h"
#define RAUMDOR_SCRIPTURE_WITNESSES "_raumdor_scripture_witnesses"
#define SCEPTRE DRAKMERE_WEP_DIR + "dl_sceptre"
inherit "/d/Raumdor/std/guard_std";
inherit "/d/Raumdor/lib/intro";
inherit "/lib/unique";

int charges = 3;
string quest_one();
int do_heal();

void
create_monster()
{
    ::create_monster();
    set_name("drakin");
    add_name("lord");
    set_race_name("human");
    set_adj("powerful");
    add_adj("fearless");
    set_short("powerful fearless lord");
    set_long(
      "This man is quite impressive. He stands tall and proud, a stern, grim " +
      "look in his eyes. He is wearing all sorts of decorations that mark " +
      "him as the Lord of Drakmere. He sits back on his throne as he regards " +
      "you carefully.\n");

    set_stats(STAT_ARRAY(220));
    set_alignment(1000);

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 100);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0); /* will accept gifts */
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(CONT_I_WEIGHT, 80000); /* weights 80 kilo's */
    add_prop(CONT_I_HEIGHT, 195);   /* 195 cm high */

    set_hp(query_max_hp()); /* heal fully */
    set_title("the Lord of Drakmere");

    set_act_time(20);
    add_act("emote scratches his chin.");
    add_act("say King Raumdor was a good man.");
    add_act("say I need a brave warrior to help me.");
    add_act("hmm");
    set_cact_time(6);
    add_cact("say I pity you, fool.");
    add_cact("say Die foul creature of hell!");
    add_cact("say Thou shalt die for this!");
    add_ask(({"help", "warrior"}), "@@quest_one@@", 1);
    set_default_answer("say What did you say?", 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    equip(({
      clone_unique(SCEPTRE, 15, DRAKMERE_WEP_DIR + "g_sword", 0, 80),
      DRAKMERE_ARM_DIR + "dl_robe", DRAKMERE_ARM_DIR + "dl_plate",
      DRAKMERE_ARM_DIR + "dl_greaves", DRAKMERE_ARM_DIR + "dl_helm",
      DRAKMERE_ARM_DIR + "dl_gloves", DRAKMERE_ARM_DIR + "eg_boots",
      DRAKMERE_ARM_DIR + "eg_cross",
    }));
    MONEY_MAKE_GC(random(10))->move(TO, 1);
}

string
quest_one()
{
    if (TP->test_bit("Raumdor", 3, 1))
        return "say Thanks, but you have already helped me.\n";
    return "say There is a dangerous necromancer that lives somewhere in the " +
           "mountain pass, hidden in the rocks. He has destroyed many " +
           "caravans that have travelled that way, one of which was that of " +
           "my cousin, Cedric. Cedric was bringing me a very precious " +
           "scripture that we hope to use in our battle against the legions " +
           "of undead. I need you to find out where this foul necromancer is " +
           "and bring me back the scripture. Please, be careful! The foul " +
           "mage has many dark minions serving him.\n";
}

void
reward_one(object ob, object from)
{
    if (!present(from, environment()))
    {
        command("say Where did " + HE(from) + "go?");
        command(
          "emote summons some guards to escort the tome to a secure " +
          "location.");
    }
    else if (from->test_bit("Raumdor", 3, 1))
    {
        command("say Thank you again, brave warrior!");
        command(
          "emote summons some guards to escort the tome to a secure " +
          "location.");
    }
    else if (member_array(from->query_real_name(),
               ob->query_prop(RAUMDOR_SCRIPTURE_WITNESSES)) > -1)
    {
        command("say Thank you brave warrior! We owe you a great debt!");
        command(
          "emote summons some guards to escort the tome to a secure " +
          "location.");
        from->catch_msg("You feel much more experienced.\n");
        from->add_exp_quest(25000);
        from->set_bit(3, 1);
        KLOG("drakmere_one_quest",
          TP->query_real_name() +
            " completed this quest and was awarded with 25000 xp from " +
            file_name(TO) + "\n");
    }
    else
    {
        command("emote examines the tome carefully.");
        command("say You did not see to its retrieval yourself, did you?");
        command(
          "say It is certaintly a forgery, a trick by that foul mage, meant " +
          "to deceive us!");
        command(
          "emote swiftly turns to one of the large braziers and throws the " +
          "tome inside, setting it aflame!");
        command(
          "say Only the true scripture can aid us in the battles ahead!");
    }
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv();
    if (from)
    {
        if (MASTER_OB(ob) == COMMON_OBJ_DIR + "scripture")
        {
            set_alarm(2.0, 0.0, &reward_one(ob, from));
        }
    }
}

int
special_attack(object enemy)
{
    int     a, x;
    mixed * i;
    object *inv;
    inv = FILTER_PLAYERS(all_inventory(E(enemy)));
    if (random(3) && do_heal())
        return 1;
    if (random(10))
        return 0;
    if (random(2))
    {
        command(
          "emote raises his hands over his head, chanting strange holy " +
          "words!");
        tell_room(E(TO),
          "A blinding light leaps out of the cross held by the " +
            TO->query_short() + " and strikes " + QTNAME(enemy) +
            " in the chest, burning " + HIS(enemy) + " flesh and soul!\n",
          enemy);
        enemy->catch_msg(
          "A blinding light leaps out of the cross held by the " +
          TO->query_short() +
          " and strikes you in the chest, burning your flesh and soul!\n");
        enemy->command("scream");
        if (enemy->query_prop(LIVE_I_UNDEAD))
        {
            enemy->catch_msg(
              "Your unholiness causes you even more pain from this holy " +
              "spell.\n");
            enemy->heal_hp(-150 - random(100));
        }
        else
        {
            enemy->heal_hp(-75 - random(100));
        }
        CHECK_DEAD(enemy, TO);
        return 1;
    }

    if (!sizeof(OBJ_IN_ARRAY(SCEPTRE, TO->query_weapon(-1))))
        return 0;

    command("scream");
    tell_watcher(QCTNAME(TO) + " swings " + HIS(TO) +
        " sceptre in an arc through the air toward " + QTNAME(enemy) +
        ". A rainbow of light cascades into " + QTNAME(enemy) +
        "'s body!\n", enemy);
    enemy->catch_msg(QCTNAME(TO) + " swings " + HIS(TO) +
        " sceptre in an arc through the air toward you. A rainbow of " +
        "light cascades into your body!\n", enemy); 
    enemy->hit_me(600 + random(150), MAGIC_DT, TO, -1);
    CHECK_DEAD(enemy, TO);
    return 1;
}

void
do_die(object who)
{
    object arm;
    seteuid(getuid());
    who->add_prop(IS_ENEMY_OF_DRAKMERE, 1);
    arm = clone_object(KEEP_OBJ_DIR + "vault_key");
    arm->move(TO);
    ::do_die(who);
}

int
do_heal()
{
    if (!charges || TO->query_hp() > 400)
       return 0;
    TELL_SEEN(TO, "Suddenly, " + QTNAME(TO) +
        "'s hands glow white and a holy light envelopes " + HIS(TO) +
        " body. " + CAP(HE(TO)) + " looks healed!\n");
    TO->heal_hp(TO->query_alignment());
    charges -= 1;
    return 1;
}

void
attack_object(object ob)
{
    int     i;
    object *obs = query_team();
    for (i = 0; i < sizeof(obs); i++)
        obs[i]->attack_object(ob);
    ::attack_object(ob);
}
