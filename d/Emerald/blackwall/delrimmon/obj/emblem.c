/*
 *  /d/Emerald/blackwall/del_rimmon/obj/emblem.c
 *
 *  This emblem was placed in both outposts. It is very special, as it
 *  is in fact a key to open a secret compartment to reveal a part
 *  of the puzzle for finding the Tower of the Torque. It is a modified
 *  version of the standard of Telberin. The player must press the
 *  correct pattern of ovals in order to open the lock.
 *
 *  Copyright (c) December 2000, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define POS_A   1
#define POS_B   2
#define POS_C   4
#define POS_D   8
#define POS_E  16
#define POS_F  32
#define POS_G  64
#define POS_H 128

/* Global Variables */
public int     Location;  /* 0 - northern outpost, 1 - southern outpost */
public int     Pushed;

public string   A = "",
                B = "",
                C = "",
                D = "",
                E = "",
                F = "",
                G = "",
                H = "";

/*                  A
 *
 *
 *        H        ...        B      The variables A-H correspond
 *             .         .           with the following positions on
 *           .      |      .         the emblem.
 *          .       |       .
 *         .       /|\       .
 *     G   .  ----<-O->----  .   C
 *         .       \|/       .
 *          .       |       .
 *           .      |      .
 *             .         .
 *        F        ...        D
 *                              
 *                  E 
 */

/* Prototypes */
public void        create_object();
public string      hand_description();
public string      print_emblem();
public string      exa_torque(int pos, string desc);
public int         do_stuff(string arg);
public string      exa_hole();
public void        check_combo(object player);
public void        init();

public void        blank_emblem();
public void        set_location(int i = 0) { Location = i; }
public void        complete_quest(int give_it, object player, object tablet);


/*
 * Function name: switch_position
 * Description:   Flip the setting at a particular position.  If the position
 *                is currently set, it will be unset.  If it is currently
 *                unset, it will be set.
 * Arguments:     int -- the position to be switched
 */
public void
switch_position(int position)
{
    Pushed ^= position;
}


/*
 * Function name: get_position
 * Description:   Determine whether a position is set or unset.
 * Arguments:     int -- the position to check.  -1 returns all positions
 * Returns:       True if the position is set, or the settings of all
 *                positions (-1 argument).
 */
public int
get_position(int position)
{
    if (position == -1)
    {
        return Pushed;
    }

    return Pushed & position;
}

/*
 * Function name:        set_oval
 * Description  :        Determine if only one oval has been pushed,
 *                       and assign its name to the variable Which_Oval
 */
