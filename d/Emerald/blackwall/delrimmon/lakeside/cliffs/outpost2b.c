/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/outpost2b.c
 *
 *  This chamber was once used to house the weapons and equipment for
 *  the soldiers stationed at the southern outpost of Del Rimmon. It has
 *  long since been abandoned, but a few old relics have been left
 *  behind.
 *
 *  Copyright (c) March 2001, by Cooper Sherry (Gorboth)
 *
 *  2017-10-27 Malus: Modifed *names so "next entry" would work 
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define READING_PROP    ("_del_rimmon_reading_outpost_log")

/* prototypes */
public void        create_del_rimmon();
public void        reset_room();
public int         read_book(string arg);
public void        init();
public string      read_entry(int entry);


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("a wide rectangular chamber, filled with dust");
    set_long("A wide rectangular chamber extends to the east and"
           + " west here. Dust covers everything in this room, giving"
           + " reason to believe that very few things have entered"
           + " here for many many years. The walls to"
           + " the north and south are lined with empty weapon and"
           + " armour racks. A passageway leads away to the west, and"
           + " at the far eastern end of the chamber, a wooden desk"
           + " rests beneath an emblem of some kind which has been"
           + " carved into the wall.\n");

    add_item( ({ "surface", "surface of the desk", "top of the desk",
                 "desk surface" }),
        "The surface of the desk is almost completely covered by a"
      + " book whose covers lie spread open.\n");
    add_item( ({ "finger", "fingers", "fingers of the hand",
                 "fingers on the figure of the hand" }),
        "The fingers on the figure of the hand are pointing down.\n");
    add_item( ({ "cover", "covers", "cover of the book",
                 "covers of the book", "book cover", "book covers" }),
        "The covers of the book lie open on the surface of the desk,"
      + " where they appear to be stuck in the resin which has seeped"
      + " to the surface.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is carved from the same stone as the walls. It,"
      + " however, is covered with a thick layer of dust.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The roof of this chamber is fairly low, and appears to be"
      + " carved of the same stone as the rest of the chamber.\n");
    add_item( ({ "peak", "melan rath" }),
        "You are within Melan Rath, but get no sense of viewing it"
      + " from here.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from inside this chamber.\n");
    add_item( ({ "here", "area", "chamber", "room", "wide chamber",
                 "rectangular chamber", "wide rectangular chamber" }),
        "From the racks which line the north and south walls, it"
      + " seems clear that at one time this room was used to house"
      + " armaments. Now it is filled with dust, and does not appear"
      + " to have been visited for hundreds of years.\n");
    add_item( ({ "dust", "layer", "layer of dust", "thick layer",
                 "thick layer of dust" }),
        "A thick layer of dust covers nearly every surface in this"
      + " room. It seems clear that no one has been here for a very"
      + " long time.\n");
    add_item( ({ "walls", "stone walls", "rock walls" }),
        "The walls of this chamber seem to have been hewn from the"
      + " rock of the peak. Cracks run along them, as if some"
      + " sort of earthquake may have shifted the stone since"
      + " their building. The north and south walls are lined with"
      + " empty racks. The wall to the east is carved with an"
      + " emblem of some kind, which is directly above a wooden"
      + " desk. The western wall houses a passageway which leads"
      + " out of the room in that direction.\n");
    add_item( ({ "crack", "cracks" }),
        "The cracks suggest that perhaps in the not too distant"
      + " past, a massive earthquake rocked this region.\n");
    add_item( ({ "rack", "racks", "weapon rack", "weapon racks",
                 "armour rack", "armour racks" }),
        "Racks line the walls to the north and south, and appear"
      + " to have once housed weapons and armour. Metal pegs and"
      + " hooks now lie empty where many items perhaps once were"
      + " held in place. They are covered with dust.\n");
    add_item( ({ "peg", "hook", "pegs", "hooks", "metal peg",
                 "metal pegs", "metal hook", "metal hooks" }),
        "Perhaps they once held sturdy armour and weaponry in"
      + " place. Now, they stand empty and forgotten.\n");
    add_item( ({ "stone", "rock" }),
        "The rock has been cleanly hewn, though there are cracks"
      + " running along many places in the stone.\n");
    add_item( ({ "north wall", "north", "northern wall" }),
        "The northern wall is lined with what appear to be weapon"
      + " racks. Long forgotten, they now hold only dust.\n");
    add_item( ({ "south wall", "south", "southern wall" }),
        "The southern wall is lined with what appear to be armour"
      + " racks. They have not held anything but dust, it seems, for"
      + " many long forgotten years.\n");
    add_item( ({ "west", "west wall", "western wall" }),
        "A passageway leads out of this chamber through the western"
      + " wall.\n");
    add_item( ({ "corridor", "exit", "passage", "passageway",
                 "tunnel" }),
        "The corridor runs west out of this chamber into what appears"
      + " to be a much larger, circular chamber.\n");
    add_item( ({ "larger chamber", "circular chamber" }),
        "From here, you can't see much detail.\n");
    add_item( ({ "east", "east wall", "eastern wall" }),
        "A wooden desk rests at the foot of the eastern wall beneath"
      + " a large emblem which has been carved in the stone there.\n");
    add_item( ({ "desk", "wood desk", "wooden desk" }),
        "The desk is made of wood, and is of plain simple construction."
      + " It seems obvious that little care went into the beauty of"
      + " its making, but it looks quite servicable, and adequate for"
      + " such purposes as it was intended. A large book lies open on"
      + " its surface.\n");
    add_item( ({ "wood", "resin" }),
        "Over the years, the resin from the wood seems to have seeped"
      + " out, and affixed to the covers of the open book.\n");
    add_item( ({ "book", "large book", "log", "open book" }),
        "The book is very large, and covers most of the surface of"
      + " the desk. Its covers lie open against the wood, revealing"
      + " pages which look to be hand-written.\n");
    add_item( ({ "page", "pages" }),
        "The pages are mostly filled with writing which seems to have"
      + " been done by hand. The last half of the book is blank.\n");
    add_item( ({ "writing", "hand writing", "hand-writing", "ink",
                 "handwriting" }),
        "The writing is in ink, and appears to have been written"
      + " by a single author. This book appears to be some kind of"
      + " log, with many entries made over time.\n");

    add_cmd_item( ({ "book", "log" }),
                  ({ "get", "take", "move", "close", "pry" }),
        "The resin from the wood along the surface of the desk seems"
      + " to have melded with the covers of the book over many many"
      + " years. It is fixed in place.\n");
    add_cmd_item( ({ "page", "pages" }),
                  ({ "turn", "flip" }),
        "You flip through the pages of the book. They are filled with"
      + " handwriting in ink, and only fill the first half of the"
      + " book. The back half of the book is blank.\n");
    add_cmd_item( ({ "book", "log" }),
                  ({ "open" }),
        "The book is already laid open.\n");
    add_cmd_item( ({ "blank page", "blank pages" }),
                  ({ "read", "examine", "exa" }),
        "Apparently, whoever was keeping this log did not make enough"
      + " entries to fill the whole book.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost2a", "west");

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        reset_room
 * Description  :        clone the emblem into the room
 */
