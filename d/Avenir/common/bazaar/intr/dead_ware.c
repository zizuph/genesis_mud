// file name: dead_ware
// creator: Cirion, Feb 1996
// last update:
// purpose: This is where the coffins to go
//          to the Isle of the Dead are kept.
// note:
// bug(s):
// to_do:

inherit "/std/room";
#include "/d/Avenir/common/ships/dead/deadship.h"

object *coffins = ({ });
int     counter;

create_room()
{

   object coffin;

   set_short("small warehouse");
   set_long("The odor in here is absolutely terrible, "
           +"like something has died. This is a small "
           +"and mostly empty warehouse, with a simple "
           +"dirt floor and wooden walls.\n");

   AI(({"smell","scent"}),"You can't see the scent, "
           +"but it reeks of the dead.\n");
   AI(({"floor","ground"}),"It is a simple "
           +"dirt floor.\n");
   AI(({"wall","walls"}),"The walls are of simple "
           +"wood frame construction. Obviously "
           +"no one went to any great lengths to "
           +"make this building very attractive.\n");
   
   AE(BAZAAR + "intr/d_str1", "west", 0, 1);

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.



   (BAZAAR+"intr/d_landing")->teledensanka();

   counter = 0;

   coffin = clone_object(COFFIN);
     coffin->bring_in_corpse();
     coffin->move(TO);
     coffin->set_id_name("ware1");

   coffin = clone_object(COFFIN);
     coffin->bring_in_corpse();
     coffin->move(TO);
     coffin->set_id_name("ware2");

   coffin = clone_object(COFFIN);
     coffin->bring_in_corpse();
     coffin->move(TO);
     coffin->set_id_name("ware3");


    add_prop(ROOM_I_NO_CLEANUP, 1);

}

object query_coffins(int number)
{
   if(number+1 > sizeof(coffins))
       return 0;
   else
       return coffins[number];
}

void fill_em_up()
{
   int       k,
             qua;

   if(!sizeof(coffins))
    return;

   for(k=0;k<sizeof(coffins);k++)
   {
     if(!present(coffins[k], TO) || present("corpse", coffins[k])
           || sizeof(filter(all_inventory(coffins[k]), living)))
        continue;
     coffins[k]->bring_in_corpse();
     qua++;
   }

   if(qua)
    tell_room(TO, "A withered human arrives dragging "
      +LANG_WNUM(qua)+" corpses and throws them in the coffins.\n"
      +"The withered human leaves west.\n");
}

void enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(!ob->id(COFFNAME))
    return;
   else
    coffins += ({ob});
    if(!present("corpse", ob))
      counter++;
    if(counter >= 3)
    {
      counter = 0;
      set_alarm(35.0, 0.0, fill_em_up);
    }
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
