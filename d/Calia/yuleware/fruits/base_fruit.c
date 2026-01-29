// OBJECT:  base_fruit

    /* Calia Domain

    HISTORY

    [1999-12-17] Created from [C:\CALIA\YULEWARE\FRUITS\BASE_FRU.DOC] by
        Uhclem.

    [02-12-19] Testing messages removed by Uhclem.

    PURPOSE

    A generic fruit that is configured with specific attributes when it is
    cloned by the yuleware storage room.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include "defs.h"

// GLOBAL VARIABLES

string Hue;
string Glaze;
string Fruit;

// FUNCTIONS

// Function:  query_recover()

/*

Purpose:  prevent this object from ever being recovered since it must be
configured by the object which clones it to be of any use.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The " + short() + " exudes " +
        ({
        "an enticing",
        "a sensuous",
        "an alluring",
        "a savory",
        "a stimulating"
        })[random(5)] +
        " aroma of " + Glaze + " with " +
        ({
        "a subtle undercurrent",
        "a hint of",
        "a nearly imperceptible suggestion",
        "just a touch",
        "faint traces",
        "a vague suggestion",
        "an indistinct yet provocative insinuation"
        })[random(7)] +
        " of " + Fruit + ".\n");

}

// Function:  configure_fruit(*hue_glaze_fruit)

/*

Purpose:  add specific attributes to this object.

Arguments:  an array of strings describing the hue, glaze, and type of fruit.

Returns:  nothing.

*/

void
configure_fruit(string *hue_glaze_fruit)

{

    string *namewords =
        explode(hue_glaze_fruit[0] + " " + hue_glaze_fruit[2], " ");

    int m = sizeof(namewords) - 1;
    set_name(namewords[m]);
    set_name("fruit");
    set_pname(namewords[m] + "s");
    set_pname("fruits");
    add_adj(namewords[m-2..m-1]);

    /*
     *  The last word in the description is always the type of fruit, the 
     *  second to last is the primary color. Add this color as an adjective so
     *  that players can get all "red" fruits, etc.    
     */

    add_adj(namewords[m - 1]);

    Hue = hue_glaze_fruit[0];
    Glaze = hue_glaze_fruit[1];
    Fruit = hue_glaze_fruit[2];

    set_short(Hue + " " + Fruit);

    set_long("The " + Fruit + " has been prepared by removing" +
        " all traces of stem, seed, and skin, and it is enrobed" +
        " in a " + Hue + " glaze created from an old" +
        " Calian recipe containing " + Glaze + " and other" +
        " delicacies. The glaze not only makes the " + Fruit +
        " an unusual taste treat but also preserves it" +
        " in perfect condition until it is eaten.\n");

}

// Function:  query_fruit_config()

/*

Purpose:  return the hue, glaze, and type of fruit.

Arguments:  none.

Returns:  array containing three strings.

*/

mixed
query_fruit_config()

{

    return ({Hue, Glaze, Fruit});

}

// Function:  splatter_fruit()

/*

Purpose:  provide a message to the room and remove the object.  This function
is called with a 0.01 second delay to allow it to "hit the floor" after it is
dropped.

Arguments:  none.

Returns:  nothing.

*/

void
splatter_fruit()

{

    string ob_name = LANG_THESHORT(this_object());
    string s;

    if (!environment()->query_prop(ROOM_I_IS))

    {

        return;

    }

    if (num_heap() == 1)

    {

        s = "s";

    }

    else

    {

        s = "";

    }

    tell_room(environment(), capitalize(ob_name) + " " +
        ({
        "hit" + s + " the ground with a resounding SPLAT! Little" +
        " fruit bits fly in all directions!",
        "fall" + s + " to the ground and splatter" + s +
        " into millions of pieces!",
        "explode" + s + " into a spray of fruit juice upon" +
        " impact with the ground!"
        })[random(3)] + "\n");

    remove_object();

}

// Function:  steal_fruit()

/*

Purpose:  provide a message to the room and remove the object.
    (real purpose:  to annoy players trying to hoard fruit)

Arguments:  none.

Returns:  nothing.

*/

void
steal_fruit()

