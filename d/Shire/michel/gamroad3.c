inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 ER_DIR + "er8","north",0,1
#define EXIT2 MICH_DIR + "gamroad2","south",0,1
#define EXIT3 MICH_DIR + "mathom/mathom_entrance","west",0,1
#define EXIT4 MICH_DIR + "residence","east",0,1


int do_enter(string str);

void
create_room()
{
     int i;
     string *herbs;

   add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 3;
   areadesc = "street";
 
   extraline = "The chalky white street leads through the town of Michel "+
   "Delving.  Just south of the Great East Road, you stand before the "+
   "Mayor's house to the east and a very strange burrow to the west.  "+
   "Hobbit burrows are dug into the White Downs which are immediately "+
   "west of here.  South the road continues towards Hardbottle.";

   add_item(({"residence","mayor's residence","mayor's house"}),
   "The Mayor's house is a large one, as hobbit houses go.  It has a "+
   "front porch, lined with benches as presumably the Mayor gets "+
   "a lot of visitors.  Or maybe he likes to take a lot of naps?\n");

   add_item(({"building","strange burrow"}),
   "The strange burrow is dug out of the White Downs, and seems to be "+
   "a repository for things.\n");

   add_item(({"sign"}),
   "The sign to the west reads: Mathom House.\n");

   add_cmd_item("sign","read","The sign to the west reads: Mathom House.\n");

   add_item(({"homes","home","houses","guard houses"}),
  "On the west side of the road, the homes of hobbits are burrows, built into "+
  "the White Downs.  On the east side of the road, where there are no "+
  "downs to burrow from, the Mayor's residence stands.\n");

   add_item(({"chalk","downs","white downs","street"}),
   "The street is made of the hard-packed chalk that is naturally found "+
   "in the White Downs, and excavated when hobbits want to build "+
   "or expand their burrows.\n");

   add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
   "The burrows are cut into the western hillside, all except one "+
   "guarded by a big round door.  The nearest burrow's door is open, "+
   "you could probably enter the burrow.\n");

   add_item(({"door","big round door","round door"}),
   "All of the holes in this area seem to be closed off by large "+
   "round doors, designed in the hobbit fashion.  One reason they "+
   "might be so big is for the hobbits to get their bellies through "+
   "the door.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   add_exit(EXIT4);

   herbs = ({HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))],
       HERBS[random(sizeof(HERBS))]});
   
   for(i = 0; i < sizeof(herbs); i++)
   add_herb_file(herbs[i]);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_prop(OBJ_I_SEARCH_TIME,8);
   
   set_search_places(({"bushes","bush","tree","trees","ground","grass"}));
   
   make_the_room();
}

reset_room()
{
 set_searched(0);
}

void
init()
{
   ::init();
   add_action("do_enter","enter");
}

int
do_enter(string str)
{

   if (!str)
     return 0;
 
   if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
   {
     write("You enter the open burrow.\n");
     say(QCTNAME(TP)+ " leaves into the open burrow.\n");
     TP->move_living("M",MICH_DIR + "burrow/3",1);
     say(QCTNAME(TP)+" arrives.\n");
     return 1;
    }

   write("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}

