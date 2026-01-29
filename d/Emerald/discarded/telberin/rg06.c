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
    set_long("   You stand under a bower in the Queen's rose " +
        "garden. The garden is filled with the most lovely roses " +
        "you have ever seen. You see white, pale pink, deep red, " +
        "lavender, yellow, and every other imaginable colored " +
        "rose growing here. They bloom continuously, providing " +
        "an everlasting supply of blossoms for her castle. A " +
        "lovely gravel path winds its way to other areas of the " +
        "garden or out to the city.\n\n");
 
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
    add_item(({"arch", "bower"}),
        "The bower is tall and wide. Roses grow up and " +
        "over it, providing shade for those who stand " +
        "underneath it. The bower marks the entrance to " +
        "the garden.\n");
 
 
    add_exit( AVENUE_DIR + "ave27", "south");
    add_exit( THIS_DIR + "rg05",    "west");
    add_exit( THIS_DIR + "rg03",    "northwest");
 
}
 
void
reset_room()
{
}
