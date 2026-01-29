/* The apollyon room. ~solace/puzzle/locations/apollyon */

#include "../defs.h"
#include "/sys/macros.h"

inherit ROOM_DEFS;

#define PASSWORDS ({ "yellowstone", "zanbar", "weaseltongue", "dree", \
                     "hoggle", "galleykeep", "nimbicus", "mutilation", \
                     "chattermatter", "romeena", "marrangha", "durdinath", \
                     "sculliweed", "snattacat", "ophidiotaur", "deathless" })

string password;
int revolve_alarm, facing; /* !facing ? "south" : "north" */

string query_password()
{
    return password;
}

void set_password()
{
    password = PASSWORDS[random(sizeof(PASSWORDS))];
}

void reset_puzzle_room()
{
    int i;
    string *exits;

    facing = 0;
    exits  = query_exit_cmds();

    for(i = 0; i < sizeof(exits); i++)
        remove_exit(exits[i]);

    add_exit(LOCATIONS + "tuttivillus", "south", 0, 1);
    set_password();
}

void create_puzzle_room()
{
    set_short("The Apollyon room");
    set_long("@@long_description");

    add_item("sign", "The sign is rectangular in shape and has sharp angular "+
        "words etched into its obnsidian surface.\n");

    add_item("lantern", "The lantern is made from a translucent crystalline "+
        "material which glows with a strong light from the small bowl of "+
        "burning pitch inside it.\n");

    add_item(({"wall", "walls", "floor", "ceiling"}), "It seems to be "+
        "constructed from a very smooth metal of a dark grey colour without "+
        "surface etchings or joins between sections.\n");

    add_item(({"metal", "smooth metal", "flawlessly smooth metal"}), "The "+
        "metal that composes the walls, floor and ceiling is without features "+
        "and joins and makes the room look quite bizarre. It is made from an "+
        "unknown substance of a dark grey colour and reflects no light.\n");

    add_item(({"doorway", "rectangular doorway"}), "The doorway is just an "+
        "area of the wall where there is no wall; it does not abruptly stop, "+
        "but just seems to leave solidity and gain insolidity. You notice "+
        "that it is leading @@door_direction@@.\n");

    reset_puzzle_room();
}

void init()
{
    ::init();

    add_action("do_read", "read");
    add_action("check_say", "say");
    add_action("check_say", "rsay");
}

int check_say(string str)
{
    if(L(str) == password)
        if(!sizeof(get_alarm(revolve_alarm)))
            revolve_alarm = set_alarm(1.0, 0.0, "revolve_room");

    return 0;
}

int do_read(string what)
{
    if(!strlen(what))
        return 0;

    if(what == "sign")
    {
        write("The sign reads:\n\n");

        seteuid(getuid(TO));
        cat(MISC + "apollyon_sign.txt");

        tell_room(TO, QCTNAME(TP)+" reads the sign on the wall.\n", TP);
        return 1;
    }
    else
        return 0;
}

string door_direction()
{
    return(facing ? "north" : "south");
}

string long_description()
{
    return "You find yourself in a moderately large circular room. The "+
        "walls, floor and ceiling are composed of a flawlessly smooth "+
        "metal without distinct joins. The only things of interest that "+
        "you can see here are a lantern hanging from the ceiling, a sign "+
        "on the wall and rectangular doorway leading "+(facing ? "north" : 
        "south")+".\n";
}

int revolve_room()
{
    object tutt, shai;

    shai = find_object(LOCATIONS + "shaitan");
    tutt = find_object(LOCATIONS + "tuttivillus");

    if(!objectp(shai))
    {
        (LOCATIONS + "shaitan")->teleledningsanka();
        shai = find_object(LOCATIONS + "shaitan");
    }

    if(!objectp(tutt))
    {
        (LOCATIONS + "tuttivillus")->teleledningsanka();
        shai = find_object(LOCATIONS + "tuttivillus");
    }

    if(!facing)
    {
        tell_room(shai, "The curved metallic area of the south wall slides "+
            "away with a harsh grating noise to reveal an entrance to "+
            "another room.\n");

        tell_room(tutt, "The entrance in the north wall closes over with a "+
            "harsh grating noise until nothing is left but a curved "+
            "metallic area.\n");

        tell_room(TO, "The whole room suddenly revolves with a harsh "+
            "grating noise. You are now facing north.\n");

        remove_exit("south");
        add_exit(LOCATIONS + "shaitan", "north", 0, 1);

        tutt->remove_exit("north");
        shai->add_exit(LOCATIONS + "apollyon", "south", 0, 1);
    }
    else
    {
        tell_room(shai, "The entrance in the south wall closes over with a "+
            "harsh grating noise until nothing is left but a curved "+
            "metallic area.\n");

        tell_room(tutt, "The curved metallic area of the north wall slides "+
            "away with a harsh grating noise to reveal an entrance to "+
            "another room.\n");

        tell_room(TO, "The whole room suddenly revolves with a harsh "+
            "grating noise. You are now facing south.\n");

        remove_exit("north");
        add_exit(LOCATIONS + "tuttivillus", "south", 0, 1);

        shai->remove_exit("south");
        tutt->add_exit(LOCATIONS + "apollyon", "north", 0, 1);
    }

    facing ^= 1;
    return 1;
}





