/* Rose Garden in Telberin
 * By Finwe
 * January 1997
 */            
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
void reset_room();
void
create_room()
{
    set_alarm(1.0,0.0,"reset_room");
    set_short("The rose garden in Telberin");
    set_long("   You stand in a corner of the rose garden of " +
        "the Queen. This quiet corner is rarely visited except by " +
        "those seeking peace and solitude in the city. Park " +
        "benches have been set here for visitors to sit on and " +
        "enjoy the beauty here. A gravel path winds its way through " +
        "the garden.\n\n");
 
    add_item(({"rose", "roses"}),
        "You see roses of every color and style. Some wind " +
        "up and over trellises and others are trained as tree " +
        "roses. You even see miniature roses growing here.\n");
    add_item(({"gravel path", "path"}),
        "The path is made from white crushed rocks which " +
        "crunch under your feet. It winds through the garden " +
        "and keeps the visitor's feet dry.\n");
    add_item(({"tree rose", "tree roses"}),
        "These plants have been specially trained to " +
        "imitate trees. The lower part of the plants are smooth " +
        "and free of thorns. The upper part branches up and " +
        "outward and is covered with blossoms.\n");
    add_item(({"trellis", "trellises"}),
        "From what you can see of them, they are painted white " +
        "and are sturdy looking. Nevertheless, the trellises are " +
        "full of rose plants.\n");
    add_item(({"miniature rose", "miniature roses"}),
        "These little plants are perfect replicas of their much " +
        "bigger counterparts. They grow along the edge of the garden " +
        "path.\n");
    add_item(({"benches" , "park benches", "park bench", "bench"}),
        "They are carved of white marble. The benches are " +
        "large enough to allow several elves to sit on. They are " +
        "ornately decorated with scrollwork, wandering ivy, " +
        "and motifs of roses.\n");
    add_item("scrollwork", 
        "This embellishment resembles a partially rolled scroll " +
        "of paper, hence its name. It carved into the ends of " +
        "the benches\n");
    add_item(({"wandering ivy", "ivy", "border", "borders"}),
        "The ivy border has been carved onto the edges of the " +
        "benches. It wanders from edge to edge and looks very real.\n");
    add_item(({"motifs", "motif", "motif of roses", "rose motifs"}),
        "The rose motifs are lovely. They are of rosebuds on " +
        "the verge of opening with one large on in the center of " +
        "the bench. The central motif is a rose fully open. The " +
        "motifs look so real, they could be picked.\n");
 
    add_exit( THIS_DIR + "rg05", "east");
    add_exit( THIS_DIR + "rg01", "northwest");
 
}
 
void
reset_room()
{
}
