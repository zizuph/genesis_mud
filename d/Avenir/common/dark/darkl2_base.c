// file name:    /d/Avenir/common/dark/darkl2_base.c
// creator(s):   Casca, 01/17/00
// revisions:    Lilith, 12/03/00 - added search_dark, TERRAIN.
//      Lucius, OCT 08 - Used the Genesis opal_fire instead of our fire_opal.
// purpose:          
// note:         This file is to be inherited in all tunnels.  
//               The more frequent add_items should be placed here.
// bug(s):           
// to-do:            

#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Inherit the Avenir time object   */
inherit "/d/Avenir/inherit/avenir_time";

/* Inherit the room_tell functions  */
inherit "/d/Avenir/inherit/room_tell";

/* Inherit clone_unique function */
inherit "/lib/unique";

#include <macros.h>                       /* macros like VBFC and QNAME */
#include <tasks.h>                        /* defines for the TASK system */
#include <terrain.h>                      /* defines for TERRAINs */
#include <ss_types.h>                     /* defines for the skills */
#include <stdproperties.h>                /* self-explanatory */
#include "/d/Genesis/gems/gem.h"          /* macros and defs for Gems */
#include "/d/Avenir/common/herbs/herbsearch.h" /* herbs for the area */

/* Include the local area defines, etc */
#include "/d/Avenir/include/defs.h"            /* Short-hand macros */
#include "/d/Avenir/include/paths.h"           /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"          /* ADD_SKIN, IN_IN, etc */

#define GET_ONE(x)   ((x) [random(sizeof(x))])
string *cv = HERB_MASTER->query_herbs( ({"cave"}) );

/* Prototypes */
/* These are the add_items and add_cmd_items For the L2 area
 * (see below)
 */
void add_cavern(); 
void add_gneiss_tunnel();
void add_gnome_home();
void add_n_tunnel();
void add_r_tunnel();
void add_w_tunnel();
void add_new_tunnel();
void add_old_tunnel();
void add_pool();

/*
 * Function name: create_tunnel_room
 * Description:   This function should be called to create tunnels.
 */
void create_tunnel_room()
{
}

/*
 * Function name: reset_tunnel_room
 * Description:   This function should be called to reset tunnel rooms.
 */
void reset_tunnel_room()
{ 
    set_searched(0);
    ::reset_domain_room();
}

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */
public void
create_domain_room()
{
    set_area("darkl2p");
    set_tell_time (250);

    /* Tells made to player when a room is occupied */
    add_tell("A faint sound echos up from the darkness.\n");
    add_tell("You hear a faint dripping sound.\n");
    add_tell("A chill breeze raises the hair on the back of your neck.\n");
    add_tell("A feeling of unease descends upon you.\n");
    add_tell("A long deep moan echos through the tunnel.\n");

    /* macro defined in /d/Avenir/include/macros.h */
    IN;
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_HIDE, 0);

    create_tunnel_room();
    reset_tunnel_room();
}

/* These are the add_items and add_cmd_items for the tunnels.
 * (Those used more than once in the area).
 */

void
add_gneiss_tunnel()
{
    add_item(({"tunnel","passage", "gneiss tunnel"}),
        "This is a natural tunnel formed by the mechanisms of the planet "+
        "eons ago. It has been modified a bit by the denizens of this "+
        "place.\n");	
    add_item(({"ground", "floor", "gravel"}),
        "The floor of the tunnel is mostly gravel made ages ago by an "+
		"ancient river that once flowed through here.\n");
    add_item(({"wall", "walls", "gneiss", "stone"}),
        "The walls of this tunnel have been polished fairly smooth by "+
        "the flow of water. The walls are composed of gneiss that is "+
        "fairly light in color, mostly sandy brown with lighter white "+
        "stripes that zig-zag through it. Here and there you can see "+
        "dark reddish brown crystals that look like garnets embedded "+
		"in the walls, and veins of ore.\n");
	add_item(({"ore", "vein", "veins", "iron ore", "gold ore",
    	"silver ore", "veins of ore"}), "The walls are pock-marked "+
        "with veins of coal, as well as iron, silver, and gold ore.\n");
    add_item(({"garnet", "garnets", "garnet in walls", "crystals",
	    "crystals in walls", "chunks", "chunks of garnet"}),
        "There are raw chunks of garnet in the walls, exposed by "+
        "the flow of water through the tunnel.\n");
    add_item(({"ceiling", "roof"}),
	    "The ceiling of the tunnel is not as smooth as the walls, "+
        "but it isn't jagged either. It's fairly low, so tall "+
        "folks will need to be careful not to bump their heads.\n");	
    add_item(({"foot print", "footprint", "footprints" }),
        "Feet have made marks here, but the gravel makes it impossible "+
        "to make out any details.\n");
		
    add_tell("Gravel crunches underfoot.\n");
    add_tell("You hear something that sounds like footfalls "+
        "on gravel.\n");	
	add_tell("A very pungent, musty odor wafts past you.\n");
	add_tell("A melody reaches your ears. It is faint and quite haunting.\n");
	
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | 
        TERRAIN_ROUGH | TERRAIN_SHADOWS);	
    set_up_herbs(({ GET_ONE(cv), GET_ONE(cv), GET_ONE(cv) }), 
        ({ "walls", "wall", "crack", "cracks", "fissure",
           "ground", "gravel", "floor", "opening", "fungi"}), 3);
}

