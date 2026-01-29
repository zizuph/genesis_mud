/* Ashlar, 8 Jun 97 - an addiction object for Black Dragonbrew */
/* Blocks the kill command once if is in need of another drink */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#define DELAY 300.0

int alarm = 0;
int alevel = 0;
int tried_to_kill = 0;

void is_addicted();
int my_kill(string str);

void
create_object()
{
    set_name("_bd_add_");
    set_no_show();
    set_long("This is addiction.\n");
    set_short("addiction");

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();
    add_action(my_kill,"kill");
}

void
start_it()
{
    alarm = set_alarm(DELAY,0.0,&is_addicted());
}

void
satisfy()
{
    if (alarm)
    {
        remove_alarm(alarm);
        alarm = 0;
    }
    alevel = 0;
    tried_to_kill = 0;
    start_it();
}

void
is_addicted()
{
    string msg;

    if (E(TO) && (E(TO)->query_prop(LIVE_I_IS)))
    {
        switch(alevel++)
        {
            case 0:
                msg = "Another glass of Black Dragonbrew would be nice..\n";
                break;
            case 1:
                msg = "You certainly wouldn't mind another glass of Black Dragonbrew.\n";
                break;
            case 2:
                msg = "Perhaps you should get another glass of Black Dragonbrew..\n";
                break;
            case 3:
                msg = "NOW would be a good time for another glass of Black Dragonbrew.\n";
                break;
            case 4:
                msg = "You REALLY want another glass of Black Dragonbrew!\n";
                break;
            case 5:
                msg = "You feel really miserable without Black Dragonbrew.\n";
                break;
            case 6:
            case 9:
            case 11:
            case 14:
                msg = "You want Black Dragonbrew! Now!\n";
                break;
            case 7:
            case 13:
                msg = "You must have Black Dragonbrew, or you will surely perish!\n";
                break;            
            case 15:
                E(TO)->catch_msg("You shake the last of your addiction to the vicious " +
                    "Black Dragonbrew, and feel much better.\n");
                set_alarm(1.0,0.0,&remove_object());
                return;
            default:
                msg = "You feel a burning hunger for Black Dragonbrew.\n";
                break;

        }
    
        E(TO)->catch_msg("\n"+msg+"\n");
        start_it();
        tried_to_kill = 0;
    }
}

void
enter_env(object inv, object from)
{
    if (inv && !inv->query_prop(LIVE_I_IS))
        set_alarm(1.0,0.0,&remove_object());
    ::enter_env(inv,from);
}

int
my_kill(string str)
{
    if (alevel && !tried_to_kill)
    {
        write("Are you sure you wouldn't rather have another Black Dragonbrew?\n");
        tried_to_kill = 1;
        return 1;
    }
    return 0;
}
