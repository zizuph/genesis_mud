/* The mammon room. ~solace/puzzle/locations/mammon */

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "../../../mucalytic/sys/language.h"

inherit ROOM_DEFS;

#define ROOM_TOGO ({ "mammon", "diabolus", "mephisto", "balthus", "azazel", \
                     "eblis",  "asmodeus", "abaddon",  "shaitan" })

int pull_alarm, number, result; /* 'result' is a binary op. 00, 01, 10 or 11. */

void reset_puzzle_room()
{
    found = 0; number = 0, result = 0;
}

void create_puzzle_room()
{
    set_short("The Mammon room");
    set_long("@@long_description");

    add_exit(LOCATIONS + "azazel", "southwest", 0, 1);

    add_item(({"slot", "small slot"}), "@@slot_description");

    add_item("room", "You are standing in it. (Type 'look').\n");

    add_item(({"plaque", "silver-coloured plaque"}), "@@plaque_description");

    add_item("ceiling", "It is even and white and has a lantern hanging "+
        "from it.\n");

    add_item(({"doorway", "arched doorway"}), "An exit from this room to "+
        "room southwest from here. You see nothing more of interest.\n");

    add_item("lantern", "The lantern is made from black steel and hangs "+
        "above your head from circular links attaching it to the ceiling.\n");

    add_item(({"floor", "stone", "harsh stone", "white stone", "harsh white "+
        "stone"}), "The floor is made from one large block of stone that "+
        "sparkles and shines with a clean whiteness. As you look at it more "+
        "closely, you find that it is not at all smooth, but granular, with "+
        "a texture resembling sand-paper.\n");

    add_item(({"walls", "marble", "blue marble", "unadorned marble",
        "unadorned blue marble"}), "The walls are covered entirely with a "+
        "strange ocean-blue marble through which veins of many different "+
        "colours run like clouds in a summer sky. Fixed to one of the walls "+
        "is a silver-coloured plaque, in the center of which is a small "+
        "slot.\n");

    add_search("lantern", "search", "inside", "discover", OBJECTS + "square");
}

void init()
{
    ::init();

    add_action("do_pull", "pull");

    add_action("do_insert", "slot");
    add_action("do_insert", "screw");
    add_action("do_insert", "insert");

    add_action("do_remove", "remove");
    add_action("do_remove", "unscrew");
}

string slot_description()
{
    if(number)
        return "You can barely see it, as a wooden lever has been screwed "+
            "into it.\n";
    else
        return "The slot in the middle of the plaque is round and threaded "+
            "as if something is mean to be slotted into it. You also notice "+
            "that it is hinged on either side.\n";
}

string plaque_description()
{
    string str = "The plaque is made from a thin metal, the colour of "+
        "silver. It is square, roughly the size of both your hands placed "+
        "side-by-side and is bolted to one of the walls. Right in the centre "+
        "is a hinged slot ";

    if(number)
        return str + "into which a wooden lever has been screwed.\n";
    else
        return str + "inside which run screw-threads as if something is "+
            "meant to be attached to it.\n";
}

string long_description()
{
    string str = "This room is small and almost square in shape. The walls "+
        "are unadorned blue marble and the floor is harsh white stone. A "+
        "lantern hanging from the ceiling provides a clear view of the "+
        "contents of the room. Fixed to the nearest wall is a silver-"+
        "coloured plaque in";

    if(number)
        str += "to the centre of which has been slotted a wooden lever.";
    else
        str += " the center of which, you notice a small slot.";

    return str + " An arched doorway leads away to the southwest.\n";
}

int do_pull(string str)
{
    if(!number)
        return 0;

    if(!strlen(str) || !parse_command(str, TP, "[wooden] 'lever'"))
    {
        notify_fail("Pull [what]?\n");
        return 0;
    }

    if((number & result) != number)
    {
        TP->catch_msg("You pull the wooden lever.\n");
        tell_room(TO, QCTNAME(TP)+" pulls the wooden lever.\n", TP);

        switch(number)
        {
            case 1:
                if(!sizeof(get_alarm(pull_alarm)))
                    pull_alarm = set_alarm(2.0 + itof(random(3)), 0.0, "case1");
                break;

            case 2:
                if(!sizeof(get_alarm(pull_alarm)))
                    pull_alarm = set_alarm(2.0 + itof(random(3)), 0.0, "case2");
                break;

            default:
                return 1;
        }

        result ^= number;
    }
    else
    {
        TP->catch_msg("You pull the wooden lever.\n");
        tell_room(TO, QCTNAME(TP)+" pulls the wooden lever.\n", TP);
    }
    return 1;
}

