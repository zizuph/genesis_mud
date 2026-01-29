#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <const.h>
#include <ss_types.h>
#include <wa_types.h>
#include "banshee.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

object banshee;
int banshee_kissed,
    banshee_slain;

public void
summon_banshee()
{
    reset_euid();

    if (banshee_kissed || banshee_slain)
        return;

    remove_item("woman");
    remove_item("body");

    tell_room(TO, "The body of the woman suddenly rises into the "+
        "air and transforms before your eyes, it's the Banshee!\n");
    banshee = clone_object(PATH + "banshee");
    banshee->move_living("M",TO);

    banshee_kissed = 1;
}

public string
exa_woman()
{
    string ret;

    ret = "Staring down at the face of the woman, your first instinct is " +
        "that she's asleep, aside from the fact that she must have " +
        "been resting here for centuries, and the absense of any sign " +
        "of breathing. ";

    switch (TP->query_gender())
    {
        case G_MALE:
            ret += "Your eyes linger across the woman's body, and you " +
                "find yourself wishing she were alive and in your arms. ";
            break;
        case G_NEUTER:
            ret += "Your eyes flicker across the young woman's beautiful " +
                "figure, and find yourself unimpressed. ";
            break;
        default:
            ret += "Your eyes glance at the woman, and you find yourself " +
                "feeling an inexplicable pang of jealousy at her " +
                "beauty. ";
    }

    ret += "Beneath her flawless ivory skin, a strange green light " +
        "glows through, it's source unexplained. Your eyes trace back " +
        "up her form and stare into her face, at peaceful eyes and " +
        "lush lips which seem to long for a kiss.\n";

    return ret;
}

public void
reset_banshee()
{
    if (banshee_slain)
        return;

    banshee_kissed = 0;
    add_item(({"woman","body"}), VBFC_ME("exa_woman"));
}

public string
vbfc_long()
{
    if (banshee_kissed)
        return "You are standing within the center of the last structure " +
        "still standing within this cavern. The construction is " +
        "fairly simple, it's little more than a smooth stone floor " +
        "upon which stand walls of tall columns which support a " +
        "peaked roof. At the center of the room stands a low stone " +
        "table.\n";
    else
        return "You are standing within the center of the last structure " +
        "still standing within this cavern. The construction is " +
        "fairly simple, it's little more than a smooth stone floor " +
        "upon which stand walls of tall columns which support a " +
        "peaked roof. At the center of the room, however, a low " +
        "stone table of sorts supports the body of a beautiful " +
        "woman.\n";
}

public string
exa_table()
{
    if (banshee_kissed)
        return "The table is constructed of white stone laid across two stone " +
        "blocks, standing about waist-high. The edge of the slab is " +
        "gilded with gold trim, upon which is engraved deep lettering.\n";
        
    else
        "The table is constructed of white stone laid across two stone " +
        "blocks, standing about waist-high. The edge of the slab is " +
        "gilded with gold trim, upon which is engraved deep lettering. " +
        "The unclothed body of a beautiful woman lies atop the surface, " +
        "apparently in a deep slumber, aside from the sickly green light " +
        "that seems to emanate from beneath her skin.\n";
}

public void
create_khalakhor_room()
{
    set_short("ancient structure");
    set_long(VBFC_ME("vbfc_long"));

    add_item(({"floor","ground"}),
        "The floor is simply enough constructed of smooth white stone.\n");
    add_item(({"columns","column"}),
        "The four sides of the building are entirely comprised of thick " +
        "white columns of stone. The columns themselves are unadorned, " +
        "but amazing still in the fact they remain standing while all " +
        "else lies in ruins.\n");
    add_item(({"roof","ceiling"}),
        "The roof of the structure is constructed of two large slabs of " +
        "white stone peaked and mounted on the columns around the edges " +
        "of the structure.\n");
    add_item(({"table","stone table"}), VBFC_ME("exa_table"));
    add_item(({"woman","body"}), VBFC_ME("exa_woman"));
    add_item(({"lettering"}),
        "The lettering is ancient, but still clearly legible if you " +
        "care to try to read it.\n");
/*
    banshee_slain = IMMORTAL_MASTER->query_banshee_status();
 */

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(PATH + "ruins", "out");
}

