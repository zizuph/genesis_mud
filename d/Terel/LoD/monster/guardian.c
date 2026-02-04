#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <language.h>
#include <std.h>

#include "/d/Terel/LoD/dungeon/quest.h"
#include "/d/Terel/include/quest_bits.h"

#define SEQ  "dq_sequence"

int attack_alarm = 0;
object caller = 0;

public int
is_caller()
{
    if (caller && ENV(caller) == ETO)
        return 1;
        
    return 0;
}

public string
cname()
{
    if (!caller)
        return "";
        
    return caller->query_real_name();
}

public string
seq1()
{
    if (!is_caller())
    {
        seq_delete(SEQ);
        return "say Hmm...";
    }
    command("smile at " + cname());
    command("whisper to " + cname() + " I'm glad to have you here. " +
            "But finding this beautiful place is not enough if " +
            "you want to gain experience and find the Treasure.");
            
    if (CAN_SEE_IN_ROOM(caller))
        return "emote hesitates for a while to study the cave.";
    else
        return "emote hesitates for a while.";
}

public string
seq2()
{
    if (!is_caller())
    {
        seq_delete(SEQ);
        return "say Hmm...";
    }
    command("point at crystal");
    command("whisper to " + cname() + " It is in there. " +
            "The Treasure was placed within the crystal by the " +
            "wicked sorcerer Sawoq. I'm its Guardian and the Avenchir " +
            "was its Keeper.");
            
    if (CAN_SEE_IN_ROOM(caller))
        return "emote hesitates for a while to study the crystal.";
    else
        return "emote hesitates for a while.";
}

public string
seq3()
{
    if (!is_caller())
    {
        seq_delete(SEQ);
        return "say Hmm...";
    }
    command("smile sadly");
    command("whisper to " + cname() + " Now to you. " +
            "Due to Sawoq's wickedness it's very difficult to " +
            "break the crystal seal and get hold of the Treasure.");
            
    if (CAN_SEE_IN_ROOM(caller))
        return "emote hesitates for a while to study you.";
    else
        return "emote hesitates for a while.";
}

public string
seq4()
{
    if (!is_caller())
    {
        seq_delete(SEQ);
        return "say Hmm...";
    }
    command("smile hopefully");
    command("whisper to " + cname() + " To retrieve it though, you " +
            "must, in some aspects, have the head of an ogre, the " +
            "quickness of a thief, and the resemblance of a wolf. " +
            "That is all I know.");
    command("whisper to " + cname() + " And remember, " +
            "the Avenchirs took great effort in keeping the demoness " +
            "captured in their dungeon. She used to be a liason of Sawoq.");
    command("say That was it.");
    
    if (CAN_SEE_IN_ROOM(caller))
        return "emote sinks into one of his daydreams.";
    else
        return "sigh";
}

public void
start_guardian_seq()
{
    if (sizeof(seq_query(SEQ)))
        return;
    
    seq_clear(SEQ);
    seq_new(SEQ);
    seq_addfirst(SEQ, ({2, "@@seq1", "@@seq2", "@@seq3", "@@seq4"}));
}

public void
set_caller(object ob)
{
    caller = ob;
    start_guardian_seq();
}

public object
query_caller()
{
    return caller;
}

public string
my_act()
{
    if (caller && CAN_SEE_IN_ROOM(caller)) {
        switch (random(2)) {
            case 1: return "emote looks carefully at the crystal.";
            case 0: return "emote looks at you with his grey eyes.";
        }
    } else {
        switch (random(3)) {
            case 2: return "touch crystal";
            case 1: return "emote taps with his staff.";
            case 0: return "emote mumbles something.";
        }
    }
}

public void
create_monster()
{
    ::create_monster();
    
    set_name("bryask");
    add_name("guardian");
    set_race_name("human");
    set_adj(({"silver-haired", "old"}));
    set_long("A very old human. He has long silverish hair. He is " +
             "dressed in a plain greyish robe and in his left hand " +
             "he holds a long wooden staff. His old eyes are grey " +
             "and his gaze is soft yet at the same time you get " +
             "the feeling that he has great powers.\n");
    set_title("Guardian of the Treasure");

    default_config_npc(60);

    set_skill(SS_AWARENESS, 95);
    set_hp(9000);
    set_mana(9000);

    add_prop(LIVE_I_SEE_DARK, 20);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
    add_prop(CONT_I_WEIGHT, 73000);
    add_prop(CONT_I_VOLUME, 73000);
    add_prop(CONT_I_HEIGHT, 170);
    add_prop(CONT_I_MAX_WEIGHT, 143000);
    add_prop(CONT_I_MAX_VOLUME, 123000);
    
    set_all_attack_unarmed(20, 20);
    set_all_hitloc_unarmed(15);
        
    set_act_time(11);
    add_act("@@my_act");
    
    add_ask(({"quest", "treasure"}), "@@ask_quest", 1);
    add_ask(({"crystal"}), "@@ask_crystal", 1);
    add_ask(({"goblet", "golden goblet"}), "@@ask_goblet", 1);
}

public string
ask_crystal()
{
    if (is_caller() && TP == caller)
    {
        command("whisper to " + TP->query_real_name() + " " +
                "The Treasure is sealed within it.");
        return "nod wisely";
    }
    else
    {
        return "shrug";
    }
}

public string
ask_goblet()
{
    object goblet = present(DQ_GOBLET, TP);
    
    if (goblet)
    {
        return "point pool";
    }
    else
    {
        return "shrug";
    }
}

public string
ask_quest()
{
    if (is_caller() && TP == caller)
    {
        start_guardian_seq();
        return "nod solemny";
    }
    else
    {
        return "shrug";
    }
}

public void
revenge(object attacker)
{
    attack_alarm = 0;
    
    if (attacker && ENV(attacker) == ETO)
    {
        command("say You should not have done that.");
        command("emote makes a sign in front of him.");
        attacker->set_mana(1);
        attacker->set_fatigue(1);
        attacker->catch_msg("You feel very dizzy.\n");
        tell_room(ETO, QCTNAME(attacker) + " looks as if " +
                  attacker->query_pronoun() + " is about to die.\n",
                  ({attacker, TO}));
        if (attacker == caller)
        {
            attacker->set_hp(0);
            attacker->do_die(TO);
        }
        else
        {
            attacker->set_hp(10);
        }
    }
    tell_room(ETO, QCTNAME(TO) + " simply ceases to exist.\n");
    remove_object();    
}

public void
attacked_by(object attacker)
{
    if (attack_alarm)
        return;
        
    attack_alarm = set_alarm(2.0, 0.0, &revenge(attacker));
}

/* We don't want the quest guardian to die */
public void
do_die(object killer)
{
    return;
}

public void
drop_obj(object ob)
{
    command("drop " + ob->query_name());
}

public void
touch_with_staff()
{
    if (!is_caller())
    {
        command("say Hmm...");
        return;
    }
    command("say Ah! That's very kind of you.");
    command("say Oh, I almost forgot. You will need this.\n");
    caller->catch_msg(QCTNAME(TO) + " places his staff on your shoulder.\n");
    tell_room(ETO, QCTNAME(TO) + " places his staff on " + QTNAME(caller) +
              "'s shoulder.\n", ({caller, TO}));
    caller->add_prop(DQ_DUBBING, 1);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!from || !living(from))
        return;
    
    if (!ob->id(DQ_LAST_LETTER) || from != caller)
    {
        set_alarm(3.0, 0.0, &drop_obj(ob));
        return;
    }
    set_alarm(3.0, 0.0, touch_with_staff);
}
