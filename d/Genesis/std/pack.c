/*  
 *  Standard pack code to be inherited for creating receptacles
 *  which may be filled/emptied in bulk. If this is not required,
 *  just use a standard receptacle. 
 *
 *  Configuring functions:  
 *  ----------------------
 *  set_mass_storage(int)   Turn on (1) / off (0) mass storage and retrieval 
 *                          commands.
 * 
 *  Creation function: 
 *  ------------------
 *  create_pack()
 *
 *  Example: 
 *  --------
 *  void
 *  create_pack()  
 *  {
 *      set_name("sack"); 
 *      set_adj("simple"); 
 *      set_long("A simple sack which looks as if it can hold a fair amount " +
 *               "of loot. You may use the `fill' and `empty' commands " +
 *               "on it.\n"); 
 *      set_mass_storage(1); 
 * 
 *      add_prop(OBJ_I_VALUE, 200); 
 *      add_prop(CONT_I_WEIGHT, 3000); 
 *      add_prop(CONT_I_WEIGHT, 3000); 
 *      add_prop(CONT_I_MAX_WEIGHT, 50000); 
 *      add_prop(CONT_I_MAX_VOLUME, 50000); 
 *  }
 *       
 * 
 *  NOTE: 
 *  ----- 
 *  Remember that these are receptacles so if one wants to make
 *  them recoverable, it is necessary to do the same as in 
 *  /std/receptacle, i.e.
 *
 *        string
 *        query_recover()
 *        {
 *            return MASTER + ":" + my_recover_args + 
 *                   query_container_recover();
 *        }
 * 
 *        void
 *        init_recover(string arg)
 *        {
 *            my_init_recover_code();
 *            init_container_recover(arg);
 *        }
 *
 *
 * See also /d/Genesis/std/wearable_pack.c for packs which can be configured
 * to be worn.
 *
 * 
 * Revision History:
 * ??/??/?? - Maniac  - Created
 * 06/23/97 - Shiva   - Updated and removed wear functionality (moved to 
 *                      wearable_pack.c)
 * 08/23/99 - Mercade - Added appraise_object()
 * 31/12/14 - Mercade - Moved fill status appraisal into /std/container.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/*
 * Global variable. It is not saved.
 */
static int mass_storage = 0;

/************ Storage and retrieval related functions *************/

/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
int
item_filter(object ob)
{
    return !((ob->query_prop(OBJ_M_NO_SELL)) ||
         (ob->query_prop(OBJ_M_NO_GIVE)) ||
         (ob->query_prop(OBJ_M_NO_DROP)) ||
         (!(ob->query_prop(OBJ_I_VALUE))) ||
         (ob->query_prop(CONT_I_IN)) || /* containers */
         (ob->query_worn()) || ob->query_held() || 
         (ob->query_wielded()) ||
         (ob->query_prop(LIVE_I_IS)) ||
         (ob->query_prop(OBJ_I_HAS_FIRE)) ||
         (ob->id("message")) ||
         (ob->id("note")) ||
         !CAN_SEE(this_player(), ob));
}


/*
 * set_mass_storage, allows retrieval and storage commands to work
 */
void
set_mass_storage(int w)
{
    mass_storage = w;
}

/*
 * query_mass_storage, returns whether pack has mass storage commands.
 */
int
query_mass_storage()
{
    return mass_storage;
}

/* 
 * Used in filtering out things that aren't standard packs and 
 * standard packs that don't allow mass storage, when doing parsing 
 * for "fill" and "empty". 
 */
nomask int
msp_filter(object o)
{
    return (o->query_standard_pack() &&
        o->query_mass_storage());
}

public void
pack_fill_hook(object *moved_items)
{
    if (!sizeof(moved_items)) 
    {
        write("You didn't put anything in the " + short() + ".\n");
    }
    else
    {
    	write("You store " + COMPOSITE_ALL_DEAD(moved_items) + " " + 
    	    (query_prop(CONT_I_ATTACH) ? "on" : "in") + " the " + short() + 
    	    ".\n");
        say(QCTNAME(this_player()) + " stores " + 
            COMPOSITE_ALL_DEAD(moved_items) + " " + 
            (query_prop(CONT_I_ATTACH) ? "on" : "in") + 
            " the " + QSHORT(this_object()) + ".\n");
    }
}

public int
pack_fill_fail()
{
    if (environment(this_object()) != this_player())
    {
        write("You need to get the " + short() + " first.\n");    
        return 1;
    }
    
    if (query_prop(CONT_I_CLOSED))
    {
        write("The " + short() + " is closed.\n");
        return 1;
    }

    return 0;
}

/*
 * Attempt to fill up this particular pack.
 */
public void
fill_me_pack()
{
    object *conts, *moved;
   
    if (pack_fill_fail())
    {
        return;
    }

    conts = filter(all_inventory(this_player()), item_filter);
    moved = filter(conts, not @ &->move(this_object()));

    pack_fill_hook(moved);
}

