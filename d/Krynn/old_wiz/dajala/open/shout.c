inherit "/std/object";

#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define TO      this_object()
#define TP      this_player()
#define C(str)  capitalize(str)
#define E(ob)   environment(ob)

void create_object()
{
    set_name("shouter");
    set_no_show();

    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 55);
}

void init()
{
    ::init();

    add_action("do_shout", "shout");
}

int do_shout(string str)
{
    string recurrroom, race, sex, func;
    mixed *myexits, recurexits;
    object *roomobjects, *playersinroom, obj, room, blah;
    int racenum, arrsize, exitcount, recurrence = 2, i, k;

    if(!str || str == "")
    {
        write("Shout what?\n");
        return 1;
    }

    obj = E(TO);

    if(obj->query_npc() || !obj->query_prop(LIVE_I_IS))
        return 0;

    myexits = E(obj)->query_exit();
    arrsize = sizeof(myexits);
    exitcount = (arrsize + 1) / 3;

    write("There are "+exitcount+" exits from this room.\n");

    if(!exitcount)
    {
        write("Scan can go no further.\n");
        return 1;
    }

    racenum = TP->query_gender();
    race = LANG_ADDART(TP->query_race_name());

    if(racenum == 1)
        sex = "male";
    else if(racenum == 0)
        sex = "female";

    while(exitcount > 0)
    {
        recurrroom = myexits[((exitcount - 1) * 3)]; // Room path.

        write("Room path = ["+recurrroom+"] exitcount = ["+exitcount+"]\n");

        if(sscanf(recurrroom, "@@%s", func) ||
           sscanf(recurrroom, "@@%s@@", func))
            exitcount--;
        else
        {
            if(!find_object(recurrroom))
                recurrroom->load_me();

            i = 0;
            k = 0;
            room = find_object(recurrroom);
            roomobjects = all_inventory(room);

            while(i < sizeof(roomobjects))
            {
                if(roomobjects[i]->query_prop(LIVE_I_IS) &&
                  !roomobjects[i]->query_npc())
                {
                    ({ blah }) = roomobjects[i];
                    playersinroom[k] = ({ blah });
                    k++;
                }
                i++;
            }

            i = 0;

            while(i < k)
            {
                write("Player: "+C(playersinroom[i]->query_real_name())+".\n");

                if(playersinroom[i]->query_met(TP))
                    playersinroom[i]->catch_msg(C(TP->query_real_name())+
                        " shouts: "+str+"\n");
                else
                {
                    if(racenum != 2)
                        playersinroom[i]->catch_msg("You hear a "+sex+" "+
                            race+"'s voice shouting: "+str+"\n");
                    else
                        playersinroom[i]->catch_msg("You hear a "+race+
                            " voice shouting: "+str+"\n");
                }
                i++;
            }
            write("End reached.\n");
            exitcount--;
        }
    }
    return 1;
}
