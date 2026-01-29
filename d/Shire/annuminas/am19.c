inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "local.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

//void reset_room();

create_room() {

  set_short("Entrance to castle");
  set_long("The entrance to the castle lies in front of you. The once "
	  +"great doors that guarded this place have been destroyed "
	  +"and lie on the floor of the castle. There is no dust here "
	  +"so it seems that some creature must be actively living "
	  +"here. There are the characteristic piles of rubble here "
	  +"that have dotted the entire city, as well as a thick cloud "
	  +"of that mist that has been a nuisance to sight.\n");
  add_item(({"doors","door"}),"The doors appear to have been shattered "
			     +"by a great force, and lay destroyed "
			     +"on the floor of the castle.\n");
  add_item(({"street","streets"}),"The streets were once made of "
                                 +"finely crafted cobbles, but now "
                                 +"lay in shambles, covered in "
                                 +"rubble.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in "
                   +"the distance.\n");
  add_item(({"stairs"}),"The stairs are made of beautiful marble, "
		       +"but have obviously felt the ages pass. The "
		       +"once polished shapely steps have given way "
		       +"to rugged, windblown steps. They lead up to "
		       +"the castle before you.\n");
  add_item(({"building","castle"}),"The building rising high into the "
			    +"sky was at some point a grand castle "
				  +"but now, time and the weather has "
				  +"its toll, and it lies as just a "
				  +"larger ruin than the rest.\n");				  
//  add_exit(ANNUM_DIR + "c1", "north", 0);
  add_exit(ANNUM_DIR + "am17", "southeast", 0);
  add_exit(ANNUM_DIR + "am18", "southwest", 0);
reset_shire_room();

}  

void
reset_shire_room()
{
    int n;

   object orcleader, orc1, orc2, yagluk;
   FIXEUID;

   if (!present("_leader"))
   {
     orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
     orcleader->set_long("This is an monstrously large orc guard who " +
        "ravages the castle grounds.\n");
     orcleader->add_name("_leader");
     orcleader->set_power(100 + random(25));
     orcleader->set_random_move(0);
     orcleader->set_type(WARRIOR);
     orcleader->move(TO);
   }

   if (!present("_guard1"))
   {
     orc1 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc1->set_long("This is a patrol orc looking for new prisoners.\n");
     orc1->add_name("_guard1");
     orc1->set_power(100 + random(20));
     orc1->set_type(SLAVE);
     orc1->set_random_move(0);
     orc1->move(TO);
     orcleader->team_join(orc1);
   }
   if (!present("yagluk"))
   {
     yagluk = clone_object(ANN_NPC + "yagluk");
     yagluk->set_random_move(0);
     orcleader->team_join(yagluk);

     yagluk->move(TO);
   }

   if (!present("_guard2"))
   {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->add_name("_guard2");
     orc1->set_long("This guard has risen high in the ranks in Annuminas. " +
        "He patrols the area looking for new prisoners to take.\n");
     orc2->set_power(100 + random(20));
     orc2->set_type(SCOUT);
     orc2->set_random_move(0);
     orc2->move(TO);
     orcleader->team_join(orc2);
   }
   if (!present("yagluk"))
   {
     yagluk = clone_object(ANN_NPC + "yagluk");
     yagluk->set_random_move(0);
     orcleader->team_join(yagluk);

     yagluk->move(TO);
   }



}
