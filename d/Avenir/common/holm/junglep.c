// file name:        /d/Avenir/common/holm/junglep
// creator(s):       Lilith, Jan 1997
// revision history: Lilith, 12 Jun 1997
// purpose:          for placing objects on the holm/jungle
// note:             
// bug(s):           
// to-do:

#include <macros.h>

#include "holm.h"
#include "/d/Avenir/smis/smis.h"
#include "/d/Avenir/include/relation.h"

#define WDDD	(JUNG + "whirlpool_die_die_die")

inherit SMIS_MODULE_PLACER;

void create_placer()
{

    set_module_id("junglep");
    set_module_description("Placer for the holm jungle");

    set_location_npc(JUNG  + "lf1",     HOLM_MON + "phrynos");
    set_location_npc(JUNG  + "lf4",     HOLM_MON + "monkey");
    set_location_npc(JUNG  + "lf8",     HOLM_MON + "deer");
    set_location_npc(JUNG  + "lf9",     HOLM_MON + "deer");
    set_location_npc(JUNG  + "lf10",    HOLM_MON + "snake");  
    set_location_npc(JUNG  + "lf11",    HOLM_MON + "noble");
    set_location_npc(JUNG  + "lf13",    HOLM_MON + "newt");
    set_location_npc(JUNG  + "lf18",    HOLM_MON + "merchant");
    set_location_npc(JUNG  + "lf20",    HOLM_MON + "monkey");
    set_location_npcs(JUNG + "lf7",  ({ HOLM_MON + "hunted_l",
                                        HOLM_MON + "hunted",  
                                        HOLM_MON + "hunted" }));
    set_location_npcs(JUNG + "lf15", ({ HOLM_MON + "termite", 
                                        HOLM_MON + "noble" }));
    set_location_npcs(JUNG + "lf16",  ({ HOLM_MON + "adept", 
                                        HOLM_MON + "noble" }));
    set_location_npcs(JUNG + "stump",({ HOLM_MON + "newt",
                                        HOLM_MON + "termite",  
                                        HOLM_MON + "termite" }));

    set_location_npc(JUNG  + "lf22",    HOLM_MON + "noble");
    set_location_npcs(JUNG  + "lf19",({ HOLM_MON + "hunted_l",
                                        HOLM_MON + "hunted",  
                                        HOLM_MON + "hunted" }));
    set_location_object(JUNG + "lf6",   HOLM_MON + "snake_master"); 


    /* High Forested Spire */
    set_location_npc(JUNG  + "hf5",     HOLM_MON + "panther");
    set_location_npc(JUNG  + "hf9",     HOLM_MON + "deer");
    set_location_npcs(JUNG + "hf6",  ({ HOLM_MON + "hunted_l",
                                        HOLM_MON + "hunted",  
                                        HOLM_MON + "hunted" }));
    set_location_npcs(JUNG  + "hf1", ({ HOLM_MON + "noble",
                                        HOLM_MON + "priest"}));   

    set_location_object(JUNG + "lf18",  HOLM_OBJ + "caltrop");

    set_location_commands(JUNG + "lf7", 
        ({"drink", MASTER, "do_drink", "sip", MASTER, "do_drink",
          "enter", MASTER, "do_dive", "dive", MASTER, "do_dive",
          "jump", MASTER, "do_dive"}));
    set_location_commands(JUNG + "lf10", 
        ({"drink", MASTER, "do_drink", "sip", MASTER, "do_drink",
          "enter", MASTER, "do_dive", "dive", MASTER, "do_dive",
          "jump", MASTER, "do_dive"}));
    set_location_commands(JUNG + "lf13", 
        ({"drink", MASTER, "do_drink", "sip", MASTER, "do_drink",
          "enter", MASTER, "do_dive", "dive", MASTER, "do_dive",
          "jump",  MASTER, "do_dive"}));
}

/*
 *  Commands added via set_location_commands
 */

/*
 * Function name: do_dive
 * Description:   Do we dive into the pool?
 * Returns:       0 - no; 1 - yes.
 */
int
do_dive(string str)
{
    object tp = this_player();

    if (!str)
        return 0;

    notify_fail("You can't do that.\n");
    if (!parse_command(str, ({ }),
        "[into] [the] 'water' / 'stream' / 'pool'"))
        return 0;    

    // In they go! Must be a good day to die.
    write("You jump into the stream.\nThe shockingly cold water "+ 
        "makes you gasp as you come into contact with it.\n");
    say(QCTNAME(tp) + " jumps into the water and is swept away!\n");
    tp->move_living("M", WDDD, 1, 0);
    return 1;
}

/*
 * Function name:  do_drink
 * Description:    Do we drink from the water?
 * Returns:        0 - no; 1 - yes.
 */
int
do_drink(string str)
{
    object tp = this_player();

    if (!str)
        return 0;

    notify_fail("You can't do that.\n");
    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'stream' / 'pool'"))
        return 0;    

    write("You kneel at the water's edge and scoop up a handful "+
        "of water, drinking greedily.\n");
    say(QCTNAME(tp) + " drinks from the stream.\n");
    this_player()->drink_soft(500, 0);

    // 1 in 10 chance of falling into the pool and drowning!
    if (random(10))
    {
        write("The water before you takes the shape of a hand.\nFrozen "+
            "with surprise, you watch as the hand becomes an arm that "+
            "extends toward you and sweeps you into the water!\n");        
        say(QCTNAME(tp) +" falls into the water and is swept away!\n");
        tp->move_living("M", WDDD, 1, 0);
        return 1;
    }
} 
