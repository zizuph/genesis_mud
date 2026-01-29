
/*
     Cadet rack.  

     A container for cadets to rack stuff. 
     When anything of value is put in here, the donator will be credited 
     with droproom points corresponding roughly to the item's value. 
     Conversely, when anything of value is taken from here, the borrower 
     will be debited accordingly. 

     Some of the ideas here are from the Calian rack sorting system 
     originated by Glykron. 

     Coded by Maniac@Genesis 2/3/99

     History:

     2/3/99       Created                                    Maniac
     Various      improvements                               Maniac
     14/11/02     added cleaner check for autoloading        Maniac
 */ 

#pragma strict_types

inherit "/std/container"; 
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <stdproperties.h>
#include <macros.h> 
#include <files.h>
#include <config.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include "cadet.h"

#define DEFAULT_MAX_OBJECTS 50
#define GC_I_CONTAINER_PUT_IN_RACK "_gc_i_container_put_in_rack"
#undef DEEP_PREVENT_LEAVE

object *oblist; 
int max_objects; 


void
set_max_objects(int i)
{
    max_objects = i; 
}


int
abs(int i)
{
    return (i < 0 ? -i : i); 
}

int
query_max_objects()
{
    return max_objects; 
}


void
create_rack() 
{
}


void
create_container()
{
    set_name("rack"); 
    add_prop(CONT_I_VOLUME, 50000); 
    add_prop(CONT_I_WEIGHT, 50000); 
    add_prop(CONT_I_MAX_VOLUME, 1000000); 
    add_prop(CONT_I_MAX_WEIGHT, 1000000); 
    add_prop(OBJ_M_NO_GET, "The rack is fixed to the wall.\n"); 
    oblist = ({ }); 
    set_max_objects(DEFAULT_MAX_OBJECTS); 
    create_rack(); 
    
    // Add the Auto-Save Functionality - October 20, 2010
    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(0);
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());    
}


int
fits(object ob)
{
    return !(ob->query_prop(OBJ_I_BROKEN) || 
             living(ob) || 
             IS_COINS_OBJECT(ob)); 
}


int
value_object(object ob)
{
    return min(GC_MAX_MISC_RACK_POINTS, ob->query_prop(OBJ_I_VALUE)); 
}


private void
clean_up_rack()
{
    object ob;

    oblist = oblist - ({ 0 }); 

    if (sizeof(oblist) > query_max_objects()) { 
        ob = oblist[sizeof(oblist) - 1]; 

        if (strlen(ob->query_auto_load())) 
        { 
            if (!ob->move(environment())) 
            { 
                tell_room(environment(), 
                    "A cleaner stops by and is about to bin " + 
                    LANG_THESHORT(ob) + ", but stops after noticing " + 
                    "something unusual. He takes " + LANG_THESHORT(ob) + 
                    " from the " + short() + " and puts it on the floor.\n"); 
                return; 
            } 
        } 

        tell_room(environment(), 
                  "A cleaner stops by, gets " + LANG_THESHORT(ob) + 
                  " from the " + short() + " and bins it.\n"); 
        ob->remove_object(); 
    } 
} 


/*
 * Insert a new object into the sorted (by value) object list. 
 */
private void
rack_insert_ob(object ob)
{
    int i, j, c, v, s, vc;

    oblist = oblist - ({ 0 }); 

    if (!(s = sizeof(oblist))) {
        oblist = ({ ob }); 
        return; 
    }

    if (member_array(ob, oblist) > -1) 
        return;

    j = --s;  
    v = value_object(ob);
    i = 0; 
    c = (i + j) / 2; 
    vc = value_object(oblist[c]); 

    while (i != j) {
        if (v == vc)
            break; 
        else if (v > vc) {
            if (j == c)
                break; 
            j = c; 
            c = (i + j) / 2; 
        } 
        else {
            if (i == c)
                break; 
            i = c; 
            c = ((i + j) / 2) + ((i + j) % 2); 
        } 
        vc = value_object(oblist[c]); 
    }

    if (v > vc) 
        if (c == 0)
            oblist = ({ ob }) + oblist;  
        else 
            oblist = oblist[0 .. c - 1] + ({ ob }) + oblist[c .. s]; 
    else { 
        if (c < s) 
            oblist = oblist[0 .. c] + ({ ob }) + oblist[c + 1 .. s];
        else
            oblist = oblist + ({ ob });
    } 

    if (sizeof(oblist) > query_max_objects())
        set_alarm(0.0, 0.0, clean_up_rack); 
}


private void
rack_remove_ob(object ob)
{
    oblist = oblist - ({ ob }); 
}


int
armageddon_it()
{
    return ARMAGEDDON->shutdown_active();  
}


/* 
 * The value for borrowing an item. 
 */ 
