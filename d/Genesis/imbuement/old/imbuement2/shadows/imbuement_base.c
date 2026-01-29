/*
 *  /d/Genesis/imbuement/shadows/imbuement_shadow.c
 *
 *  This is the base file to be inherited by all shadows which are used 
 *  to modify items based on the random dice rolls performed by the
 *  imbuement_generator.c file.
 *
 *  Created November 2009 by Cooper Sherry (Gorboth) and Petros
 */
#pragma strict_types

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "../imbuement.h"

/* Global Variables */
public int        Power_Level = 1;  /* range = 1-3 */
public int        Shadow_ID;
public int        Shadow_Num  = 0;  /* range = 1-3 */
public string     Imbue_ID_Info = "This item has been imbued with"
                                + " magical power of some kind!";
public string    *Add_Item_Array = ({ });
public string     Add_Item_Desc = "How utterly bizarre!\n";

/* Prototypes */
public int               is_toplevel_imbue_shadow();
public varargs string    short(object for_obj);
public varargs string    vbfc_short(object pobj);
public string            plural_short();
public string            query_imbue_info();
public void              init_imbue_shadow(int lvl);
public int               imbue_power_chance(int lvl);
public int               dispel_magic(int magic);
public void              add_shadow_items();
public object            get_shadow(int num);
public int               remove_object();
public string            query_recover();


public void       set_imbue_info(string s) { Imbue_ID_Info = s; }
public void       set_add_item_array(string *s) { Add_Item_Array = s; }
public void       set_add_item_desc(string s) { Add_Item_Desc = s; }
public string *   query_add_item_array() { return Add_Item_Array; }
public void       set_id(int id) { Shadow_ID = id; }
public void       set_num(int num) { Shadow_Num = num; }


public int
has_imbue_shadow()
{
    return 1;
}

public void
remove_imbue_shadow()
{
    remove_shadow();
}


/*
 * Function name: is_toplevel_imbue_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       int - 1 if this is the top level shadow
 *                      0 otherwise
 */
public int
is_toplevel_imbue_shadow()
{
    object * imbue_shadows = ({ });
    object me = shadow_who;
    if (!me)
        return 0;
    while (me = shadow(me, 0))
    {
        if (wildmatch(SHADOW_DIR + "*", file_name(me)))
        {
            imbue_shadows += ({ me });
        }
    }

    if (file_name(this_object()) ==
        file_name(imbue_shadows[sizeof(imbue_shadows) - 1]))
    {
        return 1;
    }
    
    return 0;    
} /* is_toplevel_imbue_shadow */


/*
 * Function name: short
 * Description  : The short description. We only add the adjective
 *                if this is the top level shadow to avoid a double
 *                adjective problem.
 * Arguments    : object for_obj - the object that wants to know.
 * Returns      : string - the description.
 */
public varargs string
short(object for_obj)
{
    if (is_toplevel_imbue_shadow()
        && strlen(shadow_who->query_prop(IMBUE_SHORT)))
    {
        return shadow_who->query_prop(IMBUE_SHORT) + " "
            + shadow_who->short(for_obj);
    }
        
    return shadow_who->short(for_obj);
} /* short */


/*
 * Function name:   vbfcshort
 * Description:     Gives short as seen by previous_object
 * Returns:         string holding short()
 * Arguments:       pobj: Object which to make the relation for
 *                  if not defined we assume that we are doing a vbfc
 *                  through the vbfc_object
 */
public varargs string
vbfc_short(object pobj)
{
    return short(pobj);
} /* vbfc_short */


/*
 * Function name:        plural_short
 * Description  :        provide a modified plural short description for
 *                       the imbued item
 * Returns      :        string - the plural short description
 */
public string
plural_short()
{
    return shadow_who->query_prop(IMBUE_SHORT)
      + " " + shadow_who->query_plural_short();
} /* plural_short */


/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return Imbue_ID_Info + "\n";
} /* query_imbue_info */


