/* created by Aridor 08/30/94 */

#include "../guild/guild.h"

inherit ROOM_BASE

#include <ss_types.h>

int poison = random(2) + 1;
int door_open = 0;
object para;
string other_room;
string *keys = ({ THIEF_OBJ_ID });

void
reset_thief_room()
{
    poison = random(2) + 1;
}

void
create_door_room()
{
    other_room = "/d/Krynn/solamn/thief/guild/shop";
}

nomask void
create_thief_room()
{

    create_door_room();

    DARK;
    
    add_item(({"metal door","door"}),
	     "It's a@@door_state@@ metal door set into the rock.\n");
    add_item(({"rock"}),
	     "Right next to the door you find a small crack in the rock.\n");
    add_search(({"crack","small crack"}),3,"search_crack",1);
    add_item(({"crack","small crack"}),
	     "It's just a crack in the rock.@@poison_someone@@\n");
    add_item(({"lock"}),"@@see_lock@@\n");
    add_cmd_item(({"metal door","door","lock","the lock"}),"pick",
		 "@@pick_the_lock@@\n");
    add_cmd_item(({"metal door","door"}),({"open","unlock"}),
		 "@@unlock_and_open_the_door@@\n");
    add_cmd_item(({"metal door","door"}),"close",
		 "@@door_closed_state@@\n");
    add_cmd_item(({"metal door","door"}),"lock",
		 "@@door_locked_state@@\n");
}

string
door_closed_state()
{
    if (!door_open)
      return "The door is closed already.";
    door_open = 0;
    tell_room(other_room, "The door closes.\n");
    SAY(" closes the door.");
    return "You close the door.";
    
}

string
door_locked_state()
{
    if (!door_open)
      return "The door appears locked already.";
    return "The door is open!";
}

string
door_state()
{
    if (door_open)
      return "n open";
    else
      return " closed";
}

int
door_is_closed()
{
    if (door_open)
      set_alarm(0.1,0.0,"close_again");
    else
      write("The door is closed!\n");
    return !door_open;
}

void
close_again()
{
    if (door_open)
      {
	  door_open = 0;
	  tell_room(TO,"The door closes again.\n");
	  tell_room(other_room, "The door closes automatically.\n");
      }
}

string
unlock_and_open_the_door()
{
    int sk,i;
    object obj;
    if (door_open)
      return "The door is open already.";
    for(i=0;i<sizeof(keys);i++)
      {
	  if (obj = P(keys[i],TP))
	    {
		SAY(" opens the door.");
		tell_room(other_room,"The door opens.\n");
		door_open = 1;
		return "You insert the " + (obj->short()) + " into the " +
		  "small crack, unlock and open the door.";
	    }
	  if (MEMBER(TP))
	    write("You cannot unlock the door without your key ring.\n");
	  sk = TP->query_skill(SS_OPEN_LOCK);
	  TELL_ROOM(TO, TP, " tries to open the door but fails.", TP);
	  return "The door seems locked, but you don't have a clue how to " +
	    "open it.";
      }
}


string
poison_someone()
{
    object pois;
    string str = "";
    int sk = TP->query_skill(SS_OPEN_LOCK);
    int aw = TP->query_skill(SS_AWARENESS);
    if (!poison)
      return "";
    if (sk > 20)
      str = " You come up with the conclusion that this crack must actually " +
	"be the lock for this door.";
    if (aw < 21 && !random(5))
      {
	  str += " You feel something sting into your finger.";
	  poison--;
	  pois = clone_object(TOBJ + "doorpoison");
	  if (!pois->move(TP))
	    set_alarm(3.0,0.0,"start_the_poison",pois);
      }
    return str;
}

