// file name: d/Avenir/common/outpost/fort1.c
// creator(s):  Kazz    Feb '95
// last update:
// purpose:     outpost guard room
// note:	various dwarves gather here if needed to defend the fort.
// bug(s):
// to-do:       

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";

static object *guards = allocate(4);

void
add_guards()
{
    int     i = sizeof(guards);
 
    while(i--)
    {
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(MON + "dw_guard");
            guards[i]->equip_me();
            guards[i]->set_fort_wander();
            guards[i]->move(this_object());
        }
    }
} // add_guards()


public void
reset_room()
{

      add_guards();
    
}


create_room()
{
        SHORT("Outpost guard room");
        LONG( "This large room seems to be where the fort guards live when "+
	      "they are not working. Several tables and chairs and benches "+
	      "fill the room. Various dwarves move around, talking, "+
	      "sitting, tending weapons and armour. Half of the north wall "+
	      "is the black stone of the fort, while the other half marks "+
	      "the beginning of the actual cavern wall. South you can see "+
	      "the black stone gate.  East you can see another room which "+
	      "appears to be an eating room.\n" );

        add_exit(OUTPOST + "fort4","east",0);
        add_exit(OUTPOST + "fort2","south",0);
	
        add_item(({"tables", "chairs", "benches"}),
                 "They are wooden, and are spread around the room.\n" );
        add_item(({"gate", "stone gate"}),
                 "The gate is closed.\n" );
	add_item(({"fort", "tall fort", "black fort", "tall black fort"}),
                 "The fort is built with the blackest, smoothest "+
                 "stone and seems very solid.\n" );
        add_item(({"wall", "cavern wall"}),
                 "Only half of the northern wall is constructed, the other "+
		 "half is the natural cavern wall, which curves overhead to "+
		 "the southeast.\n" );

        LIGHT
        IN
	reset_room();

} // create_room()
