
// file name:        /d/Avenir/common/village/street/02.c
// creator(s):       Avenir Wizards, 10/98
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/street/street_base.c";

/* Now create the room.  */
void
create_street_room()
{
    set_short("Street north of the merchantile pale");
    set_long("The lush hedges continue to frame the broad walk as it "+
        "stretches along. To the west the cobbled street bends south"+
        "westwards, while eastwards it bends southeast. "+
        "There is a break in the hedgerow south of here, where the "+
		"cobbled walk leads into the garment district of the "+
		"mercantile pale. An open iron gate grants passage.\n");

//  add_exit(MERC+"10", "south", 0); 
    add_exit("01", "west", 0);
    add_exit("03", "east", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */
	 
    add_item(({"gate","iron gate"}),
        "This gate is apparently more of an adornment than an actual "+
        "means of keeping people in or out of this area. Finely wrought "+
		"iron has been sculpted into a magnificent piece of art. It looks "+
		"very delicate, but the size of it implies that it still weighs "+
		"quite a bit. It has been left open for free passage in and out.\n");
    add_cmd_item(({"gate","iron gate"}), ({"open","close"}),
        "It won't budge.\n");

    reset_domain_room();
}

