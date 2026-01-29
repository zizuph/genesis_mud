/* Mucalytic's soul commands. Version 1 27-06-95. ~mucalytic/open/wiz_soul
 *                            Version 2 29-06-95.
 *                            Version 3 01-02-96.
 */

inherit "/cmd/std/command_driver";
inherit "/cmd/std/tracer_tool_base";

#include "/sys/macros.h"
#include "/sys/filepath.h"
#include "../master_defs.h"
#include "/sys/stdproperties.h"

int set_idle_message();
void dump_line(object *arr, int tab);

string get_soul_id()
{
    return "Mucalytic's Wizard soul";
}

int query_tool_soul()
{
    return 1;
}

mapping query_cmdlist()
{
    return(["elec":		"do_electricity",
            "electricity":	"do_electricity",
            "stamp":		"do_stamp",
            "rasp":		"alter_say",
            "clear":		"clear_screen",
            "cls":		"clear_screen",
            "xwhere":		"xwhere",
            "xw":		"xwhere",
            "work":		"work_place",
            "Iplus":		"trace_inventory",
            "Ip":		"trace_inventory"]);
}

/*
void using_soul(object live)
{
    set_alarm(5.0, 5.0, "set_idle_message");
}
*/

void set_idle_message()
{
    int idle_time;

    if(!objectp(TP))
	return;

    if(!interactive(TP))
	return;

    idle_time = query_idle(TP);

    if(idle_time > 300)
    {
        if(TP->query_wiz_level())
            TP->set_al_title("Idle "+idle_time / 60+" mins");

        TP->add_prop(LIVE_S_EXTRA_SHORT, " (idle "+idle_time / 60+" minutes)");
    }
    else
    {
        if(TP->query_wiz_level())
            TP->set_al_title("I'm here!");

        if(TP->query_prop(LIVE_S_EXTRA_SHORT))
           TP->remove_prop(LIVE_S_EXTRA_SHORT);
    }
}

int do_electricity(string arg)
{
    if(arg == "?")
    {
        write("Simply type 'elec' or 'electricity' for electricity to play "+
            "between your hands.\n");
        return 1;
    }

    if(TP->query_get_echo())
        write("Sparks of electricity play between your hands.\n");
    else
        write("Ok.\n");

    say("Electricity plays between "+QTNAME(TP)+"'s outstretched hands.\n");
    return 1;
}

int do_stamp(string arg)
{
    if(arg == "?")
    {
        write("Simply type 'stamp' to create a thunderous earthquake.\n");
        return 1;
    }

    if(TP->query_get_echo())
        write("You stamp on the ground, causing the it to quake and "+
            "tremble.\n");
    else
        write("Ok.\n");

    say(QCTNAME(TP)+" stamps on the ground with incredible force, causing "+
        "you to fall over clumsily as the earth quakes and trembles.\n");
    return 1;
}

int xwhere(string path)
{
    int count = 0, i = 0;
    object *people, file_object;
    string tilde_path, file_path, player_path, pathtmp, place, func, short;

    people = users();

    if(path == "?")
    {
        write("xwhere provides a list of people currently in locations with "+
            "a specified pathname. IE: 'xwhere ~Krynn/solace' will show the "+
            "names of all players in these rooms and the set_short()s of the "+
            "rooms themselves.\n");
        return 1;
    }

    if(!path || path == "")
        return 0;

    if(sscanf(path, "~%s", pathtmp))
    {
        file_path = TPATH("~", "~"+pathtmp);
        tilde_path = path;
    }
    else
    {
        file_path = path;
        tilde_path = RPATH(path);
    }

    write(LINE + "List of players in "+tilde_path+"\n" + LINE);

    while(i < sizeof(people))
    {
        if(E(people[i]))
        {
            player_path = file_name(E(people[i]));

            if(sscanf(player_path, file_path+"%s", place))
            {
                write(people[i]->query_name()+" is in ");

                if(!player_path->query_short())
                    write("a place with no description.\n");

                else if((sscanf(player_path->query_short(), "@@%s@@", func)) ||
                        (sscanf(player_path->query_short(), "@@%s", func)))
                {
                    file_object = find_object(player_path);
                    short = call_other(file_object, func);

                    write(L(short)+".\n");
                }
                else
                    write(L(player_path->query_short())+".\n");
                count ++;
            }
        }
        i++;
    }
    if(!count)
        write("There are no players currently in that area.\n");

    write(LINE);
    return 1;
}

