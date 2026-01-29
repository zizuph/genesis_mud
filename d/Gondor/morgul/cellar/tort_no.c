/* /d/Gondor/common/guild2/prison.c
 *
 * Prison where an elf is kept in Minas Morgul.
 *
 * Coded by Gwyneth and Stern
 * June 3, 2000
 */

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

#define NPC_I_TORTURE_TIME "_npc_i_torture_time"
#define PLAYER_I_RELEASED_LENTIL "_player_i_released_lentil"

/* Prototype */
void scream(object victim);

object elf, orc;
int gCounter = -1;
int gAlarm1, gAlarm2;

void
reset_room()
{
    /* Elf will only reset approximately every 6 hours, or
       12 room resets. */

    gCounter++;

    if(elf)
    {
        if (!orc)
        {
            orc = clone_object(MORGUL_DIR + "npc/tort_orc");
            orc->arm_me();
            orc->move(TO, 1);
        }

        return;
    }
    else if(gCounter % 12 != 0)
    {
        return;
    }
    else
    {
        elf = clone_object(MORGUL_DIR + "npc/elf_pris");
        elf->arm_me();
        elf->move_living("M", TO);
        if (!orc)
        {
            orc = clone_object(MORGUL_DIR + "npc/tort_orc");
            orc->arm_me();
            orc->move(TO, 1);
        }
    }
}

public string
free_elf()
{
    int alarm_num = TO->query_alarms();
    object orc;

    /* Elf is present. If he is not too hurt, release him,
       otherwise give message that he is too hurt to leave.
    */
    if(elf)
    {
        /* Only allow releasing of the prisoner provided for now. */
        if(elf->query_real_name() != "lentil")
        {
            return("Release whom?\n");
        }

        if((elf->query_hp()) < (elf->query_max_hp() / 6))
        {
            return("The prisoner is wounded too gravely to " +
                "escape. Perhaps if his wounds were healed, " +
                "he would have a chance.\n");
        }
        
        if(sizeof(alarm_num) > 1)
        {
            remove_alarm(gAlarm1);
            remove_alarm(gAlarm2);
        }
 
        write("You release the prisoner from his " +
            "bonds and help him to stand. He grasps your hand " +
            "in gratitude.\n");
        say(QCTNAME(TP) + " releases the prisoner from his " +
            "bonds and helps him to stand. " + QCTNAME(elf) +
            " grasps " + QTPNAME(TP) + " hand in gratitude.\n");
        elf->command("say Thank you my rescuer! If I escape, " +
            "meet me in Imladris and I shall thank you properly!");
        elf->command("emote slips out of the chamber, stumbling " +
            "slightly before reaching the door.");
        TP->add_prop(PLAYER_I_RELEASED_LENTIL, 1);
        if (orc = present("torture_orc", TO))
        {
            orc->command("shout Heeelp, heeeelp, they are rescuing " +
                "the prisoner!");
            orc->command("emote runs out with his hands in the air.");
            orc->remove_object();
        }
        elf->remove_object();
        return "";
    }
    else
    {
        return "Release whom?\n";
    }
}

int
check_leave(object who)
{
    int alarm_num = TO->query_alarms();
    mixed *alarms, *arg;

    if(sizeof(alarm_num) > 1)
    {
        alarms = get_alarm(gAlarm1);
        arg = alarms[4];
        if(arg[1] == who)
        {
            scream(arg[0]);
            set_alarm(0.9,0.0,&tell_room(TO, "A servant enters, " +
                "releases the prisoner from his torture, and " +
                "shuffles out again.\n"));

            /* Remove the alarm to torture and damage the victim
               since the torturer left. */
            remove_alarm(gAlarm1);
            remove_alarm(gAlarm2);
        }
    }
    return 0;
}

public void
leave_inv(object ob, object to)
{
    check_leave(ob);
    ::leave_inv(ob, to);
}