void
add_gnome_home()
{
    add_item(({"recess", "recesses", "niche", "niches", "slots"}), 
        "These recesses have been carved into the gneiss walls to provide "+         
		"sleeping spaces and perhaps a bit of privacy. Some of them are "+
        "extra deep so families may lay together, probably to share "+
        "warmth.\n");
    add_item(({"bed", "mat"}), "Resources are few and there isn't "+
        "anything to make beds or mats from, so the gneiss gnomes "+
        "sleep on the bare stone.\n");
    add_item(({"cubby", "cubbyhole", "cubbyholes"}), "Here and there "+
        "you can see cubbyholes carved into the gneiss. They look like "+
		"individual sleeping spaces, as well as places to stash things.\n");
    add_item(({"mushroom", "mushrooms", "fungi"}), 
        "There are a few different types of mushrooms growing "+
        "here. Some of them might even be useful.\n");
	
}
void 
add_n_tunnel()
{
    add_item(({"tunnel","passage"}),
        "This is a natural tunnel formed by the mechanisms of the planet "+
        "many ages ago.\n");
    add_item(({"floor","ground"}),
        "The stone of the ground is uneven and rough, covered in places "+
        "by dirt and mud.\n");
    add_item(({"dirt","mud"}),
        "There is nothing remarkable about the stuff, it is what it appears "+
        "to be.\n");
    add_item(({"wall","walls"}),
        "The walls are different everywhere you look. Over there is a smooth "+
        "section that looks like a sheet of glass and over there an odd wavy "+
        "section that looks like melted wax. In someplaces it is rough and in "+
        "others smooth.\n");
    add_item(({"ceiling","roof","above"}),
        "The ceiling varies in height, sometimes you have to duck to get past "+
        "while in others it soars above you nearly reaching the limit of your "+
        "vision.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_dark");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_MUD |
	TERRAIN_ROUGH | TERRAIN_SHADOWS);
	
}

string
do_wash()
{
    write("Wow that water is ice cold!\nYou do a quick wash-up.\n");
	return "";
}
	
string 
do_drink()
{
    int dr;

    dr = TP->query_prop(LIVE_I_MAX_DRINK) / 10;
    if (!dr) dr = 200;
	
    if (!TP->drink_soft(dr))
    {
        write("The water is too much for you.\n");
        return "";
    }

    write("You squat down at the water's edge and drink from it "+
        "with cupped hands.\n"+
        "The water is intensely cold and sweet with minerals.\n");
    say(QCTNAME(TP)+" squats down at the water's edge and drinks.\n");
    return "";		
}

void
add_pool()
{
    add_item(({"water", "pool", "river", "lake"}),
		"There is a pool of water here, perhaps part of a lake or "+
        "an underground river, as it appears to be fresh water. "+
        "It is impossible to see below the surface, but you get "+
        "a feeling that it is deep enough for something to live in it.\n");		
	add_cmd_item(({"water", "pool", "river", "lake" }),
        ({"enter", "swim", "swim" }), 
        "You move to enter the water, but a little voice in "+
        "your head tells you that drowning is an unpleasant "+
        "way to die.\n");
    add_cmd_item(({"in water", "in pool", "in river", "in lake" }),
	    ({ "wash", "clean", "bathe" }), do_wash);
    add_cmd_item(({"water", "pool", "river", "lake" }),
	    ({ "drink", "sip" }), do_drink);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", ({"subterranean"}));
}	


void 
add_r_tunnel()
{
    /* Default in every room */
    add_item(({"tunnel","passage"}),
        "This tunnel has been laboriously carved from the earth by some "+
        "unknown agency.\n");
    add_item(({"floor","ground"}),
        "The floor here is relatively level and smooth having been "+
        "carved from the solid rock of the area.\n");
    add_item(({"wall","walls"}),
        "These walls have been carved out of solid stone. They still bear the "+
        "scars from the tools used in their creation. Occasional timbers have "+
        "been used to shore up areas of dubious stability. You notice an "+
        "octagon carved into the wall.\n");
    add_item(({"octagon","symbol"}),
        "While simple, this symbol has been carved into the wall with "+
        "great care and attention to symmetry. It is a plea to the "+
		"Goddess Sair to lend her strength to the walls.\n");
    add_item(({"ceiling","roof","above","beams"}),
        "The ceiling is of a decent height here. You can see marks from when "+
        "this tunnel was created. Some sections seem rather unstable with "+
        "cracks and fissures marring their surface, beams have been put in "+
        "place to support these areas.\n");
    add_tell("The ceiling groans ominiously and trickles of dust sift down "+
        "from the cracks.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_dark");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_SHADOWS);

}

