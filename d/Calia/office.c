// ROOM:  domain office

    /* Calia Domain

    HISTORY

    [02-10-31] Weenware deployment dates adjusted for new 4-day scevenger hunt.

    [02-10-13] Uhclem added turtle-related weenware.

    [99-12-04] Uhclem added weenware (Halloween) code.

    [99-02-21] Uhclem removed reference to mudtime.h.

    [98-12-18] Uhclem added reset_room function and yuleware code.

    [98-09-22] Reworked into domain office [C:\CALIA\OFFICE.DOC] by Uhclem.
    Eventually this room will be moved to Gelan and the domain office replaced
    with a completely different room.

    [98-03-11] Improvements to ink stain added by Uhclem.

    [97-01-06] Created by Uhclem as Scribe's Office in Calia Palace from
    [D:\CALIA\GLYKRON\SCRIBES.DOC].

    PURPOSE

    This room provides a place where mortals can learn about the domain,
    especially by reading (and commenting on, if they so choose) the Calian
    Chronicles while the text is still being developed.

    The room has further evolved into a center where seasonal treats are
    deployed.  So far, only Christmas and Halloween items have been developed,
    but the wizards of Calia plan to celebrate many more holidays here.  Some
    will coincide with real-world holidays in date and theme; others will be
    entirely our own creations.  */

// INCLUSIONS AND DEFINITIONS

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/start/human/town/tower.h"
#include "/d/Calia/domain.h"
#include "/d/Calia/glykron/palace/rooms/light/defs.h"
#include CALIAN_HEADER

#define CHRON_PATH      (DOMAIN_DIR + "open/chronicles/")

/*  Christmas definitions  */
#define YULETREE             "/d/Calia/yuleware/yuletree"
#define PILE_OF_GIFTS        "/d/Calia/yuleware/pile"

/*  Halloween definitions  */
#define BLACK_CAT            "/d/Calia/weenware/black_cat"
#define DISPENSER            "/d/Calia/weenware/dispenser"
#define MOUSE_HOLE           "/d/Calia/weenware/mouse_hole"
#define CALIA_TURTLE_CHAT    "_calia_turtle_chat"

inherit TOWER_OFFICE;

// GLOBAL VARIABLES

object Black_Cat;  /*  Used to track the wandering Halloween cat.  */
int Smear = 0;  /*  Increases when someone sits or stands on the desk.  */
string *Who_Smeared = ({" "});  /*  Records who smeared the ink.  */
string Test_Date;  /*  Used to test the deployment-by-date functions.  */

// FUNCTIONS

// Function:  set_test_date

/*

Purpose:  set the date to test the holiday items deployed by reset_room().

Arguments:  string containing date and time in same format as displayed by the
'date' command.

Returns:  1/0.

*/

int
set_test_date(string str)

{

    if (this_player()->query_wiz_level())

    {

        write("You set the test date to: " + str + ".\n");
        Test_Date = str;
        return 1;

    }

    else

    {

        return 0;

    }

}

// Function:  reset_room

/*

Purpose:  called by system about once per hour to reset room condition.

Arguments:  none

Returns:  nothing

*/

void
reset_room()

