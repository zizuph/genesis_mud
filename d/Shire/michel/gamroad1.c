inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 MICH_DIR + "hdbtlroad","south","@@not_open@@"
#define EXIT2 MICH_DIR + "gamroad2","north",0,1
#define EXIT3 MICH_DIR + "fairroad1","east",0,1

int
not_open()
{
   write("The road south to Hardbottle is not yet repaired.\n");
   write("Come back again another day!\n");
    return 1;
}


int do_enter(string str);

void
create_room()
{
     int i;
     string *herbs;
   
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 3;
   areadesc = "street";
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   extraline = "This street is made of the chalk of the White Downs "+
   "that rise up immediately to the west.  The chalk is an excellent building "+
   "material, hobbits have found; they make their homes and roads and many "+
   "other things from it.  East is the Fair Field, where every seventh summer "+
   "is held the Midsummer's Fair and a new Mayor is elected for the whole Shire. "+
   " North, the Mayor's home is visible as are the guard houses around it.  A sign "+
   "extends off a burrow in that direction.";

   add_item(({"sign"}),
   "The sign is too faint to read from this distance.  Go north.\n");

   add_item(({"homes","home","houses","guard houses"}),
  "On the west side of the road, the homes of hobbits are burrows, built into "+
  "the White Downs.  On the east side of the road, where there are no "+
  "downs to burrow from, houses have been erected, especially on the path "+
  "leading to the Fair's Field.\n");

   add_item(({"fair field","field","fair"}),
   "The beautifully pastoral Fair Field is to the east, a large flat grassy "+
   "field, surrounded by trees for shade.\n");

   add_item("trees","The trees are mostly tall willows, growing up from "+
   "some nearby water source, you imagine but do not see.\n");

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
     TP->move_living("M",MICH_DIR + "burrow/1",1);
     say(QCTNAME(TP)+" arrives.\n");
     return 1;
    }

   write("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}

