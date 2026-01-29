inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"


#define EXIT1 MICH_DIR + "gamroad4","south",0,1
#define EXIT2 MICH_DIR + "gamroad6","north","@@block_exit@@"
#define EXIT3 MICH_DIR + "farmrd1","northeast",0,1
#define EXIT4 MICH_DIR + "butchery","east","@@block_butcher@@"

int
block_exit()
{
   write("The road to Gamwich is still under construction.\n");
   return 1;
}
int
block_butcher()
{
    write("The butcher's shop is not yet ready for business.\n");
    return 1;
}


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
 
   extraline = "Here the town of Michel Delving ends, parting into a "+
   "dirt path leading northeast and the main road continuing north, towards "+
   "Gamwich and Tighfield. " +
//   "A tall thin building lies to the east; a yellow sign affixed to the front door. " +
   "There is a burrow here, dug out of the White "+
   "Downs. The main parts of Michel Delving, and the road to Hardbottle are "+
   "south.";

   add_item(({"building","tall building","tall thin building","front door"}),
   "This building is tall and thin, the framework for a large chimney.  A "+
   "smell of roasting meat comes from within. A yellow sign is affixed "+
   "to the front door and is readable.\n");

   add_item(({"path","northeast path","dirt path"}),
   "The dirt path leads northeast, out of Michel Delving through some fields.\n");

   add_item(({"sign","signs","yellow sign"}),"The sign is readable.\n");

   add_cmd_item(({"yellow sign", "sign"}),"read","The sign reads: Anselm, Butcher.\n");

   add_item(({"homes","home","houses","guard houses"}),
  "On the west side of the road, the homes of hobbits are burrows, built into "+
  "the White Downs.  On the east side of the road, where there are no "+
  "downs to burrow from, two buildings that look like lodges stand.\n");

   add_item(({"chalk","downs","white downs","street"}),
   "The street is made of the hard-packed chalk that is naturally found "+
   "in the White Downs, and excavated when hobbits want to build "+
   "or expand their burrows.\n");

   add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
   "The burrows are cut into the western hillside, all except one "+
   "guarded by a big round door.  The northern burrow's door is open, "+
   "you could probably enter the burrow.\n");

   add_item(({"door","big round door","round door"}),
   "All of the holes in this area seem to be closed off by large "+
   "round doors, designed in the hobbit fashion. One reason they "+
   "might be so big is for the hobbits to get their bellies through "+
   "the door.\n");

   add_exit(EXIT1);
//   add_exit(EXIT2);
   add_exit(EXIT3);
//   add_exit(EXIT4);

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
 
   if ((str == "burrow") || (str == "smial") || (str == "northern burrow"))
   {
     write("You enter the open burrow.\n");
     say(QCTNAME(TP)+ " leaves into the open burrow.\n");
     TP->move_living("M",MICH_DIR + "burrow/5",1);
     say(QCTNAME(TP)+ " arrives.\n");
     return 1;
    }

   write("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}

