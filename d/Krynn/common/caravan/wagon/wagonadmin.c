/*
 *      /w/vencar/caravan/wagon/wagonadmin.c
 *
 *      A wagon administrator
 *      Created by Vencar 13/08/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      08/2003
 *
 */
#pragma strict_types

inherit "/std/object.c";

#include "/d/Krynn/common/defs.h"
#include "wagonadmin.h"
#include "route.h"

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/*
 *      Global variables:
 */
static string   *Wagons       = ({ });
static string   *WagonTypes   = ({ });
static object   CaravanLeader;

public void    set_wagons(string *wagonlist)          { Wagons        = wagonlist; }
public void    set_wagontypes(string *wagontype)      { WagonTypes    = wagontype; }

public int
set_caravanleader(mixed obj)
{
    if (obj == 0)
    {
        CaravanLeader = 0;
        return 1;
    }

    if (stringp(obj))
    {
        obj = clone_object(obj);
    }
    if (!objectp(obj))
        return 0;

    CaravanLeader = obj;
    return 1;
}


void
create_caravan(string destination)
{
    int ir;
    object obj1;
    object obj2;
    string str;

    setuid();
    seteuid(getuid());

    set_wagons( VENCAR_TEST_WAGONS );
    set_wagontypes( VENCAR_TEST_WAGONS_TYPES );
    if (sizeof(Wagons) == 0)
       return;

    // TODO: want to check if destination is a valid file
    // TODO: want to check if Wagons[0] is a valid file
    str = Wagons[0];
    DEBUG_MSG(str);
    CaravanLeader = clone_object(str);
    CaravanLeader->set_wagontype(WagonTypes[0]);
    CaravanLeader->move(destination);
    obj1 = CaravanLeader;

    for (ir = 1;ir < sizeof(Wagons);ir++)
    {
        // TODO: want to check if Wagons[ir] is a valid file
        str = Wagons[ir];
        obj2 = clone_object(str);
        obj2->set_wagontype(WagonTypes[ir]);
        obj2->move(E(obj1));
        obj1->set_back_wagon(obj2);
        obj2->set_front_wagon(obj1);
        obj1 = obj2;

    };
}

void
StartCaravan(string destination)
{

    create_caravan(destination);
    CaravanLeader->create_rooms();
    CaravanLeader->connect_environment();
    CaravanLeader->start_movement();

}

string*
GetRoute(int Departure, int Destination)
{

  switch ( Departure)
  {
      case WAGON_TEST_LOC1:
          switch ( Destination )
          {
              case WAGON_TEST_LOC2:
                CaravanLeader->set_path( VENCAR_TEST_ROUTE );
                break;
              default:

          }
      case WAGON_TEST_LOC2:
          switch ( Destination )
          {
              case WAGON_TEST_LOC1:
                CaravanLeader->set_path( VENCAR_TEST_REROUTE );
                break;
              default:
          }
      default:
  }

}

public mixed
FindWagon(string str)
{
    int ir;
    object TempWagon;


    // TODO: would be better with a do while there's something in object

    TempWagon = CaravanLeader;
    for (ir = 1;ir < sizeof(Wagons);ir++)
    {
        if (TempWagon->id(str))
            return TempWagon;

        TempWagon = TempWagon->query_back_wagon();
    }

    return 0;
}

public string
stat_object()
{

    return str;

}
