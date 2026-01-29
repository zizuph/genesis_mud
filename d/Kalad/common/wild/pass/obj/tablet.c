inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("tablet");
   set_adj("large");
   add_adj("stone");
   set_long("A large and completely flat slab of rock. It is furnished "+
      "with nothing save for a few names that have been enscribed upon "+
      "one side.\n");
   add_item(({"names","name"}),"The names can be read, perhaps you should "+
      "do so.\n");
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,50000);
   add_prop(OBJ_I_LIGHT,2);
   add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }) );
}
init()
{
   ::init();
   add_action("show","show");
   add_action("read","read");
}
show()
{
   write("You hold the large stone tablet with both hands and display "+
      "it righteously.\n");
   say(QCTNAME(TP) + " holds the large stone tablet with both " + TP->query_possessive() + " hands and displays it righteously.\n");
   return 1;
}
read(string str)
{
   if(!str || str != "names")
      {
      notify_fail("Read what?\n");
      return 0;
   }
   write("You see several names enscribed upon the tablet...\n");
   say(QCTNAME(TP) + " reads something on the large stone tablet.\n");
  set_alarm(2.0,0.0,"glow");
   return 1;
}
void
glow()
{
   write("A faint glow enshrouds you.\n");
   say("A faint glow enshrouds " + QCTNAME(TP) + ".\n");
   return;
}
