/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>
#include <filter_funs.h>
#include RND_MEET

inherit  XAKINROOM

#define  TABLE "/d/Krynn/common/rndtables/tbldraconians"

object drac1, drac2, drac3, drac4, drac5;

create_xak_room()
{
    set_short("The bottom of the lift");
    set_long(BS(
		"You find yourself in a large open square deep down in a huge"
		+ " underground cavern. There is a"
		+ " bucket here attached to a rope that leads up into darkness."
		+ " You can also see a wooden sign swinging freely from"
		+ " the crumbling stone wall of one of the many deserted buildings"
		+ " down here. High above the sign on the wall is a torch burning"
		+ " merrily providing light." , 70));

    add_exit(DDIR + "larder.c", "north", 0);
    add_exit(DDIR + "street1.c", "south", 0);

    add_item(({"lift", "bucket", "buckets"}), "@@liftdesc");
    add_item(({"sign", "wooden sign"}), "@@sign");
    add_item(({"torch", "wooden torch"}), "@@torch");
    INSIDE
      LIGHT
	(CDIR + "lifttop.c")->load_me();

    reset_room();
}

reset_xak_room()
{
    if (!drac1)
      set_alarm(1.0,0.0,"load_d1");
    if (!drac2)
      set_alarm(2.0,0.0,"load_d2");
    if (!drac3)
      set_alarm(3.0,0.0,"load_d3");
    if (!drac4)
      set_alarm(5.0,0.0,"load_d4");
    if (!drac5)
      set_alarm(6.0,0.0,"load_d5");
}

query_gully()
{
    object *ob, here;
    int safety, i;

    here = find_object(CDIR + "lifttop.c");

    ob = FILTER_LIVE(all_inventory(here));
    for (i = 0; i < sizeof(ob); i++)
    {
	if (ob[i]->query_name() == "Gully dwarf")
	  safety += 1;
	if (ob[i]->query_name() == "Gully dwarf")
	  safety += 1;
    }
    return safety;
}

bucket_arrival()
{
    object here;
    here = find_object(DDIR + "liftbottom.c");
    tell_room(here, "The bucket leaves up and the other bucket"
	      + " arrives.\nSomeone gets out.\n");
}

load_d1()
{
    drac1 = RANDOM_MEET(TABLE);
    /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
    if (drac1->query_prop(OBJ_I_COLORABLE))
      drac1->set_color("black");
    drac1->move_living(0,TO);
    drac1->set_aggressive(1);
    drac1->set_random_move(30);
    tell_room(this_object(), "A draconian arrives.\n");
}

load_d2()
{
    drac2 = RANDOM_MEET(TABLE);
    /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
    if (drac2->query_prop(OBJ_I_COLORABLE))
      drac2->set_color("black");
    drac2->move_living(0,TO);
    drac2->set_aggressive(1);
    drac2->set_random_move(30);
    tell_room(this_object(), "A draconian arrives.\n");
}

load_d3()
{
    drac3 = RANDOM_MEET(TABLE);
    /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
    if (drac3->query_prop(OBJ_I_COLORABLE))
      drac3->set_color("black");
    drac3->move_living(0,TO);
    drac3->set_aggressive(1);
    drac3->set_random_move(30);
    tell_room(this_object(), "A draconian arrives.\n");
}

load_d4()
{
    drac4 = RANDOM_MEET(TABLE);
    /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
    if (drac4->query_prop(OBJ_I_COLORABLE))
      drac4->set_color("black");
    drac4->move_living(0,TO);
    drac4->set_aggressive(1);
    drac4->set_random_move(30);
    tell_room(this_object(), "A draconian arrives.\n");
}

load_d5()
{
    drac5 = RANDOM_MEET(TABLE);
    /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
    if (drac5->query_prop(OBJ_I_COLORABLE))
      drac5->set_color("black");
    drac5->move_living(0,TO);
    drac5->set_aggressive(1);
    drac5->set_random_move(30);
    tell_room(this_object(), "A draconian arrives.\n");
}


init()
{
    ::init();
    ADA("enter");
    ADA("read");

}

read(str)
{
    NF("Read what?\n");
    if (str != "sign" && str != "wooden sign")
      return 0;
    write("The sign reads: 'Entor dat buckot iff in me pulls yous up.... probably.\n");
    return 1;
}

sign()
{
    write("Its a wooden sign with some readable words on it.. sort of.\n");
    return "";
}

torch()
{
    write("The torch is well out of reach high on the wall.\n");
    return "";
}

enter(str)
{
    object *ob, here;
    int i, safety;
    NF("Enter what?\n");
    if ((str == "lift") || (str == "bucket"))
    {	
	here = find_object(CDIR + "lifttop.c");

	ob = FILTER_LIVE(all_inventory(here));
	for (i = 0; i < sizeof(ob); i++)
	{
	    if (ob[i]->query_name() == "Gully dwarf")
	      safety += 1;
	    if (ob[i]->query_name() == "Gully dwarf")
	      safety += 1;
	}
	if (safety == 0)
	{
	    write(BS("\nYou get in the bucket, but nothing happens."
		     + " after a few moments you decide to get out again. Well "
		     + "that was fun!\n", 70));
	    return 1;
	}
	write(BS("You enter the bucket and immediatly it rises upwards"
		 + " pretty soon you find yourself rising up through the"
		 + " roof of the cavern and into a room above.\n", 70));
	SAY(" enters the bucket and is lifted up into the darkness above.");
	say("The other bucket arrives.\n");
	call_other(CDIR + "lifttop.c", "bucket_arrival");
	TP->move_living("M", CDIR + "lifttop.c", 1);
	return 1;
    }
    return 0;
}


liftdesc()
{
    write(BS("The lift is a crude device, it is operated by two buckets"
	     + " tied together by a rope and the rope is passed over a pully"
	     + ". The gully dwarf that wants to get to the streets below"
	     + " simply jumps in the bucket up here and his weight causes"
	     + " the bucket to drop and the other bucket at the bottom of"
	     + " the chasm to rise to the top. If necessary the buckets"
	     + " are slowed by 2 gully dwarves at the pully to stop"
	     + " the buckets from arriving at their destination too"
	     + " quickly....", 70));
    SAY(" examines the lift.");
    return "";
}
