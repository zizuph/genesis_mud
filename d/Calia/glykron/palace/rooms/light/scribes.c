// ROOM:  palace scribes' office (temporary)

    /* Calia Domain

    HISTORY

    [98-03-11] Improvements to ink stain added by Uhclem.
    [97-01-06] Created by Uhclem from [C:\CALIA\GLYKRON\SCRIBES.DOC].

    PURPOSE

    This room provides a place where Guild members can read and comment on the
    Calian Chronicles while they are still in progress.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include CALIAN_HEADER

/*  Change "private" to "open" in the following statement when the chronicles
go public.  */

#define CHRON_PATH (DOMAIN_DIR + "open/chronicles/")

// GLOBAL VARIABLES

int Smear = 0;  /*  Increases when someone sits or stands on the desk.  */
string *Who_smeared = ({" "});  /*  Records who smeared the ink.  */

// FUNCTIONS

// Function:  read_volume

/*

Purpose:  read a volume of the Chronicles

Arguments:  name of the volume to be read

Returns:  1/0

*/

int
read_volume(string volume_name)

    {

    string *volumes = ({"first notebook", "first book", "book 1",
        "notebook 1", "first volume", "volume 1", "Volume 1",
        "second notebook", "second book", "book 2",
        "notebook 2", "second volume", "volume 2", "Volume 2",
        "third notebook", "third book", "book 3",
        "notebook 3", "third volume", "volume 3", "Volume 3",
        "fourth notebook", "fourth book", "book 4",
        "notebook 4", "fourth volume", "volume 4", "Volume 4",
        "fifth notebook", "fifth book", "book 5",
        "notebook 5", "fifth volume", "volume 5", "Volume 5",
        "sixth notebook", "sixth book", "book 6",
        "notebook 6", "sixth volume", "volume 6", "Volume 6",
        "seventh notebook", "seventh book", "book 7",
        "notebook 7", "seventh volume", "volume 7", "Volume 7",
        "eighth notebook", "eighth book", "book 8",
        "notebook 8", "eighth volume", "volume 8", "Volume 8",
        "ninth notebook", "ninth book", "book 9",
        "notebook 9", "ninth volume", "volume 9", "Volume 9",
        "tenth notebook", "tenth book", "book 10",
        "notebook 10", "tenth volume", "volume 10", "Volume 10",
        "eleventh notebook", "eleventh book", "book 11",
        "notebook 11", "eleventh volume", "volume 11", "Volume 11",
        "twelfth notebook", "twelfth book", "book 12",
        "notebook 12", "twelfth volume", "volume 12", "Volume 12",
        "thirteenth notebook", "thirteenth book", "book 13",
        "notebook 13", "thirteenth volume", "volume 13", "Volume 13",
        "fourteenth notebook", "fourteenth book", "book 14",
        "notebook 14", "fourteenth volume", "volume 14", "Volume 14",
        "fifteenth notebook", "fifteenth book", "book 15",
        "notebook 15", "fifteenth volume", "volume 15", "Volume 15",
        "sixteenth notebook", "sixteenth book", "book 16",
        "notebook 16", "sixteenth volume", "volume 16", "Volume 16",
        "seventeenth notebook", "seventeenth book", "book 17",
        "notebook 17", "seventeenth volume", "volume 17", "Volume 17",
        "eighteenth notebook", "eighteenth book", "book 18",
        "notebook 18", "eighteenth volume", "volume 18", "Volume 18"});

    string *filenames = ({"vol_01", "vol_02", "vol_03", "vol_04", "vol_05",
        "vol_06", "vol_07", "vol_08", "vol_09", "vol_10", "vol_11", "vol_12",
        "vol_13", "vol_14", "vol_15", "vol_16", "vol_17", "vol_18"});

    int selector = member_array(volume_name, volumes);

    if (selector == -1)

        {

        notify_fail("There is no notebook labelled " + volume_name + ".\n");
        return 0;

        }

    selector = selector / 7;

    this_player()->more(read_file(CHRON_PATH + filenames[selector] + ".txt"));
    return 1;

    }

