#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>


inherit "/std/container";
string desc_lake();
int move_the_boat(string str);
int check_light();
string query_action();

void
create_container()
{
    set_name("rowing boat");
    add_name("boat");
    set_short("small rowing boat");
    set_long("This is a small and steady rowing boat. It was once "+
        "painted blue with white trim, but most of the paint has "+
        "flaked off, exposing the bare wood. " +
        "It has seen better days when it comes to maintenance, "+
        "but it was soundly constructed, so it should be secure " +
        "as long as it is not overloaded with too many passengers.\n");
    add_item(({"view","lake"}),"@@desc_lake");
    add_prop(CONT_I_RIGID, 0);          // Fixed volume
    add_prop(CONT_I_TRANSP, 1);         // Transparent
    add_prop(CONT_I_VOLUME, 1000000);  // One cubic meter
    add_prop(CONT_I_WEIGHT, 100000);    // Boat weights 100 Kg
    add_prop(CONT_I_MAX_WEIGHT, 300000);  // Max weight is 100 Kg also
    add_prop(CONT_I_MAX_VOLUME, 3000000); // Max volume is 1 cubic meter
    add_prop(ROOM_I_LIGHT, check_light());
    add_item(({"wood", "bare wood" }),
        "The wood itself is solid and sound. The paint has flaked off, "+
        "but this doesn't effect the sea-worthiness of the boat.\n");
    add_item(({"paint", "blue paint", "white paint", "white trim"}),
        "The paint, or what remains of it, is blue and white.\n");
    add_item("rock","@@desc_rock");
    add_item("tower","@@desc_tower");
    add_item("mill","@@desc_mill");
    add_item("house","@@desc_house");
    add_item("reed","@@desc_reed");
    setuid();
    seteuid(getuid());

    reset_container();
}

void
reset_container()
{

}

void
init()
{
    ::init();
    add_action("do_row","row");
    add_action("do_enter","enter");
    add_action("do_leave","leave");
    add_action("do_leave","disembark");
    add_action("do_look","look");
    add_action("do_look","l");
}



string
desc_lake()
{
    if (TO == environment(TP))
    {
        return("You look out and see "+ENV(TO)->long_description());
    }
}

int
do_look(string str)
{

    if (!str || !strlen(str))
        return 0;
    if (str == "east")
    {
        write(ENV(ENV(this_player()))->desc_east());
        return 1;
    }
    if (str == "west")
    {
        write(ENV(ENV(this_player()))->desc_west());
        return 1;
    }
    if (str == "south")
    {
        write(ENV(ENV(this_player()))->desc_south());
        return 1;
    }
    if (str == "north")
    {
        write(ENV(ENV(this_player()))->desc_north());
        return 1;
    }
    return 0;

}

string
return_long_env()
{
    object ob = environment(environment(TP));
    return ob->long();
}

string
return_short_env()
{
    object ob = environment(environment(TP));
    return ob->short() + "\n";
}

