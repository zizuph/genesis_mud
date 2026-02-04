//-*-C++-*-
// file name:      gate_outside.c
// creator(s):     Lilith July 2008
// last update:    
//                 Lilith Jan 2022: moved connecting room out of 
//                   Sorgum's dir and into Terel/common/moor so 
//                   I'm updating the exit here.
// note: 
// bug(s):
// to-do:  

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

object door;


public void create_vamp_room()
{

    set_short("outside gate in the valley of the shadow of death");
    set_long("Just north lies the rusted old gate that guards the "+
       "mansion. Through it you can see the crumbling outline "+
       "of the ruined structure, as well as a large amount of "+
       "stone and shale debris. "+
       "Dark mountains tower above, their peaks jutting upward "+
       "like the accusing fingers of an old crone. "+
       "A foul wind gusts and blows as it slams into the cliff "+
       "face, but even it is silent in this eerie place. "+
       "South lies the tortured vineyard and the road leading "+
       "up out of the valley.\n");



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
    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "In the distance you can see some trees.\n");
    add_item(({"ground", "snow"}),
	"The ground is hard with frost and covered in snow.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads south "+
        "into the mountain.\n");
    add_item(({"vineyard", "vines"}),
        "The vines were long ago petrified into the grotesquely "+
        "tortured shapes you see now.\n");
   add_item(({"mountains", "valley"}), 
       "These mountains are dark and forbidding. They cast "+
       "shadows over most of the valley and the water that "+
       "is slowly encroaching upon it.\n");
   add_item(({"water", "dam"}),
       "Rocks and shale fallen from the mountainside have "+
       "dammed the flow of water, forming a large body "+
       "of icy water that is slowly drowning the valley.\n");
  

//    add_exit("/d/Terel/sorgum/tomb/forest07", "south"); 
    add_exit("/d/Terel/common/moor/forest/forest07", "south");   
   
    door=clone_object(OBJ_DIR +"door1");
    door->move(this_object());
    

    add_prop(ROOM_I_LIGHT,1);
    remove_prop(ROOM_I_INSIDE);
    
}


int do_up(string str)
{
    notify_fail("What?\n");
    
    if (!strlen(str))
    {
        return 0;
    }

    if (parse_command(str,({}),
        " [up] / [over] [the] [stone] 'wall' / 'fence' / 'gate'"))
    {
        if (IS_VAMP(TP) || IS_BG(TP)) 
        {
            write("You launch yourself into the air and vault easily over "+
               "the stone wall despite its imposing height.\n\n");
            TP->move_living("vaulting over the stone wall", 
            ROOM_DIR+"gate_inside");
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
    add_action(do_up, "vault");   
}