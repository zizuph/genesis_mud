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
   set_long("This room is almost empty of mathoms, and it "+
   "looks like no one bothers to come back here anymore.  Dust "+
   "covers everything and the little that remains is even more "+
   "unwanted than the mathoms in the rest of the Mathom house. "+
   "There is a small heap of mathoms on the floor, though.  West is "+
   "the way back to the end of the hallway.\n");

   add_item(({"dust","remains"}),"A thick coat of dust is settled "+
   "on top of the heap of mathoms here.\n");

   add_item(({"heap","mathoms","trinkets","unwanted mathoms"}),
   "The heap of unwanted, dusty mathoms is much smaller than those "+
   "in other parts of the Mathom house.\n");


   add_exit(MATHOM_DIR + "mathom7","west",0,2);
   add_prop("_obj_s_search_fun","do_search");
   add_prop(OBJ_S_SEARCH_FUN,"do_search");
   add_prop(OBJ_I_SEARCH_TIME,8);

   
   add_stuff();

}
void add_stuff()
{
    object desk;
    if(!present("warchest",TO))
    {
      desk = clone_object(MATHOM_DIR + "obj/warchest");
      desk->move(TO);
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
   if(searches > 3) return 0;
   seteuid(getuid(TO));
   mathom = clone_object(MATHOM_DIR + "obj/mathom");
   mathom->move(searcher);
   say(QCTNAME(searcher)+ " finds something in the heap.\n");
    return "You find a "+mathom->short()+" in the heap.\n";
}

