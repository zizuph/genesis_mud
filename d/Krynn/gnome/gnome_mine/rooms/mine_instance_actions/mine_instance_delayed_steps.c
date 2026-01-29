
/*  Function name: delayed_call_steps
    Description: 
    WIP

*/
/*
void
delayed_call_steps(int delayed_timer, string delayed_options, int delayed_someone_is_doing, 
                string delayed_verb, string delayed_fatigue_text, int delayed_fatigue,
                string * delayed_messages, string * delayed_envs, 
                int * delayed_timer_time, int * delayed_fatigue_mult, int * delayed_percents)
{
    object tp = this_player();
    int selected = 0;

    if (delayed_timer < 0)
    {
        finish_delayed();
    }
    else
    {
        if (tp->query_fatigue() < 1)
        {
            if (this_player()->query_wiz_level())
            {
                write("Since you are a wizard, you can keep "+delayed_verb+" without worring about fatigue.\n");
            }
            else
            {
                delayed_someone_is_doing = 0;
                paralyze_delayed->stop_paralyze();
                tp->catch_msg(delayed_fatigue_text +
                    "You are too tired to keep "+verb+".\n");
                return;
            }
        }

        //read percents and do a random, like the ore dispenser.

        tp->catch_msg(delayed_messages[selected]+"\n");
        tell_room(environment(tp), delayed_envs[selected] + "\n", tp);
        delayed_timer = delayed_timer - delayed_timer_time[selected];
        tp->add_fatigue(delayed_fatigue*delayed_fatigue_mult[selected]);

        delayed_alarm = set_alarm(5.0, 0.0, &delayed_call_steps(delayed_timer));
    }
}
*/
