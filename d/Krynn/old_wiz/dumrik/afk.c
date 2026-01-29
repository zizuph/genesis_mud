inherit "std/object";

object obj;

create_object()
{
  set_name("afk");
  set_short("afk");
}


init()
{
  ::init();
  add_action("gone","gone");
  add_action("back","back");
}


int
gone(string message)
{
  
  obj = clone_object("/d/Krynn/dumrik/ct.c");
  obj->set_mess(message);
  obj->move(environment(this_object()));
  obj->shadow_me(this_player()->query_real_name());
  
  write("Gone-Message set to " + message + "\n");

  
  
  return 1;
}

int
back()
{
  obj->remove();
  write("Gone-Message removed.\n");

  return 1;
}




