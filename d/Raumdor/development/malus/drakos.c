/* Lord of Drakmere by Sarr 
 * Modified by Toby, 971014 (added random stats *grin*)
 * Repaired typo, Damaris 12/07/2002
 * 2017-05-24 Malus: Changed alignment to enable him to wield his sceptre
 * 2018-03-18 Shanoga: Added interactions regarding lich amulet
 */
#include "defs.h"

#define RAUMDOR_SCRIPTURE_WITNESSES "_raumdor_scripture_witnesses"
#define ARTIFACT_REMOVED 19 

inherit STD_DIR + "guard_std";
inherit LIB_DIR + "intro";
inherit "/lib/unique";

object amulet, priest, scripture, sep;
int    charges = 3;
string quest_one();
int    do_heal();
int    conversion_alarm;
int    step = 0;

void
create_monster()
{
    ::create_monster();
    set_name("drakos");
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
              "scripture you also recovered, we can adjust the " +
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
        "the forest. Upon studying the scripture you retrieved from the " +
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


public float
do_convert_amulet_step(object from, object ob, int step)
{
    switch (step)
    {
        case 0:
            seen_emote("beckons towards a priest at the far end of " +
                "of the chamber.");
            return 3.0;
        case 1:
            if (!present(priest, E(TO)))
            {
                priest = clone_object(COMMON_NPC_DIR + "high_priest");
                priest->clear_act();
                priest->move(E(TO), 1);
                TELL_CAN_SEE(E(TO), "A priest approches " + QTNAME(TO) + ".\n");
                return 2.0;
            }
            return 0.1;
        case 2:
            command("say We have recovered one of those vile devices from " +
              "a lich. Let us retrieve the scripture and make preparations.");
            return 1.0;
        case 3:
            priest->seen_emote("'s eyes open wide.");
            return 1.0;
        case 4:
            priest->seen_emote("nods emphatically.");
            return 1.0;
        case 5:
            TELL_SEEN(priest, QCTNAME(priest) + " shuffles away quickly.\n");
            priest->set_no_show();
            return 3.0;
        case 6:
            command("say A moment.");
            return 3.0;
        case 7:
            scripture = clone_object(COMMON_OBJ_DIR + "scripture");
            scripture->move(priest, 1);
            priest->unset_no_show();
            priest->seen_emote("arrives in a bustle, carrying a tome.");
            return 2.0;
        case 8:
            priest->seen_emote("approaches the font.");
            return 1.0;
        case 9: 
            priest->command("hold " + OB_NAME(scripture));
            return 1.0;
        case 10:
            priest->command("say Let us begin.");
            return 2.0;
        case 11:
            seen_emote("moves to stand near the priest.");
            return 2.0;
        case 12:
            priest->seen_emote("intently studies the " + QSHORT(scripture) + ".");
            return 4.0;
        case 13:
            priest->seen_emote("gestures towards the " + QSHORT(ob) + ".");
            return 2.0;
        case 14:
            seen_emote("holds the " + QSHORT(ob) + " out over the font.");
            return 3.0;
        case 15:
            priest->command("emote begins to chant.");
            return 4.0;
        case 16:
            TELL_CAN_SEE(E(TO), "The " + QSHORT(ob) + " begins to shift color, " +
              "gaining a red hue.\n");
            return 2.0;
        case 17:
            priest->command("emote continues chanting more loudly and quickly.");
            return 4.0;
        case 18:
            priest->seen_emote("reaches into the font with " + HIS(priest) +
              " free hand and splashes the " + QSHORT(ob) + " with water!");
            return 1.0;
        case ARTIFACT_REMOVED:
            TELL_NOT_BLIND(E(TO), "There is a sudden flash of red light!\n");
            TELL_CAN_SEE(E(TO), "The " + QSHORT(ob) + " shatters to pieces, " +
              "revealing a translucent sphere!\n");
            ob->remove_object(ob);
            return 2.0;
        case 20:
            priest->seen_emote("reaches for something in " + HIS(priest) +
              " pocket.");
            priest->emote("chants more slowly now.");
            return 2.0;
        case 21:
            priest->seen_emote("puts " + HIS(priest) + " clenched fist into " +
              "the font.");
            priest->seen_emote("nods encouragingly at " + QTNAME(TO) + ".");
            return 2.0;
        case 22:
            seen_emote("puts the sphere into the font.");
            priest->seen_emote("extends his fingers around the sphere, " +
              "taking hold of it.");
            return 2.0;
        case 23:
            priest->seen_emote("looks searchingly at the " + QSHORT(scripture) + ".");
            priest->emote("stops chanting.");
            return 2.0;
        case 24:
            priest->command("shout LUMIOUS DAE VITOLUS IMMORTO!");
            return 2.0;
        case 25:
            amulet = clone_object(COMMON_ARM_DIR + "life_amulet");
            amulet->move(priest, 1);
            priest->seen_emote("withdraws his hand from the water, revealing a " +
              QSHORT(amulet) + " and attaches it to a small silver chain.");
            return 2.0;
        case 26:
            command("nod " + OB_NAME(from));
            return 2.0;
        case 27:
            priest->command("give " + OB_NAME(amulet) + " to " + OB_NAME(from));
            if (E(amulet) == priest)
            {
                priest->command("hmm");
                priest->seen_emote("places the " + QSHORT(amulet) + " on the floor.");
                command("say It is yours.");
            }
            return 2.0;
        case 28:
            command("say I entrust this artifact of power to you, hero. " +
              "May it assist you in your time of need.");
            return 1.0;
        case 29:
            command("say Know that the amulet will now undo the dark magic " +
              "that burdens the souls of our undead. When you defeat such a " +
              "creaure, they will be freed from the Mortal Realm.");
            return 2.0;
        case 30:
            command("say In doing so, the magical power used to subjugate " +
              "them will be released. We have blessed the amulet with the " +
              "will of the Creator, allowing it to harness such power.");
            return 2.0;
        case 31:
            command("say Merely clutch the amulet tightly to be healed by " +
              "by this power. The more souls you free while wearing it, " +
              "the powerful the effect.");
            return 2.0;
        default:
            command("say Now go with the blessing of the Creator and " +
              "cleanse the forest of that wicked army!");
            return 0.0;
    }
}

public float
do_scripture_needed_step(object from, object ob, int step)
{
    switch(step)
    {
        case 0:
            seen_emote("examines the " + QSHORT(ob) + " carefully.");
            return 3.0;
        case 1:
            command("say This is indeed an artifact of great value to us, " +
              "but not without the holy scripture.");
            return 3.0;
        case 2:
            command("say The scripture provide essential guidance on how " +
             "to transfigure this unholy instrument.");
            return 3.0;
        case 3:
            command("say Once you have recovered it, we can repurpose " +
              "this into a tool of the Creator.");
            return 3.0;
        case 4:
            command("say Until then, it should remain under your attentive " +
              "care.");
            return 2.0;
        default:
            command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
            if (present(ob, TO))
            {
                command("hmm");
                seen_emote("places the " + QSHORT(ob) + " on the floor.");
                ob->move(E(TO), 1);
                command("say Take it.");
            }
            return 0.0;
    }
}

void
receive_phylactery(object from, object ob, int step = 0, int attempt = 0)
{
    /* It would be ideal if we could use the routine system here, come to
     * think of it. There are a lot of cases to handle and we could use it
     * to recover more elegantly from interruption.
     *
     * For now, I'm just going to handle it this way so we can move on to
     * other stuff.
     */
    int finished = 0;
    float delay = 4.0;
    attempt++;
    if (query_attack() || (priest && priest->query_attack()))
    {
        finished = 1;
        command("shout Do not let the artifact fall into the wrong hands!");
        seen_emote("darts towards the southern end of the chamber and " +
          "tosses the " + QSHORT(ob) + " to a guard at the far end, who " +
          "quickly scurries away.");
    }
    else if (query_prop(LIVE_I_BLIND))
    {
        finished = 1;
        command("shout I am blinded. I cannot protect the artifact " +
          "like this! Take it!");
        seen_emote("stumbles towards the southern end of the chamber and " +
          "tosses the " + QSHORT(ob) + " in the air. A guard manages to " +
          "spring backwards to catch it and then dashes out of the chamber.");
    }
    else if (step <= ARTIFACT_REMOVED && !present(ob, TO))
    {
        finished = 1;
        command("say Where did it go!?! I just had it?!");
        command("shout THIEF! Guards, find the artifact!");
    }
    else if (scripture && E(scripture) != priest)
    {
        finished = 1;
        priest->command("say The scripture... it's gone!");
        command("shout THIEF! Guards, find the artifact!");
    }
    else if (attempt > 3)
    {
        finished = 1;
        command("say Enough, let us safeguard this.");
        command("shout Guard!");
        seen_emote("gestures towards a guard at the southern end of the " +
          "chamber.");
        TELL_CAN_SEE(E(TO),
          "A guard haphazardly rushs over and accepts the " + QSHORT(ob) +
          " and then retreats south and out of the chamber.\n"); 
    }
    else if (!CAN_SEE_IN_ROOM(TO))
    {
        command(one_of_list(({
            "say I cannot conduct these matters in the dark.",
            "say Darkness here is unnatural.",
            "say What is it about these two large braziers and all of " +
              "this white marble that convinced someone we wanted it gloomy?",
        })));
    }
    else if (!present(from, E(TO)) || !CAN_SEE(TO, from))
    {
        command(one_of_list(({
            "peer",
            "say Where did " + HE(from) + " go?",
            "shout Where did you go?",
        })));
    } 
    else if (!from->test_bit(DOMAIN, 3, 1))
    {
        delay = do_scripture_needed_step(from, ob, step++);
        if (delay == 0.0)
            finished = 1;
        else
            attempt = 0;
    }
    else
    {
        delay = do_convert_amulet_step(from, ob, step++);
        if (delay == 0.0)
            finished = 1;
        else
            attempt = 0;
    }

    if (finished)
    {
        remove_prop(LIVE_M_NO_ACCEPT_GIVE);
        if (present(ob,TO))
            ob->remove_object(ob);
        return;
    }

    set_alarm(delay, 0.0, &receive_phylactery(from, ob, step, attempt));
}



void
enter_inv(object ob, object from)
{
    ::enter_inv();
    if (from)
    {
        if (MASTER_OB(ob) == COMMON_OBJ_DIR + "scripture")
            set_alarm(2.0, 0.0, &reward_one(ob, from));
        if (MASTER_OB(ob) == COMMON_ARM_DIR + "lich_phylactery")
        {
            add_prop(LIVE_M_NO_ACCEPT_GIVE,
              " is too busy speaking with someone to accept gifts.\n");
            set_alarm(2.0, 0.0, &receive_phylactery(from, ob));
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
