/*
 * This is the entrance to the Shelobs lair. To escape from Shelob you will
 * need to cut the cobweb that het ladyship makes as soon as she enters the
 * room at a moment you are in it. This will give a few xp points.
 *
 * /Mercade, 12 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

#define SHELOB MORDOR_DIR + "npc/shelob"
#define COBWEB_QUEST_GROUP 0 /* ? */
#define COBWEB_QUEST_BIT   7 /* ? */
#define MAX_COBWEB_STRENGTH 10

/*
 * Prototypes
 */
void reset_room();

/*
 * static variables
 */
int cobweb_strenth;

/*
 * This function defines the room.
 */
void
create_room()
{
    set_name("First part of Shelobs lair");

    add_prop(OBJ_S_WIZINFO, BSN("Trying to leave this room to the south, " +
        "leaving the lair, will, with a certain random change, make a " +
        "cobweb from Shelob block your exit. You will need a knife or sword " +
        "and some skill and str to be able to cut the cobweb and gain some " +
        "xp. When Shelob is in the room, she will definately make a cobweb " +
        "the moment you enter the room (enterning the room isn't hindered)." +
        "You can even enter the room after Shelob made a cobweb."));

    add_exit(LAIR_DIR + "lair02", "", 0, 1);
    add_exit(LAIR_DIR + "entrance", "south", "@@blocked_by_cobweb", 1);

    cobweb_strength = 0; /* The cobweb isn't there on initialisation */

    make_the_room();
    reset_room();
}

/*
 * This procedure is called each time the room needs to be updated.
 */
void
reset_room()
{
    object shelob;

    if (!find_living("shelob, her ladyship"))
    {
        setuid();
        seteuid(getuid(TO));

        shelob = clone_object(SHELOB);
        shelob->move(LAIR_DIR + "lair03");
        TO->create_cobweb();
    }

    return;
}

/*
 * This procedure is called to add the cut-command to mortals, every time they
 * enter this lair.
 */
void
init()
{
    ::init();

    add_action("do_cut", "cut");
    add_action("do_break", "break");
    add-action("do"break", "tear");
}

/*
 * If Shelob enters this cave, she will automatically seal the room by creating
 * a cobweb. This cobweb will also be created if Shelob is present in this
 * cave and a mortal (and not wizard) enter this room.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv();

    if (ob->query_wiz_level())
    {
        return;
    }

    if (present("shelob", TO))
    {
        TO->create_cobweb();
    }

    return;
}

string
cobweb_description()
{
    string str;

    if (cobweb_strength)
    {
        str = "Across the height and width of the tunnel a vast web was " +
            "spun, orderly as the web of a some huge spider, but " +
            "denser-woven and far greater. Each thread is as thick as a " +
            "rope. The cobwebs seem soft and a little yielding, and yet " +
            "strong and impervious; air filters through, but not a glimmer " +
            "of any light.";
        if (cobweb_strenth < (MAX_COBWEB_STRENGTH / 2))
        {
            str += " Hacking the cobweb seems to have made at least a few " +
                "of the countless cords snap as one end lashes your hand as " +
                "as you reach for the cobweb to examine it.";
        }
    }
    else
    {
        str = "Luckily you don't see any cobwebs in this cave.";
    }

    return BSN(str);
}

/*
 * This function is called by Shelob to create the cobweb.
 */
void
create_cobweb()
{
    cobweb_strength = MAX_COBWEB_STRENGTH;
}

/*
 * If a wizard casts a shrink spell on himself, he'd better cast a growth
 * spell as well.
 */
void
cast_growth_spell(object player)
{
    player->catch_msg(BSN("Before you get lost in this huge world, you cast " +
        "another spell on yourself. This time it is a growth spell that " +
        "restores your previous size."));
    TELL_ROOM(" casts a growth spell on " + OBJECTIVE(player) + "self to " +
        "restore " + POSSESSIVE(player) + " previous size, for " +
        PRONOUN(player) + " cast a shrink spell on " + OBJECTIVE(player) +
        "self to be able to escape from Shelobs lair.", player);

    return;
}

/*
 * This function is called to determine whether a player can leave through the
 * the lair or whether this exit is blocked by the cobweb.
 */
int
blocked_by_cobweb()
{
    if (cobweb_strength)
    {
        if (TP->query_wiz_level())
        {
            write(BSN("A cobweb blocks the exit, being a wizard though, you " +
                "cast a shrink spell on yourself and are able to pass the " +
                "cobweb without touching it."));
            set_alarm(1.0, 0.0, "cast_growth_spell", TP);
            LSAY("A cobweb blocks the exit from the lair, but ", " casts a " +
                "shrink spell on " + OBJECTIVE(TP) + "self and manages to " +
                "pass the cobweb without touching it.");

            return 0;
        }

        write(BSN("The opening, the tunnels end, at last is is before you. " +
            "Panting, yearning for a roofless place, you fling yourself " +
            "forward; and then in amazement you stagger, tumbling back. The " +
            "outlet is blocked with some barrier, but not of stone: soft " +
            "and a little yielding it seems, and yet strong and impervious.));
        SAY(" tries to leave this tunnel, but to " + POSSESSIVE(TP) +
            "amazement, " + PRONOUN(TP) + " is hurled back by something " +
            "soft and strong. You fear that it is a cobweb, woven by a huge " +
            "spider that blocked " + OBJECTIVE(TP) + ".");

        return 1;
    }

    /* no cobweb, no talk */
    return 0;
}

/*
 * You can't "break" the cobweb. It wield not yield to pressure.
 */
int
do_break(string str)
{
    object weapon;

    if (!str)
    {
        NF("What do you want to " + query_verb() + "?");
        return 0;
    }

    NF("What do you want to " + query_verb() + " with what?");

    if (!parse_command(str, ENV(TP),
        " 'cobweb' / 'cobwebs' / 'cord' / 'cords' 'with' %o ", weapon))
    {
        write (BSN("You try to " + query_verb() + " with your " +
            check_call(weapon->short()) + ", but that effective at all. " +
            "The cobwebs yield a little, but won't break."));
        SAY("tries to " + query_verb() + " the cobweb, but fails.");
        return 1;
    }

    return 0;
}

/*
 * You can "cut" the cobweb though, provided that you have the str and the
 * skill to handle your weapon.
 */
int
do_cut(string str)
{
    object weapon;

    if (!str)
    {
        NF("What do you want to " + query_verb() + "?");
        return 0;
    }

    NF("What do you want to " + query_verb() + " with what?");

    if (!parse_command(str, ENV(TP),
        " 'cobweb' / 'cobwebs' / 'cord' / 'cords' 'with' %o ", weapon))
    {
/*
   do the cutting and solve the quest perhaps ?
*/
        return 1;
    }

    return 0;
}
