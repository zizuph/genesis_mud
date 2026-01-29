/* temple/obj/bag.c is cloned by temple/court_w.c */
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
void
create_object()
{
  seteuid(getuid(this_object()));
  set_name("bag");
  add_name("_ring_quest_bag_");
  set_short("large bag");
  set_adj("large");
  set_long("It's a large closed bag. There is something inside, " +
           "but you need open it to know what exactly it is.\n");
 
  add_prop(OBJ_I_WEIGHT,500);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,100+random(20));
  add_prop(OBJ_M_NO_SELL,"Get all from the bag before selling it, fool!\n");
}
 
init()
{
 ::init();
 if (environment()==this_player())
   add_action("do_open","open");
 if (environment()==this_player())
   add_action("do_untie","untie");
}
 
int
do_open(string str)
{
  if (parse_command(str,TP,"[the][large]'bag'"));
   {
    write("Odd. You cannot find out how to open it.\n");
    write("It seems there is some secret to it.\n");
    return 1;
   }
  notify_fail("Open what?\n");
  return 0;
}
