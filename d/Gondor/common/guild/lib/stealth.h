#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#define STEALTH_OFF    0
#define STEALTH_ON     1

int
stealth_mode(string str)
{
    int mode;
    mode = this_player()->query_autosneak();
    if (!str)
    {
        if (mode == STEALTH_ON)
            stealth_mode("off");
        else
            stealth_mode("on");
        return 1;
    }
    else
    {
        if (str == "status")
        {
            write("You "+(mode == STEALTH_ON ? "are" : "are not")+
                  " being stealthy.\n");
            return 1;
        }
        else if (str == "on")
        {
            if (mode == STEALTH_ON)
            {
                NFN0("You are already being stealthy.");
            }
            else
            {
                write("You prepare to move stealthily around.\n");
                this_player()->set_autosneak(1);
                say(QCTNAME(this_player()) + " crouches down a bit.\n", TP);
                return 1;
            }
        }
        else if (str == "off")
        {
            if (mode == STEALTH_OFF)
            {
                NFN0("You were not attempting stealthiness in the first place.");
            }
            else
            {
                write("You cease being stealthy.\n");
                this_player()->set_autosneak(STEALTH_OFF);
                say(QCTNAME(this_player()) + " straightens up.\n", this_player());
                return 1;
            }
        }
        else
            return 0;

    }
}
