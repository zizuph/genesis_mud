// OBJECT:  black beer

    /* Calia Domain

    HISTORY

    [98-02-10] Created by Uhclem from [D:\CALIA\UHCLEM\PRACTICE\BLK_BEER.DOC].

    PURPOSE

    Originally created as a New Year's Eve treat for the Calian Warriors Guild
    in December of 1997, it has been adapted for general use in a tavern
    created by Kentari of Krynn. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/drink";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_drink()

    {

    /*  DESCRIPTION  */

    set_short("black beer");
    set_name("beer");
    set_adj("black");
    add_name("stinkythick");
    add_name("stinkythick black");

    set_long("This beer isn't just dark, it's black! Even" +
        " though the label covers only a small area, you still can't" +
        " see through the bottle. A pungent and yeasty aroma" +
        " wafts - nay, erupts - from the opening, and from deep within" +
        " you can hear an occasional heavy, gelatinous 'pop!'" +
        " as unseen bubbles strain to relieve themselves of" +
        " their formidable burden of fumes.\n");

    /*  PROPERTIES  */

    set_soft_amount(540);  /*  A full pint bottle  */
    set_alco_amount(32);   /*  about 8% alcohol, a respectable beer  */
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 650);

    /* ITEMS */

    add_item(("label"),
        "  |   |              *****              |   | \n" +
        "  |   |          ****     ****          |   | \n" +
        "  |   |       ***             ***       |   | \n" +
        "  |   |     **    - genuine -    **     |   | \n" +
        "  | S |    *                       *    | B | \n" +
        "  | T |   *  S T I N K Y T H I C K  *   | R | \n" +
        "  | I |  *                           *  | E | \n" +
        "  | N |  *  XXXX  X           X      *  | W | \n" +
        "  | K |  *  X  XX X  XXX XXXX X   X  *  | I | \n" +
        "  | Y |  *  XXXX  X    X X    X  XX  *  | N | \n" +
        "  | T |  *  X  XX X XXXX X    XXXX   *  | G | \n" +
        "  | H |  *  X  XX X X  X X    X  XX  *  |   | \n" +
        "  | I |  *  XXXX  X XXXX XXXX X   X  *  | C | \n" +
        "  | C |   *                         *   | O | \n" +
        "  | K |    *    - the world's -    *    | . | \n" +
        "  |   |     **    - darkest -    **     |   | \n" +
        "  |   |       ***  - beer! -  ***       |   | \n" +
        "  |   |          ****     ****          |   | \n" +
        "  |   |              *****              |   | \n" +
        "\n" +
        "      Brewed in Lower Calia.  Much Lower.     \n");

    add_item(("opening"),
        "You can't see anything, but you think you hear some" +
        " churning inside the bottle. Is it the bubbles" +
        " bursting, or could something be actually swimming" +
        " around in there? After a few seconds of" +
        " reflection and appreciation of the beer's extraordinary" +
        " aroma, you figure that nothing inside the bottle" +
        " could possibly survive, so it must be only the" +
        " sound of bubbles that you hear.\n");

    add_item(("bottle"),
        "This must be a bottle of the legendary Stinkythick" +
        " Black, the world's darkest beer, judging from its" +
        " label and the foreboding color of its" +
        " contents. It's legendary because you've rarely met a" +
        " living soul who claimed to have drunk one, yet you" +
        " seem to recall encountering its name repeatedly." +
        " Perhaps on tombstones?\n");

    }

// FUNCTIONS

// Function:  special_effect

/*

Purpose:  adds human interest (or hobbit, gnome, dwarf, elf, goblin interest)
to the drinking experience.

Arguments:  number of beers consumed.

Returns:  nothing.

*/

