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
    set_long("   You stand under a bower in the rose garden " +
        "of the Queen. It is easy to see why the Queen loves roses. " +
        "Roses of every known type surround you and offer a non-" +
        "stop symphony of color and beauty. The fragrance fills " +
        "the air with a sweet perfume. It is quiet here which " +
        "is why many elves enjoy the peace and quiet the garden " +
        "offers them. A lovely statue has been erected here. A " +
        "path of white gravel leads out to the city and winds " +
        "its way further into the garden.\n\n");
 
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
 
    add_item("statue",
        "As you look at the statue, you are startled by how " +
        "real it looks. It looks like it is alive, as the eyes " +
        "seem to look into your soul. The face looks to be wise " +
        "beyond comprehending but fair to look upon. A feeling of " +
        "gentleness seems to surround the statue. Suddenly, you " + 
        "recognize who it is. This is a sculpture of the Queen " +
        "of Telberin.\n");
 
    add_exit( AVENUE_DIR + "road03", "east");
    add_exit( THIS_DIR + "rg02",     "west");
    add_exit( THIS_DIR + "rg06",     "southeast");
 
}
void
reset_room()
{
}
