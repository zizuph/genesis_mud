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
   set_long("This expansive burrow dug into the chalky White Downs "+
                  "is wide and tall beyond any hobbit burrowing imaginable. "+
                  "The room is literally filled from top to bottom with all "+
                  "sorts of trinkets and mathoms given to hobbits over the "+
                  "years.  To the east, north and south, narrow paths have "+
                  "been created by a low fence to keep the heap from "+
                  "flooding the room entirely.\n");

   add_item(({"burrow","burrowing","room","walls","wall"}),
   "This burrow's walls are white with the chalk of the White Downs "+
   "that they are tunnelled from.\n");

   add_item(({"white downs","chalk","chalky"}),
   "The chalk on the walls seems to remain there for the most "+
   "part.\n");

   add_item(({"trinket","trinkets","heap","mathoms","mathom"}),
   "These trinkets are literally swallowing the room!\n");

   add_item(({"paths","path","low fence","fence"}),
   "The low fences are made of wood and painted white, "+
   "just like picket fences you see around the town of Michel Delving. "+
   "The fences are bulging under the weight of all the unwanted "+
   "mathoms, however.\n");

   add_exit(MATHOM_DIR + "mathom_entrance","south",0,2);
   add_exit(MATHOM_DIR + "mathom2","east",0,2);
   add_exit(MATHOM_DIR + "mathom3","north",0,2);

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

