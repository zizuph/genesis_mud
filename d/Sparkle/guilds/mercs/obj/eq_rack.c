/* 
 * Mercenary racks, by Morrigan 11/2001
 *
 * Adapted from code by Gwyneth from July 1999 
 *
 * Modified by Eowul on 20-9-2003 to add the rack shadow instead of just the
 *      property.
 *
 */
inherit "/std/container";

#include "../merc.h"

static int recovering; 

void
create_container()
{
    set_name("chest");
    add_name("rack");
    add_name("_merc_guild_weapon_rack_");
    add_adj("weapon");
    set_short("weapon chest");
    set_long("A black wooden chest, adorned with the emblem of a red dragon. "+
	"Mercenaries can place their equipment for use by other mercenaries. "+
	"The word 'weapon' has been painted into the side.\n");

    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The rack is impossible to carry.\n");
}

void
rack_get(object ob, object to, string equip)
{
    write("A mercenary scowls at you, and you replace the " + equip + ".\n");
    say("A mercenary scowls at "+QTNAME(to)+", and "+PRONOUN(to)+
        " replaces the "+
	equip + ".\n");
    ob->move(this_object());
}

void
leave_inv(object ob, object to)
{
    int skill, new_value;

    /* Name of the borrower */
    string name = capitalize(to->query_real_name()); 

    /* Short desc of the object being borrowed. */
    string equip = ob->short(); 

    /* Add this to prevent endless loops */
     if (ob->query_prop("_merc_rack_reject"))
     {
        ob->remove_prop("_merc_rack_reject");
        return;
     }

    if (!interactive(to))
    {
        ::leave_inv(ob, to);
        return;
    }

    ::leave_inv(ob, to);

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
        new_value = F_VALUE_WEAPON(ob->query_hit(), ob->query_pen());

    /* Calculate values for armours depending on its ac. */
    if (function_exists("create_armour", ob))
        new_value = F_VALUE_ARMOUR(ob->query_ac());

    /* Tally depending on what has been put into and taken out of the rack. */
    skill = to->query_skill(SS_MERC_RACK);
    
    /* If it's not armageddon, and the borrower doesn't have
       enough in his tally, he can't borrow anything. */
    if (!ARMAGEDDON->shutdown_active() && skill < new_value)
        set_alarm(0.1, 0.0, &rack_get(ob, to, equip));

    /* If it's not armageddon, decrease the tally by the calculated
       value of an object. */
    if (!(ARMAGEDDON->shutdown_active()))
        to->set_skill(SS_MERC_RACK, to->query_base_skill(SS_MERC_RACK) -
            new_value);
}

void
enter_inv(object ob, object from)
{
    int     new_value;
    string  name = capitalize(from->query_real_name()); 
    string  equip = ob->short(); 
    object  shadow;

    if (!interactive(from))
    {
        ::enter_inv(ob, from);
        return;
    }

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
        new_value = F_VALUE_WEAPON(ob->query_hit(), ob->query_pen());

    /* Calculate values for armours depending on its ac. */
    if (function_exists("create_armour", ob))
        new_value = F_VALUE_ARMOUR(ob->query_ac());

    /* If it's not armageddon, raise the tally by the calculated value. */
    if (!ARMAGEDDON->shutdown_active()) 
    from->set_skill(SS_MERC_RACK, from->query_base_skill(SS_MERC_RACK) + 
        new_value);

    // Check if we placed the mark of the armoury
    if(!ob->query_mercenary_rack_shadow())
    {
        // Create the shadow and add it to the equipment
        seteuid(getuid());
        shadow = clone_object(MOBJ + "rack_shadow");
        shadow->shadow_me(ob);
    }

    ::enter_inv(ob, from);
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int prevent_enter(object ob)
{
    // Check if the object entering is a piece of armour
    if (!IS_WEAPON_OBJECT(ob))
    {
        // Not allowed to enter
	    write("The "+ob->short()+" does not belong in the "+
	        this_object()->short()+"!\n");
        return 1;
    }


    // Return the original value
    return ::prevent_enter(ob);
}