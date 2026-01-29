/* 
 * enchantment.c
 *
 * This is the base shadow for 'runtime' enchantment of objects.
 * It handles common checks, adding and removing, removing when
 * disspelled, and recovery.
 *
 * Ashlar, 31 Jul 97
 *
 * Stralle @ Genesis 040210
 *   Added allbb()
 */

#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

/* Variables */
static int gDurationAlarm;
static int gStrength;

/* Prototypes */
int dispel_magic(int magic);

/**********************************************************************
  THESE FUNCTIONS ARE INTENDED TO BE REDEFINED IN THE INHERITED OBJECT
 **********************************************************************/

/* These do not require calling of the inherited function */
string wizinfo_extra() { return "None."; }
mixed enchant_object(object obj) { return 0; }
varargs void remove_enchantment(int quiet) { }
string query_enchantment_recover() { return ""; }
void init_enchantment_recover(string arg) { }

mixed query_can_wear(object what) { return 0; }
mixed query_can_remove(object what) { return 0; }
void hook_can_wear_msg(object what) { }
void hook_can_not_wear_msg(object what) { }
void hook_can_remove_msg(object what) { }
void hook_can_not_remove_msg(object what) { }

mixed query_can_wield(object what) { return 0; }
mixed query_can_unwield(object what) { return 0; }
void hook_can_wield_msg(object what) { }
void hook_can_not_wield_msg(object what) { }
void hook_can_unwield_msg(object what) { }
void hook_can_not_unwield_msg(object what) { }

/* To redefine these, you must call the inherited function (::wear etc.) */
mixed
wear(object what)
{
	mixed s;
	if (s = query_can_wear(what))
	{
		hook_can_not_wear_msg(what);
		return s;
	}
    if (objectp(gAfObj))
        return gAfObj->wear(what);
    else
	{
		hook_can_wear_msg(what);
        return 0;
	}
}

mixed
remove(object what)
{
	mixed s;
	if (s = query_can_remove(what))
	{
	hook_can_not_remove_msg(what);
	return s;
	}
    if (objectp(gAfObj))
        return gAfObj->remove(what);
    else
	{
	hook_can_remove_msg(what);
        return 0;
	}
}

mixed
wield(object what)
{
	mixed s;
	if (s = query_can_wield(what))
	{
	hook_can_not_wield_msg(what);
	return s;
	}
    if (objectp(gAfObj))
        return gAfObj->wield(what);
    else
	{
	hook_can_wield_msg(what);
	return s;
	}
}

mixed
unwield(object what)
{
	mixed s;
	if (s = query_can_unwield(what))
	{
	hook_can_not_unwield_msg(what);
	return s;
	}
    if (objectp(gAfObj))
        return gAfObj->unwield(what);
    else
        return 0;
}

/**********************************************************************
                YOU SHOULD NOT CHANGE ANYTHING BELOW
 **********************************************************************/

/*
 * Function name: set_enchantment_duration
 * Description  : Call this to set a duration on the enchantment. If it
 *                is not set, the enchantment will only go away if dispelled
 *                or if the object is lost at reboot.
 * Arguments    : int time - the number of seconds for the duration of the
 *                  enchantment
 */
void
set_enchantment_duration(int time)
{
    if (gDurationAlarm)
    {
        remove_alarm(gDurationAlarm);
        gDurationAlarm = 0;
    }

    /* Use dispel magic so that we get a nice message for the object too */
    gDurationAlarm = set_alarm(itof(time), 0.0, &dispel_magic(100));
}

/*
 * Function name: query_enchantment_duration
 * Description  : Gives information about the duration of the enchantment.
 * Returns      : The number of seconds remaining, or -1 if the enchantment
 *                is permanent.
 */
int
query_enchantment_duration()
{
    mixed *call;
    int t;

    if (!gDurationAlarm)
        return -1;

    call = get_alarm(gDurationAlarm);
    /* Check whether the alarm really exists. /Mercade. */
    if (!sizeof(call))
    {
        gDurationAlarm = 0;
        return -1;
    }
    
    t = ftoi(call[2]);
    return (t > 0 ? t : 0);
}

string
query_enchantment_duration_string()
{
    return sprintf("%d", query_enchantment_duration());
}

/*
 * Function name: set_enchantment_strength
 * Description  : Sets the strength of the enchantment.
 * Arguments    : int strength - a number between 0 and 100, where 0 is no
 *                strength at all, and 100 is full strength, all but
 *                impossible to dispell.
 */
void
set_enchantment_strength(int strength)
{
    if (strength < 0)
        strength = 0;
    else if (strength > 100)
        strength = 100;

    gStrength = strength;
}

/*
 * Function name: query_enchantment_strength
 * Description  : Returns the strength of the enchantment.
 * Returns      : strength of the enchantment, a number between 0 and 100.
 */
int
query_enchantment_strength()
{
    return gStrength;
}

/*
 * Function name: query_enchanted
 * Description  : Returns the enchanted object
 * Returns      : the enchanted object, or 0 if the enchantment is not
 *                attached.
 */
object
query_enchanted()
{
    return objectp(query_shadow_who());
}

