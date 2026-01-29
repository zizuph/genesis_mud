#include <macros.h>


/* prototypes /*
public void        douse_flames(object pl);


/*
 * Function name:        douse_flames
 * Description  :        simulate the effect of submersion by
 *                       extinguishing any torches, etc carried
 *                       by the player
 * Arguments    :        object pl - the player object
 */
public void
douse_flames(object pl)
{
    int     i;
    object *inv_list = deep_inventory(pl);
    object  here     = environment(pl);

    for(i = 0; i < sizeof(inv_list); i++)
    {
        if(inv_list[i]->query_prop("_obj_i_light"))
        {
            if(function_exists("extinguish_me",inv_list[i]))
            {
                pl->catch_msg("When it touches the water, your "
                  + inv_list[i]->query_name()
                  + " goes out with a loud hiss.\n");

                inv_list[i]->extinguish_me();

                tell_room(environment(pl),
                    "A " + inv_list[i]->query_name()
                  + " goes out as it touches the water.\n", pl);
            }
            else if(function_exists(
                    "create_object",inv_list[i]) == "/std/torch")
            {
                pl->catch_msg("When it touches the water, your "
                  + inv_list[i]->query_name()
                  + " goes out with a loud hiss.\n");

                inv_list[i]->add_prop("_obj_i_light",0);

                tell_room(environment(pl),
                    "A " + inv_list[i]->query_name()
                  + " goes out as it touches the water.\n", pl);

                here->update_light();
            }
            else if (inv_list[i]->query_name() == "torch" ||
                     inv_list[i]->query_name() == "lamp")
            {
                pl->catch_msg("When it touches the water, your " 
                  + inv_list[i]->query_name()
                  + " goes out with a loud hiss.\n");

                inv_list[i]->add_prop("_obj_i_light",0);

                tell_room(environment(pl),
                    "A " + inv_list[i]->query_name() 
                  + " goes out as it touches the water.\n", pl);

                here->update_light();
            }
        }
    }
} /* douse_flames */
