/* This is a dry roasted flea, normally found on the heads of Grunts who */
/* have been trying to think too hard. Coded 07/05/96 by Tulix III.      */

inherit "/std/food";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "/d/Emerald/tulix/t_defs.h"

#pragma strict_types

public void
create_food()
{
    set_name("flea");
    set_pname("fleas");
    set_adj(({"dry roasted", "roasted"}));
    set_short("dry roasted flea");
    set_pshort("dry roasted fleas");
    set_long("This flea is of a type only commonly found on Grunts.\n" +
        "It is considered a delicacy among goblins, and this one has " +
        "been cooked to perfection.\n" + "@@extra_desc");

    set_amount(0);  /* Fleas obviously don't contain too much protein. */

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 6); /* Looks like it will float. */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "Fleas do not sell very well.\n");

    add_prop(OBJ_S_WIZINFO, "This flea is edible. It does not actually " +
        "have a food value though, and is not useful, just fun - so no " +
        "tax is charged for it. This flea came from the head of a Grunt.\n");
}

public string
extra_desc()
{
    string race;

    race = TP->query_race_name();

    switch (race)
    {
        case "goblin":
            return "It looks really good to eat! You almost drool...\n";

        case "dwarf":
            return "Dwarves don't normally eat these fleas.\n";
        
        case "gnome":
            return "Gnomes tend to avoid eating these fleas.\n";
        
        case "hobbit":
            return "Hobbits hate the taste of these fleas.\n";
        
        case "elf":
            return "An elf wouldn't eat this, even if starving to death.\n";
        
        case "human": 
            return "Eating it would probably not be fatal. You think.\n";
    }

    return "You're not sure if you should eat it or not.\n";
}

/*
 * Function name: consume_text
 * Description:   The eat message is redefined for this morsel.
 * Arguments:     arr - Objects being consumed
 *                vb  - The verb player used to consume them
 */
public void
consume_text(object *arr, string vb)
{
    string str, race;
    
    race = TP->query_race_name();

    if (sizeof(arr) != 1)
    {
        write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + "....\n");
        say(QCTNAME(TP) + " " + vb + "s " + str + "....\n");
    }

    switch (race)
    {
        case "goblin": 
        {    
            write("You happily crunched the flea between your teeth.\n" +
                "The flea tasted absolutely delicious!\n");
            say(QCTNAME(TP) + " happily crunched the flea between " + 
                POS(TP) + " teeth.\n");
            break;
        }
        
        case "dwarf": 
        {    
            write("The flea was a bit crunchy, but was at least edible.\n");
            say(QCTNAME(TP) + " munched the flea uncertainly.\n");
            break;
        }
        
        case "gnome":
        {    
            write("You had difficulty, but finally swallowed the flea.\n");
            say(QCTNAME(TP) + " swallowed the flea with difficulty.\n");
            break;
        }
        
        case "hobbit":
        {    
            write("You ate the flea, but it was a struggle.\n");
            say(QCTNAME(TP) + " ate the flea, but it was a struggle.\n");
            break;
        }
        
        case "elf":   
        {    
            write("You ate the flea, but you now feel rather ill.\n");
            say(QCTNAME(TP) + " ate the flea, but now looks rather ill.\n");
            break;
        }
        
        case "human": 
        {    
            write("You ate the flea, but it wasn't pleasant.\n");
            say(QCTNAME(TP) + " ate the flea, but didn't enjoy it.\n");
            break;
        }
    }
}
