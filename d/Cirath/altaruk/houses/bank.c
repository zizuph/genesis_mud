#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/bank.c";

#include "../defs.h"
#include <stdproperties.h>

object deposit;
void reset_room();


void
create_room()
{
  ::create_room();
  config_default_trade();
  set_short("The Bank of Altaruk");
  set_long("This small room serves as the Bank. On a wall hangs"+
    " a poster. The sweet smell of money is in the air." +
    " Opposite the entrance is a carved obsidian desk. Behind it"+
    " sits the clerk. On top of the desk facing towards you is"+
    " a sign.\n");
 
    add_item(({"wall", "walls"}),"They are white and kept clean" +
        " with obvious effort.\n");
 
    add_item("clerk","The cleks is a lazy dwarf. He is slowly counting" +
        " a large stack of coins.\n");

    add_item("poster","The poster says:\n Come to the Vavir trading" +
        " emporium. We always have great deals. We buy and sell" +
        " everything!\n");
 
    add_item(({"obsidian desk", "carved obsidian desk", "carved desk", "desk"}),
             "It has been polished. You can see your reflection in it.\n");

  add_item("sign","You might want to read it.\n");

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

  add_exit(ALT_STR+"17.c", "east", 0, 1);
  INSIDE;
  reset_room();

}

void
init()
{
  ::init();
  bank_init();
}

void
reset_room()
{
 

  if(deposit) return;
  deposit=clone_object("/d/Genesis/obj/deposit");
  deposit->move(this_object());

}

