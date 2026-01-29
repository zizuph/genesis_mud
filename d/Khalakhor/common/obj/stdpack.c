/*  
 *  Coded by Maniac
 *
 *  Standard pack code to be inherited for creating receptacles
 *  which may be worn and/or filled/emptied in bulk. If neither of these
 *  things are required just use a standard receptacle. 
 *  This offers smart parsing for wear, remove, fill and empty commands, gets
 *  rid of the old problems with OBJ_M_NO_DROP when worn and offers a 
 *  standard subloc for all packs that may be worn. 
 *
 *  Configuring functions:  
 *  ----------------------
 *  set_wearable(int)          Turn on (1) / off (0) wearability.  
 *  set_mass_storage(int)      Turn on (1) / off (0) mass storage and retrieval 
 *                             commands.
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
 *      set_wearable(0); 
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
 *         }
 *
 *
*/

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define PACK_SUBLOC "_pack_subloc"



int worn = 0;
int wearable = 0; 
int mass_storage = 0;


/*
 *  CODE LAYOUT:
 *            (i)    Wear and remove related functions
 *            (ii)   Storage and retrieval related functions
 *            (iv)   Misc functions
 *            (v)    Initialisation and creation functions                 
 */



/******** Wear and remove related functions ********/

/*
 * Return whether the pack is worn or not
 */
int
query_worn()
{
    return worn;
}


/*
 * set_wearable, allows wear and remove commands to work.
 */
void
set_wearable(int w)
{
    if (w < 0) 
        w = 0;
    else if (w > 1)
        w = 1;

    wearable = w;
}


/*
 * query_wearable, returns whether pack is wearable.
 */
int
query_wearable()
{
    return wearable;
}


/* 
 * Used in filtering out things that aren't standard packs and 
 * standard packs that aren't wearable when doing parsing for 
 * "wear" and "remove".
 */
nomask int
wp_filter(object o)
{
    if (o->query_standard_pack() &&
        o->query_wearable())  
        return 1;
    else
        return 0;
}


/*
 * Attempt to wear this particular pack.
 * Returns a message, "ok" if worked, or the fail message if it didn't. 
 */
string
wear_me_pack(object tp)
{
    if (environment(this_object()) != tp)
        return "You need to get the " + short() + " first.\n";    
    
    if (worn)
        return "You are already wearing the " + short() + ".\n";
  
    if (member_array(PACK_SUBLOC, tp->query_sublocs()) > -1)
       return "There is no space on your back for the " +
                   short() + ".\n";

    /* Successful wear */
    tp->add_subloc(PACK_SUBLOC, this_object());
    tp->catch_msg("You wear the " + short() + " on your back.\n");
    tell_room(environment(tp), QCTNAME(tp) + " wears the " + 
              short() + " on " +
              tp->query_possessive() + " back.\n", tp);
    worn = 1;
    /* Do not show in ordinary inventory */
    this_object()->move(tp, PACK_SUBLOC); 
    return "ok";
}


/* 
 * Attempt to remove this particular pack 
 * Returns a message, "ok" if worked, or the fail message if it didn't. 
 */
string
remove_me_pack(object tp)
{
    if (environment(this_object()) != tp)
        return "You do not have the " + short() + ".\n";    
    
    if (!worn)
        return "You are not wearing the " + short() + ".\n";
  
    /* Successful remove */
    tp->remove_subloc(PACK_SUBLOC);
    tp->catch_msg("You remove the " + short() + ".\n");
    tell_room(environment(tp), QCTNAME(tp) + " removes the " +
              short() + ".\n", tp);
    worn = 0;
    /* Display in inventory again */
    this_object()->move(tp);   
    return "ok";
}




/* 
 * An attempt to remove something. See if it is a pack that the player
 * is trying to remove. If it is, try to carry the remove out. 
 * Returns 1 if player attempted to remove a pack, 0 if s/he did not.
 */ 
nomask int
remove_pack(string str)
{
    object tp = this_player();
    object *o;
    string s;
    
    if (!stringp(str) || (str == "all")) {
         notify_fail("Remove what?\n");
         return 0;
    }

    o = FIND_STR_IN_ARR(str, filter(all_inventory(tp) + 
                                  all_inventory(environment(tp)), wp_filter));

    if (!sizeof(o)) {
        notify_fail("Remove what?\n");
        return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't remove more than one thing from " +
                      "your back.\n");
        return 1;
    }

    if (sizeof(o) == 1) {
        s = o[0]->remove_me_pack(tp);
        if (s == "ok")
           return 1;
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
}


/* 
 * An attempt to wear something. See if it is a pack that the player
 * is trying to wear. If it is, try to carry the wear out. 
 * Returns 1 if player attempted to wear a pack, 0 if s/he did not.
 */ 
