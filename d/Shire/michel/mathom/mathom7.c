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
   set_short("Inside the Mathom house of Michel Delving");
   set_long("This is the end of the long hallway in the "+
   "Mathom house under the White Downs of Michel Delving. "+
   "The hallway branches here, east and west, and it is possible to "+
   "return back south, over and around the heap of trinkets and mathoms "+
   "that fill this room.\n");

   add_item(({"hallway","long hallway"}),"This hallway leads back "+
   "to the entrance hall.\n");

   add_item(({"heap","trinkets","mathoms"}),
   "Not inclined to waste space, the hobbits have piled "+
   "this room with mathoms, just like all the others.\n");

   add_exit(MATHOM_DIR + "mathom5","south",0,2);
   add_exit(MATHOM_DIR + "mathom8","east",0,2);
   add_exit(MATHOM_DIR + "mathom9","west",0,2);

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