/*
 * Function name: enchant
 * Description  : Called to enchant an object
 * Arguments    : object obj - object to enchant
 *                int str - strength of spell used, if gStrength is not
 *                to be used.
 * Returns      : 0 if enchantment succeeded, otherwise a fail message
 */
varargs mixed
enchant(object obj, int str)
{
    string s;

    if (!objectp(obj))
    {
        return "Cannot find object.";
    }

    if (!str)
        str = gStrength;
    
    str -= obj->query_prop(MAGIC_I_RES_MAGIC);

    if (str <= 0)
    {
        return "The enchantment did not manage to affect the item.";
    }

    set_enchantment_strength(str);

    s = enchant_object(obj);

    if (!shadow_me(obj))
    {
        return "Could not attach the enchantment.";
    }
    
    if (stringp(s))
    {
        return s;
    }
    return 0;
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    // We override a few properties in this shadow
    // 1. OBJ_I_IS_MAGIC_WEAPON or OBJ_I_IS_MAGIC_ARMOUR
    // 2. MAGIC_AM_ID_INFO
    // 3. MAGIC_AM_MAGIC
    // 4. OBJ_S_WIZINFO
    // 5. OBJ_M_NO_BUY
    mixed current_value = ::query_prop(prop);
    switch (prop)
    {
    case OBJ_I_IS_MAGIC_WEAPON:
        if (IS_WEAPON_OBJECT(query_shadow_who()))
        {
            return 1;
        }
        break;
    
    case OBJ_I_IS_MAGIC_ARMOUR:
        if (IS_ARMOUR_OBJECT(query_shadow_who()))
        {
            return 1;
        }
        break;
    
    case MAGIC_AM_ID_INFO:
        return this_object()->query_identify_info();
    
    case MAGIC_AM_MAGIC:
        return ({ gStrength, "enchantment" });        
        
    case OBJ_S_WIZINFO:
        {
            string current_wiz_info = current_value ? (current_value + "\n") : "";
            current_wiz_info += 
                + "This object has been enchanted by " + file_name(this_object())
                + ". The enchantment is implemented as a shadow to the object, "
                + "which recovers if the object recovers. "
                + (query_enchantment_duration()!=-1 ? "The enchantment will last "
                + "@@query_enchantment_duration_string@@ seconds. " : "")
                + "The effects of this enchantment:\n@@wizinfo_extra@@\n");
            return current_wiz_info;
        }
        break;
    
    case OBJ_M_NO_BUY:
        return 1; // an enchanted object can't be bought/sold
    
    }
    return current_value;
}

/*
 * Function   : remove_enchantment_shadow
 * Description: Removes the shadow without removing the shadowed object.
 */
void
remove_enchantment_shadow()
{
    remove_shadow();
}

int
dispel_magic(int magic)
{
    if (magic >= gStrength)
    {
        if (gDurationAlarm)
        {
            remove_alarm(gDurationAlarm);
            gDurationAlarm = 0;
        }

        set_alarm(0.5, 0.0, remove_enchantment_shadow);
        return 1;
    }
    return 0;
}

string
query_recover()
{
    if (!stringp(query_shadow_who()->query_recover()))
        return 0;
    
    return "/d/Ansalon/guild/pot/rituals/obj/recover:" +
        query_shadow_who()->query_recover() +
        "#ENCH#" + query_enchantment_duration() + "##" +
        query_enchantment_strength() + "##" +
        MASTER + "#ENCH#";
#ifdef 0

    return MASTER + ":" + query_enchantment_duration() + "#ENCH#" +
        query_enchantment_recover() +
        "#ITEM#" + query_shadow_who()->query_recover();
#endif
}

#ifdef 0
void
init_recover(string arg)
{
    string *a;
    string earg,obarg;
    int t = -1;
    object real_ob;

    setuid();
    seteuid(getuid());

    a = explode(arg,"#ENCH#");
    arg = implode(a[1..],"#ENCH#");

    sscanf(a[0], "%d", t);

    a = explode(arg,"#ITEM#");
    arg = implode(a[1..],"#ITEM#");

    earg = a[0];

    a = explode(arg,":");
    obarg = implode(a[1..],":");

    real_ob = clone_object(a[0]);
    if (!objectp(real_ob))
        return;
    real_ob->init_recover(obarg);
    init_enchantment_recover(earg);
    if (t >= 0)
        set_enchantment_duration(t);
    enchant_object(real_ob);
}
#endif

/* Function name: allbb
 * Description:   Sends a message to interested parties
 * Arguments:     str - the message, either to the holder of the
 *                      object or everyone in the room if no holder
 *                others - the message to send to onlookers if at all
 */
varargs void
allbb(string str, string others)
{
    object env = environment(query_enchanted());

    if (!env)
        return;

    if (env->query_prop(CONT_I_IN) && !env->query_prop(ROOM_I_IS) &&
        !living(env))
        env = environment(env);

    if (living(env))
    {
        env->catch_tell(str);
        if (stringp(others))
            tell_room(environment(env), others, env);
    }
    else
    {
        tell_room(env, str);
    }
}

