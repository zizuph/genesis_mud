
#ifndef TOWER_OF_REALMS_DEFS
#define TOWER_OF_REALMS_DEFS

/* The maximum number of info offices on each floor may be changed  
   since there was an idea to possible have a non-homogeneous structure. */ 
#define MAX_OFFICES ({ 0, 5, 5, 5, 5 })  
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
            "From each floor it will be possible to access " + \
            "the information office of one or more domains. ")

#define FLOOR_STAIRDESC \
           "Broad stairs lead up to the next floor of the tower. "

#define ADD_FLOOR_ITEMS add_item(({"floor", "marble", "walls", "stairs"}), \
        "Everything here seems to by made of finely polished marble.\n"); 

#endif

