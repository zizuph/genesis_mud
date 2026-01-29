#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <files.h>
#include <state_desc.h>

inherit "/std/shadow";

object flag;
object room;
object me;

public void
enter_inv(object ob, object from)
{
  query_shadow_who()->enter_inv(ob, from);
  if(!present(flag, room))
  {
    me->remove_shadow();
    return;
  }
  if(interactive(ob))
  {
    flag->check_alarm();
  }
}

public void
leave_inv(object ob, object to)
{
  query_shadow_who()->leave_inv(ob, to);
  if(!present(flag, room))
  {
    me->remove_shadow();
    return;
  }

  if(interactive(ob))
  {
    flag->check_alarm();
  }
}

public void init_shadow(object a_flag, object a_room, object a_shadow)
{
  flag = a_flag;
  room = a_room;
  me = a_shadow; 
}