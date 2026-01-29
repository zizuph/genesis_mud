/* This room controls the fog that creeps into the hills now and again.
 *
 * ~mucalytic/hills/hill_control
 */

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

int fog_alarm;

void create_room()
{
    set_short("The control room for the foot-hills of Sha'ang'sei");
    set_long("This room is devoid of everything. You hear a faint humming "+
        "sound coming from nearby though. You guess magic is at work here. "+
        "Although you cannot see, it you guess that there is an exit to "+
        "your start position nearby.\n");

    add_exit("@@goto_start", "start", 0, 1);

    set_alarm(1.0, 60.0, "create_fog");

    add_prop(ROOM_I_INSIDE, 1);
}

string goto_start()
{
    string start;

    start = (string)TP->query_default_start_location();

    if(!stringp(start))
    {
        start = (string)TP->query_temp_start_location();

        if(!stringp(start))
            start = SHAANGSEI + "shops/gen_store";
    }
    return start;
}

void create_fog()
{
    int chance;

    chance = 2; // 2% chance of fog entering the foothills every minute.

    if(random(100) < chance)
        if(!sizeof(get_alarm(fog_alarm)))
            fog_alarm = set_alarm(10.0, 0.0, "fog_roll_in", 0);
}

void fog_roll_in(int pos)
{
    int i;
    object room;

    if(pos < 8)
    {
        for(i = 0; i > -1; i++)
        {
            if(sizeof(ORDER[pos]) != i)
            {
                room = find_object(LOCATIONS + ORDER[pos][i]);

                if(objectp(room))
                    room->become_fogbound();
            }
            else
                break;
        }

        pos ++; fog_alarm = set_alarm(5.0, 0.0, "fog_roll_in", pos);
    }
    else
        fog_alarm = set_alarm(90.0 + itof(random(90)), 0.0, "fog_roll_out", 7);
}

void fog_roll_out(int pos)
{
    int i;
    object room;

    if(pos >= 0)
    {
        for(i = 0; i > -1; i++)
        {
            if(sizeof(ORDER[pos]) != i)
            {
                room = find_object(LOCATIONS + ORDER[pos][i]);

                if(objectp(room))
                    room->become_clear();
            }
            else
                break;
        }

        pos--; fog_alarm = set_alarm(5.0, 0.0, "fog_roll_out", pos);
    }
}

int query_light_cond(string str)
{
    int line, i, j;
    string filepath;
    mixed *call = get_alarm(fog_alarm);

    sscanf(str, LOCATIONS +"%s", filepath);

    if(!sizeof(call))
        return(50 + random(50)); // No fog.

    if(call[1] == "fog_roll_in")
    {
        line = call[4][0];

        if(line)
        {
            for(i = 0; i < line; i++)
            {
                j = 0;

                while(sizeof(ORDER[i]) != j)
                {
                    if(ORDER[i][j] == filepath)
                        return -99;
                    j++;
                }
            }
            return 50 + random(50);
        }
        return -99;
    }
    else if(call[1] == "fog_roll_out")
    {
        line = call[4][0];

        if(line != 7)
        {
            for(i = 7; i > line; i--)
            {
                j = 0;

                while(sizeof(ORDER[i]) != j)
                {
                    if(ORDER[i][j] == filepath)
                        return -99;
                    j++;
                }
            }
            return 50 + random(50);
        }
        return -99;
    }
}
