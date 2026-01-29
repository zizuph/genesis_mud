/*
 * /d/Gondor/mordor/ungol/lair/std_lair.c
 *
 * This room is the standard lair/tunnel room of the lair of Shelob, Torech
 * Ungol. It adds some properties and descriptions and sound dies it it!
 *
 * /Mercade, 18 july 1993
 *
 * Revision history:
 *
 *    Toby, 10th-Sept-2007: Added terrain.h
 */

/*
 * This room doesn't use the time function by Elessar Telcontar for the lair
 * is too dark to see anything... The only thing you can do here is the
 * estimate the time of day.
 */
inherit "/std/room";

#include <stdproperties.h>
#include <terrain.h>
#include "/d/Gondor/defs.h"

#define WIZ_I_I_GOT_THE_MESSAGE_AT_TORECH_UNGOL \
      "_wiz_i_i_got_the_message_at_torech_ungol"

/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long)
{
    string long_add_text = "Nothing special can be seen, but ";

    if (!strlen(extra_long))
    {
        extra_long = "";
    }

    switch(random(5))
    {
        case 0:
            long_add_text = "You see a cobweb in the corner and ";
            add_item("cobweb", BSN("In one of the corners of this dark cave " +
                "you see a gigantic cobweb, each single bond of it being an " +
                "inch in diameter. It might be blocking your exit. " +
                "You wonder what creature could have made such a cobweb."));
            break;
        case 1:
            long_add_text = "Except from some rocks, nothing special can be " +
                "seen, but ";
            break;
        case 2:
            long_add_text = "Several tales are told about this place, each " +
                "one scarier than the other, making ";
            break;
        case 3:
            long_add_text = "Some illegible runes are carved in the wall and ";
            add_item( ({ "rune", "runes" }), BSN("There are some runes " +
                "carved into the wall. They must be made by orcs to help " +
                "them find their way in this dark cave. You do not " +
                "understand them at all."));
            break;
    }

    set_name("Torech_Ungol");
    set_short("Inside a dangerous cave, Torech Ungol, close to Mordor");
    set_long(BSN("Inside this cave called Torech Ungol there is nothing " +
        "but darkness. The air is still, stagnant, heavy and the sound " +
        "falls dead. Sniffing the air you are overcome by a terrible smell. " +
        long_add_text + "you sense evil lurking in the dark." + extra_long));

    add_item(({"cave", "lair"}), BSN("The darkness here prevents you to see " +
        "much of this lair. You feel evil lurking in the dark and wonder " +
        "what peril might be your fate."));
    add_item(({"wall", "walls"}), BSN("The walls feel remarkably smooth."));
    add_item(({"floor", "ground"}), BSN("As you move around, you stumble " +
        "over rocks all over the floor."));
    add_item(({"roof", "ceiling"}), BSN("The ceiling is too high for you to " +
        "reach."));
    add_item(({"rock", "rocks"}), BSN("There are many rocks in this lair, " +
        "some of them are big, some are smaller. There is nothing special " +
        "about them though."));
    add_item("air", BSN("Even though the air in this lair is stagnant and " +
        "heavy, it cannot be seen. In fact you cannot see more than darkness " +
        "here, but there is a difference between air and darkness."));
    add_item("darkness", BSN("You are really curious as to what darkness " +
        "looks like."));

    set_terrain(TERRAIN_SHADOWS | TERRAIN_UNDERGROUND | TERRAIN_BITTER_COLD | TERRAIN_ROCK);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1); /* it is rather dark in here ;-) */
    add_prop(OBJ_S_WIZINFO,
        BSN("This is Torech Ungol, Shelobs lair. In this lair you might " +
        "encounter Shelob and if you do, you'd better run for your life " +
        "for She is not to toy with. Another feature about this lair is " +
        "that speech (generally: sound) is blocked with 50 percent chance. " +
        "This also applies to think and ponder to block all communications " +
        "that is not due to some guild command. BTW: the light level in the " +
        "lair = -1."));


}

/*
 * Sound dies in the lair. (and you'd better not try to smell the air.)
 */
