inherit "/std/object";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
static int corked=1;
static int counter=0;
static int ruined=0;
static int drank=0;
void
create_object() {
   set_name("potion");
   set_adj(ONE_OF_LIST(({"purple","red","blue","green"})));
   set_adj(ONE_OF_LIST(({"light","dark","heavy","viscous"})));
   set_long("@@my_desc");
   add_prop(OBJ_I_VALUE, 2000);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME,  900);
}

string
my_desc()
{
   string desc;
   
   if(!drank)
      desc = "This is a glass vial, with a cork, and apparently " +
   "filled with a viscous purple liquid.\n";
   else
      desc = "This is a glass vial, with a cork.  It is empty.\n";
   
   if(!corked)
      desc += "The potion is currently uncorked.\n";
   else
      desc += "The potion is currently corked.\n";
   
   return desc;
}

void
init()
{
   ::init();
   add_action("drink_potion","drink");
   add_action("uncork_potion","uncork");
   add_action("sip_potion","sip");
   add_action("cork_potion","cork");
}

int
drink_potion(string str) {
   notify_fail("Drink what?\n");
   if (!str)
      return 0;
   if (str != "potion")
      return 0;
   if (corked==1)
      {
      write("Try taking the cork out first.\n");
      return 1;
   }
   else
      if (ruined==1)
      {
      write("Someone took too much out of this potion already.\n");
      return 1;
   }
   else
      if (drank==1)
      {
      write("There is nothing left to drink.\n");
      return 1;
   }
   else
      {
      write("You drink the potion...\n");
      say(QCTNAME(this_player()) + " drinks a potion\n");
      set_alarm(5.0,0.0,"part_drunk");
      return 1;
   }
}
int
uncork_potion(string str) {
   notify_fail("Uncork what?\n");
   if (!str)
      return 0;
   if (str !="potion")
      return 0;
   if (!corked)
      {
      write("It's already uncorked.\n");
      return 1;
   }
   else
      {
      write("You uncork the potion.\n");
      say(QCTNAME(this_player()) + " uncorks a potion.\n");
      corked=0;
      return 1;
   }
}
int
sip_potion(string str) {
   notify_fail("Sip what?\n");
   if (!str)
      return 0;
   if (str!="potion")
      return 0;
   if (corked==1)
      {
      write("Try taking the cork out first.\n");
      return 1;
   }   
   else
      if (drank==1)
      {
      write("There's nothing left to sip.\n");
      return 1;
   }
   if (counter++ > 1)
      {
      write("You take a sip of the potion and feel a bit healthier, " +
         "but you've taken too much of the potion and ruined it.\n");
      say(QCTNAME(this_player()) + " sips a potion.\n");
      ruined = 1;
      return 1;
   }
   else
      {
      write("You take a sip of the potion and feel a bit healthier.\n");
      say(QCTNAME(this_player()) + " sips a potion.\n");
      counter++;
      return 1;
   }
}
int
cork_potion(string str) {
   notify_fail("Cork what?\n");
   if (!str)
      return 0;
   if (str!="potion")
      return 0;
   if (corked) {
      write("It is already corked.\n");
      return 1;
   }
   else
      {
      write("You cork the potion.\n");
      say(QCTNAME(this_player()) + " corks a potion.\n");
      corked = 1;
      return 1;
   }
}
int
part_drunk() {
   write("You feel healthier.\n");
   this_player()->heal_hp(400);
   drank=1;
   return 1;
}
