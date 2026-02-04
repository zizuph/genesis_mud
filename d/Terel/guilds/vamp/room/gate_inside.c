//-*-C++-*-
// file name:      gate_inside.c
// creator(s):     Lilith July 2008
// last update:    
// note: 
// bug(s):
// to-do:  

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

object door;


public void create_vamp_room()
{

    set_short("inside gate");
    set_long("Just north of the gate that leads out into the shadowed "+
       "valley. Dark mountains tower above, their peaks jutting upward "+
       "like the accusing fingers of an old crone. Rock and shale are "+
       "scattered everywhere, dismembered parts of the mountain's face. "+
       "North lies the portico of the ancient mansion, which "+
       "appears to be crumbling and unsafe.\n");



    add_item(({"water", "lake", "pond"}), 
        "It is dark and choppy, and ringed with stones that have fallen "+
        "from the side of the mountain above it. It looks very cold, so "+
        "cold that it is unlikely anyone could survive in it for long.\n");
    add_item(({"mountain", "mountainside", "sheer walls", "avalanche", 
        "rockslide"}), 
        "The mountain appears to have lost a large portion of this side. "+
        "The area near the lake sports a sheer drop, whereas the area "+
        "near the mansion is concave and riddled with rubble and scree.\n");
    add_item(({"rubble", "rocks", "rock", "debris", "stones", "scree", "shale"}),
        "The remains of an avalanche that swept down the mountain and "+
        "devastated this holding.\n");
    add_item(({"snow", "ice"}),
        "Snow and ice are ever-present in this place. Watch your step.\n");
    add_item(({"domus", "structure", "mansion"}),
        "A two-level mud-brick and plaster structure that seems to have "+
        "been built in a time when the weather was much warmer. The high "+
        "portico looks like it once went all the way around the mansion "+
        "but most of it lies in ruins. This place does not appear to "+
        "have been maintained in a long, long time.\n");
    add_item(({"wall", "stone wall", "fence", "stone fence"}),
        "It is a very high wall, and thick, too. It encircles the mansion "+
        "protectively, like a fortification.\n");
    add_item(({"ruins", "portico", "porch"}),
        "All that remains of a colonnaded portico that once surrounded "+
        "the building and extended toward the outlying buildings is a "+
        "small area still standing at the front of the mansion.\n");
    add_item(({"door", "buried door"}),
        "The door is partly ajar, wedged open by stones that also "+
        "prevent it from being closed entirely.\n");
    add_cmd_item(({"debris", "rocks", "stones"}), ({"move", "shift"}),
        "You begin moving some rocks around but soon stop when you "+
        "realize the futility of your efforts.\n");
  

    add_exit("porch",      "north"); 
    

    door=clone_object(OBJ_DIR +"door2");
    door->move(this_object());

    add_prop(ROOM_I_LIGHT,1);
    remove_prop(ROOM_I_INSIDE);
    reset_room();
    
}


int do_up(string str)
{
    notify_fail("What?\n");
    
    if (!strlen(str))
    {
        return 0;
    }

   if (TP->is_emerald_vampire())
   {
       return 0;
   }
   if (parse_command(str,({}),
        " [up] / [over] [the] [stone] 'wall' / 'fence' / 'gate'"))
    {
        if (IS_VAMP(TP) || IS_BG(TP)) 
        {
            write("The wall is very high and prone to crumbling under your "+
               "weight, but you manage to climb over it without falling.\n\n");
            TP->move_living("over the stone wall", 
            ROOM_DIR+"gate_outside");
            return 1;
        }
        write("You try climbing over it, but you cannot seem to get "+
            "a good grip.\n");
        say(QCTNAME(TP) +" tries to climb the stone wall, but only "+
            "succeeds in scattering a bunch of gravel.\n");
        return 1;
    }
    
    return 0;
}

public void init()
{
    ::init();
    
    add_action(do_up, "up");
    add_action(do_up, "climb");
}