/* This is an old man who's wandering the moors in search of a 
herb. To get rewarded for the grotto quest, he must have told
you the name of the incantation needed to pass into the grotto
area, and the only way to get him to do that is to perform a 
task for him. */


inherit "/std/monster";            
inherit "/d/Genesis/lib/intro"; 
inherit "/std/act/domove";

#include <ss_types.h> 
#include <macros.h>  
#include <stdproperties.h> 
#include <const.h>  
#include <tasks.h> 
#include "../pond.h";

public int special_attack(object enemy);
public string reply();
public void react_give(object ob, object from);
public void leave();
public void equip_me();
public void enter_inv(object ob, object from);
public void greet(object who);
public void introduce(object who);

void
create_monster()
{
    set_name("hylar");
    add_name("hylar");
    set_race_name("human");

    add_adj("old");
    add_adj("irritable");

    set_title("the Retired Sorcerer");
    set_gender(G_MALE);

    set_long("This old man looks as if he's searching for" +
        " something." +
        " His eyes are framed by thick glasses, his gaze sweeping" +
        " the area. He doesn't seem to take much notice of you." +
        " He has a faint aura of power surrounding him.\n");

    set_alignment(150);

    set_base_stat(SS_STR, 80);
    set_base_stat(SS_DEX, 100);
    set_base_stat(SS_CON, 80);
    set_base_stat(SS_INT, 120);
    set_base_stat(SS_WIS, 80);
    set_base_stat(SS_DIS, 60);

    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_SPELLCRAFT, 50);
    set_skill(SS_HERBALISM, 50);
    set_skill(SS_UNARM_COMBAT, 70);
   
    set_hp(query_max_hp());

    set_act_time(10);
    add_act("emote sweeps the ground with his gaze.");
    add_act("emote mutters to himself.");
    add_act("emote stretches his weary body.");
    add_act("emote looks at you briefly, as if searching you for" +
        " something.");
    add_act("emote cleans his glasses.");
    add_act("say Move along! Can't you see I'm herbing here?");
    add_act("emote goes hrmph!");
    add_act("sigh impatiently");


//  set_restrain_path("/d/Calia/mountain/road/m");
//  set_random_move(20);

    add_ask(({"help", "quest", "task", "about task",
        "about quest"}), VBFC_ME("reply"), 1);
    add_ask(({"angeltear", "Angeltear"}), "say Angeltear is a" +
        " white mushroom.", 1);
    add_ask(({"hint", "hints", "where"}), "If I knew exactly where" +
        " it's found, I wouldn't be asking you to help me!", 1);
    add_ask(({"grotto", "Grotto"}), "say You're looking for the" +
        " Grotto, eh?" +
        " Don't expect me to help you out.", 1);
    add_ask("truth", "say You want the truth? You can't handle" +
        " the truth!", 1);

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 70000);
    add_prop(CONT_I_HEIGHT, 90);
    add_prop(NPC_I_NO_LOOKS,1);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

int
special_attack(object enemy)
{
    int i, x;
    object *weapons, *adj_rooms, *adj_rooms_desc, *enemies;

    enemies = TO->query_enemy(-1);
    x = random(sizeof(enemies));
    enemy = enemies[x];
    weapons = filter(all_inventory(enemy),
        &operator(!=)(0) @ &->query_wielded());
    adj_rooms = environment(TO)->query_exit_rooms();
    adj_rooms_desc = environment(TO)->query_exit_cmds();
    i = random(sizeof(adj_rooms));

    if (random(10) && sizeof(weapons) > 0) 
    {
        return 0;
    }

    if (resolve_task(TASK_ROUTINE, ({TS_INT, SS_SPELLCRAFT}), enemy, 
        ({TS_STR, SS_FORM_ABJURATION})) < 0)
    {
        enemy->catch_msg(QCTNAME(TO) + " makes a quick motion" +
            " with his hand and barks an alien word, and suddenly" +
            " your "+ weapons[0] +" jerks in your hand, but you" +
            " manage to hang onto it.\n");
        tell_room(environment(TO), QCTNAME(TO) + " makes a quick" +
            " motion with his hand and barks an alien word, and" +
            " suddenly the " + weapons[0]->query_name() + " wielded"+
            " by " + QTNAME(enemy) + " jerks violently," +
            " but " + enemy->query_pronoun() + " manages to hang" +
            " onto it.\n", enemy);
        command("smirk");
    }
    else
    {
        weapons[0]->move(adj_rooms[random(sizeof(adj_rooms))]);
        enemy->catch_msg(QCTNAME(TO) + " makes a quick motion with" +
            " his hand and barks an alien word, and suddenly your " + 
            weapons[0]->query_name() + " flies out of your grasp!" +
            " The weapon flies " + adj_rooms_desc[i] + ".\n");
        tell_room(environment(TO), QCTNAME(TO) + " makes a quick" +
            " motion with his hand and barks an alien word, and" +
            " suddenly the " + weapons[0]->query_name() + " flies" +
            " out of the hands of " + QTNAME(enemy) + "!" +
            " The weapon flies " + adj_rooms_desc[i] + ".\n", enemy);
        tell_room(adj_rooms[i], "A " + weapons[0]->query_name() + 
            " suddenly flies in and falls to the ground.\n");
        command("say Ah, now the fight is more fair!");
    }
}