void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("torture chamber");
    set_extra_long("A most rare collection of tools for torture " +
        "was brought together here. Floor, walls, ceiling, everything seems " +
        "to be in some way involved in inflicting pain.");

    add_cmd_item(({"prisoner", "elf", "weary elf", "tortured elf",
        "weary tortured elf", "prisoners", "elves", "lentil",
        "weary elves", "weary tortured elves"}), ({"release", "free"}),
        "@@free_elf");
    add_item(({ "collection", "tool", "tools", "device", "devices"}), 
        "You can only guess with respect to the use of some of these " +
        "devices. Your eyes are drawn to the Iron Maiden, that rests " +
        "on the floor in a rather central position, next to an " +
        "intimidating large wooden rack.\n");
    add_item(({"rack", "wooden rack", "large rack", "large wooden rack"}), 
        "This is one of the most cruel torture devices known " +
        "to man. It consists of a wooden bed with wheels on two sides, " +
        "which can be turned in opposite directions to stretch the " +
        "joints and muscles of the poor soul tied to them, separating " +
        "joints and ripping muscles, crippling a victim for life.\n");
    add_item(({"wheel", "wheels", "roller", "rollers"}), 
        "Wheels and rollers are used with several devices for leverage. " +
        "Two large ones are positioned at opposite sides of the bed. " +
        "Turning them shortens the chains attached to them and lengthens " +
        " the victim on the rack.\n");
    add_item(({"table", "instrument", "instruments", "item", "items"}),
        "On the sturdy wooden table you see several " +
        "smaller instruments for torture. You recognize a head crusher, " +
        "thumb screws and needles in a heap of less recognizable but " +
        "obviously pain inflicting items.\n");
    add_item(({"knife"}),
        "A small but razor sharp knife lies on the table.\n");
    add_item(({"screw", "screws", "thumb screw", "thumb screws"}), "The " +
        "thumb screws are made of iron and very efficient to crush one's " +
        "thumbs quickly, or slowly.\n");
    add_item(({"crusher", "head crusher"}), "This implement consists of " +
        "an iron cap to be worn on the head, with a screw mechanism " +
        "added to slowly apply a most excruciating pressure to the skull " +
        "of the unfortunate wearer.\n");
    add_item(({"maiden", "iron maiden", "Maiden", "Iron Maiden"}), 
        "This device resembles a coffin, except that the inner surface " +
        "is covered with spikes.\n");
    add_item(({"needle", "needles"}), "Several sharp needles are " +
        "scattered on the table. They look perfect for inserting " +
        "beneath the fingernails.\n");
    add_item(({"ropes", "chains", "straps", "rope", "chain", "strap"}), 
        "Ropes, straps, and chains " +
        "hang down from the ceiling and the walls. Some with weights " +
        "attached, others with spiky attributes. Obviously these items " +
        "are meant to suspend or immobilize a victim in a most " +
        "uncomfortable manner.\n");
    add_item(({"hook", "hooks"}), "Hooks are set into the walls and " +
        "ceiling to accomodate chains, ropes, and straps.\n");
    add_item(({"weight", "weights"}), "Weights are attached to some " +
        "of the ropes and chains, most likely to increase the discomfort " +
        "of the  experience.\n");
    add_item(({"spike", "spikes"}), "Spikes seem to be popular here. " +
        "Many constructs in this room have some sharp elements attached.\n");
    add_item(({"torch", "torches"}), "Torches in wall-mounted stands line " +
        "the walls. A chilly draft causes shivery shadows in the room.\n");
    add_item(({"stand", "stands"}), "Stands are mounted along the walls " +
        "and hold burning torches that light the room.\n");
    add_floor("Old and fresh stains tell their own horrid history. Bolted " +
        "to the floor are several torture devices. You recognize a rack and " +
        "an iron maiden, while you never even heard of some of the other" +
        "things you see around you.\n");
    add_ceiling("From the ceiling ropes and chains hang down.");
    add_walls("Here and there you see chains bolted to the wall, " +
        "on various heights, for whatever purpose one could think of.");
    add_stones("Blood stains and smears of filth cover the blocks.");
    
    add_exit(CELLAR_DIR + "dung_1e1", "up");
    add_prop(ROOM_I_LIGHT, 1);
    reset_room();
}

