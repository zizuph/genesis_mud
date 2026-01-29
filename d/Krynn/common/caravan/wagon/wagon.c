/*
 *      /w/vencar/caravan/wagon/wagon.c
 *
 *      A generic wagon to be inherited.
 *      Created by Vencar 13/08/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      08/2003
 *
 *
 *      Credits to:
 *      Elessar, Olorin
 *      For original design in file
 *      /d/Gondor/common/lib/wagon.c
 */
#pragma strict_types

inherit "/std/object.c";

#include "wagon.h"
#include "/d/Krynn/common/defs.h"
#include "route.h"

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

/*
 *      Prototypes:
 */
public string  carriage_short();
public string  carriage_long();
public int     start_burning();
public int     connect_environment();
public int     set_room(mixed str);
public mixed   query_room(mixed str, int position);
public int wagontype;
public object caravan;

/*
 *      Global variables:
 */
static int     Burn_Id,
               BurnStep,
               BurnNumbers = 0,
               BurnDamageTooMuch = 0;


static mapping Rooms = ([ ]);
static mapping BurnMsg = ([ ]);

/*
 *      Small overrideable functions:
 */


public void    create_krynn_wagon() { }
public int     add_room_items() { }
public int    check_enter_wagon(string str) { return 1; }
public int    check_leave_wagon(string str) { return 1; }



public void
set_caravan(object obj)
{
    caravan = obj;
}


public void
set_wagontype(int wtype)
{
    if (wtype)
        wagontype = wtype;
    else
        wagontype = random(15);
}


public int
query_wagontype(int typ)
{
    return typ;
}


/***************** LINKED LIST CODE FOR WAGONS ***************/

/*
 * Function name:  query_front_wagon
 * Description:    Returns the wagon in front of this wagon
 *                  if it returns 0, then this is the leading
 *                  wagon in the caravan
 * Returns:        0 If this is the leading wagon
 *                 Otherwise the object of the wagon in front of
 *                  this wagon
 */


public mixed
query_front_wagon()
{
    return (caravan->query_front_wagon(TO));
}

public mixed
query_back_wagon()
{
    return (caravan->query_back_wagon(TO));
}


/*
 * Function name:  query_leader
 * Description:    Checks if its the leader wagon
 * Returns:        0 if not
 *                 1 if it is the leader
 */
public int
query_leader()
{
    /* the wagon without a wagon in front of it,... is the leader */
    return (query_front_wagon() ? 0 : 1 );
}

public int
query_rear()
{
    return (query_back_wagon() ? 0 : 1 );
}

/*
 * Function name:  remove_wagon
 * Description:    Removes a wagon from the caravan
 *                 and binds the wagons in front and
 *                 behind together.
 *                 If a new wagon gets the leadership
 *                 it will automatically move on
 * Returns:        1 if succesfully removed
 *                 0 if not.
 */
public int
remove_wagon()
{

    int scenario;
    mixed FrontWagon;
    mixed BackWagon;
    BackWagon =  query_back_wagon();
    FrontWagon = query_front_wagon();

    caravan->remove_wagon(TO);
    // binary operation without using bit as i don't know how to :)
    scenario = 0;

    if (FrontWagon)
    {
        DEBUG_MSG("There is a wagon in front");
        scenario += 1;
    }
    if (BackWagon)
    {
        DEBUG_MSG("There is a wagon in behind");
        scenario += 2;
    }

    switch (scenario)
    {
        /* X scenario (the last one) */
        case 0:
        {
            break;
        }
        /* X-0-0 scenario (last wagon)*/
        case 1:
        {
            /*and make new front and back rooms around the new leaders and
            myself */
            FrontWagon->set_room(R_BACK);
            FrontWagon->query_room(R_BACK,M_OBJECT)->set_wagon(FrontWagon);
            set_room(R_FRONT);
            query_room(R_FRONT,M_OBJECT)->set_wagon(TO);
            FrontWagon->connect_environment();

            break;
        }
        /* 0-0-X scenario (front wagon) */
        case 2:
        {
            /* and make new front and back rooms around the new leaders and
               myself */

            set_room(R_BACK);
            query_room(R_BACK,M_OBJECT)->set_wagon(TO);
            BackWagon->set_room(R_FRONT);
            BackWagon->query_room(R_FRONT,M_OBJECT)->set_wagon(BackWagon);

            BackWagon->connect_environment();

            break;
        }
        /* 0-0-X-0 scenario */
        case 3:
        {
            //and make new front and back rooms around myself
            set_room(R_BACK);
            query_room(R_BACK,M_OBJECT)->set_wagon(TO);
            set_room(R_FRONT);
            query_room(R_FRONT,M_OBJECT)->set_wagon(TO);

            //and redo the connection in the wagons in front and back of me
            FrontWagon->connect_environment();
            BackWagon->connect_environment();
            break;
        }
        default:
            return 0;
    }


    //and update my pointers to the world
   connect_environment();

    return 1;

}

