/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * cave1.c (at the beach)
 *
 */

inherit "/std/room";

#include "/d/Terel/include/Terel.h"

#define FAT_LIM 15
#define NO_DIGS 5
#define OUT     (PORT_DIR + "beach/b12")

static int no_digs=0;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("In a cave");
    set_long("You are standing in a small cave. It looks to be bigger " +
             "to the east.\n");
    
    add_item(({"exit", "hole", "out"}), "@@my_out@@");
    add_exit(OUT, "out", "@@test_out|"+OUT+"@@");
    add_exit(PORT_DIR + "beach/cave2", "east", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

public void
init()
{
    ::init();
    add_action("do_dig", "dig");
}

public string
do_search(object searcher, string str)
{
    return "";
}

public string
my_out()
{
    if (OUT->check_entrance(file_name(TO))) {
        return "The exit out is free from sand.\n";
    } else {
        return "The exit out is filled with sand.\n";
    }
}

public int
test_out(string file)
{
    if (file->check_entrance(file_name(TO))) return 0;
    
    write("There is too much sand in the way.\n");
    return 1;
}

public int
do_dig(string str)
{
    object shovel;
    string s1, s2;
    
    notify_fail("Dig where with what?\n");
    if (!str) return 0;
    if (sscanf(str, "%s with %s", s1, s2) != 2) return 0;
    
    if (s2 == "hands" || s2 == "bare hands" || s2 == "hand") {
        shovel = 0;
    } else if (s2 == "shovel") {
        shovel = present("shovel", TP);
        if (!shovel) return 0;
    } else {
        return 0;
    }
    
    if (s1 == "exit" || s1 == "hole" || s1 == "out" || s1 == "sand") {
        s1 = "out";
    } else if (s1 == "here" || s1 == "ground") {
        write("You cannot dig here, it's stone.\n");
        say(QCTNAME(TP) + " tries to dig in the stone.\n");
        TP->add_fatigue(-FAT_LIM);
        return 1;
    } else {
        return 0;
    }
    
    if (OUT->check_entrance(file_name(TO))) {
        write("You don't have to dig up the exit, it's open.\n");
        no_digs = 0;
        return 1;
    }
    
    if (TP->query_fatigue() < FAT_LIM) {
        write("You are too tired to dig right now.\n");
        say(QCTNAME(TP) + " tries to dig, but is too tired.\n");
        return 1;
    }
    
    if (shovel) {
       TP->add_fatigue(-FAT_LIM/5);
       write("You dig to clear the exit from sand using the " +
             shovel->short() + ".\n");
       say(QCTNAME(TP) + " digs with the " + shovel->short() +
           " to clear up the cave exit from sand.\n");
    } else {
       TP->add_fatigue(-FAT_LIM);
       write("You dig to clear the exit from sand using your bare hands.\n");
       say(QCTNAME(TP) + " digs with " + TP->query_possessive() +
           " bare hands to clear up the cave exit from sand.\n");
    }
    
    no_digs++;
    if (no_digs >= NO_DIGS) {
        OUT->open_entrance(file_name(TO));
        write("You see some light through the hole!\n");
        no_digs = 0;
    }
    return 1;
}