void
special_effect(int num)

    {

    if(num > 1)

        {

        object tp = this_player();

        write("You may have made a strategic drinking error in" +
            " choosing to down more than one black beer at a" +
            " time. The thick, turbid brew churns and bubbles as" +
            " it works its way down your gullet, and" +
            " a sudden prolific discharge of foam fills your" +
            " nasal passages! As you involuntarily twitch" +
            " and convulse, it's all you can do to keep" +
            " from falling over. Eventually you regain" +
            " your equilibrium, but now it seems that you've" +
            " managed to discard the empty bottles without" +
            " knowing how or where.\n");

        say(QCTNAME(tp) + " gags, twitches, and nearly falls over" +
        " as black beer foam erupts from " + tp->query_possessive() +
        " nose and mouth!\n");

        }

    else

        {

        if(random(2))

            {

            write("You rapidly gulp down the black beer. You" +
                " had intended to drink it slowly and enjoy" +
                " its piquant flavor, but it quickly slides down" +
                " your throat in one slippery, gelatinous mass." +
                " It's a big, bulky swallow, and you have to strain" +
                " to get it down - then you realize that the" +
                " beer adhered to the bottle and dragged it" +
                " into your stomach as well!\n");

            }

        else

            {

            write("The heavy, rich black beer squeezes down" +
                " your gullet with all the ease of a garden" +
                " slug being mashed through a tea" +
                " strainer. It's a teeth-gritting experience to" +
                " get it all down, but get it down you do," +
                " gritting your teeth so hard that you grind up" +
                " the bottle into tiny bits and swallow it. That's" +
                " not such a bad move, though - with" +
                " the coagulated brew deposited firmly in" +
                " your stomach, you'll eventually need" +
                " the extra roughage.\n");

            }

        }

    }

// Function:  consume_text

/*

Purpose:  provides an alternative to the standard "You drink..." message.

Arguments:  arr, array of objects being drunk; vb, verb used to drink.

Returns:  nothing.

*/

void
consume_text(object *arr, string vb)

    {

    object tp = this_player();
    string po = tp->query_possessive();
    string st = COMPOSITE_DEAD(arr);

    /*  Special check for "a black beer is too much for you" condition.  A
        player holding this beer and typing "drink all" may call this
        consume_text function even when unable to drink this beer.  If a player
        calls this function but cannot drink any black beer, the emotes in the
        section are used.  If the player is holding more than one black beer
        and simply cannot drink all of them, I do not want to use the emotes in
        this section.  The wildmatch function is the easiest way to detect any
        occurrence of black beer in the list of items being drunk.  */

    if(!wildmatch("*black beer*", st))

        {

        if(sizeof(arr)>1)  /*  Player drinks a combination of beverages.  */

            {

            write("Undaunted by your inability to down the" +
                " black beer, you still manage to display a" +
                " bit of drinking bravado by downing " + st +
                " in quick succession.\n");

            say(QCTNAME(tp) + " scrutinizes some baleful black beer" +
                " for a moment, then prudently " + vb + "s " + st +
                " instead.\n");

            }

        else  /*  Player drinks 1 kind of beverage; use its consume_text.  */

            {

            arr[0]->consume_text(arr, vb);

            }

        return;

        }

    if(sizeof(arr)==1)  /*  Player drinks black beer only (any amount).  */

        {

        if(random(2))

            {

            write("You take a deep breath, close your eyes," +
                " tense your abdominal muscles, and " + vb +
                " " + st + ".\n");

            say(QCTNAME(tp) + " takes a deep breath," +
                " closes " + po + " eyes," +
                " tenses " + po + " abdominal muscles, and " + vb + "s" +
                " " + st + ".\n");

            }

        else

            {

            write("You eye the opaque liquid warily for a moment," +
                " then throw caution to the wind and " + vb +
                " " + st + ".\n");

            say(QCTNAME(tp) + " eyes the opaque liquid" +
                " warily for a moment, then throws caution to" +
                " the wind and " + vb + "s" +
                " " + st + ".\n");

            }

        }

    else  /*  Player consumes multiple kinds of beverage.  The consume_text
        function is only called in the first object in the drink list, so this
        message's appearance depends upon the position of this beer in the
        player's inventory.  */

        {

        if(random(4))

            {

            string *word1 = ({"caution", "restraint", "self-control",
                "moderation"});

            string *word2 = ({"timid", "spineless", "feeble", "weak"});

            /*  Having the player say one thing but think he's saying something
            else should lead to the occasional drunken argument.  */

            write("You sneer," +
                " '" + word1[random(sizeof(word1))] +
                " is for the " + word2[random(sizeof(word2))] + ",'" +
                " hold up your alarming combination of beverages," +
                " and " + vb + " " + st +
                ", one right after the other!\n");

            say(QCTNAME(tp) + "sneers," +
                " '" + word1[random(sizeof(word1))] +
                " is for the " + word2[random(sizeof(word2))] + ",'" +
                " holds up an alarming combination of beverages," +
                " and " + vb + "s " + st +
                ", one right after the other!\n");

            }

        else

            {

            write("You give the term 'mixed drinks' a" +
                " new and perilous significance by " + vb + "ing " + st +
                " in quick succession!\n");

            say(QCTNAME(tp) + " gives the term 'mixed drinks' a" +
                " new and perilous significance by " + vb + "ing " + st +
                " in quick succession!\n");

            }

        }

    }
