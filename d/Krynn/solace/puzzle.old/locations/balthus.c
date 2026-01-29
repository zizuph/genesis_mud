/* The balthus room. ~solace/puzzle/locations/balthus */

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/composite.h"

inherit ROOM_DEFS;

void reset_puzzle_room()
{
    object lever;

    seteuid(getuid(TO));
    lever = clone_object(OBJECTS + "lever");

    lever->set_lever_number(2);
    lever->move(TO);

    room_add_object(OBJECTS + "window");
}

void create_puzzle_room()
{
    set_short("The Balthus room");
    set_long("This room is small and roughly cubular in proportions. The "+
        "ceiling is not flat but consists of many brick arches to form "+
        "a concave shape. The walls also seem to be made of brick; on one "+
        "you see a wooden sign and cut into another, you see a compartment "+
        "@@is_broken@@. Light comes from beneath the fine-meshed grate "+
        "that covers the floor beneath your feet. The only exit seems to "+
        "be an arched doorway leading eastwards.\n");

    add_item("light", "It seems to be coming from beneath the grate under "+
        "your feet.\n");

    add_item(({"window", "glass window", "broken window", "broken glass "+
       "window", "compartment"}), "@@window_status@@");

    add_item(({"arches", "brick arches"}), "They are very regular and seem "+
        "to be holding up the ceiling.\n");

    add_item(({"doorway", "arched doorway", "exit"}), "An exit from this "+
        "room to the room east of here. You see nothing more of interest.\n");

    add_item("ceiling", "The ceiling is made of brick and is given a curved "+
        "shape from the arches rising up from the upper-walls to the centre "+
        "of the ceiling.\n");

    add_item(({"grate", "meshed grate", "fine-meshed grate"}), "The grate "+
        "is made of many strips of a strong black metal interlayed together. "+
        "From under this, a light source of some form illuminates the room.\n");

    add_item(({"wall", "walls"}), "The walls are made of a dark red brick "+
        "and are quite square and regular on all four sides, except near "+
        "their tops, arches have been built which curve above your head to "+
        "the centre of the ceiling. In one wall, you see a wooden sign and "+
        "on another, you see a compartment @@is_broken@@.\n");

    add_exit(LOCATIONS + "azazel", "east", 0, 1);

    reset_puzzle_room();
}

void init()
{
    ::init();

    add_action("do_read", "read");
}

string is_broken()
{
    object window = present("window", TO);

    if(!objectp(window))
    {
        room_add_object(OBJECTS + "window");
        window = present("window", TO);
    }

    if(window->query_broken())
        return "from which is hanging the broken remains of a glass window";
    else
        return "which seems to be fronted by a glass window";
}

string window_status()
{
    string str;
    object *cont, window = present("window", TO);

    if(!objectp(window))
        room_add_object(OBJECTS + "window");

    if(window->query_broken())
        str = "A broken window, now little more than jagged glass shards "+
            "fronting a small but roughly square compartment cut out of the "+
            "north wall. You can't see into it very well";
    else
        str =  "A glass window fronting a small but roughly square "+
            "compartment cut out of the north wall";

    if(sizeof(cont = I(window)))
    {
        if(window->query_broken())
            str += " but can just make out "+COMPOSITE_DEAD(cont);
        else
            str += ". Inside, you can see "+COMPOSITE_DEAD(cont);
    }

    return str + ".\n";
}

int do_read(string what)
{
    if(!strlen(what))
        return 0;

    if(what == "sign")
    {
        write("The sign reads:\n\n");

        seteuid(getuid(TO));
        cat(MISC + "balthus_sign.txt");

        tell_room(TO, QCTNAME(TP)+" reads the sign on the wall.\n", TP);
        return 1;
    }
    else
        return 0;
}
