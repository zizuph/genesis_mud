#include "defs.h"

inherit TRICKSTER_STD_ROOM;
inherit "/lib/bank";

#define BANK_FEE 20

void create_room()
{
 set_short("Trickster Bank");
 set_long("This is small room , used as bank for tricksters. In the "+
   "corner you see ladge sturdy safe. In the middle of the room you "+
   "see table with clerk sitting near it. Near the strongroom you "+
   "see plaque.\n");

 add_item("safe","It looks very sturdy and impossible to break.\n");
 add_item("table","Large table with clerk sitting near.\n");
 add_item("clerk","Clerk is sitting near the table , he is ready "+
   "to help you.\n");
 add_item("plaque","@@plaque");
 add_cmd_item("plaque","read","@@plaque");

 config_default_trade();
 set_bank_fee(BANK_FEE);
 config_trade_data();

 clone_object("/d/Genesis/obj/deposit")->move(TO);

 add_exit(TRICKSTERS+"discuss","southeast");
}

void
init()
{
 ::init();
 bank_init();
}

string plaque()
{
 return "Welcome to Tricksters branch of Order of Temple Bank.\n"+
   "Clerk is here for your service.\n"+
   sprintf("The fee is %d %s.\n",BANK_FEE,"%");
}

