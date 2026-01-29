/* 
 * 
 * Nerull 2021
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/rhovanion/defs.h"

inherit "/std/object.c";

#define MM_GURUQUEST      "_on_mm_quest"
#define FOUND_MM_BOOK     "_found_mm_book"

int fail_timer = 0;


/*
 * Function name: remove_bleed_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_failtimer_object()
{
    environment(this_object())->catch_tell("The Dark Lord finally destroys "
    +"you for failing the quest!\n");
     
    tell_room(environment(environment(this_object())), environment(this_object())->query_name()
    +" suddenly dies!\n", environment(this_object()));
    
    environment(this_object())->remove_prop(MM_GURUQUEST);
    environment(this_object())->remove_prop(FOUND_MM_BOOK);
    
    environment(this_object())->set_hp(0);
    environment(this_object())->do_die(this_object());
    
    remove_object();
}
 
 
 /*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
timer_effect()
{
    switch(fail_timer)
    {
        case 1:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 1\n");
        break;
        case 2:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 2\n");
        break;
        case 3:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 3\n");
        break;
        case 4:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 4\n");
        break;
        case 5:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 5\n");
        break;
        case 6:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 6\n");
        break;
        case 7:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 7\n");
        break;
        case 8:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 8\n");
        break;
        case 9:
        environment(this_object())->catch_tell("The Dark Lord is growing "
        +"impatient! You better hurry! 9\n");
        break;
        case 10:
        break;
    }
    
    if (fail_timer == 10)
    {
        remove_failtimer_object();
        
        return;
    }
     
    fail_timer = fail_timer + 1;
    
    return;
}
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_object()
{
	setuid();
    seteuid(getuid());
	
    set_name("_mm_timerobject1_");
    add_adj( ({"moldy"}) );
    set_short("moldy _mm_timerobject1_");
    set_long("This is a timerobject for MM guruquest.\n");
    add_prop(OBJ_S_WIZINFO,"A MM guruquest timer object.\n");
                      
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    add_prop(OBJ_I_INVIS, 100);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    
    set_no_show();
    
    set_alarm(20.0, 20.0, &timer_effect());
}
























