/*
 * Genesis ShipLines - Sparkle office.
 * Shiplines leaflet
 * TAPAKAH, 02/2009
 * To be transferred later into /d/Sparkle
 */

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/std/object";

string exa_leaflet ();

void
create_object ()
{

  ::create_object();
  set_name("leaflet");
  set_adj(({"thin", "medium-sized", "paper"}));
  set_long("A medium-sized leaflet, made of thin paper. "+
           "It lists the lines of the Genesis ShipLines Company.\n" +
           "@@exa_leaflet");
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_VALUE,  0);
  
}

string
exa_leaflet ()
{
  return
    "The leaflet reads:\n" +
    "   The Genesis ShipLines Company operates the following lines:\n" +
    SHIP_MANAGER->query_all_routes();
}


int
read_leaflet (string str)
{

  if(str != "leaflet")
    NF0("Read what?");
  write(exa_leaflet());
  return 1;
}

void
init ()
{
  ::init();
  add_action(&read_leaflet(), "read");
}
  
