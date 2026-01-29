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

#define MM_GURUQUEST   "_on_mm_quest"
#define INSTANCEKEY    "_instancekey_access"


int instance_timer = 0;

object instances_main;
string room_main;

int
create_instance()
{
	setuid();
    seteuid(getuid());
	
    instances_main = clone_object(RHOVANION_DIR +"dolguldur/instances/instances_main");

	instances_main->set_short("Inside an ancient mausoleum");
	
	instances_main->set_long("To the back is a stairwell that sticks "
	+"out above the floor due to the tilt of the mausoleum, but "
	+"still manages to allow access down. On the left side is "
	+"a crypt which has a knightly figured carved in stone "
	+"resting on the top of the sarcophagus. On the right "
	+"side is a black chapel.\n");
	
	instances_main->add_item(({ "stairwell"}), "Even with all the settling "
	+"of the main structure, the stairs provide a safe "
	+"passage down into the darkness.\n");
    
    int dice = random(4);
    
    switch (dice)
    {
        case 0:
        room_main = "/d/Gondor/rhovanion/dolguldur/mirk8";
        break;
        
        case 1:
        room_main = "/d/Gondor/rhovanion/dolguldur/mirk5";
        break;
        
        case 2:
        room_main = "/d/Gondor/rhovanion/dolguldur/mirk6";
        break;
        
        case 3:
        room_main = "/d/Gondor/rhovanion/dolguldur/mirk4";
        break;
    }

	// Default northeast entrance.	
	instances_main->set_direction(4);

    room_main->add_exit(file_name(instances_main),
    "northeast", 0, 1);
	
    instances_main->add_exit(room_main, "southwest");
	
    return 1;
}


/*
 * Function name: remove_bleed_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_instancetimer_object()
{
	room_main->remove_exit("northeast");

    remove_object();
}
 
 
 /*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
timer_instance_countdown()
{
    if (instance_timer == 10)
    {
        remove_instancetimer_object();
        
        return;
    }
     
    instance_timer = instance_timer + 1;
    
    return;
}
 
 
void
create_object()
{
	setuid();
    seteuid(getuid());
	
    set_name("_mm_instanceobject_");
    add_adj( ({"moldy"}) );
    set_short("moldy _mm_instanceobject_");
    set_long("This is a instance timer object for MM guruquest.\n");
    add_prop(OBJ_S_WIZINFO,"A MM guruquest instance timer object.\n");
                      
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
    
    set_alarm(20.0, 20.0, &timer_instance_countdown());
	set_alarm(0.1, 0.0, &create_instance());
}
