mixed
search_crack(object searcher, string what)
{
    object pois;
    string str = "You search the crack very carefully";
    int sk = TP->query_skill(SS_OPEN_LOCK);
    int aw = TP->query_skill(SS_AWARENESS);
    if (!poison)
      return "";
    if (sk > 20)
      str += "and you come up with the conclusion that this crack must actually " +
	"be the lock for this door.";
    else
      str += " but you cannot find anything special.";
    if (aw < 21 && random(5))
      {
	  str += " You feel something sting into your finger.";
	  poison--;
	  pois = clone_object(TOBJ + "doorpoison");
	  if (!pois->move(searcher))
	    set_alarm(3.0,0.0,"start_the_poison",pois);
      }
    return str + "\n";
}


void
start_the_poison(object pois)
{
    pois->start_poison();
}

string
see_lock()
{
    string str = "You find no lock.";
    int sk = TP->query_skill(SS_OPEN_LOCK);
    if (sk > 30)
      str = "This is just a crack in the rock right next to the door, but " +
	"your experience with these things tell you that this is the lock " +
	"of the metal door. You have no clue though how to overcome it, as " +
	"the workings of this lock seem to be beyond your knowledge.";
    if (sk > 60)
      str = "This is just a crack in the rock right next to the door, but " +
	"your experience with these things tell you that this is the lock " +
	"of the metal door. You know that this is a poisoned lock and you " +
	"better not fiddle with it, considering that your skill isn't " +
	"quite up to the complexity of this lock yet.";
    if (sk > 90)
      str = "You easily figure out that this lock is of the poison type, " +
	"you have seen such before. It should be only a matter of concen" +
	"tration and a few minutes to pick it without triggering the poison.";
    return str;
}

string
pick_the_lock()
{
    string str = "What?";
    object pois;
    int tme, tmp;
    int sk = TP->query_skill(SS_OPEN_LOCK);
    if (door_open)
      return "The door is already open!";
    if (para)
      return "Someone else is already busy at the lock!";
    if (sk > 90)
      {
	  para = clone_object("/std/paralyze");
	  para->set_stop_verb("");
	  para->set_stop_message("");
	  para->set_stop_fun("stop_paralyze");
	  para->set_fail_message("You are too busy with the lock right now " +
				 "to do something else.\n");
	  para->set_stop_object(0);
	  tmp = random(2);
	  if (tmp)
	    tme = random(4) + 7;
	  else
	    tme = random(8) + 1;
	  set_alarm(itof(tme),0.0,"spring_open", tmp, TP);
	  para->set_remove_time(tme);
	  para->move(TP);
	  return "You carefully get to work on the lock, this will take " +
	    "some time.";
      }
    if (sk > 60)
      {
	  str = "You failed to open the lock";
	  if (!random(100))
	    {
		str = "By pure luck, you managed to open the lock";
		door_open = 1;
	    }
	  if (!random(10) && poison)
	    {
		str += ", but you also feel a sting in your finger";
		poison--;
		pois = clone_object(TOBJ + "doorpoison");
		if (!pois->move(TP))
		  set_alarm(3.0,0.0,"start_the_poison",pois);
	    }
	  return str + ".";
      }
    if (sk > 30)
      {
	  str = "You fail to pick the lock";
	  if (poison)
	    {
		str += ", and you feel a sting in your finger";
		poison--;
		pois = clone_object(TOBJ + "doorpoison");
		if (!pois->move(TP))
		  set_alarm(3.0,0.0,"start_the_poison",pois);
	    }
      }
    return str + "."; 
}

void
spring_open(int yes, object who)
{
    if (yes)
      {
	  para->remove_object();
	  who->catch_msg("The door springs open as you succeed in picking " +
			 "the lock.\n");
	  SAY(" opens the door.");
	  tell_room(other_room, "The door opens.\n");
	  door_open = 1;
      }
    else
      {
	  who->catch_msg("You fail to open the door, but you managed to " +
			 "avoid the poison.\n");
	  SAYBB(" tried to open the door, but failed.");
      }
    set_alarm(30.0,0.0,"close_again");
}
