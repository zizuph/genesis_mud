/*
 * dice, or bones, that can be tossed/shaken
 * updated by Finwe, April 2004
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>

#include "/d/Shire/sys/defs.h"

int max_die = 20;
    
string face;

void print_die(int cube);

void init() 
{
    add_action("roll_bone","toss");
}

string dice_desc()
{
    return "This is a small white, round die carved from a large bone. It " +
        "has twenty sides with numbers scrached on each side. It looks well " +
        "used. You may <toss bone> to roll it.";
}

void print_die(int cube)
{
    switch(cube)
    {
        case 1:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 01 \\ \n"+
                    "   /______\\\n";

            break;
        case 2:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 02 \\ \n"+
                    "   /______\\\n";
            break;
        case 3:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 03 \\ \n"+
                    "   /______\\\n";
            break;
        case 4:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 04 \\ \n"+
                    "   /______\\\n";
            break;
        case 5:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 05 \\ \n"+
                    "   /______\\\n";
            break;
        case 6:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 06 \\ \n"+
                    "   /______\\\n";
            break;
        case 7:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 07 \\ \n"+
                    "   /______\\\n";
            break;
        case 8:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 08 \\ \n"+
                    "   /______\\\n";
            break;
        case 9:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 09 \\ \n"+
                    "   /______\\\n";
            break;
        case 10:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 10 \\ \n"+
                    "   /______\\\n";
            break;
        case 11:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 11 \\ \n"+
                    "   /______\\\n";
            break;
        case 12:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 12 \\ \n"+
                    "   /______\\\n";
            break;
        case 13:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 13 \\ \n"+
                    "   /______\\\n";
            break;
        case 14:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 14 \\ \n"+
                    "   /______\\\n";
            break;
        case 15:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 15 \\ \n"+
                    "   /______\\\n";
            break;
        case 16:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 16 \\ \n"+
                    "   /______\\\n";
            break;
        case 17:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 17 \\ \n"+
                    "   /______\\\n";
            break;
        case 18:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 18 \\ \n"+
                    "   /______\\\n";
            break;
        case 19:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 19 \\ \n"+
                    "   /______\\\n";
            break;
        case 20:
            face =  "      __    \n"+
                    "     /  \\  \n"+
                    "    / 20 \\ \n"+
                    "   /______\\\n";
            break;
    }       
}                 

int roll_bone(string str)
{
    int    die;
    string phrase1, phrase1a, phrase2, phrase3, phrase4;
    string roll_phrase;
    if(str == "bone" || str == "die" || str == "block" ||
       str =="cube" || str == "knucklebone" ||  str == "dice")
    {

        switch(random(5))
        {
            case 0:
                phrase1  =  "You cup the " + short() + " in your hand " +
                    "together and shake it vigorously. ";
                phrase1a = QCTNAME(TP) + " cups the " + short() + " in " + 
                    HIS_HER(TP)+ " hand and shakes it vigorously. ";
                break;

            case 1:
                phrase1  = "You take the " + short() + " in one hand, " +
                    "toss it in the air, and catch it. ";
                phrase1a = QCTNAME(TP) + " takes the " + short() + 
                    " in one hand, tosses it in the air, and catches it. ";
                break;

            case 2:
                phrase1  =  "You toss the " + short() + " up and down " +
                    "several times, catching it in your hand. ";
                phrase1a = QCTNAME(TP) + " tosses the " + short() + 
                    " up and down several times and catches it in " + 
                    HIS_HER(TP) + " hand. ";
                break;

            case 3:
                phrase1  = "You bounce the " + short() + " around in your hand. ";
                phrase1a = QCTNAME(TP) + " rolls the " + short() + 
                    " around in " + HIS_HER(TP) + " hand. ";
                break;

            case 4:
                phrase1  = "You toss the " + short() + " back and forth " +
                    "from one hand the to the other. ";
                phrase1a = QCTNAME(TP) + " tosses the " + short() + 
                    " back and forth from one hand the to the other. ";
                break;
        }

        switch(random(9))
        {
            case 0: phrase2 = "Next, ";
                    break;
            case 1:
                phrase2 = "Suddenly, ";
                    break;
            case 2:
                phrase2 = "Grinning, ";
                    break;
            case 3:
                phrase2 = "Without a second thought, ";
                    break;
            case 4:
                phrase2 = "Quickly ";
                    break;
            case 5:
                phrase2 = "Nonchalantly, ";
                    break;
            case 6:
                phrase2 = "Galantly, ";
                    break;
            case 7:
                phrase2 = "Carefully, ";
                    break;
            case 8:
                phrase2 = "Offhandedly, ";
                    break;


        }

        switch(random(5))
        {
            case 0:
                phrase3 = "it is tossed to the ground. ";
                break;

            case 1:
                phrase3 = "the " + short() + " is cast to the ground. ";
                break;

            case 2:
                phrase3 = "the " + short() + " is thrown to the ground. ";
                break;

            case 3:
                phrase3 = "the " + short() + " is flung to the ground. ";
                break;

            case 4:
                phrase3 = "and a flick of the wrist, the " + short() + 
                    " flys to the ground. ";
                break;
        }

        switch(random(3))
        {
            case 0:
                phrase4 = "It rolls around and comes up:\n";
                break;
            
            case 1:
                phrase4 = "It bounces a few times and come up:\n";
                break;
            
            case 2:
                phrase4 = "It rolls around a few times before coming up:\n";
                break;
        }

        write(phrase1 + phrase2 + phrase3 + phrase4 + "\n");
        say(phrase1a + phrase2 + phrase3 + phrase4 + "\n");

        die = random((max_die-1));
        if (die == 0) die = max_die;
        print_die(die);

        write(face + "\n");
        say(face + "\n");

        set_long("@@dice_desc@@" + "\n");
        return 1;
    }
    else
    {
        NF("Toss what, the die?\n");
        return 1;
    }
    return 0;

}

create_object()
{
    FIXEUID;    
    set_name("die");
    add_name("_shire_20_dice_");
    add_name("20 sided die");
    add_name("twenty sided die");

    set_adj("multi-sided");
    set_short("multi-sided die");
    set_long("@@dice_desc@@" + "\n");

    add_prop(OBJ_I_VOLUME,150);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VALUE,50); 
}

string
query_auto_load() { return MASTER + ":"; }

public string
query_recover() { return 0; }
