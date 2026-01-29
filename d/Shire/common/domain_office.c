#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <language.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Genesis/start/human/town/tower.h"

inherit TOWER_OFFICE;
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define SOFA_CHAIR      "overstuffed beige sofa"
#define COUCH_CHAIR     "large beige couch"
#define NO_FIGHT_MSG    "This is a room is for learning and contemplation, not fighting.\n"

public string	look_at(string arg);    /* VBFC for chairs */
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);    /* VBFC for chairs */

object mirror, compartment, mantle;
int alarm_id;

void
create_tower_office()
{
    object mantle;

    set_short("Shire domain office");
    set_long("This is an office set up by a hobbit. It is unusually " +
        "spacious and neat. The floors are clean, and papers are neatly " +
        "stacked on a bookshelf and desk in the office. Windows are set " +
        "into the walls, which fill the room with fresh air. A fireplace " +
        "sits in a corner and provides warmth and light. A large sofa " +
        "and couch are set in the office. A scroll hangs on the wall.\n");

// chair functions
    add_chair(SOFA_CHAIR,
        "[down] [on] / [in] [the] [overstuffed] [beige] 'sofa'", 5);
    add_item( ({ "sofa"}), &look_at(SOFA_CHAIR) );

    add_chair(COUCH_CHAIR,
        "[down] [on] / [in] [the] [large] [beige] 'couch'", 5);
    add_item( ({ "couch", }), &look_at(COUCH_CHAIR) );

// fireplace add_items
add_prop(OBJ_I_HAS_FIRE,1);

    room_add_object("/d/Shire/common/dom_office/domain_mantel");
    add_item(({"windows", "window"}),
        "They are long and set into the walls. They are open, and look out " +
        "over Sparkle.\n");
    add_item(({"sparkle", "sparkle"}),
        "Looking through the window, the village of Sparkle surrounds " +
        "the tower. There is just so much to see that it can't all be " +
        "taken in from this view.\n");
    add_item(({"walls"}),
        "They are smooth and tall with windows are set into them. A banner " +
        "hangs on one wall, and a sign on another.\n");
    add_item(({"floor"}),
        "It is smooth and clean. A plush rug covers the floor.\n");
    add_item(({"rug", "carpet"}),
        "The rug is thick and fills the room. It is a deep brown " +
        "brown color. It is decorated with patterns of green leaves, " +
        "and resembles a forest floor.\n");
    add_item(({"leaves", "green leaves", "patterns of green leaves", 
            "leaf", "green leaf", "pattern of green leaf"}),
        "They are patterns of leaves and are all sizes. They are scattered " +
        "across the the rug and look like the forest floor. They are " +
        "shades of green and look real. \n");
    add_item(({"rocks", "stones"}),
        "There are several types of rock in the office. You see granite " +
        "making up the mantle, large river rocks for the fireplace, " +
        "and smooth stones for the hearth.\n");
    add_item(({"granite"}),
        "The granite is a single piece of stone that was cut into a long " +
        "rectangular block. It sits above the fireplace as the mantle. " +
        "It is white and polished smooth.\n");
    add_item(({"slate stones", "slate"}),
        "These are square pieces of black stone. They are set into " +
        "the ground and make up the hearth in front of the fireplace.\n");
    add_item(({"river stones", "river stone"}),
        "They are all shapes, sizes, and are large. They were smoothed " +
        "and rounded by the forces of rivers and have no sharp edges. " +
        "They are stacked on top of each other and make up the fireplace.\n");
    
    add_item(({"fireplace", "large fireplace", "large stone fireplace"}),
        "It is a large stone fireplace. It is made of large river " +
        "stones and sits against a wall. It is tall and has a fire burning " +
        "continuously. The fire fills the room with a gentle yelllow glow. " +
        "The fireplace has a large brass screen in front of it to prevent " +
        "logs from rolling out and to keep sparks inside. A large stone " +
        "hearth sits in front of the fireplace.\n");
    add_item("fire",
        "Red and yellow flames dance across logs, filling the room with " +
        "a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly in the fire.\n");
    add_item(({"screen", "brass screen", "large brass screen"}),
        "The brass screen is made up of several panels of brass. Each " +
        "panel is made of woven brass wires that have been stretched " +
        "across a metal frame to and connected. They prevent sparks " +
        "from flying out but allowing light to fill the room.\n");
    add_item(({"hearth", "stone hearth", "large stone hearth"}),
        "The stone hearth is made of slate. They protect the floor and " +
        "catch any falling items or errant sparks from the fire. The " +
        "hearth extends a little bit on either side of the fireplace and " +
        "out away from the front of it, too.\n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend the fire " +
        "and stoke it when necessary. They are made of hardened steel and " +
        "include a shovel, poker, and a set of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to clean the " +
        "fireplace out. It is about the size of a snow shovel with a " +
        "large mouth for scooping ashes and fireplace debris.\n");
    add_item("ashes",
        "The ashes sitting closest to the hot flames are white. They turn " +
        "from gray to black the further from the flames they are.\n");
    add_item(({"fireplace debris", "debris"}),
        "Around the edges of the fire you see partially burned twigs, sticks, " +
        "and a few logs.\n");
    add_item(({"partially burned twigs", "partially burned sticks",
            "partially burned logs", "burned logs", "burned twigs",
            "burned sticks"}),
        "They are the remains from yesterday's fire and are scattered " +
        "around the perimeter of the fire. The ends are burned.\n");
    add_item("poker",
        "This long pole is made of hardened steel. One end has a  point " +
        "and just below the point is a curved claw, useful for poking " +
        "the fire and moving logs around.\n");
    add_item("tongs",
        "This instrument is made of two arms that are joined together by " +
        "a steel pin. The ends of the tongs are shaped like claws and are " +
        "used for grasping logs and placing them in the fire or for moving " +
        "wood around within the fireplace. They are made of hardened steel.\n");
    add_item("bellows",
        "The bellows are made of two pieces of smooth wood. They are " +
        "joined together at the front with a strip of leather. A tube is " +
        "set into the center to direct the airflow. The sides and back of " +
        "the instrument are joined together with a large piece of tanned " +
        "hide. When pumped, the bellows blow a stream of air into the " +
        "fire, improving the draft of the fire.\n");

    add_item("banner",
        "It is woven of fine threads and hangs above the door. It is long " +
        "and appears folded inward at either end. Words are woven into " +
        "the banner and can be read.\n");
    add_item(({"words"}),
        "There are words woven into both the banner above the door and " +
        "written on the scroll. You may either read the banner or the " +
        "scroll to learn what they say.\n");
    add_item(({"letters", "fine letters"}),
        "They are written onto the scroll by a stead hand and can be read.\n");
    add_item(({"scroll"}),
        "It is long and made of parchmant. It hangs on the wall and looks " +
        "well read. Fine letters are written on the scroll and look like " +
        "they were done by one with a steady hand.\n");
    add_item(({"threads", "fine threads"}),
        "The threads are woven into the banner above the door. Each thread " +
        "looks smooth and expertly made. Some are woven into words.\n");
    add_item(({"desk"}),
        "It is large and rectangular, and holds some drawers. Some quills " +
        "and inkwells are scattered acrossed it along with some neatly " +
        "stacked papers. The desk sits in the center of the room.\n");
    add_item(({"quills"}),
        "These are feathers whose tips have been shaped and hollowed " +
        "out. They are dipped in an inkpot and used to write with.\n");
    add_item(({"feathers"}),
        "They are made from white feathers and neatly trimmed. Their " +
        "tips have been shaped and hollowed out.\n");
    add_item(({"white feathers"}),
        "They are from the wings of white birds.\n");
    add_item(({"inkwell", "inkwells"}),
        "It is a small, round reservoir used to hold ink. The bottom is " +
        "large and flat. A holder extends out from the base.\n");
    add_item(({"holder"}),
        "It is a hollow and extends upwards from the base of the inkwell. " +
        "It is designed to hold quills that have been used.\n");
    add_item(({"papers", "paper", "documents", "document"}),
        "They are stacked neatly on the desk and shelves. Flowing characters " +
        "are written on them. It appears they are notes about the projects " +
        "and wizards in the Shire.\n");
    add_item(({"characters", "flowing characters", "flowing character", "character"}),
        "They are written on the documents. They were written by someone " +
        "with a steady hand with dark ink.\n");
    add_item(({"ink", "dark ink", "black ink"}),
        "It is a black fluid used to write on the papers and documents " +
        "with quills. It is stored in inkwells on the desk.\n");
    add_item(({"bookshelf"}),
        "It is sturdy and tall, and set against the wall. The bookshelf " +
        "holds neatly stacked papers and books.\n");
    add_item(({"knick-knacks", "knick-knack", "knick knack", "knick knacks"}),
        "They are items gathered from different places in the Shire. They " +
        "are scattered across the mantle.\n");
    add_item(({"books"}),
        "They are well used and different sizes. The books are stacked " +
        "in the bookshelf.\n");

    add_cmd_item("banner","read","@@my_banner@@");
    add_cmd_item("scroll","read","@@my_scroll@@");

    set_project_path("/d/Shire/open/projects/");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK,1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");

    add_tower_link("tower");

    reset_room();
}


