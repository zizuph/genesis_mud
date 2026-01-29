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
    set_long("   You stand in the Queen's rose garden. Everywhere " +
        "you look, you see roses. They are perfect and blossom in " +
        "many colors. The roses never stop flowering and provide a " +
        "show stopping display for everyone who comes here. As you " +
        "look around, you see climbing roses growing up trellises, " +
        "rose trees, and a lovely fountain. Growing at the base of " +
        "the fountain are miniature roses. Some even climb up around " +
        "the base of the fountain. A gravel path winds its way " +
        "through the garden.\n\n");
 
 
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
        "path, under the rose bushes and around the fountain.\n");
    add_item("fountain",
        "The fountain is bowl shaped and sits on top of a pedestal. " +
        "In the center of the bowl is a elven child, standing. " +
        "Little of streams of water spray over his head, creating " +
        "a quiet sound.\n");
 
    add_exit( THIS_DIR + "rg03", "east");
    add_exit( THIS_DIR + "rg01", "west");
 
}
 
void
reset_room()
{
}
