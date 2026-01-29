inherit "/d/Krynn/open/room_tell";
inherit "/std/object";   // for check_call()

object *whom_to_tell = ({ });

object *query_registered();

void create_object()
{
  set_tell_time(10);
    add_tell("Some deer prance across the road in front of you.\n");
    add_tell("A gentle breeze caresses your face.\n");
    add_tell("A small squirrel chitters at you for being so close " +
        "to his tree.\n");
    add_tell("The wind blows gently through the treetops.\n");
    add_tell("You wrinkle your nose as a skunk meanders past you.\n");
    add_tell("The forest suddenly becomes deathly quiet.\n"); 
    add_tell("All around you, sounds of life can be heard from the " +
        "the forest.\n");
    add_tell("The sunlight warms your skin.\n");
}

/*
 * Function:    do_room_tell()
 * Arguments:   -
 * Description: Perform one tell in the room.
 * Returns:     void
 */
/* This mostly copied from room_tell.c */
public void
do_room_tell()
{
  int     i;
  string  this_tell_string;
  object *who;

  if (!pointerp(tell_strings_left) || !sizeof(tell_strings_left))
     tell_strings_left = tell_strings + ({ });

  if (!pointerp(tell_strings_left) || !sizeof(tell_strings_left))
  {
    tell_alarm = 0;
    return;
  }

  if (sizeof(who = query_registered()) &&
      !(tell_alarm && sizeof(get_alarm(tell_alarm))))
  {
    tell_alarm = set_alarm(10.0 + repeat_tell / 2.0 + rnd() * repeat_tell,
        0.0, do_room_tell);
  }
  else
  {
    tell_alarm = 0;
  }

  i = random(sizeof(tell_strings_left));
  this_tell_string = tell_strings_left[i];
  tell_strings_left -= ({ this_tell_string, 0 });

  who->catch_msg(check_call(this_tell_string));    
}

int register(object ob)
{
  if (member_array(ob, whom_to_tell) >= 0)
  {
    return 0;
  }

  whom_to_tell += ({ ob });

  if (sizeof(whom_to_tell) == 1)
  {
    start_room_tells();
  }

  return 1;
}

int unregister(object ob)
{
  if (member_array(ob, whom_to_tell) < 0)
  {
    return 0;
  }

  if (!sizeof(whom_to_tell -= ({ ob })))
  {
    stop_room_tells();
  }
}

object *query_registered() { return (whom_to_tell -= ({ 0 })); }