void case1()
{
    int i;
    string room;
    object jug, obj;

    seteuid(getuid(TO));
    jug = clone_object(OBJECTS + "jug");

    room = ROOM_TOGO[random(sizeof(ROOM_TOGO))];

    for(i = 0; i < sizeof(ROOM_TOGO); i++)
    {
        obj = find_object(LOCATIONS + ROOM_TOGO[i]);

        if(objectp(obj))
        {
            if(ROOM_TOGO[i] == room)
                tell_room(obj, C(LANG_ASHORT(jug))+" suddenly appears out "+
                    "of thin air and clatters to the floor.\n");
            else
                tell_room(obj, "You hear a loud metallic CLATTER from one "+
                    "of the other rooms.\n");
        }
    }

    if(!objectp(find_object(LOCATIONS + room)))
        (LOCATIONS + room)->teleledningsanka();

    jug->move(LOCATIONS + room);
}

void case2()
{
    int i;
    string room;
    object obj, apol;

    room = ROOM_TOGO[random(sizeof(ROOM_TOGO))];

    for(i = 0; i < sizeof(ROOM_TOGO); i++)
    {
        obj = find_object(LOCATIONS + ROOM_TOGO[i]);

        if(objectp(obj))
        {
            if(ROOM_TOGO[i] == "shaitan")
                break;
            else
                tell_room(obj, "You hear a harsh metallic grating noise "+
                    "coming from one of the other rooms.\n");
        }
    }

    apol = find_object(LOCATIONS + "apollyon");

    if(!objectp(apol))
    {
        (LOCATIONS + "apollyon")->teleledningsanka();
        apol = find_object(LOCATIONS + "apollyon");
    }

    apol->revolve_room();
}

int do_insert(string str)
{
    int test;
    object *obj;
    string what, pstr = "%s 'in' / 'into' [the] [small] 'slot'";

    if(!strlen(str) || !parse_command(str, TP, pstr, what))
    {
        notify_fail(C(query_verb())+" [what] into [what]?\n");
        return 0;
    }

    obj = FIND_STR_IN_OBJECT(what, TP);

    if(!sizeof(obj))
    {
        notify_fail("You don't have "+LANG_ADDART(what)+".\n");
        return 0;
    }

    if(sizeof(obj) > 1)
    {
        notify_fail("Which "+what+" do you want to "+query_verb()+
            (query_verb() == "insert" ? "" : " in")+"?\n");
        return 0;
    }

    if(number)
    {
        notify_fail("There is already a lever there!\n");
        return 0;
    }

    test = obj[0]->query_lever_number();

    if(!test)
    {
        notify_fail("You can't "+query_verb()+" that into there!\n");
        return 0;
    }

    number = test;

    write("You "+query_verb()+" "+LANG_THESHORT(obj[0])+" into the slot.\n");
    say(QCTNAME(TP)+" "+LANG_TVERB(query_verb())+" "+LANG_ASHORT(obj[0])+
        "into the slot in the plaque.\n");

    add_item(({"lever", "wooden lever"}), "A lever is protruding from a slot "+
        "in the small plaque into which it has been screwed. It is made of a "+
        "light supple wood and has the number "+LANG_WNUM(number)+" carved "+
        "into one end.\n");

    obj[0]->remove_object();
    return 1;
}

int do_remove(string str)
{
    object *obj, lever, hands;
    string what, pstr = "%s 'from' [the] [small] 'slot' / 'wall' / 'plaque'";

    if(!strlen(str))
    {
        notify_fail(C(query_verb())+" [what] from [what]?\n");
        return 0;
    }

    if(str != "slot" && str != "plaque" && !parse_command(str, TP, pstr, what))
    {
        notify_fail(C(query_verb())+" [what] from [what]?\n");
        return 0;
    }

    if(what != "lever" && str != "wooden lever")
    {
        write("You can't "+query_verb()+" that from there.\n");
        return 0;
    }

    if(!number)
    {
        notify_fail("There is no "+what+" here.\n");
        return 0;
    }

    seteuid(getuid(TO));
    lever = clone_object(OBJECTS + "lever");
    lever->set_lever_number(number);

    hands = present("hands", TP);

    if(!hands->manip_drop_get(TP, lever, "unscrew", "from the slot"))
    {
        number = 0;

        remove_item("lever");
        remove_item("wooden lever");
    }
    else
        lever->remove_object();

    return 1;
}
