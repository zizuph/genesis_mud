/*
 * /d/Sparkle/area/jade/obj/jade_pear.c
 *
 * Herb from Jade Forest - affects how sharply someone perceives the morality
 * of their actions. Modeled on Gorboth's /d/Sparkle/common/herbs/cattails.c
 *
 * Created 2017-02-03 by Martin Berka (Mar) for Genesis MUD
 */

#pragma strict_types
inherit "/std/herb";
#include <herb.h>
#include <macros.h>
#include <math.h>
#include <poison_types.h> //For effect strength modification

/* Definitions */
#define JADED_POISON "/d/Sparkle/area/jade/obj/jaded_poison.c"

/* Global variables */
int stored_align,
    time_created;
object pear_eater;

public void        create_herb();
/*
 * Function name:        create_herb
 * Description  :        the constructor for the herb object
 */
public void
create_herb()
{
    set_name("fruit");
    add_name( ({ "fruit" }) );
    add_pname("fruits");
    set_adj( ({"grey", "shriveled", "green"}) );
    set_herb_name("neh fruit");
    set_short("grey shriveled fruit");
    set_ingest_verb("eat");
    set_effect(HERB_SPECIAL, "jade", 50);
    set_unid_long("This dried-up fruit is grey with hints of green all over "
        + "its shriveled surface.\n");
    set_id_long("The grey-green fruit of the neh tree takes a full two years "
        + "to drop, in which time the tree provides it with the bare minimum "
        + "of nourishment to keep the seeds alive. The result is a dry, "
        + "shriveled fruit too dull for any but the hungriest herbivore, and "
        + "too tough to be challenged by any climate. Those who can stomach it "
        + "report a short-lived but intense ambivalence about the morality "
        + "of their subsequent actions.\n");
    set_amount(15); /* Think of a large, grey prune. */
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 20); //Dry but probably not completely free of air.
    //Normal pear would float (V>W), but this one is 80% alcohol and 20% jade.

    set_id_diff(40); /* Obscure, affects alignment - should be substantial.*/
    set_find_diff(5);
    set_herb_value(400);
    //set_dryable(); //Probably the driest fruit imaginable

    time_created = time();

} /* create_herb */


/*
 * Function:    query_recover
 * Description: You recover (this herb)
 * Returns:     The recovery string
 */
string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
} /* query_recover */

/*
 * Function:    init_recover
 * Description: Launch herb-recovery function
 */
void
init_recover(string arg)
{
    init_herb_recover(arg);
} /* init_recover */

/*
 * Function name:   special_effect
 * Description  :   effect of eating the neh - reduce alignment change
 */
public void
special_effect()
{
    object to = this_object();

    setuid();
    seteuid(getuid(to));

    int object_life = time() - time_created;
    int effect_strength = 20 + ftoi( log(itof(object_life + 1)) );
    //Fruit becomes more jaded over time - 20%->38% after 3 years.
    //+ 1 to eliminate risk of log(0)

    object poison = clone_object(JADED_POISON);
    poison->set_effect_strength(effect_strength);
    poison->move(this_player());
    poison->start_poison(this_player()); //Chose to consume.
}
