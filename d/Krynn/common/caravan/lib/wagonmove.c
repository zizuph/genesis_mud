/***************** MOVEMENT CODE FOR A CARAVAN LEADER ***************/



public void    tour_move();
public void    start_movement();


static int     Move_Id,
               Turn_Id,
               Step;


mixed *MyRoute = ({});




public void
get_tour()
{
    remove_alarm(Turn_Id);
    Turn_Id = 0;

    Step = -1;
    Move_Id = set_alarm(15.0, 0.0, tour_move);
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
        /*error what to do?*/
        tell_room(E(MyWagons[0]), "The caravan seems unable to move.\n");
        return;
    }



    if((ir = member_array(MyRoute[++Step], exits = get_E()->query_exit())) < 0)
    {
        /*error what to do?*/

        if (MyRoute[Step] == "PAUSE")
        {
            Move_Id = set_alarm(120.0, 0.0, tour_move);
            return;
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

