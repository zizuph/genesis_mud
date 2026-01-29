/* My workroom! Good innit? X^)   /d/Krynn/mucalytic/workroom */

inherit "/std/room";

#include "master_defs.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#define LOG_FILE        ROOT + "log/enter"

int alarm_id;

void create_money();

void create_room()
{
    set_short("Mucalytic's workroom");
    set_long("@@long_desc");

    add_exit("@@goto_start", "start");
    add_exit(DOMAIN + "common/domain_entr", "info", "@@check");
    add_exit("/d/Genesis/wiz/post", "mail", "@@check");
    add_exit(PUZZLE_QUEST + "locations/entrance", "puzzle", "@@check");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
}

void init()
{
    ::init();

    add_action("create_money","create");

    alarm_id = set_alarm(1.0, -1.0, "who_enters");
}

void long_desc()
{
    cat(ROOT + "workroom_desc.txt");
}

string goto_start()
{
    return (string)this_player()->query_default_start_location();
}

int check()
{
    string name = this_player()->query_real_name();
    int level = this_player()->query_wiz_level();

    if(name != "mucalytic" && name != "mucalyticjr" && level < 15)
    {
        write("You try to walk through the portal, but somehow fail.\n");
        say(QCTNAME(this_player())+" tries to walk through the portal, but "+
            "somehow fails.\n");
        return 1;
    }
    return 0;
}

static create_money(str)
{
    int amount;
    object money;
    string type, name = this_player()->query_real_name();

    if(name != "mucalytic" && name != "mucalyticjr")
    {
        notify_fail("Nothing happens.\n");
        return 0;
    }

    sscanf(str, "%d %s", amount, type);

    if(type == "copper" || type == "silver" || type == "gold" ||
       type == "platinum")
    {
        if(amount > 1)
        {
            write("You recieve "+amount+" "+type+" coins.\n");
            say(QCTNAME(this_player())+" creates some money.\n");
        }
        else if(amount == 1)
        {
            write("You receive 1 "+type+" coin.\n");
            say(QCTNAME(this_player())+" creates a coin.\n");
        }
        else
        {
            amount = 0;
        }
    }
    switch(type)
    {
    case "copper":
        {
            money = MONEY_MAKE_CC(amount);
            break;
        }
    case "silver":
        {
            money = MONEY_MAKE_SC(amount);
            break;
        }
    case "gold":
        {
            money = MONEY_MAKE_GC(amount);
            break;
        }
    case "platinum":
        {
            money = MONEY_MAKE_PC(amount);
            break;
        }
    default:
        {
            notify_fail("Nothing happens!\n");
            return 0;
        }
    }
    money->move(this_player());
    return 1;
}

int who_enters()
{
    string name = this_player()->query_real_name();

    if(name != "mucalytic" && name != "mucalyticjr")
    {
        write_file(LOG_FILE, name+" entered at "+ctime(time())+"\n");
        return 1;
    }
    return 0;
}
