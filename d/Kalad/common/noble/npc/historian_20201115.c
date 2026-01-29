/*
    historian.c
    
    Code by Sarr,
    Recoded by Fysix, Feb 1998
 */
inherit "/d/Kalad/std/monster";

#include "default.h"

/* quest-log name */
#define QUEST "noble_spherequest"

string check_int();
string check_sphere();

void
create_kalad_monster()
{
    set_name("chatale");
    set_adj("old");
    add_adj("silver-haired");
    add_name("historian");
    set_race_name("human");
    set_short("old silver-haired historian");
    set_gender(1);
    set_long("This woman has piercing blue eyes that contrast greatly "+
        "with her old, silver hair. A vast amount of knowledge must reside "+
        "in her head, as she appears to be very old and wise. She regards "+
        "you carefully.\n");
    set_stats(({50,50,50,40,50,40}));
    set_skill(SS_DEFENCE,30);
    set_alignment(500);
    set_knight_prestige(-200);

    set_act_time(3);
    add_act("say Greetings, Travellers.");
    add_act("say Welcome to the historical museum of Kabal.");
    add_act("say Intresting blue sphere, isn't it?");
    add_act("emote looks puzzled.");
    add_act("say I wonder what happened to that medallion.");

    add_speak("I need help locating a medallion.\n");

    set_default_answer("I don't know anything about that.\n");
    add_ask(({"sphere","blue sphere"}),VBFC_ME("check_sphere"));
    add_ask("interested",VBFC_ME("check_int"));
    add_ask(({"medallion","help"}),"The "+short()+" says: "+
        "A golden medallion that belonged to a very powerful and rich "+
        "noble of Kabal, in fact, he was one of the very first nobles, "+
        "has been stolen. For what reason, I know not. If you find it, "+
        "please bring it back to me.\n");

    set_cact_time(3);
    add_cact("shout Help! Guards! Help!");

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    
    add_equipment(({
        NOBLE + "arm/toga",
        }));
}

string
check_sphere()
{
    if(ENV(TO))
    {
        if (present("_case6_", ENV(TO)) )
            return "Yes, it is a very intresting sphere, but lately, "+
            "not many people have been coming to see it. I guess if "+
            "you've seen it once, thats all. It is a real mystery, and "+
            "people around here don't like that. You wouldn't be 'interested' "+
            "in having it, would you?\n";
        return "Ah, I gave that sphere away to someone.\n";
    }
}

string
check_int()
{
    if (ENV(TO))
    {
        if (!present("_case6_",ENV(TO)))
            return "It is not here, I'm sorry.\n";
        if (TP->test_bit("Kalad",1,8))
        {
            set_alarm(3.0,0.0,"give_sphere",TP);
            return "Well, you have helped me with my medallion problem, "+
            "so you should have it...you deserve it.\n";
        }
        return "Hmm...maybe if you helped me, I would consider it.\n";
    }
}

void
give_sphere(object ob)
{
    object globe,gcase;

    seteuid(getuid());
    globe = clone_object("/d/Emerald/kroad/graveyard/obj/sphere1.c");
    tell_room(ENV(TO),QCTNAME(TO)+" opens the glass case.\n");
    tell_room(ENV(TO),QCTNAME(TO)+" takes out the "+globe->short()+".\n");
    ob->catch_msg(QCTNAME(TO)+" gives you the "+globe->short()+".\n");
    tell_room(ENV(TO),QCTNAME(TO)+" gives "+QTNAME(ob)+" the "+
    globe->short()+".\n",ob);
    gcase = present("_case6_",ENV(TO));
    gcase->remove_object();
    gcase = clone_object(NOBLE + "obj/emptycase");
    gcase->move(ENV(TO));
    globe->move(ob);
    command("smile");
}

void
enter_inv(object ob, object from)
{
    if(interactive(from))
    {
        if(MASTER_OB(ob) == NOBLE + "obj/medallion")
        {
            set_alarm(2.0,0.0,"reward_quest",from);
            set_alarm(2.0,0.0,"remove_medallion",ob);
        }
    }
    ::enter_inv(ob,from);
}

void
remove_medallion(object ob)
{
    ob->remove_object();
}

void
reward_quest(object ob)
{
    if(ob->test_bit("Kalad",1,8))
    {
        command("say Thank you once again.\n");
    }
    else
    {
        command("say Thank you very much, Sir!");
        command("say You have saved a very important artifact.");
        command("emote stores away the medallion in vault.");
        ob->add_exp(500);
        tell_object(ob,"You feel a little more experienced.\n");
        ob->set_bit(1,8);
        log_file(QUEST, extract(ctime(time()),4,15) + " "+
           capitalize(TP->query_real_name()) + " rewarded with 500 xp,"+
           "<"+TP->query_average_stat()+"> average stats.\n");
    }
}

