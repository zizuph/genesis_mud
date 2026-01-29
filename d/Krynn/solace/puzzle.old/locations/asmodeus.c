/* The asmodeus room. ~solace/puzzle/locations/mammon */

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "../../../mucalytic/sys/language.h"

inherit ROOM_DEFS;

#define ROOM_TOGO ({ "asmodeus", "diabolus", "mephisto", "balthus", "azazel", \
                     "mammon",   "eblis",    "abaddon",  "shaitan" })

#define BLOCK_DESCS ({ "stone", "brown stone", "rough stone", "blocks",     \
"curved blocks", "blocks of stone", "curved blocks of stone", "blocks of "+ \
"brown stone", "curved blocks of brown stone",  "blocks of rough stone",    \
"curved blocks of rough stone", "blocks of rough brown stone", "curved "+   \
"blocks of rough brown stone" })

int pull_alarm, number, result;

void reset_puzzle_room()
{
    found = 0; number = 0, result = 0;
}

void create_puzzle_room()
{
    set_short("The Asmodeus room");
    set_long("@@long_description");

    add_exit(LOCATIONS + "azazel", "northeast", 0, 1);

    add_item(({"slot", "small slot"}), "@@slot_description");

    add_item("room", "You are standing in it. (Type 'look').\n");

    add_item(({"plaque", "copper-coloured plaque"}), "@@plaque_description");

    add_item(({"bracket", "metal bracket"}), "A bracket on the the wall, into "+
        "which has been placed a torch.\n");

    add_item(({"doorway", "arched doorway"}), "An exit from this room to "+
        "room northeast from here. You see nothing more of interest.\n");

    add_item(({"torch", "smokeless torch"}), "The torch flickers and hisses "+
        "but does not produce smoke, nor does it burn down. This is obviously "+
        "the work of magic.\n");

    add_item(({"tube", "metal tube"}), "The tube is made of a rusty coloured "+
        "metal, its diameter is about equal to that of your forearm and it "+
        "protrudes about the length of your hand from the wall.\n");

    add_item(({"crystals", "small crystals", "glittering crystals"}), "The "+
        "crystals embedded in the blocks of stone that make up the walls "+
        "are the size of grains of sand, but as the light is cast upon them, "+
        "they shine with a relentless sparkle.\n");

    add_item(BLOCK_DESCS, "The blocks of stone are slightly curved to "+
        "compensate for the roundness of the room, but the are very big "+
        "and thick. The have a rough sandy texture to them, but are also "+
        "quite damp as moisture collects on them.\n");

    add_item(({"wall", "walls"}), "The walls are curved and made from "+
        "rough brown blocks of stone. A torch is bracketted to one wall "+
        "and on the other is a copper-coloured plaque, in the center of "+
        "which is a small slot. Beneath this, a metal tube protrudes out "+
        "from the stone.\n");

    add_search(BLOCK_DESCS, "search", "", "discover behind a loose block of "+
        "stone,", OBJECTS + "star");
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
        "copper. It is square, roughly the size of both your hands placed "+
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
    string str = "You find yourself in a roughly circular room made from "+
        "curved blocks of rough brown stone in which are embedded many "+
        "small glittering crystals that reflect the light, casting rainbows "+
        "about the walls. At head-height nearby, a smokeless torch fixed to "+
        "a metal bracket burns with a faint hissing noise. Almost opposite "+
        "this but at waist height, is a copper-coloured plaque in";

    if(number)
        str += "to the centre of which has been slotted a wooden lever.";
    else
        str += " the center of which, you notice a small slot.";

    return str + " Immediately below this, a metal tube protrudes from the "+
        "wall. An arched doorway leads away to the northeast.\n";
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

    if(number == 2 || (number == 1 && !result))
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
                    pull_alarm = set_alarm(1.0, 0.0, "case2");
                break;

            default:
                return 1;
        }
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
    object key, obj;

    seteuid(getuid(TO));
    key = clone_object(OBJECTS + "cage_key");

    room = ROOM_TOGO[random(sizeof(ROOM_TOGO))];

    for(i = 0; i < sizeof(ROOM_TOGO); i++)
    {
        obj = find_object(LOCATIONS + ROOM_TOGO[i]);

        if(objectp(obj))
        {
            if(ROOM_TOGO[i] == room)
                tell_room(obj, C(LANG_ASHORT(key))+" suddenly appears out "+
                    "of thin air and clangs to the floor.\n");
            else
                tell_room(obj, "You hear a loud metallic CLANG from one "+
                    "of the other rooms.\n");
        }
    }

    if(!objectp(find_object(LOCATIONS + room)))
        (LOCATIONS + room)->teleledningsanka();

    key->move(LOCATIONS + room);
    result = 1;
}

void case2()
{
    object jug, puddle;

    jug = present("jug", TO);

    if(!objectp(jug))
    {
        puddle = present("puddle", TO);

        if(!objectp(puddle))
        {
            seteuid(getuid(TO));
            puddle = clone_object(OBJECTS + "puddle");
            puddle->move(TO);
        }

        puddle->add_water(150 + random(100));

        tell_room(TO, "Water gushes from the metal tube onto the floor.\n");
    }
    else
    {
        jug->fill_me(150 + random(100));

        tell_room(TO, "Water gushes from the metal tube into the jug!\n");

        if(jug->query_filled() == 1000)
        {
            puddle = present("puddle", TO);

            if(!objectp(puddle))
            {
                seteuid(getuid(TO));
                puddle = clone_object(OBJECTS + "puddle");
                puddle->move(TO);
            }

            puddle->add_water(150 + random(100));
            
            tell_room(TO, "Water spills over the brim of the jug onto the "+
                "floor.\n");
        }
    }
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
