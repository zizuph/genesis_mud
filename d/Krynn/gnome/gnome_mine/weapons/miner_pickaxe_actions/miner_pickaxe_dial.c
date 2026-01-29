

string
set_mining_speed(int speed)
{
    string msg;

    if (speed > 0 && speed < 21) {
        mining_speed = speed;
        msg = "You turn the dial to the desired speed.";
        if (speed == 20){
            msg += " The lava powered pickaxe gives a low hum as you set the power to max.";
        }
    }
    else
    {
        msg = "You try to crank the dial, but the speed you want is not available.";
    }

    return msg;
}

int
do_turn_dial(string str)
{

    object tp = this_player();
    string msg;
    string *data;
    string item;
    string place;

    if (!str)
    {
        notify_fail("Try 'turn dial to <number>' E.G. 12\n");
        return 0;
    }

    data = explode(str, "dial to ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        item = data[0];
        place = "";
    }

    if (place != "" && atoi(place)) //place is numeric
    {
        msg = set_mining_speed(atoi(place));
        tp->catch_msg(msg + "\n");
        tell_room(environment(tp), QCTNAME(tp) + " moves a dial in "+tp->query_possessive()+" pickaxe.\n", tp);

        return 1;
    }

    notify_fail("Try 'turn dial to <number>' E.G. 12\n");
    return 0;       
}