// file name:        /d/Avenir/common/holm/jungle/lf15.c
// creator(s):       Lilith, Nov 96
// revisions:        Lilith, Jun 97
// purpose:
// note:
// bug(s):
// to-do

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include <ss_types.h>
#include <tasks.h>

int i_pl;
void set_full(int i) {    i_pl = i;    }

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}


/* Now create the room.  */
void
create_jungle_room()
{
    set_short("entrance to a hollow");
    set_long("You stand near the cathedral pillar of a rotting "+
        "stump that marks the high point of this hollow. "+
        "Water condenses and runs down the sides of the cliff "+
        "wall rising in the east and collects at its base, "+
        "forming a narrow stream that grows wider in the "+
        "north. An ancient deer path runs along the stream "+
        "edge.\n");

    add_exit("lf13", "north", 0);
    add_exit("lf16", "east", 0);
    add_exit("lf18", "southwest", 0);

    add_item(({"stump", "pillar", "trunk"}), 
        "This is the rotting remains of a once-great tree. It "+
        "juts up into the air like a cathedral pillar, intri"+
        "cately scarred by the efforts of wood-destroying "+
        "insects. It marks the high-point of the hollow to "+
        "the north.\n");

    add_cliff();
    add_moss();
    add_atrack();
    add_stream();
    add_grass();

    reset_domain_room();
}

int
check_climb(string str)
{
    int climb_task;
    string qvb;
 
    qvb = query_verb();

    notify_fail(capitalize(qvb) +" what?\n");    
    if (!str)
        return 0;

    if (!parse_command(str, ({ }), 
        "[up] [into] [the] 'trunk' / 'stump' / 'pillar'"))
        return 0;    

    climb_task = TP->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_CLIMB }));
    if (climb_task > 0)
    {
        if (!i_pl)
        {
            write("You inch your way up the pillar of the rotting "+
                "stump, then lower yourself inside it.\n");
            say("With great care and a show of climbing expertise, "+ 
                QCTNAME(TP) +" inches "+ POSSESS(TP) +" way "+
                "up the stump and then disappears inside.\n");
            i_pl = 1;
            TP->move_living("M", JUNG + "stump", 1);
            return 1;
        }
        else
        {
            write("You inch your way up the pillar of the rotting "+
                "stump, but when you get to the top, you find that "+
                "the interior is occupied by someone else, so you "+
                "climb back down.\n");
            say(QCTNAME(TP) +" works "+ POSSESS(TP) +" way painstak"+
                "ingly up the tree stump, and then after a moment, "+
                "climbs back down.\n");
            return 0;
        }        
    }
    else
    {
        write("You try to climb the rotting trunk, but don't get "+
            "very far, as it is beyond your skills.\n");
        say(QCTNAME(TP) +" tries to climb the rotting stump, but "+
            "fails.\n");
        return 1;
    }    
}

void init()
{
    ::init();

    add_action(check_climb, "climb");
}
