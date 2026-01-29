/*
 *  /d/Gondor/morgul/tower/audience_chamber.c
 *
 *  This is a room which may be used by the Lord of the Nazgul
 *  or his minions to grant a secret audience to any who are
 *  unfortunate enough to deserve such an honour.
 *
 *  Copyright (c) September 10, 1997 by Cooper Sherry (Gorboth)
 * A Description of the words of power here follows:

There are two words of command within the morgul chamber in the
Tower of Sorcery. They are obeyed only when invoked by the rasped
voice of a Mage. They are utterances of Black Speech, which I
have been forced to manufacture based on speculation and research.

Command 'Waken Eye' - Henkoiva (Quenya), Katuohek (Black Speech)

Command 'Return Slumber' - Pelmurme (Quenya), Beshnurza (Black Speech)
*/
#pragma strict_types.h

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define  TOWER        "/d/Gondor/morgul/tower/tower_0w"
#define  LOG_FILE     "/d/Gondor/common/guild2/log/morgul_chamber"

//  Global Variables
int     Eye_Opened = 0;

//  Prototypes
void  do_log(object ob, string logtxt);

void
create_gondor()
{
    set_short("a secret alcove in the Tower of Black Sorcery");
    set_long(BSN(
        "A terrible blackness hangs heavily in this chamber, suffocating"
      + " the very presence of light with its weight. There is"
      + " nothing here to supply comfort. Smooth black stone comprises"
      + " the surface of all within, so that only the all-consuming"
      + " visage upon the eastern wall provides any variance."));

    add_item( ({"stone", "black stone", "smooth stone",
                "smooth black stone"}), BSN(
        "The stone which comprises the surfaces here is unblemished,"
      + " and does not bear the mark of any instrument of"
      + " Men or Elves."));
    add_item( ({"floor", "ground"}), BSN(
        "The floor is smooth and black as pitch. Even a very"
      + " powerful light source would have a difficult time"
      + " illuminating its surface."));
    add_item( ({"ceiling", "roof", "up"}), BSN(
        "The ceiling of this room is very low, creating a feeling"
      + " of oppression and weight upon your shoulders. It, like"
      + " the floor below, is an unmarked surface of utter blackness."));
    add_item( ({"walls", "wall"}), BSN(
        "There are four walls here. One to the north, south, east, and"
      + " west."));
    add_item( ({"north wall", "north walls", "northern wall"}), BSN(
        "The wall to the north is bleak and unadorned."));
    add_item( ({"south wall", "south walls", "southern wall"}), BSN(
        "The wall to the south is bleak and unadorned."));
    add_item( ({"west wall", "west walls", "western wall"}), BSN(
        "The wall to the west is utterly black."));
    add_item( ({"east wall", "east walls", "eastern wall", "visage"}), BSN(
        "The eastern wall has been inlaid with crudely cut rubies,"
      + " which depict the visage of a lidless red eye, burning"
      + " into you with its tireless gaze."));
    add_item( ({"ruby", "rubies"}), BSN(
        "Though harshly cut, and unbeautiful, it is obvious that"
      + " the rubies of this mosaic are very valuable indeed."));
    add_item( ({"mosaic", "mosaics", "eye", "red eye", "lidless eye",
                "lidless red eye"}), BSN(
        "The mosaic depicted on the east wall has been painstakingly"
      + " rendered with many hundreds of rubies. As you look at it,"
      + " the mosaic seems to glow dully, almost pulsing with an"
      + " energy you can feel in your skin."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -4);
}

int
eye_transfer(string str)
{
    object *others;
    string  logtxt;
    int     i;

    if ( str != "mosaic" && str != "eye" && str != "lidless eye"
      && str != "lidless red eye" && str != "red eye"
      && str != "rubies" && str != "ruby" && str != "east wall"
      && str != "eastern wall" && str != "visage")
    {
        if ( str == "wall" || str == "walls" )
        {
            write("Which wall do you wish to " + query_verb() + "?\n");
            return 1;
        }
        if ( str == "west wall" || str == "north wall" ||
             str == "south wall" || str == "western wall" ||
             str == "northern wall" || str == "southern wall")
        {
            write("You " + query_verb() + " the wall, but discover nothing"
               + " interesting about it.\n");
            return 1;
        }
        if (str == "floor" || str == "ground")
        {
            write("You " + query_verb() + " the floor, but notice nothing"
                + " unusual.\n");
            return 1;
        }

        NF0("What do you wish to " + query_verb() + "?\n");
    }

    if (TP->query_nazgul() < 1)
    {
        write(BSN("The mosaic flashes a sudden red, sending a"
          + " sudden pain up your arm!"));
        say(QCTNAME(TP) + " reaches out to touch the mosaic, and"
                        + " then instantly recoils as a sudden"
                        + " flash of red light flickers along "
                        + TP->query_possessive() + " arm.\n");

        TP->heal_hp(-20);
        if (TP->query_hp() <= 0)
        {
            TP->command("$wail");
            logtxt = " was KILLED by the eye ";
            do_log(TP, logtxt);
            TP->do_die(TO);
        }

        return 1;
    }

    tell_room(TO, "A burning flash of red light blinds you"
                + " momentarily!\n");
    others = FILTER_PLAYERS(all_inventory(TO));
    while (i < sizeof(others))
    {
        others[i]->move_living("M", TOWER, 1, 1);
        i++;
    }
    return 1;
}

void
open_eye()
{
    tell_room(TO, "With a sudden flash, the mosaic upon the eastern"
                + " wall glows a brilliant red, and fades slowly to"
                + " illuminate the room with a dull glow.\n");

    add_prop(ROOM_I_LIGHT, 1);
    Eye_Opened = 1;

    return;
}

void
close_eye()
{
    tell_room(TO, "Following a sudden pulse of brilliance, the mosaic"
                + " upon the eastern wall fades into blackness,"
                + " leaving the room in shadow.\n");

    add_prop(ROOM_I_LIGHT, -4);
    Eye_Opened = 0;

    return;
}

int
rasp_command(string str)
{
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (!IS_MORGUL_MAGE(TP))
        return 0;

    if (str != "katuohek" && str != "beshnurza")
        return 0;

    write(BSN("Feeling a sudden sense of power flowing through your"
      + " undead veins, you rasp: " + CAP(str) + "!"));
    say(QCTNAME(TP) + " stands suddenly erect, and with a low,"
      + " gutteral voice, rasps harshly, '" + CAP(str) + "!'\n");
    TP->add_mana(-30);

    if (str == "katuohek")
        if (Eye_Opened)
            tell_room(TO, "The mosaic flares up suddenly, and then"
                        + " returns to its dull red glow.\n");
        else
            open_eye();

    if (str == "beshnurza")
        if (!Eye_Opened)
            return 1;
        else
            close_eye();

    return 1;
}

void
init()
{
    ::init();

    add_action(rasp_command, "rasp");
    add_action(eye_transfer, "touch");
    add_action(eye_transfer, "feel");
    add_action(eye_transfer, "press");
    add_action(eye_transfer, "push");
    add_action(eye_transfer, "pull");
}

void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE, ob->query_name() + " ("
      + ob->query_average_stat() + ")" + logtxt + "on: "
      + ctime(time()) + ".\n");

    return;
}
