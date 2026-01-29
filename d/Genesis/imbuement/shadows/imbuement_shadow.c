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

#include <macros.h>
#include <files.h>
#include "../imbuement.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global Variables */
public int        Power_Level = 1;  /* range = 1-3 */
public int        Shadow_ID;
public int        Shadow_Num  = 0;  /* range = 1-3 */
public int        Imbuement_Hidden = 0;
public string     Imbue_ID_Info = "This item has been imbued with"
                                + " magical power of some kind!";
public string    *Add_Item_Array = ({ });
public string     Add_Item_Desc = "How utterly bizarre!\n";
public string     Nullstone_Type = ""; /* When disenchanted, what stone
                                        * is created from the mod? */

/* Prototypes */
public int               is_toplevel_imbue_shadow();
public varargs string    short(object for_obj);
public varargs string    vbfc_short(object pobj);
public string            plural_short();
public string            query_imbue_info();
public void              init_imbue_shadow(int lvl);
public int               imbue_power_chance(int lvl);
public mixed             dispel_magic(int magic, object agend = 0);
public void              add_shadow_items();
public object            get_shadow(int num);
public void              remove_object();
public void              enter_env(object to, object from);
public string            unimbue(int num);


public int        has_imbue_shadow() { return 1; }
public void       set_imbue_info(string s) { Imbue_ID_Info = s; }
public void       set_add_item_array(string *s) { Add_Item_Array = s; }
public void       set_add_item_desc(string s) { Add_Item_Desc = s; }
public string *   query_add_item_array() { return Add_Item_Array; }
public void       set_nullstone_type(string s) { Nullstone_Type = s; }
public string     query_nullstone_type() { return Nullstone_Type; }
public int        query_id() { return Shadow_ID; }
public void       set_num(int num) { Shadow_Num = num; }
public void       set_imbuement_hidden(int hid) { Imbuement_Hidden = hid; }
public int        query_imbuement_hidden() { return Imbuement_Hidden; }
public int        set_imbuement_power_level(int level) { level = max(1, min(3, level)); Power_Level = level; }
public int        query_imbuement_power_level() { return Power_Level; }
public string     query_imbuement_master_file() { return MASTER; }

public void
set_id(int id)
{
    if (!IMBUE_MASTER->check_access()) return;
    Shadow_ID = id;
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
        && strlen(shadow_who->query_prop(IMBUE_SHORT))
        && !Imbuement_Hidden)
    {
        if (member_array(calling_program(),
            ({ "d/Sparkle/clubs/rmc/room/private4.c",
               "d/Gondor/minas/rooms/mt_paint_shop.c",
               "d/Gondor/morgul/npc/gruzgh.c" })) >= 0)
            return shadow_who->short(for_obj);
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
    string ps = shadow_who->query_plural_short();
    if (is_toplevel_imbue_shadow()
        && strlen(shadow_who->query_prop(IMBUE_SHORT)) && ps)
        return shadow_who->query_prop(IMBUE_SHORT)
            + " " + shadow_who->query_plural_short();
    else
        return 0;
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
    set_imbuement_power_level(lvl);

    /* We do this with a delay to allow the child shadow to first
     * set up Add_Item_Array properly.
     */
    set_alarm(1.0, 0.0, add_shadow_items);
    
    IMBUE_LOGGER->log_shadow(Shadow_ID, Shadow_Num, file_name(this_object())
        [29..] + " created on " + (shadow_who ? file_name(shadow_who):"???"));
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
        case 2:
            return IMBUE_HIT_CHANCE_MEDIUM;
        case 3:
            return IMBUE_HIT_CHANCE_HIGH;
        default:
            return 0;
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
 *                agent - the object doing the dispelling
 * Returns:       0 - No dispelling, 1 - Object dispelled
 */
public mixed
dispel_magic(int magic, object agent = 0)
{
    object  room = environment(shadow_who);

    if (magic < shadow_who->query_magic_res(MAGIC_I_RES_MAGIC))
    {
        return 0;
    }

    IMBUE_LOGGER->log_shadow(Shadow_ID, Shadow_Num, "Dispelled by " +
        file_name(calling_object()) + " " +
        this_interactive()->query_real_name());

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
    return Nullstone_Type;
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
        send_debug_message("Shadows", "Trying to add items.");
        shadow_who->add_item(Add_Item_Array, Add_Item_Desc);
    }
    else
    {
        send_debug_message("Shadows", "No size found!");
    }
} /* add_shadow_items */


