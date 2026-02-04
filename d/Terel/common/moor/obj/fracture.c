/*
 * fracture.c
 *
 * A broken arm.
 * This object simulates a broken arm by occupying a toolslot until it is
 * removed.
 *
 *   Zizuph Dec 2021: changed the way the fracture worked in order to 
 *     resolve some old bugs.
 *   Lilith Feb 2022: fixed so two-handed weapon is unwielded when one
 *     of the arms is broken. Also changed order of shadow_remove() so
 *     the shadow doesn't autoload on players when the fracture has 
 *     healed.
 *   Zizuph 
 *     
 */
#pragma strict_types

inherit "/std/shadow";

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

#define FRAC_SUBLOC "_frac_subloc"

static int msg_seen = 0;

int arms;

object broken_arm_obj;

mapping heal_alarms = ([]);

public string
query_recovery() { return 0; }

public int query_broken_arms()
{
    return arms;
}

public string hold(object holdable_item)
{
    int* slots = holdable_item->query_slots();
    foreach (int slot : slots)
    {
        if (slot & arms)
        {
            return "Your arm is broken, you cannot hold the "
                + holdable_item->short() + ".\n";
        }
    }
    
    return shadow_who->hold(holdable_item);
}

public mixed query_tool(int slot)
{
    if (!broken_arm_obj)
    {
        broken_arm_obj = clone_object("/std/object");
        broken_arm_obj->set_short("broken arm");
    }
    
    //shadow_who->catch_msg("Query tool " + slot + "\n");
    if ((arms & slot) == slot)
    {
        return broken_arm_obj;
    }
    return shadow_who->query_tool(slot);
}

public string show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    string *indexes;
    int i;

    if (subloc != FRAC_SUBLOC)
	return shadow_who->show_subloc(subloc, carrier, for_obj);

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if ((arms & W_BOTH) == W_BOTH)
    {
        str = "broken left and right arms.\n";
    }
    else if ((arms & W_LEFT) == W_LEFT)
    {
        str = "a broken left arm.\n";
    }
    else
    {  
        str = "a broken right arm.\n";
    }
    

    if (for_obj == carrier)
        str = "You have " + str;
    else
	str = capitalize(carrier->query_pronoun()) + " has " + str;
    
    return str;
}

public string
cr_attack_desc(int aid)
{
    if (aid & arms)
    {
        switch(aid)
        {
            case W_RIGHT:return "right elbow";
            case W_LEFT:return "left elbow";
        }
    }
    return shadow_who->cr_attack_desc(aid);
}

void fracture_fixed(int arm)
{
    string side = (arm == W_LEFT ? "left" : "right");
    shadow_who->catch_msg("Your " + side + " arm is healed.\n");
    arms -= (arm & arms);
    if (heal_alarms[arm])
    {
        remove_alarm(heal_alarms[arm]);
        heal_alarms[arm] = 0;
    }
    if (!arms)
    {
        shadow_who->remove_subloc(FRAC_SUBLOC);
        shadow_who->remove_autoshadow(MASTER + ":");
		remove_shadow();
    }
    else
    {
        shadow_who->add_autoshadow(sprintf(
            "%s:R%d", MASTER_OB(this_object()), arms));
    }
}

public void add_fracture(int arm)
{
    object armour;
    object weapon;
    object holdable;

    string side = (arm == W_LEFT ? "left" : "right");
    if (heal_alarms[arm])
    {
        remove_alarm(heal_alarms[arm]);
        shadow_who->catch_msg("Your " + side + " arm has been rebroken!\n");
    }
    else
    {
        shadow_who->catch_msg("Your " + side + " arm has been broken!\n");
    }

    // Bye bye weapon.
    if ((weapon = shadow_who->query_weapon(arm))) {
	    weapon->remove_broken();
        weapon->unwield_me();
    }    

    // Two handers too.
    if ((weapon = shadow_who->query_weapon(W_BOTH))) {
	    weapon->remove_broken();
        weapon->unwield_me();
    }    
    
    // So long shield.
    if ((armour = shadow_who->query_armour(arm))) {
	if (MASTER_OB(armour) != MASTER_OB(TO)) {
	    armour->remove_broken();
	    armour->remove_me();
	}
    }
    
    // Wand be gone.
    if ((holdable = shadow_who->query_tool(arm)))
    {
        if (holdable->query_holdable_item())
        {
            shadow_who->catch_msg("Your " + holdable->short() +
               " is broken as well.\n");
            holdable->command_release();
            holdable->add_prop(OBJ_I_BROKEN, 1);
        }
    }
    
    // Unarmed enhancer no more.
    object* armours = shadow_who->query_armour(-1);
    foreach (object armour : armours)
    {
        int* ids = armour->query_enhanced_attack_ids();
        foreach (int id : ids)
        {
            if (id & arm)
            {
                armour->remove_broken();
                armour->remove_me();
            }
        }
    }

    if (!arms)
    {
        shadow_who->add_subloc(FRAC_SUBLOC, TO);
    }
    arms |= arm;
    shadow_who->add_autoshadow(sprintf(
        "%s:R%d", MASTER_OB(this_object()), arms));
    heal_alarms[arm] = set_alarm(3600.0, 0.0, &fracture_fixed(arm));
}

public int apply_fracture(object victim, int arm)
{
    setuid();
    seteuid(getuid());
    if (victim->query_broken_arms())
    {
        victim->add_fracture(arm);
        return 1;
    }
    object shadow = clone_object(MASTER_OB(this_object()));
    shadow->shadow_me(victim);
    victim->add_fracture(arm);
    return 1;
}

public void
autoload_shadow(mixed arg)
{
	setuid();
	seteuid(getuid());
    int redo_arms;
    if (sscanf(arg,"R%d", redo_arms))
    {
        ::autoload_shadow(arg);
        if (redo_arms & W_LEFT)
        {
            add_fracture(W_LEFT);
        }
        if (redo_arms & W_RIGHT)
        {
            add_fracture(W_RIGHT);
        }
    }
}