void
setup_torture(object victim, object who, string device)
{
    switch(device)
    {
        case "chain":
        case "chains":
            who->catch_msg("From the collection hanging from hooks attached " +
                "to the the wall you pick a chain flail, made of " +
                "razor-sharp, flat oval links. You use it to caress " +
                QTPNAME(victim) + " back, increasing the pressure as " +
                "you go.\n");
            say(QCTNAME(who) + " selects a chain flail from a hook set in " +
                "the wall, and caresses " + QTPNAME(victim) + " back " +
                "with its razor-sharp, flat oval links.\n");
            break;
        case "crusher":
            who->catch_msg("You take the head crusher from the table " +
                "and attach it firmly to " + QTPNAME(victim) + 
                " head. You use all your force to screw it tight, " +
                "applying extreme pressure to your victims's skull.\n");
            say(QCTNAME(who) + " takes a head crusher from the table and " +
                "screws it tightly onto " +  QTPNAME(victim) +
                " head, applying extreme pressure to the victim's " +
                "skull.\n");
            break;
        case "maiden":
            who->catch_msg("You force " + QTNAME(victim) + " into the " +
                "Iron Maiden. The doors automatically start to close in " +
                "on their victim.\n");
            say(QCTNAME(who) + " forces " + QTNAME(victim) + 
                " into the Iron Maiden. The doors automatically start to " +
                "close in on its victim.\n");
            break;
        case "needle":
        case "needles":
            who->catch_msg("You take a needle from the table, carefully " +
                "choosing one that is not too thin, but has a sharp tip. " +
                "With a grin on your face, you take " + QTPNAME(victim) + 
                " hand, isolate the ring " +
                "finger in your firm grasp, and slowly insert the needle " +
                "under your victim's fingernail.\n");
            say(QCTNAME(who) + " carefully chooses a needle from the " +
                "variety on the table. With a grin on " + 
                who->query_possessive() +
                " face " + who->query_pronoun() + " takes " +
                 QTPNAME(victim) + 
                " hand in a firm grip, isolating the ring finger. " +
                QCTNAME(who) + " slowly inserts the needle under " +
                QTPNAME(victim) + " fingernail.\n");
            break;
        case "rack":
            who->catch_msg("You place " + QTNAME(victim) + 
                " on the large wooden rack and tie your victim across " +
                "the board by ankles and wrists. You turn the roller " +
                "with all your might, cursing the hard work. A scream " +
                "fills the air.\n");
            say(QCTNAME(who) + " places " + QTNAME(victim) + 
                " on the large wooden rack and ties " +
                victim->query_possessive() + " ankles and wrists across the " +
                "board. Cursing the hard work, " + QCTNAME(who) +
                " turns the wheel with all " + who->query_possessive() +
                " might. A scream fills the air.\n");
            break;
        case "rope":
        case "ropes": 
            who->catch_msg("You take the end of a thick rope " +
               "that hangs from the ceiling, and wind it tightly around " +
               QTPNAME(victim)  + " wrists, causing the blood to painfully " +
               "stagnate in " + victim->query_possessive() + 
               " hands. You pull the other end of the rope over a lever, " +
               "causing your condemned victim to rise above the ground, " +
               "hanging with his whole weight from " +
               victim->query_possessive() + " tightly restrained wrists. " +
               "You leave your victim dangling while you select a knife " +
               "from the table.\n");
            say(QCTNAME(who) + " takes the end of a thick rope " +
               "that hangs from the ceiling, and winds it tightly around " +
               QTPNAME(victim)  + " wrists, causing the blood to painfully " +
               "stagnate in " + victim->query_possessive() +  " hands. " + 
               QCTNAME(who) + " pulls the other end of the rope over a " +
               "lever, causing the condemned victim to rise above the " +
               "ground, hanging with his whole weight from " +
               victim->query_possessive() + " tightly restrained wrists. " +
               QCTNAME(victim) + " is left dangling, while " + QTNAME(who) +
               " takes a knife from the table.\n");
            break;
        case "screw":
            who->catch_msg("You take " + QTPNAME(victim)  + 
               " hands and islolate the thumbs. You brutally force them " +
               "into the thumb screw and quickly screw it tight. A final " +
               "turn causes a sickening snapping sound.\n");
            say(QCTNAME(who) + " takes " + QTPNAME(victim)  + 
               " hands and islolates the thumbs. " + 
               capitalize(who->query_pronoun()) + " brutally forces the " +
               "thumbs into the thumb screw and quickly screws it tight. " +
               "A final turn causes a sickening snapping sound.\n");
            break;
        case "spike":
        case "spikes":
            who->catch_msg("You tightly wrap " + QTPNAME(victim)  + " body " +
               "in a long chain covered with sharp spikes of various sizes, " +
               "immobilizing " + QTPNAME(victim)  +  " arms and legs.\n");
            say(QCTNAME(who) + " tightly wraps " + QTPNAME(victim)  + 
               " body in a long chain covered with sharp spikes of " +
               "various sizes, immobilizing " + QTPNAME(victim)  +  
               " arms and legs.\n");
            break;
    }
}

