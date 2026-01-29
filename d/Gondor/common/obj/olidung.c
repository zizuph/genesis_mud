/*  
 *  /d/Gondor/common/obj/olidung.c
 *  Dung from the oliphaunts.
 *
 *  29 June 01, Serif.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/sys/stdproperties.h";

int decay_time;		
int simple_names;	

static private int decay_alarm;

public void decay_fun();

/* prototype */
int
get_test()
{
    if (this_player()->query_prop("IS_HARADRIM"))
        return 1;
    else
        return 0;
}

public void
create_leftover()
{
   set_name("pile of dung");
   add_name("manure");
   add_name("poop");
   add_name("dung");
   add_name("_oli_dung_");
   add_name("pile");
   add_pname("piles");
   add_adj("oliphaunt");
   add_adj("large");
   add_adj("stinking");
   set_short("large pile of dung");
   set_pshort("large piles of dung");
   set_long("This is a rather large pile of dung from an oliphaunt. It gives "
       + "off a mildly fetid odor and is still moist.\n");
   add_prop(OBJ_I_WEIGHT,9000+random(1000));
   add_prop(OBJ_I_VOLUME,13000+random(2500));
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_INVIS, &get_test());

}

public nomask void
create_food() 
{ 
    simple_names = 0;
    decay_time = 3600+random(400);
    set_amount(9000+random(200));
    create_leftover();
}

public void
set_decay_time(int time)
{
    decay_time = time;
}

public int
query_decay_time()
{
    return decay_time;
}

public void 
enter_env(object dest, object old) 
{
    ::enter_env(dest, old);

    remove_alarm(decay_alarm);
    if (IS_ROOM_OBJECT(dest))
    {
	decay_alarm = set_alarm(1.0, 0.0, decay_fun);
    }
}

public void
decay_fun()
{
    if (--decay_time)
    {
	decay_alarm = set_alarm(60.0, 0.0, decay_fun);
    }
    else
    {
        tell_room(environment(this_object()),
	    capitalize(LANG_THESHORT(this_object())) +
            " slowly " + ((num_heap() == 1) ? "decays" : "decay") 
	        + " into dust.\n");
	remove_object();
    }
}
