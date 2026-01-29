#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"
#define MAX_RAB 1

#define EXIT1 ERE_DIR + "err20","west",0,1
#define EXIT2 ERE_DIR + "err18","south",0,1

//   Prototypes
void make_rab();

int alarm_id;
object *rab;
int no_of_rab;
string *herbs;


create_er_room()
{
    int i;

    area = "just off";
    areaname = "Eastroad";
    land = "Eriador";
    areatype = 3;
    areadesc = "small clearing";
    grass = "green";

    extraline = "This seems to be a pleasant place to rest for "+
    "a while. The clearing is peaceful and serene but rustling "+
    "leaves from the south break the mood. Possibly it may not "+
    "be wise to tarry here too long.";
    "the few trees here, making it very difficult to move "+
    "around. Fortunately, there is a narrow path leading "+
    "east and west.";




    add_exit(EXIT1);
    add_exit(EXIT2);
    set_noshow_obvious(1);
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

make_rab()
{
    remove_alarm(alarm_id);
    alarm_id = 0;
    if(!rab[no_of_rab])
    {
	rab[no_of_rab] = clone_object(NPC_DIR + "errabbit.c");
	if(!random(MAX_RAB))
	{
	    rab[no_of_rab]->set_random_move(5);
	    rab[no_of_rab]->set_restrain_path("/d/Shire/eastroad/");
	}
	rab[no_of_rab]->move(TO);
	tell_room(TO,CAP(LANG_ADDART(rab[no_of_rab]->query_nonmet_name())) +" bounds up to you.\n");
    }
    no_of_rab++;
    if(no_of_rab == MAX_RAB)
    {
	no_of_rab = 0;
	return;
    }
    if (alarm_id)
	alarm_id = set_alarm(itof(200 + random(200)),0.0,&make_rab());

}
