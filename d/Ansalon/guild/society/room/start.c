/*
 * /d/Ansalon/guild/society/room/start.c
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
 * Kender start room
 * Gwyneth, July 1999
 */
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <macros.h>

inherit KENDERMORE_IN;

#define PLAYER_I_IS_IN_BED "_player_i_is_in_bed"
#define PLAYER_I_IS_SLEEPING "_player_i_is_sleeping"

void
create_kendermore_room()
{
    set_short("Kender sleeping quarters");
    set_long("This is a cozy looking room. Many small, but comfortable, " +
        "looking beds line the walls in two rows. Brightly coloured quilts " + 
        "cover each of the beds, and a fluffy pillow has been placed at each " +
        "head. A long woven rug runs from one wall to the other, separating " + 
        "the two rows of beds. The beds don't seem to belong to any one " + 
        "kender, but are here for any who care to use them. Several " +
        "wooden pegs hang on one of the walls.\n");

    add_item(({"several wooden pegs", "several pegs", "wooden pegs",
        "pegs", "peg", "wooden peg"}), "Many different colours and " +
        "styles of beads hang on the pegs. You might exchange the " +
        "ones you have for a different kind. The colours merge and " +
        "intertwine with each other, but you can make out red, orange, " +
        "green, blue, violet, pink, white, black, silver, gold, bronze, " +
        "brass, and platinum. The types of beads are difficult to " +
        "make out as well, but you manage to find a variety of them, " +
        "including pale, shiny, dark, long, sparkly, metallic, large, " +
        "small, medium, bright and short strands of beads.\n");
    add_item(({"rug", "long rug", "woven rug", "long woven rug"}), "This is " + 
        "a very long rug, stretching from one wall to the other. Many " + 
        "different colours have been woven into this rug, from vivid blues " + 
        "to bright yellows and greens, into a beautiful sunburst pattern. " + 
        "Not only is this rug pleasing to the eye, but it looks like it " + 
        "would keep tiny kender feet warm on cold winter mornings.\n");
    add_item(({"pattern", "colours", "lines", "wavy lines"}), 
        "Various shades of startling blue, " + 
        "yellow and green work their way out from the center of the rug " + 
        "to the outside in wavy lines.\n");
    add_item(({"small beds", "comfortable beds", "small comfortable beds",
        "beds", "rows", "two rows"}), "The beds are here for any kender who " + 
        "needs a place to stay after returning from their long travels.\n"); 
    add_item(({"walls", "wall"}), "The walls have been hand painted by " + 
        "the residents to reflect their travels. The scenes merge into " + 
        "each other, but the overall effect is pleasant.\n");
    add_item("scenes", "You see many different scenes, from dragons and " + 
        "mages to dogs and children.\n");
    add_item("quilts", "They are each different. Some are bright solid " + 
        "colours, while others are plaid, striped or spotted. They all " + 
        "look very warm and fluffy, though.\n");
    add_item(({"pillows", "fluffy pillows", "head"}), "Made of soft cloth " + 
        "stuffed with goose down, these pillows look very inviting.\n");

    add_prop(ROOM_M_NO_ATTACK, "Shh! People are trying to sleep!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "Shh! People are trying to sleep!\n");
    add_exit(KGROOM + "po", "north", 0);
    add_exit(KGROOM + "rack_room", "east", 0);
}

int
start(string str)
{
    if (str != "here")
    {
        NF("Start where?\n");
        return 0;
    }

    if (!MEMBER(TP))
    {
       write("The beds are only for members of this guild!\n");
       return 0;
    }

    if (TP->set_default_start_location(GUILD_STARTLOC))
        write("You will now start here in the Kender house.\n");

    else
        write("Sorry, some problem prevents you from starting here!\n");

    return 1;
}

int
bed_sit(string str)
{
    if ((str == "on bed") || (str == "in bed") || (str == "down on bed") ||
        (str == "down in bed"))
    {
        if (!TP->query_prop(PLAYER_I_IS_IN_BED))
        {
            write("You pull back the quilts and hop into one of the " + 
                "beds.\n");
            say(QCTNAME(TP) + " pulls back the quilts and hops into one of " + 
                "the beds.\n");
            TP->add_prop(PLAYER_I_IS_IN_BED, 1);
            TP->add_prop(LIVE_S_EXTRA_SHORT, " lying in a bed");
            TP->reveal_me();
            return 1;
        }

        if (TP->query_prop(PLAYER_I_IS_IN_BED))
        {
            write("You're already in the bed!\n"); 
            return 1;
        }
    }
    NF("Sit where?\n");
    return 0;
}

int
stand_up(string str)
{
    if ((str == "up") || (!str))
    {
        if (TP->query_prop(PLAYER_I_IS_IN_BED))
        {
            write("You hop out of bed.\n");
            say(QCTNAME(TP) + " hops out of bed.\n");
            TP->remove_prop(LIVE_S_EXTRA_SHORT);
            TP->remove_prop(PLAYER_I_IS_IN_BED);
            TP->remove_prop(PLAYER_I_IS_SLEEPING);
            TP->remove_prop(LIVE_M_MOUTH_BLOCKED);
            TP->reveal_me();
            return 1;
        }

        if (!TP->query_prop(PLAYER_I_IS_IN_BED))
        {
            write("First you must be in the bed in order to stand " + 
                "up from it!\n");
            return 1;
        }
    }
    NF("Stand up?");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    if (ob->query_prop(PLAYER_I_IS_IN_BED))
    {
        ob->catch_tell("You hop out of bed.\n");
        ob->tell_watcher(QCTNAME(ob) + " hops out of bed.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop(PLAYER_I_IS_IN_BED);
        ob->remove_prop(PLAYER_I_IS_SLEEPING);
        ob->remove_prop(LIVE_M_MOUTH_BLOCKED);
        TP->reveal_me();
        return;
    }

    return;
}

int
bed_sleep(string str)
{
    if (TP->query_prop(PLAYER_I_IS_IN_BED))
    {
        write("You close your eyes and travel into the land of dreams.\n");
        say(QCTNAME(TP) + " closes " + HIS(TP) + " eyes and falls " + 
            "asleep.\n");
        TP->add_prop(PLAYER_I_IS_SLEEPING, 1);
        TP->add_prop(LIVE_S_EXTRA_SHORT, ", who is fast asleep");
        TP->add_prop(LIVE_M_MOUTH_BLOCKED, " You are asleep, and only " + 
            "manage to mumble something.\n");
        return 1;
    }

    if (TP->query_prop(PLAYER_I_IS_SLEEPING))
    {
        write("You're already asleep!\n");
        return 1;
    }

    else
    {
        write("You pull back the quilt, and lay down in one of the " + 
            "beds. You close your eyes and travel into the land of " + 
            "dreams.\n");
        say(QCTNAME(TP) + " pulls back the quilt, hops into one of " + 
            "the beds and falls fast asleep.\n");
        TP->add_prop(PLAYER_I_IS_SLEEPING, 1);
        TP->add_prop(PLAYER_I_IS_IN_BED, 1);
        TP->add_prop(LIVE_S_EXTRA_SHORT, ", who is fast asleep");
        TP->add_prop(LIVE_M_MOUTH_BLOCKED, " You are asleep, and only " +
            "manage to mumble something.\n");
        TP->reveal_me();
        return 1;
    }
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

int
exchange(string str)
{
    object beads;
    string type, colour;

    if(!strlen(str))
    {
        NF("Exchange your beads for what?\n");
        return 0;
    }

    str = lower_case(str);

    sscanf(str, "beads for %s %s beads", type, colour);

    if(!type || !colour)
    {
        NF("Exchange your beads for what? Syntax is <exchange " +
            "beads for type colour beads>.\n");
        return 0;
    }

    if(!parse_command(type, ({}), "'pale' / 'shiny' / " +
        "'dark' / 'long' / 'sparkly' / 'metallic' / 'large' / 'small' / " +
        "'medium' / 'bright' / 'short'"))
    {
        NF("There is no such type " + type + " on the pegs. Syntax " +
            "is <exchange beads for type colour beads>.\n");
        return 0;
    }

    if(!parse_command(colour, ({}), "'red' / 'orange' / " +
        "'green' / 'blue' / 'violet' / 'pink' / 'white' / 'black' / " +
        "'silver' / 'gold' / 'bronze' / 'brass' / 'platinum'"))

    if(!parse_command(colour, ({}), "'red' / 'orange'"))
    {
        NF("There is no such colour " + colour + " on the pegs. Syntax " +
            "is <exchange beads for type colour beads>.\n");
        return 0;
    }

    if(MEMBER(TP) &&
       (beads = present("kender_guild_emblem", TP)))
    {
        beads->remove_adj(beads->query_adjs());
        beads->setup_beads(type, colour);
        write("You exchange your beads for a strand of " +
            type + " " + colour + " beads.\n");
        tell_room(TO, QCTNAME(TP) + " exchanges " + HIS(TP) +
            " beads for a strand of " + type + " " + colour +
            " beads.\n", TP);
    }
    else if(MEMBER(TP) &&
            (TP->query_login_time() < (TP->query_login_time() + 60)))
    {
        NF("Please wait a minute after entering the " +
            "realms to get a new set of beads.\n");
        return 0;
    }
    else if(MEMBER(TP))
    {
        beads = clone_object(GUILD_EMBLEM);
        beads->remove_adj(beads->query_adjs());
        beads->setup_beads(type, colour);
        beads->move(TP);
        write("You find that you've lost your beads, so " +
            "you pick up a strand of " + type + " " + colour +
            " beads.\n");
        tell_room(TO, QCTNAME(TP) + " takes a strand of beads from " +
            "a peg on the wall.\n", TP);
    }
    else
    {
        write("You must be a member of this guild to take " +
            "a new strand of beads! Contact a wizard if you are a " +
            "member.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(bed_sit, "sit");
    add_action(stand_up, "stand");
    add_action(bed_sleep, "sleep");
    add_action(start, "start");
    add_action(exchange, "exchange");
    add_action(stand_up, "wake");
}