// Function:  sit_on_desk

/*

Purpose:  sit or stand on the desk in this room and smear the ink stain.

Arguments:  string containing "desk".

Returns:  1/0

*/

int
sit_on_desk(string input_text)

    {

    string *desk_check = explode(input_text, " ");
    object tp = this_player();

    if (desk_check[sizeof(desk_check)-1] != "desk")

        {

        notify_fail(capitalize(query_verb()) + " on what?\n");
        return 0;

        }

    if (member_array(tp->query_name(), Who_smeared) != -1)

        {

        write("No, you already saw that ink stain on the desk;" +
            " you're not about to try to " + query_verb() + " on it!\n");

        return 1;

        }

    write("You are just about to " + query_verb() + " on the wooden" +
        " desk when you notice that there is a large ink stain on" +
        " it which isn't quite dry!  You quickly move back to" +
        " avoid getting ink on yourself, but it looks like you" +
        " may have spread the ink around just a bit more when" +
        " you jostled the desk.\n");

    say(QCTNAME(tp) + " is just about to " + query_verb() +
        " on the wooden desk when " + tp->query_pronoun() +
        " notices that there is an ink stain on it which" +
        " isn't quite dry, and " + tp->query_pronoun() +
        " quickly moves back to avoid getting ink" +
        " on " + tp->query_objective() + "self.\n");

    Smear = Smear + random(10) + 1;
    Who_smeared = Who_smeared + ({tp->query_name()});
    return 1;

    }

// Function:  interpret_ink_stain

/*

Purpose:  pure silliness.  Each player will see something different when he
takes a look at the ink stain on the desk.

Arguments:  none

Returns:  string containing the ink stain's appearance.

*/

