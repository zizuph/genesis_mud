/*
 * /d/Sparkle/area/jade/obj/green_jam.c
 *
 * A jar of suspicious jam from the Jade Forest orchard, mixed from who-knows-
 * what local plants. Eat at own risk - has the effect of the unknown herb
 * that was mixed into it, and also dyes the skin. Can be eaten slightly more
 * often then herbs, though also fills more.
 *
 * Created 2017-03-10 by Martin Berka (Mar) for Genesis MUD
 */

#pragma strict_types
inherit "/std/food";

#include "../defs.h"
#include <macros.h>
#include <math.h>

/* Definitions */
#define HERB_TIME   "_live_i_herb_effect"

/* Global variables */
int time_created;
string  custom_adj,
        effect_file;
//function remote_effect;

int mix_ingredients(string str);

/*
 * Function name:        create_food
 * Description  :        Jam object constructor
 */
public void
create_food()
{
    custom_adj = "green";
    time_created = time(); //Store time of creation to help determine effect?

    add_name( ({ "jam", "jar", "jam", "jam in a jar", "jam jar",
        "jar of jam", "jam in a jar"}) );
    set_pname("jars of " + custom_adj + " jam");
    add_pname( ({"jars", "jams"}) );

    set_short("jar of " + custom_adj + " jam");
    set_pshort("jars of " + custom_adj + " jam");

    set_long("The small glass jar is full of clear jam, made from "
        + "an ambiguous mixture of fruits. The visual and olfactory "
        + "jumble is too complex for you to identify its components in detail. "
        + "There is a small label - 'Goes well with herbs!'\n");

    set_amount(90); //Small jar, quitee nourishing

    add_prop(OBJ_I_VOLUME, 100); //Small jar, one mouthful
    add_prop(OBJ_I_WEIGHT, 120); //Some of those fruits are dense

    string *default_herbs = ({"/d/Earthsea/herbs/herb_files/bergamot",
        "/d/Gondor/common/herbs/basil",
        "/d/Krynn/common/herbs/fdlhead",
        "/d/Gondor/common/herbs/laurel",
        "/d/Gondor/common/herbs/mint",
        "/d/Gondor/common/herbs/savory",
        "/d/Sparkle/area/jade/obj/neh_fruit"
    });

    effect_file = default_herbs[random( sizeof(default_herbs) )];
} /* create_food */


/*
 * Function name: command_eat
 * Description:   Eat the jam - override food's function to check herb condition
 * Returns:       (mixed) 1/0/error (like in /std/food)
 */
public mixed
command_eat()
{
    if (this_player()->query_prop(HERB_TIME) > time() - 40)
    {
        return "As you raise the " + this_object()->singular_short()
            + " to your mouth, you feel a wave of nausea. Maybe you should "
            + "wait a bit before consuming whatever is in it.\n";
    }
    return ::command_eat();
}


/*
 * Function name: init
 * Description  : Add herb-planting action
 */
void
init()
{
    ::init();
    add_action(mix_ingredients, "mix");
    add_action(mix_ingredients, "stir");
}


/*
 * Function name: init_recover
 * Description  : Called when the jam recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string foobar;
    int    num;
    string  custom_adj,
            effect_file;
    if (sscanf(str, "%sheap#%d#%s#%s#%d#%s", foobar, num, effect_file,
        custom_adj, time_created, foobar ) >= 3)
    {
        set_heap_size(num);
    }
} /* init_recover */

/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover. It will only function for food that has a
 *                real file rather than being cloned from /std/food.c
 *                since only the amount of food on the heap is saved.
 */
public string
query_recover()
{
    string file = MASTER;
    return file + ":heap#" + num_heap() + "#" + effect_file + "#"
        + custom_adj + "#" + time_created + "#";
}


/*
 * Function name:   mix_ingredient
 * Description  :   Mix an edible ingredient into the jam to affect it.
 * Arguments    :   A string describing the ingredients from among whose
 *      properties the jam may choose.
 * Returns      :  Whether the action was recognized.
 */
int
mix_ingredients(string str)
{
    if (!str) //Nothing to mix in
    {
        return 0;
    }

    if (TP->query_prop(LIVE_O_SPELL_ATTACK) || TP->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You are busy with other things!\n");
        return 1;
    }

    mixed *ingredients; //What are we mixing?
    if (!parse_command(str, TP,
        "[the] %i [with] / [into] [the] [jar] [of] [jam] / [jar]", ingredients))
    {
        notify_fail("Stir what?\n");
        return 1;
    }
    object ingredient = ingredients[1];

    string *adjectives =({});
    string shorts = "";

    write("You messily stir the " + ingredient->query_short()
        + " into the jar.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
        + " stirs something into a jar of jam.\n", this_player());

    shorts += "," + ingredient->query_short();

    ingredient->remove_object();

    string *col_names = ({"red", "orange", "white", "yellow", "brown", "green",
        "blue", "purple", "grey", "black" }); //colors of herbs
    string *patterns = ({ "*red*", "*orang*", "*whit*", "*yellow*", "*brown*",
        "*green*", "*blue*", "*purpl*", "*grey*", "*black*" });
    for (int i = sizeof(patterns) - 1; i--; )
    {
        if (wildmatch(patterns[i], shorts))
        {
            adjectives += ({col_names[i]});
        }
    }
    if (random(1))
    {
        custom_adj = one_of_list(adjectives);
        set_name("jar of " + custom_adj + " jam");
        add_adj(custom_adj);
        set_short("jar of " + custom_adj + " jam");
        set_pshort("jars of " + custom_adj + " jam");
        set_long("The small glass jar is full of " + custom_adj + " jam, made "
            + "from an ambiguous mixture of fruits and herbs. The visual "
            + "and olfactory jumble is too complex for you to identify its "
            + "ingredients in detail. "
            + "There is a small label - 'As safe as Jade!'\n");

        write("The jam turns " + custom_adj + ".\n");
    } //Otherwise remains green

    if (random(1) && function_exists( "special_effect", ingredient))
    {//Independent of description change
        effect_file = function_exists( "special_effect", ingredient);
    }
    return 1;
} /* mix_ingredients */


/*
 * Function name:   special_effect
 * Description  :   effect of eating the jam - one of several
 */
void
special_effect(int number_eaten)
{
    if (effect_file)
    {
        /* We need our own instance of the object so that anything can happen
         * to it.
         */
        object effect_obj = clone_object(effect_file);
        this_player()->catch_msg( "The texture of the jam reminds you of a certain "
            + effect_obj->query_short() + ".\n");

        //Launch the herb effect
        effect_obj->do_herb_effects();

        this_player()->add_prop(HERB_TIME, time() - 20);
        //Jam is
        //Look into /lib/herb_support.c
    }

    object to = this_object();

    setuid();
    seteuid(getuid(to));
    int object_life = time() - time_created;

    object dye = clone_object(OBJ_DIR + "dyed_skin");
    dye->set_skin_adj(custom_adj);
    dye->move(this_player());
} /* special_effect */
