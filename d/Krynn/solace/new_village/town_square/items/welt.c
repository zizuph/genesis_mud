/* 
** Welt For Zahrtok's Whip
** Set In Motion By Leia
** Coding Made Possible By Louie
** June 19, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <std.h>
#include <stdproperties.h>

private int alarm;
private string welt_location = "face";
public void set_welt_location(string str);

void
create_object()
{
    set_name("_leia_welt");
    add_name("welt");
    set_short("you shouldn't see this welt");
    set_long("This is a swollen red welt that you should not see.\n");
    
    //Don't see it
    set_no_show();

    //Lightweight and oh so clingy
    add_prop(OBJ_M_NO_DROP, 1);
    //add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME,  0);

}

public void
set_welt_location(string str)
{
    welt_location = str;
}

//When the welt enters a player, welt them
void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    if (living(to)) {
        to->add_subloc("_welt_"+welt_location, TO);
        if (alarm) {
            remove_alarm(alarm);
        }
        alarm = set_alarm(600.0, 0.0, &remove_object());
    }

    if (living(from)) {
        from->remove_subloc("_welt_"+welt_location);
    }

}

string
show_subloc(string subloc, object me, object for_obj)
{
    //What they see in their inventory
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        //return "You have a painful red welt on your "+welt_location+".\n";
        return "";
 
    //What they see when they examine themselves
    if (for_obj == me) {
        return "You have a painful red welt on your "+welt_location+".\n";
    } else {
        //What others see when they examine the welt-haver
        return C(PRONOUN(me)) + " has a painful red welt on "+
        HIS(me)+ " "+welt_location+".\n";
    }

}
