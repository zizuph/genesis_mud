inherit "/d/Gondor/elessar/lib/field";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/lib/herb_list.h"
#define MAX_RAB 1

//   Prototypes
void make_rab();

object *rab;
int no_of_rab;
int alarm_id = -1;
string *herbs;


create_room()
{
int i;
   
   area = "southeast";
   areaname = "Lebennin";
   land = "Gondor";
   areatype = 2;
   areadesc = "field";
   grass = "green";
   add_exit(LEB_DIR + "road/fieldr6","south",0,1);
   
   add_item(({"house","hut","building"}),BSN(
         "This old hut seems inhabited, but you think you should not try to go in."));
   
   extraline = "A hut is to your north is in sharp contrast to the lack "+
   "of civilization in this area.";
   
   herbs = ({HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))]});
   
   for(i = 0; i < sizeof(herbs); i++)
   add_herb_file(herbs[i]);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_prop(OBJ_I_SEARCH_TIME,8);
   
   set_search_places(({"bushes","bush","field","fields","ground","grass"}));
   
   rab = allocate(MAX_RAB);
   add_stuff();
   
   make_the_room();
}
add_stuff()
{
   alarm_id = set_alarm(4.0,0.0,&make_rab());
}
reset_room()
{
  ::reset_room();
   add_stuff();
}

void
make_rab()
{
    remove_alarm(alarm_id);
      alarm_id = -1;
   if(!rab[no_of_rab])
      {
      rab[no_of_rab] = clone_object(NPC_DIR + "wrabbit.c");
      if(!random(MAX_RAB))
         {
         rab[no_of_rab]->set_random_move(5);
         rab[no_of_rab]->set_restrain_path("/d/Gondor/lebennin/");
      }
      rab[no_of_rab]->move(TO);
      tell_room(TO,CAP(LANG_ADDART(rab[no_of_rab]->query_nonmet_name()))+" hops into view.\n");
   }
   no_of_rab++;
   if(no_of_rab == MAX_RAB)
      {
      no_of_rab = 0;
      return;
   }
    if (alarm_id == -1)
      alarm_id = set_alarm(itof(200+random(200)),0.0,&make_rab());
   
}

init()
{
  ::init();
  add_action("enter_house","enter");
}

enter_house(string str)
{
  NF("Enter where?\n");
  if (!str || str == "") return 0;
  NF("Enter what?\n");
  if (str != "hut" && str != "house") return 0;
  write("You enter the little hut.\n");
  TP->move_living("into the hut",LEB_DIR+"road/hut1");
  return 1;
}

