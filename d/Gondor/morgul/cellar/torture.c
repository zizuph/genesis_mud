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

#define PLAYER_I_RELEASED_LENTIL "_player_i_released_lentil"

/* Prototype */

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
torture(string str)
{
    int delay_time;
    string target, implement;
    mixed victim;

        write("You decide to leave the torturing to the guards instead.\n");
}

int
enter_maiden(string str)
{
    if(!strlen(str))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if(str != "maiden" && str != "iron")
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