int alter_say(string what)
{
    if(!strlen(what))
        return 0;

    if(what == "?")
    {
        write("Simply typing 'rasp <message>' will make you rasp things "+
            "rather than say them.\n");
        return 1;
    }

    if(TP->query_get_echo())
        write("You rasp: "+what+"\n");
    else
        write("Ok.\n");

    say(QCTNAME(TP)+" rasps: "+what+"\n");
    return 1;
}

int clear_screen()
{
    int i;

    for(i = 0; i < 56; i++)
        write("\n");
    return 1;
}

void dump_part(object obj, object *arr, int tab)
{
    int i;
    string str, tmp = "";

    for(i = 0; i < (tab - 2); i++)
        tmp += " ";

    str = tmp + "+ Inside "+obj->query_name()+": +";

    while(strlen(str) < 24)
        str += "-";

    write(str + "+\n");

    dump_line(arr, tab);

    tmp += "+";

    while(strlen(tmp) < 24)
        tmp += "-";

    write(tmp + "+\n");
}

void dump_line(object *arr, int tab)
{
    int i, j;
    object *inv;
    string tmp, str, tabstr = "";

    for(j = 0; j < tab; j++)
        tabstr += " ";

    for(i = 0; i < sizeof(arr); i++)
    {
        tmp = tabstr + arr[i]->query_name();
        str = extract(tmp, 0, (strlen(tmp) > 23 ? 23 : strlen(tmp)));

        write(sprintf("%-25s", str));

        tmp = RPATH(file_name(arr[i]));
        str = extract(tmp, 0, (strlen(tmp) > 54 ? 54 : strlen(tmp)));

        write(str + "\n");

        if(function_exists("create_object", arr[i]) == "/std/container")
        {
            inv  = I(arr[i]);

            if(sizeof(inv))
                dump_part(arr[i], inv, (tab + 2));
        }
    }
}

int trace_inventory(string str)
{
    object obj, *inv;

    if(str == "?")
    {
        write("Simply type 'Ip <player>' or 'Iplus <player>'. This gives a "+
            "'deep_inventory' of a person modelled on the standard tracer "+
            "command 'I(nventory)'.\n");
        return 1;
    }

    if(!strlen(str))
        obj = TI;
    else
    {
        obj = parse_list(str);

        if(!objectp(obj))
        {
            notify_fail("Ip(lus) of which object?\n");
            return 0;
        }
    }

    write(LINE+"Inventory of: "+C(obj->query_name())+" ("+
        RPATH(file_name(obj))+")\n"+LINE);

    inv = I(obj);

    dump_line(inv, 0);

    write(LINE);
    return 1;
}

int work_place(string str)
{
    int result;
    object room;
    string roompath;

    if(str == "?")
    {
        write("To use this command, type 'work here' to set the room you are "+
            "currently in. Type 'work' to go to that room.\n");
        return 1;
    }

    if(!strlen(str))
    {
        setuid();
        seteuid(getuid());

        roompath = read_file(OPEN + "work_locs/wiz.work.loc."+RNAME(TP), 1, 1);

        if(!strlen(roompath))
            write("You don't have a work location set. Type 'work ?' to "+
                "learn how to set it.\n");
        else
        {
            result = TP->move_living("X", roompath, 1);

            if(!result)
                write("Ok.\n");
            else
                write("Error ("+result+") in move_living().\n");
        }
        return 1;
    }
    else if(str == "here")
    {
        room = E(TP);

        if(!objectp(room))
            write("Error! You don't seem to be in a valid room.\n");
        else
        {
            roompath = file_name(room);

            setuid();
            seteuid(getuid());

            rm(OPEN + "work_locs/wiz.work.loc."+RNAME(TP));
            write_file(OPEN + "work_locs/wiz.work.loc."+RNAME(TP), roompath);

            write("You set the current work location to "+RPATH(roompath)+"\n");
        }
        return 1;
    }
    else
        write("Use 'work ?' for help.\n");
    return 1;
}
