/*
 * A large vase to carry flowers
 * Based on an example bag, made by Nick and 
 * the herb pouch by Elessar
 * 
 * Coded by Finwe, October 1996
 */
 
inherit "/std/container";
 
#include <stdproperties.h>
 
#define EMERALD_FLOWER          "_garden_flower"
 
int      wilt_time, wilt_left, wilt_stopped, wilt_alarm, inited_once;
 
void
create_container()
{
    set_name("vase");
    set_adj("large");
    set_long("A large crystal vase.\n");
 
    add_prop(CONT_I_WEIGHT, 250);      /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 562);  /* It can hold 562 grams of weight. */
    add_prop(CONT_I_VOLUME, 8);        /* Only 8 ml volume  */
    add_prop(CONT_I_MAX_VOLUME, 508);  /* .5 litres of volume */
 
    add_prop(OBJ_I_VALUE, 40);         /* Worth 40 cc */
}
 
 
/*
 * Function name: wilt
 * Description:   This function is called with an alarm, and simulates the
 *                wilting of flowers
 */
int
wilt()
{
    object env;
    string mess;
 
    wilt_alarm = 0;
 
    if (env = environment())
    {
        mess = "The " + short() + " slowly dries up and dies from lack " +
            "of water.\n";
        if (living(env))
            tell_object(env, mess);
        else if (env->query_prop(ROOM_I_IS))
            tell_room(env, mess);
    }
            
    remove_object();
    return 1;
}
 
/*
 * Function name: set_wilt_time
 * Description:   Set the wilting time of the flower
 * Argumetns:     i - The time (in seconds)
 */
void
set_wilt_time(int i) { wilt_time = i; }
 
 
/*
 * Function name: query_wilt_time
 * Description:   Checks how long it takes for the flower to wilt
 * Returns:       The time in seconds
 */
int                             
query_wilt_time() { return wilt_time; }
 
 
/*
 * Function name: stop_wilt
 * Description:   halts the wilting process of the flower temporarily.
 *                use start_wilt to have the flower resume wilting.
 */
void
stop_wilt(object obj)
{
    if (!inited_once || wilt_stopped)
        return;
    wilt_left = ftoi(get_alarm(wilt_alarm)[2]);
    remove_alarm(wilt_alarm);
    wilt_alarm = 0;
    wilt_stopped = 1;
} 
 
 
/*
 * Function name: restart_wilt
 * Description:   Starts the wilting process of a flower
 *                by stop_wilt.
 */
void
restart_wilt()
{
  if (!wilt_stopped) return;
  wilt_alarm = set_alarm(itof(wilt_left), 0.0, wilt);
  wilt_stopped = 0;
}
 
 
/*
 * Function name: start_wilt
 * Description:   Start the wilt process of a herb
 */
void
start_wilt(object obj)
{
    if (!inited_once)
    {
        if (wilt_time)
            wilt_alarm = set_alarm(itof(wilt_time), 0.0, wilt);
        inited_once = 1;
    }
}
 

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
 
    if (obj->query_prop(EMERALD_FLOWER))
    {
        obj->move(this_player());
        return;
    }
    obj->stop_wilt();
    notify_fail("The vase will only hold flowers.\n");
}
 
 
 
void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
    if (obj->query_prop(EMERALD_FLOWER))
        obj->restart_wilt();
}
