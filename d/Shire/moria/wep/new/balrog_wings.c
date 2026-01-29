/*
*  Balrog's wings
*
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  23/04-17                   Several updates                          Znagsnuf
*  24/04-17                   Added resistance                         Znagsnuf
*
*/

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <files.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>

int do_repair(string str);
public void do_ignite();

// Slots for magical properties 
int w_power = 0;
int d_timer = 0;
int f_wings = 0;
int worn = 0;
// Light / Darkness
int bd = 2;
object res_obj;

#define SUBLOC "_balrog_wing_subloc"
#define FLAMING_WINGS 7
#define BALROG_REPAIR "_live_i_used_wing_repair"
#define decay_timer 3600.0

/*
 * Function name: create_armour
 * Description  : In order to create an armour, you should redefine this
 *                function. Typically you use this function to set the
 *                name and description, the armour type, the armour class
 *                etcetera.
 */
void
create_armour()
{
    set_name("wings");
    set_adj( ({ "shadowy", "black" }) );

    set_short("pair of black shadowy wings");
    set_pshort("pairs of black shadowy wings");
    set_long("Shadows sharply defined as wings, spreads out and cover "
           + "a vast area. @@check_power@@\n@@black_pattern@@");

    set_ac(50);
    set_at(A_ROBE);
    set_wf(this_object());

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)
                        + random(100) + 100);

    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchanted" }));
    add_prop(MAGIC_AM_ID_INFO,({
        "The magical properties of this item helps you withstand fire",  1,
        "The light seems to adjust around these wings",  20,
        "Swirling these wings around your body will force it to consume "
        + "a magical armour",  50, 
        "These wings hungers for more power, to fuel its self repairing "
        + "mechanisms", 60 }) );

    add_prop(OBJ_S_WIZINFO, "Wings used by the Balrog, will grow in intensity "
                          + "if magical armours is consumed. Will also adjust "
                          + "the Light, according to its current status, "
                          + "shadowy wings will devour the light, while "
                          + "flaming wings will shed light. The wings will "
                          + "also give you protection against fire.\n");

}

/*
 * Function name: black_pattern()
 * Description  : Check is the cool down is active.
 */
string
black_pattern()
{
    if (this_player()->query_prop(BALROG_REPAIR) + 60 > time()
                    || query_prop(BALROG_REPAIR) + 60 > time())
    {
        return "These wings seem to push you away, almost as if there is a " +
            "power hidden within them that is not ready to accept you.\n";
    }
    else
    {
        return "These wings are strangely compelling, as if begging you " +
               "to embrace the power hidden within!\n";
    }
}

/*
 * Function name: query_shield_slots
 * Description:   Give a body part protected by a shield or magic armour
 */
public int *
query_shield_slots()
{
    return ({ A_BODY, A_LEGS});
}


/*
 * Function name: set_wing_power()
 * Description  : Sets the wing power.
 */
int
set_wing_power(int i)
{
    w_power = i;
}

/*
 * Function name: query_wing_power)
 * Description  : Return the wing power.
 */
int
query_wing_power(int i)
{
    return w_power;
}
    
/*
 * Function name: set_repair
 * Description:   When trying to repair the armour, call this function. Repairs
 *                can only increase the repair factor.
 * Arguments:     rep - The new repair number
 * Returns:       1 if new repair status accepted
 */
int
set_repair(int rep)
{
    notify_fail("Try as you might, you cannot repair the wings like this. You "
              + "get the impression that a stronger magic is required.\n");
    return 0;
}

/*
 * Function name: set_condition
 * Description:   Use this to increases the corroded status on armour. If the
 *                armour gets dented or anything that turns it into worse
 *                condition, call this function.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 */
