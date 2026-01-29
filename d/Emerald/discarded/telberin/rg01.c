/* Rose Garden in Telberin
 * By Finwe
 * January 1997
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
#define MAX_FLOWERS   3         /* max num of flowers per room */ 
 
int flower;
int flower_counter;

void reset_room();
void
create_room()
{
    set_alarm(1.0,0.0,"reset_room");
    set_short("The rose garden in Telberin");
    set_long("   You stand under a bower in the royal rose garden " +
        "The sweet fragrance of roses fills the air. All around " +
        "you are various roses of every imaginable type. The Queen " +
        "loves flowers but holds roses in the highest esteem. Many " +
        "different rose varieties are grown here for her enjoyment. " +
        "A lovely gravel path winds its way here to other " +
        "parts of the garden.\n\n");
 
    add_item(({"rose", "roses"}),
        "You see roses of every color and style. Some wind " +
        "up and over trellises and others are trained as tree " +
        "roses. You even see miniature roses growing here.\n");
    add_item(({"gravel path", "path"}),
        "The path is made from white crushed rocks which " +
        "crunch under your feet. It winds through the garden " +
        "and keeps the visitor's feet dry.\n");
    add_item(({"arch", "bower"}),
        "The bower is tall and wide. Roses grow up and " +
        "over it, providing shade for those who stand " +
        "underneath it. The bower marks the entrance to " +
        "the garden.\n");
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
        "largercounterparts. They grow along the edge of the garden " +
        "path and under the rose bushes.\n");

    flower = 0;  

    add_exit( THIS_DIR   + "rg02",  "east");
    add_exit( AVENUE_DIR + "ave31", "west");
    add_exit( THIS_DIR   + "rg04",  "southeast");
 
}

init()
{
    add_action("pick_flower", "pick");
    ::init();
}



pick_flower(string str)
{
    int ran_fl;
    string what_flower;
 
    what_flower = "r_rose";
 
 
   if (flower_counter == MAX_FLOWERS)
    {
        write ("You notice that all the flowers has been picked.\n");
        return 1;
    }
    else
    {
            if (str == "rose")
        {
            clone_object(TOWNSHIP_DIR + "flowers/" + what_flower)->
                move(this_player());
            write ("You pick a red rose from the trellis.\n");
            say (QCTNAME(this_player()) + " picks a flower from the " +
                "trellis.\n");
            flower_counter = flower_counter + 1;
            return 1;
         }
    }
    return 0;
}
 

void
reset_room()
{
    flower_counter = 0;
}
 
void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}
