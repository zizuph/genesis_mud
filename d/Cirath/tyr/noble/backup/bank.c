 /* /d/Cirath/athas/a_tyr/noble/bank.c
  * A bank within the noble district.
  * Decius, January 1997
  * Modified by Damaris 5/2003 - Added varried bank fee
 * Modified by Serpine 04/2013 - Degnomed it a bit
  */

#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/bank";

#include "defs.h"
#include <stdproperties.h>

void reset_room();

void
create_room()
{
  ::create_room();
  config_default_trade();
  bank_fee = 5 + random(26);
  set_bank_fee(bank_fee);
  config_trade_data();
  set_short("The Bank of Tyr");
  set_long("White marble walls and barred windows mark this as "+
    "the bank of Tyr. Here is guarded the riches of many "+
    "nobles, thus it is very heavily fortified. Mul guards "+
    "line the walls, ready to deal with trouble. "+
    "Opposite the entrance is a carved obsidian desk, with "+
    "a pale templar sitting behind it who appears to be "+
    "the banker. On top of the desk facing towards you is "+
    "a sign. Along the wall is a plaque.\n");
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

    add_item(({"plaque"}),
      "          The gold plated plaque reads:\n"+
      "          +----------------------------------------+\n"+
      "          |               Bank of Tyr              |\n"+
      "          |        " + bank_fee + "% Fee to change coins         |\n"+
      "          |----------------------------------------|\n"+
      "          | Examples:                              |\n"+
      "          | change copper and silver for gold      |\n"+
      "          | test change copper and silver for gold |\n"+
      "          | change 1 platinum for copper           |\n"+
      "          | change platinum for 100 silver         |\n"+
      "          | minimize coins                         |\n"+
      "          +----------------------------------------+\n");
    add_cmd_item("plaque","read",
      "          The gold plated plaque reads:\n"+
      "          +----------------------------------------+\n"+
      "          |               Bank of Tyr              |\n"+
      "          |        " + bank_fee + "% Fee to change coins         |\n"+
      "          |----------------------------------------|\n"+
      "          | Examples:                              |\n"+
      "          | change copper and silver for gold      |\n"+
      "          | test change copper and silver for gold |\n"+
      "          | change 1 platinum for copper           |\n"+
      "          | change platinum for 100 silver         |\n"+
      "          | minimize coins                         |\n"+
      "          +----------------------------------------+\n");

    add_exit(TYR_NOBLE+"rd_hr_02.c", "south", 0, 1);
    
	object deposit = clone_object("/d/Genesis/obj/deposit");
        deposit->set_clerk_race("templar");
	deposit->set_bank_id(4201, "Tyr");
    add_item( ({ "gnome", "small gnome", "wizened gnome",
        "small wizened gnome" }),
        "A gnome? Gnomes in Athas were largely exterminated.\n");
    deposit->set_long("It is small and fort-like. It has an opening protected " +
        "with marble bars and a large sign. Behind the opening there is " +
        "a templar.\n");
    deposit->add_item( ({ "letters", "crooked letters" }),
        "GnoMeS Of GeNeSiS\n");
    deposit->add_item( ({ "opening" }),
        "It is the counter, protected by marble bars. Behind it you find a " +
        "a templar.\n");
    deposit->set_sign_text("The sign reads:\n\n" +
        "GnoMeS Of GeNeSiS\n" +
        "- mOsTLy SaFe\n" +
        "- NoN LeTHaL SeRViCe\n" +
        "- aVaiLaBLe eVeRyWHeRe\n" +
        "- iN SoMe FOrm AnYwAy\n" +
        "- FeeS... sO MaNy fEEs!\n" +
        "- RhUlIsTi SPeCiaL RaTeS\n\n" +
        "After that there is a lot of fine print regulating the terms " +
        "of deposit and giving instructions on using the GoG deposit.\n");
	deposit->move(this_object(), 1);
	reset_room();
}

void
reset_room()
{
}

void
init()
{
    ::init();
    bank_init();

}
