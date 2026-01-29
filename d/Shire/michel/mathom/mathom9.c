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
   set_long("This corner of the Mathom house is most startling "+
   "because of its almost complete lack of mathoms.  There is a "+
   "very small heap of mathoms in the corner of the west wall, "+
   "and the only other item you note is a very large rocking chair.\n");

   add_item(({"corner","west wall"}),"The corner of the west wall and "+
   "the south wall has a few mathoms in it.\n");

   add_item(({"heap","mathoms","heap of mathoms","trinkets"}),
   "This heap of mathoms is very small indeed, almost all broken "+
   "and all are useless.\n");

   add_exit(MATHOM_DIR + "mathom7","east",0,2);
   add_prop("_obj_s_search_fun","do_search");
   add_prop(OBJ_S_SEARCH_FUN,"do_search");
   add_prop(OBJ_I_SEARCH_TIME,8);

   
   set_alarm(0.7,0.0,"add_stuff");

}
void add_stuff()
{
    object desk;
    if(!present("chair",TO))
    {
      desk = clone_object(MATHOM_DIR + "obj/chair");
      desk->move(TO);
     }
}

void reset_room()
{
   set_alarm(0.7,0.0,"add_stuff");
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
   if(searches > 0) return 0;
   seteuid(getuid(TO));
   mathom = clone_object(MATHOM_DIR + "obj/mathom");
   mathom->move(searcher);
   say(QCTNAME(searcher)+ " finds something in the heap.\n");
    return "You find a "+mathom->short()+" in the heap.\n";
}

