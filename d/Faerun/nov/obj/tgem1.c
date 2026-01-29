
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../banedead.h"

inherit "/std/object";

static object trial1;


void
mk_trial1()
{
    setuid();
    seteuid(getuid());
    
    trial1 = clone_object(BANEDEAD_DIR +"temple/trials/trial1-1");
    trial1->set_outside(this_object());
}

create_object()
{
        set_name("portal");
        add_name("whirling");
        set_adj("black");
        set_short("black whirling portal");
        set_long("This is a black whirling portal, leading into a trial pocket domain.\n");
        add_prop(OBJ_I_VALUE, 800);
        add_prop(OBJ_I_WEIGHT, 500);
        add_prop(OBJ_M_NO_SELL, 1);
        add_prop(OBJ_I_NO_STEAL, "No, you cannot steal the portal.\n");
        add_prop(OBJ_M_NO_GET, "No, you cannot pick that up.\n");
        add_prop(OBJ_I_RES_MAGIC, 100);
        
        mk_trial1();

}

int
do_portal(string str)
{
	if (str != "black portal")
	{
		write("Enter <colour> portal, perhaps?\n");
		return 1;
	}
	
	write("You boldly enter the "+short()+"!\nSuddently, you are teleported elsewhere...\n");
	tell_room(trial1, this_player()->query_name() + " suddently steps out of " +
        "nowhere!\n", this_player());
        
        tell_room(environment(this_object()), this_player()->query_name() + " enters " +
        "the "+short()+"!\nThe "+short()+" collapses into itself and vanishes!\n", this_player());
                
        this_player()->move_living("M", trial1, 1);
        remove_object();
        return 1;

	
}


void
init()
{
    ::init();
    add_action(do_portal, "enter");
    //add_action(do_start, "start");
}