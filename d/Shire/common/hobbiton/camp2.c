inherit "/std/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#define QUEST_GROUP 0
#define QUEST_BIT   1

int solved;

create_room() {
   set_short("bushy field");
   set_long("@@room_long");

   add_item("hole","@@hole_long");
   add_prop(ROOM_I_INSIDE,0);

   add_exit(HOBBIT_DIR + "camp1","north",0,1);
   add_exit(HOBBIT_DIR + "camp4","east",0,1);
   reset_room();
}

reset_room() {
   object *arr;
   int i,s;

   if (!(s = sizeof(arr = all_inventory(this_object()))) ||
      (s = sizeof(filter(arr, "is_orc", this_object()))) < 2)
   {
      for (i=0; i<(2-s); i++)
         clone_object(NPC_DIR + "random_orc")->move(TO);
   }
   solved = 0;
}

is_orc(obj) { return obj->id("_random_orc_") && living(obj); }

init() {
   ::init();
   add_action("do_dig","dig");
}

room_long() {
   string the_long;

   the_long = "You have stumbled upon an orc camp. This is where the regular "
            + "orc footsoldiers have to lie in the grass. "
            + "North is the entrance of the camp and east is a corner of "
            + "the camp.";

   if (solved)
      the_long += " Someone has dug a hole here.";

   return break_string(the_long + "\n", 70);
}

hole_long() {
   if (solved)
      return "The hole is not too deep, and does not look interesting.\n";
   else
      return "What hole?";
}

do_dig() {
   object *arr;
   int i,s, amount;
   object tp, shovel;

   seteuid(getuid());
   tp = this_player();

   notify_fail("You see no reason to dig here.\n");
   if (tp->query_prop("_freed_orc_prisoner_") != 2)
      return 0;

   /* Are there orcs present? */
   if (!sizeof(arr = all_inventory(this_object())) ||
       (s = sizeof(filter(arr, "is_orc", this_object()))) > 0)
   {
      if (s == 1)
      {
         write("The orc stops you from digging here.\n");
         say("The orc stops " + QCTNAME(tp) + " from digging here.\n");
         return 1;
      }
      else
      {
         write("One of the orcs stops you from digging here.\n");
         say("One of the orcs stops " + QCTNAME(tp) + " from digging here.\n");
         return 1;
      }
   }

   /* Too late? */
   if (solved)
   {
      notify_fail("It looks like someone has been digging here before.\n"
                + "You find nothing.\n");
      return 0;
   }

   /* Does the player have a shovel? */
   if (!(shovel = present("shovel", tp)))
   {
      write("The ground is too hard to dig in with your hands.\n");
      say(QCTNAME(tp)
        + " tries to dig in the ground with his hands, but fails\n");
      return 1;
   }

   if (MASTER_OB(shovel) != "/d/Shire/common/obj/shovel2")
   {
      write("You start to dig.\n"
          + "Suddenly you hit a magical forcefield, and your shovel refuses "
          + "to go deeper!\n"
          + "You remember that the prisoner shouted something about an "
          + "alchemist.\n");
      return 1;
   }
   write("You start to dig in the ground with your shovel and discover "
       + "a tome!\n"
       + "You quickly get the tome.\n"
       + "Your shovel has lost its aura of enchantment.\n");
   say(QCTNAME(tp) + " starts to dig in the ground with "
     + tp->query_possessive() + " shovel and\ndiscovers a tome!\n"
     + tp->query_pronoun() + " quickly gets the tome.\n");

   shovel->remove_object();
   clone_object(STAND_PARENT + "obj/shovel")->move(this_player());
   tp->add_prop("_freed_orc_prisoner_",1);

   /* Only add experience if not solved before */
   if (!(tp->test_bit("Shire", QUEST_GROUP, QUEST_BIT)))
   {
      tp->set_bit(QUEST_GROUP, QUEST_BIT);

      /* NEVER add more exp than the player has */
      if (tp->query_exp() < 7000)
         amount = tp->query_exp()*3/4;
      else
         amount = 7000;

      tp->add_exp(amount,0);            /* Add quest experience */
      log_file("QUESTS", "free prisoner: " + extract(ctime(time()), 4, 15)+ " "
	     + capitalize(tp->query_real_name()) + " got "
	     + amount + "xp.\n");
   }

   solved = 1;
   clone_object(STAND_PARENT + "obj/spelltome")->move(tp);
   return 1;
}
