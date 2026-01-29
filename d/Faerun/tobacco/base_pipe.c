/*   Thanks to Vladimir for his help with all of the Hobbit project
 *   This file is based on Varl's traveller insignia, which has
 *   passed through many changes, mostly Vladimir's.
 *   Used for the Adventuresome Hobbits guild
 *   Dunstable, Oct 1994
 * 
 *  Made the pipe actually smokable!
 *  Igneous, August 1996 
 *
 *  General Update and Improvements 
 *  Igneous, Feb 1998
 * 
 *  Borrowed for Faerun's smoke shop 
 *  Finwe, November 2015
 *
 *  Updated by Shanoga, 2020-09-29:
 *   - Adjusted Puff_time alarm so emotes are a bit more randomized
 *   - Now saves leftover tobacco keeping remaining time and reducing ~20s
 *   - Added vbfc call so players can see current and leftover duration
 *   - Added <clean> emote to clear out old tobacco
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
//#include "/d/Shire/hobbit/hobbit.h"

// Global Vars
int  Puff_time, Smoke_time, Smoking, Packed, Packed_time;
string Flavour, tob_type, Packed_tobacco;

void create_pipe()
{
}

void
create_object()
{
    set_name("pipe");
    add_adj(({"large","brown"}));
    add_name("_smoking_pipe");
    add_name("pipe");
    set_short("large plain basic pipe");
    set_long("This is a large plain basic pipe. @@Packed_desc@@" +
        "Some instructions are etched on the bottom of the pipe.\n");

    set_keep(1);

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,   5);
    add_prop(OBJ_I_VALUE,   10);
    Packed = 0;
    Smoking = 0;
    create_pipe();
    add_cmd_item("instructions", ({"read", "exa", "examine"}), "@@instructions@@");
}

string
Packed_desc()
{
    string temp_time;
    if (!Packed)
        return "";
    if (Smoking) {
        Packed_time = ftoi(get_alarm(Smoke_time)[2]) + random(5) - random(5);
    }

    switch (Packed_time) {
        case 0..100:
            temp_time = " a little ";
            break;
        case 101..200:
            temp_time = " some ";
            break;
        case 201..300:
            temp_time = " a lot of ";
            break;
        default:
            temp_time = " an abundance of ";
            break;
    }
    return "You still have" + temp_time + tob_type + " left.\n";
}

void
do_puff(object player)
{
    if (Smoking) {
        player->catch_tell("You take a puff from your " + TO->query_short() +
            " and savor the intoxicating " + Flavour + " smoke.\n");
        say(QCTNAME(player)+" takes a puff from " + HIS_HER(player) +
            " pipe.\n", ({player}));
    }
}

void
puff_delay(object player)
{
    set_alarm(itof(random(70))/10.0, 0.0, &do_puff(player));
}

void
timeout(object player)
{
    remove_alarm(Puff_time);
    remove_alarm(Smoke_time);
    Puff_time = 0;
    Smoke_time = 0;
    Smoking = 0;
    player->catch_tell("Your pipe ran out of tobacco!!\n");
    say(QCTNAME(player)+"'s pipe ran out of tobacco and " +
      HE_SHE(player) + " ceased to smoke.\n", ({player}));
    return;
}

int
hsmoke(string str)
{
    int duration;
    object tobacco;

    if (Smoking)
    {
        notify_fail("But you haven't finished your last batch of " + 
            tob_type + ".\n");
        return 0;
    }

    if (!str)
    	str = "tobacco";

    tobacco = present(str, TP);
    //       Wizards always get to smoke!!!
    if (!tobacco && !tobacco->query_is_tobacco())
    {
        notify_fail("You have no tobacco to smoke!\n");
        return 0;
    }
    if (function_exists("create_herb", tobacco))
    {
        if (!tobacco->query_dried())
        {
            NF("Your " + tobacco->short()+" needs to be dried before you can "+
              "smoke it!\n");
            return 0;
        }
    }
    if (Packed)
    {
        duration = Packed_time;
        tob_type = Packed_tobacco->query_short();
        Flavour = Packed_tobacco->query_flavour();
// let's smoke the pipe
    Puff_time = set_alarm(itof(random(40)+random(40))/10.0, 15.0, &puff_delay(TP));
    Smoke_time = set_alarm(itof(duration), 0.0, &timeout(TP));
    Smoking = 1;
    write("You realize your " + TO->query_short() + " is already packed " +
        "with some " + tob_type + " and re-light it. As you continue to " +
        "inhale the wonderful tobacco smoke, you smile happily, thoroughly " +
        "enjoying it.\n");
    say(QCTNAME(TP) + " lights " + HIS_HER(TP) + " " + TO->query_short() +
        " and then proceeds to smoke it. " +
        CAP(HE_SHE(TP)) + " smiles happily as " + HE_SHE(TP) + 
        " exhales the intoxicating " + tob_type + " smoke.\n");
    add_prop(OBJ_M_NO_GIVE, "You need to extinguish the pipe before you " +
        "can drop it or give it away.\n");

    } else if (tobacco && tobacco->query_is_tobacco())
    {
        duration = tobacco->query_prop(OBJ_I_VALUE) * 10;
        if (!duration)
            duration = tobacco->query_herb_value();
        tob_type = tobacco->query_short();
        Flavour = tobacco->query_flavour();
        Packed_tobacco = MASTER_OB(tobacco);
        Packed = 1;
        tobacco->remove_object();
// let's smoke the pipe
    Puff_time = set_alarm(itof(random(40)+random(40))/10.0, 15.0, &puff_delay(TP));
    Smoke_time = set_alarm(itof(duration), 0.0, &timeout(TP));
    Smoking = 1;
    write("You quickly fill your " + TO->query_short() + " with some " + 
        tob_type + " and immediately " +
      "light it. As you start to inhale the wonderful tobacco " +
      "smoke, you smile happily, thoroughly enjoying it.\n");
    say(QCTNAME(TP) + " stuffs some " + tob_type + " into " + 
        HIS_HER(TP) + " pipe and then proceeds to light it. " +
        CAP(HE_SHE(TP)) + " smiles happily as " + HE_SHE(TP) + 
        " exhales the intoxicating " + tob_type + " smoke.\n");
    add_prop(OBJ_M_NO_GIVE, "You need to extinguish the pipe before you " +
        "can drop it or give it away.\n");
    }
    else
    {
        write("You need to specify which tobacco to smoke, or you don't " +
            "have any.\n");
    }
    return 1;
}

int
extinguish(string str)
{
    int new_value;
    
    if (!str || str != "pipe")
    {
        notify_fail("Extinguish what, your pipe?\n");
        return 0;
    }
    if (!Smoking)
    {
        notify_fail("The pipe is already out.\n");
        return 0;
    }

    Packed_time = 0;
    new_value = ftoi(get_alarm(Smoke_time)[2]) / 10;
    if (new_value > 5)
        Packed_time = (new_value - 2) * 10 + random(5) - random(5);
    remove_alarm(Puff_time);
    remove_alarm(Smoke_time);
    Puff_time = 0;
    Smoke_time = 0;
    Smoking = 0;
    if (Packed_time) {
        write("You decide to stop smoking your pipe and snuff it out, happy " +
            "to see you salvaged some " + tob_type + " for later.\n");
        say(QCTNAME(TP) + " stops smoking " + HIS_HER(TP) + " pipe by "+
            "snuffing it out.\n");
    } else
    {
        write("You decide to stop smoking your pipe and snuff it out.\n");
        say(QCTNAME(TP) + " stops smoking " + HIS_HER(TP) + " pipe by "+
            "snuffing it out.\n");
    }
    add_prop(OBJ_M_NO_GIVE, 0);
    return 1;
}

int
clean(string str)
{
    if (!str || str != "pipe")
    {
        notify_fail("Clean what, your pipe?\n");
        return 0;
    }
    if (Smoking) {
        notify_fail("You need to extinguish the pipe before you " +
        "can clean it.\n");
        return 0;
    }
    if (!Packed) {
        notify_fail("Clean your pipe? But it's not even dirty!\n");
        return 0;
    }
    Packed = 0;
    Puff_time = 0;
    Smoke_time = 0;
    Packed_tobacco = 0;
    Flavour = "";
    write("You clean your pipe of its old " + tob_type + " so it is " +
        "ready to smoke something new.\n");
    say(QCTNAME(TP) + " cleans " + HIS_HER(TP) + " " + 
        TO->query_short() + ".\n");
    return 1;
}

int
query_pipe_is_smoking()
{
    return Smoking;
}

string
query_pipe_smoke_flavour()
{
    return Flavour;
}

void
init()
{
    ::init();
    add_action(hsmoke,     "smoke");
    add_action(extinguish, "extinguish");
    add_action(extinguish, "ext");
    add_action(clean,      "clean");
}


public string
query_auto_load()
{
    return MASTER + ":";
}
 
public string
query_recover()
{
    return 0;
}

string
instructions()
{
    return "\nOn the bottom of the pipe you see the following " +
        "instruction:\n" +
        "     - To smoke some tobacco, you will need " +
        "to <smoke tobacco>.\n" + 
        "     - To stop smoking, do <extinguish pipe> or <ext pipe>.\n" +
        "     - You can <clean> your pipe if it is filled with " +
        "old tobacco.\n";
}