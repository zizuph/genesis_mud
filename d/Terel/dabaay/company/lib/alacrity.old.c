// Alacrity
// Special ability of the fighters of the Company
// Adds LIVE_I_QUICKNESS to the player dependent on skill 
// and guildstat.
// 
// Shinto, 7-30-00
// Revisions:
//

#include "/d/Terel/include/Terel.h"
#include "company.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

int quickness = (TP->query_skill(COMP_ALACRITY) + TP->query_stat(7)) / 2.2;
int duration = (TP->query_skill(COMP_ALACRITY) + TP->query_stat(7)) / 4;


void end_alacrity();
void reset_alacrity();
void message_one();
void message_two();
void message_three();
void message_four();

int
alacrity()
{
    int quickness, duration, mess_dur, alarm_id1;

    // Must be in combat to perform alacrity.
    if(!TP->query_attack())
    {
        write("You can't perform that ability if your not in combat.\n");
        return 0;
    }
    // Must be completely sober.
    if(TP->query_intoxicated() > 0)
    {
        write("You can't perform that ability while drunk.\n");
        return 0;
    }
    // Check to see if player is already using alacrity.
    if(TP->query_prop(LIVE_I_ALACRITY))
    {
        write("You are already using that ability.\n");
        return 0;
    }
    // Check to see if alacrity is reseting
    if(TP->query_prop(LIVE_I_ALACRITY_RESET))
    {
        write("You can't use that ability again yet.\n");
        return 0;
    }
    // Determine how much speed is added and make sure it doesn't exceed 100.
    if(quickness >= 100)
    {
        quickness = 100;
    }
    // Determine duration and make sure it doesn't exceed 100.

    if(duration >= 100)
    {
        duration = 100;
    }

    // Set the props for the speed and performing the ability.
    TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + quickness);
    TP->add_prop(LIVE_I_ALACRITY, 1);
    write("You begin alacrity.\n");


    // Send our messages.
    set_alarm(20.0, -1.0, "message_one");

    return 1;
}

void
message_one()
{
    write("Message one for alacrity.\n");
    if(duration > 20)
    {
        set_alarm(20.0, -1.0, "message_two");
        return;
    }
    end_alacrity();
    return;
}

void
message_two()
{
    write("Message two for alacrity.\n");
    if(duration > 40)
    {
        set_alarm(20.0, -1.0, "message_three");
        return;
    }
    end_alacrity();
    return;
}

void
message_three()
{
    write("Message three for alacrity.\n");
    if(duration > 60)
    {
        set_alarm(20.0, -1.0, "message_four");
        return;
    }
    end_alacrity();
    return;
}

void
message_four()
{
    write("Message four for alacrity.\n");
    if(duration > 80)
    {
        set_alarm(20.0, -1.0, "end_alacrity");
        return;
    }
    end_alacrity();
    return;
}

void
end_alacrity()
{
    TP->remove_prop(LIVE_I_ALACRITY);
    TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - quickness);
    TP->add_prop(LIVE_I_ALACRITY_RESET,1);
    write("Alacrity has ended.\n");
    set_alarm(60.0, -1.0, "reset_alacrity");
    return;
}

void
reset_alacrity()
{
    TP->remove_prop(LIVE_I_ALACRITY_RESET);
    write("You can use alacrity again.\n");
    return;
}


