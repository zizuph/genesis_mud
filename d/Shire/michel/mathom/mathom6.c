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
   set_long("Deep in the Mathom house under the White Downs "+
   "at Michel Delving, this room begins to show its age.  Long "+
   "ago when these halls were first being dug out, hobbits "+
   "put their most worthless junk in this room.  Consequently "+
   "it is barely enterable thanks to a slight semi-circle which "+
   "is not taken up by the heap of mathoms which fills the room "+
   "from top to bottom.  West is the hallway.\n");

   add_item(({"room","halls","junk","semi-circle"}),
   "This room is one of the first carved off the main hallway. "+
   "The junk in here is really old, you suppose, as all the items "+
   "are covered in dust, except for the semi-circle of floor which "+
   "seems to be kept swept.\n");

   add_item(({"heap","mathoms","mathom","trinkets"}),
   "This heap of trinkets seems even older than all the rest.\n");

   add_item(({"hallway"}),"The hallway is west, which can lead "+
   "out or deeper into the Mathom house.\n");


   add_exit(MATHOM_DIR + "mathom5","west",0,2);
   add_prop("_obj_s_search_fun","do_search");
   add_prop(OBJ_S_SEARCH_FUN,"do_search");
   add_prop(OBJ_I_SEARCH_TIME,8);

   
//   add_stuff();
   reset_room();

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