void
init()
{
    ::init();

    /*
     * If you try to give the time-command.
     */
    add_action("do_time_in_lair", "time");

    /*
     * These add_actions are called when you try to smell of sniff the air!
     */
    add_action("do_smell_in_lair", "smell");
    add_action("do_smell_in_lair", "sniff");

    /*
     * The next add_actions are to make sure that no sound is heard in this
     * lair.
     */
    add_action("do_no_sound_in_lair", "ask");
    add_action("do_no_sound_in_lair", "cry");
    add_action("do_no_sound_in_lair", "'", 1);
    add_action("do_no_sound_in_lair", "say");
    add_action("do_no_sound_in_lair", "rsay");
    add_action("do_no_sound_in_lair", "grsay");
    add_action("do_no_sound_in_lair", "dsay");
    add_action("do_no_sound_in_lair", "rasp");
    add_action("do_no_sound_in_lair", "hiss");
    add_action("do_no_sound_in_lair", "mumble");
    add_action("do_no_sound_in_lair", "aasay");
    add_action("do_no_sound_in_lair", "ksay");
    add_action("do_no_sound_in_lair", "scream");
    add_action("do_no_sound_in_lair", "swear");
    add_action("do_no_sound_in_lair", "shout");
    add_action("do_no_sound_in_lair", "whisper");

    /*
     * These add_actions are to make sure that other people see you think
     * or ponder something as a way of communication.
     */
    add_action("do_no_vision_in_lair", "ponder");
    add_action("do_no_vision_in_lair", "think");
    add_action("do_no_vision_in_lair", "clook");

    /*
     * In addition, the Ranger-command 'listen' should not work well here.
     */
    // Ranger command listen was changed to rhear
    add_action("do_no_listen_in_lair", "rhear");
    add_action("do_no_listen_in_lair", "listen");
}

/*
 * Only with a 50 percent change, you are heard in Shelobs lair. The write,
 * return 1; construct is used to block speech etc. Wizards aren't affected
 * of course.
 */
int
do_no_sound_in_lair(string str)
{
    int amount;

    if(TP->query_wiz_level())
    {
        amount = (int)TP->query_prop(WIZ_I_I_GOT_THE_MESSAGE_AT_TORECH_UNGOL);
        if (amount >= 5)
        {
            return 0;
        }

        amount += 1;
        TP->add_prop(WIZ_I_I_GOT_THE_MESSAGE_AT_TORECH_UNGOL, amount);

        write(BSN("Mortals can only speak with a 50% chance in this cave."));
        return 0;
    }

    if(random(100) < 50)
    {
        write(BSN("The air is so heavy in this cave that the sound you " +
            "make dies out before anyone can hear it."));
        return 1;
    }

    return 0;
}

/*
 * Only with a 50 percent change, you are seen in Shelobs lair. The write,
 * return 1; construct is used to block ponder etc. Wizards aren't affected
 * of course.
 */
int
do_no_vision_in_lair(string str)
{
    int amount;

    if(TP->query_wiz_level())
    {
        amount = (int)TP->query_prop(WIZ_I_I_GOT_THE_MESSAGE_AT_TORECH_UNGOL);
        if (amount >= 5)
        {
            return 0;
        }

        amount += 1;
        TP->add_prop(WIZ_I_I_GOT_THE_MESSAGE_AT_TORECH_UNGOL, amount);

        write(BSN("Mortals can only speak with a 50% chance in this cave."));
        return 0;
    }

    if(random(100) < 50)
    {
        write(BSN("The darkness in this cave is so impervious that " +
            "your thought cannot be seen by anyone."));
        return 1;
    }

    return 0;
}

/*
 * Better not try to smell the air.
 */
int
do_smell_in_lair(string str)
{
    write(BSN("You shouldn't have tried to " + query_verb() + " anything in " +
        "here. Now you are overcome by a terrible smell. This lair smells " +
        "worse than orcs or goblins do. You wonder what could produce such " +
        "a smell."));

    /*
     * I should do something nasty to him, like a small poison or something,
     * but for the time being, I shall only make him puke.
     */
    FIX_EUID;
    TP->command("puke");

    return 1;
}

/*
 * If you try to give the time-command.
 */
int
do_time_in_lair(string str)
{
    write(BSN("You guess it is " + call_other(CLOCK,
        "query_time_of_day") + " now, but since you are in this dark cave, " +
        "you cannot estimate the time more precisely."));
    return 1;
}

/*
 * If a Ranger tries to 'listen' into adjacent rooms.
 */
int
do_no_listen_in_lair(string str)
{
    if (random(100) < 80)
    {
        write(BSN("The heavy and stifling air in this cave hardly carries " +
            "any sound far before it dies out. You hear nothing."));
        return 1;
    }
    return 0;
}