int
do_row(string str)
{
    int i;
    string desc;

    if (!str || !strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    switch(str)
    {
        case "n":
            str = "north";
            break;
        case "s":
            str = "south";
            break;
        case "w":
            str = "west";
            break;
        case "e":
            str = "east";
            break;
        case "nw":
            str = "northwest";
            break;
        case "ne":
            str = "northeast";
            break;
        case "sw":
            str = "southwest";
            break;
        case "se":
            str = "southeast";
            break;
    }

    i = member_array(str, environment(TO)->query_exit_cmds());
    if (i < 0)
    {
        notify_fail("Row where?\n");
        return 0;
    }
    if (str == "boathouse")
    {
        write("You row the boat back into the boathouse.\n");
        say(QCTNAME(TP) + " rows the boat into the boathouse.\n");
        move_the_boat(str);
        if (TP->query_option(2))
            desc = return_short_env();
        else
            desc = return_long_env();
        write(desc);
        say(desc);
        return 1;
    }
    else
    {
        write("You row the "+ short() +" to the "+ str +".\n");
        say(QCTNAME(TP) + " rows the boat to the " +str+".\n");
        if (str == "lake")
            tell_room("The boathouse disappears in the reed " +
                "behind you.\n");
        move_the_boat(str);
        if (TP->query_option(2))
            desc = return_short_env();
        else
            desc = return_long_env();
            write(desc);
            say(desc);
        return 1;
    }



}

string
query_action()
{
    if (ENV(TP)->id("boat"))
        return "rowing on";
    return "swiming in";
}

int
move_the_boat(string str)
{
    mixed exits = environment(TO)->query_exit();
    int index = member_array(str, exits);
    mixed room = environment(TO)->check_call(exits[index - 1]);
    mixed arg3 = environment(TO)->check_call(exits[index + 1]);
    mixed e = filter(ENV(ENV(TP))->query_exit(), &wildmatch("*reed|*"));
    dump_array(({ exits, index, room, arg3, e }));
    if (arg3) // If arg3 = 1 we are trying to move into reed.
    // exec e=filter(ENV(ENV(TP))->query_exit(), &wildmatch("*reed|*"));

    {
        ENV(TO)->reed(str);
        return 0;
    }
    move(room, 1);
}

int
do_enter(string str)
{
    if (!str || !strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if(TO == environment(TP))
    {
        notify_fail("You are already inside the "+query_short()+".\n");
        return 0;
    }

    if (TP->weight() > 100000)
    {
        notify_fail("You are too heavy for the "+query_short()+".\n");
        return 0;
    }

    if (((TO->weight() - TO->query_prop(CONT_I_MAX_WEIGHT))
        + TP->weight()) > 200000)
    {
        notify_fail("That would sink the loaded "+query_short()+".\n");
        return 0;
    }

    write("You lean down and take a step down into the "+query_short()+".\n");
    say(QCTNAME(TP) + " bends down and steps into the "+query_short()+".\n");
    TP->move(TO, 1);
    return 1;
}

int
do_leave(string str)
{
    if(TO != ENV(TP))
    {
    notify_fail(CAP(QVB)+" what?\n");
    return 0;
    }

    if (ENV(TO)->query_prop(LAKE))
    {
        write("Before jumping you stick a hand into " +
            "the water to check the temperature. Its freezing " +
            "cold and you realise you wouldnt survive long. So " +
            "you decide leaving the "+query_short()+" wasnt " +
            "such a good idea after all.\n");
        return 1;
    }
    else
        say(QCNAME(TP) + " climbs out of the "+query_short()+".\n");
        write("You climb out of the "+query_short()+".\n");
        TP->move_living("M", ENV(TO));
        return 1;
}


int query_prop(string prop)
{
    if (prop == OBJ_I_LIGHT)
        return check_light();
    else
        return ::query_prop(prop);
}


int
check_light()
{
    int light;

    light = environment(TO)->query_prop(ROOM_I_LIGHT);
    return light;
}

string
desc_rock()
{
    if (ENV(TO)->query_prop(ROCK))
        return "You cant see much of the rock from " +
            "this distance. But its quite obvious " +
            "thats its a very big and tall rock.\n";
    else
        return "What?\n";
}

string
desc_tower()
{
    if (ENV(TO)->query_prop(TOWER))
        return "You stretch up and look up at the " +
            "mansion tower. The source reflects in its " +
            "windows and it looks very beautiful from " +
            "down here. You cant see any other part " +
            "of the mansion from this location.\n";
    else
        return "What?\n";
}

string
desc_mill()
{
    if (ENV(TO)->query_prop(MILL))
        return "You stand up in the rickety boat to get a " +
            "better look. A bit behind the hill ridge you " +
            "can see a bit of the roof and two of the vanes " +
            "of the mill. The vanes stand in a ten to two " +
            "position but thats about it.\nYou sit down " +
            "again before the boat should capsize of you " +
            "loosing your balance.\n";
    else
        return "What?\n";
}

string
desc_house()
{
    if (ENV(TO)->query_prop(HOUSE))
        return "The house looks abandoned from what you can " +
            "see from here. Broken windows, a broken " +
            "door hanging on only one hinge and a garden " +
            "that no one have touched for many years. The " +
            "building stands in a small grove of birches " +
            "making it hard to see from another angel than " +
            "this one.\n";
    else
        return "What?\n";
}

string
desc_reed()
{
    if (ENV(TO)->query_prop(LAKE))
        return "The reed is growing thick around the lake. " +
          "Its impossible to pass through it.\n";
    else
        return "There is no reed here.\n";
}