void
init()
{
    ::init();
    init_room_chairs(); /* add chair verbs */
}


public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);

}


/*
 * Function name:   look_at
 * Description  :   VBFC to describe chair/sofa + occupants
 * Arguments    :   string arg -- what's being looked at
 *                  null str -> it's the room
 * Returns      :    string -- the description
 */
public string
look_at(string arg)
{
    switch ( arg )
    {

    case SOFA_CHAIR:
       return "The sofa is overstuffed and very inviting. It is covered " +
       "with supple beige leather, and looks sturdy enough to hold several " +
       "people with ease.\n"+
    sitting_on_chair(SOFA_CHAIR, this_player(), 0);
    break;

    case COUCH_CHAIR:
       return "The couch is plush and very inviting. It is covered " +
       "with supple beige leather and can support hold several people " +
       "with plenty of room left over.\n"+
    sitting_on_chair(COUCH_CHAIR, this_player(), 0);
    break;


    }
}

string
my_banner()
{
    return "\n\n"+
      "\t           __________________________________________\n" +
      "\t          |                                          |\n" +
      "\t          |   S H I R E   D O M A I N  O F F I C E   |\n" +
      "\t          |                                          |\n" +
      "\t          | You have the following two commands      |\n" +
      "\t          | available in this office.                |\n" +
      "\t          |                                          |\n" +
      "\t _________| wizards - Lists the wizards of the Shire |_______\n" +
      "\t|         | projects <shire/wizards> - The projects  |       |\n" +
      "\t|         | of either the Shire or of its wizards.   |       |\n" +
      "\t|         |__________________________________________|       |\n" +
      "\t|           \\#####|                          |#####/         |\n" +
      "\t|            \\####|                          |####/          |\n" +
      "\t|             \\###|                          |###/           |\n" +
      "\t|              \\##|                          |##/            |\n" +
      "\t|               \\#|                          |#/             |\n" +
      "\t|________________\\|                          |/______________|\n\n\n";
}

