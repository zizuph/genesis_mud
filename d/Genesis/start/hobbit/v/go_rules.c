#pragma save_binary

inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_object() {
   set_name(({"go_rules","rules","note"}));
   set_adj("go");
   set_short("note with rules");
   set_pshort("notes with rules");
   set_long("There are five rules. Do \"rule X\" to read rule number X.\n");
   add_prop(OBJ_M_NO_GET,"The rules are glued to the floor.\n");
}

void
init() {
   add_action("do_read","read");
   add_action("do_rule","rule");
}

int
do_read(string str) {
   if (str == "note" || str == "rules")
      notify_fail("Use \"rule X\" to read rule number X.\n");
   return 0;
}

int
do_rule(string str) {
   int rule;

   notify_fail("Use \"rule X\" to read rule number X.\n");
   if (!str)
      return 0;

   if (str == "1")
   {
      write(
 "There are two players, black and white. They take turns, playing one stone\n"
+"each. Black starts with one or more stones, depending on the handicap.\n\n"
+"The stones are played in a matrix on the intersections. It is allowed to\n"
+"play on the outer border.\n\n"
+"The normal game size is 19 x 19 (that is 18 x 18 squares), but the game\n"
+"can also be played on smaller boards.\n");
      return 1;
   }
   if (str == "2")
   {
      write(
 "The winner is the player with the highest score on the board when the game\n"
+"ends.\n\n"
+"The game ends when both players have passed.\n\n"
+"The score is the number of stones + number of surrounded empty intersections.\n");
      return 1;
   }
   if (str == "3")
   {
      write(
 "A group is defined as one or more stones of the same colour, that are\n"
+"connected along the lines. Stones besides each other are connected,\n"
+"but stones positioned diagonally from each other are not.\n\n"
+"A liberty is an empty space beside a stone. Again, an empty space diagonally\n"
+"from a stone does not count.\n\n"
+"The liberties of a group, are the number of liberties that a group have.\n\n"
+"Liberties can be shared by more than one group.\n");
      return 1;
   }
   if (str == "4")
   {
      write(
 "If a stone is played so that the last liberty of an enemy group is removed,\n"
+"then all stones in that enemy group are removed.\n\n"
+"If a stone is played so that the last liberty of a group of the same colour\n"
+"is removed, then it is an illegal move.\n");
      return 1;
   }
   if (str == "5")
   {
      write(
 "If the position of the board is a repeat of an earlier position, then the\n"
+"last move was illegal.\n");
      return 1;
   }
   return 0;
}