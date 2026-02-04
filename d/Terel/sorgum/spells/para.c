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

    if (stop_verb && query_verb() == stop_verb)
    {
    /* If a stop_fun is defined it MUST return 1 to not stop the paralyze */
	if (stop_object && call_other(stop_object, stop_fun, str))
	    return 1;

	set_alarm(1.0, -1.0, "remove_object");

	if (stop_message)
	    this_player()->catch_msg(stop_message);

	return 1;
    }

    if (fail_message)
	this_player()->catch_msg(fail_message);

    if (!this_player()->query_wiz_level())
	return 1;
}

     
