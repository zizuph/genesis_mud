/*
 * - froom.c
 *
 * Room where Felix resides and orders for his services may be placed.
 */
#pragma no_clone
#pragma strict_types

#include "defs.h"
inherit STD_ROOM;

object felix;

string
query_sign()
{
    return("                              ''~``\n"+
"                             ( o o )\n"+
"           +------------.oooO--(_)--Oooo.------------+\n"+
"           |                                         |\n"+
"           |           Drakmere Apothecary           |\n"+
"           |                                         |\n"+
"           |     Ask the proprietor for a 'list'     |\n"+
"           |                                         |\n"+
"           |              .oooO                      |\n"+
"           |              (   )   Oooo.              |\n"+
"           +---------------\\ (----(   )--------------+\n"+
"                            \\_)    ) /\n"+
"                                   (_/\n"); 
}

void
reset_room()
{
    if (!felix)
    {
        felix = clone_object(FELIX_DIR + "felix");
        felix->move_living("M", TO);
        TELL_CAN_SEE(TO, QCTNAME(felix) + " steps into view.\n");
    }
}

static void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Ruined apothecary");
    set_long("This is an apothecary that appears to be in ruin. "+
        "There are bottles and jars of all different shapes and sizes "+
        "lining the walls and filling the tables and counters. There is "+
        "a strange yet familiar odor that permeates the area. In the "+
        "corner there is a young man holding up a sign.\n");
    add_item(({"room", "apothecary", "area", "ruined apothecary"}), query_long);
    add_item(({"sign"}), query_sign);
    add_cmd_item("sign","read", query_sign);
    add_item(({"man", "young man"}),
        "He is in the corner holding up a sign.\n");
    add_item(({"bottles", "bottles"}),
        "There are many different bottles in many different "+
        "shapes, colours and sizes. Some are empty and some filled "+
        "with strange liquids.\n");
    add_item(({"empty bottles", "empty bottle"}),
        "There are empty bottles everywhere just waiting to be filled "+
        "with some great potion.\n");
    add_item(({"filled bottles", "filled bottle"}),
        "There are so many filled bottles here that are just waiting "+
        "to be purchased.\n");
    add_item(({"jars", "jar"}),
        "There are many different jars in many different "+
        "shapes, colours and sizes. Some are empty and some filled "+
        "with strange creams and salves.\n");
    add_item(({"empty jars", "empty jar"}),
        "There are empty jars everywhere just waiting to be filled "+
        "with some great salve or cream.\n");
    add_item(({"filled jars", "filled jar"}),
        "There are so many filled jars here that are just waiting "+
        "to be purchased.\n");
    add_item(({"wall", "walls"}),
        "The walls are a bit worn and in ruin.\n");
    add_item(({"floor", "flooring", "ground"}),
        "The floor is made of hardwood and is in badly need of repair.\n");
    add_item(({"hardwood", "wood", "board", "boards", "damaged board",
        "damaged board", "damaged wood", "damaged hardwood"}),
        "The hardwood is in much need of repair. There are long "+
        "splinters jutting upwards in places.\n");
    add_item(({"splinter", "splinter"}),
        "There are long splinters jutting upwards out of the many "+
        "damaged wood boards that make up the floor.\n");

    add_prop(ROOM_I_LIGHT, 5);
    add_prop(ROOM_I_HIDE, -1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(OBJ_I_HAS_FIRE, 1);

    add_exit(DRAKMERE_DIR + "road04", "southwest");
    add_exit(DRAKMERE_DIR + "road03", "west");
    
    reset_room();
}

public int
unq_no_move(string str)
{
    string dir = query_verb();

    write("You run smack into a wall on your hurry to leave "+ dir +
      ", nearly upsetting numerous bottles and jars.\n");
    say(QCTNAME(TP) + " runs smack into a wall as "+ HE(TP) +" attempts "+
        "to leave "+ dir +".\n");

    if (!felix)
        return 1;

    felix->command("shout Watch out you OAF!");
    felix->command("say You break it you bought it!");

    return 1;
}

int *
query_coordinates()
{
    return ({67, 5, 0});
}
