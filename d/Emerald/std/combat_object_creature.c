/*
 * Customizations to the standard emerald creature's combat object routines.
 *
 * Shiva Sept. 5 2003
 */

inherit "/std/combat/cplain";

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