int
set_condition(int cond)
{
    condition = cond;

    // The condition should never be negative.
    if(condition <= 0)
        condition = 0;

    // The item is breakable.
    if (F_ARMOUR_BREAK(condition - repair, likely_break))
            set_alarm(0.1, 0.0, remove_broken);

        if (worn && wearer)
            wearer->update_armour(this_object());

    return 1;
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
mixed
wear(object ob)
{
    worn = 1;

    // Adding subloc.
    wearer->add_subloc(SUBLOC, this_object());

    setuid();
    seteuid(getuid());

    // Cloning Resistance object.
    res_obj = clone_object("/std/resistance");
    res_obj->set_strength(40);
    res_obj->set_res_type(MAGIC_I_RES_FIRE);
    res_obj->move(wearer);

    // If the power is above FLAMING_WINGS, summon the flaming wings. 
    if(this_object()->query_wing_power() > FLAMING_WINGS)
    {    
        remove_adj( ({ "shadowy", "black" }) );
        set_adj( ({ "flaming", "ethereal" }) );
        set_short("pair of flaming ethereal wings");
        set_pshort("pairs of flaming ethereal wings");
        set_long("Flickering, weaving under the life it was sparked into. "
            + "The glowing wings leaps and twirls in a fiery dance. "
            + "@@check_power@@\n@@black_pattern@@\n");
        this_object()->add_prop(OBJ_I_LIGHT, bd);
        wearer->update_armour(this_object());

        tell_object(wearer, "Swirling flames wrap around your body, " 
                          + "stretching high above your head as you wear "
                          + "the " + this_object()->short() +"!\n");
        tell_room(environment(wearer), QCTNAME(wearer) + " is suddenly "
                + "draped in a storm of swirling flame.\n", wearer);
        return 1;
    } 

    this_object()->add_prop(OBJ_I_LIGHT, -bd);
    wearer->update_armour(this_object());

    // Tell message.
    tell_object(wearer, "You drape the " + this_object()->short()
                + " carefully over your shoulders, finding it fits"
                + " you just perfectly!\n");

    tell_room(environment(wearer), QCTNAME(wearer) + " slips the "  
                + QSHORT(this_object()) + " over "
                + this_player()->query_possessive() + " shoulders.\n", wearer);

    return 1;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object ob)
{
    object wearer;
    worn = 0;

    wearer = query_worn();

    // Removing subloc.
    wearer->remove_subloc(SUBLOC);

    // Stopping and removing the resist object.
    if(res_obj)
        res_obj->stop_res();

    // Changing back to ordinary desc.
    // And adjusting the light.
    if(this_object()->query_wing_power() > FLAMING_WINGS)
    {    

        tell_object(wearer, "The " + this_object()->short()
                          + " dims as it slips off your shoulders.\n");
        tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " dims as "
              + this_player()->query_pronoun() + " removes it from "
              + this_player()->query_possessive() + " shoulders.\n", wearer);

        remove_adj( ({ "flaming", "ethereal" }) );
        set_adj( ({ "shadowy", "black" }) );
        set_short("pair of black shadowy wings");
        set_pshort("pairs of black shadowy wings");
        set_long("Shadows sharply defined as wings, spreads out and cover "
           + "a vast area. @@check_power@@\n@@black_pattern@@");

        // Adjusting the light.
        this_object()->add_prop(OBJ_I_LIGHT, 0);
        wearer->update_armour(this_object());

        return 1;
    }

    // Adjusting the light.
    this_object()->add_prop(OBJ_I_LIGHT, 0);
    wearer->update_armour(this_object());

    // Tell msg.
    tell_object(wearer, "You slip out of the " + this_object()->short() 
                      + ".\n");
    tell_room(environment(wearer), QCTNAME(wearer) + " slips "  
                + QSHORT(this_object()) + " off from "
                + this_player()->query_possessive() + " shoulders.\n", wearer);
    return 1;
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
public void
init()
{
    ::init();
    add_action(do_repair, "swirl");
}

/*
 * Function name: do_decay
 * Description:   Wing power diminish
 */
public void
do_decay()
{
    int power;
    d_timer = 0; 

    // Removing a portion of the power.
    // Removing some AC, and updating the armour.
    if(this_object()->query_wing_power() > 0)
    {
        this_object()->set_wing_power(this_object()->query_wing_power() - 1);
        this_object()->set_ac(this_object()->query_ac() - 1);
    }

    if (worn && wearer)
            wearer->update_armour(this_object());

    power = this_object()->query_wing_power();    

    // Tell message.    
    tell_object(wearer, "The " + this_object()->short() + " seems to "
                      + "lessen in intensity.\n");
    tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " seems to lessen in " +
              "intensity.\n", wearer);

    if(f_wings)
    {
        if(this_object()->query_wing_power() < FLAMING_WINGS)
        {   

            tell_object(wearer, "The " + this_object()->short() + " fades "
                + "as they turn shadowy black.\n");
            tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " fades as they turn "
              + "shadowy black.\n", wearer);

            remove_adj( ({ "flaming", "ethereal" }) );
            set_adj( ({ "shadowy", "black" }) );
            set_short("pair of black shadowy wings");
            set_long("Shadows sharply defined as wings, spreads out and cover "
                   + "a vast area. @@check_power@@\n@@black_pattern@@");

            this_object()->add_prop(OBJ_I_LIGHT, -bd);
            wearer->update_armour(this_object());

            wearer->remove_subloc(SUBLOC);
            wearer->add_subloc(SUBLOC, this_object());

            f_wings = 0;
        }
    }    

    // Run the alarm, as long there is power in the item.
    if(this_object()->query_wing_power() > 0 && wearer->query_real_name() != "gash")
    {
        set_alarm(30.0, 0.0, &do_decay());
        d_timer = 1;
    }    

}

