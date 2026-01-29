#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

inherit "/std/object";
inherit "/sys/global/cmdparse";

int bloody; /*Has the player stabbed himself yet?*/

void
create_object()
{
   set_name("feather");
   set_pname("feathers");
   set_short("feather");
   set_pshort("feathers");
   set_long("@@my_long");
   
   add_prop(OBJ_I_WEIGHT, 3);
   add_prop(OBJ_I_VOLUME, 50);
   bloody=0;
}

string
my_long()
{
   if(bloody)
      return "A large, but extremely light griffon feather. It is dripping with blood.\n";
   else
      return "A large, but extremely light griffon feather. You wonder what you can use it for. The tip of the feather looks very sharp.\n";
}

void
init()
{
   add_action("feather_stab", "stab");
   add_action("feather_stab", "poke");
   add_action("feather_stab", "cut");
   add_action("feather_stab", "prick");
}
int
feather_stab(string str)
{
   string self;
   string a,b;int i;
   object * temparray;
   object target;
   if(!(interactive(E(TO))))
      {
      NF("What?\n");
      return 0;
   }
   NF("Stab who with what?\n");
   if(!str)
      return 0;
   if(bloody)
      {
      NF("The feather is already dripping with blood. Why put anyone through unnecessary pain?\n");
      return 0;
   }
   i = sscanf(str, "%s with %s", a, b);
   if(!((a)&&((b=="feather")||(b=="griffon feather"))))
      {
      NF("Stab who with what?\n");
      return 0;
   }
   temparray = (find_str_in_object(a, E(E(TO))));
   if(sizeof(temparray) == 0)
      target = 0;
   else
      target = temparray[0];
   if((i)&&((b=="feather")||(b=="griffon feather"))&&((a=="me")||(a=="myself")))
      target = TP;
   if(!(living(target)))
      {
      NF("Exactly how would stabbing that help you??\n");
      return 0;
   }
   if((i)&&(((a=="me")||(a=="myself"))&&((b=="feather")||(b=="griffon feather"))))
      
   /*
   */
   if(!(((b=="feather")||(b=="griffon feather"))&&(i)&&(target)))
      {
      NF("Stab who with what?\n");
      return 0;
   }
   if(target==TP)
      {
      bloody = 1;
      if(TP->query_gender() == 0)
         self = "himself";
      else
         if(TP->query_gender() == 1)
         self = "herself";
      else
         self = "itself";
      write("You stab yourself with the griffon feather. Your blood wets and reddens the feather.\n");
      say(QCTNAME(TP) + " stabs " + self + " with " + (POSSESSIVE(TP)) + " feather.\n");
      return 1;
   }
   NF("Stab who with what?\n");
   if(!((target)&&(i)))
      return 0;
   bloody = 1;
   if(TP->query_met(target))
      b = QCTNAME(target);
   else
      b = QTNAME(target);
   TP->catch_msg("You stab " + b + " with your griffon feather. " +
      C(POSSESSIVE(target)) +
      " blood wets and reddens the feather.\n");
   target->catch_msg(QCTNAME(TP) +
      " stabs you with the pointy tip of a large griffon feather!\n");
   tell_room(E(TP), C(QCTNAME(TP)) + " stabs " + C(QCTNAME(target)) +
      " with the pointy tip of a large griffon feather.\n" +
      "", ({TP, target}));
   return 1;
}

int
query_bloody()
{
   return bloody;
}
