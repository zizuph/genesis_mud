/* Ashlar, 8 Jun 97 - a barkeeper */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define Q_GROUP 1
#define Q_BIT   0

object parrot;

void arm_me();
int need_ladle = 0;

void
create_krynn_monster()
{
    set_name("barkeep");
    add_name("barkeeper");
    add_name("_bs_barkeep_");
    set_race_name("barkeeper");
    set_adj("short");
    add_adj("swarthy");
    set_short("short swarthy barkeeper");
    set_long("This man of uncertain heritage seems to be the owner " +
        "of this inn, but it seems his previous occupation involved sailing " +
        "and probably some piracy.\n" +
        "He has an eyepatch covering his left eye.\n");
    set_stats(({80,65,75,50,55,70}));
    set_act_time(12);
    add_act("emote cleans the bar with a rag.");
    add_act("emote sits in the corner and studies the room.");
    add_act("say Business isn't what it used to be.");
    set_cact_time(2);
    add_cact("shout Guards, guards!");
    add_cact("say I'll get you for this!");
    add_cact("back");
    add_prop(OBJ_M_NO_ATTACK,"@@is_addicted");

    add_ask(({"quest", "task", "help"}), VBFC_ME("answer_help"));
}

void
set_need_ladle()
{
    need_ladle = !need_ladle;
}

int
query_need_ladle()
{
    return need_ladle;
}

varargs string
answer_help(object asker, string str)
{
    if (!asker->query_prop(NERAKA_MI_DRAGONBREW))
        asker->add_prop(NERAKA_MI_DRAGONBREW, ([ ]));

    if (environment()->query_out_of_dragonbrew())
    {
        if (member_array("inn_fetch_root",
            m_indices(this_player()->query_prop(NERAKA_MI_DRAGONBREW))) >= 0)
        {
            command("say to " + OB_NAME(this_player()) + " I've told you " +
                "already what I need.");
            return "";
        }
        
        command("say to " + OB_NAME(this_player()) + " Unfortunately " +
            "I've run out of dragonbrew.");
        command("say I could make a substitute from what I have but " +
            "it wouldn't be the same.");
        command("say I lack one key ingredient - a woody root.");
        command("say Preferably fresh but pickled will do as well.");
        command("say I sent for a shipment from Sanction by caravan " +
            "but it's yet to show up.");
        command("grumble angr");
        command("say Two should be sufficiant for a big enough batch.");
        
        this_player()->add_prop(NERAKA_MI_DRAGONBREW,
            this_player()->query_prop(NERAKA_MI_DRAGONBREW) +
            ([ "inn_fetch_root" : time() ]));
    }
    else if (query_need_ladle() && member_array("inn_fetch_root",
        m_indices(this_player()->query_prop(NERAKA_MI_DRAGONBREW))) >= 0)
    {
        if (member_array("inn_fetch_ladle",
            m_indices(this_player()->query_prop(NERAKA_MI_DRAGONBREW))) >= 0)
        {
            command("say to " + OB_NAME(this_player()) + " I've told you " +
                "already what I need.");
            return "";
        }
        command("say You wouldn't believe this.");
        command("say Here I was stirring up another batch of my " +
            "famous dragonbrew when my ladle broke.");
        command("say I need a replacement or this batch will have " +
            "gone spoiled.");
        command("say I'd fetch it myself but where do you find one " +
            "in an army camp?");

        this_player()->add_prop(NERAKA_MI_DRAGONBREW,
            this_player()->query_prop(NERAKA_MI_DRAGONBREW) +
            ([ "inn_fetch_ladle" : time() ]));
    }
    else
    {
        command("say I don't require any help at the moment, thank you.");
    }

    return "";
}

void
give_back(object obj, object from)
{
    command("say That won't help me.");
    command("drop " + OB_NAME(obj));
}