/*
 * Function name: do_ignite
 * Description:   Add max power, for the Balrog
 */
public void
do_ignite()
{
    //Max power.
    if(worn)
    {
        this_object()->set_wing_power(10);
        this_object()->set_ac(60);
    }

    if (worn && wearer)
            wearer->update_armour(this_object());

    if(!f_wings && worn)
    {
        if(this_object()->query_wing_power() >= FLAMING_WINGS)
        {    
            remove_adj( ({ "shadowy", "black" }) );
            set_adj( ({ "flaming", "ethereal" }) );
            set_short("pair of flaming ethereal wings");
            set_long("Flickering, weaving under the life it was sparked into. "
            + "The glowing wings leaps and twirls in a fiery dance. "
            + "@@check_power@@\n@@black_pattern@@\n");

            f_wings = 1;

            add_prop(OBJ_I_LIGHT, bd);
            wearer->update_armour(this_object());

            wearer->remove_subloc(SUBLOC);
            wearer->add_subloc(SUBLOC, this_object());

            tell_object(wearer, "The " + short(wearer) + " burst into fire!\n");
            tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " burst out into "
            + "fire!!!\n", wearer);
        }
    }
    // Just to start the timer.
    set_alarm(decay_timer, 0.0, &do_decay()); 
}

/*
 * Function name: do_extinguish
 * Description:   Remove power, for the Balrog
 */
public void
do_extinguish()
{
    //Min power.
    if(worn)
    {
        this_object()->set_wing_power(0);
        this_object()->set_ac(50);
    }

    if (worn && wearer)
            wearer->update_armour(this_object());

    if(worn)
    {
        if(this_object()->query_wing_power() < FLAMING_WINGS)
        {    
            tell_object(wearer, "The " + this_object()->short() + " fades "
                + "as they turn shadowy black.\n");
            tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " fades as they turn "
              + "shadowy black.\n", wearer);

            remove_adj( ({ "flaming", "ethereal" }) );
            set_adj( ({ "shadowy", "black" }) );
            set_short("pair of black shadowy wings");
            set_long("Shadows sharply defined as wings, spreads out and cover "
                   + "a vast area. @@check_power@@\n@@black_pattern@@");

            this_object()->add_prop(OBJ_I_LIGHT, 0);
            wearer->update_armour(this_object());

            wearer->remove_subloc(SUBLOC);
            wearer->add_subloc(SUBLOC, this_object());

            f_wings = 0;
        }
    }
}

/*
 * Function name: do_repair
 * Description  : Execute the repair command
 */
