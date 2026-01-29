/*
 * Ritual to break knives into shards
 *
 * This ritual was introduced to ease the use of gems in the
 * PoT guild. By converting gems into dusts, it gives priests
 * the ability to get more from each gem that is collected.
 *
 * Created by Zizuph, November 2022
 */

inherit "/d/Ansalon/guild/new_pot/rituals/rituals/std_ritual";

#include "../rituals.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <composite.h>
#include <files.h>
#include <wa_types.h>

/*
 * Function:    create_ritual
 * Description: Initialization function to set the name to be
 *              used by the ritual code. The definition of all
 *              currently available/used rituals is in ritual.h
 */
public void
create_ritual()
{
    setuid();
    seteuid(getuid());

    set_name("knife");
}

/*
 * Function:    ritual_specific_effect
 * Description: This is the function that should be overridden by the ritual
 *              to actually describe the "meat" of the ritual. It does the
 *              cloning, shadowing, and the creation of the "product" of the
 *              ritual.
 */
public void
ritual_specific_effect()
{
    GUILD_ADMIN->log(query_chantee(), "rituals", "knife shard;");
    
    // We convert all the knives on the altar
    object * all_knives = filter(all_inventory(query_altar()),
        &operator(==)(W_KNIFE) @ &->query_wt());
    all_knives = filter(all_knives, not @ &->query_prop(OBJ_I_BROKEN));
    foreach (object knife : all_knives)
    {
        object ritual_product = clone_object(GUILDDIR + "rituals/obj/knife_shard");
        // Each knife will result in between 4-8 knife shards.
        int new_quantity = 4 + random(5);
        ritual_product->set_heap_size(new_quantity);
        ritual_product->move(query_altar());
    }
    all_knives->remove_object();
}

varargs void
perform_ritual(int round = 0)
{
    if (!sanity_check())
    {
        reset_ritual_variables();
        return;
    }

    switch (round)
    {
        case 0:
            chantee("You chant: Oh Takhisis whose might is unquestionable.");
            others(0, " chants: Oh Takhisis whose might is unquestionable.");
            others("In unison with ", " you chant: Takhisis.");
            onlookers(QCTNAME(query_chantee()) + " chants: Oh Takhisis " +
                "whose might is unquestionable", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 1:
            chantee("You continue: Break these weapons that they might be a " +
                "vessel of your power.");
            others(0, " continues: Break these weapons that they might be a " +
                "vessel of your power.");
            others("In unison with ", " you chant: The power of Takhisis.");
            onlookers(QCTNAME(query_chantee()) + " chants: Break these " +
                "weapons that they might be a vessel of your power", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 2:
            chantee("You close your eyes, raise your arms up high and " +
                "barely whisper: Our Saviour!");
            others(0, " closes " + HIS(query_chantee()) + " eyes, raises " +
                HIS(query_chantee()) + " arms up high and barely whispers: " +
                "Our Saviour!");
            others("In unison with ", " you chant: Our Saviour!");
            onlookers(QCTNAME(query_chantee()) + " closes " +
                HIS(query_chantee()) + " eyes, raises " +
                HIS(query_chantee()) + " arms up high and barely whispers: " +
                "Our Saviour", " while " + COMPOSITE_LIVE(query_others()) +
                " chants in unison.");
            break;
        case 3:
            tell_room(environment(query_chantee()), "The eyes of the statue " +
                "opens ever so slightly and " + ({"looks", "looks", "looks",
                "glares"})[random(4)] + " about the abbey and its " +
                "occupants.\n");
            break;
        case 4:
            tell_room(environment(query_chantee()), "There is a thundering " +
                "noise and flames spawn from the altar.\n");

            break;
        case 5:
            tell_room(environment(query_chantee()), "As the eyes of the " +
                "statue closes there is a strange silence.\n");
            chantee("Overcome by ectasy you chant: Takhisis!");
            others(0, " chants overcome by ectasy: Takhisis!");
            others("In unison with ", " you chant: Takhisis!");
            onlookers("Overcome by ectasy " + QTNAME(query_chantee()) +
                " chants: Takhisis", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");

            ritual_effect();
            break;        
    }
    
    if (round < 5)
        set_alarm(4.3, 0.0, &perform_ritual(round + 1));
}

/*
 * Function:    query_ingredients
 * Description: This returns the string list of ingredients that the ritual
 *              requires. It accept a few types of ingredient strings.
 *                 - W<weapon type>. For example, Wclub means to look for a club type.
 *                 - /path/file. This is a fully qualified path to the object
 *                 - _<property>. For example _live_is_undead is a property that can be checked.
 *                 - name - can be either the name of an herb or an object
 */
public string *
query_ingredients()
{
    return ({ "Wknife" });
}

/*
 * Function:    query_difficulty
 * Description: Returns the difficulty level (task-based) by which the
 *              ritual should be compared against the PS_SKILL_POINTS of
 *              the chantee.
 */
public int
query_difficulty()
{
    return TASK_SIMPLE;
}


/*
 * Function:    query_minimum_priests
 * Description: Each ritual can have a minimum number of priests requried
 *              to perform the ritual. 
 */
public int
query_minimum_priests()
{
    return 1;
}