public string
query_oval_desc()
{
    switch (get_position(-1))
    {
        case POS_A:
            return "top";
        case POS_B:
            return "upper right";
        case POS_C:
            return "right";
        case POS_D:
            return "lower right";
        case POS_E:
            return "bottom";
        case POS_F:
            return "lower left";
        case POS_G:
            return "left";
        case POS_H:
            return "upper left";
        default:
            return "other";
    }

    return "";
} /* set_oval */


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("emblem");
    add_name( ({ "symbol", "symbol of telberin", "standard",
                 "standard of telberin", "emblem",
                 "emblem of telberin", "torque_quest_emblem" }) );
    add_adj( ({ "large" }) );

    set_short("emblem");
    set_long(print_emblem);

    add_item( ({ "figure", "carved figure", "tiny figure",
                 "tiny carved figure", "hand" }), hand_description);
    add_item( ({ "hole", "holes", "dark hole", "dark holes" }),
                  &exa_hole());
    add_item( ({ "center", "center of the emblem", "center oval",
                 "center shape", "center torque", "center oval shape",
                 "central oval", "central oval shape", "central torque",
                 "central shape", "central headpiece", "center necklace",
                 "center button", "central button", 
                 "middle", "middle of the emblem", "middle oval",
                 "middle shape", "middle torque", "middle oval shape",
                 "middle button" }),
        "Directly in the center of the four-pointed star which makes"
      + " up the emblem of Telberin is an oval shape resembling a"
      + " torque headpiece.\n");
    add_item( ({ "emblem of telberin", "standard of telberin",
                 "symbol of telberin" }), print_emblem);
    add_item( ({ "top oval", "top torque", "top shape", "top oval shape",
                 "upper oval", "upper torque", "upper shape",
                 "upper oval shape", "top button", "upper button" }), 
                 &exa_torque(POS_A, "directly above"));
    add_item( ({ "upper right oval", "upper right torque", 
                 "upper right shape", "upper right oval shape",
                 "upper right button", "top right oval",
                 "top right torque", "top right shape",
                 "top right oval shape", "top right button" }),
                 &exa_torque(POS_B, "to the upper right of"));
    add_item( ({ "right oval", "right torque", "right button",
                 "right shape", "right oval shape" }),
                 &exa_torque(POS_C, "directly to the right of"));
    add_item( ({ "lower right oval", "lower right torque", 
                 "lower right shape", "lower right oval shape",
                 "lower right button", "bottom right oval",
                 "bottom right torque", "bottom right shape",
                 "bottom right oval shape", "bottom right button" }),
                 &exa_torque(POS_D, "to the lower right of"));
    add_item( ({ "bottom oval", "bottom torque", "bottom button",
                 "bottom shape", "bottom oval shape",
                 "lower oval", "lower torque", "lower button",
                 "lower shape", "lower oval shape" }),
                 &exa_torque(POS_E, "directly below"));
    add_item( ({ "lower left oval", "lower left torque", 
                 "lower left shape", "lower left oval shape",
                 "lower left button", "bottom left oval",
                 "bottom left torque", "bottom left shape",
                 "bottom left oval shape", "bottom left button" }),
                 &exa_torque(POS_F, "to the lower left of"));
    add_item( ({ "left oval", "left torque", 
                 "left shape", "left oval shape"}),
                 &exa_torque(POS_G, "directly to the left of"));
    add_item( ({ "upper left oval", "upper left torque", 
                 "upper left shape", "upper left oval shape",
                 "upper left button", "top left oval",
                 "top left torque", "top left shape",
                 "top left oval shape", "top left button" }),
                 &exa_torque(POS_H, "to the upper left of"));
    add_item( ({ "star", "four-pointed star", "four pointed star",
                 "stars" }),
        "The emblem bears a four-pointed star, the traditional symbol"
      + " of the Order of Telan-Ri from the city of Telberin.\n");
    add_item( ({ "band", "circle", "circular band" }), 
        "The circular band surrounds the four-pointed star, to complete"
      + " the traditional emblem of Telberin. The ovals which surround the"
      + " emblem are rather unfamiliar, however.\n");
    add_item( ({ "ovals", "oval shapes", "shapes", "eight ovals",
                 "eight shapes", "eight oval shapes", "buttons" }),
        "The oval shapes are intricately carved, and seem to resemble"
      + " torque headpieces. They surround the emblem in a symmetrical"
      + " formation. One is also in the center of the emblem.\n");
    add_item( ({ "north shape", "north oval", "north torque",
                 "north button", "northern shape", "northern oval",
                 "northern torque", "northern button",
                 "northeast shape", "northeast oval", "northeast torque",
                 "northeast button", "northeastern shape", 
                 "northeastern oval", "northeastern torque",
                 "northeastern button",
                 "east shape", "east oval", "east torque", "east button",
                 "eastern shape", "eastern oval", "eastern torque",
                 "eastern button",
                 "southeast shape", "southeast oval", "southeast torque",
                 "southeast button", "southeastern shape",
                 "southeastern oval", "southeastern torque",
                 "southeastern button",
                 "south shape", "south oval", "south shape",
                 "south button", "southern shape", "southern oval",
                 "southern toruqe", "southern button",
                 "southwest shape", "southwest oval", "southwest torque",
                 "southwest button", "southwestern shape",
                 "southwestern oval", "southwestern torque",
                 "southwestern button",
                 "west shape", "west oval", "west torque", "west button",
                 "western shape", "western oval", "western torque",
                 "western button",
                 "northwest shape", "northwest oval", "northwest torque",
                 "northwest button",
                 "northwestern shape", "northwestern oval",
                 "northwestern torque", "northwestern button",
                 "first shape", "first oval", "first torque",
                 "first button",
                 "second shape", "second oval", "second torque",
                 "second button",
                 "third shape", "third oval", "third torque",
                 "third button",
                 "fourth shape", "fourth oval", "fourth torque",
                 "fourth button",
                 "fifth shape", "fifth oval", "fifth torque",
                 "fifth button",
                 "sixth shape", "sixth oval", "sixth torque",
                 "sixth button",
                 "seventh shape", "seventh oval", "seventh torque",
                 "seventh button",
                 "eighth shape", "eighth oval", "eighth torque",
                 "eighth button" }),
        "The shapes are arranged according to top, bottom, left, and"
      + " right. Which do you wish to examine?\n");
    add_item( ({ "torques", "torque headpieces", "headpieces",
                 "torque headpiece" }),
        "Upon closer inspection, you decide that there can be no"
      + " mistake. These oval shapes are carved to look exactly like"
      + " a torque headpiece. They surround the emblem in a"
      + " symmetrical formation. One is also in the center of the"
      + " emblem itself.\n");
    add_item( ({ "formation", "symmetrical formation" }),
        "The formation of the oval shapes is roughly circular. There"
      + " are eight individual torques: top, upper right and left,"
      + " right and left, lower right and left, and bottom. There is"
      + " also one right in the center of the emblem itself.\n");
    add_item( ({ "oval", "oval shape", "shape", "torque", "headpiece",
                 "button" }),
        "Which of them do you wish to examine? There are eight"
      + " individual torques arranged in a circular formation: top,"
      + " upper right and left, right and left, lower right and left,"
      + " and bottom. There is also one in the center of the emblem.\n");

    add_cmd_item(
              ({ "north shape", "north oval", "north torque",
                 "north button", "northern shape", "northern oval",
                 "northern torque", "northern button",
                 "northeast shape", "northeast oval", "northeast torque",
                 "northeast button", "northeastern shape", 
                 "northeastern oval", "northeastern torque",
                 "northeastern button",
                 "east shape", "east oval", "east torque", "east button",
                 "eastern shape", "eastern oval", "eastern torque",
                 "eastern button",
                 "southeast shape", "southeast oval", "southeast torque",
                 "southeast button", "southeastern shape",
                 "southeastern oval", "southeastern torque",
                 "southeastern button",
                 "south shape", "south oval", "south shape",
                 "south button", "southern shape", "southern oval",
                 "southern toruqe", "southern button",
                 "southwest shape", "southwest oval", "southwest torque",
                 "southwest button", "southwestern shape",
                 "southwestern oval", "southwestern torque",
                 "southwestern button",
                 "west shape", "west oval", "west torque", "west button",
                 "western shape", "western oval", "western torque",
                 "western button",
                 "northwest shape", "northwest oval", "northwest torque",
                 "northwest button",
                 "northwestern shape", "northwestern oval",
                 "northwestern torque", "northwestern button",
                 "first shape", "first oval", "first torque",
                 "first button",
                 "second shape", "second oval", "second torque",
                 "second button",
                 "third shape", "third oval", "third torque",
                 "third button",
                 "fourth shape", "fourth oval", "fourth torque",
                 "fourth button",
                 "fifth shape", "fifth oval", "fifth torque",
                 "fifth button",
                 "sixth shape", "sixth oval", "sixth torque",
                 "sixth button",
                 "seventh shape", "seventh oval", "seventh torque",
                 "seventh button",
                 "eighth shape", "eighth oval", "eighth torque",
                 "eighth button" }),
              ({ "push", "press", "pull", "turn" }),
        "The shapes are arranged according to top, bottom, left, and"
      + " right. Which do you wish to manipulate?\n");

    add_prop(OBJ_M_NO_GET, "The emblem cannot be taken.\n");
    set_no_show_composite(1);   /* We don't want it listed in the room */

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        hand_direction
 * Description  :        used to describe the direction which the
 *                       hand figurine is pointing
 * Returns      :        string - some text description
 */
