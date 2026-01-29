#pragma strict_type

#include "defs.h"
#include <filter_funs.h>

inherit "/std/monster";

object lord;
object quester;
int dagger_seen,
    cloth_seen,
    remembered_murder;

public void create_monster();
public void init_living();
public string react_ask_help();
public string react_ask_killer();
public string react_ask_murder();
public string react_ask_work();
public string react_ask_dagger();
public string react_ask_cloth();
public void remember_murder(object ob);
public void remember_murder_2(object ob);
public string my_default_answer(); 

public void
create_monster()
{
    set_living_name("lenthin");
    set_name("lenthin");
    set_race_name("human");
    add_name("seer");
    add_name("advisor");
    add_name("seer-advisor");
    add_name("ghost");
    add_name("undead");
    add_name("man");
    set_adj("old");
    add_adj("withered");
    set_title("Seer-Advisor to the Lord of Castle Chimera");
    set_long("This old man is richly clothed in black robes made " +
        "of the finest fabric. They're in beautiful condition, " +
        "aside from a small scrap of cloth that has been torn from " +
        "the hems. He has an aura of wisdom about him, but he " +
        "seems quite agitated about something.\n");

    set_gender(G_MALE);
    default_config_npc(75);
    set_invis(100);

    add_prop(LIVE_I_UNDEAD, 10);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 5);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 300);

    set_act_time(40);
    add_act("emote paces around the room restlessly.");
    add_act("mutter");
    add_act("emote says to himself: I should have told him!");
    add_act("emote knuckles his forehead.");
    add_act("say My Lord, what have I let happen to thee?");
    add_act("wail");
    add_act("say Murdered he was, and I could have stopped it!");
    add_act("say Leave me to my misery. I must think...");
    add_act("say I must make amends...somehow...");

    add_ask(({"help", "quest", "task"}),
        "@@react_ask_help", 1);
    add_ask(({"murderer", "killer", "assassin", "slayer"}),
        "@@react_ask_killer", 1);
    add_ask(({"galyn", "lord galyn", "Galyn", "Lord Galyn",
        "murder", "victim", "who was murdered"}),
        "@@react_ask_murder", 1);
    add_ask(({"him","lord","Lord","his lord","his Lord"}),
        "@@react_ask_lord", 1);
    add_ask(({"name","job","work"}), "@@react_ask_work", 1);
    add_ask(({"dagger", "knife"}), "@@react_ask_dagger", 1);
    add_ask(({"cloth", "tear", "fabric", "robe"}), "@@react_ask_cloth", 1);

    set_default_answer(my_default_answer); 
    set_dont_answer_unseen(1);

    reset_euid();
    SEER_BRAIN->add_seer(TO);    
}


public string
my_default_answer()
{
    command("emote doesn't seem to notice your question."); 
    return ""; 
}


public int 
test_for_dagger(object who)
{
    object ob;

    if ((objectp(ob = present(ELDORAL_DAGGER_NAME, who)) && 
        !ob->query_prop(OBJ_I_LORD_SAW_ME)) || 
        who->test_bit("Calia", ELDORAL_QUEST_GROUP, 
            ELDORAL_SEER_QUEST_BIT)) 
    { 
        set_alarm(0.0, 0.0, remove_object); 
        return 1; 
    } 
    return 0; 
}

public void
init_living()
{
    ::init_living();
    if (test_for_dagger(TP))
        return; 

    if (query_invis())
    {
        set_invis(0);
        tell_room(environment(TO), QCTNAME(TO) + " arrives.\n");
    }
}

public string
react_ask_help()
{
    command("blink");
    command("say You wish to help a spineless wretch like me? " +
        "Light bless you! If I could only bring the slayer of " +
        "my precious Lord to justice, my heart would be light " +
        "again.");
    TP->add_prop(LIVE_I_SEER_QUEST,
        TP->query_prop(LIVE_I_SEER_QUEST) | SEQ_SPOKE_SEER);
    return "";
}

public string
react_ask_killer()
{
    string extra;
    int skill;

    extra = SEER_BRAIN->query_location("index");
    command("say I know not who it was, only that it " +
        "happened, and afterwards the sounds of a small boat were " +
        "heard in the lake to the " + extra + " of Eldoral Isle, " +
        "and the dagger my lord was slain with never recovered.");
    skill = TP->query_skill(SK_ELDORAL_CASTLE_NAME);
    if (!(skill & SK_ELDORAL_NAME_VALUE))
    {
        TP->set_skill(SK_ELDORAL_CASTLE_NAME, 
            skill | SK_ELDORAL_NAME_VALUE);
    }
    if (TP->query_prop(LIVE_I_SEER_QUEST) & SEQ_SPOKE_SEER)
    {
        command("say Have you discovered his identity yet?");
        command("smile hopefully");
    }
    else
    {
    TP->add_prop(LIVE_I_SEER_QUEST,
        TP->query_prop(LIVE_I_SEER_QUEST) | SEQ_SPOKE_SEER);
    }
    return "";
}

public string
react_ask_murder()
{
    command("say Murdered he was, and I saw it coming! But " +
        "I said nothing, I feared for my life...");
    command("wail");
    command("say Curse my eyes, I said nothing!");
    return "";
}

public string
react_ask_lord()
{
    int skill;
    command("say Who is he? Lord Galyn of Castle Chimera, of " +
        "course. I swore my life to him, and cost him his!");
    command("emote curses hotly at himself.");
    skill = TP->query_skill(SK_ELDORAL_CASTLE_NAME);
    if (!(skill & SK_CASTLE_NAME_VALUE))
    {
        TP->set_skill(SK_ELDORAL_CASTLE_NAME, 
            skill | SK_CASTLE_NAME_VALUE);
    }
    return "";
}

