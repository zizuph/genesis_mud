#include "../defs.h"
inherit "/d/Shire/common/lib/rom";
inherit "/d/Shire/std/room/room_tell";


static int life;
string *life_list;

create_rom()
{
    add_item(({"tunnel","tunnels"}),
        "The tunnel is very dark, as there is no light sources down here. "
       +"It has soft walls, consisting of almost only pure soil. Water is "
       +"trickeling down the walls making the air very moisty. It is a "
       +"nasty, reek smell in here, as it must be a place where evil has "
       +"dwelled for a long time.\n");

    set_room_tell_time(random(30)+120);
    add_room_tell("A blast of dank, evil-smelling wind blows " +
        "through the tunnels.");
    add_room_tell("The faint sounds of loud fighting can be heard in the distance.");
    add_room_tell("A large, black rat darts past you.");
    add_room_tell("Something drips on your shoulder.");
    add_room_tell("A sickly smell drifts past you.");
    life_list =
    ({
        "wind",
            "The wind has a evil smell, yet it cannot be touched.",
        "scream",
            "The scream came from within the tunnels.",
        "sounds",
            "It is difficult to know what the sound came from. Maybe it came "
            +"from yourself..",
        "noises",
            "It is hard to know what this noise is, but yet it is horrifying, "
            +"tearing deep into your bones!",
        "rock,falling",
            "It sounded like a rock, but could be something else that fell to the ground...",
        "troll, noise, inferno",
            "The scream from the troll can be heard throughout the tunnels, making your "
            +"entire soul tremble in fear. Only a troll can scream that horrifying."
    });

    TO->create_tunnrom();

}

reset_rom()
{
    TO->reset_tunnrom();
}

static string *name;
/*
 *Room-tells dependent of trolls in the tunnels
 */


string
add_extra_noise()
{
   life = random(5);
   if(name && sizeof(name))
       remove_item(name[0]);
   name = explode(life_list[2*life+1],",");
   add_item(name, life_list[2*life+1]+"\n");
  
   switch(life)
   {
    case 0:
    return
        "A ghastly scream fills the tunnels as it echoes off the walls.\n";
    case 1:
    return
        "Suddenly, sounds of something moving in the tunnel echo around you. Maybe it was your footsteps that echoed through the tunnels, or maybe not.\n";
    case 2:
    return
        "Loud strange popping noises can be heard mourning through the tunnels.\n";
    case 3:
    return
        "Angry grunting and fighting from trolls echo around you.\n";
    case 4:
    return
        "A troll suddenly raises his voice to a horrifying inferno of sound, making "
        +"the ground shake, and the walls to rumble.\n";
    }

}    
    
string
query_extra()
{
    string extra;
    extra = "";
    if (random(3)==2)
        extra += add_extra_noise();
    return extra;
}
    
    
    
    
    
    
    