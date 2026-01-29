/*
 * Nov hut for bank
 * -- Finwe, November 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/lib/bank";

#define FIREKNIVES_MASTER "/d/Faerun/guilds/fire_knives/master/occ_fireknives_master"
#define FIREKNIVES_OBJ "/d/Faerun/guilds/fire_knives/obj/"
#define I_CAN_VISIT_MEETINGROOM     "_i_can_visit_meetingroom"
#define I_CAN_CREATE_CONTRACT       "_i_can_create_contract"


public int
block_check()
{
    if (this_player()->query_prop(I_CAN_VISIT_MEETINGROOM))
    {
       write("The guard dogs raise their heads to look at "
       +"you suspiciously, but they "
       +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until they "
            +"stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_possessive()
            +", blocking the way.\n", this_player());
            return 1;
        }
    }
      
    write("The guard dogs raise their heads to look at you, then look down "
    +"and turn around in a submissive gesture.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" receives a furtive glance from the dogs before they lower "
    +"their head and turn around in a submissive gesture.\n", this_player());
        
    return 0;
}


public int
leaving_bank()
{
    this_player()->remove_prop(I_CAN_VISIT_MEETINGROOM);
    this_player()->remove_prop(I_CAN_CREATE_CONTRACT);
        
    return 0;
}


void
create_indoor_room()
{
    object deposit = clone_object("/d/Genesis/obj/deposit");

    deposit->set_bank_id(5201, "Sword Mountains in Faerun");
    deposit->move(this_object(), 1);

    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    config_default_trade();
    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    set_bank_fee(20);

    config_trade_data();



    set_short("inside a strong hut");
    set_extraline("The hut is larger than the others and looks better "
    +"built. A single lamp hangs from the ceiling. It illuminates the many chinks "
    +"in the walls of the hut. The floor is swept clean and a fireplace sits in one "
    +"corner of the hut. A doorway is seen to the west, adjacent to resting guard "
    +"dogs. A gnome sits behind the money deposit.");

    add_item(({"walls"}),
        "They are made of wood stacked on top of each other. There are chinks in "
        +"the walls where cold air blows through. The walls look sturdy and have "
        +"some shelves against them. There is a menu on another wall. There is a doorway "
        +"into a different room to the west, guarded by guard dogs.\n");
        
    add_item(({"doorway"}),
        "The doorway to the west seems to lead into a smaller more dim room. Guard dogs "
        +"are resting next to it.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is peaked and supported by strong beams. Hanging from the beams is a single lamp.\n");
    add_item(({"beams"}),
        "They are squared logs and support the ceiling. Hanging from the beams is a single lamp.\n");
    add_item(({"logs", "squared logs"}),
        "They are large and were hauled up here from the mountains. They are square and support the ceiling.\n");

    add_item(({"lamp"}),
        "The lamp hangs from the ceiling, casting a warm glow around the room. The lamp is large and and unusually bright.\n");
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");
        
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs is resting at the western part of the room. They appear to be guarding "
    +"the entrance to the west.\n");

// fireplace
    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("fire",
        "Red and yellow flames dance across logs, filling the " +
        "room with a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly " +
        "in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against a wall and is " +
        "made from large blocks of stone. It is as tall as an " +
        "elf and burns continuously. The fire light fills the " +
        "room a gentle yellow glow and the warmth comforts " +
        "you. The fireplace has a large brass screen in front of " +
        "it to prevent logs from rolling out and to keep sparks " +
        "inside. A large stone hearth sits in front of the " +
        "fireplace.\n");
    add_item(({"screen", "brass screen", "large brass screen"}),
        "The brass screen is made up of several panels of " +
        "brass. The panels are made of woven brass wires that " +
        "have been stretched across each panel, preventing " +
        "sparks from flying out but allowing light to fill " +
        "the room.\n");
    add_item(({"hearth", "stone hearth", "large stone hearth"}),
        "The stone hearth is made of smooth stones. Its purpose " +
        "is to catch any falling items or errant sparks from " +
        "the fire. The hearth extends a little bit the width of " +
        "the fireplace. It extends out from the fireplace about " +
        "the length of a human. \n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend " +
        "the fire and stoke it when necessary. They are made of " +
        "hardened steel and include a shovel, poker, and a set " +
        "of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to " +
        "clean the fireplace out. It is about the size of a " +
        "snow shovel with a large mouth for scooping ashes and " +
        "fireplace debris.\n");
    add_item("ashes",
        "The ashes sitting closest to the hot flames are white " +
        "and turn from gray to black the further from the " +
        "flames they are.\n");
    add_item("fireplace debris",
        "Around the edges of the fire you see partially burned " +
        "twigs, sticks, and a few logs.\n");
    add_item(({"partially burned twigs", "partially burned sticks",
                "partially burned logs", "burned logs", 
                "burned twigs", "burned sticks"}),
        "They are the remains from yesterday's fire and are " +
        "scattered around the perimeter of the fire. The ends " +
        "are burned.\n");
    add_item("poker",
        "This long pole is made of hardened steel. One end has a " +
        "point and just below the point is a curved claw, " +
        "useful for poking the fire and moving logs around.\n");
    add_item("tongs",
        "This instrument is made of two arms that are joined " +
        "together by a steel pin. The ends of the tongs are " +
        "shaped like claws and are used for grasping logs and " +
        "placing them in the fire or for moving wood around " +
        "within the fireplace. They are made of hardened steel.\n");
    add_item("bellows",
        "The bellows are made of two pieces of smooth wood. " +
        "They are joined together at the front with a strip of " +
        "leather. A tube is set into the center to direct the " +
        "airflow. The sides and back of the instrument are " +
        "joined together with a large piece of tanned hide. " +
        "When pumped, the bellows blow a stream of air into " +
        "the fire, improving the draft of the fire.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_I_NO_SCRY, "You focus on finding your "
    +"target but are suddenly repelled by an aura of musky ice.\n");

    set_room_tell_time(300);
    add_room_tell("The lamp swings overhead, casting shadows around the room.");
    add_room_tell("A cold breeze blows through a chink in the walls.");

    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("A log breaks, sending a shower of sparks flying up the chimney.");
    add_room_tell("The fire flares, filling the room with a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("Shadows from the flames dance across the room.");

    add_exit(HR_DIR + "htr14", "east", leaving_bank);
    add_exit(HR_DIR + "meeting_room", "west", block_check);
    
    room_add_object(FIREKNIVES_OBJ + "donation_box");

    reset_faerun_room();
}

void
reset_faerun_room()
{
}

void
init()
{
    ::init();

    bank_init();
}

int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there yet.\n");
    return 1;
}
