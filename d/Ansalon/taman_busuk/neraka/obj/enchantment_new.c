/* 
 * enchantment.c
 *
 * This is the base shadow for 'runtime' enchantment of objects.
 * It handles common checks, adding and removing, removing when
 * disspelled, and recovery.
 *
 * Ashlar, 31 Jul 97
 */

#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define ET_WEAPON   1
#define ET_ARMOUR   2
#define ET_OBJECT   4

/* Things about the object that is saved */
static string gWizinfo;
static mixed gNoBuy;
static object gAfObj;
/* Variables */
static object gEnchanted;
static int gDurationAlarm;
static int gStrength;
static int gObjectType;

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
    gDurationAlarm = set_alarm(itof(time),0.0,&dispel_magic(100));
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
    t = ftoi(call[2]);
    return (t > 0 ? t : 0);
}

string
query_enchantment_duration_string()
{
    return sprintf("%d",query_enchantment_duration());
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
    return gEnchanted;
}

/*
 * Function name: query_enchanted_object_type
 * Description  : Returns the type of the enchanted object
 * Returns      : the enchanted object, or 0 if the enchantment is not
 *                attached.
 */
int
query_enchanted_object_type()
{
    return gObjectType;
}

/*
 * Function name: remove_all_extra
 * Description  : Removes every enchanting effect from the object
 * Arguments    : object obj - The object to de-enchant.
 */
void
remove_all_extra(object obj)
{
    int lock;
    
    lock = obj->query_lock();
    if (lock)
        obj->set_lock(0);

    switch (gObjectType)
    {
        case ET_WEAPON:
            obj->set_wf(gAfObj);
            obj->remove_prop(OBJ_I_IS_MAGIC_WEAPON);
            break;
        case ET_ARMOUR:
            obj->set_af(gAfObj);
            obj->remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
            break;
    }
    if (stringp(gWizinfo))
        obj->add_prop(OBJ_S_WIZINFO, gWizinfo);
    else
        obj->remove_prop(OBJ_S_WIZINFO);
    obj->remove_prop(MAGIC_AM_ID_INFO);
    obj->remove_prop(MAGIC_AM_MAGIC);

    if (gNoBuy)
        obj->add_prop(OBJ_M_NO_BUY, gNoBuy);
    else
        obj->remove_prop(OBJ_M_NO_BUY);

    catch(remove_enchantment());

    if (lock)
        obj->set_lock(lock);

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
    int lock;
    string s;

    if (!objectp(obj))
    {
        return "Cannot find object.";
    }
    
    if (obj->query_prop(OBJ_I_IS_MAGIC_ARMOUR)  ||
        obj->query_prop(OBJ_I_IS_MAGIC_WEAPON)  ||
        obj->query_prop(MAGIC_AM_ID_INFO)       ||
        obj->query_prop(MAGIC_AM_MAGIC))
    {
        return "Cannot enchant magic items.";
    }

    if (!str)
        str = gStrength;
    
    str -= obj->query_prop(MAGIC_I_RES_MAGIC);

    if (str <= 0)
    {
        return "The enchantment did not manage to affect the item.";
    }

    set_enchantment_strength(str);

    /* If the object is locked from changes, we must unlock it. */
    lock = obj->query_lock();
    if (lock)
        obj->set_lock(0);

    /* Find out what manner of object this is */
    switch (function_exists("create_object", obj))
    {
        case "/std/weapon":
            gObjectType = ET_WEAPON;
            gAfObj = obj->query_wf();
            obj->set_wf(this_object());
            obj->add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
            break;
        case "/std/armour":
            gObjectType = ET_ARMOUR;
            gAfObj = obj->query_af();
            obj->set_af(this_object());
            obj->add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            break;
        default:
            gObjectType = ET_OBJECT;
    }

    gWizinfo = obj->query_prop(OBJ_S_WIZINFO);
    obj->add_prop(OBJ_S_WIZINFO, (gWizinfo ? (gWizinfo + "\n") : "") +
        "This object has been enchanted by " + file_name(this_object()) +
        ". The enchantment is implemented as a shadow to the object, " +
        "which recovers if the object recovers. " +
        (query_enchantment_duration()!=-1 ? "The enchantment will last " +
        "@@query_enchantment_duration_string@@ seconds. " : "") +
        "The effects of this enchantment:\n@@wizinfo_extra@@\n");
    obj->add_prop(MAGIC_AM_ID_INFO,
        ({ "This object has been magically altered.\n", 1 }));
    obj->add_prop(MAGIC_AM_MAGIC,
        ({ "enchantment", str }));

    gNoBuy = obj->query_prop(OBJ_M_NO_BUY);
    obj->add_prop(OBJ_M_NO_BUY, 1);

    s = enchant_object(obj);

    if(lock)
        obj->set_lock(lock);

    gEnchanted = obj;
    
    if (!shadow_me(obj))
    {
        remove_all_extra(obj);
        return "Could not attach the enchantment.";
    }
    if (stringp(s))
    {
        remove_all_extra(obj);
        return s;
    }
    return 0;
}

/*
 * Function   : remove_shadow
 * Description: Removes the shadow without removing the shadowed object.
 */
void
remove_shadow()
{
    object obj;

    obj = query_shadow_who();
    if (!objectp(obj))
        return ::remove_shadow();

    remove_all_extra(obj);

    ::remove_shadow();
}

void
remove_object()
{
    /* Since remove_enchantment removes any effect on the player, we
       must call it, but tell it to be quiet. */
    remove_enchantment(1);
    ::remove_object();
}

int
dispel_magic(int magic)
{
    object e;
    if (magic >= gStrength)
    {
        set_alarm(0.5,0.0,remove_shadow);
        return 1;
    }
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_enchantment_duration() + "#ENCH#" +
        query_enchantment_recover() +
        "#ITEM#" + query_shadow_who()->query_recover();
}

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


