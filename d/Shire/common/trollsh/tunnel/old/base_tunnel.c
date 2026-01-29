/*
 * This is the base room for the tunnels in the Trollshaws
 * --Finwe, August 2001
 * Thanks to Tomas for the sconce idea and using his code.
 * -- Finwe, September 2001
 *  
 */
 
inherit "/d/Shire/std/room.c";
inherit "/d/Shire/std/room/room_tell";
//inherit AREA_ROOM;

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

//#define max_trolls = random(4);
int max_trolls = random(2);

int num_trolls, alarm_id;
object leader, *trolls = ({});

void
make_trolls();

void
reset_room()
{
  make_trolls();
}


int ext_sconce = 1; // rooms start out dark, but pitch can be lit

static string add_bones = "",
              add_slimy_walls = "",
              add_water_pools = "",
              add_guardroom_dirty = "",
              add_guard_room_clean = "";

void
create_tunnel_room()
{
}
 
public void
//create_shire_room()

create_room()
{
    set_long("@@tunnel_desc3@@");
    set_short("A dark tunnel beneath the Trollshaws");
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy. 

    create_tunnel_room();
    add_item(({"wall", "walls"}),
        "The walls are rough and have odd shaped grooves, " +
        "almost like the tunnel was carved by crude tools. They " +
        "curve upwards and meet together, forming an uneven ceiling.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling is uneven with many deep grooves, like it " +
        "was carved out of stone with crude tools. Black circles " +
        "hang directly over the torches where soot has accumulated " +
        "for long years.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is uneven. Grooves mark where crude tools " +
        "were used to dig the tunnel. Oddly enough, the floor " +
        "is unusually smooth.\n");
    add_item("water",
        "The water looks brackish and sickly. It drips from " +
        "various places in the tunnels and doesn't look good to " +
        "drink.\n");
    add_item(({"pools of water", "pool of water", "pools", "pool",
            "puddle of water", "puddles of water", "puddle", "puddles",
            "wet spots", "wet spot"}),
        "The pools of water are scattered throughout the tunnels. " +
        "Some large enough to be called puddles while others are " +
        "nothing more than wet spots on the ground. There aren't " +
        "many of them, just enough to be a nusiance. The pools " +
        "look unhealthy from countless feet that splash in them.\n");

    add_item(({"pitch","iron sconce","sconce"}),"@@sconce@@");

    add_cmd_item(({"sconce","pitch"}),
                 ({"get","take"}),
                   "You cant remove the sconce or the pitch.\n");

    add_cmd_item(({"pitch","sconce"}),
                 ({"extinguish"}),
                   "@@extinguish@@");

    add_cmd_item(({"pitch","sconce"}),
                 ({"light"}),
                   "@@light_sconce@@");


/*
 * room starts dark. let mortals discover they can light the
 * pots of pitch in the sconces.
 */
    add_prop(ROOM_I_LIGHT, -1);    

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A dripping sound echoes in the distance.");
    add_room_tell("A large rat scampers past you.");
    add_room_tell("Some odd sounds echo in the distance.");
    add_room_tell("Something rancid smelling drifts past you.");
    add_room_tell("Water drips on you from above.");
    add_room_tell("A bloodcurdling scream echoes from somewhere " +
        "in the distance.");
    // roomtells based on whether room is lit or dark
    add_room_tell("@@dynamic_room_tell@@");



}

/*
 * torches and sconce routines
 */
 
string
sconce()
{
   if (ext_sconce == 1)
   {
     return "An iron sconce can be seen attached to the rock wall. " +
            "A chain dangling from the sconce holds a large " +
            "pot containing pitch.\n";
   }
     return "An iron sconce can be seen attached to the rock wall. " +
            "A chain dangling from the sconce holds a large " +
            "pot containing burning pitch, which provides " +
            "light to the tunnel.\n";
}
     

