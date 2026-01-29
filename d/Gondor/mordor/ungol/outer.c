/*
 * /d/Gondor/mordor/ungol/outer.c
 *
 * This is the room under the tower of Cirith Ungol, the entrance to Mordor
 * where many evil orcs and other foul creatures may be found. There is an
 * entrance into the tower and a field of darkness, preventing you from going
 * west. Maybe you should better read the long desc or something. Several
 * descriptions are written by the master, J.R.R. Tolkien. I took them for
 * they are brilliant and so I need to notify you I did and honour him.
 *
 * /Mercade, may 31 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/common/room";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/findroom.h"

#define OTHER_PASS         UNGOL_DIR + "inner"
#define PLAYER_HOLDS_PHIAL "_player_holds_phial"
#define PHIAL_FILE         MORDOR_DIR + "obj/phial.c"

/*
 * This variable is used to make sure the watchers only call once if a team
 * passes.
 */

int watchers_cried;

/*
 * Prototypes
 */

void reset_room();
string describe_room();

/*
 * This function defines the room.
 */

void
create_room()
{
    set_name("Pass into Mordor, below the towers");
    set_short("At the gate at the Morgul Pass, outside Mordor");
    set_long("@@describe_room");

    add_item(({"field", "darkness", "field of darkness"}), "@@exa_field");
    add_item(({"watcher", "watchers"}), BSN("The watchers are like great " +
        "figures seated upon thrones. Each has three joined bodies, and " +
        "three heads facing outward, inward and across the gateway. The " +
        "heads have vulture-faces, and on their great knees are laid " +
        "clawlike hands. They seem to be carved out of huge blocks of " +
        "stone, immovable, and yet they are aware: some dreadful spirit of " +
        "evil vigilance abode in them. They know an enemy. Visible or " +
        "invisible none can pass unheeded. They will forbid his entry, or " +
        "his escape."));
    add_item(({"gate", "arch"}), BSN("You are standing under a dark arch " +
        "and above you, you can see the dark tower of Cirith Ungol. Mighty " +
        "watchers have their obscure way of keeping the enemy out (OR IN!)" +
        "The stones of the arch are smooth and you don't think you can " +
        "climb your way into Mordor here."));
    add_item("tower", BSN("Standing here you see the tower of Cirith Ungol " +
        "in all its might. There is a small court surrounding the tower. In " +
        "fact, you are standing in the courtyard right now. A wall shields " +
        "the courtyard from unwanted visitors. You are lucky the guards " +
        "didn't oppose too much to you getting here. The walls of the tower " +
        "are so smooth that probably a spider wouldn't be able to climb up " +
        "to the top."));
    add_item(({"wall", "walls"}), BSN("The wall surrounding the courtyard " +
        "you are in, are so smooth that a spider can't climb up to the top. " +
        "You are amazed by the skills the craftsman of the old had."));
    add_item(({"yard", "courtyard"}), BSN("You see nothing special about " +
        "the courtyard. In fact, you are glad that there aren't many orcs " +
        "roaming the place and making your life miserable."));

    add_prop(OBJ_S_WIZINFO, BSN("When a mortal travels west, his way is " +
        "blocked by an invisible field of darkness. I don't know where " +
        "mortals can find the phial from the Lady Galadriel yet, but that " +
        "is the object that mrotals need to be able to break the force of " +
        "the watchers. The phial is to be found in " + PHIAL_FILE + "."));

    add_exit(UNGOL_DIR + "", "southeast", 0, 1);
    add_exit(OTHER_PASS, "west", "@@pass_gate", 1);

    watchers_cried = 0;

    reset_room();
}

/*
 * This procedure is called each time the room needs to be updated. Here also
 * is a check for the orc guards. They will re-appear if killed before.
 */

void
reset_room()
{

}

/*
 * Init is called to make sure a player can try to climb here.
 */

void
init()
{
    ::init();

    add_action("do_climb", "climb");
}

string
describe_room()
{
    object clock;
    string time;
    string long_desc;

    clock = find_object("/d/Gondor/elessar/lib/clock");
    time = clock->query_time_of_day();

    long_desc = "You are at the Pass into Mordor, at the gate into Mordor. " +
        "Further to the west you can see the great tower. Here you can see " +
        "a great arch over the gate. Two stone watchers seem to guard the " +
        "gate into Mordor. Further to the east is the nameless land. ";

    if ((time == "evening") || (time=="night") || (time=="early morning"))
    {
        long_desc += "Massive dark clouds cover the sky, making it " +
            "difficult to distinguish night and day. The clouds seem to be " +
            "coming from the east, where Mordor lies. You suspect it is " +
            "night now, as it is as dark as it can get.";
    }
    if (time == "morning")
    {
        long_desc += "A thick cover of clouds prevent the sun from shining " +
            "here at Cirith Ungol, and it is almost as dark as at night. " +
            "However you gather that it is probably morning, as it is " +
            "getting a bit lighter than earlier.";
    }
    if (time == "noon")
    {
        long_desc += "A dark mass of clouds seems to be rolling in from " +
            "the east, covering the sky above Cirith Ungol. It is not much " +
            "lighter now than it usually is at night, but still you suspect " +
            "it is the middle of the day.";
    }
    if (time == "afternoon")
    {
        long_desc += "A thick mass of clouds cover the sky, making it " +
            "difficult to see far. You suspect that it is afternoon, as it " +
            "is getting a bit darker than earlier.";
    }

    return BSN(long_desc);
}