public string
hand_description()
{
    string  txt = "Beneath the emblem, the tiny figure of a hand has"
                + " been carved into the rock. Its fingers are pointed ";

    if (Location)
    {
        txt += "downward";
    }
    else
    {
        txt += "upward";
    }

    return txt + ".\n";
} /* hand_description */


/*
 * Function name:        print_emblem
 * Description  :        show what the emblem currently looks like
 */
public string
print_emblem()
{
    string txt;

    A = (get_position(POS_A) ? "@" : "O");
    B = (get_position(POS_B) ? "@" : "O");
    C = (get_position(POS_C) ? "@" : "O");
    D = (get_position(POS_D) ? "@" : "O");
    E = (get_position(POS_E) ? "@" : "O");
    F = (get_position(POS_F) ? "@" : "O");
    G = (get_position(POS_G) ? "@" : "O");
    H = (get_position(POS_H) ? "@" : "O");

    txt =
        "The wall bears the symbol of Telberin - a four-pointed star"
      + " within a circular band. Eight oval shapes surround the"
      + " emblem. There is also one in the center of the emblem"
      + " itself.\n\n\n"
      + "                    " + A + "\n"
      + "\n"
      + "          " + H + "        ...        " + B + "\n"
      + "               .         .\n"
      + "             .      |      .\n"
      + "            .       |       .\n"
      + "           .       /|\\       .\n"
      + "       " + G + "   .  ----<-O->----  .   " + C + "\n"
      + "           .       \\|/       .\n"
      + "            .       |       .\n"
      + "             .      |      .\n"
      + "               .         .\n"
      + "          " + F + "        ...        " + D + "\n"
      + "\n"
      + "                    " + E + "\n\n\n"
      + "You notice a tiny carved figure beneath the emblem.\n";


    return txt;
} /* print_emblem */


