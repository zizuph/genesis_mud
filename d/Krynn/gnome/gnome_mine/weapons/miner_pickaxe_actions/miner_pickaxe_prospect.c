
int
finish_prospect_ore()
{
    object tp = this_player();
    string show_ore = "";

    if (!environment(tp)->query_prop(ROOM_I_INSIDE))
    {
        if (is_terrain_minable())
        {    
            if (tp->query_skill(SS_AWARENESS) > random(100))
            {
                show_ore = "You find " + ore_in_room() + ".\n";
            }
            else if (tp->query_skill(SS_AWARENESS) > 10)
            {
                show_ore = "You think you found " + random_ore_by_value(0) + ", but you are unsure; " +
                "Perhaps being more aware of things would help.\n";
            }
            else
            {
                show_ore = "You seem to lack awareness to find anything here.\n";
            }
        }
        else
        {
            show_ore = "There's nothing here. Probably not the correct terrain.\n";
        }
    }
    else
    {
        show_ore = "You cannot prospect indoors or underground, try outside.\n";
    }

    //(clouded by awareness/mining skill, etc)
    tp->catch_msg(show_ore);
    return 1;
}

int
do_prospect_ore()
{

    object tp = this_player();

    tp->catch_msg("You start looking for minerals.\n");
    tell_room(environment(tp), QCTNAME(tp) + " kneels down and starts " +
        "shuffling through the ground.\n", tp);

    int time_to_prospect = 2 + random(10);

    seteuid(getuid());
    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_fun("stop_prospect");
    paralyze->set_stop_verb("stop");
    paralyze->set_combat_stop(1);
    paralyze->set_stop_message("You stop prospecting.\n");
    paralyze->set_remove_time(time_to_prospect);
    paralyze->set_fail_message("You are busy looking for minerals. You must " +
        "'stop' to do something else.\n");
    paralyze->move(this_player(),1);

    prospect_alarm = set_alarm(itof(time_to_prospect), 0.0, &finish_prospect_ore());
    return 1;
}

varargs int
stop_prospect(mixed arg)
{

    remove_alarm(prospect_alarm);

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " stops prospecting.\n",this_player());

    return 0;
}