void
show_torture(object victim, object who, string device)
{
    switch(device)
    {
        case "chain":
        case "chains":
            who->catch_msg("You make a halfhearted attempt to sign " +
               "your name on your victims back before returning the chains " +
               "to its proper place.\n");
            tell_room(TO, QCTNAME(who) + " makes some intricate movements " +
               "on " + QTPNAME(victim) + " back  before returning the " +
               "chains to the wall.\n", who);
            break;
        case "crusher":
            who->catch_msg("You screw the device just a little tighter, " +
               "causing " +  QTNAME(victim) + " to whimper, " +
               "before releasing " + victim->query_objective() + 
               " from its grasp. You neatly place the crusher back on " +
               "the table where you found it.\n");
            tell_room(TO, QCTNAME(who) + " screws the device even more " +
               "tightly, causing " + QTNAME(victim) + " to whimper " +
               "before releasing " +victim->query_objective() + " from its " +
               "grasp. " + QCTNAME(who) + " puts the head crusher back on " +
               "the table.\n", who);
            break;
        case "maiden":
            who->catch_msg("You savor your victims muffled screams for " +
              "a few minutes before releasing the Maiden's doors, causing " +
              QTNAME(victim) + " to stumble out.\n");
            tell_room(TO, QCTNAME(who) + " chortles in appreciation " +
              "while listening to the muffled screams from inside the " +
              "Maiden. After long minutes doors swing open, causing " + 
              QTNAME(victim) + " to stumble out.\n", who);
            break;
        case "needle":
        case "needles":
            who->catch_msg("You wiggle the needle a little under " +  
               QTPNAME(victim) + " fingernail, causing " +
               victim->query_objective() + " to scream in terror. You " +
               "firmly keep " + victim->query_possessive() + " finger " +
               "locked in your grasp. You then slowly remove the needle " +
               "and wipe it clean on on your clothes, before putting it " +
               "back on the table.\n");
            tell_room(TO, QCTNAME(who) + " wiggles the needle a little " +
               "under " +  QTPNAME(victim) + " fingernail, causing " +
               QTNAME(victim) + " to scream in terror. " +
               QCTNAME(who) + " firmly keeps the finger locked in " + 
               who->query_possessive() + " grip. " +
               capitalize(who->query_pronoun()) + 
               " finally removes the needle in a slow motion " +
               "and wipes it clean on " + who->query_possessive() + 
               " clothes, before putting it back on the table.\n", who);
            break;
        case "rack":
            who->catch_msg("You wipe some sweat from your brow and " +
              "pause, inspecting your stretched work, before letting " +
              "go of the rollers and releasing the poor soul.\n");
            tell_room(TO, QCTNAME(who) + " wipes the sweat from " +
               who->query_possessive() + " brow, inspecting the trapped " +
               "soul with an almost scientific interest, before " +
               "releasing the stretched victim.\n", who);
            break;
        case "rope":
        case "ropes":
            who->catch_msg("You push " + QTNAME(victim) + " to a swing, " +
               "and then quickly release the rope, causing " +
               "the abused to be thrown to the ground. You cut the rope " +
               "at " + QTPNAME(victim) + " wrists not aiming your knife " +
               "too carefully. You put the knife back where you " +
               "found it, after wiping it clean.\n");
            tell_room(TO, QCTNAME(who) + " pushes " + QTNAME(victim) + 
               " to a swing, and then quickly release the rope, " +
               "causing the abused to be thrown to the ground. " +
               QCTNAME(who) + " cuts the rope at " + QTPNAME(victim) + 
               " wrists, spilling blood in the process. " +
               capitalize(who->query_pronoun()) + " wipes the knife clean " +
               "and returns it to the table.\n", who);
            break;
        case "screw":
            who->catch_msg("After a short pause you release the shattered " +
               "useless thumbs.\n");
            tell_room(TO, QCTNAME(who) + " releases the shattered thumbs " +
               "after a short pause, leaving them useless.\n", who);
            break;
        case "spike":
        case "spikes":
            who->catch_msg("You pull the chain carelessly at random " +
               "locations, savoring the moans of pain, before you " +
               "release your abused prisoner.\n");
            tell_room(TO, QCTNAME(who) + " pulls the chain carelessly " +
               "at random locations, listening with interest at the " +
               "resulting moans of pain, before releasing the abused " +
               "prisoner.\n", who);
            break;
    }
}