public string
react_ask_work()
{
    int skill;
    command("say Eh? Oh, I'm Lenthin, Seer-Advisor to Galyn, " +
        "Lord of Castle Chimera. Or I was, before I let him " +
        "be murdered!");
    skill = TP->query_skill(SK_ELDORAL_CASTLE_NAME);
    if (!(skill & SK_CASTLE_NAME_VALUE))
    {
        TP->set_skill(SK_ELDORAL_CASTLE_NAME, 
            skill | SK_CASTLE_NAME_VALUE);
    }

    FILTER_LIVE(all_inventory(environment(TO)))->add_introduced("lenthin");
    command("wail");
    return "";
}

public string
react_ask_dagger()
{
    if (!present(ELDORAL_DAGGER_NAME, TP))
    {
        command("shrug");
        command("say I don't know much about that, I'm afraid.");
    }
    else
    {
        command("frown");
        command("say That dagger looks familiar somehow...I " +
            "remember something...or do I?");
        command("confused");
        command("say It's quite cloudy...couldn't have been " +
            "important.");
        dagger_seen = 1;
    }

    if (dagger_seen && cloth_seen)
    {
        set_alarm(5.0, 0.0, &remember_murder(TP));
    }
    return "";
}

public string
react_ask_cloth()
{
    if (!present(ELDORAL_CLOTH_NAME, TP))
    {
        command("shrug");
        command("say I don't know much about that, I'm afraid.");
    }
    else
    {
        command("blink");
        command("say Curious...it almost looks like the same " +
            "material as my robe...");
        command("ponder");
        command("say How could that be?");
        cloth_seen = 1;
    }

    if (dagger_seen && cloth_seen)
    {
        set_alarm(5.0, 0.0, &remember_murder(TP));
    }
    return "";
}

public void
show_hook(object what)
{
    if (what->id(ELDORAL_DAGGER_NAME))
        react_ask_dagger();
    else if (what->id(ELDORAL_CLOTH_NAME))
        react_ask_cloth();
}

public void
remember_murder(object ob)
{
    if (!present(ob, environment(TO)))
        return;

    if (remembered_murder)
        return;

    command("emote glances down, noticing, as if for the first " +
        "time, a tear from the hem of his robes.");
    command("frown");
    command("emote looks back to the dagger in you carry.");
    command("emote looks down to the hem of his robe again, and " +
        "his eyes suddenly widen in horror.");
    set_alarm(3.0, 0.0, &remember_murder_2(ob));
    remembered_murder = 1;
    environment(TO)->remove_timeout(ob);
}

public void
remember_murder_2(object ob)
{
    if (!present(ob, environment(TO)))
        return;

    command("emote whispers hoarsely: No, it couldn't have been " +
        "me...I couldn't have...but I...");
    command("emote screams: NOOOOOOOOOO!");
    lord = SEER_BRAIN->query_poltergeist();
    lord->react_seer(TO);
    quester = ob;
}

public void
react_lord(object ob)
{
    command("emote starts to cringe in fear and humiliation, " +
        "but then something seems to take hold of him, an old " +
        "power that has lain dormant.");
    command("say I killed you once, I'll do it again!");
    set_alarm(8.0, 0.0, &ob->react_seer_2(TO));
}

public void
react_lord_2(object ob)
{
    command("emote snarls in anger, and spins around, running " +
        "for the " + environment(TO)->query_seer_wall(quester) + 
        " wall of the chamber. Reaching out, he presses his " +
        "hand against the " +
        LANG_WORD(environment(TO)->query_seer_stone(quester)) + 
        " stone from the bottom of the wall.");
    set_alarm(8.0, 0.0, &ob->react_seer_3(TO));
} 

public void
react_lord_3(object ob)
{
    command("emote presses against the stone, and to his apparent " +
        "shock, his hand passes straight through the stone! He " +
        "draws it back out, and simply stares at it for a moment.");
    set_alarm(8.0, 0.0, &ob->react_seer_4(TO));
}
   
public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object *temp;
    int i;

    if (dt == MAGIC_DT)
        return ::hit_me(wcpen, dt, attacker, attack_id);

    temp = attacker->query_weapon(-1);
    for (i = 0; i < sizeof(temp); i++)
    {
        if (temp[i]->query_attack_id() == attack_id)
        {
            if (temp[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
                return ::hit_me(wcpen, dt, attacker, attack_id);
            else
            {
                tell_object(attacker, "Your " + temp[i]->query_name() +
                    " passes harmlessly through the old man!\n");
                tell_room(environment(), QCTNAME(attacker) + "'s " +
                    temp[i]->query_name() + " passes harmlessly " +
                    "through the old man!\n", attacker);
                return ({0, 0, 0, 0});
            }
        }
    }
    tell_object(attacker, "Your " + 
        attacker->cr_attack_desc(attack_id) + " passes " +
        "harmlessly through the old man!\n");
    tell_room(environment(), QCTNAME(attacker) + "'s " +
        attacker->cr_attack_desc(attack_id) + " passes " +
        "harmlessly through the old man!\n", attacker);
    return ({0, 0, 0, 0});
}

public void
finish_quest()
{
    if (!quester || !present(quester, environment(TO)))
        return;

    seteuid(getuid());
    BITMASTER->set_bit(ELDORAL_SEER_QUEST_BIT, quester);
    quester->add_prop(LIVE_I_DID_SEER_QUEST, 1);
    quester->remove_prop(LIVE_I_SEER_QUEST);
    SEER_BRAIN->reset_quest();
    environment()->reset_room();
    remove_object();
}
