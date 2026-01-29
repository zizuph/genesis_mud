/*
 * /d/Gondor/common/guild/ithilien/door.c
 *
 * Inherit /std/door.c and make some local tweaks
 *
 */

inherit "/std/door";

void
do_open_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc("open", this_object());
    if (strlen(mess))
	tell_room(env, mess);
    open_status = 1;
}

void
do_close_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc("closed", this_object());
    if (strlen(mess))
	tell_room(env, mess);
    open_status = 0;
}

void
do_lock_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc("locked", this_object());
    if (strlen(mess))
	tell_room(env, mess);
    lock_status = 1;
}

void
do_unlock_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc("closed", this_object());
    if (strlen(mess))
	tell_room(env, mess);
    lock_status = 0;
}
