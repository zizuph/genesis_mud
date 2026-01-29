/*
 * /d/Gondor/guilds/rangers/soul/stealth.c
 *
 * Included in the soul. Ability to toggle stealth on or off.
 *
 * Originally coded by Elessar I think, but there were no credits.
 *
 * Modification log:
 *
 * Recode by Gwyneth 4/13/01
 */
#include <macros.h>

#define STEALTH_OFF    0
#define STEALTH_ON     1
 
int
stealth_mode(string str)
{
    int mode = this_player()->query_autosneak();

    if (!strlen(str))
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
            write("You " + (mode == STEALTH_ON ? "are" : "are not") +
                 " being stealthy.\n");
            return 1;
        }
        else if (str == "on")
        {
            if (mode == STEALTH_ON)
            {
                notify_fail("You are already being stealthy.\n");
            }
            else
            {
                write("You prepare to move stealthily around.\n");
                this_player()->set_autosneak(1);
                say(QCTNAME(this_player()) + " crouches down a bit.\n", 
                    this_player());
                return 1;
            }
        }
        else if (str == "off")
        {
            if (mode == STEALTH_OFF)
            {
                notify_fail("You were not attempting stealthiness in the " +
                    "first place.\n");
            }
            else
            {
                write("You cease being stealthy.\n");
                this_player()->set_autosneak(STEALTH_OFF);
                say(QCTNAME(this_player()) + " straightens up.\n");
                return 1;
            }
        }
    }

    return 0;
}
