/*
 * /d/Gondor/guilds/rangers/obj/r_hat.c
 * A travellers hat, for sale in the Ranger guild
 * By Gilgalad, June 1995.
 * With help from Rohim
 */
inherit "/std/armour.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
 
#include "/d/Gondor/defs.h"

int AlarmId, Hatstat;
 
void do_wind();

void
create_armour()
{
    set_name("hat");
    set_adj(({"wide brim", "green", "forest"}));
    set_short("wide brim, forest green hat");
    set_long("The hat has a wide brim. And has a forest green shade " +
        "to it. It's a little too big. You might want to yank on your " +
        "hat once and a while to make sure you don't loose it.\n");

    set_ac(3);
    set_at(A_HEAD);
    set_af(TO);

    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 25 + random(10));
    add_prop(OBJ_I_VALUE,  25 + random(2));
    Hatstat = 0;
}
 
int
do_yank(string str)
{
    string shrt = short();

    if(!this_object()->query_worn())
    {
        write("You need to be wearing the hat to do that.\n");
        return 1;
    }
 
    if(str != "hat")
    {
        notify_fail("Yank what?\n");
        return 0;
    }
 
    write("You yank your " + shrt + " over your eyes.\n");
    say(QCTNAME(TP) + " pulls " + POSSESSIVE(TP) + " " + shrt + " over " +
        POSSESSIVE(TP) + " eyes.\n");
    remove_alarm(AlarmId); 
    AlarmId = set_alarm(300.0, 10.0, &do_wind());
    return 1;
}
 
public int
wear(object arm) 
{
    int wear;
    string shrt = short();
 
    wear = random(2);
    Hatstat = 0;
 
    if(wear == 0)
    {
        write("You wear the " + shrt + " on your head.\n");
        say(QCTNAME(TP) + " wears a " + shrt + " on " +
            POSSESSIVE(TP) + " head.\n");

        /* This is so when a person puts on the hat, it can blow off. */
        AlarmId = set_alarm(500.0,20.0, &do_wind());
        return 1; 
    }

    if(wear == 1)
    {
        write("You wear the " + shrt + " on your head.\nYour " + shrt +
            " slides in front of your eyes.\n");
        say(QCTNAME(TP) + " wears a " + shrt + " on " + POSSESSIVE(TP) +
            " head.\n" + QCTPNAME(TP) + shrt + " slides in front of " +
            POSSESSIVE(TP) + " eyes.\n");

        /* This takes longer for the hat to blow off. */
        AlarmId = set_alarm(1000.0, 40.0, &do_wind());
        return 1;
    }
}
 
public int
remove(object arm) 
{
    string shrt = short();

    if(Hatstat == 1)
    {
        write("You try to grab the hat as it blows out of your grasp!\n");
        say(QCTNAME(TP) + " tries to catch " + POSSESSIVE(TP) +
            " hat but fails!\n"); 
        remove_alarm(AlarmId); 
        Hatstat = 0;
        return 1;
    }

    if(Hatstat == 2)
    {
        write("You are just barely able to catch your hat!\n");
        say(QCTNAME(TP) + " just barely caught " + POSSESSIVE(TP) + " hat!\n");
        remove_alarm(AlarmId); 
        Hatstat = 0;
        return 1;
    }

    write("You remove the " + shrt + " from your head.\n");
    say(QCTNAME(TP) + " removes the " + shrt + " from his head.\n");
    remove_alarm(AlarmId); 
    return 1; 
}
 
void 
do_wind()
{
    int ran = random(3);
    string shrt = short();
 
    if(!ran)
    {
        Hatstat = 1;
        write("All of a sudden a huge gust of wind comes along and " +
            "whips loose your hat!\n");
        say("All of a sudden a huge gust of wind comes along and whips " +
            "loose " + QCTPNAME(TP) + " hat!\n");
        TO->move(ENV(TP));
        return;
    }

    if(ran == 1)
    { 
        Hatstat = 2;
        write("All of a sudden a gust of wind comes along and whips loose " +
            "your hat!\n");
        say("All of a sudden a gust of wind comes along and whips loose " +
            QCTPNAME(TP) + " hat!\n");
        command_remove();
        return;
    }

    if(ran == 2)
    { 
        Hatstat = 3;
        write("A small gust of wind comes along and gently rocks the " +
            shrt + ". You hold on to it so that it does not blow away.\n");
        say("A small gust of wind comes along and gently rocks " +
            QTPNAME(TP) + " " + shrt + ". " + QCTNAME(TP) + " holds onto " +
            POSSESSIVE(TP) + " " + shrt + " so that it does not blow away.\n");
        Hatstat = 0;
        remove_alarm(AlarmId); 
        AlarmId = set_alarm(300.0,10.0, &do_wind());
        return;
    }
}

void
init()
{
    ::init();
    add_action(do_yank, "yank");
}
 
