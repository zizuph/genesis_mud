/*
 * GRAVEYARD2.c
 * Re-vamped, re-described by Alaron July 26, 1996
 */

inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
reset_room()
{
    object bat;
    int    i;
 
    bat=present("bat");
    if (bat)
        return;
    i = random(5);
    while (i-- > 0) {
        bat=clone_object( GRAVEYARD_DIR + "npc/bat");
        bat->move_living("into a room", this_object());
    }
}
 
void create_room()
{
    set_short("Graveyard");
    set_long("  A soft, cool breeze drifts through the area, gently "+
	     "brushing tall, untended grass. A thick, dark gray fog "+
	     "looms unwaveringy over the entire scene, blanketing "+
	     "the graves in a sheet of despair and loneliness. Hundreds "+
	     "of broken, worn, and neglected headstones line the damp, "+
	     "hilly field, salting the misty countryside with images "+
	     "of death and sadness. The depressing landscape sprawls out "+
	     "in all directions, and endless dark green and gray sea of "+
	     "gravestones.\n\n");

    add_item( ({"fog", "mist", "dark fog", "dark gray fog", "gray fog"}),
	     "A thick, dark gray fog looms over the area, hovering and "+
	     "drifting slowly back and forth, dampening the ground "+
	     "beneath it as well as the spirits of those standing "+
	     "within.\n");

    add_item( ({"ground", "field", "hilly field", "countryside",
		"landscape"}),
	     "The landscape is a dark, moist field of hills and dales. "+
	     "Dark gray stone headstones and graves dot the scene, "+
	     "conjuring up images of the deaths of those who fill "+
	     "the earth beneath the stones.\n");

    add_item( ({"grave" ,"graves", "grave stone", "grave stones",
		"gravestones", "headstones" }),
	     "The stone grave stones are old and worn, showing obvious "+
	     "signs of water decay, in addition to being cracked, "+
	     "broken, chipped, and falling out of the soil. There are "+
	     "hundreds of gravestones leading off in random patterns "+
	     "in all directions. It would take someone quite a long time "+
	     "to search through all of the gravestones to find the "+
	     "one they were looking for.\n");

    add_exit(GRAVEYARD_DIR + "graveyard1", "north", 0);
    add_exit(GRAVEYARD_DIR + "graveyard5", "east", 0);
    add_exit(GRAVEYARD_DIR + "graveyard6", "south", 0);
    add_exit(GRAVEYARD_DIR + "graveyard3", "west", 0);
 
    reset_room();
}
