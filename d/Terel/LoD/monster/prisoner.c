/*
 * prisoner.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

object chain = 0;
int alarm_id = 0;

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({ });
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
   
    set_name("innocent");
    add_name("prisoner");
    set_long("An old prisoner. He has been since the last of the " +
             "Avenchirs captured him. The reason for his captivity " +
             "has been forgotten of everyone---including himself.\n");
    set_adj("old");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(100);

    set_stats(({30, 35, 20, 60, 55, 25}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      10 + random(11));
    set_skill(SS_UNARM_COMBAT, 10 + random(11));
    set_skill(SS_PARRY,        10 + random(11));
    set_skill(SS_WEP_SWORD,    10 + random(5));
    set_skill(SS_WEP_KNIFE,    10 + random(5));
    set_skill(SS_2H_COMBAT,    10);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS,    70);
    
    add_prop(LIVE_I_QUICKNESS, 0);
    add_prop(LIVE_I_SEE_DARK,  1);
    add_prop(LIVE_I_SEE_INVIS, 1);
    
    set_chat_time(18);
    add_chat("I can't remember why I'm here.");
    add_chat("I can't even remember my name.");
    add_chat("Who am I?");
    add_chat("What am I doing here?");
    add_chat("Those walls are my best and only friends.");
    
    set_act_time(19);
    add_act("scratch");
    add_act("emote scratches his armpit.");
    add_act("@@chain_check");
    add_act("emote mumbles some gibberish.\n");
}

public string
chain_check()
{
    if (!chain)
        return "emote looks as if he doesn't know what to do.";
    
    if (chain->query_tied_to() != TO)
        return "say I'm going to miss those chains...";
    
    if (random(11))
        command("say Could you remove these? Please...");
    else
    {
        command("say The only thing I remember at all is what the " +
                "guard told me when he chained me. He said that those " +
                "chains was being used to tame the three-headed one...");
    }
    return "point chain";
}

public int
tie_object(object ob, string what)
{
    if (chain || !id(what))
        return 0;
        
    if (!ob->id(DQ_HYDRA_CHAIN))
    {
        TP->catch_msg("The " + ob->short() + " doesn't seem to fit.\n");
        tell_room(ETO, QCTNAME(TP) + " tries, in vain, to chain " +
                       QTNAME(TO) + ".\n", TP);
        return 0;
    }

    chain = ob;
    return 1;
}

public void
hug(object who)
{
    alarm_id = 0;
    
    if (who && ENV(who) == ETO)
    {
        if (CAN_SEE(TO, who) && CAN_SEE_IN_ROOM(TO))
            command("hug " + who->query_real_name());
        else
            command("emote looks confused but happy.");
    }
        
    command("say What shall I do now? I'll think I stay here...");
}

public varargs int
untie_object(object ob, string what = "")
{
    object key;
    
    if (!chain || chain != ob)
        return 0;
        
    notify_fail("Unlock chain with what?\n");
    if (!strlen(what) || !(key = present(what, TP)))
        return 0;
        
    notify_fail("The " + key->short() + " does not fit the lock.\n");
    if (!key->id(DQ_CHAIN_KEY))
        return 0;
        
    if (!alarm_id)
        alarm_id = set_alarm(2.0, 0.0, &hug(TP));
    
    chain = 0;
    return 1;
}
