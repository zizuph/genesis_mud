inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

#define PANDORA_QUEST_LETTER "_pandora_quest_letter"

void create_scroll()
{
    set_name("letter");
    set_short("usual letter");
	set_long("This letter looks pretty personal.\n");
	set_file(A_OBJ_D+"pandoras.letter");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 0);
  add_prop(PANDORA_QUEST_LETTER,1);
}

leave_env(object a,object b)
{
  ::leave_env(a,b);

    if(living(b))
      return;

    call_out("remove_object",2);
  }

remove_object()
{
	tell_room(E(TO),"The letter is caught by the winds, and blows away.\n");
  ::remove_object();
}
