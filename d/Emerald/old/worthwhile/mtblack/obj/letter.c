inherit "/std/object";

void
create_object()
{
  set_alarm(5.0, 0.0, remove_object);
}