void 
add_w_tunnel()
{
    /* Default in every room */
    add_item(({"tunnel","passage"}),
        "This tunnel has been laboriously carved from the earth by some "+
        "unknown agency.\n");
    add_item(({"wall","walls"}),
        "These walls have been carefully finished so that they are level "+
        "and straight. They are perfectly smooth and have been polished "+
        "to a soft finish. "+
        "There is an octagon carved in the wall here.\n");
    add_item(({"octagon","symbol"}),
        "While simple, this symbol has been carved into the wall with "+
        "great care and attention to symmetry.\n");
    add_item(({"floor","ground"}),
        "The floor here is perfectly level and smooth. "+
        "Great care has been taken in its creation.\n");
    add_item(({"ceiling","roof","above","vault"}),
        "The ceiling has been carved with a barrel vault to support "+
        "the weight bearing down upon it.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_dark");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_SHADOWS);

}

void
add_cavern()
{
    add_item(({"floor","ground"}),
        "The floor is rough and uneven. Dirt and mud cover some areas "+
        "of it.\n");
    add_item(({"ceiling","roof","above"}),
        "The rough ceiling hangs far over your head, cloaked in shadow.\n");
    add_item(({"cavern","room"}),
        "This is a large natural cavern formed long ago by the mechanisms "+
        "of this world.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_dark");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_OPENSPACE |
	TERRAIN_MUD | TERRAIN_ROUGH | TERRAIN_SHADOWS);
	set_up_herbs(({ GET_ONE(cv), GET_ONE(cv), GET_ONE(cv) }), 
        ({ "walls", "wall", "mud",
           "ground", "dirt", "floor"}), 3);


}

void
add_old_tunnel()
{
    add_item(({"timber","timbers"}),
        "These timbers are thick beams of oak that have been used here "+
        "and there to help shore up the tunnel. "+
        "Sections of the beams look as if they have been hacked at with a "+
        "sharp weapon or tool, probably scavanged for firewood.\n");
    add_item(({"scars","marks"}),
        "Faint time-worn marks still attest to the ancient efforts put "+
        "forth in the construction of this tunnel.\n");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_SHADOWS);

}

void
add_new_tunnel()
{
    add_item(({"timber","timbers"}),
        "Thick beams of oak have been used here and there to help shore up "+
        "the tunnel.\n");
    add_item(({"scars","marks"}),
        "The walls and ceiling still bear mute testimony of the intensive "+
        "labor needed to carve a path through solid stone.\n");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_SHADOWS);

}

/* Start the room tells as soon as someone enters the room */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}


/*
 * Function name: search_dark
 * Description:   Search results for add_items in the Dark.
 *                Gives general experience 100 each for max of  
 *                10 successful searches per login.
 * Returns:       string for success
 */
string 
search_dark(object player, string str)
{
    object    ob;
    int       i, n, w; 
       
    switch (str)
    {
        case "dirt":    
        case "debris":  
        case "detritus":
        case "dust":
        case "litter":
        case "trash":
        case "rocks":
        case "mud":
            w = random(6); 
            break; 
        case "water":   
        case "trickle":
        case "pool":
		case "puddle":
		case "puddles":
            w = 7;
            break;
        case "nook":
        case "nooks":
        case "crevice":
        case "crevices":
		case "crack":
		case "cracks":
            w = 8;
            break;
        case "hole":
        case "holes":
        case "tubes":
		case "tube":
		case "pillar":
            w = 9;
            break;
        case "wall":
        case "walls":
            w = 10;
            break;
        default:   
            return "";
    }
 

    /* If I've found objects already, I'm not finding any more */   
    n = player->query_prop("_avenir_dark_found");
    if (n > 5)
        return "";    

    /* Do I have the simple awareness to find something
     * and the wisdom to recognize it as being of value?
     */
    i = player->resolve_task(TASK_SIMPLE, ({ TS_WIS, SS_AWARENESS,}));
    if (i < 0)
        return "";    

    /* What I can find, depending on where I search */
    switch (w)
    {
        case 0 .. 1:
            ob = RANDOM_GEM_BY_RARITY(GEM_RARE);      break;
        case 2:
            ob = clone_unique(HOLM + "wolf/pelvic",
                 15, DARK +"obj/t_torch");            break;
        case 3:
            ob = clone_unique(HOLM + "wolf/toe",
                 15, "/d/Avenir/common/obj/coal");    break;
        case 4:
            ob = clone_object(DARK +"obj/t_torch");   break;
        case 5:
            ob = clone_object(COM + "obj/feather");   break;
        case 6 .. 8:
            ob = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_RARE);  break;
        case 9:
            ob = clone_object("/d/Genesis/gems/obj/opal_fire");
            break ;
        case 10:
            ob = clone_object("/d/Avenir/common/outpost/obj/lsource");
            break;
        default:  return "";
    }

    /* Make sure to add to the counter */
    player->add_prop("_avenir_dark_found", n + 1);

    /* I get some general experience for succeeeding */
    player->add_exp_general(100 + random(50));
    ob->move(player, 1);          
    
    return "You find "+LANG_ASHORT(ob)+".\n";
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
