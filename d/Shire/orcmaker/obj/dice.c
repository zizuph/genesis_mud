/*
 * dice, or bones, that can be tossed/shaken
 * updated by Finwe, April 2004
 */

#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Shire/sys/defs.h"

int die1 = random(5), 
    die2 = random(5);
    
string face;


void print_die(int cube);

void init() 
{
    add_action("roll_dice","roll");
}

string dice_desc()
{
    return "This is a small set of dirty white cubes that have some " +
        "strange patterns scratched into the sides. The corners are all " +
        "rounded off from the numerous times they have been rolled during " +
        "games, leaving the cubes pretty banged up. You may <roll dice> at " +
        "anytime. The face of the cubes show a " + die1 + " and a " + 
        die2 + ".";
}

void print_die(int cube)
{
    switch(cube)
    {
        case 1:
        face =  "+-------+\n" +
                "|       |\n" +
                "|   *   |\n" +
                "|       |\n" +
                "+-------+\n";
        break;
        
        case 2:
        face =  "+-------+\n" +
                "| *     |\n" +
                "|       |\n" +
                "|     * |\n" +
                "+-------+\n";
        break;
        
        case 3:
        face =  "+-------+\n" +
                "|     * |\n" +
                "|   *   |\n" +
                "| *     |\n" +
                "+-------+\n";
        break;
        
        case 4:
        face =  "+-------+\n" +
                "| *   * |\n" +
                "|       |\n" +
                "| *   * |\n" +
                "+-------+\n";
        break;
        
        case 5:
        face =  "+-------+\n" +
                "| *   * |\n" +
                "|   *   |\n" +
                "| *   * |\n" +
                "+-------+\n";
        break;

        case 6:
        face =  "+-------+\n" +
                "| *   * |\n" +
                "| *   * |\n" +
                "| *   * |\n" +
                "+-------+\n";
        break;
        
    }       
}                 

int roll_dice(string str)
{
    int    count;
    string phrase1, phrase1a, phrase2, phrase3, phrase4;
    string roll_phrase;
    if(str == "bones" || str == "dice" || str == "blocks" ||
       str =="cubes" || str == "knucklebones")
    {

        switch(random(4))
        {
            case 0:
                phrase1  =  "You cup the bones in your hands together and shake " +
                    "them vigorously. ";
                phrase1a = QCTNAME(TP) + " cups the bones in " + HIS_HER(TP)+ 
                    " hands together and shakes them vigorously. ";
            break;

            case 1:
                phrase1  = "You take the bones and cup them in one hand, " +
                    "shaking them back and forth. ";
                phrase1a = QCTNAME(TP) + " takes the bones and cups them " +
                    "in one hand, and shakes them back and forth. ";
            break;

            case 2:
                phrase1  =  "You throw the bones up and down several times, " +
                    "catching them in your hand. ";
                phrase1a = QCTNAME(TP) + " tosses the bones up and down " +
                    "several times and catches them in " + HIS_HER(TP) + 
                    " hand. ";
            break;

            case 3:
                phrase1  = "You roll the bones around in your hand. ";
                phrase1a = QCTNAME(TP) + " rolls the bones around in " + 
                    HIS_HER(TP) + " hand. ";
            break;

            case 4:
                phrase1  = "You toss the bones back and forth from one " +
                    "hand the to the other. ";
                phrase1a = QCTNAME(TP) + " tosses the bones back and " +
                    "forth from one hand the to the other. ";
            break;
        }

        switch(random(5))
        {
            case 0:
                phrase2 = "With a wink, ";
            break;

            case 1:
                phrase2 = "Suddenly, ";
            break;

            case 2:
                phrase2 = "Unexpectedly ";
            break;

            case 3:
                phrase2 = "Grinning ";
            break;

            case 4:
                phrase2 = "Without a second thought, ";
            break;

            case 5:
                phrase2 = "For better or for worse, ";
            break;
        }

        switch(random(4))
        {
            case 0:
                phrase3 = "they are tossed to the ground. ";
            break;

            case 1:
                phrase3 = "the bones are cast to the ground. ";
            break;

            case 2:
                phrase3 = "the bones are thrown to the ground. ";
            break;

            case 3:
                phrase3 = "the bones are flung to the ground. ";
            break;

            case 4:
                phrase3 = "and a flick of the wrist, the bones fly to " +
                    "the ground. ";
            break;
        }

        switch(random(2))
        {
            case 0:
                phrase4 = "They roll around and come up:\n";
            break;
            
            case 1:
                phrase4 = "They bounce a few times and come up:\n";
            break;
            
            case 2:
                phrase4 = "They hit each other a few times and come up:\n";
            break;
        }

        write(phrase1 + phrase2 + phrase3 + phrase4 + "\n");

//        say(CAP(this_player()) + " rolls a \n");
        die1 = random(5);
        if (die1 == 0) die1 = 6;
        print_die(die1);

        write(face + "\n and a \n\n");
        say(face + "\n and a \n\n");

        die2 = random(5);
        if (die2 == 0) die2 = 6;
        print_die(die2);
        write(face + "\n\n\n");
        say(face + "\n\n\n");
        set_long("@@dice_desc@@" + "\n");
        return 1;
    }
    write("Roll what, the bones?\n");
    return 0;

}

create_object()
{
    FIXEUID;
    set_name("bones");
    add_name("knucklebones");
    add_name("dice");
    add_name("cubes");
    add_name("blocks");

    set_adj("dirty");
    add_adj(({"white","knuckle"}));
    set_short("set of dirty white cubes");
    set_long("@@dice_desc@@" + "\n");


    add_prop(OBJ_I_VOLUME,150);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VALUE,50); 
}
