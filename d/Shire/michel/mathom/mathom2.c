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
    set_long("This side room at the mathom house seems to "+
   "hold a disproportionate amount of old, discarded trinkets. "+
   "From the floor to a foot shy of the ceiling, mathoms are piled "+
   "in one giant heap.  On a special stand, somewhat away from "+
   "the big heap, there is a wire rack with a note attached to it.\n");


   add_item(({"heap","trinkets","mathoms"}),
   "The mathoms are piled in a big heap around the stand.\n");
   add_item(({"stand","wire rack","rack"}),
   "The stand and wire rack look as if they were made to support "+
   "something light.\n");

   add_item(({"floor","ceiling","room","walls","wall"}),
   "The mathoms cover the floor and walls almost completely. "+
   "The ceiling, seven feet above the floor only gets about "+
   "a foot and a half of breathing room.  This place is truly crammed.\n");

   add_item(({"note","attached note","note attached"}),
   "The note has writing on it, you may read it.\n");

   add_cmd_item("note","read","The note reads:\n"+
   "Reclaimed by owner, B.B.\n");

   add_exit(MATHOM_DIR + "mathom1","west",0,2);

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

