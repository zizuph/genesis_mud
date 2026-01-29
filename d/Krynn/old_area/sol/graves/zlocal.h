#define PARENT	"/d/Krynn/solace/"
#define TDIR	PARENT + "graves/"
#define BOOK	TDIR + "book/"
#define LOG	TDIR + "log/"
#define MONSTER	TDIR + "mnstrs/"
#define OBJ	TDIR + "obj/"

#define C_SOLACE	PARENT + "village/solace22"

#define GRAVE_STD	"/d/Krynn/solace/graves/zgrave_std"

#define INSIDE_BASE    "/d/Krynn/solace/std/inside_base"
#define OUTSIDE_BASE   "/d/Krynn/solace/std/outside_base"

#define K_HOLE1 0232773270

#define GRAVE_LOG      "/d/Krynn/common/log/graves/"
#define NUM_OF_GRAVES  20
#define CONTROLLER     TDIR + "controller"

#define ADD_GRAVES     add_item(({"grave", "graves"}), "@@graves");
#define WHAT_GRAVES    add_item(({"grave", "graves"}), "@@wgraves");
#define OLD_GRAVES    add_item(({"old grave", "old graves"}), "@@ograves");
#define NEW_GRAVES    add_item(({"new grave", "new graves"}), "@@graves");
#define ADD_GRAVEYARD  add_item("graveyard", "@@graveyard");
#define LOOK_BUSHES    add_item(({"the bushes", "bushes", "a bush", "bush",\
				  "thick bushes"}), "@@bushes");
#define LOOK_PATH      add_item(({"path", "the path"}), "@@path");
#define LOOK_VALLEN    add_item(({"the vallenwood", "the vallenwood tree",\
			        "vallenwood", "vallenwood tree",\
				"the Vallenwood", "the Vallenwood tree",\
				"Vallenwood"}), "@@vallenwood");
#define READ_GRAVE     add_cmd_item("grave", "read", "@@grave_look");
#define LOOK_EXTRAS    init() { ::init(); ADA("look"); }
