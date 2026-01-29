inherit "/std/object";

#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>
#include <ss_types.h>
#include "/std/combat/combat.h"
#include <wa_types.h>
#include "/d/Roke/Cirath/defs.h"

int light = 0,     /* 0 = light off, 1 = light on, -1 = darkness */
    connect = 0; /* 0 = connected */
query_auto_load()
{
  return MASTER;
}

public string 
show_subloc(string subloc, object me, object for_obj)
{
  string data,str;

  if(light = 0) str = "";
  else if(light == -1) str = "darkened";
  else str = "glowing ";

  if(for_obj != me)
    data = capitalize(this_player()->query_pronoun()) + 
           " has a "+str+"moonstone ring in "+TP->query_possessive()+
           " nose.\n";
  else
    data = "You have your "+str+"moonstone ring in your nose.\n";

  return data;
}

create_object()
{
  set_short("nose-ring");
  set_name("ring");
  add_name("ciubori_moon_ring");
  
  set_adj("moonstone");
  set_short("moonstone nose-ring");
  set_long("This is a moonstone nose-ring.\n");

  add_prop(OBJ_M_NO_DROP,1);
  this_object()->set_no_show_composite(0);
}

init()
{
  ::init();
  add_action("connect","connect");
  add_action("disconnect","disconnect");

  call_out("lighter",1);
}

enter_env(object dest,object old)
{
  remove_name("ciubori_moon_ring");
  add_name("ciubori_moon_ring");
  if(living(E(TO)))
  dest->add_subloc("ciubori_moon_ring", this_object());
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("ciubori_moon_ring");
}


int print_light_txt(int new)
{
  if (light != new)
  {
    if(new == 0)
    {
      if (light == 1)
      {
        write("Your moonstone nose-ring's light fades away.\n");
        say(QCTNAME(TP)+"'s moonstone nose-ring stops to glow.\n");
      }
      else if (light == -1)
      {
        write("Your moonstone nosering's stops emitting darkness.\n");
        say(QCTNAME(TP)+"'s moonstone nosering stops emitting darkness.\n");
      }
    }
    else if(new == 1)
    {
      write("Your moonstone nose-ring begins to glow with a strange light.\n");
      say(QCTNAME(TP)+"'s moonstone nose-ring begins to glow with a strange light.\n");
    }
    else if(new == -1)
    {
      write("Your moonstone nose-ring starts emitting darkness.\n");
      say(QCTNAME(TP)+"'s moonstone nose-ring starts emitting darkness.\n");
    }
    else write("Hmmm...something's wrong with your nose-ring.\n");
  }

  light = new;
  return 1;
}

int lighter()
{
  int l;

  if(connect == 0)
  {
    l = random(10);
    if (l > 7)
    {
      add_prop(OBJ_I_LIGHT,1);
      print_light_txt(1);
    }
    else if (l < 2)
    {
      add_prop(OBJ_I_LIGHT,-1);
      print_light_txt(-1);
    }
    else
    {
      add_prop(OBJ_I_LIGHT,0);
      print_light_txt(0);
    }
  }

  call_out("lighter",500);
  return 1;
}

int connect(string str)
{
  if (str == "nosering")
  {
    if (TP->query_wiz_level()) /* only wizards will be able to connect/disconnect the ring */
    {
      connect == 0;
      write("<=-Nosering Connected-=>\n");
      say(QCTNAME(TP)+" connects the edges of his moonstone nosering.\n");
      return 1;
    }
  }

  return 0;
}

int disconnect(string str)
{
  if(str == "nosering" && TP->query_wiz_level())
  {
    connect == 1;
    write("<=-Nosering Disconnected-=>\n");
    add_prop(OBJ_I_LIGHT,0);
    say(QCTNAME(TP)+" disconnects the edges of his moonstone nosering.\n");
    return 1;
  }

  return 0;
}
