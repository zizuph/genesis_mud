/*
 * Originally coded by Palmer on December 2002
 * Updated for Faerun by Finwe, October 2016
 */

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "stables.h"
#include <stdproperties.h>
#include <terrain.h>
#include <filter_funs.h>

inherit FAERUN_OUTDOOR_BASE;

/* Function prototypes */
public void     reset_room_org();
public void     add_horse(int num, int type);

/* Globals */
int     corral_security();
object  horse;

void
create_faerun_room()
{

    set_short("Corral");
    set_long("This large dirt area is surrounded by a sturdy fence. The ground is littered with hay. Against the eastern part of the fence is a large water trough. Feeding bins overflowing with hay hang along the fence. A gate opens up to the west where you came from.\n");

    add_item("ground", "Its dirt and littered with hay.\n");
    add_item("hay", "Its for horses.\n");
    add_item("gate", "The large wooded gate is open.\n");
    add_item(({"water trough", "trough"}), "A long narrow trough filled with water.\n");
    add_item(({"feeding bin", "bin", "bins", "feeding bins"}), "A wooden box " +
             "hanging on the fence. Its filled with hay.\n");

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_prop(ROOM_I_INSIDE, 0);
    add_exit("stable", "south", corral_security, 0, 0);

    reset_faerun_room();
}


// This keeps visitors to the corral from leading/riding off with a horse
// without paying for it.

int
corral_security()
{
  // The stable master and tack shop keeper run here when attacked
  if (TP->query_wiz_level() || TP->query_name() == "torvil" || TP->query_name() == "Torvil")
        return 0;

  if (present("__leader_object", TP) || present("__rider_object", TP))
  {
   write("The stable master blocks the entrance, shouting 'Do you know " +
      "what we do to horse thieves in these parts!?'\n");
   return 1;
  }

  return 0;
}


/* unused
public void
fill_stable()
{
    int i;
    
    for (i = 0; i < NBR_HORSES; i++)
    {
       horse = clone_object(BREE_STABLES_DIR + "obj/steed");
       horse->move_living("down", TO);
    }
}
*/


public void
//add_horse(int num)
add_horse(int num, int type = 0)
{
    int i;
    for (i = 0; i < num; i++)
     {
       horse = clone_object(STABLES_STEED_DIR + "steed");
//       horse = clone_object("/d/Faerun/stables/steeds/steed");
       if (((type == 1) && horse->id("pony")) ||
           ((type == 2) && horse->id("horse")))
       {
         horse->remove_object();
         i--;
       }
       else
       horse->move_living("down", TO);
     }
}


public void
reset_room_org()
{
     mixed horses, ponies, steeds;
     int to_add;
     int nbr_horses, nbr_ponies, nbr_steeds;
     object room;
     
     room = this_object ();
     //horses = FILTER_RACE (all_inventory (room), "horse");
     steeds = FILTER_RACE (all_inventory (room), "horse");
     // Why isn't there a FILTER_x for this???
     horses = filter(all_inventory (room), &->id("horse"));
     ponies = filter(all_inventory (room), &->id("pony"));
     
     nbr_horses = sizeof (horses);
     nbr_ponies = sizeof (ponies);
     nbr_steeds = sizeof (steeds);
     //if (nbr_horses < NBR_HORSES)
     if (nbr_steeds < NBR_HORSES)
     {
       if (nbr_horses < 2)
       {
         add_horse(1, 1);
         nbr_steeds++;
         nbr_horses++;
       }
       if (nbr_ponies < 2)
       {
         add_horse(1, 2);
         nbr_steeds++;
         nbr_ponies++;
       }
        
       //to_add = NBR_HORSES - nbr_horses;
       to_add = NBR_HORSES - nbr_steeds;
       add_horse(to_add);
     }
}

void reset_faerun_room()
{
    reset_room_org();
}