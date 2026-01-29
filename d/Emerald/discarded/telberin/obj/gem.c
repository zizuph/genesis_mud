inherit "/std/object";

#include "default.h"
#include <macros.h>

int do_clean(string str);
static int is_cleaned; /* Has the player cleaned the gem? */

void
create_object()
{
   set_short("gem");
   set_long("@@my_long");
   set_name("gem");
   add_name("gemstone");
   add_name("_mylos_quest_gem_");
   add_name("emerald");
   add_prop(OBJ_I_VALUE, 670);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_WEIGHT, 101);
   add_prop(OBJ_I_VOLUME, 245);
   
   is_cleaned = 0;
}

int query_is_cleaned() { return is_cleaned; }

void set_is_cleaned(int i) { is_cleaned = i; }

string
my_long()
{
   if(query_is_cleaned())
      return "This gemstone sparkles like a bright star at night. It's " +
          "green colour and lovely finished edges, make it an emerald which " +
          "would be worth a lot.\n";
   change_prop(OBJ_I_VALUE, 1056);
   
   return "This stone is a large lump of raw gemstone, which needs proper " +
       "cleaning to be identifiable.\n";
}

void
init()
{
   ::init();
   add_action(do_clean, "clean");
   add_action(do_clean, "polish");
   add_action(do_clean, "rub");
}

int
do_clean(string str)
{
   if(!strlen(str))
      {
      notify_fail("Clean what?\n");
      return 0;
   }
   
   if(str != "gem" && str != "gemstone")
      {
      NF("Clean what?\n");
      return 0;
   }
   
   if(query_is_cleaned())
      {
      notify_fail("You have already cleaned the gem.\n");
      return 0;
   }
   
   write("You rub the gem fastidiously until it starts to gleam.\n"+
      "A sparkling green gemstone is eventually what you end up with.\n");
   say(QCTNAME(this_player())+" cleans "+TP->query_possessive()+
      " gemstone.\n");
   set_is_cleaned(1);
   return 1;
}
