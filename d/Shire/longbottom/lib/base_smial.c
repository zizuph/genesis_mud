/* Smial generator
 * Finwe, January 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

static int     roomtype;    /* 1=Front Hall 2=Parlor 3=Dining Room 4=Kitchen
			                 * 5=Master Bed Room 6=Bed Room 7=Storage Room
			                 * 8=Corridor 9=Cellar 10=Pantry */

static string  smialsize,   /* eg "small", "large"*/
               areaname,    /* eg "Mithlond", "Michel Delving", */
			                /*"Hobbiton", "Bree" */
               areatype,    /* eg "hamlet", "village", "town", "city" */
               land,        /* "the Shire" */
               extraline;   /* additional room description */

void create_smial() {}

string
short_func()
{
    switch(roomtype)
    {
        case 1: // front hall
            return "A front hall";
        case 2: // parlor
            return "A parlor";
        case 3: // dining room
            return "A dining room";
        case 4: // kitchen
            return "A kitchen";
        case 5: // master bedroom
            return "A master bedroom";
        case 6: // bedroom
            return "A small bedroom";
        case 7: // storage room
            return "A storage room";
        case 8: // corridor
            return "A corridor";
        case 9: // cellar
            return "A cellar";
        case 10:// pantry
            return "A pantry";
   }
}

void
create_shire_room()
{
    set_short("@@short_func@@");
    set_long("@@long_descr@@");

    add_prop(ROOM_I_INSIDE,1);
    create_smial();
}

string
long_descr()
{
    string long_descf = short_func();
    string room_descr = "";
    switch(roomtype)
    {
        case 1: // front hall
            room_descr = "You are standing in the front hall of this " + smialsize
            + " smial in the " + areatype + " of " + areaname + " in " + land 
            + ". There is a round wooden door leading out of the smial.";
            break;
        case 2: // parlor
            room_descr = "This is a " + smialsize + " parlor. There " +
            "are several comfortable looking chairs and sofas here. A " +
            "large fireplace, set into one of the walls, heats and fills " +
            "the room with a soft glow.";
            break;
        case 3: // dining room
            room_descr = "This is without a doubt the most popular " +
            "room in this smial -- it is the dining room. A large table " +
            "dominates the room and can seat many hobbits. Surrounding " +
            "the table are a number of chairs and benches.";
            break;
        case 4: // kitchen
            room_descr = "This is one of the largest rooms in this " + 
            smialsize + " smial -- the kitchen. Cupboards and shelves " +
            "line the walls, as well as cooking utensils hanging from " +
            "the roof and a large stove.";
            break;
        case 5: // master bedroom
            room_descr = "This is the master bedroom of the smial. It " +
                "is larger than the other rooms in the smial. A huge " +
                "bed sits against a wall. A dresser sits " +
                "across from it, some cupboards hang on a wall, and " +
                "a rug covers the floor.";
            break;
        case 6: // bedroom
            room_descr = "This is a small bedroom. It is sparsely " +
            "furnished with nothing more than a bed, a chest of drawers, " +
            "and a rug on the floor.";
            break;
        case 7: // storage room
            room_descr = "This is a small storage room. Shelves line " +
            "the walls and are used to store items. The room is cramped, " +
            "so probably not a lot of stuff is kept here.";
            break;
        case 8: // corridor
            room_descr = "This is a tube-shaped hall, with paneled " +
            "walls, and floors covered in carpet.";
            break;
        case 9: // cellar
            room_descr = "This room serves as a cellar. It is cool " +
            "and dry, and fitted with a number of wine-racks and shelves.";
            break;
        case 10:// pantry
            room_descr = "One of the larger rooms in this smial, " +
            "this is a pantry. It has shelves fitted to the walls to " +
            "store all sorts of food. All through this room a faint " +
            "smell of apples permeates the air.";
            break;
    }

//    if (extraline)
        long_descf = room_descr + " " + extraline + "\n";
//    else
//        long_descf = room_descr + " " + extraline + "\n";
   return (long_descf);
 }


