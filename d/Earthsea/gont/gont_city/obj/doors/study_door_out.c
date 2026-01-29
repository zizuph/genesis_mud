inherit "/std/door";

public void
create_door()
{
  set_door_id("__study_door");
  set_pass_command(({"n", "north"}));
  set_door_name(({"black door", "door"}));
  set_open(0);
  set_other_room("/d/Earthsea/gont/gont_city/rooms/manor/study");
}
