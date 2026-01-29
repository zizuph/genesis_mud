/* 
*  /d/Faerun/guilds/warlocks/obj/infant_meat1.c
*
*  Food item 
*
*  Nerull, 2018
*
*/

inherit "/std/food";
#include <stdproperties.h>
#include "../guild.h"

#define EAT_VERB     ("eat")   /* the common ingestion verb of food */


/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("fingers");
    add_name("infant fingers");
    add_name("heap");
    add_name("boiled fingers");
    
    set_short("heap of boiled infant fingers");
    set_pshort("heaps of boiled infant fingers");
    
    set_long("This meshy heap of boiled fingers from "
    +"humanoid infants should ease your hunger. They give "
    +"away an intricate stink though.\n");
    
    set_amount(110);
}


/*
* Function name: command_eat
* Description:   Eat this food.
* Returns:       string - an error message (failure)
*                1 - food successfully eaten.
*                0 - access failure; default error message.
*/
public mixed
command_eat()
{
    mixed err;
    int am, num, index;
    
    /* Protect against redefined eat verbs for herbs. */
    if (query_verb() != EAT_VERB)
    {
        return 0;
    }

    am = query_amount();
    num = num_heap();
    
    for (index = 0; index < num; index++)
    {
        /* See if we are too full */
        if (!this_player()->eat_food(am))
        {
            if (index == 0)
            {
                return "The " + singular_short() + " is too much for you.\n";
            }
            
            split_heap(index);
            
            this_object()->special_effect(index);
            
            return 1;
        }
    }
    
    if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        this_player()->catch_msg("You greedily devour "+short()
        +"! So..sweet!\n");
     
        this_object()->special_effect(num);
        
        //this_player()->command("lick .");
        
        return 1;
    }
 
    return "Uh, no...you are not going to eat that!\n";
}
