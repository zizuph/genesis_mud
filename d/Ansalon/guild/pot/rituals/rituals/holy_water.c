/*
 * Revisions:
 *   Lucius, Aug 2016: Made it possible to enchant multiple phials.
 *
 */
inherit "/d/Ansalon/guild/pot/rituals/rituals/std_ritual";

#include "../rituals.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <composite.h>

void
create_ritual()
{
    setuid();
    seteuid(getuid());

    set_name("holy_water");
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
    // This ritual enchants a phial of water and makes it full of
    // holy water.
    foreach (object ingredient : ingredients)
    {
        if (MASTER_OB(ingredient) == (GUILDDIR + "rituals/obj/phial"))
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
    object * all_waters = filter(all_inventory(query_altar()),
	&->id("water"));
    object * all_phials = filter(all_inventory(query_altar()) - all_waters,
	&->id("_std_potion_vial"));
	
    all_phials = filter(all_phials, not @ &->query_enchanted());

    foreach(object phial: all_phials)
    {
	if (!sizeof(all_waters))
	    break;

	// Clone the Enchantment Shadow
	object sh = clone_object(GUILDDIR + "rituals/shadows/holy_water");

	// Get the Object to Enchant
	string msg = sh->enchant(phial, max(1, query_result()));
	if (strlen(msg))
	{
	    set_fail(msg);
	    query_chantee()->catch_tell(msg + "\n");
	}
	else
	{
	    phial->set_contains_water();

	    object water = all_waters[0];
	    if (water->num_heap() > 1)
	    {
		water->set_heap_size(water->num_heap() - 1);
	    }
	    else
	    {
		water->remove_object();
		all_waters = filter(all_waters, objectp);
	    }
	}
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
            chantee("You chant: Oh Takhisis whose might is unquestionable.");
            others(0, " chants: Oh Takhisis whose might is unquestionable.");
            others("In unison with ", " you chant: Takhisis.");
            onlookers(QCTNAME(query_chantee()) + " chants: Oh Takhisis " +
                "whose might is unquestionable", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 1:
            chantee("You continue: Bless this phial that it might be a " +
                "vessel of your power.");
            others(0, " continues: Bless this phial that it might be a " +
                "vessel of your power.");
            others("In unison with ", " you chant: The power of Takhisis.");
            onlookers(QCTNAME(query_chantee()) + " chants: Bless this " +
                "phial that it might be a vessel of your power", " while " +
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
                "opens ever so slightly and looks about the abbey and its " +
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
    // The water ingredient can be found: /d/Ansalon/taman_busuk/neraka/obj/drink/swater
    return ({ (GUILDDIR + "rituals/obj/phial"), "water" });
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

