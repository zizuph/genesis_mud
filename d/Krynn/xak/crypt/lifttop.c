/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>
#include <filter_funs.h>
#include RND_MEET

inherit  XAKINROOM

#define  TABLE "/d/Krynn/common/rndtables/tbldraconians"


object gullyp1, gullyp2, drac1, drac2, drac3, drac4, drac5;

void
create_xak_room()
{
        set_short("The top of the lift");
        set_long(BS(
           "You are at a dead end. There is a lift here that can take"
	 + " you down through a hole in the ground and perhaps further"
	 + " into the city. There is a torch here burning merrily high up"
	 + " on one of the walls." , 70));

        add_exit(CDIR + "southcrypt4.c", "north", 0);

	add_item(({"lift", "bucket", "buckets"}), "@@liftdesc");
	add_item(({"torch", "burning torch", "wooden torch"}), "@@torch");
        INSIDE;
        LIGHT;

	(DDIR + "liftbottom.c")->load_me();

        set_alarm(1.0,0.0,"reset_xak_room");
}

void
reset_xak_room()
{
  if (!gullyp1)
  {
    gullyp1 = clone_object(MONSTER + "gully_p1.c");
    gullyp1->move(TO);
  }
  if (!gullyp2)
  {
    gullyp2 = clone_object(MONSTER + "gully_p2.c");
    gullyp2->move(TO);
  }
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
    here = find_object(CDIR + "lifttop.c");
    tell_room(here, "The bucket leaves down and the other bucket"
	      + " arrives, someone gets out.\n");
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
      
}

enter(str)
{
    object *ob;
    int i, safety;
    NF("Enter what?\n");
    if ((str == "lift") || (str == "bucket"))
      {
	  write(BS("\nYou step boldly into the lift..   and immediatly it drops"
		   + " like a stone. Your stomach is left behind as the lift"
		   + " drops speedily through the floor and down into a huge"
		   + " underground cavern where it hurtles at breakneck speed"
		   + " towards the cavern floor!.\n", 70));
	  SAY(" boldly steps into the lift and it drops like a"
	      + " brick towards the cavern floor below.");
	  ob = FILTER_LIVE(all_inventory(environment(TP)));
	  for (i = 0; i < sizeof(ob); i++)
	    {
		if (ob[i]->query_name() == "Gully dwarf")
		  safety += 1;
		if (ob[i]->query_name() == "Gully dwarf")
		  safety += 1;
	    }
	  if (safety == 0)
	    {
		write(BS("\nUnfortunatly the gully dwarves that are supposed to"
			 + " slow the lift down appear to be dead. So you hit"
			 + " the ground extremly hard! That hurt!\n", 70));
		say("\nUnfortunatly the gully dwarves that are supposed to"
		    + " slow the lift down\nappear to be dead. So " +
		    QCTNAME(TP) + " hits the ground below very hard!\n");
		say("The other bucket arrives.");
		call_other(DDIR + "liftbottom.c", "bucket_arrival");
		TP->move_living("M", DDIR + "liftbottom.c", 1);
		TP->reduce_hit_point(1000);
		if (TP->query_hp() <= 0)
		  TP->do_die(this_object());
		return 1;
	    }
	  write(BS("Just before the lift smashes into the ground, it suddenly"
		   + " slows and you arrive at your destination no worse"
		   + " for the wear.\n", 70));
	  say(BS("One of the gully dwarves slows the lift just before it arrives"
		 + " at the bottom.", 70));
	  say(BS("The other bucket arrives.", 70));
	  call_other(DDIR + "liftbottom.c", "bucket_arrival");
	  TP->move_living("M", DDIR + "liftbottom.c", 1);
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

torch()
{
    write("The torch is high up on the wall well out of reach.\n");
    return "";
}