string
reply()
{
    if (TP->query_prop(GQ_I_TALK_WANDERER) ||
        TP->test_bit(GQ_DOMAIN, GQ_GROUP, GQ_BIT))
    {
        return "say I don't need any further help from you.";
    }
    else
    {
        return "say If you want to help me, don't just stand there!"+
            " Go find me an Angeltear.";
    }
}

void
react_give(object ob, object from)
{
    if (!CAN_SEE(TO, from) || !CAN_SEE_IN_ROOM(TO))
    {
        command("say What's going on? I can't see you!");
    }
    else
    if (!living(from))
    {
        command("emote closely examines the herb, and puts it in" +
           " his pouch with a disappointed look.");
        command("put herbs in pouch");
    }
    else
    if (member_array(from, query_enemy(-1)) > -1)
    {
        command("say You can keep it, bastard!");
        command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
    }
    else
    if (!ob->query_herb_name())
    {
        command("say I'm not interested in this.");
        command("drop " + OB_NAME(ob));
    }
    else
    if (ob->query_herb_name() 
        && ob->query_herb_name() != "angeltear")
    {
        command("say Thank you. Not exactly what I need, though.");
        command("put herbs in pouch");
    }
    else
    if (ob->query_herb_name() == "angeltear")
    {
        command("emote studies the pale white mushroom carefully.");
        if (!from->test_bit(GQ_DOMAIN, GQ_GROUP, GQ_BIT)
            && !from->query_prop(GQ_I_TALK_WANDERER))
        {
            command("say Yes, this is exactly what I'm looking for!"+
                " You've done good, so I'll let you in on a" +
                " secret.");
            command("whisper " + OB_NAME(from) + " The incantation" +
                " you have to pronounce is known as klifsims. I'll" +
                " finally be able to enter the grotto, and so can" +
                " you, if you have another Angeltear! Don't expect" +
                " me to tell you where it is though.");
            command("smile wryly");
            from->add_prop(GQ_I_TALK_WANDERER, 1);
            command("put herbs in pouch");
            set_alarm(2.0, 0.0, &leave());
        }
        else
        {
            command("say Yes, I could always use another one of" +
                " these. You've helped me before though.");
            command("put herbs in pouch");
        }
    }
}

void
leave()
{
    command("say It's time for me to go.");
    command("emote barks a few words of power and disappears" +
        " in a flash of light.");
    remove_object();
}

void
enter_inv(object ob, object from)
{
    if (living(from) || ob->query_herb_name())
    {
        set_alarm(1.0, 0.0, &react_give(ob, from));
    }
    ::enter_inv(ob, from);
}

void
equip_me()
{
    object pouch, coat;
    seteuid(geteuid());

    coat = clone_object("/d/Calia/pond/objects/wanderer_coat.c");
    coat->move(TO);

    pouch = clone_object("/d/Calia/sea/objects/herbpouch");
    pouch->move(TO);

    command("tie pouch");
    command("wear all");
}

void
greet(object who)
{
    command("emote nods at you faintly in acknowledgement.");
}

void
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who));
}