public void
reset_room()
{
    object  emblem;

    if (emblem = present("torque_quest_emblem"))
    {
        emblem->blank_emblem();
    }
    else
    {
        emblem = clone_object(DELRIMMON_DIR + "obj/emblem");
        emblem->set_location(1);
        emblem->move(this_object());
    }
} /* reset_room */


/*
 * Function name:        read_book
 * Description  :        allow the player to read various things in
 *                       the book.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
read_book(string arg)
{
    int     current = 0;
    string  txt;
    string *names = ({
        "next entry",
        "next",
        "first entry",
        "1st entry",
        "entry 1",
        "entry one",
        "entry number one",
        "second entry",
        "2nd entry",
        "entry two",
        "entry number two",
        "entry 2",
        "third entry",
        "3rd entry",
        "entry three",
        "entry number three",
        "entry 3",
        "fourth entry",
        "4th entry",
        "entry four",
        "entry number four",
        "entry 4",
        "fifth entry",
        "5th entry",
        "entry five",
        "entry number five",
        "entry 5",
        "sixth entry",
        "6th entry",
        "entry six",
        "entry number six",
        "entry 6",
        "seventh entry",
        "7th entry",
        "entry seven",
        "entry number seven",
        "entry 7",
        "eighth entry",
        "8th entry",
        "entry eight",
        "entry number eight",
        "entry 8",
        "ninth entry",
        "9th entry",
        "entry nine",
        "entry number nine",
        "entry 9",
        "tenth entry",
        "10th entry",
        "entry ten",
        "entry number ten",
        "entry 10",
        "eleventh entry",
        "11th entry",
        "entry eleven",
        "entry number eleven",
        "entry 11",
        "twelfth entry",
        "12th entry",
        "entry twelve",
        "entry number twelve",
        "entry 12",
        "thirteenth entry",
        "13th entry",
        "entry thirteen",
        "entry number thirteen",
        "entry 13",
        "fourteenth entry",
        "14th entry",
        "entry fourteen",
        "entry number fourteen",
        "entry 14",
        "fifteenth entry",
        "15th entry",
        "entry fifteen",
        "entry number fifteen",
        "entry 15",
        "sixteenth entry",
        "16th entry",
        "entry sixteen",
        "entry number sixteen",
        "entry 16",
        "seventeenth entry",
        "17th entry",
        "entry seventeen",
        "entry number seventeen",
        "entry 17",
        "eighteenth entry",
        "18th entry",
        "entry eighteen",
        "entry number eighteen",
        "entry 18",
        "nineteenth entry",
        "ninteenth entry",
        "19th entry",
        "entry ninteen",
        "entry number ninteen",
        "entry 19",
        "twentieth entry",
        "20th entry",
        "entry twenty",
        "entry number twenty",
        "entry 20",
        "twenty first entry",
        "twenty-first entry",
        "21st entry",
        "entry twenty one",
        "entry twenty-one",
        "entry number twenty one",
        "entry number twenty-one",
        "entry 21",
        "twenty second entry",
        "twenty-second entry",
        "22nd entry",
        "entry twenty two",
        "entry twenty-two",
        "entry number twenty two",
        "entry number twenty-two",
        "entry 22"
    });
    if (!strlen(arg))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }

    if (this_player()->query_prop(READING_PROP))
    {
        current = this_player()->query_prop(READING_PROP) + 1;
    }
    if (!parse_command(arg, ({}),
        "[at] [the] %p", names))
    {
        if (!parse_command(arg, ({}),
            "[at] [the] [open] 'book' / 'log' / 'page' / 'pages'"))
        {
            if (arg == "entry" ||
                arg == "entries" ||
                arg == "many entries" ||
                arg == "at entries" ||
                arg == "at many entries" ||
                arg == "at entry")
            {
                write("You flip through the book, and count twenty-two"
                    + " separate entries. They fill the first half of"
                    + " the book. Which entry do you wish to read?\n");

                return 1;
            }

            return 0; /* can't process player's syntax choice */
        }

        if (QVB == "exa" ||
            QVB == "examine" ||
            QVB == "look")
        {
            return 0; /* let the add_item process this */
        }

        write("You glance through the book, and decide that it"
            + " is probably a log of some kind. There are many entries"
            + " which seem to have been made over a long period of"
            + " time, mostly in the same handwriting.\n");

        return 1;
    }

    switch(names[0])
    {
        case "first entry":
        case "1st entry":
        case "entry one":
        case "entry number one":
        case "entry 1":
            txt = read_entry(current = 1);
            break;
        case "second entry":
        case "2nd entry":
        case "entry two":
        case "entry number two":
        case "entry 2":
            txt = read_entry(current = 2);
            break;
        case "third entry":
        case "3rd entry":
        case "entry three":
        case "entry number three":
        case "entry 3":
            txt = read_entry(current = 3);
            break;
        case "fourth entry":
        case "4th entry":
        case "entry four":
        case "entry number four":
        case "entry 4":
            txt = read_entry(current = 4);
            break;
        case "fifth entry":
        case "5th entry":
        case "entry five":
        case "entry number five":
        case "entry 5":
            txt = read_entry(current = 5);
            break;
        case "sixth entry":
        case "6th entry":
        case "entry six":
        case "entry number six":
        case "entry 6":
            txt = read_entry(current = 6);
            MANAGER->set_read_log(this_player(), "Yes");
            break;
        case "seventh entry":
        case "7th entry":
        case "entry seven":
        case "entry number seven":
        case "entry 7":
            txt = read_entry(current = 7);
            break;
        case "eighth entry":
        case "8th entry":
        case "entry eight":
        case "entry number eight":
        case "entry 8":
            txt = read_entry(current = 8);
            break;
        case "ninth entry":
        case "9th entry":
        case "entry nine":
        case "entry number nine":
        case "entry 9":
            txt = read_entry(current = 9);
            break;
        case "tenth entry":
        case "10th entry":
        case "entry ten":
        case "entry number ten":
        case "entry 10":
            txt = read_entry(current = 10);
            break;
        case "eleventh entry":
        case "11th entry":
        case "entry eleven":
        case "entry number eleven":
        case "entry 11":
            txt = read_entry(current = 11);
            break;
        case "twelfth entry":
        case "12th entry":
        case "entry twelve":
        case "entry number twelve":
            txt = read_entry(current = 12);
            break;
        case "thirteenth entry":
        case "13th entry":
        case "entry thirteen":
        case "entry number thirteen":
        case "entry 13":
            txt = read_entry(current = 13);
            break;
        case "fourteenth entry":
        case "14th entry":
        case "entry fourteen":
        case "entry number fourteen":
        case "entry 14":
            txt = read_entry(current = 14);
            break;
        case "fifteenth entry":
        case "15th entry":
        case "entry fifteen":
        case "entry number fifteen":
        case "entry 15":
            txt = read_entry(current = 15);
            break;
        case "sixteenth entry":
        case "16th entry":
        case "entry sixteen":
        case "entry number sixteen":
        case "entry 16":
            txt = read_entry(current = 16);
            break;
        case "seventeenth entry":
        case "17th entry":
        case "entry seventeen":
        case "entry number seventeen":
        case "entry 17":
            txt = read_entry(current = 17);
            break;
        case "eighteenth entry":
        case "18th entry":
        case "entry eighteen":
        case "entry number eighteen":
        case "entry 18":
            txt = read_entry(current = 18);
            break;
        case "ninteenth entry":
        case "19th entry":
        case "entry ninteen":
        case "entry number ninteen":
        case "entry 19":
            txt = read_entry(current = 19);
            break;
        case "twentieth entry":
        case "20th entry":
        case "entry twenty":
        case "entry number twenty":
        case "entry 20":
            txt = read_entry(current = 20);
            break;
        case "twenty first entry":
        case "twenty-first entry":
        case "21st entry":
        case "entry twenty one":
        case "entry twenty-one":
        case "entry number twenty one":
        case "entry number twenty-one":
        case "entry 21":
            txt = read_entry(current = 21);
            break;
        case "twenty second entry":
        case "twenty-second entry":
        case "22nd entry":
        case "entry twenty two":
        case "entry twenty-two":
        case "entry number twenty two":
        case "entry number twenty-two":
        case "entry 22":
            txt = read_entry(current = 22);
            break;
        case "next":
        case "next entry":
        default:
            if (!this_player()->query_prop(READING_PROP))
            {
                write("You'll have to start somewhere first.\n");
                return 1;
            }

            if (this_player()->query_prop(READING_PROP) >= 22)
            {
                write("It seems you have already read the final"
                    + " entry.\n");
                return 1;
            }

            txt = read_entry(this_player()->query_prop(READING_PROP)+1);
            break;
    }

    write(txt + "\n");
    this_player()->add_prop(READING_PROP, current);

    return 1;
} /* read_book */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(read_book, "read");
    add_action(read_book, "exa");
    add_action(read_book, "examine");
    add_action(read_book, "look");
} /* init */


/*
 * Function name:        read_entry
 * Description  :        prints the text of a given entry
 * Arguments    :        int entry -- the entry we want to read
 * Returns      :        string - the entry text
 */
public string
read_entry(int entry)
{
    string etxt = read_file(DELRIMMON_DIR
                + "text/outpost/entry_" + entry + ".txt", 0);

    write("The " + LANG_WORD(entry) + " entry in the book reads"
        + " as follows:\n\n");

    return etxt;
} /* read_entry */
