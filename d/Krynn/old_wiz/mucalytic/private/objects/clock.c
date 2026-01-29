/* A clock. /d/Krynn/mucalytic/private/objects/clock */

inherit "/std/object";

#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

void create_object()
{
    set_name("parrot");
    set_adj("green feathered");
    set_short("@@short_desc");
    set_long(
"A beautiful green parrot with dark gleaming eyes and pristine feathers.\n"+
"it is obviously tame and very intelligent. In fact it is so intelligent\n"+
"that it can tell you the time if you type 'time'!\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 4000);
}

void init()
{
    ::init();

    add_action("do_squark", "time");
    add_action("do_kill", "kill");
}

int do_kill(string what)
{
    if(what == "parrot" || what == "green parrot" ||
       what == "green feathered parrot")
    {
        write("As you go to attack the parrot, it squarks loudly at you and "+
            "flies away!\n");
        say("As "+QTNAME(this_player())+" goes to attack the parrot, it "+
            "squarks loudly at "+this_player()->query_objective()+" and "+
            "flies away!\n");
        this_object()->remove_object();
        return 1;
    }
    return 0;
}

string short_desc()
{
    object env;

    env = environment(this_object());

    if(env->query_prop(LIVE_I_IS))
        return("green feathered parrot (perched on the shoulder)");
    else
        return("green feathered parrot");
}

int do_squark()
{
    int hour, minute, alt_hour;
    string day, min_desc;

    day    = extract(ctime(time()), 0, 2);
    hour   = atoi(extract(ctime(time()), 11, 12)) - 1;
    minute = atoi(extract(ctime(time()), 14, 15));

    alt_hour = hour;

    if(hour > 12)
        alt_hour = hour - 12;

    if(minute >= 0 && minute <= 30)
    {
        if(minute == 15)
            min_desc = "quarter past";
        else if(minute == 30)
            min_desc = "half past";
        else if(minute == 1)
            min_desc = LANG_WNUM(minute)+" minute past";
        else
            min_desc = LANG_WNUM(minute)+" minutes past";
    }
    else if(minute > 30)
    {
        if(minute == 45)
            min_desc = "quarter to";
        else if(minute == 59)
            min_desc = LANG_WNUM(minute)+" minute to";
        else
        {
            alt_hour++;
            if(alt_hour == 13)
                alt_hour = 1;
            min_desc = LANG_WNUM(60 - minute)+" minutes to";
        }
    }
    if(minute == 0)
    {
        write("The parrot on your shoulder squarks: The time is "+alt_hour+
            " o'clock.\n");
        say("The parrot on "+QTNAME(this_player())+"'s shoulder squarks: "+
            "The time is "+alt_hour+" o'clock.\n");
        return 1;
    }
    else
    {
        write("The parrot on your shoulder squarks: The time is "+min_desc+
            " "+LANG_WNUM(alt_hour)+".\n");
        say("The parrot on "+QTNAME(this_player())+"'s shoulder squarks: "+
            "The time is "+min_desc+" "+LANG_WNUM(alt_hour)+".\n");
        return 1;
    }
}
