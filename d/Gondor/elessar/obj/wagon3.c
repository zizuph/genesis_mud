string name, alias, short_desc, dest_dir;
object driver;
int    max_livings, livings;
status anywhere_mode;


reset(arg)
{
  if (arg) return;

  set_name("carriage");
  set_alias("wagon");
  set_max_livings(3);
  set_livings(0);
  short_desc="A carriage with two horses is standing here";

  set_anywhere_mode(1);
}

get()        {return 0;}
id(str)      {return (str==name || str==alias);}

init()
{
  add_action("my_say", "say");
  if (environment(this_player())!=this_object())
  {
    add_action("enter",     "enter");
  }
  else
  {
    add_action("leave",     "leave");
    add_action("leave",     "out");
    add_action("drive",     "drive");
    add_action("my_look",   "look");
    if (this_player()==driver) move_actions();
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
      " tried to enter the wagon, but the people inside pushed "+
      this_player()->query_objective()+" back down.\n");
    return 1;
  }
  write("You climb into the carriage.\n");
  say(this_player()->query_name()+" climbs into the wagon.\n");
  tell_room(this_object(), this_player()->query_name()+
    " jumps in.\n");
  move_object(this_player(), this_object());
  command("look", this_player());
  livings++;
  return 1;
}

my_say(str)
{
  if (!str) {write("Ok.\n"); return 1;}
  write("You said: "+str+"\n");
  say(this_player()->query_name()+" says: "+str+"\n");
  if (environment(this_player())==this_object())
    tell_room(environment(this_object()),
      this_player()->query_name()+" says: "+str+"\n");
  else
    tell_room(this_object(),
      this_player()->query_name()+" says: "+str+"\n");
  return 1;
}

leave(str)
{
  if (str && !id(str)) return 0;
  write("You jump out of the carriage.\n");
  say(this_player()->query_name()+" jumps out.\n");
  tell_room(environment(this_object()), this_player()->query_name()+
    " jumps out of the wagon.\n");
  if (this_player()==driver) driver=0;
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
    move_actions();
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

look_in() {long();}

look_out()
{
  move_object(this_player(), environment(this_object()));
  command("look", this_player());
  move_object(this_player(), this_object());
}

short()
{
  if (driver) return (short_desc+". "+driver->query_name()+" is driving it");
  return short_desc;
}

long()
{
  object ob;

  if (driver && !present(driver, this_object())) driver=0;
  ob=first_inventory(this_object());
  write("It's a small horse-carriage, of the kind farmers use for\n");
  write("transporting their wares to the market.\n");
  write("Inside the wagon, you see:\n");
  if (!ob) write("Nothing.\n");
  else
    while (ob)
    {
      if (ob!=this_player())
        write(ob->short()+".\n");
      ob=next_inventory(ob);
    }
  if (driver)
    write(driver->query_name()+" is driving the carriage.\n");
  else
    write("The driver seat is empty.\n");
}

move_actions()
{
  int i;

  dest_dir=environment(this_object())->query_dest_dir();
  if (!dest_dir) return;
  i=1;
  while (i<sizeof(dest_dir))
  {
    add_action("move", dest_dir[i]);
    i+=3;
  }
}

move(str)
{
  object room, dest_room;
  int    i;

  room=environment(this_object());
  i=1;
  while (i<sizeof(dest_dir))
  {
    if (query_verb()==dest_dir[i])
    {
      dest_room=dest_dir[i-1];
      if (dest_room->road() || anywhere_mode)
      {
         write("You somehow make the horse go "+dest_dir[i]+".\n");
         say("The wagon moves.\n");
         tell_room(room, "The wagon drives "+dest_dir[i]+" along the trail.\n");
         tell_room(dest_room, "A wagon arrives.\n");
         move_object(this_object(), dest_room);
         look_out();
         return 1;
      }
      write("Better stick to the road...\n");
      return 1;
    }
    i+=3;
  }
  return 0;
}


set_name(n)           {name=n;}
set_alias(a)          {alias=a;}
set_max_livings(l)    {max_livings=l;}
set_livings(l)        {livings=l;}
set_driver(obj)       {driver=obj;}
set_anywhere_mode(b)  {anywhere_mode=b;}

query_name()          {return name;}
query_alias()         {return alias;}
query_max_livings()   {return max_livings;}
query_livings()       {return livings;}
query_driver()        {return driver;}
query_anywhere_mode() {return anywhere_mode;}

