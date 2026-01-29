string name, alias, short_desc;
object driver;
int    max_livings, livings;

reset(arg)
{
  if (arg) return;

  set_name("carriage");
  set_alias("wagon");
  set_max_livings(2);
  set_livings(0);
  short_desc="A carriage with one horse is standing here";
}

get()        {return 0;}
id(str)      {return (str==name || str==alias);}

init()
{
  if (environment(this_player())!=this_object())
    add_action("enter",     "enter");
  else
  {
    add_action("leave",     "leave");
    add_action("leave",     "out");
    add_action("drive",     "drive");
    add_action("my_look",      "look");
  }
}

enter(str)
{
  object ob;

  if (!id(str)) return 0;

  livings=0;
  ob=first_inventory(this_object());
  while (ob)
  {
    if (living(ob)) livings++;
    ob=next_inventory(ob);
  }

  if (livings>=max_livings)
  {
    write("The carriage is too crowded already.\n");
    say(this_player()->query_name()+
      " tried to enter the wagon, but the mob inside pushed "+
      this_player()->query_objective()+" back down.\n");
    return 1;
  }
  write("You jump into the carriage.\n");
  say(this_player()->query_name()+" jumps into the wagon.\n");
  tell_room(this_object(), this_player()->query_name()+
    " jumps in.\n");
  move_object(this_player(), this_object());
  command("look", this_player());
  livings++;
  return 1;
}

leave(str)
{
  if (str && !id(str)) return 0;
  write("You jump out of the carriage.\n");
  say(this_player()->query_name()+" jumps out.\n");
  tell_room(environment(this_object()), this_player()->query_name()+
    " jumps out of the wagon.\n");
  move_object(this_player(), environment(this_object()));
  command("look", this_player());
  livings--;
  return 1;
}

drive(str)
{
  if (str && !id(str)) return 0;
  if (!driver)
  {
    write("You sit down in the driver's seat.\n");
    say(this_player()->query_name()+" sits down in the driver's seat.\n");
    driver=this_player();
    return 1;
  }
  if (driver==this_player())
  {
    write("You leave the driver's seat.\n");
    say(this_player()->query_name()+" just left the driver's seat.\n");
    driver=0;
    return 1;    
  }
  write(driver->query_name()+" is already driving!.\n");
  return 1;
}

my_look(str)
{
  if (this_player()==driver)
  {
    if (str=="in")          {look_in();  return 1;}
    if (!str || str=="out") {look_out(); return 1;}
    return 0;
  }
  if (!str || str=="in")    {look_in();  return 1;}
  if (str=="out")           {look_out(); return 1;}
  return 0; 
}

look_in()  {long();}
look_out() {environment(this_object())->long();}

short()
{
  if (driver && !present(driver, this_object())) driver=0;
  if (driver) return (short_desc+".\n"+driver->query_name()+" is driving it");
  return short_desc;
}

long()
{
  object ob;

  if (driver && !present(driver, this_object())) driver=0;
  if (environment(this_player())==this_object())
    write("You are inside a wagon.\n");
  else
  {
    ob=first_inventory(this_object());
    if (!ob)
      write("The wagon is empty.\n");
    else
    {
      write("Inside the wagon, you see:\n");
      while (ob)
      {
        write(ob->short()+".\n");
        ob=next_inventory(ob);
      }
    }
  }
  if (driver)
    write(driver->query_name()+" is driving the carriage.\n");
  else
    write("The driver seat is empty.\n");
}

set_name(n)         {name=n;}
set_alias(a)        {alias=a;}
set_max_livings(l)  {max_livings=l;}
set_livings(l)      {livings=l;}
set_driver(obj)     {driver=obj;}

query_name()        {return name;}
query_alias()       {return alias;}
query_max_livings() {return max_livings;}
query_livings()     {return livings;}
query_driver()      {return driver;}
