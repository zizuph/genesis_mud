/**********************************************************************
 * - office.c                                                       - *
 * - This is an updated domain office for Khalakhor.                - *
 * - It is based upon  /d/Genesis/room/info_office.c, which was     - *
 * - orginally created by Maniac 7/1/97.                            - *
 * - The orginal domain_office created by Teth is saved as          - *
 * - domain_office.bak. The long description is used within this    - *
 * - room, slightly reworded and broken in different sections       - *
 * - within different events.                                       - *
 * - Created by Damaris@Genesis 01/2006                             - *
 * - Cleaned up the indentation to Emacs Pike mode, Tapakah 04/2021 - *
 **********************************************************************/
#pragma strict_types

#include "/d/Genesis/start/human/town/tower.h"


#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit TOWER_OFFICE;
#include "laying.c"
#include "/d/Khalakhor/pit.c"
int alarmid;
int eventnumber = 0;
int events_is_on = 0;

string *events = (({"The fire flickers brightly\n\n"+
                    "Images shoot forth from the fire...\n\n"+
                    "The fluid images suddenly become clear as mist born "+
                    "of spilled blood veils the highland, obscuring vision "+
                    "and dampening sound. The keening wail of bagpipes seems "+
                    "to echo even through the flames, playing a hymn of "+
                    "mourning. Corpses of humans, goblins and dwarves, "+
                    "all wearing tartan, mar the patches of blooming "+
                    "thistle and heather... suddenly the images shift into "+
                    "blurry motion once again with the flames...\n\n",
                    "Images shoot forth from the fire...\n\n"+
                    "The almost fluid images become suddenly clear as a mist "+
                    "rises upward and through the fog several people are "+
                    "blessing and burying the dead some distance away. A "+
                    "piece of tattered sheepskin hangs from an upright "+
                    "claymore. A large important banner hangs suspended "+
                    "from the remains of a broken pike embedded in the "+
                    "ground, waving slowly in wind... suddenly the images "+
                    "shift into blurry motion once again with the flames...\n\n",
                    "Images shoot forth from the fire...\n\n"+
                    "The almost fluid images become suddenly clear to a "+
                    "darkened forest rising in the distance and there is "+
                    "unimaginable movement within the trees. There are elves, "+
                    "which seem to be swallowed up within the devastation of "+
                    "a giant goblin horde from the north... suddenly the images "+
                    "shift into blurry motion once again with the flames...\n\n",
                    "Images shoot forth from the fire...\n\n"+
                    "The almost fluid images become suddenly clear as a large "+
                    "tower glowing rises majestically upward on an isle... "+
                    "suddenly the images shift into blurry motion once again "+
                    "with the flames...\n\n",
                    "Images shoot forth from the fire...\n\n"+
                    "The almost fluid images become suddenly clear as if from "+
                    "far up in the air gliding over the waters an amazing land "+
                    "mass appears resembling a three-spoke pinwheel, spinning "+
                    "clockwise. A chain of islands encircles the perimeter. "+
                    "The northern spoke consists of wastelands, which seems "+
                    "to be cast into eternal darkness. Great forests dominate "+
                    "the southwestern areas while the southeast has a varied "+
                    "landscape ranging from highlands, small forests, plains "+
                    "and even rocky moors... suddenly the images shift into "+
                    "blurry motion once again with the flames...\n\n"}));

void
create_tower_office ()
{
	set_short("a grassy knoll");
	set_long("   A vast amount of vibrant green grass saturates "+
           "this knoll in beauty and splendor. The edge of the "+
           "circumference there is a small sign among breathtaking "+
           "flowers of all different shapes, sizes and colours. From "+
           "the top of this knoll the vision of Khalakhor can be seen "+
           "with the splendor of ages being passed down from one tale "+
           "to another all spanned out before ones eyes. The center of "+
           "this knoll has a fire pit that has been dug with precision. "+
           "Every now and again this pit burns with flames that fuel the "+
           "imaginations of wizards making this a truly mystical and "+
           "magical place.");
	
	add_item(({"area", "grassy knoll", "room", "knoll"}), query_long);
	add_item(({"pit", "fire pit", "flames", "buring flames", "fire"}),
           "The center of this knoll has a fire pit that has been dug "+
           "with precision. Every now and again this pit burns with "+
           "flames that fuel the imaginations of wizards making this a "+
           "truly mystical and magical place.\n");
	add_item(({"image", "images"}),
           "The fire dances with images fluidly move giving only a "+
           "glimpse of clarity now and again before they blur in motion "+
           "with the flames.\n");
	add_item("sign", OFFICE_SIGN_TEXT);
	add_item(({"circle"}),
           "There is a circle of mats that suround the fire pit.\n");
	add_item(({"ground", "mat", "mats", "grass",
             "soft grass", "blanket","green grass"}), lay_desc);
  add_item(({"flower", "flowers"}),
           "Breathtakingly beautiful flowers of all shapes and colours.\n");
  add_item(({"khalakhor"}),
           "You see a large continent consisting of three peninsulas, "+
           "southeastern, southwestern and northern ones joined in "+
           "some kind of a nexus. Some islands of peculiar shapes are "+
           "scattered around, a couple of them emitting a different "+
           "aura than the others. You notice a lot of ship traffic "+
           "between various regions of the continent and the islands.\n");
	add_my_desc(lay_desc, this_object());
	add_cmd_item("sign", "read", OFFICE_SIGN_TEXT);
	add_item(({"graph", "player graph"}), "@@graph@@");
	disable_logged_in_display();
	set_project_dir("/d/Khalakhor/open/project/");
	add_tower_link("tower");
  clone_object("/d/Khalakhor/open/project/journal")->move(TO);
  add_prop(ROOM_S_MAP_FILE, "domain_office.txt");

  reset_room();
}
/*
 * start_events()
 * Starts the alarm that echoes text-events to the players in this room.
 *
 */
void
start_events ()
{
	alarmid = set_alarm(30.0,60.0,"do_event");
	events_is_on = 1;
	return;
}

/*
 * do_event()
 * Echoes the next text in a list of texts to all players in the room.
 * Will turn off the alarm calling this function if no players are
 * present here.
 *
 */
void
do_event ()
{
	object *all_players_here;
	string str;
	
	all_players_here = FILTER_LIVE(all_inventory(TO));
	if (!sizeof(all_players_here)) {
    remove_alarm(alarmid); /* remove the repeating alarm! */
    events_is_on = 0;
    return;
  }
	eventnumber = eventnumber + 1;
	if (sizeof(events) < (eventnumber + 1)) eventnumber = 0;
	str = events[eventnumber];
	tell_room(TO, str);
	return;
}

/*
 * init()
 * Is called when an object enters this room.
 * Is used here to start events if the events are not already on.
 *
 */
void
init()
{
	object *all_in_room;
	::init();
	init_lay();
	init_fire();
	all_in_room = FILTER_LIVE(all_inventory(TO));
	if (sizeof(all_in_room) && events_is_on == 0)
    start_events();
	return;
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
    
  if (!present("_genesis_quest_orb")) {
    quest_orb = clone_object(QUEST_ORB);
    quest_orb->set_orb_domain("Khalakhor");
    quest_orb->set_extra_line("The dark crystal orb is floating"
                              + " before you, seemingly on the wind.");
    quest_orb->move(this_object(), 1);
  }    
}