/*
 * Function name:        exa_buttons
 * Description  :        handles the descriptions of the eight torques
 *                       and gives feedback as to whether or not they
 *                       have been pushed.
 * Returns      :        string - the description for the button
 */
public string
exa_buttons()
{
} /* exa_buttons */

/*
 * Function name:        exa_torque
 * Description  :        give a description for each torque, and whether
 *                       or not it has been pushed into the wall
 * Arguments    :        int    - which torque are we examining?
 *                       string - partial description of the torque we are
 *                                examining 
 * Returns      :        text description of the torque
 */
public string
exa_torque(int position, string desc)
{
    string  txt;

    txt = "This torque has been carved into the stone " + desc
        + " the emblem of Telberin. ";

    if (get_position(position))
    {    
        txt += "It seems to have receded into the wall, and now only"
             + " a dark hole remains in its place.";
    }

    return txt + "\n";
} /* exa_torque */


/*
 * function name:        do_stuff
 * description  :        handle attempts to push/press/pull/turn emblem
 * arguments    :        string arg -- whatever the player typed
 * returns      :        1 on success, 0 on failure
 */
public int
do_stuff(string arg)
{
    int position_selected = 0;
    string which_oval;
    string *names = ({
        "emblem",
        "band",
        "circle",
        "circular band",
        "four pointed star",
        "four-pointed star",
        "symbol",
        "headpiece",
        "headpieces",
        "oval",
        "ovals",
        "shape",
        "standard",
        "shapes",
        "star",
        "stars",
        "torque",
        "button",
        "torques",
        "buttons",
        "top oval",
        "top headpiece",
        "top shape",
        "top torque",
        "top button",
        "upper oval",
        "upper headpiece",
        "upper shape",
        "upper torque",
        "upper button",
        "upper right oval",
        "upper right headpiece",
        "upper right shape",
        "upper right torque",
        "upper right button",
        "right oval",
        "right headpiece",
        "right shape",
        "right torque",
        "right button",
        "lower right oval",
        "lower right headpiece",
        "lower right shape",
        "lower right torque",
        "lower right button",
        "lower oval",
        "lower headpiece",
        "lower shape",
        "lower torque",
        "lower button",
        "bottom oval",
        "bottom headpiece",
        "bottom shape",
        "bottom torque",
        "bottom button",
        "lower left oval",
        "lower left headpiece",
        "lower left shape",
        "lower left torque",
        "lower left button",
        "left oval",
        "left headpiece",
        "left shape",
        "left torque",
        "left button",
        "upper left oval",
        "upper left headpiece",
        "upper left shape",
        "upper left torque",
        "upper left button",
        "center headpiece",
        "center of the emblem",
        "center of the symbol",
        "center of the standard",
        "center oval",
        "center shape",
        "center torque",
        "center button",
        "central oval",
        "central shape",
        "central torque",
        "central button",
        "middle headpiece",
        "middle of the emblem",
        "middle of the symbol",
        "middle of the standard",
        "middle oval",
        "middle shape",
        "middle torque",
        "middle button",
        "wall",
        "top right oval",
        "top right headpiece",
        "top right shape",
        "top right torque",
        "top right button",
        "bottom right oval",
        "bottom right headpiece",
        "bottom right shape",
        "bottom right torque",
        "bottom right button",
        "bottom left oval",
        "bottom left headpiece",
        "bottom left shape",
        "bottom left torque",
        "bottom left button",
        "top left oval",
        "top left headpiece",
        "top left shape",
        "top left torque",
        "top left button",
        "figure",
        "carved figure",
        "tiny carved figure",
        "hand"
                    }); /* we want to be syntax friendly */

    if (!strlen(arg))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }
    arg = LOW(arg);

    if (!parse_command(arg, ({}),
        "[the] %p", names))
    {
        return 0;      /* bad arg */
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NFN0("You cannot see well enough to try that.");
    }

    if (names[0] == "shape"      || names[0] == "shapes"    ||
        names[0] == "oval"       || names[0] == "ovals"     ||
        names[0] == "torque"     || names[0] == "torques"   ||
        names[0] == "headpiece"   || names[0] == "headpieces" ||
        names[0] == "button"     || names[0] == "buttons")
    {
        write("Which of them do you wish to " + QVB + "?\n");
        return 1;
    }

    if (QVB == "pull")
    {
        WRITE("You attempt to pull the "+names[0]+", but it does not"
            + " yield any obvious finger holds.");
        return 1;
    }

    if (QVB == "turn")
    {
        WRITE("There does not seem to be any way to turn the "
            + names[0] + ".");
        return 1;
    }

    if (QVB == "push" || QVB == "press")
    {
        switch(names[0])
        {
            case "top oval":
            case "top headpiece":
            case "top shape":
            case "top torque":
            case "top button":
            case "upper oval":
            case "upper headpiece":
            case "upper shape":
            case "upper torque":
            case "upper button":
                if (!get_position(POS_A))
                {
                    position_selected = POS_A;
                }

                break;
            case "upper right oval":
            case "upper right headpiece":
            case "upper right shape":
            case "upper right torque":
            case "upper right button":
            case "top right oval":
            case "top right headpiece":
            case "top right shape":
            case "top right torque":
            case "top right button":
                if (!get_position(POS_B))
                {
                    position_selected = POS_B;
                }

                break;
            case "right oval":
            case "right headpiece":
            case "right shape":
            case "right torque":
            case "right button":
                if (!get_position(POS_C))
                {
                    position_selected = POS_C;
                }

                break;
            case "lower right oval":
            case "lower right headpiece":
            case "lower right shape":
            case "lower right torque":
            case "lower right button":
            case "bottom right oval":
            case "bottom right headpiece":
            case "bottom right shape":
            case "bottom right torque":
            case "bottom right button":
                if (!get_position(POS_D))
                {
                    position_selected = POS_D;
                }

                break;
            case "lower oval":
            case "lower headpiece":
            case "lower shape":
            case "lower torque":
            case "lower button":
            case "bottom oval":
            case "bottom headpiece":
            case "bottom shape":
            case "bottom torque":
            case "bottom button":
                if (!get_position(POS_E))
                {
                    position_selected = POS_E;
                }

                break;
            case "lower left oval":
            case "lower left headpiece":
            case "lower left shape":
            case "lower left torque":
            case "lower left button":
            case "bottom left oval":
            case "bottom left headpiece":
            case "bottom left shape":
            case "bottom left torque":
            case "bottom left button":
                if (!get_position(POS_F))
                {
                    position_selected = POS_F;
                }

                break;
            case "left oval":
            case "left headpiece":
            case "left shape":
            case "left torque":
            case "left button":
                if (!get_position(POS_G))
                {
                    position_selected = POS_G;
                }

                break;
            case "upper left oval":
            case "upper left headpiece":
            case "upper left shape":
            case "upper left torque":
            case "upper left button":
            case "top left oval":
            case "top left headpiece":
            case "top left shape":
            case "top left torque":
            case "top left button":
                if (!get_position(POS_H))
                {
                    position_selected = POS_H;
                }

                break;
            case "center headpiece":
            case "center of the emblem":
            case "center of the symbol":
            case "center of the standard":
            case "center oval":
            case "center shape":
            case "center torque":
            case "center button":
            case "central headpiece":
            case "central oval":
            case "central shape":
            case "central torque":
            case "central button":
            case "middle headpiece":
            case "middle of the emblem":
            case "middle of the symbol":
            case "middle of the standard":
            case "middle oval":
            case "middle shape":
            case "middle torque":
            case "middle button":
                if (get_position(-1) == 0)
                {
                    write("You push the " + names[0] + ", and it"
                        + " receeds slightly into the wall. As you"
                        + " remove your finger, it returns to its"
                        + " normal position. Nothing else seems to"
                        + " happen.\n");             
                     return 1;
                }

                check_combo(this_player());
                which_oval = query_oval_desc();
                if (which_oval == "other")
                {
                    write("As you push the " + names[0]
                        + ", a loud 'snap' is heard, and"
                        + " the recessed shapes pop"
                        + " back into view.\n");
                    switch_position(get_position(-1));
                    return 1;
                }


                write("As you push the " + names[0] + ", a"
                    + " loud 'snap' is heard, and the "
                    + which_oval + " shape pops back into"
                    + " view.\n");
                switch_position(get_position(-1));
                return 1;
            default:
                write("You push hard on the " + names[0] + ", but it"
                    + " does not budge.\n");
                return 1;
        } /* switch(names[0]) */


        if (position_selected)
        {
            write("You push the " + names[0] + ", and it slides"
                + " into the wall and disappears with a 'click.'\n");
            switch_position(position_selected);
        }
        else
        {
            write("The " + names[0] + " seems to have"
                + " receeded into the wall, and now only"
                + " a dark hole marks its place.\n");
        }

        return 1;
    } /* if (QVB == "push") */

    return 0; /* shouldn't ever happen */
} /* do_stuff */