public int
extinguish()      // Extinguish the sconce.
{
    switch(ext_sconce)
    {
        case 1:
        write("The pot of pitch isn't lit.\n");
        break;

        case 0:
        ext_sconce = 1;  // Extinguish the wall sconce.
        write("Using the iron lid, you snuff out the burning " +
         "pitch within the wall sconce.\n");
        say(QCTNAME(TP) + " snuffs out the burning pitch by closing " +
         "the iron lid on the wall sconce.\n");
        add_prop(ROOM_I_LIGHT, -1);   // add darkness to the room.
        break;
    }
    return 1;
}


public int
light_sconce()        // Light the sconce
{
    switch(ext_sconce)
    {
        case 0:
        write("The pot of pitch is already lit.\n");
        break;

        case 1:
        write("You light the pot of pitch in the wall sconce.\n");
        say(QCTNAME(TP) + " lights the wall sconce.\n");
        add_prop(ROOM_I_LIGHT, 1);  // Add light to the room.
        ext_sconce = 0;    // add light to the room.
        break;
    }
    return 1;
}


/*
 * Tunnel descriptions
 */
 
string tunnel_desc1()
{
    return "You stand in a tunnel beneath the Trollshaws. " +
    "It has been roughly carved leaving the walls rough looking " +
    "and grooved. The darkness is suffocating and absorbs almost " +
    "all the light. A feeling of uneasiness seems to pervade the area. ";
}

string tunnel_desc2()
{
    return "This is a tunnel deep in the Trollshaws. The rough " +
    "walls are evidence that the tunnel was carved by orcs or " +
    "trolls or even their slaves. There are deep grooves in the " +
    "wall, probably from the crude tools used to carve out the " +
    "tunnel. The darkness is thick, almost clammy as it absorbs " +
    "light and and muffles sounds. ";
}

string tunnel_desc3()
{
    return "Deep gashes in the walls, ceiling, and floor show that " +
    "this tunnel was carved ages ago by the trolls, or by their slaves. ";
}

string tunnel_desc4()
{
    return "A dark and forboding tunnel inside the Trollshaws. " +
    "Darkness seems to blanket everything here, " +
    "smothering out all light. Gashes in the wall are evidence " +
    "that terrible creatures may have once inhabited these " +
    "tunnels. ";
}


string tunnel_desc5()
{
    return "Deep beneath the Trollshaws, sounds echo around. " +
    "Some are deep throated grunts, howls, and scampering. The " +
    "darkness seems to amplify the sounds, making them seem " +
    "louder and closer than they really are. ";
}

string tunnel_desc6()
{
    return "Somewhere under the Trollshaws. The air is unusually " +
    "moist, probably from the dripping water that seems to seep " +
    "in from above. A rancid smell fills the area. All seems " +
    "unusually quiet, as waiting for something to happen. ";
}

string gr_desc1()
{
    return "This is a dirty guard room. Piles of garbage and " +
    "trash are scattered about the room showing this is a busy " +
    "place. The tunnel is collapsed, yet remains unrepaired. ";
}

string gr_desc2()
{
    return "You stand inside a dirty guard room. The piles of " +
    "garbage and trash show that trolls visit here often. ";
}

string gr_desc3()
{
    return "The garbage and filth show this to be a very active " +
    "guardroom. The garbage is piled high and smells strong.  ";
}


string gr_desc4()
{
    return "You stand in a guardroom that is relatively clean. " +
    "There are still piles of garbage, but it looks like there " +
    "has been little activity. The tunnel is cramped and makes " +
    "things uncomfortable. ";
}

string gr_desc5()
{
    return "Somewere deep in a troll guardroom. The room looks " +
    "abandoned though there are still piles of garbage lying " +
    "around. The tunnel seems cramped and dark even with the light. ";
}

string gr_desc6()
{
    return "This is an unused guardroom somwhere in the Trollshaws. " +
    "It looks relatively clean, considering trolls once used the "  +
    "room. Still, there are piles of garbage on the floor and the " +
    "room seems generally deserted. ";
}


/*
 * Function name : set_add_bones
 * Description   : describes bones found in the tunnels
 */
void set_add_bones()
{
    add_item(({"bones", "broken bones", "gnawed bones"}),
        "The bones are scattered about the tunnel. Some are " +
        "broken and splintered while others are whole. They appear " +
        "to be the bones from unlucky prisoners of the trolls, " +
        "or maybe even the trolls themselves.\n");
}

