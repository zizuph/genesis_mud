// file name:    mcorpse
// creator(s):   Cirion, April 1996
// last update:
// purpose:      The corpse of the mommy grub
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/corpse";
#include "../outpath.h"

int search_count;

void create_corpse()
{
   set_long("It is a translucet, slimy white corpse "
      +"of a maggot. There seems to be something lodged "
      +"inside of it, but you cannot tell without "
      +"searching it.\n");

   add_prop(OBJ_S_SEARCH_FUN, "search_me");
   add_prop(OBJ_I_SEARCH_TIME, 3);
}

mixed search_me(object me, string str)
{
  object     obj;

  search_count++;

  seteuid(getuid());

  switch(search_count)
  {
    case 1:
     say(QCTNAME(me)+" feels around inside "+LANG_THESHORT(TO)+", "
          +"and two slimy eggs roll out.\n");
     obj = clone_object(OBJ+"egg");
      obj->move(ENV(me), 1);
      obj->hatch();
     obj = clone_object(OBJ+"egg");
      obj->move(ENV(me), 1);
     return "Inside the corpse you find two slimy unhatched eggs "
          +"that roll to the ground.\n";
     break;

    case 2:
     say(QCTNAME(me)+" finds a small gem inside "+LANG_THESHORT(TO)+".\n");
     obj = clone_object(BAZAAR+"Obj/misc/gem");
      obj->set_gem_type("jasper");
      obj->move(TP, 1);
     return "Buried within the slime of the corpse, you find a small "
          +"gem which you pull out!\n";
     break;

    default:
     return;
     break;
   }
}






