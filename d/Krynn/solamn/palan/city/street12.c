/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

string
query_to_jail()
{
  return "southwest";
}

void
create_palan_room()
{

    set_short("Fish market");
    set_long(BS("This is the fish market. The smell of fish is "
         +   "overwhelming, but unfortunately the market is closed. "
         +   "You can see the stands deserted. The view over "
         +   "the bay from here is impressive, fishing boats "
         +   "line the pier and are spread out over the bay.",SL));

    add_exit(ROOM + "street11","east",0,1);
    add_exit(ROOM + "street13","west",0,1);
    add_exit(ROOM + "plaza","southwest",0,1);

    add_item(({"stand","stands","market"}),BS("Strange really that "
         +   "all is deserted here. There is nothing left for you "
         +   "but to look for fish elsewhere.",SL));
    add_item(({"bay","water","ships","boat","ship","boats","fishing boat"
             ,"fishing boats"}),BS("Most boats are anchored at the pier "
         +   "but a few float idly in the bay. Further out you can see "
         +   "see the bay opening into the ocean.",SL));

}



