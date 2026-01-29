inherit  "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"
#include <filter_funs.h>


object k1;
int pres,i;
object *ob;

create_room() 
{
 ::create_room();

set_short("Dim Corridor");
set_long(BS("The walls of this corridor are made of a strange, smooth black"
	+ " stone. It seems to absorb the light and causes the entire corridor"
	+ " to seem enshrouded in a perpetual twilight. An eerie silence"
	+ " is the only sound, as if the walls were also absorbing the noise as well.",70));

add_item(({"black wall","smooth wall","wall","walls","strange wall","strange walls"}),"It has a very smooth texture and just seems"
	+ "to absorb light.\n"
	+ "It doesnt look like it is natural stone.\n");


add_exit(KARGS + "temple12","southwest","@@query_move");
add_exit(KARGS + "temple5","north",0);

INSIDE;

call_out("reset_room",1);
}

reset_room()
{
if (!k1)
        {
k1 = clone_object(KARGS + "monsters/kguard");
k1->move_living("xxx", TO);
        }
}

query_move()
{
	object *ob;
	int pres,i;

	ob = FILTER_LIVE(all_inventory(this_room()));
	pres = 0;
	for (i = 0; i < sizeof(ob); i++){
	   if (ob[i]->query_name() == "Monster"){
	      pres = 1;
	   }
	}
	 if (pres == 1){
		write("The guard stops you.\n");
		say("The guard stops you.\n");
	 }

return pres;
}