// file name:        /d/Avenir/common/village/street/05.c
// creator(s):       Avenir Wizards, 10/98
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/street/street_base.c";

// object trefoil;

/* Now create the room.  */
void
create_street_room()
{
    set_short("three-way intersection east of the Mercantile Pale, "+
        "north of the Temple Pale, and northeast of the Center Pale");
    set_long("The hedgerow parts with geometric precision, forming three "+
        "corridors that lead away from this point. The northwest path "+
        "leads toward the Bazaar, the eastern one toward the Tribunal,"+
        "and the southwestern one to the village center.\n   "+
        "A trefoil-shaped sculpture upon an alabaster pedestal rises "+
        "from the center of the intersection.\n");

    add_exit("04", "northwest", 0);
    add_exit("06", "east", 0);
    add_exit("40", "southwest", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    add_item(({"pedestal", "alabaster", "alabaster pedestal"}),
        "The pedestal has a broad, pyramidal base. It narrows as "+
        "rises just above eye-level, where the trefoil sculpture "+
        "somehow balances upon its pristine alabaster point.\n");

    /* Cloning the statue here directly because I'm describing
     * a specific one in the room and I want to make it no_show.
     
    trefoil = clone_object(V_OBJ +"sculptures");
    trefoil->set_decor(TREFOIL);
    trefoil->set_no_show();
    trefoil->move(this_object());
      */
    reset_domain_room();
}

