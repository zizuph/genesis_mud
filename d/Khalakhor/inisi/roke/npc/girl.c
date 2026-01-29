/*
 * girl.c
 *
 * Used in nyreese/cadu_s1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

int rescued;
int speakid, screamid;

int rescue(string s);
void one();
void two();
void three();
void four();
void five();
void scream();
void speak();

void
create_monster()
{
    rescued = 1;

    set_name("lisa");
    set_living_name("lisa");
    add_name("girl");
    set_race_name("girl");
    set_adj("pretty");
    set_short("pretty girl");

    set_gender(1);
    
    set_long("This is a small girl, about eleven years old.\n");
  
    default_config_npc(15);

    /* yes, she is not supposed to be able to swim, but she should stay
       floating for a while so she must have a swim skill */

    set_skill(SS_SWIM, 25);
    set_alignment(300);
    seteuid(getuid());

    set_alarm(6.0, 0.0, one);
}

int query_knight_prestige() {return -2;}

void
init_living()
{
    ::init_living();

    add_action(rescue, "rescue");
}

int
rescue(string s)
{
    NF("Rescue who?\n");
    if (s != "girl" && s != "human" && s != "lisa")
        return 0;

    NF("Nah, she doesn't need to be rescued now.\n");
    if (rescued)
        return 0;

    rescued = 1;

    say(QCTNAME(TP) + " rescues Lisa.\n");
    write("You rescue Lisa and carry her up on the cliff.\n");

    TP->move_living("up", NYREESEDIR + "cadu_s6");
    TO->move(NYREESEDIR + "cadu_s6");

    command("say Thanks!");

    if (!QDONE(ROKEGROUP, DROWNGIRL))
    {
        command("say I will reward you for your help!");
        TP->catch_msg("You feel more experienced.\n");
        TP->add_exp_quest(DROWNGIRLXP);
        QSET(ROKEGROUP, DROWNGIRL);
        QLOG("Drowning girl quest", DROWNGIRLXP);
    }
    else
    {
        command("say Hey! You have rescued me before!");
        command("say You must be a very kind person!");
    }

    tell_room(ENV(TO),
              "The pretty girl waves happily and leaves into the forest.\n");

    remove_object();

    return 1;
}

void
one()
{
    command("west");
    set_alarm(8.0, 0.0, two);
}

void
two()
{
    command("smile");
    command("west");
    set_alarm(4.0, 0.0, three);
}

void
three()
{
    command("west");
    command("introduce me");
    set_alarm(14.0, 0.0, four);
}

void
four()
{
    command("west");
    set_alarm(10.0, 0.0, five);
}

void
five()
{
    tell_room(ENV(TO),
              "Suddenly the little girl slips on the rock and falls into the water!\n");
    TO->move(NYREESEDIR + "cadu_water2");
    tell_room(ENV(TO), "A young girl falls into the water.\n");

    screamid = set_alarm(1.0, 0.0, scream);
    speakid = set_alarm(itof(random(6) + 1), 0.0, speak);
    rescued = 0;
}

void
do_die(object who)
{
    remove_alarm(speakid);
    remove_alarm(screamid);

    tell_room(NYREESEDIR + "cadu_s6", 
              "You hear the sounds of a drowning person from below.\n");

    ::do_die(who);
}

void
speak()
{
    command("say Please rescue me!");
    speakid = set_alarm(itof(random(5) + 1), 0.0, speak);
}

void
scream()
{
    tell_room(ENV(TO), "The pretty girl screams for help!\n");
    tell_room(NYREESEDIR + "cadu_s6",
              "You hear someone screaming for help in the water.\n");
    tell_room(NYREESEDIR + "cadu_s4",
              "The wind carries a scream for help from the west.\n");

    screamid = set_alarm(itof(random(7) + 2), 0.0, scream);
}
