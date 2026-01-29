/* created by Aridor 01/11/94 */

inherit "/std/room";

#include "../local.h"
#define SKIE       LIV + "skie"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

object my_dragon;

void
get_started()
{
  if (my_dragon)
    return;
  my_dragon = clone_object(SKIE);
  my_dragon->move_living("xx",ROOM + "lair");
}


void
create_room()
{
  set_short("On Skie's back");
  set_long("You are on the back of a huge blue dragon. You can dismount.\n");
  add_item(({"view","surroundings"}),"@@my_surroundings");
  
  get_started();
}


void
init()
{
  ::init();
  ADA("dismount");
}

int
dismount(string str)
{
  int ok = 0;
  if (!str)
    ok = 1;
  else if (str == "dragon")
    ok = 1;
  if (!ok)
    return 0;
  if (my_dragon)
    TP->move_living("dismounting the dragon", E(my_dragon));
  else
    write("Hmmm, you can't dismount a FLYING dragon!\n");
  return 1;
}

object
query_my_dragon() 
{
  if (!my_dragon)
    get_started();
  return my_dragon;
}

void
drop_everyone_down()
{
  object *onme = all_inventory(TO);
  object whereto = E(my_dragon);
  int i;
  tell_room(TO,"The dragon you are on spreads its wings and takes to the sky.\n");
  tell_room(TO,"It flies a loop and you faaaaaaaaaaaaaall...\n");
  for(i = 0; i<sizeof(onme); i++)
    {
      if (onme[i]->query_prop(LIVE_I_IS))
	{
	    if (onme[i]->query_real_name() != "kitiara")
	      onme[i]->move_living("falling through the air",whereto);
	}
      else
	{
	  tell_room(whereto,capitalize(onme[i]->short()) + " drops to the ground.\n");
	  onme[i]->move(whereto);
	}
    }
}


my_surroundings()
{
  object *things;
  string thd, thl;
  if (my_dragon)
    {
      things = all_inventory(E(my_dragon));
      thd = COMPOSITE_DEAD(FILTER_DEAD(things));
      thl = COMPOSITE_LIVE(FILTER_LIVE(things));
      return (E(my_dragon))->long() +
	((thd != "something") ? capitalize(thd) + ".\n" : "") +
	  ((thl != "someone") ? capitalize(thl) + ".\n" : "");
    }
  else
    return "You are in the big black void.\n";
}


everyone_down_im_dead()
{
    object *onme = all_inventory(TO);
    object whereto = E(my_dragon);
    mixed onmel = FILTER_LIVE(onme);
    mixed onmed = FILTER_DEAD(onme);
    int i;
    tell_room(TO,"The dragon crumbles beneath you and you topple down " +
	      "to the ground.\n");
    if (onmed && onmed != ({}))
      tell_room(whereto, capitalize(COMPOSITE_DEAD(onmed)) + " drop" +
		((sizeof(onmed)<=1) ? "s" : "") + " to the ground.\n");
    for(i = 0; i<sizeof(onme); i++)
      {
	  if (onme[i]->query_prop(LIVE_I_IS))
	    {
		onme[i]->move_living(0,whereto);
		tell_room(whereto, QCTNAME(onme[i]) +
			  " arrives tumbling off the dead dragon.\n");
	    }
	  else
	    onme[i]->move(whereto);
      }
}
