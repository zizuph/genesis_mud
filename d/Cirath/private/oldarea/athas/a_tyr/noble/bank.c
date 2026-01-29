 /* /d/Cirath/athas/a_tyr/noble/bank.c
  * A bank within the noble district.
  * Decius, January 1997
  */

#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/bank.c";

#include "defs.h"
#include <stdproperties.h>

void
create_room()
{
  ::create_room();
  config_default_trade();
  set_short("The Bank of Tyr");
  set_long("White marble walls and barred windows mark this as "+
    "the bank of Tyr. Here is guarded the riches of many "+
    "nobles, thus it is very heavily fortified. Mul guards "+
    "line the walls, ready to deal with trouble. "+
    "Opposite the entrance is a carved obsidian desk, with "+
    "a pale templar sitting behind it who appears to be "+
    "the banker. On top of the desk facing towards you is "+
    "a sign.\n");
 
    add_item(({"wall", "walls", "marble walls", "white marble walls"}),
             "They are white and kept clean with obvious effort.\n");
 
    add_item(({"window", "windows", "barred window", "barred windows", "bar", "bars"}),
             "The bars are made from petrified brambleweed, razor sharp "
            +"and near impossible to cut.\n");
 
    add_item(({"guard", "guards", "mul guard", "mul guards","mul", "muls"}),
             "Powerful warriors hand-picked from the arena for their "
            +"intimidating looks and fighting skills.\n");
 
    add_item(({"templar", "pale templar", "banker"}),
             "In spite of his unhealthy palor, the templar appears well "
            +"fed and extremely happy to be in control of so much money.\n");
 
    add_item(({"obsidian desk", "carved obsidian desk", "carved desk", "desk"}),
             "It has been polished to highlight the glossy blackness, and "
            +"its edges are appear sharp enough to sever a limb.\n");

  add_item("sign","This is a large sign carved from white "+
    "marble, scratched onto it are writings for nobles "+
    "and templars to read.\n");

  add_cmd_item("sign","read",
    "You squint your eyes and read the sign, it says:\n"+
    "\n"+
    "Here you may:\n"+
    "Minimize your currency\n"+
    "Change your currency\n"+
    "Test the results of Minimizing or Changing.\n"+
    "We charge a 30% fee to Minimize or Change.\n\n");

  set_bank_fee(30);

  config_trade_data();

    add_exit(TZ_NOBLE+"rd_hr_02.c", "south", 0, 1);
}

void
init()
{
  ::init();
  bank_init();
}
