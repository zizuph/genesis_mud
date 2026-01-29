#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define  OTHER_SIDE    (MORGUL_DIR + "city/w_wall")
#define  MAX_PASSAGES_WHEN_LOCKED   3

/*
 * Prototypes
 */
void open_wall();

/*
 * Global Variables
 */
int     opening;
string  passage_text = " A dark passageway has opened amidst the deep"
                     + " shadows which cover the wall of the city here.";
mapping locked_passages = ([ ]);

#include "/d/Gondor/morgul/city/entr_funs.h"  // yes its ugly, sue me.

public void
create_morgul_room()
{
    set_road(9);
    set_short_desc("along the walls in near to the northwestern"
      + " corner of Minas Morgul");
    set_extraline("The walls rise above here, and loom darkly to the"
      + " west and east. Directly north, shadows lie so deeply upon"
      + " the wall that it is difficult to focus on its surface. A"
      + " ways to the south and east lies Angmar Square before the"
      + " feet of the Tower of Dark Sorcery.");

    add_tower();

    add_item(({"shadows","shadow","darkness"}), exa_shadows);
    add_item(({"wall","walls","city wall"}), exa_wall);
    add_item(({"rune","runes","inscription","inscriptions"}), exa_runes);
    add_item(({"opening","openings","passageway","passageways",
               "passage","passages"}), exa_opening);

    add_cmd_item(({"rune","runes","inscription","wall"}), "read",
                 exa_runes);

    add_exit(MORGUL_DIR + "city/square","southeast","@@check_exit",1);
}

int query_main_gate_locked()
{
    object main_road = find_object(MORGUL_DIR + "city/mmr3");
    if (!objectp(main_road)) return 0;
    
    object gate = present("iron gate", main_road);
    if (!objectp(gate)) return 0;
        
    return gate->query_locked();
}

int block_passageway_when_overused()  
{
    int result = block_passageway();
    if (result) return result;
    
    if (!query_main_gate_locked()) return 0;
    
    if (member_array(TP->query_real_name(), m_indexes(locked_passages)) == -1) {
        locked_passages[TP->query_real_name()] = 0;
    }
    
    if (locked_passages[TP->query_real_name()] >= MAX_PASSAGES_WHEN_LOCKED) {
        log_file("morgulmage_secret_entrance", ctime(time()) + " " 
            + capitalize(TP->query_real_name()) + " was blocked from using "
            + "the entrance again while main gate was locked.\n", 0);   

        write("A threatening voice rasps to you: Like a rebel you are, "
            + "sneaking away from my city. Use the gate for what it is "
            + "intended!\nYou back away from the passageway.\n");
        return 1;
    }

    log_file("morgulmage_secret_entrance", ctime(time()) + " " 
        + capitalize(TP->query_real_name()) + " used the passageway "
        + "while main gate was locked.\n", 0);    
    locked_passages[TP->query_real_name()]++;
    return 0;
}

void 
setup_passageway_exit() 
{
    add_exit(OTHER_SIDE, "north", block_passageway_when_overused);
}

void
remove_passageway_exit()
{
    remove_exit("north");
}

void
close_wall()
{
    if (!opening)
        return;

    string message = "With a groan, the opening in the wall begins to slide"
      + " shut, sending a rumble through the ground at your feet. A rush"
      + " of swirling darkness covers the wall, and the opening is"
      + " gone.\n";
      
    tell_room(TO, message);
    tell_room(OTHER_SIDE, message);
    
    remove_passageway_exit();
    OTHER_SIDE->remove_passageway_exit();
    
    opening = 0;

    return;
}

void
open_wall()
{
    if (opening)
        return;

    string message = "With a terrible grinding sound, the darkness which"
      + " covers the city wall trembles and parts to reveal a thin"
      + " opening in the stone.\n";
    tell_room(TO, message);
    tell_room(OTHER_SIDE, message);

    setup_passageway_exit();
    OTHER_SIDE->setup_passageway_exit();
    
    opening = 1;
    set_alarm(10.0, 0.0, "close_wall");
    return;
}

void
init()
{
    ::init();

    add_action("rasp_password","rasp");
}
