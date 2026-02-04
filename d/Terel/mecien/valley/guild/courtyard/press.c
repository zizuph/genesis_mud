/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/container";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO this_object()
#define TP this_player()

int level = 0;

public void
init()
{
   ::init();
   add_action("turn", "turn");
   add_action("fill", "fill");
   add_action("drain", "drain");
}

public void
create_container()
{
   set_name("press");
   set_adj("old");
   add_adj("wine");
   set_long("It is an old wooden wine press. There is a "+
            "large crank that is used to smash grapes placed within "+
            "the press. A spout protrudes from the reservoir of the "+
            "press, where the juice is held. Though it is old, it looks "+
            "to be in good condition.\n");

   add_item("reservoir", "@@check_level@@");
   add_item("spout", "This is where the juice exits after "+
            "grapes have been pressed. Some kind of vessel must be used "+
            "to catch it.\n");
   add_item("crank", "It is turnable.\n");

   add_prop(CONT_I_VOLUME, 100000);
   add_prop(CONT_I_WEIGHT, 300000);
   add_prop(CONT_I_MAX_VOLUME, 150000);
   add_prop(CONT_I_MAX_WEIGHT, 500000);
   add_prop(CONT_M_NO_INS, "That is not the correct way to use the press.\n");
   add_prop(OBJ_I_NO_GET, "It's far too heavy!\n");
}

public string
check_level()
{
   string str;

   str = "It is where the juice from the pressed grapes is held.";
   if (level >= 20)
      str += " It is full.";
   else if (level <= 0)
      str += " It is empty.";
   else if (level)
      str += " It is partly full.";
   return str + "\n";
}

public int
turn(string str)
{
   object grapes;
   int num;

   notify_fail("Turn what?\n");
   if (str != "crank")
      return 0;
   grapes = present(MYSTIC_GRAPES, TO);
   num = grapes->num_heap();
   if (num) {
      write("You turn the crank and begin pressing the grapes.\n");
      say(QCTNAME(TP) + " turns the crank of the press.\n");
      grapes->remove_object();
      level += num;
      if (level > 20) {
         tell_room(environment(), "The press overflows and juice runs "+
            "out of it.\n");
         level = 20;
      }
      return 1;
   }
   write("Nothing happens.\n");
   say(QCTNAME(TP) + " turns the crank of the press.\n");
   return 1;
}

public int
fill(string str)
{
   object grapes;

   notify_fail("Fill what?\n");
   if (!str)
      return 0;
   notify_fail("Fill it with what?\n");
   if (str == "press")
      return 0;
   notify_fail("That is not possible.\n");
   if (str != "press with grapes")
      return 0;
   grapes = present(MYSTIC_GRAPES, TP);
   if (grapes) {
      remove_prop(CONT_M_NO_INS);
      grapes->move(TO);
      add_prop(CONT_M_NO_INS, "That is not the correct way to use the press.\n");
      write("You fill the press with grapes.\n");
      say(QCTNAME(TP) + " fills the press with grapes.\n");
      return 1;
   }
   write("You have no grapes.\n");
   return 1;
}

public int
drain(string str)
{
   object chalice;
   int amount;

   notify_fail("Drain what into what?\n");
   if (!str)
       return 0;
   if (!parse_command(str, TP, "'juice' / 'press' 'into' %o", chalice))
       return 0;
   notify_fail("You cannot drain it into that!\n");
   if (!chalice->id(MYSTIC_CHALICE))
       return 0;
   notify_fail("The reservoir does not have enough juice to fill it.\n");
   amount = chalice->query_prop("_can_hold_amount");
   if (level < amount)
       return 0;
   notify_fail("The " + chalice->query_name() + " is already full.\n");
   if (present(MYSTIC_JUICE, chalice) || present(MYSTIC_WINE, chalice))
       return 0;
   
   seteuid(getuid());
   chalice->remove_prop(CONT_M_NO_INS);
   clone_object(GUILD_DIR + "obj/juice")->move(chalice);
   chalice->add_prop(CONT_M_NO_INS, "That may not be placed in the chalice.\n");
   level -= amount;
   write("You open the spout and drain juice into the " + chalice->short() +
         ".\n");
   say(QCTNAME(TP) + " drains juice from the press, filling " +
       LANG_ADDART(chalice->short()) + ".\n");
   return 1;
}

