inherit "/std/room";

#define TOWNSHIP_TELL  "/d/Emerald/tmp/township/township_tell"
#define REGISTER(ob)   TOWNSHIP_TELL->register(ob);
#define UNREGISTER(ob) TOWNSHIP_TELL->unregister(ob);

int is_township_room() { return 1; }

void enter_inv(object ob, object from)
{
  if (interactive(ob))
  {
    REGISTER(ob);
  }

  ::enter_inv(ob, from);
}

void leave_inv(object ob, object to)
{
  if (interactive(ob) && !to->is_township_room())
  {
    UNREGISTER(ob);
  }

  ::leave_inv(ob, to);
}
