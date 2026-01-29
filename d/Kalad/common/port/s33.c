#include "default.h"
inherit PORT_ROOM;

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int pres,i;
object *ob;
object ob1;

void
create_port_room()
{
    set_short("Bayside Street");
    set_long("You are travelling on a street aside the bay. The cobblestones beneath you "+
      "are moist and covered with some greenish grime. To the northeast, east "+
      "and southeast "+
      "is a large wooden building. The sparkling bay lies gloriously to your "+
      "west, its beauty only mirrored by the skies above.\n");
    add_item(({"street"}),"A narrow lane that seems to hug the side of "+
      "the bay, as one would a lover.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is weathered "+
      "and as a result has a rather extensive network of cracks on its "+
      "surface. Due to the constant moisture of the environment, a number "+
      "of plants have taken to growing on it.\n");
    add_item(({"greenish grime","grime","plants","plant"}),"Rootless "+
      "plants such as moss and lichen are growing on the pavement.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "An extremely large wooden structure, probably used as some sort of "+
      "warehouse by the size of it.\n");
    add_item(({"sparkling bay","bay"}),"A brilliant azure color, the "+
      "bay mirrors the deep blue of the skies above.\n");
    add_item(({"skies","sky"}),"They are a stunning azure in color, the "+
      "mirror image of the bay beneath.\n");
    add_exit(PORT + "s20", "north");
    add_exit(PORT + "s34", "east", "@@query_move");
    add_exit(PORT + "s46", "south");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/portguard_n");
	ob1 -> move_living("xxx", TO);
    }

}

query_move()
{
    object *ob;
    int pres,i;
    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;
    for(i = 0; i < sizeof(ob); i++){
	if(ob[i]->query_name() == "Aylmer"){
	    pres = 1;
	}

    }

    if (pres == 1){
	write("You are stopped by the militiaman.\n");
	say(QCTNAME(TP) + " tries to go east but is stopped by the militiaman.\n");
    }

    return pres;
}