/*
 * Function name : set_add_slimy_walls
 * Description   : describes the slime on the walls
 */
void set_add_slimy_walls()
{
    add_item(({"slimy wall", "slimy walls"}),
        "The walls are covered with patches of slime. The slime " +
        "has grown on the walls where water constantly drips and " +
        "runs down the walls. It is moist to the touch, and slick.\n");
    add_item("slime",
        "The slime grows on the moist walls. It is dark colors " +
        "and and grows in patches.\n");

}

/*
 * Function name : set_add_guardroom_clean
 * Description   : describes how clean a guard room is
 */
void set_add_guardroom_clean()
{
    add_item(({"garbage", "trash", "litter"}),
        "The garbage is scattered around the room in heaps. For " +
        "the trolls, the room is clean even though piles of " +
        "garbage lie scattered about the room.\n");
}
/*
 * Function name : set_add_guardroom_dirty
 * Description   : describes how dirty a guard room is
 */

void set_add_guardroom_dirty()
{
    add_item(({"garbage", "trash", "litter"}),
        "The garbage is smelly and scattered all over the floor. " +
        "It is thick in places, making walking on the floor " +
        "treacherous. It looks like the garbage has been lying " +
        "on the floor for quite some time now.\n");
}


/*
 * Function name : set_add_water_pools
 * Description   : describes the slime on the walls
 */
void set_add_water_pools()
{
    add_item(({"pools", "pools of water","pool", "puddles", 
            "puddle of water", "puddles of water", "puddle"}),
        "The pools and puddles of water are of varying sizes " +
        "throughout the tunnel. One large one has accumulated in " +
        "the center of the tunnel. It is dirty and putrid looking " +
        "and unfit to drink.\n");
}
// Randomly generates special roomtells based on 
// if the room is lit or not
string dynamic_room_tell()
{
    int roomtell_count, 
        max_msgs = 4;
    string msg;

    roomtell_count = random(max_msgs);

    if (ext_sconce == 1) // not lit
    {
        switch(roomtell_count)
        {
            case 0:
            {
                msg = "Something pitchy smelling fills the air.";
                break;
            }
            case 1: 
            {
                msg = "The sound of grunts and slapping runs " +
                "past you in the dark.";
                break;
            }
            case 2:
            {
                msg = "Snorts and snufflings echo nearby.";
                break;
            }
            case 3:
            {
                msg = "A pot swings squeakily against the wall.";
                break;
            }
        } // end of unlit roomtells
    }
    else
    {
        switch(roomtell_count)
        {
            case 0:
            {
                msg = "The flames flicker and dance in the breeze.";
                break;
            }
            case 1: 
            {
                msg = "Dark tendrils of smoke rise from the " +
                "burning pots of pitch.";
                break;
            }
            case 2:
            {
                msg = "Black, pitchy smoke drifts about the room.";
                break;
            }
            case 3:
            {
                msg = "The pot of pitch pops, sending a flare of " +
                "sparks into the air.";
                break;
            }
        } // end of lit roomtells
    }
    return msg;
}

void
make_trolls()
{
    int i;
    
    if(!leader)
    {
        leader = clone_object(NPC_DIR + "newtroll");
        leader->move(TO);
        tell_room(TO,CAP(LANG_ADDART(leader->query_nonmet_name())) +
           " charges in and prepares for battle.\n");
    }
    
    if(!sizeof(trolls))
        trolls = allocate(max_trolls);
    for(i = 1; i < max_trolls; i++)
    if(!trolls[i])
    {
      	trolls[i] = clone_object(NPC_DIR + "newtroll");
      	leader->team_join(trolls[i]);
      	trolls[i]->move(TO);
      	tell_room(TO,CAP(LANG_ADDART(trolls[i]->query_nonmet_name()))+
      	    " charges in, preparing for battle.\n");
    }
    else
        if(trolls[i]->query_leader() !=leader)
        leader->team_join(trolls[i]);
}
