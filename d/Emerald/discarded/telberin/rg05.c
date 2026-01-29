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
    set_long("   You stand in the royal rose garden. The air " +
        "is filled with the scent of many roses which grow here. " +
        "Perfect in every way, the roses never stop flowering and " +
        "are a showpiece of beauty for everyone in the city. You " +
        "see rose trees, climbing roses that twine up and over " +
        "trellises. Tucked away among the flowers, a small fountain " +
        "fills the garden with a melodious song. A gravel path " +
        "winds its way through the garden.\n\n");
 
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
    add_item("fountain",
        "The fountain is bowl shaped and sits on top of a pedestal. " +
        "In the center of the bowl, water bubbles up and splashes " +
        "onto some rocks in the bowl. The effect creates a gentle " +
        "sound that fills the garden with a relaxing sound.\n");
 
    add_exit( THIS_DIR + "rg06", "east");
    add_exit( THIS_DIR + "rg04",    "west");
 
}
 
void
reset_room()
{
}
