/*********************************************************************
 * - ticket.c                                                      - *
 * - shipline Gont-Kabal                                           - *
 * - Recoded by Damaris 5/2003                                     - *
 * - ported to new ship system by Tapakah, 05/2009                 - *
 *********************************************************************/
 
#pragma save_binary
#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

#define TICKET_VALUE 36

inherit STDTICKET;
 
public void create_object()
{
    set_name("ticket");
    add_name("newbiegontkalad");
    add_adj("dingy brown");
    set_long("The dingy brown ticket is made from a thin sheet of parchment, "+
             "which is filthy. It gives the bearer passage on the shipline "+
             "that visits the ports of Kabal Port District and Gont.\n");
    add_prop(OBJ_I_VALUE,  TICKET_VALUE);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}
 
