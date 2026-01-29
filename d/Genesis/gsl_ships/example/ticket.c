/*
 * Test Ticket
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../ships.h"

inherit STDTICKET;

public void
create_object()
{
    ::create_ticket();

    set_name("ticket");
    add_name("_test_ship_ticket");
    add_adj("test");
    set_long("A test ticket for use on the test shipline.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_M_NO_SELL, 1);
    
    set_price(30);      
}