nomask int
wear_pack(string str)
{
    object tp = this_player();
    object *o;
    string s;
    
    if (!stringp(str) || (str == "all")) {
        notify_fail("Wear what?\n");
        return 0;
    }    

    o = FIND_STR_IN_ARR(str, filter(all_inventory(tp) + 
                                  all_inventory(environment(tp)), wp_filter));

    if (!sizeof(o)) {
         notify_fail("Wear what?\n");
         return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't wear more than one thing on your back.\n");
        return 1;
    }

    if (sizeof(o) == 1) {
        s = o[0]->wear_me_pack(tp);
        if (s == "ok")
           return 1;
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
}




/* Ensure here that the player removes the pack first if 
   it leaves his/her inventory.
 */
void
leave_env(object old, object dest)
{
    if (worn) {
        if (living(old)) {
            if (member_array(PACK_SUBLOC, old->query_sublocs()) > -1)
                old->remove_subloc(PACK_SUBLOC);
            old->catch_msg("You remove the " + short() + ".\n");
            tell_room(environment(old), QCTNAME(old) + " removes " +
                      "the " + short() + ".\n", old);
        }
        worn = 0;
    }
    ::leave_env(old, dest);
}




/************ Storage and retrieval related functions *************/

/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
int
item_filter(object ob)
{
    if  ((ob->query_prop(OBJ_M_NO_SELL)) ||
         (ob->query_prop(OBJ_M_NO_GIVE)) ||
         (ob->query_prop(OBJ_M_NO_DROP)) ||
         (!(ob->query_prop(OBJ_I_VALUE))) ||
         (ob->query_prop(CONT_I_IN)) || /* containers */
         (ob->query_worn()) ||
         (ob->query_wielded()) ||
         (ob->query_prop(LIVE_I_IS)) ||
         (ob->query_name() == "message"))
        return 0;
    else
	return 1;
}


/*
 * set_mass_storage, allows retrieval and storage commands to work
 */
void
set_mass_storage(int w)
{
    if (w < 0) 
        w = 0;
    else if (w > 1)
        w = 1;

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
    if (o->query_standard_pack() &&
        o->query_mass_storage())  
        return 1;
    else
        return 0;
}


/*
 * Attempt to fill up this particular pack.
 */
string
fill_me_pack(object tp)
{
    object *conts, *moved;
    int x;

    if (environment(this_object()) != tp)
        return ("You need to get the " + short() + " first.\n");    
    
    if (query_prop(CONT_I_CLOSED)) 
        return ("The " + short() + " is closed.\n");

   /* Try to fill the pack up. */
    conts = ({ });
    moved = ({ });

    conts = filter(all_inventory(tp), item_filter);
    
    for (x = 0; x < sizeof(conts); x++)
        if (!conts[x]->move(this_object()))
            moved += ({ conts[x] }) ;     /* successful move */
    
    if (!sizeof(moved)) 
        return ("You didn't put anything in the " + short() + ".\n");
    else {
        tp->catch_msg("You store " + COMPOSITE_DEAD(moved) + 
                       " in the " + short() + ".\n");
        tell_room(environment(tp), QCTNAME(tp) + " stores " + 
            COMPOSITE_DEAD(moved) + " in the " + short() + ".\n", tp);
    }

    return "ok";
}



/* 
 * Attempt to empty this particular pack 
 */
string
empty_me_pack(object tp)
{
    object *conts, *moved;
    int x;

    if (environment(this_object()) != tp)
        return "You do not have the " + short() + ".\n";    
    
    if (query_prop(CONT_I_CLOSED)) 
        return ("The " + short() + " is closed.\n");

    conts = ({ });
    moved = ({ });

    conts = filter(all_inventory(this_object()), item_filter);

    for (x = 0; x < sizeof(conts); x++)
        if (!conts[x]->move(tp)) 
            moved += ({ conts[x] }) ;     /* successful move */

    if (!sizeof(moved)) 
        return ("You didn't retrieve anything from the " + 
                     short() + ".\n");
    else {
        tp->catch_msg("You retrieve " + COMPOSITE_DEAD(moved) + 
            " from the " + short() + ".\n");
        tell_room(environment(tp), QCTNAME(tp) + " retrieves " + 
            COMPOSITE_DEAD(moved) + " from the " + short() + ".\n", tp);
    }

    return "ok";
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
    object tp = this_player();
    object *o, b;
    string s;
    
    if (!stringp(str) || (str == "all")) {
         notify_fail("Empty what?\n");
         return 0;
    }

    o = FIND_STR_IN_ARR(str, filter(all_inventory(tp) + 
                             all_inventory(environment(tp)), msp_filter)); 


    if (!sizeof(o)) {
        notify_fail("Empty what?\n");
        return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't empty more than one thing at once.\n");
        return 1;
    }

    if (sizeof(o) == 1) {
        b = o[0];
        s = b->empty_me_pack(tp);
        if (s == "ok")
           return 1;
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
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
    object tp = this_player();
    object *o, b;
    string s;
    
    if (!stringp(str) || (str == "all")) {
        notify_fail("Fill what?\n");
        return 0;
    }    

    o = FIND_STR_IN_ARR(str, filter(all_inventory(tp) + 
                             all_inventory(environment(tp)), msp_filter)); 


    if (!sizeof(o)) {
         notify_fail("Fill what?\n");
         return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't fill more than one thing at once.\n");
        return 1;
    }
        
    if (sizeof(o) == 1) {
        b = o[0];
        s = b->fill_me_pack(tp);
        if (s == "ok")
           return 1;
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
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
    if (ob->query_prop(CONT_I_IN))  {  /* containers */
         write("The " + short() + " isn't a good place for the " + 
               ob->short() + ".\n"); 
         return 1;
    } 
    return 0;
}


/* 
 * Display the pack sublocation 
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (subloc == PACK_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) + 
                " is wearing " + LANG_ADDART(short()) + " on " +
                on->query_possessive() + " back.\n";
        else
            data = "You are wearing " + LANG_ADDART(short()) + 
                   " on your back.\n";
        return data;
    }
}



/******** Creation and Initialisation Functions ********/

/*
 * Call create_pack on creation of the receptacle.
 */
nomask void
create_receptacle()
{
    this_object()->create_pack();
    add_name("pack");
}


/*
 * Initialise relevant pack commands, if any 
 */
void
init()
{
     ::init();
     if (query_mass_storage()) {
         add_action(fill_pack, "fill");
         add_action(empty_pack, "empty"); 
     }
     if (query_wearable()) {
         add_action(wear_pack, "wear");
         add_action(remove_pack, "remove");
     }
} 

