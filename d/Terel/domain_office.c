#include <stdproperties.h>
#include "/d/Genesis/start/human/town/tower.h"

inherit TOWER_OFFICE;


/*
 * Function name:        reset_room
 * Description  :        lets add the quest orb (Gorboth, April 2008)
 */
public void
reset_room()
{
    object  quest_orb;

    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Terel");
        quest_orb->set_extra_line("The orb is hovering in mid air.");
        quest_orb->move(this_object(), 1);
    }    
} /* reset_room */

void
create_tower_office()
{
    set_short("Domain Office of Terel");
    set_long("You have entered the Terel domain office. "+
    "The room is made of white stone, something like marble. Before you "+
    "stands a large, open window overlooking the Dragon Mountains and "+
    "south over all of Terel. The Dragon Mountains spread westward as "+
    "far as the eye can see, a monstrous range of snow covered mountains "+
    "filled with wild animals and home to numerous goblin tribes. Just "+
    "below the mountains spans the Silver Forest, flowing southward "+
    "towards the city of Maskyr Keep on the east coastline, the town of "+
    "Calathin to the west, and farther west to the town of Ribos. Beyond "+
    "that to the south is the Enchanted Forest running south for many "+
    "miles. The small village of Dabaay can be seen far down the eastern "+
    "coastline.\n");

    add_tower_link("tower");
    set_project_path("/d/Terel/open/project/");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");
    reset_room();
}

