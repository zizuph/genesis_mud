inherit "/d/Rhovanion/lib/room";

#define CONTROL_FILE "/d/Rhovanion/quetzl/codeideas/controller"

string exitdesc();

static int base, rand;

public nomask
create_room()
{
    set_short("Plains");
    set_long("@@londesc");

    add_item(({ "mirkwood forest", "forest", "mirkwood" }),
        "Mirkwood forest lies to the east, dark and ancient and menacing.\n");

    add_item(({ "anduin", "anduin river", "great river" }),
        "The Anduin flows through the center of the Vale, a gleaming " +
        "ribbon of silver light in the day, and scintillating flashes " +
        "in the night.\n");

    add_item(({ "misty mountains", "mountains" }),
        "The misty mountains rise above you to the west.\n");

    create_plains();
}

string londesc()
{
    string str;

    str = exitdesc();
    return "The plains of Anduin stretch out before you, vast and " +
        "timeless.  The Vale has stood since the dawn of time, since " +
        "before Mirkwood was corrupted, and it will probably stand until " +
        "the end of time.  " + str;
}

nomask void reset_plains()
{
    object ob;

    ob = find_object(CONTROL_FILE);
    reset_euid();
    if (!ob)
    {
        CONTROL_FILE->teleledningsanka();
        ob = find_object(CONTROL_FILE);
    }
    if (!ob)
        return;

    ob->establish_control(this_object());
}

create_plains()
{
}
string exitdesc()
{
    return "\n";
}
