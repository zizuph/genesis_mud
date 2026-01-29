/*
 * Customizations to the standard emerald monster's combat object routines.
 *
 * Shiva Sept. 5 2003
 */

inherit "/std/combat/chumanoid";

public static void
restart_heart()
{
    ::restart_heart();
    qme()->combat_heartbeat_started();
}

public static void
stop_heart()
{
    ::stop_heart();
    qme()->combat_heartbeat_stopped();
}
