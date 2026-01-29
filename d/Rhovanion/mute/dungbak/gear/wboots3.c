inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#define OBJ_I_BURNT"_obj_i_burnt"
public string adj1;
public string adj2;
public string long;
void
create_armour() {
   adj1 = "hemp";
   adj2 = "old";
   long = "These old boots are made entirely with " +
   "hemp!  Though once lusch and green, they now are " +
   "dry and brown and probably highly flammable!  You'd " +
   "better keep them away from fire!\n";
   set_name("boots");
   add_adj("@@new_adj@@");
   add_adj("@@same_adj@@");
   set_long("@@set_my_long");
   set_ac(1);
   set_am(({ 0, 0, 0 }));
   set_at(A_FEET);
}
void
init()
{
   ::init();
   add_action("part_light","light");
}
int
part_light(string str) {
   notify_fail("Light what?\n");
   if (!str)
      return 0;
   if (str != "boots")
      return 0;
   if (query_prop(OBJ_I_BURNT)) {
      write("They are just cinders now!  Unburnable!\n");
      return 1;
   }
   write("You set your boots on fire!!!\n");
   say(QCTNAME(this_player()) + " sets his boots on fire!!!\n");
   add_adj("burning");
   this_player()->drink_alco(10);
   set_alarm(0.0,0.0,"make_me_burnt");
   return 1;
}
public int
make_me_burnt() {
   adj2 = "burning";
   long = "This pair of dry, hemp boots is on fire!  The smoke " +
   "is starting to get to you making you a bit dizzy.\n";
   TO->add_prop(OBJ_I_LIGHT, 1);
   set_alarm(100.0,0.0,"part_burnt");
   set_alarm(20.0,0.0,"part_high");
   return 1;
}
int
part_burnt() {
   this_object()->set_condition(10);
   write("Your boots burn out and your head clears a little.\n");
   say(QCTNAME(this_player()) + " watches as his boots " +
      "burn away to cinders.\n");
   TO->add_prop(OBJ_I_LIGHT, 0);
   adj2 = "burnt";
   long = "These are the remains of some old burnt up " +
   "hemp boots.\n";
   return 1;
}
public string
same_adj() {
   return adj1;
}
public string
new_adj() {
   return adj2;
}
public string
set_my_long()
{
   return long;
}
int
part_high() {
   write("The smoke from your boots is making your head swim, " +
      "but you like it!\n");
   TP->drink_alco(1);
   say(QCTNAME(this_player()) + " smiles dreamily " +
      "as the smoke from his burning hemp boots swirls round " +
      "his head.\n");
   set_alarm(35.0,0.0,"part_high2");
   return 1;
}
int
part_high2() {
   write("The smoke from your boots is making your head swim, " +
      "but you like it!\n");
   TP->drink_alco(1);
   say(QCTNAME(this_player()) + " smiles dreamily " +
      "as the smoke from his burning hemp boots swirls round " +
      "his head.\n");
   return 1;
}
