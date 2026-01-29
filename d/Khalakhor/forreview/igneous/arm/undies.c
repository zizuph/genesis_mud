inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Shire/common/defs.h"

static string      name;
void
create_armour()
{
   ::create_armour();
   set_name("underpants");
   set_short("underpants");
   set_long("A pair of underpants.\n");
   set_ac(1);
   set_at(A_HEAD);
   
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_VALUE, 100);
}

void
set_owner(string str)
{
   name = CAP(str);
   
   set_short(name +"'s underpants");
   set_adj(name +"'s");
   set_long("These underpants once belonged to " +name+ ".\n");
}

void
init()
{
   ::init();
   
   add_action("burn","burn");
   add_action("fan","fan");
   add_action("give_back","give back");
   add_action("taunt","taunt");
}

int
burn(string str)
{
   if (str == "underpants")
      {
      write("You light the underpants on fire!!\n");
      say(QCTNAME(TP) + " sets " +name+ "'s underpants on fire!\n");
      tell_room(ENV(ENV(TO)), name+ "'s underpants burn to ashes " +
         "in a great ball of flame!\n");
      remove_object();
      return 1;
   }
   write("Burn what?  The underpants?\n");
   return 1;
}

int
fan(string str)
{
}

int
give_back(string str)
{
}

int
taunt(string str)
{
}