{

    object env = environment();
    object *fruit_array;
    string *fruit_effects;
    string ob_name = LANG_THESHORT(this_object());
    int fruit_count = 0;
    int m;
    int n;

    /*
     *  Only fruits held by the player or put in a room are vulnerable.  Fruits 
     *  will not be removed from backpacks and other containers.    
     */

    if (living(env))

    {

        fruit_array = FIND_STR_IN_OBJECT("fruits", env);
        m = sizeof(fruit_array);

        for (n = 0; n < m; n += 1)

        {

            fruit_count += fruit_array[n]->num_heap();

        }

        if (random(fruit_count) > (env->query_stat(SS_DEX) / 20))

        {

            tell_room(environment(env),
                QCTNAME(env) + " seems to be having trouble holding" +
                " on to a large supply of fruit.\n",
                env);

            env->command("$drop fruit");

        }

    }

    if (env->query_prop(ROOM_I_IS))

    {

        if (num_heap() == 1)

        {

            fruit_effects =
                ({
                "The Mouse King, clad in grandiose robes and" +
                " a golden crown, marches in, grabs " + ob_name +
                ", and scampers out with his prize!",
                capitalize(ob_name) + " mysteriously rolls away.",
                capitalize(ob_name) + " spontaneously bursts into" +
                " flames and is consumed in an instant!",
                "A slight crack suddenly appears in the glaze" +
                " on " + ob_name + ", and then in an instant" +
                " the glaze dissolves entirely from the effects" +
                " of the juice within, leaving nothing behind but a" +
                " pleasant aroma of fruit.",
                "A fruit bat swoops in and in one swift, graceful" +
                " arc grabs " + ob_name + " and then" +
                " flies away again.",
                "Lightning strikes " + ob_name + " with a" +
                " deafening roar and blinding flash! When you regain" +
                " your senses, you see that it has" +
                " been completely destroyed.",
                capitalize(ob_name) + ", impertinently refusing to" +
                " behave like a proper " + Fruit + ", sprouts wings" +
                " and flies out of sight."
                });

        }

        else

        {

            fruit_effects =
                ({
                capitalize(LANG_WNUM(num_heap())) +
                " mice wearing little military uniforms" +
                " dash in, grab " + ob_name + ", squeak excitedly" +
                " at their prizes, and, straining under their" +
                " loads, dash out again!",
                capitalize(ob_name) + " mysteriously vanish.",
                capitalize(ob_name) + " unexpectedly roll toward" +
                " each other and are destroyed in" +
                " a horrible collision!",
                "Lightning strikes " + ob_name + " with a" +
                " deafening roar and blinding flash! When you regain" +
                " your senses, you see that they have" +
                " been completely destroyed.",
                "A gloomy old male human arrives, spies " + ob_name +
                ", stomps them mercilessly into a pulp, and" +
                " then storms away. As he departs, you can" +
                " hear him grumbling: " + capitalize(Fruit) + "s!" +
                " Humbug, I tell you! Humbug!"
                });

        }

        tell_room(env,
            fruit_effects[random(sizeof(fruit_effects))] + "\n");

        remove_object();

    }

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  called by system when this object moves to a new environment; used
here to detect when fruit is dropped to make it splatter.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    int n;

    ::enter_env(ob_to, ob_from);

    /*
     *  This test makes sure that we don't generate runtime errors when the 
     *  object is moved around by any wizard commands or system functions,
     *  especially the split and merge heap routines.    
     */

    if (!ob_to || !ob_from)

    {

        return;

    }

    if (living(ob_to))

    {

        set_alarm(0.5, 0.0, steal_fruit);

    }

    else if (ob_to->query_prop(ROOM_I_IS))

    {

        if (query_verb() == "drop"  || query_verb() == "$drop")

        {

            set_alarm(0.0, 0.0, splatter_fruit);

        }

        if (query_verb() == "put")

        {

            n = random(5);

            switch (n)

            {

                case 0:
                set_alarm(11.1, 0.0, steal_fruit);
                break;

                case 1:
                set_alarm(22.2, 0.0, steal_fruit);
                break;

                case 2:
                set_alarm(33.3, 0.0, steal_fruit);
                break;

                case 3:
                set_alarm(55.5, 0.0, steal_fruit);
                break;

                case 4:
                set_alarm(77.7, 0.0, steal_fruit);

            }

        }

    }

}

// OBJECT DEFINITION

void
create_food()

{

    object *my_clones;

    /*
     *  DESCRIPTION    
     */

    set_name("fruit");
    set_short("fruit");
    set_long(explode(file_name(this_object()), "#")[0] + "\n");

    /*
     *  PROPERTIES    
     */

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 110);

}
