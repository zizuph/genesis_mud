/*
 */

inherit "/d/Ansalon/guild/pot/rituals/rituals/std_ritual";

#include "../rituals.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <composite.h>

void
create_ritual()
{
    set_name("magical_vestment");
}

/*
 * Function:    exclude_ritual_products
 * Description: Returns a list of ritual products to exclude from the
 *              ingredient list. This ensures that the product won't be
 *              removed when the ingredients are consumed.
 */
public object *
exclude_ritual_products(object * ingredients)
{
    // This ritual enchants a robe. so we have to make sure the robe is
    // excluded.
    foreach (object ingredient : ingredients)
    {
        if (ingredient->id("robe"))
        {
            return ({ ingredient });
        }
    }
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

    // Clone the Enchantment Shadow
    object sh = clone_object(GUILDDIR + "rituals/shadows/vestment");
    
    // Get the Object to Enchant
    object object_to_enchant = query_object_to_enchant(); 
    string msg = sh->enchant(object_to_enchant, max(1, query_result()));
    if (msg)
    {
        set_fail(msg);
        query_chantee()->catch_tell(msg + "\n");
    }
    else
    {
        GUILD_ADMIN->log(query_chantee(), "rituals", "magical_vestment;");
    }
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
            chantee("You light the candles on the altar.");
            tell_room(environment(query_chantee()),
                QCTNAME(query_chantee()) + " lights the candles on the " +
                "altar.\n", query_chantee());
            all_inventory(query_altar())->light_me();
            break;
        case 1:
            chantee("You raise your voice in a hymn to Takhisis.");
            others(0, " raises " + HIS(query_chantee()) + " voice in a " +
                "hymn to Takhisis in which you join.");
            onlookers(QCTNAME(query_chantee()) + " raises " +
                HIS(query_chantee()) + " voice in a hymn to Takhisis",
                " in which " + COMPOSITE_LIVE(query_others()) + " join.");
            break;
        case 2:
            chantee("You open the leather pouch and sprinkle its " +
                "glimmering contents upon the robe.");
            tell_room(environment(query_chantee()),
                QCTNAME(query_chantee()) + " opens the leather pouch " +
                "and sprinkles its glimmering contents upon the robe " +
                "resting on the altar.\n", query_chantee());
            break;
        case 3:
            chantee("You close your eyes, raise your arms up high and " +
                "sing a praise to Takhisis.");
            others(0, " closes " + HIS(query_chantee()) + " eyes, raises " +
                HIS(query_chantee()) + " arms up high and sing a praise " +
                "Takhisis.");
            others("In unison with ", " you chant: Takhisis!");
            onlookers(QCTNAME(query_chantee()) + " closes " +
                HIS(query_chantee()) + " eyes, raises " +
                HIS(query_chantee()) + " arms up high and sing a praise " +
                "to Takhisis", " while " + COMPOSITE_LIVE(query_others()) +
                " chants in unison.");
            break;
        case 4:
            tell_room(environment(query_chantee()), "The eyes of the " +
                "statue opens ever so slightly and looks about the abbey " +
                "and its occupants.\n");
            break;
        case 5:
            tell_room(environment(query_chantee()), "The lit candles upon " +
                "the altar flickers violently and a thundering noise is " +
                "heard.\n");
            break;
        case 6:
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

    if (round < 6)
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
    return ({ "robe", (GUILDDIR + "rituals/obj/xxx") });
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
    return TASK_ROUTINE;
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
