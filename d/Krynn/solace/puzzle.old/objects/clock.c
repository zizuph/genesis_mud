/* A grandfather clock. ~solace/puzzle/objects/clock */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"
 
int alarm1, alarm2, cuckoo_got, hour = 11, min = 59, sec = 0;

#define TOCK ({ 0, 10, 20, 30, 40, 50 })
#define TICK ({ 5, 15, 25, 35, 45, 55 })
  
#define ACTION ({ "Suddenly, a small hatch opens in the clock.",            \
                  "A cuckoo sproings out on a spring and warbles merrily!", \
                  "Just as suddenly, the hatch closes and the cuckoo "+     \
                  "disappears."                                             })

void create_object()
{
    set_name("clock");
    set_adj("old");
    add_adj("grandfather");
    set_long("@@long_desc");

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_M_NO_GET, C(LANG_THESHORT(TO))+" is far too heavy to lift.\n");
}

void init()
{
    ::init();

    add_action("get_cuckoo", "get");
    add_action("get_cuckoo", "take");
    add_action("get_cuckoo", "grab");
    add_action("get_cuckoo", "snatch");
    add_action("attach_pendulum", "put");
    add_action("attach_pendulum", "attach");
}

int attach_pendulum(string str)
{
    string parse_str;
    object pendulum, obj;

    parse_str = "%o 'on' / 'to' [brass] 'ring' [in] [clock] / [chamber]";

    if(!strlen(str))
    {
        notify_fail(C(query_verb())+" what?\n");
        return 0;
    }

    if(parse_command(str, TP, parse_str, obj))
    {
        if(MASTER_OB(obj) != OBJECTS + "pendulum")
        {
            notify_fail("You can't attach that to the ring in the clock!\n");
            return 0;
        }

        write("You "+query_verb()+" the pendulum "+(query_verb() == "put" ?
            "on" : "to")+" the brass ring in the chamber of the clock and "+
            "it starts to swing from side to side.\n");

        say(QCTNAME(TP)+" attaches a pendulum to the grandfather clock.\n");

        obj->remove_object();

        alarm1 = set_alarm(1.0, 1.0, "increment_time");
    }
    else
        write(C(query_verb())+" what?\n");

    return 1;
}
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*
 * Every five seconds the clock will tick or tock. Every five minutes, the   *
 * cuckoo will appear. The cuckoo has to be snatched away whilst it is there *
 *=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void increment_time()
{
    sec++;

    if(member_array(sec, TICK) != -1)
        tell_room(E(TO), C(LANG_THESHORT(TO))+" ticks.\n");

    if(member_array(sec, TOCK) != -1)
        tell_room(E(TO), C(LANG_THESHORT(TO))+" tocks.\n");

    if(sec == 60)
    {
        min++;
        sec = 0;
    }
    if(min == 60)
    {
        hour++;
        min = 0;
    }

    if(hour == 13)
        hour = 1;

    if((member_array(min, TOCK) != -1) && !cuckoo_got)
        if(!pointerp(get_alarm(alarm2)))
            alarm2 = set_alarm(1.0, 10.0, "produce_cuckoo");
}

void produce_cuckoo()
{
    int i;

    if((member_array(min, TOCK) != -1) && !cuckoo_got)
    {
        for(i = 0; i < sizeof(ACTION); i++)
            tell_room(E(TO), ACTION[i] + "\n");
    }
    else
        remove_alarm(alarm2);
}

int get_cuckoo(string str)
{
    int i;
    object hands, give_obj;
    string get_str, parse_str1, parse_str2;

    parse_str2 = "'pendulum' [from] [the] [old] [grandfather] [clock]";
    parse_str1 = "[small] [yellow-plumed] 'cuckoo' [from] [the] [old] "+
                 "[grandfather] [clock]";

    if(!strlen(str))
        return 0;

    if(parse_command(str, TP, parse_str1))
    {
        if(pointerp(get_alarm(alarm2)))
        {
            seteuid(getuid(TO));

            hands    = present("hands", TP);
            give_obj = clone_object(CREATURES + "cuckoo");
            get_str  = "as it sproings out of "+LANG_THESHORT(TO);

            if(hands->manip_drop_get(TP, give_obj, query_verb(), get_str));
            {
                cuckoo_got = 1;
                remove_alarm(alarm2);
            }
            return 1;
        }
        else
            return 0;
    }
    else if(parse_command(str, TP, parse_str2))
    {
        if(pointerp(get_alarm(alarm1)))
        {
            seteuid(getuid(TO));

            hands    = present("hands", TP);
            get_str  = "from "+LANG_THESHORT(TO);
            give_obj = clone_object(OBJECTS + "pendulum");

            if(hands->manip_drop_get(TP, give_obj, query_verb(), get_str));
            {
                remove_alarm(alarm1);

                if(pointerp(get_alarm(alarm2)))
                    remove_alarm(alarm2);
            }
            return 1;
        }
        else
            return 0;
    }

    notify_fail(C(query_verb())+" what?\n");
    return 0;
}

string long_desc()
{
    string dhour, dmin, dsec, str;

    dhour = LANG_WNUM(hour);

    if(min == 0)
        dmin = "twelve";
    else
        dmin = LANG_WNUM(min);

    if(sec == 0)
        dsec = "zero";
    else
        dsec = LANG_WNUM(sec);

    str = "A tall wooden clock reaching almost to the ceiling. At its summit, "+
        "below some ornamental carving is a round white clock face, the hour "+
        "hand pointing to "+dhour+", the minute hand to "+dmin+" and a "+
        "second hand pointing to "+dsec+". ";

    if(pointerp(get_alarm(alarm1)))
        str += "The second hand is moving briskly around the face and a "+
            "pendulum in a chamber below swings from side to side with a "+
            "tick-tock sound.\n";
    else
        str += "You notice that the hands aren't moving, because there "+
            "doesn't seem to be a pendulum in its chamber; all there is is "+
            "a solitary brass ring connected to the internal workings.\n";

    return(str);
}

int not_wanted(object obj)
{
    return(!obj->query_no_show() & !obj->query_prop(OBJ_M_NO_DROP));
}
