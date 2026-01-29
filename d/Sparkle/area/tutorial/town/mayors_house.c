/*
 *  /d/Sparkle/area/tutorial/town/mayors_house.c
 *
 *  This is the Mayor's House in Greenhollow. He is the one who
 *  tells the player all about Baron von Krolock, and gets them
 *  started questing. This room teaches about quests.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated August 2015, by Bart Freeman (Tedare)
 *  Added newbie area quest orb with hints.
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    29  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("inside the Mayor's House in Greenhollow");
    set_long("You stand inside a well-furnished home. The walls"
      + " here display many portraits of family members as well"
      + " as a very large map of Silverdell. A desk sits in one"
      + " corner of the room, beside a window. A doorway leads"
      + " east out onto the street.\n\n");

    add_item( ({ "here", "area", "house", "home", "room" }), long);
    add_item( ({ "wall", "walls" }),
        "The walls are hung with portraits and a large map. They are"
      + " finely painted and interrupted only by a large window and"
      + " a door which leads out onto the street.\n");
    add_item( ({ "portraits", "portrait", "painting", "paintings" }),
        "The portraits on the wall display faces which look very much"
      + " like that of the Mayor. They must be relations.\n");
    add_item( ({ "face", "faces" }),
        "Big noses, small ears, and puffy cheeks. Most definitely"
      + " relations of the Mayor.\n");
    add_item( ({ "map", "large map", "very large map",
                 "map of silverdell", "silverdell map" }),
        "The map on the wall shows the town of Greenhollow in the"
      + " south, farmland to the north, the Sterling Woods to the"
      + " east, and mountains to the west. A large black castle is"
      + " depicted in the mountains.\n");
    add_item( ({ "castle", "black castle", "large castle",
                 "large black castle" }),
        "Perhaps this castle has some significance to the townsfolk"
      + " of Greenhollow. It appears larger than any other symbol on"
      + " the map. Beneath it the words 'Baron von Krolock' are"
      + " written.\n");
    add_item( ({ "desk", "corner", "large desk" }),
        "The desk in the corner is very tidily kept. It seems that"
      + " the Mayor takes his job very seriously.\n");

    add_indoor_items();
    add_door_items();
    add_window_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("street_5", "east");

} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Sure, here's a hint. You might want to ask the mayor"
      + " about any tasks he may have for adventurers like yourself.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object    npc;
	object    sign;
	object 	  quest_orb;
	
	if (!present("_tutorial_mayor"))
	{
		add_npc(NPC_DIR + "mayor", 1);
	}
	
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(OBJ_DIR + "quest_orb");
        quest_orb->move(this_object(), 1);
    }
} /* reset_room */


