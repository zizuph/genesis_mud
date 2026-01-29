inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/hobbit/hobbit.h"

#define EXIT1 ER_DIR + "er8","south",0,1
#define EXIT2 MICH_DIR + "gamroad5","north",0,1
#define EXIT3 MICH_DIR + "inn","southwest",0,1
#define EXIT4 MICH_DIR + "newphouse","east",0,1
#define EXIT5 MICH_DIR + "guardr2","southeast",0,1
#define EXIT6 HOBGLD_DIR + "entrance","west",0,1


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
 
   extraline = "Just north of the Great East Road, this chalky white "+
   "street leads north towards Gamwich and south towards Hardbottle. "+
   "East and southeast are free-standing houses, while west and southwest "+
   "lead to burrows dug into the White Downs.  "+  
   "The smaller of the two burrows has a red sign hanging "+
   "from it and the larger one has a white sign.  A burrow slightly north of "+
   "the larger burrow seems enterable.";

   add_item(({"sign","signs","red sign","white sign"}),"The signs are readable "+
   "individually.\n");

   add_cmd_item("red sign","read","The red sign reads: Adventuresome Hobbits.\n");

   add_cmd_item("white sign","read","The white sign reads: Pipe and Fork.\n");

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
   "round doors, designed in the hobbit fashion.  One reason they "+
   "might be so big is for the hobbits to get their bellies through "+
   "the door.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   add_exit(EXIT4);
   add_exit(EXIT5);
   add_exit(EXIT6);

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
     TP->move_living("M",MICH_DIR + "burrow/4",1);
     say(QCTNAME(TP)+ " arrives.\n");
     return 1;
    }

   write("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}