/*
 * Function name: get_shadow
 * Description:   Identify the shadow for a certain "slot"
 * Argument:      num - Slot number
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
//public int
public void
remove_object()
{
    if (!IS_CLONE)
        return;
    IMBUE_LOGGER->log_shadow(Shadow_ID, Shadow_Num, "Removed by " +
        file_name(calling_object()) + " " +
        this_interactive()->query_real_name());

    send_debug_message("Imbuement_debug", "Removing " + Shadow_ID + " " +
        file_name(this_object()) + " by " + file_name(calling_object()) + ":" +
        calling_function());
    shadow_who->remove_object();
    if (shadow_who)
        send_debug_message("Imbuement_debug", "Not removed!!");
    else
    {
        //send_debug_message("Imbuement_debug", "Removed.");
        IMBUE_GENERATOR->destructed(Shadow_ID, calling_function());
    }
    destruct();
} /* remove_object */


/*
 * Function name: query_recover
 * Description:   Replace recover string
 * Returns:       New recover string, or old if not top shadow
 */
public string
query_recover()
{
    string func = calling_function();
    object cobj = calling_object();
    if (!is_toplevel_imbue_shadow())
        return shadow_who->query_recover();

    if (member_array(func, ({ "add_auction_item", "compute_recover_str", "add_rack_entry",
        "create_auction", "populate_row_entry" })) >= 0)
    {
        //IMBUE_LOGGER->log_shadow(Shadow_ID, Shadow_Num, "Saved for recovery " +
        //    "by " + file_name(calling_object()) + " " +
        //    this_interactive()->query_real_name());
        IMBUE_GENERATOR->set_recover(Shadow_ID, shadow_who->query_recover());
        return RECOVER_OBJ + ":" + Shadow_ID;
    }

    return shadow_who->query_recover();
} /* query_recover */


/*
 * Function name: enter_env
 * Description:   Track item movement
 */
public void
enter_env(object to, object from)
{
    if (is_toplevel_imbue_shadow())
    {
        IMBUE_LOGGER->log_shadow(Shadow_ID, Shadow_Num, "Moved from " +
            (from ? (IS_PLAYER_OBJECT(from) ? 
                capitalize(from->query_real_name()) : file_name(from))
                    : "the void") + " to " +
            (to ? (IS_PLAYER_OBJECT(to) ? 
                capitalize(to->query_real_name()) : file_name(to))
                    : "the void"));
        if (Imbuement_Hidden)
        {
            shadow_who->add_adj(POWER_SHORT[Shadow_Num]);
            Imbuement_Hidden = 0;
        }
    }
    ::shadow_who->enter_env(to, from);
} /* enter_env */


/*
 * Function name: unimbue
 * Description:   Remove an imbuement. Only used by Enchanter
 * Argument:      num - slot number
 * Returns:       string - Text to show to player
 */
public string
unimbue(int num)
{
    if (!wildmatch("*"+ ENCHANTER[..-3] + "*", IMBUE_LOGGER->callers()))
    {
        IMBUE_LOGGER->log("bad_unimbue", Shadow_ID + " " + Shadow_Num +
            " " + IMBUE_LOGGER->callers() + " " +
            this_interactive()->query_real_name());
        return 0;
    }
    if (num != Shadow_Num)
        return shadow_who->unimbue(num);

    set_alarm(0.0, 0.0, remove_shadow);

    return dispel_msg_hook();
} /* unimbue */

/*
 * Function:    query_owner
 * Description: Returns the owner of this imbuement.
 */
