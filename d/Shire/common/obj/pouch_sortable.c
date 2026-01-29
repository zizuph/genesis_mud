inherit "/d/Gondor/common/guild/obj/herbpouch";
inherit "/lib/keep";

#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <wa_types.h>

void
create_container()
{
    set_name("pouch");
    set_pname("pouches");
    set_short("small leather pouch");
    set_pshort("small leather pouches");
    set_adj("small");
    set_adj("leather");
    set_long("The small leather pouch is used to hold herbs. It is made of " +
        "leather and looks well worn.\n");

    add_prop(CONT_I_WEIGHT, 750); 	/* 750 grams */
    add_prop(CONT_I_MAX_WEIGHT, 2000); 	/* 2 kg      */
    add_prop(CONT_I_VOLUME, 300); 	/* 300 ml    */
    add_prop(CONT_I_MAX_VOLUME, 2000); 	/* 2 l       */

    add_prop(OBJ_I_VALUE, 48); 		/* Worth 48 cc */
    set_keep();
}



/*
 * Function name: reject_me
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
int
reject_me(object ob, object env)
{
    if (ob->move(env) == 0) 
    {  
        write("You remove "+ LANG_THESHORT(ob) +" from " + 
            LANG_THESHORT(this_object()) + ".\n"); 
        return 1; 
    } 
    return 0; 
}

/*
 * Function name: check_lasting
 * Description  : check to see if item is recoverable or autoloading
 */
void
check_lasting(object ob, object env)
{
    if (ob->check_recoverable()) 
        return;
    if (ob->query_auto_load())
        return;
    else
        reject_me(ob, env);
}

/*
 * Function name: do_sort
 * Description  : runs inventory through check_lasting.
 */
void
do_sort()
{
    map(all_inventory(this_object()), 
         &check_lasting(,environment(this_object()))); 
}

/*
 * Function name: start s
ort
 * Description  : 
 */
int
start_sort(string arg)
{
    object *ob;

    if (!stringp(arg))
    {
        notify_fail("Sort what?\n");
        return 0;
    }
    
    ob = FIND_STR_IN_OBJECT(arg, this_player());   
    if (sizeof(ob))
    {
        do_sort();       
        return 1;
    }

    notify_fail("You can't seem to sort "+ arg +".\n");
    return 0;
}


void
init()
{
    ::init();
    add_action(start_sort, "qsort");
}


