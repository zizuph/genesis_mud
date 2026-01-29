/*  Created 6/2/95 by Maniac.
 *
 *  Standard backpack code to be inherited for creating receptacles
 *  which may be worn. 
 *
 *  Remarks:
 *     This offers smart parsing for wear and remove commands, gets
 *     rid of the old problems with OBJ_M_NO_DROP in backpacks,
 *     and offers a standard subloc for all backpacks that use it.
 *     Remember that these are receptacles so if one wants to make
 *     them recoverable, it is necessary to do the same as in 
 *     /std/receptacle, i.e.
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


inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define BACKPACK_SUBLOC "_backpack_subloc"
#define FILTER_BACKPACKS(tp) \
        filter(all_inventory(tp) + all_inventory(environment(tp)), \
               "b_filter", this_object())

int worn;


int
is_worn()
{
    return worn;
}

void
create_receptacle()
{
    this_object()->create_backpack();
}


/* move_from, send container back into player's main inventory */
void
move_from(object ob, object from)
{
    if (interactive(from))
        from->catch_msg("The " + short() + " rejects the " + 
                        ob->short() + ".\n");
    ob->move(from);
}


/* Reject containers of any sort */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_prop(CONT_I_IN))  /* containers */
        set_alarmv(1.0, 0.0, "move_from", ({ ob, from }) );
}



/* Attempt to wear this specific backpack.
*/
nomask string
wear_me_backpack(object tp)
{
    if (environment(this_object()) != tp)
        return "You need to get the " + short() + " first.\n";    
    
    if (worn)
        return "You are already wearing the " + short() + ".\n";
  
    if (member_array(BACKPACK_SUBLOC, tp->query_sublocs()) > -1)
       return "There is no space on your back for the " +
                   short() + ".\n";

    /* Successful wear */
    tp->add_subloc(BACKPACK_SUBLOC, this_object());
    tp->catch_msg("You wear the " + short() + " on your back.\n");
    tell_room(environment(tp), QCTNAME(tp) + " wears the " + 
              short() + " on " +
              tp->query_possessive() + " back.\n", tp);
    worn = 1;
    /* Do not show in ordinary inventory */
    this_object()->set_no_show_composite(1); 
    return "ok";
}


/* Attempt to remove this particular backpack */
nomask string
remove_me_backpack(object tp)
{
    if (environment(this_object()) != tp)
        return "You do not have the " + short() + " .\n";    
    
    if (!worn)
        return "You are not wearing the " + short() + ".\n";
  
    /* Successful remove */
    tp->remove_subloc(BACKPACK_SUBLOC);
    tp->catch_msg("You remove the " + short() + ".\n");
    tell_room(environment(tp), QCTNAME(tp) + " removes the " +
              short() + ".\n", tp);
    worn = 0;
    /* Display in inventory again */
    this_object()->set_no_show_composite(0);  
    return "ok";
}


/* To filter out backpacks */
nomask int
b_filter(object o)
{
    if (o->is_standard_backpack())  
        return 1;
    else
        return 0;
}


nomask int
is_standard_backpack()
{
    return 1;
}


/* An attempt to remove something, see if it is a backpack, if so
   try to carry it out. Returns 1 for success, 0 for failure.
 */ 
nomask int
remove_backpack(string str)
{
    object tp = this_player();
    object *o, b;
    string s;
    
    if (!str || (str == "all")) {
         notify_fail("Remove what?\n");
         return 0;
    }

    o = FIND_STR_IN_ARR(str, FILTER_BACKPACKS(tp));

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
        b = o[0];
        s = b->remove_me_backpack(tp);
        if (s == "ok")
           return 1;
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
}


/* An attempt to wear something, see if it is a backpack, if so
   try to carry it out. Returns 1 for success, 0 for failure.
 */ 
nomask int
wear_backpack(string str)
{
    object tp = this_player();
    object *o, b;
    string s;
    
    if (!str || (str == "all")) {
        notify_fail("Wear what?\n");
        return 0;
    }    

    o = FIND_STR_IN_ARR(str, FILTER_BACKPACKS(tp));

    if (!sizeof(o)) {
         notify_fail("Wear what?\n");
         return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't wear more than one thing on your back.\n");
        return 1;
    }

    if (sizeof(o) == 1) {
        b = o[0];
        s = b->wear_me_backpack(tp);
        if (s == "ok")
           return 1;
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
}



/* Ensure here that the player removes the backpack first if 
   it leaves his/her inventory.
 */
void
leave_env(object old, object dest)
{
    if (worn) {
        if (old && living(old)) {
            if (member_array(BACKPACK_SUBLOC, old->query_sublocs()) > -1)
                old->remove_subloc(BACKPACK_SUBLOC);
            old->catch_msg("You remove the " + short() + ".\n");  
            if (environment(old) == dest)
                tell_room(dest, QCTNAME(old) + " removes " +
                          "the " + short() + ".\n", old);
        }
        this_object()->set_no_show_composite(0);
        worn = 0;
    }
    ::leave_env(old, dest);
}


/* Display the backpack sublocation */
public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (subloc == BACKPACK_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) + 
                " is wearing a " + short() + " on " +
                on->query_possessive() + " back.\n";
        else
            data = "You are wearing a " + short() + 
                   " on your back.\n";
        return data;
    }
}



void
init()
{
     ::init();
     add_action("wear_backpack", "wear");
     add_action("remove_backpack", "remove");
} 