{

    object ob;
    object room = this_object();
    object scribe = present("scribe", room);
    string *datetext = explode(ctime(time()), " ");

    if (!scribe)

    {

        scribe = clone_object(GLYKRON_MONSTERS + "scribe");
        scribe->move(room);
        tell_room(room, "A scribe arrives.\n");

    }

    if (this_player() && Test_Date)

    {

        tell_room(room,
            "\n" + QCTNAME(this_player()) + " tests" +
            " reset_room function with date '" + Test_Date + "'.\n");

        datetext = explode(Test_Date, " ");
        Test_Date = 0;

        if (sizeof(datetext) == 5)

        {

            tell_room(room,
                "Day of week = " + datetext[0] + "," +
                " month = " + datetext[1] + "," +
                " day = " + datetext[2] + "," +
                " time = " + datetext[3] + "," +
                " year = " + datetext[4] + ".\n\n");

        }

        else

        {

            tell_room(room,
                "Error in date format; reset" +
                " cancelled. Use same format as" +
                " displayed by 'date' command.\n\n");

            return;

        }

    }

    if (strlen(datetext[2]) == 1)

    {

        datetext[2] = "0" + datetext[2];

    }

    /*
     *  Halloween items are deployed starting at 23:00:01 the day before 
     *  Halloween so that they ready for the beginning of the game-wide
     *  scavenger hunt.    
     */

    if ((datetext[1] == "Oct" &&
        (datetext[2] == "31" ||
        (datetext[2] == "30" && datetext[3] > "23:00:00")))
        ||
        (datetext[1] == "Nov" && datetext[2] <= "03"))

    {

        if (!present("huge mysterious device", room))

        {

            ob = clone_object(DISPENSER);
            ob->move(room);

            tell_room(room,
                "A vast chasm sudenly opens up in the floor," +
                " and you barely manage to avoid falling into" +
                " it! From the shadowy depths a " + ob->short() +
                " rises silent as a spectre. After it has" +
                " fully emerged, the chasm seals up and" +
                " disappears without a trace.\n");

        }

        if (!present("mouse hole", room))

        {

            ob = clone_object(MOUSE_HOLE);
            ob->move(room);

            tell_room(room,
                "Sounds of gnawing come from one of the walls, and" +
                " soon a small hole forms near the floor. A" +
                " small animal sticks its head out of the hole" +
                " ever so briefly as if to see what the commotion" +
                " is in here, but it ducks back inside the hole" +
                " so quickly that you can't discern what kind" +
                " of animal it was.\n");

        }

        if (!objectp(Black_Cat))

        {

            Black_Cat = clone_object(BLACK_CAT);
            Black_Cat->move(room);

            tell_room(room,
                QCNAME(Black_Cat) + " dashes into the room," +
                " crouches down by the wall, and stares" +
                " intently into the hole.\n");

        }

        /*
         *  New asks added for Halloween:  clues about turtles on the beaches 
         *  of Calia.    
         */

        if (!scribe->query_prop(CALIA_TURTLE_CHAT))

        {

            scribe->add_ask(({"shell", "shells", "tiny shell", "tiny shells"}),
                "say Shells? What kind of shells?", 1);

            scribe->add_ask(({"tiny turtle shell", "tiny turtle shells"}),
                "say I suppose tiny turtle shells would" +
                " come from tiny turtles?", 1);

            scribe->add_ask(({"turtle shell", "turtle shells"}),
                "say I suppose you'd be most likely to find" +
                " turtle shells on turtles.", 1);

            scribe->add_ask(({"turtle", "turtles"}),
                "say Why, yes there are turtles in Calia," +
                " although they aren't given much mention" +
                " in the Chronicles.", 1);

            scribe->add_ask(({"tiny turtle", "tiny turtles"}),
                "say Turtles grow to various sizes, but all" +
                " baby turtles are tiny.", 1);

            scribe->add_ask(({"baby turtle", "baby turtles"}),
                "say What a coincidence that you should ask" +
                " about baby turtles! It just happens to be" +
                " the season when baby turtles appear on" +
                " the beaches of Calia.", 1);

            scribe->add_ask(({"season", "turtle season",
                "baby turtle season", "beaches", "beaches of Calia"}),
                "say Every year at this time, baby turtles" +
                " appear on the beaches of Calia. If you want to" +
                " see them, you should go right away - they'll" +
                " only be there for a few days!", 1);

            scribe->add_prop(CALIA_TURTLE_CHAT, 1);

        }

    }

    /*
     *  Christmas items are deployed over many days so that all players have an 
     *  opportunity to come by and enjoy them sometime during the holiday
     *  period.    
     */

    if (datetext[1] == "Dec" &&
        datetext[2] >= "25" &&
        datetext[2] <= "29" &&
        !present("pile", room))

    {

        ob = clone_object(PILE_OF_GIFTS);
        ob->move(room);

        tell_room(room, "A sleigh pulled by eight reindeer arrives" +
            " and skids to a halt. A jolly old elf jumps out," +
            " empties a huge sack of packages onto the ground," +
            " then gets back into the sleigh and drives off" +
            " in a big hurry!\n");

    }

    if (datetext[1] == "Dec" &&
        datetext[2] >= "23" &&
        datetext[2] <= "27" &&
        !present("tree", room))

    {

        ob = clone_object(YULETREE);
        ob->move(room);

        tell_room(room, "A small seedling bursts through the" +
            " ground and grows at an amazing rate in front of" +
            " you! The cloud of dust it produces settles on" +
            " the tree's limbs and transforms into ornaments," +
            " and you suddenly find yourself facing a" +
            " fully-grown " + ob->short() + ".\n");

    }

}