/*
 * Function name:        exa_hole
 * Description  :        allow the player to examine the dark hole(s)
 * Returns      :        string - the text for the add_item
 */
public string
exa_hole()
{
    switch(get_position(-1))
    {
        case POS_A:
        case POS_B:
        case POS_C:
        case POS_D:
        case POS_E:
        case POS_F:
        case POS_G:
        case POS_H:
            return "A dark hole is all that can be seen where the "
                 + query_oval_desc() + " torque carving should be.\n";
        case 0:
            return "What?\n";
        default:
            return "Dark holes are visible in certain of the positions"
                 + " surrounding the emblem where it seems torque"
                 + " carvings belong.\n";
    }

    return ""; /* should never happen, but just to be safe */
} /* exa_hole */


/*
 * Function name:        check_combo
 * Description  :        see if the player has the right combo
 * Arguments    :        object player - the player in question
 */
public void
check_combo(object player)
{
    int     combo   = MANAGER->query_emblem_1(player);
    int     give_it = 0;
    object  tablet;

    if (Location)
    {
        combo = MANAGER->query_emblem_2(player);
        tablet = clone_object(DELRIMMON_DIR + "obj/left_fragment");

        if (!present("_del_rimmon_tablet_left", player))
        {
            give_it = 1;
        }
    }
    else
    {
        tablet = clone_object(DELRIMMON_DIR + "obj/right_fragment");

        if (!present("_del_rimmon_tablet_right", player))
        {
            give_it = 1;
        }
    }


    if (get_position(-1) == combo)
    {
        set_alarm(2.0, 0.0, &complete_quest(give_it, player, tablet));

        return;
    }

    return;
} /* check_combo */