/*
 * Function name:        init_imbue_shadow
 * Description  :        Called when the shadow is first moved to the
 *                       item so that certain processes can be begun
 *                       and initializations set.
 * Arguments    :        int lvl - the power level of the imbuement.
 *                                 Range: 1-3
 */
public void
init_imbue_shadow(int lvl)
{   
    Power_Level = lvl;

    /* We do this with a delay to allow the child shadow to first
     * set up Add_Item_Array properly.
     */
    set_alarm(1.0, 0.0, add_shadow_items);
} /* init_imbue_shadow */


/*
 * Function name:        imbue_power_chance
 * Description  :        Assign the likelihood that the power given by
 *                       this imbuement will trigger on any given roll.
 * Arguments    :        int lvl - the power level of the imbuement
 * Returns      :        int - the chance (in terms of %)
 */
public int
imbue_power_chance(int lvl)
{
    switch (lvl)
    {
        case 1:
            return IMBUE_HIT_CHANCE_LOW;
            break;
        case 2:
            return IMBUE_HIT_CHANCE_MEDIUM;
            break;
        case 3:
            return IMBUE_HIT_CHANCE_HIGH;
            break;
        default:
            return 0;
            break;
    }

    return 0; /* should never happen, but just in case. */
} /* imbue_power_chance */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "There is a brief flash of magic, and the " + shadow_who->short()
      + " loses its " + shadow_who->query_prop(IMBUE_SHORT)
      + " appearance.\n";
} /* dispel_msg_hook */


/*
 * Function name: dispel_magic
 * Description:   Function called by a dispel spell
 * Argument:      magic - How strong the dispel is
 * Returns:       0 - No dispelling, 1 - Object dispelled
 */
public int
dispel_magic(int magic)
{
    object  room = environment(shadow_who);

    if (magic < shadow_who->query_magic_res(MAGIC_I_RES_MAGIC))
    {
        return 0;
    }

    if (living(room))
    {
        room = environment(room);
    }

    tell_room(room, dispel_msg_hook());

    /* We get rid of the items that have been added specifically due
     * to the outward appearance of this imbuement.
     */
    foreach(string additem : Add_Item_Array)
    {
        shadow_who->remove_item(additem);
    }

    remove_shadow();
    return 1;
} /* dispel_magic */


/*
 * Function name:        add_shadow_items
 * Description  :        We want the things mentioned by the description 
 *                       of the mod to be examinable by players. Thus,
 *                       we add those items (as specified by the specific
 *                       child shadow using set_add_item_array()) here.
 *                       If dispel_magic() should be called, they will
 *                       be removed from that function.
 */
public void
add_shadow_items()
{
    if (sizeof(Add_Item_Array))
    {
        TELL_G("Trying to add items.");
        shadow_who->add_item(Add_Item_Array, Add_Item_Desc);
    }
    else
    {
        TELL_G("No size found!");
    }
} /* add_shadow_items */


/*
 * Function name: get_shadow
 * Description:   Identify the shadow for a certain "slot"
 * Argument:      magic - How strong the dispel is
 * Returns:       object of shadow
 */
public object
get_shadow(int num)
{
    if (num == Shadow_Num)
        return this_object();
    return shadow_who->get_shadow(num);
} /* get_shadow */


/*
 * Function name: remove_object
 * Description:   Update master when removing shadow if removal is
                    unexpected (object being destructed)
 * Returns:       object of shadow
 */
public int
remove_object()
{
    if (is_toplevel_imbue_shadow())
    {
        IMBUE_MASTER->destructed(Shadow_ID, calling_function());
    }
    return shadow_who->remove_object();
} /* remove_object */


/*
 * Function name: query_recover
 * Description:   Replace recover string
 * Returns:       New recover string, or old if not top shadow
 */
public string
query_recover()
{
    if (is_toplevel_imbue_shadow())
    {
        if (calling_function() == "compute_recover_str")
        {
            IMBUE_MASTER->set_recover(Shadow_ID, shadow_who->query_recover());
            return RECOVER_OBJ + ":" + Shadow_ID;
        }
    }
    return shadow_who->query_recover();
} /* query_recover */


