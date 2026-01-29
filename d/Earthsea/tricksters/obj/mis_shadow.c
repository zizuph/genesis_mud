inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

#define SW shadow_who

object mis_obj;

void remove_mischief()
{
 string *arr;

 SW->remove_prop(OBJ_S_SEARCH_FUN);
 if(SW->query_prop_setting("_trick_i_old_search"))
   SW->add_prop(OBJ_S_SEARCH_FUN,
     SW->query_prop_setting("_trick_i_old_search"));
 SW->remove_prop("_trick_i_old_search");
 SW->remove_prop("_trick_i_mischief");
 SW->remove_prop("_trick_i_mischief_owner");
 arr=explode(SW->query_long(),INFESTED_ARM_DESC);
 SW->set_long(arr[0]);
 remove_shadow();
}

public string wear(object what)
{
 setuid();
 seteuid(getuid());

 if(ENV(what)==SW->query_prop_setting("_trick_i_mischief_owner"))
   return "Now why would you want to spring your trap after going to "+
          "all that trouble of setting it up?\n";

 switch(SW->query_prop_setting("_trick_i_mischief"))
  {
   case "itching powder":
     mis_obj=clone_object(TRICKSTERS+"obj/itchpowder");
     mis_obj->move(ENV(what));
     mis_obj->set_length(9999);
     mis_obj->start();
     break;

   case "smelly liquid":
     mis_obj=clone_object(TRICKSTERS+"obj/stinksplash");
     mis_obj->move(ENV(what));
     mis_obj->set_length(9999);
     mis_obj->start();
     break;

   case "sneezing powder":
     mis_obj=clone_object(TRICKSTERS+"obj/sneezepowder");
     mis_obj->move(ENV(what));
     mis_obj->set_length(9999);
     mis_obj->start();
     break;
  }

 return SW->wear(what);
}

public string remove(object what)
{
 mis_obj->end_in(5);

 return SW->remove(what);
}

string find_mischief(object who,string what)
{
 string desc,kind;

 desc=SW->short();kind=SW->query_prop("_trick_i_mischief");
 set_this_player(who);
 say(QTNAME(TP)+" found something in "+SW->short()+".\n");

 remove_mischief();
 return "You find some "+kind+" in "+desc+"!  You give the "+desc+
   " good shake which removes the "+kind+" from it.\n";
}

