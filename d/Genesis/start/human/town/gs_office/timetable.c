/*
 * Genesis ShipLines - Sparkle office.
 * Ship timetable
 * TAPAKAH, 10/2008
 * To be transferred later into /d/Sparkle
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/ship_new/ships.h"
#include "gs_office.h"

inherit "/std/object";
inherit "/lib/trade";

string exa_timetable ();
int    read_timetable (string str);

void
create_object ()
{
  ::create_object();
  set_name("timetable");
  set_adj(({"large", "cardboard"}));
  set_long("A large cardboard timetable, bolted into wall. "+
           "Several bells and whistles are attached to the perimeter of the "+
           "cardboard.\n" +
           "You notice a narrow slit about a width of a coin at the right "+
           "lower corner of the timetable.\n" +
           "@@exa_timetable");
  add_item(({"bells", "whistles"}),
           "The bells and whistles do not seem to serve any purpose, but "+
           "show the gnomish design of the timetable.\n");
  add_item(({"slit"}),
           "Above the list there is a small plaque that reads:\n"+
           "LearnArrivalAndDepartureInformationForOnePlatinumCoin!\n");
  add_prop(OBJ_M_NO_GET, "The timetable is bolted to the wall.\n");
  config_default_trade();
  set_money_accept(({ 0, 0, 0, 1 }));
}

string
exa_timetable ()
{
  return
    "The timetable reads:\n" +
    SHIP_MASTER->query_timetable("Sparkle");
}


int
read_timetable (string str)
{

  if(str != "timetable" && str != "table")
    NF0("Read what?");
  write("The timetable reads:\n");
  write(SHIP_MASTER->query_timetable("Sparkle"));
  return 1;
}

int
pay_timetable (string str)
{
  int *arr;
  setuid();
  seteuid(getuid());

  if(str != "coin" && str != "coins" && str != "platinum coin" && str != "platinum coins")
    NF0("Maybe, 'insert platinum coin'");
  //  if (!can_pay(1728, TP))
  //  return 0;
  
  arr =  pay(1728, TP, 0, 0, 0, 0, 1);
  if(sizeof(arr) == 1)
    NF0("You have to use a platinum coin!");
  write("You slip the platinum coin into the slit.\n");
  
  write("The timetable flickers and reads:\n");
  write(SHIP_MASTER->query_timetable("Sparkle", 1));
  write("\nThe timetable resets immediately again.\n");
  write_file(GS_TT_LOG, ctime(time()) + " " + TP->query_name() + "\n");
  return 1;
}

void
init ()
{
  ::init();
  add_action(read_timetable, "read");
  add_action(pay_timetable, "pay");
  add_action(pay_timetable, "insert");
}
  
