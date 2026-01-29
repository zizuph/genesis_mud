/* 	
 * lawn.c			Styles.   3 Mar 1993
 *
 * Modified - Varian March 2016
 */
#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

int do_pick(string str);

int apples_left = 3;
int pears_left = 3;
int peaches_left = 3;

void
create_wild_room()
{
    set_items_sparkle();
    set_herbs();

    set_short("Old garden");
    set_long("You are standing on a path in the middle of a magnificent " +
        "garden, surrounded by an immaculately maintained lawn. A wide " +
        "variety of trees, flowers and bushes have all been sculpted " +
        "and strategically placed to impress and overwhelm a visitor " +
        "with incredible variety and beauty. A small gravel path leads from " +
        "the ruins at the top of the hill just east of here, before it winds " +
        "its way through the garden, twisting and turning in a serpentine " +
        "manner so as to proudly display every inch and corner of the " +
        "garden. However, the path also seems to cut through the green " +
        "lawn away from the garden as it falls down the hill towards the " +
        "massive mountains which dominate the southern horizon.\n");

    add_trees(1);

    add_exit(THIS_DIR + "gravel","south");
    add_exit(THIS_DIR + "mansion","east");
    add_exit(THIS_DIR + "lawn1", "west", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "lawn1", "northwest", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "lawn1", "southwest", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "lawn1", "northeast", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "lawn1", "north", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "lawn1", "southeast", "@@hill@@", 1,1);

    add_item(({"garden","magnificent garden"}),
             "Filled with dozens of species of flowers and plants, this " +
             "garden is a magnificent sight to behold. Strangely enough, " +
             "despite the ruins nearby, it does appear as if the garden " +
             "is still well tended.\n");
    add_item(({"lawn","green lawn"}),
             "The lawn here is green and well manicured, having been " +
             "tended by someone who has maintained it in a clean and " +
             "tidy manner. Of course, just who that might be is a " +
             "mystery, as the mansion at the top of the hill lies in " +
             "ruins.\n");
    add_item(({"flower","flowers","plant","plants"}),
             "There are dozens of different species of plants and flowers " +
             "all carefully planted together in harmony.\n");
    add_item(({"path","gravel","gravel path","down","ground"}),
             "This gravel path cuts through the garden before winding " +
             "down the south side of the hill and towards the jagged " +
             "heights of the Grey Mountains.\n");
    add_item(({"mansion","ruins"}),
             "The collapsed ruins at the top of the hill appear to be " +
             "that of an ancient mansion. You can see more details if " +
             "you were to go east towards them.\n");
    add_item(({"hill","hillside"}),
             "This hill was once the proud home of some wealthy individual, " +
             "judging from the magnificent garden surrounding you and " +
             "the collapsed ruins of the mansion at the top of the hill.\n");
    add_item(({"trees","tree","fruit trees","fruits","fruit","fruit tree"}),
             "Several different varities of fruit trees have been " +
             "cultivated in this garden. You can see apples, peaches " +
             "and pears all growing here.\n");
    add_item(({"bush","bushes"}),
             "Several lines of bushes have been carefully tended and " +
             "scultped here in the garden.\n");
    add_item(({"horizon","southern horizon"}),
             "The jagged heights of the Grey Mountains dominate your " +
             "view across the southern horizon.\n");
    add_item(({"apples","apple","apple tree","apple trees"}),
             "There are several apple trees growing in the garden here. " +
             "The trees appear to be well tended and in excellent " +
             "condition.\n");
    add_item(({"peaches","peach","peach tree","peach trees"}),
             "There are several peach trees growing in the garden here. " +
             "The trees appear to be well tended and in excellent " +
             "condition.\n");
    add_item(({"pear","pear","pear tree","pear trees"}),
             "There are several pear trees growing in the garden here. " +
             "The trees appear to be well tended and in excellent " +
             "condition.\n");
    add_item(({"wildflower","wildflowers"}),
             "While there are no wildflowers growing on the lawn or " +
             "in this well cultivated garden, there are certainly " +
             "many of them growing in the lands around you here.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

public int
do_pick(string str)
{
    string  fruit;
    object  flower,
            peach,
            apple,
            pear;
            
    if (!strlen(str))
    {
        notify_fail("What exactly are you trying to pick here?\n");
        return 0;
    }
    
    parse_command(str, ({ }), " [in] [on] [the] [from] %s", fruit);
    
    switch(fruit)
    {
        case "flower":
        write("You bend down to pick one of the beautiful flowers from the " +
              "garden, but a strange, almost magical force prevents you " +
              "doing so.\n");
        SAYBB(" stops to pick a flower from the garden, but stops and " +
              "thinks better of it.\n");
        return 1;
            
        case "apple":
        case "apples":
        if (apples_left < 1)
        {
            write("You look around at the apple trees growing in the " +
                  "garden here, but it appears that there are no more " +
                  "apples that are ripe enough to pick.\n");
            return 1;
        }
        
        str = "apple";
        
        setuid();
        seteuid(getuid());
        
        apple = clone_object(WILD_DIR + "obj/apple");
        apple->move(this_player(), 1);
        apples_left = apples_left -1;
            break;
            
        case "peach":
        case "peaches":
        
        if (peaches_left < 1)
        {
            write("You look around at the peach trees growing in the " +
                  "garden here, but it appears that there are no more " +
                  "peachs that are ripe enough to pick.\n");
            return 1;
        }
        
        str = "peach";
        setuid();
        seteuid(getuid());
        
        peach = clone_object(WILD_DIR + "obj/peach");
        peach->move(this_player(), 1);
        peaches_left = peaches_left -1;
            break;
            
        case "pear":
        case "pears":
        
        if (pears_left < 1)
        {
            write("You look around at the pear trees growing in the " +
                  "garden here, but it appears that there are no more " +
                  "pears that are ripe enough to pick.\n");
            return 1;
        }
        
        str = "pear";
            
        setuid();
        seteuid(getuid());
       
        pear = clone_object(WILD_DIR + "obj/pear");
        pear->move(this_player(), 1);
        pears_left = pears_left -1;
            break;
            
        case "fruit":
        case "fruits":
        
        do_pick(one_of_list(({"apple","pear","peach"})));
        return 1;
            
        default:
        notify_fail("What exactly are you trying to pick here?\n");
        return 0;
    }
    
    write("You reach up and gently pluck a ripe " + fruit + " from " +
          "a nearby tree.\n");
    say(QCTNAME(TP) + " picks " + LANG_ADDART(fruit) + " from a " +
          "nearby tree.\n");
    return 1;
}
public void
init()
{
    ::init();
    add_action("do_pick","pick");
}

/*
 * Function name:        hill
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the hill in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
hill()
{
    write("The hill looks a little bit steep in that direction, you " +
        "can follow the path east to get back to the Orc Road or south " +
        "towards the mountains.\n");
    return 1;
}
/* hill */