inherit "/d/Ansalon/guild/new_pot/rituals/rituals/std_ritual";

#include "../rituals.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <composite.h>
#include <wa_types.h>

public void
create_ritual()
{
    setuid();
    seteuid(getuid());

    set_name("dark_touch");
}

public string
query_strength_desc(int str)
{
    switch (str)
    {
        case 1..15:
            return "weak";
        case 16..30:
            return "somewhat powerful";
        case 31..50:
            return "powerful";
        case 51..75:
            return "very powerful";
        case 76..90:
            return "extremely powerful";
        case 91..100:
            return "vastly powerful";
    }
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
    // This ritual enchants a club. so we need to make sure the club is
    // excluded from the ingredients to get consumed.
    int wt = W_FIRST + member_array("club", W_NAMES);
    foreach (object ingredient : ingredients)
    {
        if (ingredient->query_wt() == wt)
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
    object sh = clone_object(GUILDDIR + "rituals/shadows/dark_touch");
    
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
        int t = 2500 + query_result() * 12 +
            query_chantee()->query_standing() * 2 +
            query_chantee()->query_priest_level() * 400 +
            sizeof(query_others()) * 250 + random(500) + random(500);
        GUILD_ADMIN->log(query_chantee(), "rituals", "dark_touch; t: " + t);
        object_to_enchant->set_enchantment_duration(t);
        query_chantee()->catch_msg("When the dust settles you are " +
            "awed by the " + query_strength_desc(max(1, query_result())) +
            " aura that spawns from the " + object_to_enchant->short() +
            ".\n");
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
            chantee("You continue: Bless this weapon that it might be a " +
                "vessel of your power.");
            others(0, " continues: Bless this weapon that it might be a " +
                "vessel of your power.");
            others("In unison with ", " you chant: The power of Takhisis.");
            onlookers(QCTNAME(query_chantee()) + " chants: Bless this " +
                "weapon that it might be a vessel of your power", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 2:
            chantee("You continue: With blood it shall be forged.");
            others(0, " continues: With blood it shall be forged.");
            others("In unison with ", " you chant: With blood.");
            onlookers(QCTNAME(query_chantee()) + " chants: With blood " +
                "it shall be forged", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 3:
            chantee("You continue: With fire it shall breathe.");
            others(0, " continues: With fire it shall breathe.");
            others("In unison with ", " you chant: With fire.");
            onlookers(QCTNAME(query_chantee()) + " chants: With fire " +
                "it shall breathe", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 4:
            chantee("You continue: With the hardness of diamond it " +
                "shall be reimbursed.");
            others(0, " continues: With the hardness of diamond it " +
                "shall be reimbursed.");
            others("In unison with ", " you chant: With diamond.");
            onlookers(QCTNAME(query_chantee()) + " chants: With the " +
                "hardness of diamond it shall be reimbursed", " while " +
                COMPOSITE_LIVE(query_others()) + " chants in unison.");
            break;
        case 5:
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
        case 6:
            tell_room(environment(query_chantee()), "The eyes of the statue " +
                "opens ever so slightly and " + ({"looks", "looks", "looks",
                "glares"})[random(4)] + " about the abbey and its " +
                "occupants.\n");
            break;
        case 7:
            tell_room(environment(query_chantee()), "There is a thundering " +
                "noise and flames spawn from the altar.\n");

            break;
        case 8:
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
    
    if (round < 8)
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
    return ({ "Wclub", "fireweed", "heart", "diamond" });
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