public void
pack_empty_hook(object *moved_items)
{
    if (!sizeof(moved_items))
    {
        write("You didn't retrieve anything from the " + short() + ".\n");
    }
    else
    {
    	write("You retrieve " + COMPOSITE_ALL_DEAD(moved_items) + 
            " from the " + short() + ".\n");
    	say(QCTNAME(this_player()) + " retrieves " + 
    	    COMPOSITE_ALL_DEAD(moved_items) + " from the " + 
            QSHORT(this_object()) + ".\n");
    }
}

public int
pack_empty_fail()
{
    if (environment(this_object()) != this_player())
    {
        write("You need to get the " + short() + " first.\n");    
        return 1;
    }
    
    if (query_prop(CONT_I_CLOSED))
    {
        write("The " + short() + " is closed.\n");
        return 1;
    }
  
    return 0;
}

/* 
 * Attempt to empty this particular pack 
 */
void
empty_me_pack()
{
    object *conts, *moved;
   
    if (pack_empty_fail())
    {
        return;
    }

    conts = filter(all_inventory(this_object()), item_filter);
    moved = filter(conts, not @ &->move(this_player()));

    pack_empty_hook(moved);
}

public int
pack_action(string action, string str)
{
    object *o;
    
    if (!strlen(str))
    {
        notify_fail(capitalize(action) + " what?\n");
        return 0;
    }    

    o = FIND_STR_IN_ARR(str, all_inventory(this_player()) + 
        all_inventory(environment(this_player())));

    if (!sizeof(o)) 
    {
         notify_fail(capitalize(action) + " what?\n");
         return 0;
    }

    if (sizeof(o) > 1) 
    {
        write("You can't " + action + " more than one thing at once.\n");
        return 1;
    }

    if (!msp_filter(o[0]))
    {
        write("You can't " + action + " that.\n");
        return 1;
    }

    call_other(o[0], action + "_me_pack");
    return 1;
}
    
/* 
 * An attempt to empty something. See if it is a pack that the player
 * is trying to empty. If it is, try to carry the empty out. 
 * Returns 1 if player attempted to empty a pack for which mass storage
 * was possible, 0 if s/he did not.
 */ 
nomask int
empty_pack(string str)
{
    return pack_action("empty", str);
}

/* 
 * An attempt to fill something. See if it is a pack that the player
 * is trying to fill. If it is, try to carry the fill out. 
 * Returns 1 if player attempted to fill a pack for which mass 
 * storage was possible, 0 if s/he did not.
 */ 
nomask int
fill_pack(string str)
{
    return pack_action("fill", str);
}

/* ******* Miscellaneous functions ******* */

/* 
 * This is a standard pack.
 */
nomask int
query_standard_pack()
{
    return 1;
}

/* 
 * Reject containers of any sort.  
 */
int
prevent_enter(object ob)
{
    if (ob->query_prop(CONT_I_IN))  
    {  /* containers */
         write("The " + short() + " isn't a good place for the " + 
               ob->short() + ".\n"); 
         return 1;
    } 

    return 0;
}

/******** Creation and Initialisation Functions ********/

public void
create_pack()
{
}

/*
 * Call create_pack on creation of the receptacle.
 */
nomask void
create_receptacle()
{
    create_pack();
    add_name("pack");
}

/*
 * Initialise relevant pack commands, if any 
 */
void
init()
{
     ::init();
     if (query_mass_storage()) 
     {
         add_action(fill_pack, "fill");
         add_action(empty_pack, "empty"); 
     }
} 

#if 0
/*
 * Function name: appraise_object
 * Description  : Called when a player tries to appraise this pack.
 * Arguments    : int skill - the value of the skill used.
 */
public void
appraise_object(int skill)
{
    int proc_weight;
    int proc_volume;
    int value;
    string str;

    ::appraise_object(skill);

    if (!sizeof(all_inventory()))
    {
        write("The " + short() + " is totally empty.\n");
        return;
    }

    skill = (skill ? skill : this_player()->query_skill(SS_APPR_VAL));
    skill = random((1000 / (skill + 1)), atoi(OB_NUM(this_object())));
    skill = ((skill % 2) ? -skill % 70 : skill);

    value = query_prop(OBJ_I_WEIGHT);
    proc_weight = (((100 * value) + (skill * value)) /
        query_prop(CONT_I_MAX_WEIGHT));
    value = query_prop(OBJ_I_VOLUME);
    proc_volume = (((100 * value) + (skill * value)) /
        query_prop(CONT_I_MAX_VOLUME));

    value = ((proc_weight > proc_volume) ? proc_weight : proc_volume);

    /* Should be a percentage with the highest fill value. */
    switch(value)
    {
    case -100..19: str = "almost empty"; break;
    case   20..39: str = "relatively empty"; break;
    case   40..59: str = "half full"; break;
    case   60..79: str = "moderately filled"; break;
    case   80..99: str = "nearly full"; break;
    default:       str = "completely filled";
    }

    write("The " + short() + " appears to be " + str + ".\n");
}
#endif
