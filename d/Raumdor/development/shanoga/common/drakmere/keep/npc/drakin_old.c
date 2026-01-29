/* Lord of Drakmere by Sarr 
 * Modified by Toby, 971014 (added random stats *grin*)
 * Repaired typo, Damaris 12/07/2002
 * 2018-03-18 Shanoga: Added interactions regarding lich amulet
 * 2017-05-24 Malus: Changed alignment to enable him to wield his sceptre
 */
#include "defs.h"
#define RAUMDOR_SCRIPTURE_WITNESSES "_raumdor_scripture_witnesses"
#undef COMMON_ARM_DIR
#define COMMON_ARM_DIR "/d/Raumdor/development/shanoga/common/arm/"
inherit "/d/Raumdor/std/guard_std";
inherit "/d/Raumdor/lib/intro";
inherit "/lib/unique";

object sep;
int    charges = 3;
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
    add_ask(({"lich", "phylactery", "amulet"}), "@@phylactery@@", 1);
    set_default_answer("say What did you say?", 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    equip(({
      clone_unique(DRAKMERE_WEP_DIR + "dl_scepter", 15,
        DRAKMERE_WEP_DIR + "g_sword", 0, 80),
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
    if (TP->test_domain_bit("Raumdor", 3, 1))
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

string
phylactery()
{
    if (sizeof(filter(object_clones(find_object(COMMON_ARM_DIR + "life_amulet")),
      &operator(==)(,this_player()) @ &environment())))
    {
        return "say Thank you for slaying the lich and bringing the " +
          "phylactery here, but we have already converted it for you. " +
          "Invoke its power by clutching it in your time of need!\n";
    }
    
    if (TP->test_domain_bit("Raumdor",3,1))
    {
        if (sizeof(filter(object_clones(find_object(COMMON_ARM_DIR + "lich_phylactery")),
          &operator(==)(,this_player()) @ &environment())))
        {
            return "say You encountered the lich and not only " +
              "survived, but recovered the phylactery? Using the " +
              "scriptures you also recovered, we can adjust the " +
              "soul-trapping magic within to serve the Creator. Please " +
              "give it to me so we can perform the ceremony for you.\n";
        }
        return "say Long ago, The Nameless One crafted an artifact, " +
        "infused it with a soul-trapping magic, and enclosed it in a " +
        "small box. This phylactery was crafted to interrupt the flow of " +
        "souls from the recently deceased and entrap them before they " +
        "passed on to face the judgment of the Creator. The Nameless One " +
        "has entrusted the phylactery to a dangerous lich who roams the " +
        "forests, tasked with using the magic within to raise more undead " +
        "and strengthen the stranglehold The Nameless One maintains in " +
        "the forest. Upon studying the scriptures you retrieved from the " +
        "necromancer, my priests have found a way to adapt the magic of " +
        "this phylactery and restore trapped souls to the Creator. If only " +
        "we could get the artifact back, then perhaps we could complete " +
        "the ceremony and turn The Nameless One's intentions for good!\n";
    }
    
    return "say Ah, yes. I could use some help in our war against the evil " +
    "forces of darkness in the forest.\n";
}

void
reward_one(object ob, object from)
{
    if (!present(from, environment()))
    {
        command("say Where did " + HE(from) + " go?");
        command(
          "emote summons some guards to escort the tome to a secure " +
          "location.");
        set_alarm(1.0, 0.0, &command("say Now if only we could track down " +
          "that lich in the forest."));
    }
    else if (from->test_domain_bit("Raumdor", 3, 1))
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
        from->set_domain_bit("Raumdor",3, 1);
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
convert_amulet_steps(object ob, object from, int step = 0)
{
    object new_amulet;
    
    if(!present(from,environment()))
    {
        command("peer");
        command("say Where did " + HE(from) + " go?");
        set_alarm(1.0, 0.0, command("emote summons some priests to escort " +
          "the phylactery to a secure location."));
        ob->remove_object();
        KLOG("drakmere_phylactery_fail", TP->query_real_name() + " left " +
          "the room _before_ receiving the converted amulet from " +
          file_name(TO) + "\n");
        return;
    }
    
    step += 1;
    
    switch (step)
    {
        case 1:
            command("say Thank you, brave warrior! We owe you a great debt!");
            set_alarm(1.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 2:
            command("emote beckons for his priests, gives " +
              "the phylactery to them and directs them to retrieve the " +
              "scriptures so they can begin the preparations.");
            set_alarm(3.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 3:
            command("say My priests will use the words of the scriptures " +
              "you returned earlier to extract the amulet from the " +
              "phylactery and alter its manipulation of life magic. Please " +
              "stay here for a moment while they complete the ceremony.");
            set_alarm(4.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 4:
            TELL_CAN_SEE(E(TO),"The priests place the scriptures and the " +
              "phylactery onto a pedestal behind the throne and begin to " +
              "intently study the sciptures.\n");
            set_alarm(4.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 5:
            TELL_CAN_SEE(E(TO),"Surrounding the pedestal, the priests each " +
              "reach out a hand in the air over the phylactery and begin " +
              "to chant in unison.\n");
            set_alarm(4.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 6:
            TELL_CAN_SEE(E(TO),"While the chanting increases in volume and " +
              "intensity, the phylactery begins to glow, filling the room " +
              "with light.\n");
            set_alarm(4.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 7:
            TELL_CAN_SEE(E(TO),"Suddenly there is a bright flash and the " +
              "box shatters to pieces, leaving in its place a spherical " +
              "glass amulet banded by perpendicular silver rings.\n");
            set_alarm(4.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 8:
            command("emote carefully retrieves the amulet from the pedestal.");
            set_alarm(1.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 9:
            command("say I entrust this artifact of power to you, hero of " +
              "Drakmere. May it assist you in your time of need.");
            set_alarm(1.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 10:
            new_amulet = clone_object(COMMON_ARM_DIR + "life_amulet");
            new_amulet->move(this_object());
            command("give amulet to " + from->query_name());
            KLOG("drakmere_phylactery_success", TP->query_real_name() +
              " had the amulet converted by " + file_name(TO) + "\n");
            ob->remove_object(ob);
            set_alarm(3.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 11:
            command("say One last thing! The scriptures state that " +
            "killing the undead in the forest whose souls were captured " +
            "by the lich allows the amulet to re-capture their souls. By " +
            "clutching the amulet, its wearer can release the souls to " +
            "the Creator and receive His blessing.");
            set_alarm(3.0, 0.0, &convert_amulet_steps(ob, from, step));
            return;
        case 12:
            command("say Now go with the blessing of Drakmere and cleanse " +
              "the forest of the wicked army!");
            return;
    }
}

void
convert_amulet(object ob, object from)
{
    if(!present(from,environment()))
    {
        command("peer");
        command("say Where did " + HE(from) + " go?");
        set_alarm(1.0, 0.0, command("emote summons some priests to escort " +
          "the phylactery to a secure location."));
        ob->remove_object(ob);
    }
    else if (from->test_domain_bit("Raumdor",3,1))
    {
        convert_amulet_steps(ob, from);
    }
    else
    {
        command("emote examines the phylactery carefully.");
        command("hmm");
        set_alarm(2.0, 0.0, &command("say This is indeed the lich's " +
          "phylactery, but we need the holy scriptures to convert its " +
          "magic to benefit the Creator rather than The Nameless One! Keep " +
          "the phylactery and return to me with the scriptures, then we " +
          "can fix the phylactery."));
        set_alarm(2.5, 0.0, &command("give phylactery to " +
          from->query_name()));
    }
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
    if (from)
    {
        if (MASTER_OB(ob) == COMMON_ARM_DIR + "lich_phylactery")
        {
            set_alarm(2.0, 0.0, &convert_amulet(ob, from));
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
    if (random(3))
    {
        if (TO->query_hp() < 400)
            do_heal();
        return 1;
    }
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
            enemy->heal_hp(-150 + -random(100));
            if (enemy->query_hp() <= 0)
                enemy->do_die(TO);
            return 1;
        }
        else
        {
            enemy->heal_hp(-75 + -random(100));
            if (enemy->query_hp() <= 0)
                enemy->do_die(TO);
            return 1;
        }
    }
    else
    {
        if (!present(sep, TO))
            return 0;
        tell_room(E(TO),
          "The " + TO->query_short() + " swings his " + sep->query_short() +
            " in an arc through the air, and a rainbow of light spews forth, " +
            "cutting into " +
            QTNAME(enemy) + "'s body!\n",
          enemy);
        enemy->catch_msg("The " + TO->query_short() + " swings his " +
                         sep->query_short() +
                         " in an arc through the air, and a rainbow of light " +
                         "spews forth, cutting into your body!\n");
        command("scream");
        enemy->hit_me(600 + random(150), MAGIC_DT, TO, -1);
        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);
        return 1;
    }
}

void
do_die(object who)
{
    object arm;
    seteuid(getuid());
    who->add_prop(IS_ENEMY_OF_DRAKMERE, 1);
    arm = clone_object(KEEP_DIR + "vault_key");
    arm->move(TO);
    ::do_die(who);
}

int
do_heal()
{
    if (charges == 0)
    {
        return 0;
    }
    set_this_player(TO);
    write("The " + TO->query_short() +
          " glows white and your body is enveloped in a holy light that " +
          "soothes your wounds.\n");
    write("You feel much better.\n");
    TO->heal_hp(TO->query_alignment());
    charges = charges - 1;
    say(QCTNAME(TO) + "'s hands glow white and envelopes " + HIS(TO) +
        " body in a holy light that heals " + HIS(TO) + " wounds.\n");
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