/*****************************************************************************/

void set_wood_panel()
{
    add_item(({"panel", "wood panel", "wood panels", "panels"}),
        "They are polished to a dark color and cover the walls and ceiling.\n");
}

void set_add_door(string color)
{
    add_item(({"door", "round door", "large round door", "large door"}),
        "The door is round and made of wood. It is painted " + color +
        " and leads outside. There is a little window set into the door, " +
        "that lets you look outside. A brass doorknob is set in the center " +
        "of the door.\n");
    add_item("window",
        "This quaint little window is round, as you would expect, with " +
        "glass panels set in a lead border. The frame is painted bright " +
        "white, and the window is kept clean. You could look outside " +
        "through this window if you wanted to.\n");
    add_item("outside",
        "Looking through the window, you can see the " + areatype +
        " of " + areaname + ".\n");
    add_item(({"hooks", "coat hook", "hook", "coat hooks"}),
        "They are 'U' shaped and made of brass. Each hook is attached " +
        "to a wall and designed to hold coats and other outerwear.\n");
    add_item(({"doorknob", "knob", "brass doorknob", "door knob", "brass door knob"}),
        "It is a handle set in the middle of the round door. The doorknob " +
        "is made of brass and smooth from constant use.\n");
}

void set_add_walls()
{
    add_item(({"walls"}),
        "The walls are round and covered in dark, wood panel. Lamps are " +
        "attached to the walls.\n");
    add_item(({"lamps"}),
        "They are made of brass and are attached to the walls. The provide " +
        "light to the area.\n");
}

void set_add_ceiling()
{
    add_item(({"ceiling", "up"}),
        "The ceiling is round and paneled with dark wood.\n");
}

void set_add_floor_plain()
{
    add_item(({"floor", "down", "ground"}),
        "The floor is covered with wood planks. It is honey colored and clean. \n");
    add_item(({"wood planks", "planks"}),
        "They are irregular sized and make up the floor. The planks are " +
        "a honey color and polished smooth.\n");
}

void set_add_floor_rug()
{
    add_item(({"floor", "down", "ground"}),
        "The floor is covered with wood planks. It is honey colored and clean. \n");
    add_item(({"wood planks", "planks"}),
        "They are irregular sized and make up the floor. The planks are " +
        "a honey color and polished smooth. A rug covers the floor\n");
    add_item(({"rug"}),
        "It is oval in shape and woven quite colorful. The rug fills " +
        "the room.\n");
}

// 1 - Front Hall
void set_add_front_hall()
{

}
// 2 - Parlor
void set_add_parlor()
{
    add_item(({"chairs","chair","comfortable chair"}),
       "Hobbits are well known for their love of comforts. "
        + "This is obvious, looking at these chairs. They are well used " +
        "and worn in several places.\n");
    add_item(({"sofa","sofa","comfortable sofa"}),
       "These sofas look as comfortable as the chairs. "
        + "They are well padded, and would be nice to "
        + "lie down on.\n");
    add_item("fireplace","This large fireplace, set into the wall, "
        + "can heat up the entire room nicely. The fireplace is "
        + "not lit, as no fire has been set.\n");
}

// 3 - Dining Room
void set_add_dining_room()
{
    add_item(({"table","dining table"}),
       "This dining table has been lovingly cared for, and has "
        + "been much polished, until its oaken surface shines "
        + "with a soft glow.\n");
    add_item(({"chairs","chair","comfortable chair"}),
       "Hobbits are well known for their love of comforts. "
        + "This is obvious, looking at these chairs that are just "
        + "begging out for you to sit upon, ready to eat.\n");
}