int do_repair(string str)
{
    int i;
    object consumed_item, wearer, *items, *targets;
    object *item_arr = ({});
    string l_file, file_loc;

    wearer = query_worn();

    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!str)
        return 0;

    // Altering the parse commands according to the short desc.
    // huge flaming / black shadowy
    if(this_object()->query_wing_power() < FLAMING_WINGS)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        if (!parse_command(str, ({ }), " [the] [black] [shadowy] 'wings' "))
            return 0;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        if (!parse_command(str, ({ }), " [the] [ethereal] [flaming] 'wings' "))
            return 0;
    }

    // Fail safe.
    notify_fail("These " + this_object()->short() + " are shattered beyond repair.\n");
    if (query_prop(OBJ_I_BROKEN))
        return 0;

    //Need to be worn to make it work.
    notify_fail("You must wear the " + this_object()->short() + " first!\n");
    if(!this_object()->query_worn())
        return 0;

    // Can't use it in combat
    notify_fail("You cannot do that while you are in combat!\n");
    if(wearer->query_attack())
        return 0;

    notify_fail("These wings are already bursting with energy, leaving you " +
                "unable to further enhance them.\n");
    if(this_object()->query_wing_power() > 9)
        return 0;

    // Wait for cooldown. 60sec
  notify_fail("You cannot do that right now, you will have to wait " +
              "for a moment first.\n");
    if (this_player()->query_prop(BALROG_REPAIR) + 60 > time()
                    || query_prop(BALROG_REPAIR) + 60 > time())
        return 0;

    // Check if there is some magical armours in the inventory.
    items = filter(all_inventory(wearer) - ({this_object()}), 
            &->query_prop(OBJ_I_IS_MAGIC_ARMOUR));

    notify_fail("The "+ short() + " bursts with energy, but nothing "
              + "happens.\n");
    if(!sizeof(items))
        return 0;

    // Remove all the worn items from the array.
    // Remove all the broken items from the array.
    // Remove all the non-drop able items from the array.
    // Remove all the auto-load items from the array.
    // Remove all the imbued items from the array.
    foreach(object nth_item: items)
    {
            if(nth_item->query_prop("_obj_s_imbue_short") ||
            nth_item->query_auto_load() ||
            nth_item->query_prop(OBJ_M_NO_DROP) ||
            nth_item->query_prop(OBJ_I_BROKEN) ||
            nth_item->query_worn())

            item_arr += ({ nth_item });
    }

    // This will occur if there is no magical items left in the inventory.
    notify_fail("The "+ short() + " bursts with energy, but nothing "
              + "happens.\n");
    if (!sizeof(items -= item_arr))
        return 0;

    // Consuming the first item in the array. 
    consumed_item = items[0];
    file_loc = MASTER_OB(consumed_item);

    // Tell msg.
    tell_object(wearer, "A vortex of pure energy surrounds you as " +
                        "the " + short(wearer) + " consumes " 
                        + LANG_ASHORT(consumed_item) + "!\n");
    tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " consumes "
                + LANG_ASHORT(consumed_item) + ".\n", wearer);

    // Add log to Monitor the items consumed.
    l_file = "\t" + ctime(time()) + " " + capitalize(wearer->query_real_name()) 
    + " (" + wearer->query_average_stat() + ") consumed item: \n'" 
    + LANG_ASHORT(consumed_item) + "' - " + file_loc + " \n";

    // Write a log file.
    write_file("/d/Shire/moria/wep/new/consumed_items", l_file);

    // Removes the consumed item.
    consumed_item->remove_object();

    // Add timer to the player, and the item. To prevent spam.
    this_player()->add_prop(BALROG_REPAIR, time());
    add_prop(BALROG_REPAIR, time());

    // Updating the condition of the current item.
    this_object()->set_armour_hits(0);
    this_object()->set_condition(this_object()->query_condition() - 1);

    // The item grows in power.
    this_object()->set_wing_power(this_object()->query_wing_power() + 1);

    // Just to make sure it doesn't go over 60
    if(this_object()->query_ac() <= 60)
        this_object()->set_ac(this_object()->query_ac() + 1);
    
    if (worn && wearer)
            wearer->update_armour(this_object());

    if(!f_wings)
    {
        if(this_object()->query_wing_power() >= FLAMING_WINGS)
        {    
            remove_adj( ({ "shadowy", "black" }) );
            set_adj( ({ "flaming", "ethereal" }) );
            set_short("pair of flaming ethereal wings");
            set_long("Flickering, weaving under the life it was sparked into. "
            + "The glowing wings leaps and twirls in a fiery dance. "
            + "@@check_power@@\n@@black_pattern@@\n");

            f_wings = 1;

            add_prop(OBJ_I_LIGHT, bd);
            wearer->update_armour(this_object());

            wearer->remove_subloc(SUBLOC);
            wearer->add_subloc(SUBLOC, this_object());

            tell_object(wearer, "The " + this_object()->short() + " burst into fire!\n");
            tell_room(environment(wearer), "The " + QSHORT(this_object()) +
              " worn by " + QTNAME(wearer) + " burst out into "
            + "fire!!!\n", wearer);
            return 1;
        }
    }    

    // Start decaying timer, but not on the Balrog
    if(!d_timer && wearer->query_real_name() != "gash")
    {    
        if(this_object()->query_wing_power() > 0)
        {
            set_alarm(decay_timer, 0.0, &do_decay());
            d_timer = 1;
        }
    }
    return 1;

}

