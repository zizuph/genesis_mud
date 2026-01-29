/*
 * Hall of Fire
 * By Finwe, January 1998
 */
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
inherit "/d/Shire/std/room/room_tell";
 
void
create_house_room()
{
    set_short("The Hall of Fire");
    set_long("You stand in the Hall of Fire, the gathering " +
        "place for the people of Imladris. Except on high days, " +
        "it usually stands empty and quiet. People come here " +
        "who wish for peace and thought. There is always a fire " +
        "here, all year round, but there is little other light.\n");
// fireplace & fire
    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("fire",
        "Red and yellow flames dance across logs, filling the " +
        "room with a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly " +
        "in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against the north wall and is " +
        "made from large blocks of stone. It is as tall as an " +
        "elf and burns continuously. The fire light fills the " +
        "room a gentle yelllow glow and the warmth comforts " +
        "you. The fireplace has a large brass screen in front of " +
        "it to prevent logs from rolling out and to keep sparks " +
        "inside. A large stone hearth sits in front of the " +
        "fireplace and a small door is to the west of it.\n");
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
        "This long pole is made of hardened steel. One end has a" +
        " point and just below the point is a curved claw, " +
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
 
    add_item(({"wall", "walls"}),
        "The walls are decorated with great murals. No lamps or " +
        "sources of light can be found on them. \n");
    add_item("floor",
        "You see a beautiful parquet hardwood floor. The " +
        "parquetry are dark maple and form diamond patterns, " +
        "contrasting with the light oak wood of the main floor. " +
        "Around the outside of the floor, at the " +
        "base of the walls, is a border of leaves made from " +
        "various dark woods.\n");
    add_item(({"parquetry", "dark maple", "maple"}),
        "The strips of wood are made from fine maple. The " +
        "grain is beautiful and the wood has been colored a " +
        "dark colour. It stands out beautifully against the " +
        "lighter colors of oak.\n"); 
 
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("An elf stokes the fire, sending a shower " +
        "of sparks flying up the chimney.");
    add_room_tell("The fire flares, filling the room with " +
        "a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the " +
        "fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("An elf puts more wood on the fire.");
    add_room_tell("Shadows from the flames dance across the " +
        "room.");

    add_item(({"murals", "great murals", "mural", "great mural"}),
        "The murals depict different scenes of elven " +
        "merriement. Some scenes are of elves dancing, singing, " +
        "and telling tales. All the scenes take place on a wide green lawn.\n");

    add_item(({"lawn", "wide green lawn", "green lawn"}),
        "@@desc_lawn@@\n");
    add_item(({"fair elves", "noble elves", "elves"}),
        "@@fair_elves@@\n");
    add_item(({"finwe","high king"}),
        "@@descr_finwe@@\n");
    add_item(({"indis", }),
        "@@descr_indis@@\n");
    add_item(({"miriel"}),
        "@@descr_miriel@@\n");
    add_item(({"feanor", "curufinwe", "feanaro"}),
        "@@descr_feanor@@\n");
    add_item(({"fingolfin"}),
        "@@descr_fingolfin@@\n");
    add_item(({"finarfin", "finarphir"}),
        "@@descr_finarfin@@\n");
    add_item(({"miriel"}),
        "@@descr_@@\n");
    add_item(({"miriel", "miriel serinde"}),
        "@@descr_@@\n");
    add_item(({"miriel"}),
        "@@descr_@@\n");
    add_item(({"valinor", "blessed realm"}),
        "@@descr_blessed@@\n");

    add_exit(VALLEY_DIR + "d_cor03",  "south");
}

init()
{   
    ::init();
    add_action("do_stoke", "stoke");
}
 
 
int do_stoke(string str)
{
  if(!str) { NF("What do you want to stoke?"); }
  write("You stoke the fire, sending embers flying as the fire burns "+
     "brighter.\n");
  SAY(" stokes the fire sending sparks flying as the fire erupts "+
     "briefly.");
  return 1;
}

// Descriptions of various items in the mural. 
// The descriptions vary based on the race of the player. Noldor,
// will naturally see all descriptions as the mural depicts their
// homeland. Regular elves won't as they haven't been there, though 
// some players may choose to differ. So sad, to bad. ;)

string descr_finwe()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "He stands surrounded by his wives Miriel and Indis as well as his sons and daughters. His dark hair and grey eyes are truly endearing as the First High King of the Noldor and leader during the Great March.";
    else 
        return "You do not recognize him in the mural, but suppose he could be the tall elf surrounded by two beautiful beautiful elves.";
}

string descr_indis()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "As the second wife of Finwe, she is tall, flaxen haired, and bears the features her Vanyar heritage. She stands beside her two sons, Fingolfin and Finarfin.";
    else 
        return "You don't know who she is, but suppose she's probably the tall, flaxen haired queen standing beside two male elves and her kingly husband.";
}

string descr_miriel()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The first wife of Finwe, her great love for her husband is evident in her countanence. She stands beside her only son, Feanor and Finwe. Miriel is clad in a beautifully embroidered dress, displaying her skill with needlework.";
    else 
        return "You aren't sure who she could be, but she appears to be the tall queen dressed in an exquisitely embroidered dress, standing beside a tall flaxen haired son and her noble husband.";
}

string descr_feanor()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The first son of Finwe, and some say the greatest elf, Feanor stands beside his mother, Miriel. His fiery spirit is evident in the mural as he seems to be watching you. His hair is flaxen colored, an unusual trait for a son of Finwe.";
    else 
        return "The elf stands alone beside a queen and a king. He has a fiery spirit about him and seems to be watching you with a measured gaze. His hair is flaxen colored, an unusual trait for a male elf.";
}

string descr_fingolfin()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The second son of Finwe, he appears temperate and forgiving as he stands beside his mother, Indis and Finwe. His valiant and strong stature is evident in the portrait as are his dark hair and piercing gray eyes. He bears a great sword.";
    else 
        return "The valiant and strong elf stands beside his queen mother. He has dark hair and piercing gray eyes. He bears a great sword.";
}

string descr_finarfin()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The third son of Finwe, and perhaps the fairest of all his kindred, he stands beside his mother, Indis and Finwe. His wise countanence looks over the other elves in the portrait";
    else 
        return "The fairest of all the elves stands beside his queen mother and noble father. His wise countanence looks over his kindred.";
}


string fair_elves()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "They are enjoying themselves at a festival and include the royal Noldor and other elves living in Eldamar. Some of them include Finwe, the first High King of the Noldor, his wives Miriel and Indis, their sons Feanor, Fingolfin, and Finarfin, and all the Noldor royal family.";
    else if (TP->query_race() == "elf")
        return "They are beautiful people, with fair faces and dark hair. They seem to be enjoying themselves as they participate in a festival of some sort out on a green lawn.";
    else
        return "They are the most beautiful creatures ever seen. Fair faces framed by dark hair or golden hair are the prime features of the elves. They surround the city, smiling and enjoying themselves.";
}

string desc_lawn()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The green lawn is somewhere in the Blessed Realm. The grass is an emerald color and looks lush and healthy. Many of the noble elves are relaxing on the grass while others are making music and enjoying themselves.";
    else
        return "It is the most beautiful swath of emerald green grass. Countless elves are sitting on the grass, or standing and enjoying themselves. They all look very noble and fair.";
}


string descr_blessed()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The Blessed Realm, or Valinor, is depicted as full of light, beauty, and joy. The beauty and richness of the murals of the land is overwhelming, and a longing begins to swell in your heart to return to its fair shores and reside there again.";
    else 
        return "You fail to recall what that is.";
}
