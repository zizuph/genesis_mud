// cell where draconian prisoner is held
// 
// grace 960420

#include "../local.h"
inherit SPURRM;

#define DOOR_ROOM  "/d/Krynn/solamn/hctower/spur/room/2hp7"
#define DOOR_HELD  DOOR_ROOM->query_door_held()

object door, drac;
int freedom_flag;

void
reset_spur_room()
{
  freedom_flag = 0;

  if (!drac)
    (drac = clone_object(SPUR + "npc/qdrac"))->move_living(0,this_object());
}

void
create_spur_room()
{
    SHORT("cell");
    LONG("This room is deep within the walls of the Knights' Spur.  "+
       "It is cool in here, but not uncomfortably so.  The stone "+
       "walls of this cell are dry and well-maintained, and its floor "+
       "is strewn with fresh-smelling straw.  Two torches flicker "+
       "in the draft which circulates from the guardroom to the east.  "+
       "Manacles on long chains hang from steel rings which protrude "+
       "from the walls at regular intervals.\n");

    AI(({"floor", "straw"}), "The floor is covered by a thick layer "+
       "of straw so fresh it would appear that it is cleaned daily.\n");
    AI(({"walls", "wall"}), "The walls are smooth and dark. There is "+
       "little sign of decay in the mortar which secures the stones in place. "+
       "Steel rings have been introduced into the wall along the seams "+
       "between the stones, and from them hang a half-dozen manacles.\n");
    AI("north wall", "@@wall_desc@@");
    AI(({"manacle", "manacles"}), "The manacles are of the same high-"+
       "quality steel as the ring and the chains that secure them to "+
       "the walls. They seem to be made with an incredible expertise, "+
       "as the locking mechanism is most unusual and appears to be "+
       "unpickable.\n");
    AI("locking mechanism", "It is very foreign to you. It appears that "+
       "certain parts of it must be rotated to form a specific pattern "+
       "inorder for the manacles to be unlocked.\n");
    AI(({"chain", "chains"}), "They are made of steel rings linked to"+
       "gether to form a strong, unbreakable bond.\n");
    ACI(({"chain", "chains"}), "break", "Better to attempt moving a "+
       "mountain with your mind alone. You succeed only in working up "+
       "a sweat.\n");
    AI(({"mortar", "seam", "seams"}), "The mortar is free of signs of "+
      "decay. Where the steel rings have been introduced into the "+
      "seams, the mortar is less uniform, indicating that the rings "+
      "were added after the wall was built.\n");
    AI(({"rings", "steel", "ring", "steel ring"}), 
      "They are made of steel and appear to be unbreakable. The mortar "+
      "around one of the rings seems damaged.\n");

    door = clone_object(SOBJ + "l1d3b");
    door->move(TO);         
    reset_spur_room();
}

leave_inv(object who, object to)
{
    ::leave_inv(who, to);
      if (living(who) && !who->query_npc())
	set_alarm(10.0, 0.0, "lock_up");

}

wall_desc()
{
   if(DOOR_HELD)
     return "The north wall has been swung aside to allow passage to the "+
      	"north.\n";
     return "There is little to distinguish this wall from any other in "+
		"the room.\n";
}


lock_up()
{

    if (door->query_locked() == 0)
    {
       call_other("/d/Krynn/solamn/hctower/spur/room/guardrm", "lockup");
       door->reset_door();
        tell_room(TO, "The iron grill swings closed. You hear the lock "
          + "click.\n");
    }

}

open_pass()
{
    add_exit(SPUR +"room/2hp7", "north");
}

close_pass()
{
   remove_exit("north");
}


/*
 *  Get the draconian free
 */

void
init()
{
    ::init();
    ADD("pry_free","pry");
    ADD("pry_free","scrape");
    ADD("pry_free", "chip");
    ADD("knock_it", "knock");
    ADD("knock_it", "bang");
}

int
pry_free(string str)
{
    mixed *wep, which;
    
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;

    NF(capitalize(query_verb()) + " what from where?\n");
    if (!str)
      return 0;

    NF("You can't seem to do that.\n");
    if (!drac)
      return 0;
 
    if (freedom_flag)
     {
	write("There is nothing of interest to pry at.\n");
        return 0;
     }
    
    NF("You pry idly at the wall.\n");
	
    if (str == "ring from wall" || str == "ring from mortar" || 
	str == "ring" || str == "at ring" || str == "mortar")
      {
	wep = TP->query_weapon(-1);
//       if (!pointerp(wep)) /* why doesn't this work? */
         if (wep == ({ }))
	  {
	      write("You start to pry at the ring, but soon realize "+
		 "you won't succeed in freeing it with your bare hands.\n");
	      say(QCTNAME(TP) + " scrapes futilely at one of the walls.\n");
	      return 1;
	  }
	which = wep[random(sizeof(wep))];
	which->set_dull(which->query_dull() + random(3));
        write("You use your "+ which->query_short() +" to pry at the "+
	   "mortar surrounding the metal ring.\n");
        say(QCTNAME(TP) + " uses a "+ which->query_short() +" to pry at "+
	   "something on the wall.\n");
        set_alarm(4.0, 0.0, "pry_at_mortar");
	return 1;
      }
    else
      return 0;
      
    NF(C(query_verb()) + " what?\n");
    return 0;
}

int
pry_at_mortar()
{
  object qdrac;
  string  ndrac;

  ndrac = "/d/Krynn/solamn/hctower/spur/npc/qdrac2";

  if (random(10))
     {
	write("The mortar crumbles away, freeing the ring from the wall.\n");
        say(QCTNAME(TP) + " seems to have accomplished something with "+
	   "all that prying.\n");
        freedom_flag = 1;
        if ((qdrac = present("_qdrac_", TO))) { qdrac->remove_object(); }
        if (!present("_qdrac2_", TO)) { clone_object(ndrac)->move(TO); }  
        write("The draconian prisoner says: Yes! Yes! You did it!\n");
        say("The draconian prisoner says: Yes! Yes! You did it!\n");
	return 1;
     }        	
   else
     {
  	write("You manage to pry some mortar loose, but not enough.\n");
        return 0;
     }
}

int
knock_it (string str)
{
  object tp = this_player();
  
  notify_fail ("Knock on what?\n");
  if (!str || str != "on north wall")
    return 0;

  if (DOOR_HELD)
    {
      tp->catch_msg ("You feel silly knocking on the north wall. It "+
	    "has been pushed open.\n");
      return 1;
    }
  tp->catch_msg ("You knock on the north wall, coaxing forth a hollow sound.\n");
  say (QCTNAME(tp) + " knocks on the north wall.\n");
  tell_room (DOOR_ROOM, "The hollow sound of something striking stone "+
        "comes from the other side of the wall. Perhaps someone is "+
	"knocking?\n");
  return 1;
}


void
remove_it(object ob)
{
      ob->remove_object();
}