int
cadet_obj_value_borrow(object ob)
{
    int v; 

    if (!(v = value_object(ob))) 
        return 0; 

    if (armageddon_it()) { 
        if (!(ob->check_recoverable())) 
            return 0; 
        return (v * 19) / 25; 
    } 

    return (v * 4) / 5; 
}


/* 
 * The value for donating an item. 
 */ 
int
cadet_obj_value_donate(object ob)
{
    int v; 

    if (!(v = value_object(ob))) 
        return 0;

    if (armageddon_it()) 
        return 0;

    return (v * 4) / 5; 
}


void
expel_non_recoverable_objects()
{
    int i; 
    string sh; 
    object env, *tmp;  

    if (!armageddon_it()) 
        return; 

    env = environment(); 
    sh = " falls out of the " + short() + ".\n"; 

    tmp = ({ }); 
    oblist = oblist - ({ 0 }); 
    for (i = 0; i < sizeof(oblist); i++) 
        if (!oblist[i]->check_recoverable()) 
            tmp += ({ oblist[i] }); 

    for (i = 0; i < sizeof(tmp); i++) {
        write(capitalize(LANG_THESHORT(tmp[i])) + sh); 
        tmp[i]->move(env); 
    } 
}


public void
enter_inv(object ob, object from)
{
    int val, rp; 

    ::enter_inv(ob, from); 

    rack_insert_ob(ob); 

    if (!(val = cadet_obj_value_donate(ob)) ||
        from->query_i_attacked_cadets()) 
        return; 

    rp = from->query_skill(SS_CADET_DROPROOM_POINTS); 

    from->set_skill(SS_CADET_DROPROOM_POINTS, rp + val); 

    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);    
}


public void
leave_inv(object ob, object to)
{
    int val, rp; 

    ::leave_inv(ob, to); 

    remove_rack_entry(ob);    
    rack_remove_ob(ob); 

    if (!IS_GELAN_CADET(to) || 
        !(val = cadet_obj_value_borrow(ob))) 
        return;

    rp = to->query_skill(SS_CADET_DROPROOM_POINTS); 
    rp = max(rp - val, 0);  
    to->set_skill(SS_CADET_DROPROOM_POINTS, rp); 
}


public int 
prevent_leave(object ob)
{
    object tp; 
    int v; 

    if (!objectp(tp = this_player())) 
        return 0;

    if (!IS_GELAN_CADET(tp)) {
        if (tp->query_wiz_level()) { 
            log_file("cadet_rack", 
                     tp->query_real_name() + " taking " + 
                     LANG_THESHORT(ob) + " from rack.\n"); 
            return 0;
        }
        else { 
            write("You are not a Cadet of Gelan. " +
                  "A rack guard stops you.\n"); 
            say("A rack guard prevents " + QTNAME(tp) + " from " + 
                "taking " + LANG_THESHORT(ob) + " from " + 
                "the " + short() + ".\n"); 
            return 1;
        } 
    }

    if (!(v = cadet_obj_value_borrow(ob))) 
        return 0; 

    if (tp->query_skill(SS_CADET_DROPROOM_POINTS) < v) {  
        write("You do not have enough rack points to take " +  
              LANG_THESHORT(ob) + ". A rack guard stops you.\n"); 
        say("A rack guard prevents " + QTNAME(tp) + " from " + 
            "taking " + LANG_THESHORT(ob) + " from " + 
            "the " + short() + ".\n"); 
        return 1;
    } 

    return 0;
}


public int
prevent_enter(object ob)
{
    if (fits(ob)) {
        if (sizeof(all_inventory(ob))) {
#ifndef DEEP_PREVENT_LEAVE
            if (!ob->query_prop(CONT_I_CLOSED)) {
                write(capitalize(LANG_THESHORT(ob)) + " has items " +
                      "in it. It may only be racked if it's closed.\n"); 
                return 1; 
            } 
#endif
            if (ob->query_prop(GC_I_CONTAINER_PUT_IN_RACK)) {
                ob->remove_prop(GC_I_CONTAINER_PUT_IN_RACK); 
                return 0; 
            } 
            else {
                write("A guard points out that " + LANG_THESHORT(ob) + 
                      " contains items. If you definitely want to " +
                      "donate it, he will not stop you at the next " +
                      "attempt.\n"); 

                ob->add_prop(GC_I_CONTAINER_PUT_IN_RACK, 1); 
                return 1;
            } 
        } 
        return 0; 
    } 

    write(capitalize(LANG_THESHORT(ob)) + " will not fit in the " + 
          short() + ".\n"); 
    return 1; 
}


void
leave_env(object from, object to)
{
    from->unregister_cadet_rack(this_object()); 
    ::leave_env(from, to); 
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from); 
    to->register_cadet_rack(this_object()); 
}


public void
appraise_object(int num)
{
    ::appraise_object(num); 
    write("The " + short() + " has space for " + 
          LANG_WNUM(query_max_objects()) + " items in total.\n"); 
}
