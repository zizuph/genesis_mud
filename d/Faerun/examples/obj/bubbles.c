/*
 * Bottle of soap for blowing bubbles
 * By Finwe, September 2001
 */


#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";
inherit "/lib/keep";

int bubble_count = 100;


create_object()
{
    set_short("crystal phial");
    set_adj("crystal");
    set_name(({"phial"}));
    set_pname("crystal phials");
    set_long("This is a crystal phial. It contains a soapy solution used " +
        "to blow bubbles. A metal stick with some holes stands vertically " +
        "inside the bottle. The phial is @@bubble_status@@.\n");
}


init()
{
    ::init();
    add_action("blow_bubbles", "blow");
}

int
query_bubbles_bottle()
{
    return 1;
}

string bubble_status()
{
    switch(bubble_count)
    {
        case 90..100:
            return "full";
            break;
        case 75..89:
            return "more than half full";
            break;
        case 50..74:
            return "about half full";
            break;
        case 25..49:
            return "less than half full";
            break;
        case 1..24:
            return "almost empty";
            break;
        default:
            return "empty";
    }
}

string blow_bubbles(string str)
{
    switch(str)
    {
        case "bubbles" :
            if(bubble_count > 0)
            {
                write("You pull the metal stick out of the phial and " +
                "blow on it. A stream of bubbles shoot up into the air. " +
                "They float down to the ground, popping as they fall.\n");
                say(QCTNAME(this_player()) + " pulls a metal stick out " +
                "of a crystal phial and blows on it. A stream of bubbles " +
                "shoot up into the air. They slowly float down to the " +
                "ground, popping as they fall.\n");
                --bubble_count; /* decrease bubble count */
                return "";
            }
            else
            {
                write("You pull the metal stick out of the phial and " +
                "look at it. The crystal phial is empty.\n");
                return "";
            }
    }
}


public void
init_recover(string arg)
{
    init_keep_recover(arg);
    sscanf(arg, "%d*%s", bubble_count, arg);
}