string
interpret_ink_stain()

    {

    /*  The following array generates an emote so that all players present in
        the room can see each other's impression of the ink stain.  */

    string *reactions =
        ({"seems convinced that the stain on the desk looks like",
        "examines the stain on the desk and sees",
        "thinks the image in the stain on the desk resembles",
        "knows for certain that the stain on the desk depicts",
        "sees in the stain on the desk a clear image of",
        "inspects the stain on the desk and perceives a silhouette of",
        "clearly distinguishes in the stain on the desk the outline of",
        "discerns in the stain on the desk the outline of",
        "observes the stain on the desk and recognizes it as representing",
        "studies the stain on the desk and concludes that it portrays"});

    /*  Elements chosen from the following arrays generate the image in the
        stain as seen by each individual observer.  The number of elements is
        different in each of these arrays and is always a prime number.  */

    string *adjectives = ({"hairless", "scrawny", "bloated",
        "giant", "two-headed", "pot-bellied",
        "three-legged", "bug-eyed", "winged",
        "fully-armoured", "knock-kneed", "long-nosed",
        "furious", "rabid", "savage",
        "morose", "leprous", "grimy",
        "voluptuous", "groggy", "drunken",
        "flying", "cranky"});  /*  23 elements  */

    string *nouns = ({"human", "elf", "goblin", "hobbit", "dwarf", "gnome",
        "wizard", "hamster", "fairy", "pixie", "rabbit", "teddy bear",
        "bull moose", "sheep", "clown", "clam", "devil"});
         /*  17 elements  */

    string *verbs = ({"seducing", "massaging", "blowing bubbles at",
        "wrestling with", "pinching the nose of", "serenading",
        "riding", "twisting the arm of", "spreading mayonnaise on",
        "carrying", "feeding cake to", "reading the palm of",
        "eating", "kicking the hindquarters of", "stalking",
        "nuzzling", "bowing before", "paddling",
        "dancing with"});  /*  19 elements  */

    string *phrases = ({"in an ox-cart",
        "in a snowstorm", "on a piano",
        "on top of a mountain", "in a forest",
        "beside a raging river", "floating in the air",
        "under a rainbow", "on a magic carpet",
        "under an enormous umbrella", "at the edge of a volcano",
        "between some puffy clouds", "covered with thick pudding",
        "surrounded by some indistinct figures", "in front of an igloo",
        "behind a picket fence", "on a pile of fluffy pillows",
        "within a great translucent sphere", "near a swarm of bees",
        "during an earthquake", "after a mudslide",
        "under attack by termites", "buffeted by high winds",
        "just emerging from an egg", "by a nice shady tree",
        "deep in a dark pit", "besieged by enraged butterflies",
        "facing a charging bull", "about to be struck by a pie"});
        /*  29 elements  */

    string adjective1;
    string adjective2;
    string adjective3;
    string adjective4;
    string noun1;
    string noun2;
    string verb;
    string phrase1;
    string phrase2;
    int avg_stat = this_player()->query_average() + Smear;
    adjective1 = adjectives[(avg_stat % sizeof(adjectives))];
    adjectives = adjectives - ({adjective1});  /*  Prevent repeat.  */
    adjective2 = adjectives[(avg_stat % sizeof(adjectives))];
    adjectives = adjectives - ({adjective2});  /*  Prevent repeat.  */
    adjective3 = adjectives[(avg_stat % sizeof(adjectives))];
    adjectives = adjectives - ({adjective3});  /*  Prevent repeat.  */
    adjective4 = adjectives[(avg_stat % sizeof(adjectives))];
    noun1 = nouns[(avg_stat % sizeof(nouns))];
    nouns = nouns - ({noun1});  /*  Prevent repeat.  */
    noun2 = nouns[(avg_stat % sizeof(nouns))];
    verb = verbs[(avg_stat % sizeof(verbs))];
    phrase1 = phrases[(avg_stat % sizeof(phrases))];
    phrases = phrases - ({phrase1});  /*  Prevent repeat.  */
    phrase2 = phrases[(avg_stat % sizeof(phrases))];

    say(QCTNAME(this_player()) +
        " " + reactions[random(sizeof(reactions))] +
        " a " + adjective1 +
        " " + adjective2 +
        " " + noun1 +
        " " + verb +
        " a " + adjective3 +
        " " + adjective4 +
        " " + noun2 +
        " " + phrase1 +
        " " + phrase2 +
        ".\n");

    return ("The ink stain looks like" +
        " a " + adjective1 +
        " " + adjective2 +
        " " + noun1 +
        " " + verb +
        " a " + adjective3 +
        " " + adjective4 +
        " " + noun2 +
        " " + phrase1 +
        " " + phrase2 +
        ".\n");

    }

// Function:  this_room_desc

/*

Purpose:  return the long description of the room.  Wizards get to see the
invisible stairs.

Arguments:  none

Returns:  string containing room description.

*/

string
this_room_desc()

    {

    string room_desc =
        "You stand in a well-lit room with light birch paneling" +
        " on all of the walls.  Everything in here is quite new, and" +
        " the pleasant aroma of freshly-cut wood pervades the air. " +
        " Rows of ornate oil-lamps hang high overhead," +
        " providing plenty of illumination for the scribes to" +
        " do their work.  In the middle of the room is a long" +
        " table on which many notebooks are laid out in a row," +
        " and a desk occupies the corner farthest from the entrance.\n";

    if (this_player()->query_wiz_level()) room_desc = room_desc +
        "[An invisible staircase leads to a not-so-obvious exit: up.]\n";

    return room_desc;

    }

// Function:  go_up_stairs

/*

Purpose:  ascend the stairs.  Only wizards are allowed to do this.

Arguments:  none

Returns:  1

*/

