// file name: d/Avenir/common/outpost/fort7.c
// creator(s):  Kazz    Feb '95
// last update:
// purpose:     Natural cave archway, leading ne to boat to Bazaar Island
// note:	
// bug(s):
// to-do:       

#pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
inherit OUTPOST +"fort_base";

#define SEE_FORT ({ OUTPOST +"fort5", OUTPOST +"fort3", OUTPOST +"fort2" })

string 
fort_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_FORT); i++)
    if((room = find_object(SEE_FORT[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " "+ COMPOSITE_LIVE(live) +" going about their business";
  }
  return " a tower at the far southwest corner of the fort";
}

void 
create_fort_room()
{
    set_short("a natural archway leading into a tunnel");
    set_long("The cavern walls and ceiling end just to the northeast "+
	    "in a natural archway. "+ 
		"Beyond lies a downward-slanting magma tunnel dimly lit by "+
	    "a glowing white light at the end. "+
        "The sounds of surf rolling onto a shore echo up the tunnel. "+	
		"Southwest leads into the center of Fort Sybarus where you can "+
		"see@@fort_view@@.\n" );

    add_exit(SHIP + "bazaar/boat_path1","northeast",0);
    add_exit("fort5","southwest",0);

	add_item(({"tower", "black tower"}), 
        "The black tower rises high above you to the southeast.\n");
	add_item(({"archway", "natural archway"}),
        "The natural archway provides entrance and exit to the "+
		"fort.\n" );
	add_item(({"cavern", "ceiling", "walls", "tunnel"}),
        "The cavern walls bend up to form the ceiling, stretching "+
		"to the southwest.\n" );
	add_item(({"light", "white light", "glowing light"}),
        "It is at the end of the tunnel. You can barely notice it "+
        "from here.\n" );

	add_exit_views();
    add_towers_out();
    add_gate_items();
    add_basic_fort();
	
} // create_room()
