/*
 * shrine
 *
 * This room contains the remains of a stone circle assembled
 * indoors for some unknown reason. Players can learn of the
 * 'Defender of Judgement' in this room, of use in the demon
 * quest.
 *
 * Khail - July 8/97
 */
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "tower.h"

inherit TOWERBASE;

int dusted;

public void
reset_room()
{
    if (dusted)
    {
        remove_item("writing");
        dusted = 0;
    }
}

public string
exa_altar()
{
    if (!dusted)
        return "The stone altar is only about a foot high, " +
            "and made of a strange black stone. It's " +
            "covered in a thick blanket of dust, but " +
            "something about the surface looks odd.\n";
    return "The stone altar is only about a foot high, " +
        "and made of a strange black stone. Parts of " +
        "it are covered in dust, but enough has been " +
        "cleared away to make out writing on it's surface.\n";
}

public string
exa_dust()
{
    if (!dusted)
        return "A thick blanket of dust covers the top " +
            "of the altar, it looks as if it hasn't been " +
            "cleaned in hundreds of years.\n";
    return "The dust has been cleared away from the top " +
        "of the altar, revealing some writing underneath.\n";
}
        
public void
create_khalakhor_room()
{
    set_short("within the ruins of an ancient tower");
    set_long("You are inside a wide, circular room in " +
        "the ruins of an ancient tower. The stone walls, " +
        "once strong, now seem on the verge of collapse. " +
        "The contents of the room are very odd, a series " +
        "of stone monoliths stand in a circle, capped " +
        "with horizontal stone slabs. In the center of " +
        "the ring, a low altar of black stone rests.\n");

    add_item(({"altar"}), VBFC_ME("exa_altar"));
    add_item(({"dust"}), VBFC_ME("exa_dust"));

    add_exit(TOWER + "storage", "east");
    add_exit(TOWER + "entrance", "southeast");
    reset_room();
}

public int
do_clear(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'dust' [from] [the] [altar]"))
    {
        NF(capitalize(query_verb()) + " what from what?\n");
        return 0;
    }

    if (dusted)
    {
        write("The dust has already been " + query_verb() + "ed " +
            "away from the surface of the altar.\n");
        return 1;
    }

    write("Bending over, you quickly " + query_verb() + 
        " some of the dust away from the surface of the " +
        "altar. You find some writing beneath!\n");
    say(QCTNAME(TP) + " bends over and brushes away some " +
        "dust from the top of the altar.\n");
    dusted = 1;
    add_item("writing", "The writing atop the stone altar " +
        "appears to be an old dialect, but you might be " +
        "able to read it if you try.\n");
    return 1;
}
 
public int
do_read(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!dusted)
        return 0;

    if (!parse_command(str, TP, "[the] 'writing' [on] [the] [altar]"))
    {
        NF("Read what?\n");
        return 0;
    }

    if (TP->query_skill(SS_LANGUAGE) < 30)
    {
        write("You cannot understand the language the " +
            "writing is in.\n");
        return 1;
    }

    write("You recognize the language of the writing as " +
        "an old human dialect several centuries old. " +
        "Loosely translated, it reads:\n\n" +
        "\tHear me, Guardians of Judgement, and feel\n" +
        "\tthe flame of power that burns within me.\n" +
        "\tAmidst these eternal stones do I cast my\n" +
        "\tfate upon thee as a Defender of Judgement,\n" +
        "\tthat I might take up the blade of masters,\n" +
        "\twhich is my right as one who bears the\n" +
        "\tthe thistlemark, and one who has been summoned\n" +
        "\tto follow those who have passed on.\n\n" +
        "Beneath the passage are carved several names, " +
        "the last one being simply Croduath.\n");
    return 1;
}
   
public void
init()
{
    ::init();
    add_action(do_clear, "clear");
    add_action(do_clear, "clean");
    add_action(do_clear, "brush");
    add_action(do_clear, "wipe");
    add_action(do_read, "read");
}