// 4 - Kitchen
void set_add_kitchen()
{
    add_item(({"utensils","cooking utensils"}),
       "These cooking utensils hang from the roof of this "
        + "smial, ready for use in making delicious meals.\n");
    add_item("stove",
       "This large stove looks like it can cook a huge meal, and "
        + "guessing from the soot around it, it obviously has cooked "
        + "many meals.\n");
    add_item(({"cupboard","cupboards"}),
       "These cupboards contain pots and pans and other "
        + "implements used in cooking the many meals that "
        + "hobbits are prone to eat.\n");

}

// 5 - Master Bedroom
void set_add_master()
{
    add_item("bed",
       "This huge bed would easily fit a couple of hobbits. "
        + "It looks soft and comfortable and inviting, ready "
        + "to be slept in.\n");
    add_item(({"cupboards","cupboard"}),
       "The cupboards in this room presumably hold clothes "
        + "and other such items. However, they are firmly "
        + "locked, and look too strong to break into.\n");
    add_item(({"dresser","dressers"}),
       "Like the cupboards, these dressers hold clothes and "
        + "similar items. Like the cupboards, the dressers are "
        + "firmly locked.\n");

}

// 6 - Bedroom
void set_add_bedroom()
{
    add_item("bed",
       "This small bed looks just right for a hobbit to use. "
        + "It looks soft and comfortable and inviting, ready "
        + "to be slept in.\n");
    add_item("dresser",
       "This dresser is used to hold clothes for visiting "
        + "hobbits. At the moment, it seems to be empty.\n");
}

// 7- Storage Room
void set_add_storage()
{
    add_item(({"shelf","shelves"}),
       "The shelves in this storage room are currently "
        + "empty, although they look like they can store "
        + "a lot of goods.\n");

}

// 8 - Corridor
void set_add_corridor()
{

}
// 9 - Cellar
void set_add_cellar()
{

    add_item( ({"shelf", "shelves", "shelfs"}), "@@exa_shelf@@");
    add_item( ({"jar", "jars", "vegetable", "vegetables", "pickles", "pickled vegetables"}),
        "The jars vary in size from single portions to huge jugs. They "
        + "contain carrots, cucumbers, cabbages, onions, asparagus, beets, "
        + "and even peppers, all sitting in salt brine, pickling for the "
        + "winter.\n");
    add_item( ({"tool", "tools", "odd tool"}), "You see hammers and "
        + "crowbars, and a small knife.\n");
    add_item(({"hammers", "hammer"}),
        "These are tools with a heavy metal head attached to wooden " +
        "handles. They lay scattered around on the shelves.\n");
    add_item(({"crowbar", "crowbars"}),
        "They are small metal bars each with a flattened end. The crowbars are " +
        "used to open containers.\n");
    add_item(({"knife", "knives", "knifes"}),
        "They are sharpened blades attached to wooden handles, and used " +
        "to cut food. \n");
    add_item( ({"pot", "pots", "pan", "pans", "pots and pans"}),
        "These pots and pans are made of cast iron. They look rusty and "
        + "dusty here in the basement. The cast iron needs a good "
        + "seasoning.\n");
    add_cmd_item( ({"iron", "cast iron", "pot", "pots", "pan", "pans", "pots and pans"}),
        "season", "In order to season the cast iron you'd need a hot stove, "
        + "or better yet an oven, some fat like lard, and some hot soapy "
        + "water. First you'd need to clean the cast iron. Then you'd need "
        + "to heat it. Once it was hot--but not too hot--you'd need to wipe "
        + "the fat inside and let it cook gently for an hour or so. After that, "
        + "the cast iron would be ready to use!\n\nBut you don't have any "
        + "of those things, do you?\n");
    add_item( ({"rack", "racks", "wine", "wine rack", "wine racks", "wine-racks"}),
        "The racks are filled old dusty bottles of wine. The racks are " +
        "made of wood and look well used.\n");	
}

// 10 - Pantry
void set_add_pantry()
{
    add_item("shelves",
       "The shelves in this pantry have the remnants of food "
        + "in them - old flour, moldy apples...\n");

}