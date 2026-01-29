/* 2017-10-27 Malus: Added some player-suggested descriptions */ 
#include <stdproperties.h>
#include "/d/Genesis/start/human/town/tower.h"
#include "/d/Emerald/defs.h"

inherit TOWER_OFFICE;

create_tower_office()
{
    set_short("Emerald's Office");
    set_long("Stepping into this room you feel as if you've entered a "+
      "wonderous, adventure-filled place. The sounds of the crashing "+
      "ocean deafens your ears. Shading your eyes from the brilliant sun "+
      "you can see vast forests to the north and west of you. "+
      "Even further to the north and east, you think you can make "+
      "out the very top of a mountain. A cold breeze rising from "+
      "the east sends a chill down your spine. You really want to "+
      "reach out and explore further.\n\n");

    add_item("ocean", "The ocean stretches out southeast of you; " +
            "vast, wild and terrifying, yet somehow very tempting.\n");
    add_item("sun", "You get blinded and quickly shade your eyes again. " +
           "After blinking a few times your vision is back to normal.\n");
    add_item("forests", "A sea of emerald green.\n");
    add_item("mountain", "You cannot say for sure, but it does look " +
           "like the top of great mountain, far, far away.\n");
    add_cmd_item("out", "reach", "You reach out. " +
            "Somehow it didn't feel as great as you expected.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_tower_link("tower");
    add_office_sign();

    set_project_path("/d/Emerald/open/projects/");
    disable_rank_display();
    disable_logged_in_display();

    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");
    reset_room();  
}


/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */

public void
reset_room()
{
    object quest_orb;
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Emerald");
        quest_orb->set_extra_line("The dark crystal orb is floating"
          + " before you, seemingly on the wind.");
        quest_orb->move(this_object(), 1);
    }    
}