void
scream(object victim)
{
    int hit_p = victim->query_hp(), broken;

    if(hit_p < (victim->query_max_hp() / 6))
    {
        broken = 1;
    }

    if(broken)
    {
        switch(random(5))
        {
            case 0:
                victim->command("emote 's eyes fly open wide as they " +
                    "glaze over with pain. A bloodcurdling scream " +
                    "flies from his lips.");
                break;
            case 1:
                victim->command("emote emits a soul-piercing shriek " +
                    "of agony. His features crumple into a look of " +
                    "defeat.");
                break;
            case 2:
                victim->command("emote writhes in agony, trembling " +
                    "and shaking as his spirit is conquered.");
                break;
            case 3:
                victim->command("emote exhales in anguish and " +
                    "bitterness as his hope gives way to despair.");
                break;
            case 4:
                victim->command("emote tries to curl into a ball as " +
                    "his last shred of courage is stripped away with " +
                    "torture.");
                break;
        }
    }
    else
    {
        switch(random(5))
        {
            case 0:
                victim->command("emote bites his lip until blood " +
                    "runs down his chin to prevent a scream.");
                break;
            case 1:
                victim->command("emote whispers some words in Quenya " +
                    "and looks strengthened for it.");
                break;
            case 2:
                victim->command("shout For the love of Elbereth! " +
                    "I shall not give in!");
                break;
            case 3:
                victim->command("shout Manwe Sulimo! Give me the " +
                    "courage to resist my tormentors!");
                break;
            case 4:
                victim->command("emote whispers in a strained voice: " +
                    "You shall never conquer my spirit. Never!");
                break;
        }
    }
}

void
damage_victim(object victim, object who)
{
    int hit_p;

    hit_p = victim->query_hp();

    if(hit_p > 0)
    {
        hit_p /= 4;
        hit_p *= -1;
        victim->heal_hp(hit_p);
    }

    scream(victim);
}

void
do_torture(object victim, object who, string device)
{
    victim->add_prop(NPC_I_TORTURE_TIME, time());
    setup_torture(victim, who, device);
    gAlarm1 = set_alarm(8.0, 0.0, &show_torture(victim, who, device));
    gAlarm2 = set_alarm(1.0 + itof(random(5)), 0.0,
        &damage_victim(victim, who));

    return;
}

