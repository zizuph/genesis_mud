/*
 * /d/Gondor/tolfalas/room/ruins_control.c
 *
 *  Toby - 24 Sept 2006
 *  
 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"


string long_desc();
string find_room();

/*          spring, summer, autumn, winter        */
#define TROLLS   ({  10, 6, 10, 14 })
#define ORCS     ({  16, 24, 22, 14 })

object *trolls;
object *orcs;

void update_season();

void control_trolls(int iSeason);
void clone_trolls();
void control_orcs(int iSeason);
void clone_orcs();

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - ruins_control]: "  + x + "\n")

public void
create_room()
{
    set_short("[control room] for the ruins on Tolfalas");
    set_long(&long_desc());

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_exit(&find_room(), "exit", 0, 2);

    reset_room();
}

string
long_desc()
{
    return "This is the [control room] for the ruins of Tolfalas where the " +
           "npc cloning will take place. Depending on season a different " +
           "amount of trolls and orcs will be cloned.\n\n"+
           "Current season is: " +CAP(CLOCK->query_season())+ "\n"+
           "Trolls to be cloned each season:\n"+
           "\tSpring: " +TROLLS[0]+ ", Summer: " +TROLLS[1]+ 
           ", Autumn: " +TROLLS[2]+ ", Winter: " +TROLLS[3]+ "\n"+
           "Orcs to be cloned each season:\n"+
           "\tSpring: " +ORCS[0]+ ", Summer: " +ORCS[1]+ 
           ", Autumn: " +ORCS[2]+ ", Winter: " +ORCS[3]+ "\n\n";
}

string
find_room()
{
    int iThe_room = random(41) + 1;
    string sThe_room = sprintf("%d", iThe_room);

    sThe_room = TOLFALAS_DIR + "room/ruins" + sThe_room;

    return sThe_room; 
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &update_season());
}

void
update_season()
{
    string sSeason = CLOCK->query_season();
    int iSeason = 1;

    if(sSeason == "spring")
       iSeason = 0;
    if(sSeason == "summer")
       iSeason = 1;
    if(sSeason == "autumn")
       iSeason = 2;
    if(sSeason == "winter")
       iSeason = 3;

    set_alarm(2.0, 0.0, &control_trolls(iSeason));
    set_alarm(5.0, 0.0, &control_orcs(iSeason));
}

void  
control_trolls(int iSeason)
{
    int num;
    int i;

    if(!pointerp(trolls))
        trolls = ({});
    else
        trolls -= ({ 0 });
    num = sizeof(trolls);

DEBUG("num (trolls) = " + num + "\tiSeason = " + iSeason);

    if(num == TROLLS[iSeason])
    {
        return;
    }

    if(num < TROLLS[iSeason])
    {
        for(i = 0; i < (TROLLS[iSeason] - num); i++)
        {
            set_alarm(7.0, 0.0, &clone_trolls());
        }
        return;
    }
    
    if(num > TROLLS[iSeason])
    {
     for(i = num; i < (num - TROLLS[iSeason]); i++)
        {
            trolls[i]->move_living("off", TO);
            trolls[i]->remove_object();
        }
        trolls -= ({ 0 });
        return;
    }
}

void
clone_trolls()
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object(TOLFALAS_DIR + "npc/rtroll");
    ob->move(TO);
    trolls = trolls + ({ ob });
}

void  
control_orcs(int iSeason)
{
    int num;
    int i;

    if(!pointerp(orcs))
        orcs = ({});
    else
        orcs -= ({ 0 });
    num = sizeof(orcs);

DEBUG("num (orcs) = " + num + "\tiSeason = " + iSeason);

    if(num == ORCS[iSeason])
    {
        return;
    }

    if(num < ORCS[iSeason])
    {
        for(i = 0; i < (ORCS[iSeason] - num); i++)
        {
            set_alarm(7.0, 0.0, &clone_orcs());
        }
        return;
    }
    
    if(num > ORCS[iSeason])
    {
     for(i = num; i < (num - ORCS[iSeason]); i++)
        {
            orcs[i]->move_living("off", TO);
            orcs[i]->remove_object();
        }
        orcs -= ({ 0 });
        return;
    }
}

void
clone_orcs()
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object(TOLFALAS_DIR + "npc/orc");
    ob->move(TO);
    orcs = orcs + ({ ob });
}