public int
query_burnstep()
{
    return BurnStep;
}

/************ ROOM CODE FOR ROOMS INSIDE WAGON OBJECT*******/

/*
 * Function name:  query_room
 * Description:    Fetches some variable from the room mappimg
 *                 the key str, and the position in the mapping position.
 *                 check wagon.h for a full description of the mapping.
 * Returns:        0 if something goes wrong.
 *                 the variable if goes good.
*/


public mixed
query_room(mixed str, int position)
{
    return Rooms[str][position];
}

public mixed
query_burn_msg(mixed str, int position)
{
    return BurnMsg[str][position];
}

public int
set_room(mixed str)
{
    object obj;

    /*must not be set already*/
    if (objectp(Rooms[str][M_OBJECT]))
        return 0;

    /*file of the room should be set*/
    if(query_room(str,MAP_FILE) == "")
        return 0;

    obj = clone_object(query_room(str, MAP_FILE));

    /*did the creation fail? */
    if (!objectp(obj))
        return 0;

    //map_file holds: " + query_room(str,MAP_FILE));
    Rooms[str][M_OBJECT] = obj;
    return 1;

}

public int
add_mapping(string mykey, mixed str)
{
    Rooms[mykey] = str;
}

public int
add_burn_msg(mapping str)
{
    BurnMsg[++BurnNumbers] = str;
}

public void

create_default_rooms()
{
        add_mapping (R_LEFT, DEFAULT_LEFT);
        add_mapping (R_RIGHT, DEFAULT_RIGHT);
        add_mapping (R_FRONT, DEFAULT_FRONT);
        add_mapping (R_BACK, DEFAULT_BACK);
        add_mapping (R_WAGON, DEFAULT_WAGON);
}



public void
create_rooms()
{


    DEBUG_MSG("entering create_rooms" );
    create_default_rooms();
    /* if the wagon is the rear it dont have a wagon in back of it,
       it will have a room in the back of it. */
    if (query_rear() )
    {
        if (!query_room(R_BACK,M_OBJECT) )
        {
            set_room(R_BACK);
            query_room(R_BACK,M_OBJECT)->set_wagon(TO);
        }
    }
    /* if the wagon is the leader it dont have a wagon in front, it
       will have a room in the front of it. */
    if (query_leader() )
    {
        if (!query_room(R_FRONT,M_OBJECT) )
        {
            set_room(R_FRONT);
            query_room(R_FRONT,M_OBJECT)->set_wagon(TO);
        }

    }

    if (!query_room(R_LEFT,M_OBJECT) )
    {
        set_room(R_LEFT);
        query_room(R_LEFT,M_OBJECT)->set_wagon(TO);
    }

    if (!query_room(R_RIGHT,M_OBJECT) )
    {
        set_room(R_RIGHT);
        query_room(R_RIGHT,M_OBJECT)->set_wagon(TO);
    }

    if  (!query_room(R_WAGON,M_OBJECT) )
    {
        set_room(R_WAGON);
        query_room(R_WAGON,M_OBJECT)->set_wagon(TO);
    }

    add_room_items();

}

