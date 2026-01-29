/*
 * /d/Ansalon/guild/society/room/train.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Kender training room
 * Gwyneth, 1999
 *
 * Updated skills based on revised skill proposal - Arman, June 2019
 */
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/clock/clock.h"

inherit KENDERMORE_IN; 

object gTrainer;

string window_climb();

/*
 * Function name : set_up_skills
 * Description : Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_TAUNT_SPECIAL,  "compose taunts",
                                    "taunt",             50, 100 );
    sk_add_train(SS_HIDE,           "hide",
                                    "hide",               0, 100 );
    sk_add_train(SS_SNEAK,          "sneak around",
                                    "sneak",              0, 100 );
    sk_add_train(SS_AWARENESS,      "be aware of surroundings",
                                    "awareness",          0, 100 );
    sk_add_train(SS_OPEN_LOCK,      "open locks",
                                    "open lock",          0,  90 );
    sk_add_train(SS_PICK_POCKET,    "borrow things",
                                    "borrow",             0,  90 );
    sk_add_train(SS_WEP_POLEARM,    "fight with a polearm",
                                    "polearm",            0,  85 );
    sk_add_train(SS_WEP_KNIFE,      "fight with a knife",
                                    "polearm",            0,  75 );
    sk_add_train(SS_DEFENCE,        "defend in combat",
                                    "defence",            0,  75 );
    sk_add_train(SS_PARRY,          "parry attacks",
                                    "parry",              0,  55 );
    sk_add_train(SS_ACROBAT,        "acrobatics",
                                    "acrobatics",         0,  90 );
    sk_add_train(SS_CLIMB,          "climb things",
                                    "climb",              0,  75 );
    sk_add_train(SS_HOOPAK_ALTER,   "alter weapons into hoopaks",
                                    "hoopak alteration", 50,  50 );
    sk_add_train(SS_FR_TRAP,        "disarm traps",
                                    "disarm traps",       0,  85 );
}

void
reset_kendermore_room()
{
    if (!gTrainer)
    {
        gTrainer = clone_object(KGNPC + "trainer");
        gTrainer->move(TO);
    }
}

public void
create_kendermore_room()
{
    set_short("Large airy training room");
    set_long("The @@light_room@@ shines in from the open windows here, " + 
        "lighting the spacious room well. Various practicing props are " + 
        "spread around the room in a bit of disarray. Several kender are " + 
        "scattered around the room, improving on their skills.\n");
    add_item(({"open windows", "windows", "open window", "window"}),
        "They are flung wide open, and a soft breeze cools the sweaty " + 
        "trainers.\n");
    add_item(({"props", "practicing props"}), "You see, among other " + 
        "things, a rope attached to the wall, several knives and some " + 
        "hoopaks.\n");
    add_item(({"several knives", "knives"}), "There are a variety of " + 
        "knives used for training. There are long and short ones, but " + 
        "all are well worn.\n");
    add_item(({"some hoopaks", "hoopaks"}), "Many hoopaks are propped " + 
        "up against one wall, their wood worn smooth by years of " + 
        "handling.\n");
    add_item("rope", "This is a very thick rope, tied to the wall and " + 
        "used to help train kender to climb.\n");
    add_item(({"wall", "walls"}), "The walls are painted pure white to " + 
        "make the room seem more spacious.\n");
    add_item("room", "It is a spacious chamber for practicing.\n");

    add_cmd_item(({"window", "out window", "through window"}),
        ({"squeeze", "climb", "enter"}), &window_climb());

    add_exit(KGROOM + "rack_room", "west", 0);
    add_exit(KGROOM + "board_room", "north",0);

    set_up_skills(); 

    reset_kendermore_room();
}

string
window_climb()
{
/*
    if(VMASTER->query_voting_member(TP))
    {
*/
        tell_room(VMASTER, QCTNAME(TP) + " comes sliding down the pole " +
            "and leaps off before spinning through the ground.\n");
        write("You glance around, and while nobody is looking climb " +
            "out the window where you find a shiny silver pole. Unable " +
            "to resist, you jump onto the pole and slide down it " +
            "through the ground.\n");
        TP->move_living("M", VMASTER, 1, 0);
        tell_room(TO, "You look away from " + QTNAME(TP) + " for a " +
            "moment, and when you turn back, " + HE(TP) + " is gone.\n");
        return "";
/*
    }
    else
    {
        return ("You lean out the window, but a nearby kender scolds " +
            "you, telling you that you aren't old enough to go " +
            "there.\n");
    }
*/
}

public void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate", "daydream");
    init_skill_raise();
}

string
light_room()
{
    if (GET_TIMEOFDAY == NIGHT)
        return "moon";
    else
        return "sun";
}

int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}

void
gs_hook_start_meditate()
{
    write("You stare into space, blocking off the noise and chatter of the " + 
        "kender nearby. You let your imagination unfold into wild " + 
        "adventures and exotic lands. In such a state, you feel you " + 
        "can exert enough " + 
        "control over your body to <set> which abilities you want to " + 
        "concentrate on. To return from your imagination, you can " + 
        "<rise>.\n"); 

    say(QCTNAME(TP) + " finds a relaxing position and closes " + HIS(TP) + 
        " eyes. A smile plays over " + HIS(TP) + " lips.\n");
}

int
gs_hook_rise()
{
    write("You gradually bring yourself back to the real world. You " + 
        "slowly open your eyes, leaving behind your fantasy world, and " + 
        "ready to make adventures of your own.\n");

    say(QCTNAME(TP) + " takes a deep breath and slowly opens " + HIS(TP) + 
        " eyes. " + capitalize(HE(TP)) + " stands up with a bounce, looking " + 
        "refreshed and ready to make some mischief.\n");
}

void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
        return sk_list(steps);

    tmp = explode(sk, " ");
    if (sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = sk;
        steps = 1;
    }

    if (!(present("trainer", TO)))
    {
        write("Without a trainer, your efforts to improve go awry.\n");
        return 1;
    }

    if (!TP->query_guild_name_occ(GUILD_NAME))
    {
        NF("Only members are allowed to train here!\n");
        return 0;
    }
    return ::sk_improve(sk);
}

void
remove_ex_members(object who)
{
    if (present(who, this_object()))
    {
        who->catch_tell("A very large looking kender enters the room and " +
            "escorts you out of the guild.\n");
        say("A very large looking kender enters the room and escorts " +
            QTNAME(who) + " out of the guild.\n", who);
        tell_room(KGROOM + "joinroom", QCTNAME(who) + " is escorted out " +
            "of the guild by a very large looking kender.\n");
        who->move_living("M", KROOM + "joinroom", 0, 0);
        return;
    }
    return;
}

