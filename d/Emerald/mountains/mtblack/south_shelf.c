inherit "/std/room";
 
#include "/d/Emerald/defs.h";
 
#define	CLIMB_MIN	30
 
void create_room()
{
    set_short("Shelf in southern wall");
    set_long(("You find yourself on a narrow shelf in the "+
       "eastern wall of the shaft. Through a crack in the shaft "+
       "you can see a magnificant view of the wonderous "+
       "land of Emerald.\n"));
    add_exit(MBLACK_DIR + "south_edge", "up", "@@climb");
    add_exit(MBLACK_DIR + "cave_top", "north", 0);
 
    add_item("crack", ("The crack is set in the wall of the cave and through it you can see "+
       "the land of Emerald.\n"));
     add_item("view", ("You take in a sudden breath as you try to take in "+
       "the magnitude of the sight of the land of Emerald. Green "+
       "forests, vast plains, and grandiose seas fill your vision.\n"));
}
 
int
climb()
{
    if (this_player()->query_skill(SS_CLIMB)<CLIMB_MIN+random(25)) {
	write("As you try to climb the mountainside, you slip and fall down.\n");
	write("You hurt yourself as you hit the ground.\n");
	this_player()->reduce_hit_point(this_player()->query_max_hp()/10);
	if (this_player()->query_hp() <= 0)
	    this_player()->do_die(this_object());
	return 1;
    }
    return 0;
}