public int
connect_environment()
{
    map(Rooms, &->connect_rooms() @ &operator([])(, 1));

/*    query_room(R_LEFT,M_OBJECT)->connect_rooms();
    query_room(R_RIGHT,M_OBJECT)->connect_rooms();
    if (query_leader())
        query_room(R_FRONT,M_OBJECT)->connect_rooms();

    if (query_rear())
    {
        query_room(R_BACK,M_OBJECT)->connect_rooms();
    }
*/
    return 1;
}

public int
add_room_item(mixed names,mixed desc, mixed room)
{
    query_room(room, M_OBJECT)->add_item(names,desc);
    return 1;
}

public int
add_global_item(mixed names,mixed desc)
{
    add_room_item(names,desc, R_LEFT);
    add_room_item(names,desc, R_RIGHT);
    add_room_item(names,desc, R_FRONT);
    add_room_item(names,desc, R_BACK);
    return 1;
}


/***************** ACTION CODE FOR DEFAULT WAGON ***************/

/*
 * Function name:  approach_caravan
 * Description:    Entering the caravan with either
 *                 approach command (enters it besides it)
 *                 or enter (enters the wagon)
 * Returns:        0 if entering fails
 *                 1 if it goes well
 */

public int
approach_caravan(string str)
{

    object TempWagon;

    if (!strlen(str))
    {
        NF("Approach what?\n");
        return 0;
    }


    /* check if its this wagon they want to approach */
    if (id(str) || (str == "caravan") )
    {
        TempWagon = TO;
    }
    else
    {
        /* Then it might be another wagon? */
        TempWagon = caravan->FindWagon(str);
        if (!objectp(TempWagon))
        {
            NF("Approach what?\n");
            return 0;
        }
    }

    if (objectp(TempWagon->query_room(R_LEFT,M_OBJECT)))
    {
        write("You approach " + LANG_ADDART(TempWagon->short()) +
              " on the left side of it.\n");
        say(QCTNAME(TP) + " approaches the " + TempWagon->short() +
        " on the left " + "side of it.\n", TP);
        tell_room(TempWagon->query_room(R_LEFT,M_OBJECT), QCTNAME(TP) +
                 " approaches the caravan.\n");
        TP->move_living("M", TempWagon->query_room(R_LEFT,M_OBJECT) );
        return 1;
    }
    else
    {
        NF("You cannot approach the caravan.\n");
        return 0;
    }
}

/*
 * Function name:  burn_caravan
 * Description:    Burning down wagons code are done here
 *                 and can be enabled by add_action in
 *                 the inherited wagon.
 * Returns:        0 if burning fails
 *                 1 if it goes well
 */

public int
burn_wagon(string str)
{
    int found = 0;
    int ir;
    mixed obj;


    if (!strlen(str))
    {
        NF("Burn what?\n");
        return 0;
    }

    /* can the wagon burn :-) ? */
    if (BurnNumbers == 0)
    {
        NF("You don't find anywhere to set this wagon on fire\n");
        return 0;
    }

    /* has it already been burned down? */
    if (BurnStep > 0)
    {
        if (BurnStep > BurnNumbers)
        {
            NF("The wagon have been burned down already!\n");
            return 0;
        }
        NF("It is already burning!\n");
        return 0;
    }

    /* do the player have a burning torch? */
    obj = all_inventory(TP);

    for (ir = 0;ir < sizeof(obj);ir++)
    {
        if (IS_TORCH_OBJECT(obj[ir]) )
        {
            /*is it burning? */
            if (obj[ir]->query_lit())
                found = 1;
        }
    }

    if (!found)
    {
        NF("You need a burning torch to do that.\n");
        return 0;
    }

    start_burning();
    return 1;
}



/***************** USUAL INITIALIZATION FUNCTIONS ***************/

nomask void
create_object()
{

    set_short(carriage_short);
    set_pshort("wagon pulled by two white horses");
    set_long(carriage_long);
    add_name("wagon");

    add_prop(OBJ_I_WEIGHT, 400000);  /* Well, a wagon is heavy - 400 kg...*/
    add_prop(OBJ_I_VOLUME, 400000);  /* Large volume too :) */

    create_krynn_wagon();

}

