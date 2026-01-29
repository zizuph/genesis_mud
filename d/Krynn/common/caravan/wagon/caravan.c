/*
 *      /w/vencar/caravan/wagon/caravan.c
 *
 *      A specific caravan containing the wagons.
 *      Created by Vencar 09/02/2004
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      02/2004
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

#define DEBUG_WIZ       "vencar"
#define DEBUG_MSG(x)   find_player(DEBUG_WIZ)->catch_msg("Debug msg: " + x + ".\n");

/*
 *      Global variables:
 */
public void    tour_move();
public void    get_tour();

object *MyWagons = ({});
object *DestroyedWagons = ({});



static int     Move_Id,
               Turn_Id,
               Step;


static string *MyRoute = ({ });









public mixed
get_E()
{
    if (sizeof(MyWagons) > 0)
        return E(MyWagons[0]);
    else
        return 0;
}

void
remove_wagon(object wagon)
{
    MyWagons -= ({wagon});
    DestroyedWagons += ({wagon});
    MyWagons -= ({ 0 });
    map(MyWagons, &->connect_environment());
}


/*
 * Function name:  query_front_wagon
 * Description:    Finds the wagon in front of the current.
 *
 * Arguments :     wagon : The wagon we want to find the one in front of
 *
 * Returns:        0 if unsuccesful in finding a wagon
 *                 the wagon if succesful
*/

public mixed
query_front_wagon(object wagon)
{
    int id = 0;
    id = member_array(wagon,MyWagons) - 1;
    if (id < 0)
        return 0;
    return MyWagons[id];
}

/*
 * Function name:  query_back_wagon
 * Description:    Finds the wagon in behind of the current.
 *
 * Arguments :     wagon : The wagon we want to find the one inbehind of
 *
 * Returns:        0 if unsuccesful in finding a wagon
 *                 the wagon if succesful
*/

public mixed
query_back_wagon(object wagon)
{
    int id = 0;
    id = (member_array(wagon,MyWagons)) + 1;
    DEBUG_MSG(sizeof(MyWagons) + "   id: " + id);
    if (id > sizeof(MyWagons) - 1)
        return 0;
    return MyWagons[id];
}



/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
/*
 * Function name:  pick_wagons
 * Description:    Picks the wagons for this caravan
 *
 * Arguments :     randomnumber: A number between 0-100 which the balance needs
 *                               to be bigger than.
 *                 wagonlist :   The wagons that can be picked.
 *
 * Returns:        0 if unsuccesful in finding a wagon
 *                 1 if successsfull
*/

int
pick_wagon(int randomnumber, mixed *wagonlist)
{
    int maxrandom = 0,ix;
    object tmpwagon;
    string str;

    for (ix = 0;ix < (sizeof(wagonlist) - 1);ix++)
    {
      maxrandom += wagonlist[ix][2];
      if (maxrandom > randomnumber)
      {
          if (wagonlist[ix][3]-- > 0)
          {
              DEBUG_MSG(wagonlist[ix][0] + " " + maxrandom + " " + randomnumber + " ix " + ix + " " + wagonlist[ix][1]);
              tmpwagon = clone_object(wagonlist[ix][0]);
              tmpwagon->set_wagontype(wagonlist[ix][1]);
              tmpwagon->set_caravan(TO);
              MyWagons += ({ tmpwagon });
              return 1;
          }
          else
          {
              return 0;
          }


      }
    }
}

/*
 * Function name:  pick_wagons
 * Description:    Picks the wagons for this caravan
 *
 * Arguments:     wagonlist: The raw list of wagons available.
 *                wagonnumber: numbers of wagons we want in this caravan.
 *
 * Returns:        nothing
*/

void
pick_wagons(int wagonnumber, mixed *wagonlist)
{
    int ir, wagoncount;

   for (ir = 1;ir < 100 ;ir++)
    {
        wagoncount += pick_wagon(random(100), wagonlist);
        if (wagoncount == wagonnumber)
            return;
    }

}