int
go_up_stairs()

    {

    object tp = this_player();

    if (tp->query_wiz_level())

        {

        write("You ascend the invisible staircase.\n");
        tp->move_living("up", "/d/Calia/uhclem/workroom");

        }

    else

        {

        write("You grope your way to the invisible staircase" +
            " and begin to ascend, but you trip on an invisible" +
            " toy left here by some invisible child!  You" +
            " come crashing back down to the floor in a heap.\n");

        say(QCTNAME(tp) + " begins to mysteriously rise off the" +
            " floor, but then comes suddenly crashing back down and" +
            " lands in a heap by the desk.\n");

        }

    return 1;

    }

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    ::init();
    add_action(read_volume, "read");
    add_action(sit_on_desk, "sit");
    add_action(sit_on_desk, "stand");
    add_action(go_up_stairs, "up");

    }

// ROOM DEFINITION

void
create_room()

    {

    /*  VARIABLES  */

    object board;
    object scribe;

    /*  DESCRIPTION  */

    set_short("The Calian Scribes' Office");
    set_long("@@this_room_desc@@");

    /*  EXITS  */

    add_exit(GLYKRON_LIGHT_ROOMS + "private_library", "west", 0);

    /*  PROPERTIES  */

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    /*  ITEMS  */

    board = clone_object(CRPALACE_OBJECTS + "calian_chronicles_board");
    board->move(THIS);
    scribe = clone_object(GLYKRON_MONSTERS + "scribe");
    scribe->move(THIS);
    tell_room(THIS, "A scribe arrives.\n");

    add_item(({"paneling", "birch paneling", "light birch paneling",
        "panels", "panel", "wooden panels", "wooden panel"}),
        "The panels are made of polished golden-brown wood" +
        " with a subtle grain pattern.  It must not have been" +
        " long since they were cut, since you can still" +
        " smell their pungent birch aroma.\n");

    add_item(({"wall", "walls"}),
        "The walls are covered with wooden panels that seem to" +
        " glow in the reflected light from the oil-lamps. " +
        " There is no decoration, however; the panels are plain" +
        " except for the lamps and the bulletin board.\n");

    add_item(({"wood", "golden-brown wood", "grain", "pattern",
        "subtle grain", "subtle grain pattern", "grain pattern", "birch"}),
        "The grain of the birch swirls and arcs in the way" +
        " that you'd expect from fine wood.  It's pleasing to the" +
        " eye, but the panels are purely decorative" +
        " and contain no hidden messages.\n");

    add_item(({"lamps", "oil-lamps", "decorative oil-lamps",
        "lamp", "oil-lamp", "decorative oil-lamp"}),
        "The lamps are all identical and are evenly spaced" +
        " along the walls.  Each one is made from a tapered" +
        " cylinder of pale amber glass, narrow at the bottom and" +
        " wider at the top, and wrapped in a delicate copper" +
        " net that glistens in the glow of the steady" +
        " flame.  Polished copper hardware secures the lamps" +
        " to the walls.  They light the room brightly but evenly so" +
        " that it is comfortable to read and write here.\n");

    add_item(({"cylinder", "glass", "tapered cylinder", "amber glass",
        "cylinders", "tapered cylinders",
        "net", "copper net", "delicate copper net",
        "nets", "copper nets", "delicate copper nets"}),
        "The glass cylinders are gracefully tapered and flared, probably" +
        " a design inspired by a lily or other tall flower, and" +
        " every strand of the copper nets sparkles in the" +
        " warm, soothing light radiating from the pale amber glass.\n");

    add_item(({"hardware", "copper hardware", "polished copper hardware"}),
        "The hardware that holds the lamps to the" +
        " walls looks really complicated, well beyond the" +
        " comprehension of mere mortals.  Maybe" +
        " there's something more interesting and less intricate" +
        " in the room that you can examine?  The desk, for" +
        " example, may be worth investigating - try asking" +
        " the scribe about it!\n");

    add_item(({"desk", "wooden desk", "massive wooden desk"}),
        "It's a massive wooden desk, finely crafted to withstand" +
        " years of hard use, and it's unusually high so" +
        " that it's comfortable to work on while standing. " +
        " The desk is bare except for a large ink stain that" +
        " mars its otherwise flawless appearance, and you feel" +
        " certain that it contains nothing of interest to you.\n");

    add_item(({"stain", "ink stain", "large ink stain"}),
        "@@interpret_ink_stain@@");

    add_item(({"flame", "light", "soothing light"}),
        "The light isn't so soothing when you're staring" +
        " directly at the flame!  It looks like a normal" +
        " flame you'd expect from an oil-lamp, providing" +
        " good illumination for reading and writing.\n");

    add_item(({"table", "long table", "notebooks"}),
        "The notebooks are laid out on the table in a long row. " +
        " Each has a title on the cover and is numbered" +
        " in sequence from 'Volume 1' to 'Volume 18'.  From" +
        " where you are standing you can see all of the titles.\n");

    add_item(({"title", "titles"}),
        "\n" +
        "  Volume 1: Calian Geography\n" +
        "  Volume 2: Calian Flora and Fauna\n" +
        "  Volume 3: Early History\n" +
        "  Volume 4: The Dim Time\n" +
        "  Volume 5: The Struggle for Dominance\n" +
        "  Volume 6: Caliana\n" +
        "  Volume 7: The Passage\n" +
        "  Volume 8: Gelan\n" +
        "  Volume 9: Kroug\n" +
        " Volume 10: Mount Kyrus\n" +
        " Volume 11: The Foundation of the Calian Warrior Guild\n" +
        " Volume 12: Annals of the Guild, Part I\n" +
        " Volume 13: Annals of the Guild, Part II\n" +
        " Volume 14: The Confederation\n" +
        " Volume 15: War Legend of Calia\n" +
        " Volume 16: Modern Times\n" +
        " Volume 17: Partings and Promises\n" +
        " Volume 18: Apotheosis\n" +
        "\n");

    add_item(({"book", "notebook", "volume"}),
        "The notebooks are labelled 'Volume 1' to 'Volume 18' -" +
        " which one did you want to look at?\n");

    add_item(({"first notebook", "first book", "book 1", "Book 1",
        "volume 1", "Volume 1"}),
        "The notebook is labelled 'Volume 1: Calian Geography'" +
        " and in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"second notebook", "second book", "book 2", "Book 2",
        "volume 2", "Volume 2"}),
        "The notebook is labelled 'Volume 2: Calian Flora and" +
        " Fauna' and in smaller letters below the title you" +
        " see the words 'compiled by Shimram and" +
        " Mezzlebeb, Scribes of Calia.'\n");

    add_item(({"third notebook", "third book", "book 3", "Book 3",
        "volume 3", "Volume 3"}),
        "The notebook is labelled 'Volume 3: Early History'" +
        " and in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"fourth notebook", "fourth book", "book 4", "Book 4",
        "volume 4", "Volume 4"}),
        "The notebook is labelled 'Volume 4: The Dim Time'" +
        " and in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"fifth notebook", "fifth book", "book 5", "Book 5",
        "volume 5", "Volume 5"}),
        "The notebook is labelled 'Volume 5: The Struggle for" +
        " Dominance' and in smaller letters below the title you" +
        " see the words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.  The text herein includes material" +
        " taken from the writings of scribes employed by" +
        " both friends and enemies of the Guild.'\n");

    add_item(({"sixth notebook", "sixth book", "book 6", "Book 6",
        "volume 6", "Volume 6"}),
        "The notebook is labelled 'Volume 6: Caliana' and" +
        " in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"seventh notebook", "seventh book", "book 7", "Book 7",
        "volume 7", "Volume 7"}),
        "The notebook is labelled 'Volume 7: The Passage'" +
        " and in smaller letters below the title you see the" +
        " words 'The original journal kept by Caliana is being" +
        " preserved in a safe place.  The text in this notebook is" +
        " a summary of the main events recorded in that journal.'\n");

    add_item(({"eighth notebook", "eighth book", "book 8", "Book 8",
        "volume 8", "Volume 8"}),
        "The notebook is labelled 'Volume 8: Gelan' and" +
        " in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb, Scribes of" +
        " Calia, with the assistance of Raspatoon of Gelan.'\n");

    add_item(({"ninth notebook", "ninth book", "book 9", "Book 9",
        "volume 9", "Volume 9"}),
        "The notebook is labelled 'Volume 9: Kroug' and" +
        " in smaller letters below the title you see the" +
        " words 'transcribed by Shimram and Mezzlebeb, Scribes" +
        " of Calia, from texts captured from Kroug's army.'\n");

    add_item(({"tenth notebook", "tenth book", "book 10", "Book 10",
        "volume 10", "Volume 10"}),
        "The notebook is labelled 'Volume 10: Mount Kyrus'" +
        " and in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"eleventh notebook", "eleventh book", "book 11",
        "Book 11", "volume 11", "Volume 11"}),
        "The notebook is labelled 'Volume 11: The Foundation" +
        " of the Calian Warrior Guild' and in smaller letters" +
        " below the title you see the words 'Shimram and" +
        " Mezzlebeb, Scribes of Calia, regret to inform you" +
        " that the original parchment on which Caliana wrote" +
        " her address was damaged during the Great Battle. " +
        " Until it is restored, the text is unavailable.'\n");

    add_item(({"twelfth notebook", "twelfth book", "book 12",
        "Book 12", "volume 12", "Volume 12"}),
        "The notebook is labelled 'Volume 12: Annals of the Guild," +
        " Part I' and in smaller letters below the title you" +
        " see the words 'compiled by Shimram and" +
        " Mezzlebeb, Scribes of Calia.'\n");

    add_item(({"thirteenth notebook", "thirteenth book", "book 13",
        "Book 13", "volume 13", "Volume 13"}),
        "The notebook is labelled 'Volume 13: Annals of the Guild," +
        " Part II' and in smaller letters below the title you" +
        " see the words 'compiled by Shimram and" +
        " Mezzlebeb, Scribes of Calia.'\n");

    add_item(({"fourteenth notebook", "fourteenth book", "book 14",
        "Book 14", "volume 14", "Volume 14"}),
        "The notebook is labelled 'Volume 14: The Confederation'" +
        " and in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"fifteenth notebook", "fifteenth book", "book 15",
        "Book 15", "volume 15", "Volume 15"}),
        "The notebook is labelled 'Volume 15: War Legend of" +
        " Calia' and in smaller letters below the title you" +
        " see the words 'compiled by Shimram and" +
        " Mezzlebeb, Scribes of Calia.'\n");

    add_item(({"sixteenth notebook", "sixteenth book", "book 16",
        "Book 16", "volume 16", "Volume 16"}),
        "The notebook is labelled 'Volume 16: Modern Times'" +
        " and in smaller letters below the title you see the" +
        " words 'compiled by Shimram and Mezzlebeb," +
        " Scribes of Calia.'\n");

    add_item(({"seventeenth notebook", "seventeenth book", "book 17",
        "Book 17", "volume 17", "Volume 17"}),
        "The notebook is labelled 'Volume 17: Partings and" +
        " Promises' and in smaller letters below the title you" +
        " see the words 'compiled by Shimram and" +
        " Mezzlebeb, Scribes of Calia.'\n");

    add_item(({"eighteenth notebook", "eighteenth book", "book 18",
        "Book 18", "volume 18", "Volume 18"}),
        "The notebook is labelled 'Volume 18: Apotheosis'" +
        " and in smaller letters below the title you see the" +
        " words 'Shimram and Mezzlebeb, Scribes of Calia," +
        " are currently working to transcribe the document" +
        " left by Caliana, which is a bit smudged and difficult" +
        " to read.  The text will be made available when" +
        " this task is completed.'\n");

    }
