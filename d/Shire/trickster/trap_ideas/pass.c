#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

//    Prototypes
void go_away(object to);

void
create_object()
{
   set_name("pass");
   set_no_show();
   add_prop(OBJ_I_NO_DROP,1);
   add_prop(OBJ_I_NO_GIVE,1);
   
}

void
enter_env(object to, object from)
{
   ::enter_env(to, from);
   
   set_alarm(120.0,0.0,&go_away(to));
   to->add_prop("_i_just_got_trapped",1);
   return;
}

void
go_away(object to)
{
   to->remove_prop("_i_just_got_trapped");
   remove_object();
   return;
}
