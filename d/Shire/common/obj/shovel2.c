/*
 *  Enchanted version of the shovel.
 */
inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

void
create_object()
{
   set_name(({"shovel"}));
   set_short("shovel (enchanted)");
   set_pshort("shovels (enchanted)");
   set_long("@@my_long");
   add_prop(OBJ_I_WEIGHT, 3500);
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_VALUE, 80);
   add_prop(MAGIC_AM_MAGIC, ({1,"enchanted"}));
}

void
init()
{
   add_action("do_dig","dig");
}

string
my_long()
{
   string the_long;
   mixed *magic_prop;

   the_long = "The shovel has a grip of oak and a dull iron blade which "
            + "will make digging harder.";

   if (magic_prop = query_prop(MAGIC_AM_MAGIC))
      the_long += " It looks " + magic_prop[1] + ".";

   return break_string(the_long + "\n", 70);
}

int
do_dig(string str)
{
   object hole, tp;
   int fatigue;
   tp= this_player();

   notify_fail("Dig where?\n");
   if (str != "here" && str != "hole")
      return 0;


   NF("You cannot dig indoors.\n");
   if (ENV(TP)->query_prop(ROOM_I_INSIDE)) return 0;


   seteuid(getuid());

   if (MASTER_OB(environment(tp)) == "/d/Shire/common/hobbiton/camp2")
      return 0;

   fatigue = tp->query_fatigue();
   if (fatigue < 40)
   {
      notify_fail("You are too tired to dig!\n");
      return 0;
   }
   else
      tp->add_fatigue(-40);

   write("You start to dig until you have worked up a sweat.\n");
   say(QCTNAME(tp) + " starts to dig until " + tp->query_pronoun()
     + " is tired.\n");

   if (hole = present("_hole_",environment(tp)))
      hole->increase_size();
   else
      clone_object(STAND_OBJ + "hole")->move(environment(tp));  
   return 1;
}
