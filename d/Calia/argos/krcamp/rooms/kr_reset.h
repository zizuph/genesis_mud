/* 
 * Kretan Camp Reset Room Include
 *
 * This should be included in every room in the kretan camp. The main
 * purpose is to set up alarms for all the reset room functionality so
 * that it does not cause runtime and eval-cost issues.
 *
 * Created by Petros, December 2009
 */

/*
 * Function:    alarmed_reset_room
 * Description: This will execute all the actions that are needed
 *              inside a reset room. It will be called from within
 *              an alarm, so no assumptions can be made about the
 *              context.
 */
public void
alarmed_reset_room()
{
    set_alarm(0.0, 0.0, make_kretans);
    set_alarm(0.0, 0.0, reduce_objects);
}

/*
 * Function:    reset_room
 * Description: This reset_room will call the meat of its functionality
 *              in an alarm. The reason is that without an alarm, it can
 *              cause runtime or eval-cost errors, leading to the room
 *              not properly being created.
 */
public nomask void
reset_room()
{
    set_alarm(0.0, 0.0, alarmed_reset_room);
}
