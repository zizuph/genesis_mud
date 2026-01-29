inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

#define MIN_AWARE 3
#define MATHOM_DIR "/d/Shire/michel/mathom/"

int searches;
void add_stuff();
void reset_room();


void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   set_short("Inside the mathom house of Michel Delving");
   set_long("This room is relatively empty of mathoms, with only "+
   "a small heap against the west wall, leaving adequate walking room "+
   "to the south, north and east.  A glass case sits mounted high on a "+
   "pedestal.  Strangely enough, there are little piles of ash all around "+
   "the pedestal.\n");

   add_item(({"heap","mathoms","trinkets"}),
                  "The heap only covers the west wall and a bit of the "+
                  "floor all around.  Rather odd.\n");

   add_item(({"pedestal","glass case","case","glass"}),
                  "The glass case seems to be made wholly of glass, "+
                  "and it sits on a pedestal of solid granite.  Inside "+
                  "the case you see a pipe mounted on a stand, with an "+
                  "inscription carved into the stand.\n");

   add_item("inscription","It has writing written on it.\n");
   add_item(({"pipe","stand"}),"This pipe looks very old indeed, "+
   "as evidenced by its great deal of wear and tear.  The bowl "+
   "is blackened by fire and the stem has bitemarks along the "+
   "sides.\n");

   add_item(({"piles","pile","tobacco","ash"}),
   "The piles of ash are where hobbits have come and emptied "+
   "their fully smoked pipes on the floor.  How odd!\n");   

   add_cmd_item("inscription","read","The inscription reads:\n"+
   "This pipe belonged to Tobold Hornblower.\n");
   add_cmd_item(({"tobold's pipe","pipe"}),({"get","take","pick"}),"You cannot take "+
   "Tobold's pipe!\n");

   add_exit(MATHOM_DIR + "mathom5","north",0,2);
   add_exit(MATHOM_DIR + "mathom1","south",0,2);
   add_exit(MATHOM_DIR + "mathom4","east",0,2);

   add_prop("_obj_s_search_fun","do_search");
   add_prop(OBJ_S_SEARCH_FUN,"do_search");
   add_prop(OBJ_I_SEARCH_TIME,8);

   
   add_stuff();

}
void add_stuff()
{
    object mathom;
    if(!present("mathom",TO))
    {
      mathom = clone_object(MATHOM_DIR + "obj/mathom");
      mathom->move(TO);
     }
}

void reset_room()
{
   add_stuff();
   searches = 0;
}


string
do_search(object searcher, string str)
{
   int awareness;
   string  dummy;
   object mathom;

   awareness = searcher->query_skill(SS_AWARENESS);
   if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
   if(!str || (str!= "heap" && str != "trinkets" && str != "mathoms")) return 0;
   if(searches > 6) return 0;
   seteuid(getuid(TO));
   mathom = clone_object(MATHOM_DIR + "obj/mathom");
   mathom->move(searcher);
   say(QCTNAME(searcher)+ " finds something in the heap.\n");
    return "You find a "+mathom->short()+" in the heap.\n";
}

