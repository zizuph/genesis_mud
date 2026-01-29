// name: Ticket   ~Avenir/common/ships/sparkle/ticket.c
// creator(s):    Tepisch  Oct 1994
// last update:   Boriska, Mar 23 1995
// purpose:       Ticket for the Melancholy         
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
  add_name("_staek_ticket");
  add_adj("bone-coloured");
  set_long("Engraved into the polished bone ticket are the words:\n"+
	   "The Good Ship Melancholy, providing transportation\n"+
	   "   between the Rift of Sybarus and Sparkle town.\n");
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_VALUE,  5);
}