void
got_it(object obj, object from)
{
    int exp, t;
    mapping m;

    if (obj->id("dethek brew"))
    {
        command("smell " + OB_NAME(obj));
        command("brighten");
        command("say This might just work!");
        command("say I'll run into the kitchen and prepare a batch.");
        command("say Please come back later for your dragonbrew.");

        from->add_prop(NERAKA_MI_DRAGONBREW,
            from->query_prop(NERAKA_MI_DRAGONBREW) +
            ([ "inn_got_root" : time() ]));

        set_alarm(0.0, 0.0, &remove_object());
    }

    if (obj->id("spoon") && member_array("inn_got_root",
        m_indices(from->query_prop(NERAKA_MI_DRAGONBREW))) >= 0)
    {
        command("emote feels the " + obj->short() + ".");
        command("say Yes this will do just perfectly.");
        command("say I will be with you momentarily.");

        if (query_need_ladle())
            set_need_ladle();

        if (from->test_bit("ansalon", Q_GROUP, Q_BIT))
        {
            from->catch_tell("No reward for you this time though.\n");
            return;
        }

        exp = 2500;
        m = from->query_prop(NERAKA_MI_DRAGONBREW);
        if (member_array("cave_slayed_knight", m_indices(m)) >= 0)
            exp += 7500;

        if (m["inn_got_root"] - m["inn_fetch_root"] > 1800)
            exp -= 500;
        if (time() - m["inn_fetch_ladle"] > 600)
            exp -= 500;
        if (time() - m["inn_fetch_root"] < 180 + (random(3) * 60))
            exp -= 2000;
        
        if (exp < 0)
            exp = 0;

        if (exp > from->query_exp())
            exp = from->query_exp();

        from->add_exp(exp, 0);
        from->set_bit(Q_GROUP, Q_BIT);
        
        A_QUEST_LOG("quest", "Dragonbrew", from, exp);
    }
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (living(from))
    {
        if (!mappingp(from->query_prop(NERAKA_MI_DRAGONBREW)))
            from->add_prop(NERAKA_MI_DRAGONBREW, ([ ]));

        if (environment()->query_out_of_dragonbrew())
        {
            if (obj->id("dethek brew") && member_array("inn_fetch_root",
                m_indices(from->query_prop(NERAKA_MI_DRAGONBREW))) >= 0)
                set_alarm(1.0, 0.0, &got_it(obj, from));
            else if (!obj->query_no_show())
                set_alarm(1.0, 0.0, &give_back(obj, from));
        }
        else if (query_need_ladle())
        {
            if (obj->id("spoon") && member_array("inn_got_root",
                m_indices(from->query_prop(NERAKA_MI_DRAGONBREW))) >= 0)
                set_alarm(1.0, 0.0, &got_it(obj, from));
            else
                set_alarm(1.0, 0.0, &give_back(obj, from));
        }            
        else if (obj->id("coin"))
            command("grin greed");
        else
            set_alarm(1.0, 0.0, &give_back(obj, from));
    }
}

void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));

    arm = clone_object(NARM+"breeches");
    arm->move(TO);
    arm = clone_object(NARM+"vest");
    arm->move(TO);
    /*
    wep = clone_object(NWEP+"knobkerrie");
    wep->move(TO);
    */
    parrot = clone_object(NNPC + "parrot");
    parrot->move(TO);
    command("wear all");
    command("wield all");
    
}

void
catch_msg(mixed str, object from_player)
{
    if (objectp(parrot))
    {
        parrot->catch_msg(str,from_player);
    }
    ::catch_msg(str,from_player);
}

public int
second_life(object killer)
{
    if (objectp(parrot))
    {
        parrot->move_living("M",E(TO));
        tell_room(E(TO),"A " + parrot->short() + " flies up from the barkeeper's " +
            "shoulder, bites " + QTNAME(killer) + " and then lands on the " +
            "ground nearby.\n", killer);
        killer->catch_msg("A " + parrot->short() + " flies up from your victim's " +
            "shoulder and bites you in the nose!\n");
    }
    return 0;
}

mixed
is_addicted()
{
    if (present("_bd_add_",TP))
    {
        return "But who would serve you the Black Dragonbrews if you killed " +
            "the barkeeper?\n";
    }
    else
        return 0;
}
