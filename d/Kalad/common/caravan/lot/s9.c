#include "../default.h"
inherit CVAN_ROOM;

#define EKGUARD	(NPC + "ekguard")

object ob1;
object ob2;
object ob3;
object ob4;

void reset_room();

void
create_cvan_room()
{
    set_short("Large Intersection in Caravan Lot");
    set_long("You have reached a large intersection, from the amount of churned "+
      "mud visible, it is quite obvious that this is a heavily travelled "+
      "section of the lot. Large muddy paths head off in several directions. "+
      "A large cage lies just to the west. Animal refuse litters the ground "+
      "here. A rickety wooden sign has been planted in the corner.\n");

    set_time_desc("The intersection is crowded with a great many people.\n",
      "The intersection is devoid of activity.\n");

    add_item(({ "people" }), "Citizens of this city, as well as a few visitors "+
      "from foreign lands.\n");

    add_item(({ "large cage", "cage" }),
      "A shadow-filled cage, little can be made out from here, but you "+
      "believe you just heard a deep throaty growl from there.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The droppings of the many animal brought here by travelling merchants.\n");

    add_item(({ "rickety wooden sign", "wooden sign", "sign", "rickety sign" }),
      "There is writing on it, perhaps you should read it?\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s8", "west");
    add_exit(CVAN + "lot/s5", "north");
    add_exit(CVAN + "lot/s10", "east");
    add_exit(CVAN + "lot/s12", "southwest");
    add_exit(CVAN + "lot/s13", "southeast");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(CVAN + "shop/clmerchant");
	ob1->arm_shopkeeper();
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2  = clone_object(EKGUARD);
	ob2->arm_me();
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(EKGUARD);
	ob3->arm_me();
	ob3->move_living("M",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(EKGUARD);
	ob4->arm_me();
	ob4->move_living("M",TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
	ob1->team_join(ob4);
	tell_room(TO, "Several people arrive at the intersection, among them are "+
	  "a dwarf and three elite soldiers.\n");
    }
}

string
sign()
{
    return "\n" +
    "                        #########################\n"+
    "                        # West: BEWARE! LION    #\n"+
    "                        # North: Intersection   #\n"+
    "                        # East: Traders         #\n"+
    "                        # Southwest: Dead end   #\n"+
    "                        # Southeast: Dealers    #\n"+
    "                        #########################\n"+
    "                                  #####          \n"+
    "                                  #####          \n"+
    "                                  #####          \n"+
    "                                  #####          \n"+
    "                                 #######         \n"+
    "                                 #######         \n";
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