// Function:  read_volume

/*

Purpose:  read a volume of the Chronicles (or the crystalline plaque)

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
        "notebook 18", "eighteenth volume", "volume 18", "Volume 18",
        "plaque", "crystalline plaque", "polished crystalline plaque",
        "brilliantly polished crystalline plaque"});

    string *filenames = ({"vol_01", "vol_02", "vol_03", "vol_04", "vol_05",
        "vol_06", "vol_07", "vol_08", "vol_09", "vol_10", "vol_11", "vol_12",
        "vol_13", "vol_14", "vol_15", "vol_16", "vol_17", "vol_18", "plaque"});

    int selector = member_array(volume_name, volumes);

    if (selector == -1)

    {

        if (volume_name == "title" || volume_name == "titles")

        {

            this_player()->command("exa titles");
            return 1;

        }

        else

        {

            notify_fail("There is no notebook labelled " + volume_name +
                ".\n");

            return 0;

        }

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

    if (member_array(tp->query_name(), Who_Smeared) != -1)

    {

        write("No, you already saw that ink stain on the desk;" +
            " you're not about to try to " + query_verb() + " on it!\n");

        return 1;

    }

    write("You are just about to " + query_verb() + " on the wooden" +
        " desk when you notice that there is a large ink stain on" +
        " it which isn't quite dry! You quickly move back to" +
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
    Who_Smeared = Who_Smeared + ({tp->query_name()});
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

    /*
     *  The following array generates an emote so that all players present in 
     *  the room can see each other's impression of the ink stain.    
     */

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

    /*
     *  Elements chosen from the following arrays generate the image in the 
     *  stain as seen by each individual observer.  The number of elements is
     *  different in each of these arrays and is always a prime number.    
     */

    string *adjectives = ({"bloated", "bug-eyed", "cranky", "drunken",
        "flying", "fully-armoured", "furious", "giant", "grimy", "groggy",
        "hairless", "knock-kneed", "leprous", "long-nosed", "morose",
        "pot-bellied", "rabid", "savage", "scrawny", "three-legged",
        "two-headed", "voluptuous", "winged"});
        /*
         *  23 elements    
         */

    string *nouns = ({"human", "elf", "goblin", "hobbit", "dwarf", "gnome",
        "wizard", "hamster", "fairy", "pixie", "rabbit", "teddy bear",
        "bull moose", "sheep", "clown", "clam", "devil"});
        /*
         *  17 elements    
         */

    string *verbs = ({"seducing", "massaging", "blowing bubbles at",
        "wrestling with", "pinching the nose of", "serenading",
        "riding", "twisting the arm of", "spreading mayonnaise on",
        "carrying", "feeding cake to", "reading the palm of",
        "eating", "kicking the hindquarters of", "stalking",
        "nuzzling", "bowing before", "paddling",
        "dancing with"});
        /*
         *  19 elements    
         */

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
        /*
         *  29 elements    
         */

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
        " on all of the walls. Everything in here is quite new, and" +
        " the pleasant aroma of freshly-cut wood pervades the air." +
        " This is the office of the scribes Shimram and" +
        " Mezzlebeb, who have been entrusted with the task of" +
        " writing the history of Calia." +
        " Rows of ornate oil-lamps hang high overhead," +
        " providing plenty of illumination for the scribes to" +
        " do their work. In the middle of the room is a long" +
        " table on which many notebooks are laid out in a row," +
        " a brilliantly polished crystalline plaque dominates one wall," +
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
        tp->move_living("up", "/w/uhclem/workroom");

    }

    else

    {

        write("You grope your way to the invisible staircase" +
            " and begin to ascend, but you trip on an invisible" +
            " toy left here by some invisible child! You" +
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
    add_action(set_test_date, "testdate");

}

// ROOM DEFINITION

void
create_tower_office()

{

    /*
     *  VARIABLES    
     */

    object board;
    object scribe;

    /*
     *  DESCRIPTION    
     */

    set_short("The Calian Scribes' Office");
    set_long("@@this_room_desc@@");

    /*
     *  EXITS    
     */

    add_tower_link("tower");

    /*
     *  Note that a special exit is provided for wizards by the go_up_stairs 
    function.  I did not use a standard add_exit function so that I will not
    hear shouts from the Scribes' Office in my workroom.  */

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    /*
     *  ITEMS    
     */

    board = clone_object(CRPALACE_OBJECTS + "calian_chronicles_board");
    board->move(THIS);

    add_item(({"paneling", "birch paneling", "light birch paneling",
        "panels", "panel", "wooden panels", "wooden panel"}),
        "The panels are made of polished golden-brown wood" +
        " with a subtle grain pattern. It must not have been" +
        " long since they were cut, as they still fill the" +
        " room with the pungent aroma of birch.\n");

    add_item(({"wall", "walls"}),
        "The walls are covered with wooden panels that seem to" +
        " glow in the reflected light from the oil-lamps.\n");

    add_item(({"wood", "golden-brown wood", "grain", "pattern",
        "subtle grain", "subtle grain pattern", "grain pattern", "birch"}),
        "The grain of the birch swirls and arcs in the way" +
        " that you'd expect from fine wood. It's pleasing to the" +
        " eye, but the panels are purely decorative" +
        " and contain no hidden messages.\n");

    add_item(({"lamps", "oil-lamps", "decorative oil-lamps",
        "lamp", "oil-lamp", "decorative oil-lamp"}),
        "The lamps are all identical and are evenly spaced" +
        " along the walls. Each one is made from a tapered" +
        " cylinder of pale amber glass, narrow at the bottom and" +
        " wider at the top, and wrapped in a delicate copper" +
        " net that glistens in the glow of the steady" +
        " flame. Polished copper hardware secures the lamps" +
        " to the walls. They light the room brightly but evenly so" +
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
        " comprehension of mere mortals. Maybe" +
        " there's something more interesting and less intricate" +
        " in the room that you can examine? The desk, for" +
        " example, may be worth investigating - try asking" +
        " the scribe about it!\n");

    add_item(({"plaque", "crystalline plaque", "polished crystalline plaque",
        "brilliantly polished crystalline plaque"}),
        "The plaque emanates an inexplicable deep blue glow," +
        " obviously not a reflection from the oil-lamps. As you" +
        " try to discern what is holding it to the wall, you" +
        " discover that it isn't attached to the wall at" +
        " all, but instead floats just in front of it" +
        " with no visible support! There's an inscription" +
        " that you can read, and below it is an ornate" +
        " gold-filled engraving.\n");

    add_item(({"engraving", "gold-filled engraving",
        "ornate gold-filled engraving"}),
        "A circle of leaves and vines is intertwined with the words" +
        " 'Glykron, Gallant White Horseman of Calia' above and" +
        " 'Founder of Calia' below the figure of a mighty wizard" +
        " astride a stallion rearing up on its hind legs. The" +
        " entire engraving is composed of countless fine lines," +
        " all filled with gold that gleams even brighter than" +
        " the blue aura of the plaque.\n");

    add_item(({"desk", "wooden desk", "massive wooden desk"}),
        "It's a massive wooden desk, finely crafted to withstand" +
        " years of hard use, and it's unusually high so" +
        " that it's comfortable to work on while standing. " +
        " The desk is bare except for a large ink stain that" +
        " mars its otherwise flawless appearance, and you feel" +
        " certain that it contains nothing of interest to you.\n");

    add_item(({"stain", "ink stain", "large ink stain", "ink"}),
        "@@interpret_ink_stain@@");

    add_item(({"flame", "light", "soothing light"}),
        "The light isn't so soothing when you're staring" +
        " directly at the flame! It looks like a normal" +
        " flame you'd expect from an oil-lamp, providing" +
        " good illumination for reading and writing.\n");

    add_item(({"table", "long table", "notebooks"}),
        "The notebooks are laid out on the table in a long row. " +
        " Each has a title on the cover and is numbered" +
        " in sequence from 'Volume 1' to 'Volume 18'. From" +
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
        " Scribes of Calia. The text herein includes material" +
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
        " preserved in a safe place. The text in this notebook is" +
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
        " to read. The text will be made available when" +
        " this task is completed.'\n");

    reset_room();

}
