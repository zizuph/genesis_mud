inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>

static object who;

public void remove_paralyze();

void create_object()
{
  set_name("_statue_paralysis");
  set_no_show();
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VALUE);
  remove_prop(OBJ_I_VOLUME);
  add_prop(OBJ_M_NO_GET, "");
  add_prop(OBJ_M_NO_DROP, "");
  add_prop(OBJ_M_NO_SELL, "");
  add_prop(OBJ_M_NO_BUY, "");
  set_alarm(30.0,0.0,remove_paralyze);   
}

public void remove_paralyze()
{
    environment(TO)->catch_msg("The mental attack subsides.\n");
    remove_object();
}

int catch_all(string str)
{
  switch (query_verb())
  {
    case "help":
    case "bug":
    case "commune":
    case "typo":
    case "sysbug":
    case "reply":
    case "stop":
    case "systypo":
    case "vitals":
    case "health":
    case "h":
    case "drop":
      return 0;
  }

  write("You can't manage it.\n");
  return 1;
}

void init()
{
  ::init();

  if (environment() == this_player())
  {  
    if (!this_player()->query_wiz_level())
    {
        add_action(catch_all, "", 1);
        this_player()->add_stun();
    }

    who = this_player();
  }
}

void remove_object()
{
  if (who)
  {  
    who->remove_stun();
  }

  ::remove_object();
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  if (!living(env))
  {
    remove_object();
  }
}