/*
 * Function name:        complete_quest
 * Description  :        give the player some experience if they
 *                       deserve it, and create an attractie delay
 *                       for the process of the tablet delivery
 * Arguments    :        int - give_it: if the player should get a new
 *                                      tablet = 1, not = 0
 *                       object player - the player object
 *                       object tablet - the tablet object
 */
public void
complete_quest(int give_it, object player, object tablet)
{
    player->catch_tell("The four pointed star on the emblem glows suddenly"
        + " with a fierce light!\n");

    if (give_it)
    {
        player->catch_tell("A stone fragment materializes before you, and you"
            + " reach out to grab it.\n");
        if (tablet->move(player))
        {
            player->catch_tell("You are carrying so much, that you fumble the"
              + " tablet, and watch with horror as it crashes to"
              + " the ground, shattering into dust!\n");
            tablet->remove_object();
        }

        if (Location)
        {
            if (QH_QUEST_COMPLETED(player, "torque_left_fragment"))
            {
                player->catch_tell("You feel more experienced!\n");
            }
        }
        else
        {
            if (QH_QUEST_COMPLETED(player, "torque_right_fragment"))
            {
                player->catch_tell("You feel more experienced!\n");
            }
        }
    }
    else
    {
        player->catch_tell("The stone fragment glows briefly in your hands.\n");
    }

    return;
} /* complete_quest */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_stuff, "push");
    add_action(do_stuff, "pull");
    add_action(do_stuff, "turn");
    add_action(do_stuff, "press");
} /* init */


/*
 * Function name:        blank_emblem
 * Description  :        The emblem will pop back into its unmeddled
 *                       position after a time.
 */
public void
blank_emblem()
{
    if (get_position(-1) == 0)
    {
        return ;
    }

    tell_room(environment(this_object()),
        "A loud 'snap' is heard, and the recessed shapes on the emblem"
      + " pop back into view.\n");
    switch_position(get_position(-1));

    return;
} /* blank_emblem */
