/*
 * Fireplace for Domain Office
 * Finwe, April 2005
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

create_object()
{
    object mantel;

    setuid(); 
    seteuid(getuid());

    set_name("fireplace");
    set_short("large stone fireplace");
    set_long("This is a large stone fireplace. It is made of large river " +
        "stones and sits against a wall. It is tall and has a fire burning " +
        "continuously. The fire fills the room with a gentle yelllow glow. " +
        "The fireplace has a large brass screen in front of it to prevent " +
        "logs from rolling out and to keep sparks inside. A large stone " +
        "hearth sits in front of the fireplace.\n");
    
    add_prop(OBJ_I_HAS_FIRE,1);
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
        "The stone hearth is made of smooth stones. Its purpose is to " +
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
 
    add_prop(OBJ_I_WEIGHT, 500000);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_I_VALUE, 0);

    remove_prop(CONT_I_TRANSP);
    add_prop(OBJ_M_NO_GET, "You can't take the fireplace.\n");
    add_prop(CONT_I_ATTACH, 1);

    set_no_show_composite(1);
    
// adds the mantel to the fireplace
    mantel = clone_object("/d/Shire/common/domain_fireplace");
    mantel->set_no_show(1);
    mantel->move(TO);


}