string
my_scroll()
{
    return "\n\n"+

"       .-----------------------------------------------------------------.\n" +
"      /  .-.                                                         .-.  \\\n" +
"     |  /   \\           T H E   S H I R E   D O M A I N             /   \\  |\n" +
"     | |\\_.  |                                                     |    /| |\n" +
"     |\\|  | /|   The Shire is the home of hobbits, elves, humans   |\\  | |/|\n" +
"     | `---' |   orcs, trolls, and things unspeakable. The borders | `---' |\n" +
"     |       |   range from Moria in the south to the Grey Moun-   |       |\n" +
"     |       |   tains of the north and beyond. The Shire also     |       |\n" +
"     |       |   stretches from the Grey Havens in the west and    |       |\n" +
"     |       |   over the Misty Mountains to the east. We also     |       |\n" +
"     |       |   encompass Mirkwood, the Lonely Mountain and the   |       |\n" +
"     |       |   old Rhovanion domain.                             |       |\n" +
"     |       |                                                     |       |\n" +
"     |       |   Presently, we are updating the domain and devel-  |       |\n" +
"     |       |   oping new and exciting things and places for      |       |\n" +
"     |       |   mortals to enjoy. But, as always, we are open to  |       |\n" +
"     |       |   new ideas and suggestions to make the domain more |       |\n" +
"     |       |   enjoyable for players. Our goal is to provide a   |       |\n" +
"     |       |   place where all levels of players can come, from  |       |\n" +
"     |       |   the smallest newbie to the largest hero.          |       |\n" +
"     |       |                                                     |       |\n" +
"     |       |   Like the Gondor domain, the Shire is based on     |       |\n" +
"     |       |   Tolkien's rich books. They provide places with    |       |\n" +
"     |       |   little characterization and hints of much more.   |       |\n" +
"     |       |   If you are interested in adding to the rich       |       |\n" +
"     |       |   environment of the Shire, contact the liege       |       |\n" +
"     |       |   of Gondor.                                        |       |\n" +
"     |       |                                                     |       |\n" +
"     |       |-----------------------------------------------------|       |\n" +
"     \\       |                                                     |       /\n" +
"      \\     /                                                       \\     /\n" +
"       `---'                                                         `---'\n\n";
}

void reset_room()
{
    object quest_orb;
    
    mantle->add_stuff();

    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Shire");
        quest_orb->set_extra_line("The dark crystal orb is floating"
          + " before you, seemingly on the wind.");
        quest_orb->move(this_object(), 1);
    }        
}
