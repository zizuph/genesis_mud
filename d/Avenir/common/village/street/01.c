// file name:        /d/Avenir/common/village/street/01.c
// creator(s):       Avenir Wizards, 10/98
// revisions:        Lilith, Oct 2021
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
    set_short("street northwest of the garment district");

    set_long("A wide break in the northwest corner of the hedgerow "+
        "reveals a broad cobbled walk leading up to an iron gate. "+
        "On either side of the gate two small towers spiral upward, "+
        "watchposts for the vigilant guards who protect the peace. "+ 
        "The bazaar lies beyond, to the north, whilst the garment "+
		"district of the sybarite village lies on the other side of "+
        "the large hedge to the south, from whence the sounds of "+
        "commerce ebb and flow.\n");

    add_exit(BAZAAR + "extr/str24", "northwest", 0);
    add_exit("02", "east", 0);
    add_exit("00", "southwest", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}

