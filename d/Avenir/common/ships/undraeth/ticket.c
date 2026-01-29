// name: Ticket   ~Avenir/common/ships/kalad/ticket.c
// creator(s):    Cirion May 1996
// last update:   
// purpose:       Ticket for the Avatar
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
  add_name("_kalad_bazaar_ticket");
  add_adj("parchment");
  set_long("It is a thin piece of parchment, with nothing written on it.\nScattered "
          +"along the parchment are many tiny holes.\n");
  AI("holes","There are numerous tiny holes punched into the parchment.\n");
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_VALUE,  5);
}