/*
 * Function name:  create_caravan
 * Description:    initializes and sets up a caravan ready to
 *                 move between two paths, with a set of wagons.
 *
 * Arguments:     destination: The room the caravan is cloned into
 *                route:      The route to drive to
 *                routeback : The route back.
 *                wagonlist:  The list of wagons that might be in the caravan
 *                wagonnumber: numbers of wagons we want in this caravan.
 *
 * Returns:        nothing
*/


void
create_caravan(string destination, mixed *route,
               string *wagonlist, int wagonnumber)
{
    int ir;
    object obj1;
    object obj2;
    string str;

    setuid();
    seteuid(getuid());

    pick_wagons(wagonnumber, wagonlist);

    DEBUG_MSG(destination);
    map(MyWagons, &->move(destination));
    map(MyWagons, &->create_rooms());
    map(MyWagons, &->connect_environment());
    MyRoute = route;
    get_tour();

}

void
StartCaravan(string destination)
{

//    create_caravan(destination, VENCAR_TEST_ROUTE_MERGE, CARAVAN_GOOD_CIVILIAN_1, 7);
      create_caravan(destination, VENCAR_TEST_ROUTE_MERGE, CARAVAN_TROOP_TEST_1 , 7);
    /*
    CaravanLeader->start_movement();
    */
}



public mixed
FindWagon(string str)
{
    int ir;
    mixed TempWagon;


    // TODO: would be better with a do while there's something in object


    TempWagon = filter(MyWagons, &->id(str));
    return TempWagon;

}

public string
stat_object()
{
    string str;

    MyWagons -= ({ 0 });
    if (sizeof(MyWagons) == 0)
        return "The caravan has been burned down.\n";
     str = "The following wagons travel with caravan from XXX to YYY:\n";
     str += implode(map(MyWagons, &->short()), ".\n");
     str += "\nThey are located:";
     str += file_name(E(MyWagons[0]));
     str += ".\n";
    return str;

}



/***************** MOVEMENT CODE FOR A CARAVAN ***************/


public void
get_tour()
{
    remove_alarm(Turn_Id);
    Turn_Id = 0;

    Step = -1;
    Move_Id = set_alarm(120.0, 0.0, tour_move);
}

public void
move_wagon(string MoveTo, string dir)
{
    map(MyWagons, &->wagon_move(MoveTo,dir));
}


public void
tour_move()
{
    int     ir;
    mixed   exits;
    string  dir,
            back_goal;

    remove_alarm(Move_Id);
    Move_Id = 0;

    if (!get_E())
        return;


    if (Step < 0)
        Step = member_array(file_name(get_E()), MyRoute);
    if (Step < 0)
    {
        DEBUG_MSG(Step + "    :" + file_name(get_E()) + "  :" + MyRoute[0]);
        tell_room(get_E(), "The caravan seems unable to move.\n");
        return;
    }



    if((ir = member_array(MyRoute[++Step], exits = get_E()->query_exit())) < 0)
    {

        if (MyRoute[Step] == "PAUSE")
        {
            Step++; //we jump a step, as this is a midway part, so we dont'
                    //want to trigger the start room of a route.
            Move_Id = set_alarm(120.0, 0.0, tour_move);
            return;
        }

        if (MyRoute[Step] == "SPECIAL")
        {
            Step++;  //we jump to the next step where the special command is
                    //defined.
            //get_E()->MyRoute[Step];
            Move_Id = set_alarm(2.0, 0.0, tour_move);
        }


        tell_room(get_E(), "The caravan seems unable to move.\n");
        return;
    }



    dir = exits[ir + 1];
    /* call movement*/
    tell_room(get_E(), "A caravan leaves " + dir + ".\n");
    move_wagon(MyRoute[Step], dir);
    tell_room(get_E(), "A caravan arrives.\n");

    // Did we arrive at the last stage of the trip?
    if (Step == (sizeof(MyRoute) - 1))
    {
        Turn_Id = set_alarm(120.0, 0.0, get_tour);
    }
    else
    {
        Move_Id = set_alarm(15.0, 0.0, tour_move);
    }
}


