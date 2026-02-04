// Lilith Dec 2021: added fishing prop.

/*
    Modified: 4 May 2003, by Bleys
        - expanded from the "drink pool" add_cmd_item to
            an add_action that accepts a few arguments to
            the drink command.
        - changed the water_animal() routine so that it
            no longer accepts any object as a target (i.e.
            "You lead your crimson steel longsword to the
            pool and water it."
        - The pool desc mentioned a thin sheet of ice,
            which seemed incompatible with drinking from
            the pool. This is now handled a little better.

    Modified: 15 May 2003, by Bleys
        - My 4 May alteration incorrectly used the %l argument to
            parse_command(), which returns an array of livings
            rather than a single living. I changed it back to
            using %o and added a check for LIVE_I_IS in order
            to filter out stuff like watering your sword. It
            might be better in the future to use %l in case
            a mortal tries "water horses."
        - water_animal() makes some more sensible checks. It is
            no longer possible to water any living - it has to
            be either a steed led by this_player or a creature
            in this_player's inventory. It also checks for a
            minimum of animal handling to be effective.


    TODO:
        - Perhaps convert water_player() to use parse_command()
        - extract water_animal and water_player to Terel's standard
            room... perhaps interactible with terrain types? At any
            rate, the original version of this is repeated multiple
            places, which is none too efficient.

*/


#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <stdproperties.h>
#include <ss_types.h>

// Prototypes.
int drink();
int water_animal(string arg);
int water_player(string arg);
string pool_ice_desc();

int ice_intact = 1; // This tracks the state of the ice covering the pool.

init()
{
     ::init();
     add_action(water_animal, "water");
     add_action(water_player, "drink");
}
/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */
public void
create_room() {

    set_short("Pool");
    set_long("A small pool, slightly iced over. It rests calmly in\n" +
             "a rift in the moor. Shrubs and foliage grow up around\n" +
             "its edges.\n");
    add_exit("moor1", "southwest",0);
    add_item("shrubs", "They grow up all around the pool.\n");
    add_item("pool","You cannot determine how deep the pool is. "+
            "@@pool_ice_desc@@ You could probably " +
            "drink from the pool.\n");
    add_prop(OBJ_I_CONTAIN_WATER,1);
	add_prop("_live_i_can_fish", "freshwater");
}


public void
reset_room()
{
    ice_intact = 1;
}


string
pool_ice_desc()
{
    if ( ice_intact ) {
        return "A thin sheet of ice covers the surface.";
    }

    return "A thin sheet of ice once covered the surface, but it " +
        "has been broken through.";
}


public int
water_player(string arg)
{

    string verb;

    verb = query_verb();

    if ( !arg )
    {
        NF(capitalize(verb) + " what?\n");
        return 0;
    }

    // This might be better off as a parse_command()
    if ( (arg != "water") &&
         (arg != "pool") &&
         (arg != "from pool") &&
         (arg != "from the pool") )
    {
        NF(capitalize(verb) + " from what?\n");
        return 0;
    }


    drink();
    return 1;

}


int
drink()
{
    if (TP->drink_soft(TP->drink_max() / 16,0))
    {

        if ( ice_intact ) {
            say(QCTNAME(TP) + " breaks the ice that covers the " +
                "pool and drinks some water from it.\n");
            write("You break the thin layer of ice that covers the pool " +
                "and drink some ice cold water. It is quite refreshing.\n");
            ice_intact = 0;
        }
        else
        {
            say(QCTNAME(TP) + " drinks some water.\n");
            write("You drink some ice cold water and feel very refreshed.\n");
        }

        return 1;
    }
    write("Hmm, you are not thirsty at all at the moment.\n");
    return 1;

}

/*********************************************************************/
/*
    This could probably benefit from some more selective
    notify_fails(). I.e. check whether the target is a living,
    and if not, "Be reasonable. You can't water your crimson
    steel longsword." But for now the default notify_fail is
    fine.
*/

int
water_animal(string arg)
{
    object animal;
    int i, amount;
    string animal_desc;

    if (!arg)
    {
        return 0;
    }

    if (parse_command( arg,
                       TO,
                       "[the] %o [from] [at] [the] [pool]",
                       animal))
    {

        if ( !animal->query_prop(LIVE_I_IS) )
        {
            notify_fail("You can't seem to make the " + animal->short() +
                " drink from the pool.\n");
            return 0;
        }

        if ( !animal->query_npc() )
        {
            notify_fail("If " + animal->query_the_name(TP) + " wants to drink, " +
                animal->query_pronoun() + " can do it on " +
                animal->query_possessive() + " own accord.\n");
            return 0;
        }

        if ( TP->query_skill(SS_ANI_HANDL) < 21 )
        {
            notify_fail("Your attempts to coax the " + animal->short() +
                " to drink do not succeed.\n");
            return 0;
        }

        if ( !animal->is_steed() &&
             !present(animal, TP)
           )
        {
            notify_fail("You can only water your own animals.\n");
            return 0;
        }

        if ( animal->is_steed() )
        {

            animal_desc = "steed";

            if ( animal->query_leader() != TP )
            {
                notify_fail("You can't water a steed you're not leading.\n");
                return 0;
            }    
        
        }
        else
        {
            animal_desc = animal->short();
        }

        

        if ( ice_intact )
        {
            say (QCTNAME(TP)+" leads "+HIS_HER+" "+animal->short()+
                 " to the pool, breaks the thin layer of ice that" +
                 " covers it, and waters "+animal->query_objective()+".\n");
            write ("You lead your " +animal->short()+
                   " to the pool, break the thin layer of ice that" +
                   " covers it, and water "+
                   animal->query_objective()+".\n");
            ice_intact = 0;
        }
        else
        {
            say (QCTNAME(TP)+" leads "+HIS_HER+" "+animal->short()+
                 " to the pool and waters "+animal->query_objective()+".\n");
            write ("You lead your " +animal->short()+
                   " to the pool and water "+animal->query_objective()+".\n");
        }

        amount=animal->drink_max() / 20;

        for (i=0;i<20;i++)
        {
            animal->drink_soft(amount);
        }
        animal->drink_soft ( animal->drink_max() - animal->query_soaked());

        return 1;

    }
    else
    {
        notify_fail("Water what, where? \n");
        return 0;
    }
}


