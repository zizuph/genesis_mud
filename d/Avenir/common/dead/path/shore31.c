// file name: shore31
// creator: Ilyian, September 21, 1995
// last update: room along the Shore path around the
//              Isle of the Dead
// purpose:
// note: Most of the code for this room is contained
//       in the inherited file /d/Avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
// #include "../dead.h"
#include "/d/Avenir/common/ships/dead/deadship.h"

object *coffins = ({ });

void
create_room()
{
   object coffin;

   shore_long("The path comes to an abrupt end here, "
             +"leading only back to the south. The "
             +"rocky shoreline of the island turns into "
             +"the marsh to the west, and north and "
             +"east lies the vast dark sea."); 

   shore_exit("south","30");
   shore_marsh("west","63");


   coffin = clone_object(COFFIN);
     coffin->move(TO);
     coffin->set_id_name("dead1");
   coffin = clone_object(COFFIN);
     coffin->move(TO);
     coffin->set_id_name("dead2");
   coffin = clone_object(COFFIN);
     coffin->move(TO);
     coffin->set_id_name("dead3");

}

void populate_island()
{
   "/d/Avenir/common/dead/u_maker"->create_room();
   "/d/Avenir/common/dead/u_maker"->start_cooking();
}

object query_coffins(int number)
{
   if(number + 1 > sizeof(coffins))
       return 0;
   else
       return coffins[number];
}

enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(interactive(ob))
      populate_island();

   if(!ob->id(COFFNAME))
    return;
   else
    coffins += ({ob});
    return;
}

leave_inv(object ob, object where)
{
   ::leave_inv(ob, where);

   if(!ob->id(COFFNAME))
    return;
   else
    coffins -= ({ob});
    return;
}
