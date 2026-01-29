// file name: ~Avenir/common/outpost/gaol_main.c
// creator(s):  Lilith Apr 2022
// purpose:     This is the main gaol room for Fort Sybarus
//              Players are actually held in gaol_cell.c
// revisions:
//

#include "/d/Avenir/common/outpost/outpost.h"

inherit "/d/Avenir/inherit/tail";
inherit OUTPOST +"fort_base";
#define SEE_WEST   ({ OUTPOST + "gaol_cell"})
#define IMPRISONED  "_free_at_last"

string 
west_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_WEST); i++)
    if((room = find_object(SEE_WEST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "You can see "+ COMPOSITE_LIVE(live) +
       " in one of the gaol cells west of you. ";
  }
  return "It looks like the gaol cells are empty. ";
}

// When the barracks are opened, allow passage.
int
no_east()
{
    write("You start to go east and notice there are a bunch of "+
        "dwarven guards sleeping in that room. Best not to wake "+
        "them.\n");
    return 1;
}

//This exit is not meant to be used.
int
no_west()
{
   write("The door to that cell is closed and locked.\n");
   return 1;
}   
	
void
create_fort_room()
{
	// add_exit_views() uses the short, so using lower case and articles.
    set_short("the gaol of Fort Sybarus");
    set_long("This large circular room is the gaol of Fort Sybarus. "+
	  "Half of it has been divided into cells for holding those who "+
      "are caught fighting or spying. "+
       west_view() +
      "This is a very bare and forbidding place. It does not look "+
      "like a pleasant place to be incarcerated. "+
      "The stone of the floor and walls have been polished so smooth "+
      "and glossy that they reflect the light of the lamps affixed "+
	  "high on the walls. "+
      "There is a set of stairs leading upwards.  "+
      "\nTwo large posters dominate the north wall. "+
      "\n");

    add_exit("adv_guild","up",0);
    add_exit("barrack1","east", no_east);
	add_exit("gaol_cell", "west", no_west);
	
	add_npc(MON + "punisher", 3);
	
	room_add_object(OBJ +"seats/stool", 1);

    // These are in the fort_base.c
	add_exit_views();
    add_fort_room();
	
    add_item(({"north wall"}),
      "The wall is very smooth and shiny. It has posters on it. "+
      "One reads 'INFIDELS' and the other reads 'ABSOLVED'.\n");
    add_item(({"sign", "poster", "posters"}),
      "Which one? The infidels sign or the absolved sign?\n");  
    add_item(({"infidel", "infidels", "infidels sign", "infidel sign",
      "infidel poster", "infidels poster"}),
      "@@do_infidel@@The people listed above are infidels unless "+
      "their names also appear on the 'absolved' sign.\n");
    add_cmd_item(({"infidel", "infidels", "infidels sign", 
	  "infidel sign", "infidel poster", "infidels poster"}), "read",
      "@@do_infidel@@The people listed above are infidels unless "+
      "their names also appear on the 'absolved' sign.\n");
    add_item(({"absolved", "absolved sign", "absolved poster"}),
      "@@do_absolved@@The people listed above have been "+
      "absolved of their crimes.\n");
    add_cmd_item(({"absolved", "absolved sign", "absolved poster"}), 
	  "read", "@@do_absolved@@The people listed above have been "+
      "absolved of their crimes.\n");
    add_item(({"cell", "cells", "gaol cell", "gaol cells"}),
	west_view() +"\n");
	reset_fort_room();

} 

string
do_infidel()
{
    string text;
    text = read_file("/d/Avenir/log/misc/malefactor");
    this_player()->more(text);
    return "\n";      
}

string
do_absolved()
{
    string text;
    text = read_file("/d/Avenir/log/misc/absolved");
    this_player()->more(text);
    return "\n";      
}

/*
 * Function name: enter_inv
 * Description  : This function is called each time an object enters the
 *                inventory of this object. If you mask it, be sure that
 *                you _always_ call the ::enter_inv(ob, old) function.
 * Arguments    : object ob  - the object entering our inventory.
 *                object old - wherever 'ob' came from. This can be 0.
 */
void enter_inv(object ob, object old)
{
    ::enter_inv();
    // Does player have the get out of jail prop? 
	// Remove it so they can't walk out if they offend again.
	// They have to wait for their release.
    if (ob->query_prop(IMPRISONED))
	    ob->remove_prop(IMPRISONED);
}
