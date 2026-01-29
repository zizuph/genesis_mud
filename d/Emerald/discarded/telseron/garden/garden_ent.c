/*
 * Garden entrance of Telseron
 * Coded by Finwe, September 1996
 */
 
#include <stdproperties.h>
#include "/d/Emerald/defs.h"
#define MAX_FLOWERS   3         /* max num of flowers per room */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
 
int flower;
int flower_counter;
 
void reset_room();
 
void
create_room()
{
    object gate;
    set_short("The garden entrance");
    set_long("   You stand at the entrance of the garden. A " +
        "gracefully arched trellis stands here. It is bedecked " +
        "with climbing roses and marks the entrance to the garden. " +
        "The roses are the best you've ever seen. They are a marvel " +
        "of beauty and hint to what is beyond the trellis. An " +
        "ornamental gate is here. It is simple yet elegant in " +
        "construction. A walkway begins here and enters the garden. " +
        "Encircling the garden is a sculptured hedge.\n\n");
 
    add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");
    add_item("gate", 
        "The gate is about 3 feet tall with a circular top. It is " +
        "made of gold filigree.\n");
    add_item(({"walkway", "ground"}),
        "The walkway is made of flagstones. Growing between the " +
        "flagstones is thyme. The plant gives exhudes a sweet " +
        "fragrance as you walk through the garden.\n");
    add_item("trellis",
        "It is is sturdy, and arches over your head. Red roses " +
        "climb up and over it, filling the air with sweet " +
        "perfume.\n");
 
    gate = clone_object( TOWNSHIP_DIR + "doors/gate_gar_in");
    gate->move(this_object());
    reset_room();
    flower = 0;

    catch(call_other(TELSERON_DIR + "garden/" +  "clone_handler", "??"));
    add_exit(TOWNSHIP_DIR + "rd27", "north");
}

 
init()
{
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("pick_fruit", "pick");
    ::init();
}
 
 
sniff_air(string str)
{
    if ((str == "air") || (str == "flowers"))
    {
        write ("You take a deep breath. The heady fragrance leaves " +
               "you smiling contendedly.\n");
        say (QCTNAME(this_player()) + " takes a deep breath and " +
             "sighs contentedly.\n");
        return 1;
    }
    else
    {
        write ("You wrinkle your nose.\n");
        say (QCTNAME(this_player()) + " wrinkles their noise.\n");
        return 0;
    }
    return 1;
}
 
pick_fruit(string str)
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
