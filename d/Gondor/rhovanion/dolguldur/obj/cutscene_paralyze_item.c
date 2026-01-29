inherit "/std/object";

#include <stdproperties.h>

#define FOUND_MM_BOOK    "_found_mm_book"

static object who;

int paralyze_counter = 0;

void remove_object()
{
    if (who)
    {  
        who->remove_stun();
    }
  
    environment(this_object())->catch_tell("You can move again!\n");

    ::remove_object();
}


void countdown()
{
    switch (paralyze_counter)
    {
        case 0:
        environment(this_object())->catch_tell("Some pesky ranger "
        +"pops up from nowhere, steals your book and stuns you!\n");
    
        tell_room(environment(environment(this_object())), "Some pesky ranger "
        +"pops out from the shadows and stuns "
        +environment(this_object())->query_name()+" while stealing something!\n", 
        environment(this_object()));
        
        environment(this_object())->add_prop(FOUND_MM_BOOK, 1);
        
        break;
        
        case 1:
        environment(this_object())->catch_tell("You are stunned! 1\n");
        break;
        case 2:
        environment(this_object())->catch_tell("You are stunned! 2\n");
        break;
        case 3:
        environment(this_object())->catch_tell("You are stunned! 3\n");
        break;
        case 4:
        environment(this_object())->catch_tell("You are stunned! 4\n");
        break;
        case 5:
        this_object()->remove_object();
        break;
        
    }
    
    paralyze_counter = paralyze_counter + 1;
}

void create_object()
{
  set_name("_mm_cutscene_paralyze_item");
  set_no_show();
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VALUE);
  remove_prop(OBJ_I_VOLUME);
  add_prop(OBJ_M_NO_GET, "");
  add_prop(OBJ_M_NO_DROP, "");
  add_prop(OBJ_M_NO_SELL, "");
  add_prop(OBJ_M_NO_BUY, "");
  
  set_alarm(0.1, 5.0, &countdown());
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
    case "systypo":
    case "vitals":
    case "health":
    case "h":
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


void enter_env(object env, object from)
{
  ::enter_env(env, from);

  if (!living(env))
  {
    remove_object();
  }
}
