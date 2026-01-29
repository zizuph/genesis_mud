/* /d/Genesis/start/human/town/tower.h
 *
 *
 *
 *
 * IMPORTANT.
 *
 * When adding a new floor make sure to import the code for reaching the attic
 * on top of the dynamic stack. The attic is the Liwitch domain office where
 * Liwitch is hidden away. Palyers need to search for the exit leading there.
 *
 * The CURRENT top dynamic floor is tfloor4.c and thats where
 * /d/Liwitch/common/player_domain_office.c has its entrance code. 
 * I have only hard coded it in for now but if someone feel inclined to write
 * a prettier solution for it, by all means. ;)
 * 
 *
 *
 * Also, when updating the tower map /d/Genesis/open/MAP_FILES/tower_map.txt
 * just edit in a new floor and don't forget to save it and the update the
 * map with <map update /d/Genesis/open/MAP_FILES/tower_map.txt> as explained
 * in <help map>
 *
 *   /Styles. 2020-09-08 (was a Tuesday and Styles was in need of much sleep)
 *
 *
 */

#ifndef TOWER_OF_REALMS_DEFS
#define TOWER_OF_REALMS_DEFS

/* The maximum number of info offices (+1) on each floor (0-4) may be changed
 * since there was an idea to possible have a non-homogeneous structure.
 *
 * Before making changes to MAX_OFFICES and FLOOR_NAMES make sure that you 
 * have added or removed said office from tower.c or that room won't load if 
 * the setting here are incorrect.
 */
//#define MAX_OFFICES ({ 0, 5, 5, 5, 5, 2 })
#define MAX_OFFICES ({ 0, 5, 5, 5, 5 })

/*#define FLOOR_NAMES ({ "tower", "tfloor1", "tfloor2", "tfloor3", 
    "tfloor4", "tfloor5" })*/
#define FLOOR_NAMES ({ "tower", "tfloor1", "tfloor2", "tfloor3", "tfloor4" })

#define TOWER_OFFICE "/d/Genesis/start/human/town/tower_office"
#define TOWER_FLOOR "/d/Genesis/start/human/town/tower_floor"
#define TOWER "/d/Genesis/start/human/town/tower"
#define TOWER_SAVE "/d/Genesis/start/human/town/tower_save"
#define FLOOR_EXITS(floor) TOWER->query_floor_exits(floor)
#define OFFICE_FLOOR(domain_name) TOWER->query_office_floor(domain_name)
#define OFFICE_PATH(domain_name) TOWER->query_office_path(domain_name)
#define PROJ_EXT ".prj"
#define OFFICE_SIGN_TEXT "Commands:\n" + \
      "wizards                  - Lists the wizards of this domain.\n" + \
      "projects <domain/wizard> - The projects of the domain/wizard.\n"

#define FLOOR_MAINDESC \
           ("The floor and walls are made of polished marble, " + \
            "reflecting your image as you look around in wonder. " + \
            "From each floor it is possible to access " + \
            "the information office of one or more domains. ")

#define FLOOR_STAIRDESC \
           "Broad stairs lead up to the next floor of the tower. "

#define ADD_FLOOR_ITEMS add_item( \
		({"floor", "marble", "walls", "stairs"}), \
        "Everything here seems to be made of finely polished marble.\n" \
  	);

#define QUEST_ORB  "/d/Sparkle/area/city/obj/quest_orb"
#endif