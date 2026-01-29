/*
 * Clone and move this object to a player if you want to paralyze him.
 * paralyze will stop with first command given
 *
 */

inherit "/std/paralyze";

/*
 * Function name: stop
 * Description:   Here all commands the player gives comes.
 * Argument:	  str - The extra string the player sent.
 */
varargs int
stop(string str)
{
    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())
	return 0;

    /* If a stop_fun is defined it MUST return 1 to not stop the paralyze */
    if (stop_object)
        call_other(stop_object, stop_fun, str);

    set_alarm(1.0, 0.0, remove_object);

    if (stop_message)
        this_player()->catch_msg(stop_message);

    return 0;
}