int
torture(string str)
{
    int delay_time;
    string target, implement;
    mixed victim;

    /* No argument given, failure notice. */
    if(!str)
    {
        notify_fail("Torture whom with what?\n");
        return 0;
    }

    /* Find what the target and implement strings should be. */
    sscanf(str, "%s", target);
    sscanf(str, "%s with %s", target, implement);

    /* Find if the target is a valid living. */
    if(!parse_command(target, TO, "[the] %l", victim))
    {
        notify_fail("Torture whom with what?\n");
        return 0;
    }

    /* Find if the victim is accessible */
    victim = NORMAL_ACCESS(victim, 0, 0);

    /* Limit torture to one victim. */
    if(sizeof(victim) > 1)
    {
        notify_fail("Torturing is best done one victim at a time.\n");
        return 0;
    }

    /* No torturing oneself */
    if(victim[0] == TP)
    {
        notify_fail("Torturing oneself can become very difficult.\n");
        return 0;
    }

    /* Only allow torturing the prisoner provided for now. */
    if(victim[0]->query_real_name() != "lentil")
    {
        notify_fail("There have been no orders to torture " +
            victim[0]->query_the_name(TP) + "!\n");
        return 0;
    }

    /* Set a delay between tortures. Wizards are exempt from the delay. */
    delay_time = time() - 8;
    if(victim[0]->query_prop(NPC_I_TORTURE_TIME) > delay_time)
    {
        notify_fail("Torture is a delicate art! You must give the " +
            "prisoner time to appreciate his situation.\n");
        return 0;
    }

    /* No implement given. */
    if(!strlen(implement))
    {
        switch(random(8))
        {
            case 0:
                implement = "chain";
                break;
            case 1:
                implement = "crusher";
                break;
            case 2:
                implement = "maiden";
                break;
            case 3:
                implement = "rack";
                break;
            case 4:
                implement = "rope";
                break;
            case 5:
                implement = "screw";
                break;
            case 6:
                implement = "spike";
                break;
            case 7:
                implement = "needle";
                break;
        }
    }

    implement = lower_case(implement);

    /* Give message dependant on the chosen implement. */
    switch(implement)
    {
        case "chain":
        case "chains":
            do_torture(victim[0], TP, "chain");
            return 1;
        case "crusher":
        case "head crusher":
            do_torture(victim[0], TP, "crusher");
            return 1;
        case "maiden":
        case "iron maiden":
            do_torture(victim[0], TP, "maiden");
            return 1;
        case "rack":
            do_torture(victim[0], TP, "rack");
            return 1;
        case "needle":
        case "needles":
            do_torture(victim[0], TP, "needle");
            return 1;
        case "rope":
        case "ropes":
            do_torture(victim[0], TP, "rope");
            return 1;
        case "screw":
        case "screws":
        case "thumb screw":
        case "thumb screws":
            do_torture(victim[0], TP, "screw");
            return 1;
        case "spike":
        case "spikes":
            do_torture(victim[0], TP, "spike");
            return 1;
    }

    notify_fail("Torture whom with what?\n");
    return 0;
}

int
enter_maiden(string str)
{
    if(!strlen(str))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if(str != "maiden" && str != "iron maiden")
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if(TP->query_hp() < (TP->query_max_hp() / 2))
    {
        notify_fail("That would be certain death in " +
            "your state of health!\n");
        return 0;
    }

    write("You enter the iron maiden. The door slams shut on " +
        "you, driving sharp deadly spikes through your body. " +
        "Waves of pain wash through you as you feel each spike " +
        "penetrating into your body. After a moment, the door " +
        "mercifully swings open, and you fall to the ground " +
        "close to death.\n");
    say(QCTNAME(TP) + " enters the iron maiden. The door slams " +
        "shut on " + TP->query_objective() + ". Bloodcurdling screams " +
        "resonate from inside until the door swings open and the " +
        "near dead " + QNAME(TP) + " falls to the ground.\n");
    TP->set_hp(1);
    TP->set_fatigue(0);

    return 1;
}

void
init()
{
    add_action(torture, "torture");
    add_action(enter_maiden, "enter");

    ::init();
}

public void
enter_inv(object ob, object from)
{
    object torturer;

    ::enter_inv(ob, from);

    if (!living(ob))
    {
        return;
    }

    if (!present("lentil", TO) && (torturer = present("torture_orc", TO)))
    {
        torturer->orc_leave();
    }
}

