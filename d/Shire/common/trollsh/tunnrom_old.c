#include "../defs.h"
inherit "/d/Shire/common/lib/rom";

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

string
add_extra_noise()
{
   life = random(6);
   if(name && sizeof(name))
       remove_item(name[0]);
   name = explode(life_list[2*life+1],",");
   add_item(name, life_list[2*life+1]+"\n");
  
   switch(life)
   {
    case 0:
    return
        "A cold foul wind rushes trough the tunnels, leaving behind a smell "
        +"of reek, evil things! ";
    case 1:
    return
        "A ghastly scream echoes trough the tunnels, making your bones tremble "
        +"and shiver! ";
    case 2:
    return
        "Suddenly you hear sounds of something moving in the tunnel.... maybe it was "
        +"your footsteps that echoed through the tunnels. ";
    case 3:
    return
        "Loud strange popping noises can be heard mourning through the tunnels. ";
    case 4:
    return
        "All of a sudden rocks falling to the ground can be heard, echoing "
        +"trough the tunnel. Could it be something else that made that noise..? ";
    case 5:
    return
        "A troll suddenly raises his voice to a horrifying inferno of sound, making "
        +"the ground shake, and the walls to rumble. ";
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
    
    
    
    
    
    
    