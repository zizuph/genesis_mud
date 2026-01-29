#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#define NO_OF_MATERIALS 8
#define NO_OF_SIZES     5
#define RS_MATERIAL ({"wood", "stone", "iron", "copper", "marble", "gold", "onyx", \
                      "black eog"})
#define RS_SIZE     ({"miniature", "small", "large", "huge", "gigantic"})
#define RMC_I_STATUE_MATERIAL "_rmc_i_statue_material"
#define RMC_I_STATUE_SIZE "_rmc_i_statue_size"
#define RMC_S_STATUE_POSE "_rmc_i_statue_pose"
    
string
sign()
{
    return "\n"+
        "+---------------------------------------------------------+\n"+
        "| $                                                     $ |\n"+
        "|       R I C H   M E N ' S   S T A T U E   S H O P       |\n"+
        "|                                                         |\n"+
        "| Here you can buy a statue made by the finest artists of |\n"+
        "| Genesis. These statues will be placed in this room when |\n"+
        "|  reboot, but you can get a small magical device which   |\n"+
        "| will make it possible for you to place it elsewhere in  |\n"+
        "|                        the lands.                       |\n"+
        "|                                                         |\n"+
        "|  To buy a statue - buy statue, but first you must have  |\n"+
        "|       to set the different sizes and materials by:      |\n"+
        "|       material <material>, size <size>, pose <pose>     |\n"+
        "|                                                         |\n"+
        "| To get the prize for a statue - cost <size>,<material>  |\n"+
        "|     To get the statue fetcher amulet - ask amulet       |\n"+
        "|                                                         |\n"+
        "|  Here are the sizes availible: miniature, small, large  |\n"+
        "|                    huge and gigantic.                   |\n"+
        "|  And the materials: wood, stone, iron, copper, marble,  |\n"+
        "|                 gold, onyx and black eog.               |\n"+
        "| $                                                    $  |\n"+
        "+---------------------------------------------------------+\n\n";
}

void
create_room()
{
    set_short("statue room");
    set_long(break_string(
        "You have entered a quite large room which is placed in the eastern part of "+
        "the top floor in the Rich Men's tower. Statues are lining the walls and "+
        "everything here seems made of expensive and rare materials. This is "+
        "the statue shop where the very wealthy members can buy their own "+
        "statue to make not-so-very-rich friends green with envy. The club has "+
        "hired the best of artists to sculpture it's members and only the best "+
        "is enough for the members of this distinguished club. A sign is "+
        "hanging on one of the walls.\n",60));

    INSIDE;
    LIGHT;

    add_item("sign", "@@sign");
    add_cmd_item("sign", "read", "@@sign");
}

void
init()
{
    ::init();

    add_action("statue_cost", "cost");
    add_action("statue_buy",  "buy");
    add_action("statue_size", "size");
    add_action("statue_material", "material");
    add_action("statue_pose", "pose");
}

int
statue_cost(string str)
{
    int val, i, cost;
    string *a;
    int material = -1;
    int size = -1;

    NF("Cost what? A statue? The correct syntax is 'cost size,material'.\n");

    a = explode(str, ",");

    if (sizeof(a) != 2)
        return 0;

    for (i = 0; i < NO_OF_MATERIALS; i++)
        if (a[1] == RS_MATERIAL[i])
            material = i;

    for (i = 0; i < NO_OF_SIZES; i++)
        if (a[0] == RS_SIZE[i])
            size = i;

    if (size == -1 || material == -1)
        return 0;

    cost = (100 * ((size+1) * (material+1))) * 4;

    write("The cost for "+LANG_ADDART(RS_SIZE[size])+" "+RS_MATERIAL[material]+
          " statue is "+cost+" platinum coins.\n");
    return 1;
}

int
statue_buy()
{
    object statue;
    int val, i, cost;
    string *a, shrt;
    int material;
    int size;
    string pose;
    
    FIXEUID;

/*    NF("You already got one! Try upgrade!\n");
    if ((RICHROOM)->query_statue(TP))
        return 0;*/

    NF("You haven't set how you want the statue! Use 'size', "+
       "'material' and 'pose'!\n");
    material = TP->query_prop(RMC_I_STATUE_MATERIAL) - 1;
    size = TP->query_prop(RMC_I_STATUE_SIZE) - 1;
    pose = TP->query_prop(RMC_S_STATUE_POSE);
    
    cost = (172800 * ((size + 1) * (material + 1))) * 4;
    write(can_pay(cost, TP)+"\n");

    write(CQRLNAME(TP)+" "+(cost/1728)+"\n");
/*    if (!can_pay(cost, TP))
    {
        TP->catch_msg("Ha! You don't have the money, you don't have the money!\n");
        return 1;
    }
    
    pay(cost, TP, "", 0, 0, "", 1); */
    shrt = "";
    a = TP->query_adjs();
    if (a)
    {
        for (i = 0; i < sizeof(a); i++)
            shrt = shrt + a[i] + " ";
    }
    shrt += TP->query_gender_string() + " " + TP->query_race();

    statue = clone_object(RICHCLUB + "statue");
    write(material+"\n");
    write(size+"\n");
    write(pose+"\n");
    write(shrt+"\n");
    statue->set_material(material);
    statue->set_size(size);
    statue->set_owner(TP->query_real_name());
    statue->set_desc(shrt);
    statue->set_pose(pose);
    statue->newdesc();
    statue->move(TO);
    return 1;
}

int
statue_size(string str)
{
    int val;

    switch(str)
    {
    case "miniature":
        val = 0;
        break;
    case "small":
        val = 1;
        break;
    case "large":
        val = 2;
        break;
    case "huge":
        val = 3;
        break;
    case "gigantic":
        val = 4;
        break;
    default:
        val = -1;
    }

    NF("No such size!\n");
    if (val == -1)
        return 0;

    write("You have set the size to "+RS_SIZE[val]+".\n");
    TP->add_prop(RMC_I_STATUE_SIZE, val+1);

    return 1;
}

int
statue_material(string str)
{
    int val;

    switch(str)
    {
    case "wood":
        val = 0;
        break;
    case "stone":
        val = 1;
        break;
    case "iron":
        val = 2;
        break;
    case "copper":
        val = 3;
        break;
    case "marble":
        val = 4;
        break;
    case "gold":
        val = 5;
        break;
    case "onyx":
        val = 6;
        break;
    case "black eog":
        val = 7;
        break;
    default:
        val = -1;
        break;
    }
    
    NF("No such material!\n");
    if (val == -1)
        return 0;

    write("You have set the material to "+RS_MATERIAL[val]+".\n");
    TP->add_prop(RMC_I_STATUE_MATERIAL, val+1);

    return 1;
}

int
statue_pose(string str)
{
    write("Okie. It'll be like this 'This is a statue of <your description> "+
          "showing "+str+"\nIf you're not satisfied, type it again and "+
          "remember: misuse of this will guarantee that it will be removed.\n");
    
    TP->add_prop(RMC_S_STATUE_POSE, str);
    return 1;
}
