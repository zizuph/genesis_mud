/*
 * dice, or bones, that can be tossed/shaken
 * updated by Finwe, April 2004
 */

#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"

int die1 = random(5), 
    die2 = random(5);
string face;


void print_die(int cube);

void init() 
{
    add_action("roll_dice","shake");
    add_action("roll_dice","roll");
    add_action("roll_dice","toss");
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
                "|*      |\n" +
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

string dice_desc()
{

 return "This is a small set of dirty white cubes that have "+
    "some strange patterns scratched into the sides. The corners "+
    "are all rounded off, and the cubes are pretty banged up. The face of the bones show a " + die1 + " and a " + die2;
}

int roll_dice(string str)
{
    if(str == "bones" || str == "dice" || str =="cubes")
    {

        write("You cup your hands together, shake them vigorously, and throw the bones to the ground. You roll a\n\n");
/*
        say (TP + " cups " +HIS_HER(TP)+" hands together, shakes them vigorously, and throws the bones to the ground.\n");
*/
        say(CAP(HE_SHE(TP)) + " rolls a \n");
        die1 = random(5);
        if (die1 == 0) die1 = 6;
//        cube = die1;
        print_die(die1);

        write(face + "\n and a \n\n");
        say(face + "\n and a \n\n");

        die2 = random(5);
        if (die2 == 0) die2 = 6;
//        cube = die2;
        print_die(die2);
        write(face + "\n\n\n");
        say(face + "\n\n\n");
        set_long("@@dice_desc@@" + "\n");
        return 1;
    }
    else
    {
        NF("Roll what, the bones?\n");
        return 1;
    }
    return 0;

}

create_object()
{
/*
    if (die1 == 0)
        die1 = 6;

    if (die2 == 0)
        die2 = 6;
*/

  set_name("bones");
  add_name("knucklebones");
  set_adj("dirty");
  add_name("cubes");
  add_name("blocks");
  add_adj(({"white","knuckle"}));
  set_short("set of dirty white cubes");
  set_long("@@dice_desc@@" + "\n");


  add_prop(OBJ_I_VOLUME,150);
  add_prop(OBJ_I_WEIGHT,250);
  add_prop(OBJ_I_VALUE,50); 
}