/*
 * This functions tests all objects in the inventory of the room and the other
 * room with the shield holds the phial.
 */

int
player_holds_phial_filter(object obj)
{
    return (obj->query_prop(PLAYER_HOLDS_PHIAL));
}

/*
 * This function return 1 if the field of darkness exists or 0 otherwise.
 * That is: if someone in the room or the adjecent room holds the phial
 * or not.
 */

int
field_of_darkness()
{
    object other_room;
    object *arr_player;

    arr_player = filter(all_inventory(TO), "player_holds_phial_filter", TO);

    other_room = find_room(OTHER_PASS);

    if (other_room)
    {
        arr_player += filter(all_inventory(other_room), "player_holds_phial_filter", TO);
    }

    if (sizeof(arr_player))
    {
        return 0;
    }

    return 1;
}

/*
 * This function is called when someone examines the field of darkness.
 */

string
exa_field()
{
    if (field_of_darkness())
    {
        return BSN("When you try to look through the arch, you cannot see " +
            "anything. You think this is because of an invisible field of " +
            "darkness. This field will prevent all mortal beings, perhaps " +
            "except orcs, from entering Mordor.");

    }
    else
    {
        return BSN("When you try to look through the arch, you cannot see " +
            "much. You think this is because of an invisible field of " +
            "darkness. This field is broken by a beam of magical white " +
            "light, piercing through it. You think you can pass the arch " +
            "now.");
    }
}

/*
 * A bell will clang when the watchers cry. This happens if a mortal enters
 * through the field of darkness.
 */

void
clang_the_bell()
{
    object other_room;
    string str;

    str = BSN("High above you a harsh bell clangs a single stroke. You think " +
        "it is a response to the cry from the watchers.");

    tell_room(TO, str);

    other_room = find_room(OTHER_PASS);

    if (objectp(other_room))
    {
        tell_room(other_room, str);
    }
}

/*
 * Reset "watchers_cried"
 */

void
remove_watchers_cried()
{
    watchers_cried = 0;
}

void
watchers_cry()
{
    object other_room;
    string str;

    if (!watchers_cried)
    {
        watchers_cried = 1;

        str = BSN("As the watchers notice that someone passes the invisible " +
            "field of darkness, you hear a high scrill cry from their evil " +
            "heads that echoes in the towering walls before you.");

        tell_room(TO, str);

        other_room = find_room(OTHER_PASS);

        if (objectp(other_room))
        {
            tell_room(other_room, str);
        }

        set_alarm(5.0, 0.0, "clang_the_bell");
        set_alarm(1.0, 0.0, "remove_watchers_cried");
    }
}

/*
 * This function tests whether a person can go west to enter Morgul
 */

int
pass_gate()
{
    string gate_desc;

    if (!field_of_darkness())
    {
        write(BSN("The field of darkness is penetrated by a beam of white " +
            "light. It is therefor possible for you to travel west."));
        LSAY("The field of darkness is penetrated by a beam of white " +
            "light. It is therefor possible for ", " to travel west.");

        set_alarm(3.0, 0.0, "watchers_cry");

        return 0;
    }

    if(TP->query_wiz_level())
    {
        write(BSN("A field of darkness prevents you from going west. Begin " +
            "a wizard though, you mumble some ancient words and a beam of " +
            "white light flashes through the field of darkness and allows " +
            "you to travel west. If you read wizinfo, you know how mortals " +
            "can follow you west. :-)"));
        LSAY("A field of darkness prevents ", " from going west. Being a " +
            "wizard though, " + PRONOUN(TP) + " mumbles some ancient words " +
            "and a beam of white light flashes throught the field of " +
            "darkness and allows " + OBJECTIVE(TP) + " to travel west.");

        set_alarm(3.0, 0.0, "watchers_cry");

        return 0;
    }

    if (TP->query_stat(SS_WIS) > 65)
    {
        gate_desc = "You know however, from old tales, that a beam of white " +
            "light will help you to pass the field.";
    }
    else
    {
        gate_desc = "You think there must be a way to pass the field, but " +
            "you can't figure out how to pass it though. Maybe you should " +
            "pay more attention when you hear old tales next time.";
    }

    write(BSN("An invisible field of darkness blocks you way to the west. " +
        "All the torches and gems you can collect won't help you to pass " +
        "the field that blocks your way. " + gate_desc));
    LSAY("An invisible field of darkness prevents ", " from going west.");

    return 1;
}

int
do_climb(string str)
{
    if (!str)
    {
        NF("What do you intend to climb here?\n");
        return 0;
    }

    if ((str == "tower") || (str == "wall") || (str == "up"))
    {
        write(BSN("Do you really think that you can climb the tower and " +
            "evade the watchers? Well... If you do, you are wrong for the " +
            "walls are so smooth that probably a spider wouldn't be able to " +
            "climb up to the top here. And I guess you don't expect " +
            LANG_ADDART(QRACENAME(TP)) + " to be able to do it if a spider " +
            "won't succeed?"));
        SAY(" in vain tries to climb up the tower. You think you should " +
            "tell " + OBJECTIVE(TP) + " the difference between " +
            LANG_ADDART(QRACENAME(TP)) + " and a spider, for " + PRONOUN(TP) +
            " thinks " + LANG_PWORD(QRACENAME(TP)) + " climb better.");

        return 1;
    }

    NF("It's a wrong assumption to think there is something to climb here.\n");
    return 0;
}
