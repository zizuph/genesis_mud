
#include "../guild.h"

inherit "/cmd/std/command_driver";
inherit CORELIB_DIR+"abilities";

int do_stop(string arg)
{
    
    if (!stringp(arg))
    {
        return 0;
    }

    switch (lower_case(arg))
    {
        case "savage":
        case "bgsavage":
        case "vsavage":
            if (!(ABILITY_DIR+"bite")->stop_ability(TP))
            {
                write("You are not in the middle of a savage attack.\n");
            }
            return 1;
        case "vflurry":
        case "flurry":
            if (!(ABILITY_DIR+"flurry")->stop_ability(TP))
            {
                write("You are not in the middle of a flurry attack.\n");
            }
            return 1;
        case "fighting":
        case "fights":
       
        //End combat with those who aren't in the room
        mixed enemies=TP->query_enemy(-1);
        if (!sizeof(enemies))
        {
             return 0;
        }
        enemies-=all_inventory(ENV(TP));
        if (sizeof(enemies))
        {
             TP->stop_fight(enemies);
             write("You stop your hunt.\n");
             return 1;
        }
        return 0;
    }
}

int
thirst(string str)
{
    int i;
    object *oblist;
    string msg;
  
    if (strlen(str))
    {
        if (!sizeof(oblist = parse_this(str, "[the] %l")))
        {
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
        }
  
        for (i = 0; i < sizeof(oblist); i++)
        {
            msg = oblist[i]->desc_vamp_thirst(TP);
            if (!strlen(msg))
            {
                write("You can't seem to tell.\n");
                continue;
            }
            
            write(msg);
        }

        return 1;
    }

    msg = TP->desc_vamp_thirst();
    write((strlen(msg) ? msg : "You can't seem to tell.\n"));
    return 1;
}