public int
do_read(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'lettering' / 'writing'"))
        return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
        notify_fail("It's too dark in here to read anything.\n");
        return 0;
    }

    say(QCTNAME(TP) + " stoops over and examines the writing on the "+
        "edge of the table carefully.\n");

    if (TP->query_skill(SS_LANGUAGE) > 50)
    {
        write("You translate the writing to read: Ye who read this beware " +
            "the temptations of the Banshee, lest ye fall to the fate of " +
            "we who once resided here. Know that even now thy doom is " +
            "almost certain.\n");
        if (banshee_kissed)
        {
            write("You stand up again and stare at the table in wonder.\n");
            say(QCTNAME(TP) + " stands up again and stares at the table " +
                "in wonder.\n");
            return 1;
        }
        write("You stand up again and stare at the body in shock.\n");
        say(QCTNAME(TP) + " straightens up again and stares at the " +
            "body in shock.\n");
        return 1;
    }

    if (TP->query_stat(SS_WIS) > 80)
    {
        write("You are unable to read the writing, but you have a " +
            "nagging suspicion it's worth finding someone who can " +
            "read it before doing anything else.\n");
        if (banshee_kissed)
        {
            write("You stand up again and stare at the table in wonder.\n");
            say(QCTNAME(TP) + " stands up again and stares at the table " +
                "in wonder.\n");
            return 1;
        }
        write("You stand up again, frowning at the body in thought.\n");
        say(QCTNAME(TP) + " straightens up again, staring at the " +
            "woman's body apparently in deep thought.\n");
        return 1;
    }

    write("You are unable to read the writing, but it couldn't be " +
        "that important anyway, so you straighten up and give a "+
        "shrug, ignoring it.\n");
    say(QCTNAME(TP) + " straightens up and shrugs, apparently " +
        "unconcerned with the lettering.\n");
    return 1;
}

public int
do_kiss(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'body' / 'woman'"))
        return 0;

    if (banshee_kissed)
        return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
        notify_fail("It's too dark to see her.\n");
        return 0;
    }

    reset_euid();

    write("Unable to resist temptation, you bend over and deeply " +
        "kiss the woman's lips, surprised to discover them warm and " +
        "full beneath yours despite her condition. You are shocked " +
        "to feel a rush of breath as she opens her mouth slightly " +
        "beneath yours and inhales deeply! Suddenly her eyes open " +
        "and as the green glow flares brighter than the sun, you " +
        "feel your life sucked out of you!\n");
    say(QCTNAME(TP) + " impulsively bends over and deeply kisses " +
        "the beautiful woman, and stares in shock as the figure " +
        "inhales deeply and opens her eyes! Suddenly, the green " +
        "light swells outwards from her open mouth and enshrouds " +
        QTNAME(TP) + " completely!\n");
    TP->command("$scream");

    if (TP->query_base_stat(SS_DIS) < 100)
    {
        write("Unable to tear yourself away, you feel the cold hand of " +
            "death close around you.\n");
        say("Unable to tear " + HIM_HER(TP) + "self away from the " +
            "the fatal kiss, " + QTNAME(TP) + "'s eyes roll back in " +
            "their sockets, and you watch helplessly as " + HE_SHE(TP) +
            " dies horribly!\n");
        TP->heal_hp(-1000000);
        TP->do_die(TO);
        log_file(BANSHEE_DEATH, TP->query_name() + " died of kiss, " +
            ctime(time()) + ", statave " + TP->query_average_stat() + ".\n");
        TP->do_die(TO);
        summon_banshee();
        return 1;
    }

    TP->hit_me(TP->query_max_hp(), MAGIC_DT, TO, -1);
    if (TP->query_hp() <= 0)
    {
        write("Summoning up your dwindling reserves of will, you " +
            "attempt to break free of the kiss, but it is too late, "+
            "and you succumb to the cold hand of death.\n");
        say(QCTNAME(TP) + " struggles to break free of the kiss, " +
            "but it is too late for " + HIM_HER(TP) + ", and " +
            "you watch helplessly as " + HIS_HER(TP) + " eyes roll " +
            "back in their sockets and "+ HIS_HER(TP) + " dies before " +
            "you!\n");
        log_file(BANSHEE_DEATH, TP->query_name() + " died of kiss, " +
            ctime(time()) + ", statave " + TP->query_average_stat() + ".\n");
        TP->do_die(TO);
        summon_banshee();
    }

    write("Summoning up your dwindling reserves of will, you manage " +
        "to break free of the kiss before the last of your life is " +
        "sucked away!\n");
    say(QCTNAME(TP) + " manages to break free of the kiss before it " +
        "finishes " + HIM_HER(TP) + " off, weak but alive!\n");
    log_file(BANSHEE_DEATH, TP->query_name() + " survived the kiss, " +
        ctime(time()) + ", statave " + TP->query_average_stat() + ".\n");
    summon_banshee();
    return 1;
}
           
public void
init()
{
    ::init();
    add_action(do_read, "read");
    add_action(do_kiss, "kiss");
}