public object
query_owner()
{
    object item = shadow_who;
    object owner = 0;

    if (find_object(MASTER_OB(this_object())) == this_object())
    {
        // Is master object, just use this_player()
        owner = this_player();
    }
    else if (IS_ARMOUR_OBJECT(item))
    {
        owner = item->query_worn();
    }
    else if (IS_WEAPON_OBJECT(item))
    {
        owner = item->query_wielded();
    }

    if (!objectp(owner))
    {
        if (living(environment(item)))
        {
            owner = environment(item);
        }
    }
   
    return owner;
}

/*
 * Function:    is_same_imbuement
 * Description: Function used for filtering out boosts that are not
 *              specifically the same as the one we're looking at.
 */
public int
is_same_imbuement(object obj)
{
    if (obj == shadow_who)
    {
        return 1;
    }
    return (MASTER == obj->query_imbuement_master_file());
}

/*
 * Function:    sort_by_power_level
 * Description: Used to topologically sort the imbuements by their power, in
 *              descending order (3 => 1)
 */
public int
sort_by_power_level(mixed a, mixed b)
{
    int a_power = (a == shadow_who ? query_imbuement_power_level() : a->query_imbuement_power_level());
    int b_power = (b == shadow_who ? query_imbuement_power_level() : b->query_imbuement_power_level());

    // Compare based on Power_Level (index == 1), sort descending
    if (a_power && b_power)
    {
        if (a_power < b_power)
        {
            return 1;
        }
        else if (a_power > b_power)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else if (a_power && !b_power)
    {
        return -1; // put a_power before b_power if it's valid
    }
    else if (!a_power && b_power)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * Function:    find_all_same_imbuement_items
 * Description: Returns all the same imbuement items that are currently
 *              active and applicable to this player. It returns an object list
 *              that is sorted by power level imbues.
 */
public object *
find_all_same_imbuement_items()
{
    object owner = query_owner();
    if (!objectp(owner))
    {
        return ({ });
    }

    object * all_worn_and_wielded = ({ });
    all_worn_and_wielded += owner->query_armour(-1);
    all_worn_and_wielded += owner->query_weapon(-1);

    object * filtered_items = filter(all_worn_and_wielded, is_same_imbuement);
    object * sorted_items = sort_array(filtered_items, sort_by_power_level);
    return sorted_items;
}

/*
 * Function:    query_imbued_indication
 * Description: This is the custom message that gets displayed on an imbued
 *              item to help identify what the particular imbuement is on
 *              the item. It is usually displayed as a part of the "long"
 *              description of the item when examined.
 *              Each imbuement base class should customize this.
 * Returns:     A string that should be displayed to the user when examining
 *              an imbued item. A newline will automatically be added at the
 *              end of the long description.
 */
public string
query_imbued_indication()
{
    return "";
}

/*
 * Function:    query_all_imbued_indications
 * Description: Builds up a string containing all the imbued indications.
 *              It doesnt just return the text for this shadow, but for
 *              all the underlying shadows as well.
 */
public string
query_all_imbued_indications()
{
    string base_imbued_indication = shadow_who->query_all_imbued_indications();
    if (!strlen(base_imbued_indication))
    {
        base_imbued_indication = "";
    }
    string imbued_indication = query_imbued_indication();
    if (!strlen(imbued_indication))
    {
        imbued_indication = "";
    }
    else
    {
        imbued_indication += "\n";
    }
    return base_imbued_indication + imbued_indication;
}

/*
 * Function name: long
 * Description  : Add our extra info to the long
 * Arguments    : string str - the pseudo-item to describe.
 *                object for_obj - the object trying to get the long.
 * Returns      : string - the description of the object or pseudo-item.
 */
varargs public mixed
long(string str, object for_obj)
{
    string long_description = shadow_who->long(str, for_obj);
    if (stringp(str))
    {
        return long_description;
    }

    string imbued_indication = query_imbued_indication();
    if (!strlen(imbued_indication))
    {
        return long_description;
    }

    return long_description + imbued_indication + "\n";
} /* long */
