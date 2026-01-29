inherit "/std/paralyze";

void
create_paralyze()
{
    set_name("_sindar_paralyze_");
    set_remove_time(20);
    set_stop_message("\nYou untangle yourself from the net and are able to move.\n\n");
    set_fail_message("The net prevents you from fighting.\n");
    set_stop_verb(0); /* No command to stop paralyze! */
    set_stop_object(0);      /* Use the messages set above */
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    env->add_stun();
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    env->remove_stun();
}