public void
init()
{
    ::init();

    /* default mappings */

    //add_action(enter_caravan, "enter");
    add_action(approach_caravan, "approach");
}


public string
carriage_short()
{
        return "wagon pulled by 2 white steeds";
}

public string
carriage_long()
{
    int     s;
    string  long_descf;

   long_descf = "This is a wagon currently being pulled by two white steeds";
   return BSN(long_descf);
}



void
move_non_living(object someroom)
{
    mixed obj;
    int ir;

    if (objectp(someroom))
    {
        if (someroom == query_room(R_WAGON,M_OBJECT))
            return;

        obj = FILTER_DEAD(all_inventory(someroom));

        obj = filter((obj), &not() @ &->query_prop(OBJ_M_NO_GET));

        map(obj, &->move(E(TO)));

/*
        obj = all_inventory(someroom);
        for (ir = 0;ir < sizeof(obj);ir++)
        {
            if (!living(obj[ir]))
            {
                if (!obj[ir]->query_prop(OBJ_M_NO_GET))
                    obj[ir]->move(E(TO));
            }
        }
*/
    }
}

public void
wagon_move(string MoveTo, string dir)
{
//    DEBUG_MSG("MOVING" + TO->short() );
    /*lets tell the ones inside the caravan that we're moving*/

    map(Rooms, &tell_room(, "You travel along with the " + TO->short() +
                        ", as it leaves " + dir + ".\n") @ &operator([])(, 1));

    map(Rooms, move_non_living @ &operator([])(, 1));

    move(MoveTo);
    //DEBUG_MSG("I am wagon: " + TO->short() + " Moving to: " + MoveTo);

}


/*********************** BURN CODE ***********************/
/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/

public void
show_burn()
{
    int ran;
    object WagonBack;
    WagonBack = query_back_wagon();

    /* only every fifth or so burn will result in next burn level reached */

    ran = random(100);
    switch (ran)
    {
        /* 80 % chance that we dont reach next level */
        case 5..80:
        {
            map(Rooms, &tell_room(,"The " + TO->short() +
                                    " roars with fire.\n") @ &operator([])(, 1));
            tell_room(E(TO),  "The " + TO->short() + " roars with fire.\n");
            Burn_Id = set_alarm(5.0, 0.0, show_burn);
            break;

        }
            /* next level - 20% chance */
        default:
        {
            DEBUG_MSG("in default burn : " + BurnStep + " out of : " + BurnNumbers);
            BurnStep++;

            map(Rooms, &tell_room(, BurnMsg[BurnStep][ROOM_MSG] ) @ &operator
            ([])(, 1));
            tell_room(E(TO),  BurnMsg[BurnStep][ROOM_MSG]);

            if (BurnStep < BurnNumbers)
            {
                DEBUG_MSG("set new alarm");
                Burn_Id = set_alarm(5.0, 0.0, show_burn);
            }

            /* Oh damn, we took so much firedamage that we can't move
               with the caravan anymore :-) */
            if (BurnDamageTooMuch == BurnStep)
                TO->remove_wagon();
        }
    }

    query_room(R_WAGON,M_OBJECT)->burn_actions();
}


public int
start_burning()
{
    DEBUG_MSG("start burning");

    if (BurnNumbers == 0 || BurnStep > 0)
        return 0;

    BurnStep = 1;

    write(BurnMsg[BurnStep][ROOM_MSG]);
    map(Rooms, &tell_room(, QCTNAME(TP) + BurnMsg[BurnStep][IGNITION_MSG], TP )
                            @ &operator([])(, 1));
    tell_room(E(TO),   QCTNAME(TP) + BurnMsg[BurnStep][IGNITION_MSG], TP);
    Burn_Id = set_alarm(5.0, 0.0, show_burn);
    return 1;

}

public int
i_am_burned_down()
{
    if (BurnDamageTooMuch <= BurnStep && BurnDamageTooMuch > 0)
        return 1;
    return 0;
}


