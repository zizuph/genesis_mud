/* 
 * This is gdhall2.c, mainroom of the Green Dragon Inn.
 * Jaypeg Brandybuck of the Shire , Oct 1997
 */

inherit  "/std/room";
#include "/d/Shire/defs.h"
#include "/d/Shire/bounders/guild.h"


void create_room()
{

    add_prop(ROOM_I_INSIDE,1);
    set_short("The dim, musty, corner of the Green Dragon Inn");
    set_long("The interior of the Green Dragon Inn is even darker "+
      "and smokier here, tucked away in a more private area in the "+
      "northwest corner. Conversation is more hushed and private "+
      "here, where the chatter of the local hobbits filters in "+
      "from the mainroom of the Inn. Burly tables and creaky old "+
      "chairs surround you, and booths hug the walls in near "+
      "darkness. Occasionally a hobbit will swagger in and take "+
      "some drink orders, but other than that you'll have to give "+
      "up your seat to go fetch a mug of your favourite thirst-"+
      "quencher. Across the Inn in the northeast corner of the Inn "+
      "a staircase dissapears up onto the next floor.\n");

    add_item(({"cedar","beams","hardwood"}),
      "These walls, that have stood for generations of hobbits, "+
      "are held up by some very sturdy hardwood beams, judging by "+
      "the heady smell probably cedar.\n");
    add_item(({"smoke","smell","odor"}),
      "The musky smell that envelopes you is born of old hardwood, "+
      "tavern food, ale and spirits carried by the tangy smelling "+
      "smoke of pipe-weed.\n");
    add_item(({"bar","barmen","long bar","long polished bar"}),
      "You can see the bar on the far side of the Inn through the "+
      "smoke and gloom, a few stout hobbits man the bar with "+
      "practiced patience, making sure no-one goes thirsty.\n");
    add_item(({"tables","burly tables","chairs","old chairs"}),
      "All about you are the heavy-set hardwood tables and chairs "+
      "that service the custom of the Inn. Most of the chairs are "+
      "the high-chairs the local hobbitfolk and the rarely seen gnomes "+
      "use, though there are a few lower chairs for the occasional "+
      "bigger folk passing through, most often dwarves or humans.\n");
    add_item(({"booth","booths","walls"}),
      "Occupying the walls of this corner are several booths, a more "+
      "private alternative to the tables and chairs in the middle of "+
      "the room. You notice a covered vent in the wall behind one of "+
      "the empty booths.\n");
    add_item(({"vent","covered vent"}),
      "As you sit in the empty booth and peer under the table, you "+
      "can see that there is indeed a vent in the wall covered with "+
      "a hinged wooden hatch. You think that you might be able to "+
      "slip through, there's just enough room for you to enter the "+
      "vent.\n");

    add_exit( BOUND_ROOM_DIR + "gdhall1", "mainroom", 0 );

}

void init()
{
    ::init();
    add_action("entervent", "enter");
}

int entervent(string vent)
{
    notify_fail("Enter what?\n");

    if (vent!="vent") return 0;
    write("You slip through the covered vent in the east wall and "+
      "exit the Green Dragon Inn.\n");

    TP->move_living("into the stables", BOUND_ROOM_DIR + "stables");

    return 1;

}
