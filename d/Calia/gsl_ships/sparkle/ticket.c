/*
 * Ticket for Shipline between Sparkle and Gelan in Calia
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "ship.h"

inherit STDTICKET;

public void
create_object()
{
    ::create_ticket();

    set_name("ticket");
    add_name("_gelan_sparkle_ticket_");
    add_adj("blue");
    set_long("A blue ticket with the picture of a dolphin stamped "+
            "on it. You somehow feel that you can 'check passengers' "+
            "to discover who is on board, if the captain is around to "+
            "ask, as long as you've got this ticket.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_M_NO_SELL, 1);
    
    set_price(30);      
}
