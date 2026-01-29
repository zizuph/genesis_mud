// name: Ticket   ~Avenir/common/ships/ansalon/ticket.c
// creator(s):    Tepisch  Oct 1994
// last update:   Boriska, Mar 23 1995
// purpose:       Ticket for the Odalisque      
// note:
// bug(s):
// to-do:    

#pragma save_binary

inherit "/std/object";

#include "/d/Avenir/common/ships/ship.h"

void
create_object()
{
  set_name("ticket");
  add_name("_SybAnsalon_Ticket");
  add_adj("mahogany");
  set_long("Engraved into the polished wooden ticket are the words:\n"+
	   "The G.S. Odalisque, providing transportation\n"+
	   "   between the Rift of Sybarus and Port Balifor.\n");
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_VALUE,  5);
}