/* Author: Modred 950816 */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

void create_room()
{
    set_short("Top of the stairs");
    set_long("You stand in at the top of the grand marble stairway."+
     " In front of you huge bronze doors are standing wide open"+
     " revealing a hallway behind them inside the fort. The fort "+
     " rise towards the sky looming over you and you feel a chill in your."+
     " bones standing in their shadow. You can enter the fort to the south"+
     " or go back to the courtyard to the north.\n");

    add_exit(RHUN_DIR + "newruins/court_s","north");
    add_exit(RHUN_DIR + "newruins/hall","south");

    add_item(({"stairway", "stairs"}),"The stairs are wide, and"+
    " almost seem to be cut from a solid block of marble. Statues"+
    " line both sides of the stairway. The craftsmanship in the stair"+
    " and the statues is exquisite, far beyond the rest of the fort\n");

  add_item(({"doors","bronze doors"}),"The doors are made of polished bronze and covered "+
     "with strange symbols. As you look closer you see that the doors are not only open,"+
     "but that they have been thrown open with such force that the walls have cracked at the"+ 
     " impact.\n");

    add_item(({"symbols","strange symbols"})," The doors are covered "+
     "with strange symbols. They appear to be the same that adorns the walls, but at the"+
     " center of each door you see a strange carving, like a rune.\n");
 
   add_item(({"rune","runes","strange carving"})," In the center of each door sits a strange "+
     "rune. You hav no idea what it means, but you are drawn towards it like a moth to a "+
     "naked flame. You slowly reach out to touch it....and quickly snatch your hand back! It is"+
     " icy cold to the touch!! Whatever used to be here hasnt left completely.\n");
}
