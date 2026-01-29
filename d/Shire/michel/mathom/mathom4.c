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
   set_long("A heap of mathoms lies at your feet, and does not "+
   "get much higher than your ankle at any point in this room, "+
   "as it is a place much visited by hobbits from all over the "+
   "Shire.  On the east wall is a painting and on the south is "+
   "a plaque.  On the north wall is a sign. "+
   "In the middle of this dim room you see various "+
   "glass cases supported by finely crafted hickory pedestals. "+
   "West is the main hall.\n");

   add_item(({"mathoms","trinkets","trinket","mathom","heap"}),
   "The mathoms are not very plentiful here, back in the other "+
   "halls, are many many more.\n");

   add_item(({"east wall","painting","bandobras","horse"}),
   "On the wall to the east is a painting of Bandobras Took riding "+
   "a horse- quite a feat for a hobbit!\n");

   add_item(({"pedestal","case"}), "There are many, examine them to see "+
   "which one in particular you wish to view.\n");

   add_item(({"glass cases","cases","pedestals","hickory pedestals"}),
   "There are three glass cases in all, supported by three pedestals. "+
   "There is a small case, a medium-sized case, and a very large case.\n");

   add_item(({"small case","small","crop","rider's crop"}),
   "In the small case is a rider's crop, used by Bandobras Took.\n");

   add_item(({"medium-sized case","medium case","stirrup","stirrups"}),
   "In the medium-sized case are the stirrups used by Bandobras Took "+
   "in the Battle of Greenfields.\n");

   add_item(({"very large case","large case","saddle"}),
   "In the very large case is Bandobras Took's saddle, made of leather "+
   "and decorated with ornate leatherwork.\n");

   add_item(({"sign","north wall"}),"The sign on the north wall has writing "+
   "on it, which you may read.\n");

   add_item(({"south wall","south","plaque"}),
   "There is an inscription on the plaque, which you may read.\n");

   add_cmd_item("inscription","read","The inscription reads:\n"+
   "This riding gear belonged to Bandobras Took, hero of the Battle "+
   "of Greenfields in 1146.\n");

   add_cmd_item(({"writing","sign"}),"read","The sign reads: "+
   "In the year 1146 of the Founding of the Shire, a great host "+
   "of orcs did descend out of the north, threatening all hobbits of "+
   "the Shire with thralldom.  The hero Bandobras Took rallied the Shire-folk "+
   "and riding his horse, led the hobbits to victory over the evil band of orcs. "+
   "He stood four-feet five inches tall, the tallest hobbit in history.\n"+
   "Bandobras Took:  1103-1205 S.R.\n");
   add_exit(MATHOM_DIR + "mathom3","west",0,2);
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

