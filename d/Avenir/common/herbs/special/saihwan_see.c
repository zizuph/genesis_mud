// saihwan_see
inherit "/std/object";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void stop_see();
int    time,       /* How long it will be in effect */
       increase;       /* the value added to the property */
void
create_object()
{
    set_long("saihwan seeing allows people to see invsisble.\n");
    set_short("saihwan seeing");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();

    time = 1;
    increase = 1;
}

/*
 * Function name: init
 * Description:   Called when this object 'gets in touch' with another object
 */
void
init()
{
    ::init();
    add_prop(LIVE_I_SEE_INVIS, ({ increase, 1}) );
    write("Either you are hallucinating, or you now have the ability to see "+
        "things that you were previously unable to more clearly.\n");

    if (time)
	set_alarm(itof(time), 0.0, stop_see);
}


/*
 * Function name: set_time
 * Description:   How long this will hold
 */

void set_time(int i) { time = i; }

/*
 * Function name: set_increase
 * Description:   Set how strong this property is
 */
void set_increase(int i) { increase = i; }

/*
 * Function name: query_increase
 * Description:   Query how strong this property is
 */
int query_increase() { return increase; }

/*
 * Function name: enter_env
 * Description:   Called each time this object enters another environment
 * Arguments:     to   - The object this object enters
 *		  from - The object this object leaves
 */
void
enter_env(object to, object from)
{
   int increase;
   increase = 1 + random(4);        // FIVE levels maxmimum 

   set_increase(increase);
    if (living(to) && (to->query_prop(LIVE_I_SEE_INVIS) < 38))
       // Won't go higher than 40
       to->add_prop(LIVE_I_SEE_INVIS, to->query_prop(LIVE_I_SEE_INVIS) + increase);

    ::enter_env(to, from);
}

/*
 * Function name: leave_env
 * Description:   Called when this object is moved from another object
 * Arguments:     from - The object this object is moved from
 *		  to   - The object to which this object is being moved
 */
void
leave_env(object from, object to)
{
    if (living(from))
      	from->add_prop(LIVE_I_SEE_INVIS, 
              from->query_prop(LIVE_I_SEE_INVIS) - query_increase());
    if (from->query_prop(LIVE_I_SEE_INVIS) < 0)
        from->remove_prop(LIVE_I_SEE_INVIS);     

    ::leave_env(from, to);
}


/*
 * Function name: stop_see
 * Description:   If the prop is time dependent this function will
 *		  called when it's time to remove this prop
 */
void
stop_see()
{
    object ob;

    if ((ob = environment(this_object())) && living(ob))
	tell_object(ob, "Your ability to discerne the unseen has diminished.\n");
    remove_object();
}