/*
 * Function name: arm_condition_desc
 * Description:   Returns the description of this armour
 */
string
arm_condition_desc()
{
    string str;

    if (query_prop(OBJ_I_BROKEN))
        return "The " + this_object()->short() + " have been shredded into a "
             + "million pieces.\n";

    switch(condition - repair)
    {
        case 0:
            str = "in a perfect condition";
            break;
        case 1:
            str = "in very good condition";
            break;
        case 2:
            str = "a little worn down";
            break;
        case 3:
            str = "slightly worn down";
            break;
        case 4:
            str = "somewhat ragged";
            break;
        case 5:
            str = "noticeably ragged";
            break;
        case 6:
            str = "starting to rip apart";
            break;
        case 7:
            str = "heavily ripped and torn";
            break;
        default:
            str = "in a perfect condition";
            break;
    }

    return "These wings look as if they are " + str + ".\n";
}

/*
 * Function name: check_power
 * Description  : as simple as that
*/
public string
check_power()
{

    int power = this_object()->query_wing_power();

    if(power > 10)
        power = 10;

    switch (power)
    {
    case 0:
        return "The black wings are barely visible, appearing as little " +
        "more than a shadowy outline.";
        break;
    case 1:
        return "These black wings are wrapped in shadow, as if they " +
        "are encased in a dormant darkness.";
        break;
    case 2:
        return "These wings are surrounded by black shadows which seem to " +
        "eminate a faint pulsing of raw power.";
        break;
    case 3:
        return "The black wings are surrounded by dark shadows that " +
        "dance with a life of their own.";
        break;
    case 4:
        return "Menacing shadows swirl around these black wings, almost " +
        "as if they were alive with power.";
        break; 
    case 5:
        return "Dark shadows have embraced the black wings, swirling around " +
        "them in a surge of power.";
        break;
    case 6:
        return "These wings are intensely black, almost as if there are " +
        "glowing embers burning within the dark shadows that engulf them.";
        break;
    case 7:
        return "The wings are covered with an ethereal fire which burns " +
        "with raw power.";
        break;
    case 8:
        return "A roaring ethereal flame has surrounded the wings, burning " +
        "brightly with raw energy.";
        break;
    case 9:
        return "The wings are engulfed in an ethereal flame so powerful " +
        "that their light has banished even the darkest shadow.";
        break;
    case 10:
        return "These wings are bursting with an ethereal flame so bright " +
        "that it hurts your eyes!";    
        break;                     
    }
    return "";
} 

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object on      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
string
show_subloc(string subloc, object on, object for_obj)
{
    string str, p_wing;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";

    if(this_object()->query_wing_power() >= FLAMING_WINGS)
        p_wing = "flaming ethereal";
    else
        p_wing = "black shadowy";

    if (for_obj == on)
        str = "You look ";
    else
        str = capitalize(on->query_pronoun()) + " looks ";
    return str + "cloaked with " + p_wing + " wings.\n";
}