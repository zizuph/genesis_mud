

int climb_alarm;
int someoneIsClimbing = 0;

object paralyze_climbing;


/*
 * Function name: finish_climbing
 * Description  : moves up one room.
 */
void
finish_climbing()
{
    object tp = this_player();

    object roomExists = query_master_instance_pointer()->query_rooms(x, y, z-1);

    tp->move(roomExists);

    tp->catch_msg("You finally pull yourself out of the hole and breathe a sigh of relief.\n");
    tell_room(environment(tp), QCTNAME(tp) + " pulls out of the hole and breathes a sigh of relief.\n", tp);

    someoneIsClimbing = 0;
    paralyze_climbing->stop_paralyze();
}

mapping CLIMBING_EVENT_CLIMB=   ([
                            "msg"   : "You steadily climb up.\n",
                            "env"   : " steadily climbs up.\n",
                            "timer"  : -1,
                            "fatigue" : -1,
                            "percent" : 0
                        ]);

mapping CLIMBING_EVENT_CLIMB_FAST=   ([
                            "msg"   : "You find all the right stones and climb up really fast.\n",
                            "env"   : " finds all the right stones and climbs up really fast.\n",
                            "timer"  : -3,
                            "fatigue" : -1,
                            "percent" : 0
                        ]);

mapping CLIMBING_EVENT_CLIMB_SLIP=   ([
                            "msg"   : "You slip and almost fall.\n",
                            "env"   : " slips and almost falls.\n",
                            "timer"  : 0,
                            "fatigue" : -2,
                            "percent" : 0
                        ]);

mapping CLIMBING_EVENT_CLIMB_SLIDE=   ([
                            "msg"   : "You grab the wrong place and slide down a few rocks.\n",
                            "env"   : " grabs the wrong place and slides down a few rocks.\n",
                            "timer"  : 2,
                            "fatigue" : -3,
                            "percent" : 0
                        ]);

mapping CLIMBING_EVENTS=    ([
                            "climb"   : CLIMBING_EVENT_CLIMB,
                            "fast"    : CLIMBING_EVENT_CLIMB_FAST,
                            "slip"    : CLIMBING_EVENT_CLIMB_SLIP,
                            "slide"   : CLIMBING_EVENT_CLIMB_SLIDE
                        ]);

/*  Function name: climb
    Description: 

*/
void
climb(int climbing_timer)
{
    object tp = this_player();

    if (climbing_timer < 0)
    {
        finish_climbing();
    }
    else if (climbing_timer > 15)
    {
        tp->catch_msg("You slide back to the ground.\n");
        tell_room(environment(tp), QCTNAME(tp) + " slides back to the ground.\n", tp);

        someoneIsClimbing = 0;
        paralyze_climbing->stop_paralyze();
    }
    else
    {
        if (tp->query_fatigue() < 1)
        {
            if (this_player()->query_wiz_level())
            {
                write("Since you are a wizard, you can keep climbing without worring about fatigue.\n");
            }
            else
            {
                someoneIsClimbing = 0;
                paralyze_climbing->stop_paralyze();
                tp->catch_msg("You slip and fall, droping to the ground and " +
                    "trying to catch your breath. You are too tired to keep climbing.\n");
                tell_room(environment(tp), QCTNAME(tp) + " slips and falls, droping to the ground.\n", tp);
                return;
            }
        }

        CLIMBING_EVENT_CLIMB["percent"]         = random(tp->query_skill(SS_CLIMB) - 10);
        CLIMBING_EVENT_CLIMB_FAST["percent"]    = random(tp->query_skill(SS_CLIMB) - 40);
        CLIMBING_EVENT_CLIMB_SLIP["percent"]    = random(80 - tp->query_skill(SS_CLIMB));
        CLIMBING_EVENT_CLIMB_SLIDE["percent"]   = random(70 - tp->query_skill(SS_CLIMB));

        string selected = random_by_percent(0, CLIMBING_EVENTS, "percent");

        tp->catch_msg(CLIMBING_EVENTS[selected]["msg"]);
        tell_room(environment(tp), QCTNAME(tp) + CLIMBING_EVENTS[selected]["env"], tp);
        climbing_timer = climbing_timer + CLIMBING_EVENTS[selected]["timer"];
        tp->add_fatigue(CLIMBING_EVENTS[selected]["fatigue"]);

        climb_alarm = set_alarm(5.0, 0.0, &climb(climbing_timer));
    }
}

/*  Function name: do_climb
    Description: 

*/
int
do_climb(string str)
{
    object tp = this_player();
    int time_to_climb = 0;

    if (!str)
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (str == "up")
    {
        if (this_object()->item_id("roof"))
        {
            if (!someoneIsClimbing)
            {
                tp->catch_msg("You start climbing up.\n");
                tell_room(environment(tp), QCTNAME(tp) + " start climbing up.\n", tp);

                time_to_climb = 1 + random(11 - (tp->query_skill(SS_CLIMB)/10));

                seteuid(getuid());
                paralyze_climbing = clone_object("/std/paralyze");
                paralyze_climbing->set_stop_fun("stop_climbing");
                paralyze_climbing->set_stop_verb("stop");
                paralyze_climbing->set_combat_stop(1);
                paralyze_climbing->set_stop_message("You stop climbing and drop back down.\n");
                paralyze_climbing->set_remove_time(300);
                paralyze_climbing->set_fail_message("You are busy climbing. You must " +
                    "'stop' to do something else.\n");
                paralyze_climbing->move(this_player(),1);

                climb_alarm = set_alarm(5.0, 0.0, &climb(time_to_climb));

                someoneIsClimbing = 1;
            }
        }
        else
        {
            notify_fail("There's no exit on the roof.\n");
            return 0;
        }
    }
    else
    {
        notify_fail("You can only climb up here.\n");
        return 0;
    }
    return 1;
}

/*  Function name: stop_climbing
    Description: stops climbing alarms. resets flag "someoneIsClimbing" so the area can be climbed again. this is for use with the paralize object only.

*/
varargs int
stop_climbing(mixed arg)
{

    remove_alarm(climb_alarm);

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " stops climbing and drops down.\n", this_player());

    someoneIsClimbing = 0;

    return 0;
}

