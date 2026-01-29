// file name:        /d/Avenir/common/holm/jungle_base.c
// creator(s):       Lilith, Oct '96
// revisions: 
// purpose:          
// note:             This file is to be inherited in all jungle rooms.  
//                   The more frequent add_items should be entered 
//                   here.		     
// bug(s):           
// to-do:            

#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include "/sys/terrain.h"

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"

string *cv = HERB_MASTER->query_herbs( ({"cave", "desert"}) );
string *ju = HERB_MASTER->query_herbs( ({"jungle"}) );
string *st = HERB_MASTER->query_herbs( ({"stream"}) );
string *ma = HERB_MASTER->query_herbs( ({"marsh"}) );

/* Prototypes */
/* These are the add_items and add_cmd_items for the jungle rooms 
 * (see below)
 */
void add_air();
void add_atrack();
void add_cliff();
void add_fern();
void add_grass();
void add_hedge();
void add_moss();
void add_sea();
void add_seawall();
void add_stream();
void add_treefern();
void add_veg();

/*
 * Function name: create_jungle_room
 * Description:   This function should be used for creating jungle rooms.
 */
void create_jungle_room()
{
    set_terrain(TERRAIN_OUTSIDE);
    set_terrain(TERRAIN_NATURAL);
}

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting jungle rooms.
 */
void reset_domain_room()
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
    set_area("junglep");
    set_tell_time (150);

    /* Tells made to player when a room is occupied */
    add_tell("The eerie call of some exotic animal echos from "+
       "above you.\n");
    add_tell("There is a sudden rustle in the bushes.\n");
    add_tell("A drop of condensed water falls onto you from "+
       "the leaves above.\n");
    add_tell("A flash of silvery-brown fur streaks across your "+
       "path and disappears from view.\n");
    add_tell("The air is ripe with the musty smell of decomposing "+
       "wood.\n");
    add_tell("A finger of mist drifts past you.\n");
    add_tell("Subdued light floods the woods, illuminating dust "+
       "motes and a delight of greenery.\n"); 
    add_tell("A rope of light plunges through the trees to the "+
       "forest floor.\n");
    add_tell("The light, now bright and now dull as the Source "+
       "fluctuates above, creates a world of green jewelled "+
       "glowing.\n");
    add_tell("The muted thunder of pounding hooves reaches your "+
       "ears.\n");


    /* If an add_item will be in every room, add it here */
    add_air();
    add_veg();
    
    /* There is light in this area (see ~Avenir/common/common.h 
     * for this define and the one following) */
    LIGHT;
    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;

    add_prop(ROOM_I_HIDE, 0);

    create_jungle_room();
    reset_domain_room();
}

/* These are the add_items and add_cmd_items for the jungle rooms 
 * (Those used more than once in the area)
 */
void
add_air()
{
    add_cmd_item("air", "smell", "It is thick with moisture and "
       +"pungent with the odour of many plants and animals.\n");
}

void 
add_atrack()
{
    add_item(({"track", "ancient track"}),
       "It is little more than an animal track, mostly obscured "+
       "by the prolific growth of vegetation along the forest "+ 
       "floor.\n");
}

void
add_cliff()
{
    add_item(({"cliff", "high cliff", "spire", "dark spire", "mountain"}), 
        "From this angle it looks like a dark wave topped with "+
        "pale green foam, caught eternally in that moment just "+
        "prior to breaking, carved in ageless stone.\n");
    set_up_herbs(({ ONEOF(cv), ONEOF(cv), ONEOF(cv) }), 
        ({ "cliff", "wall", "stone" }), 5);
}

void 
add_fern()
{
    add_item(({"fern", "ferns", "soil", "floor", "litter"}),
        "Ferns grow thickly on the rich soil and leaf litter "+
        "of the forest floor, making it difficult to follow "+
        "trails.\n");
    set_up_herbs(({ ONEOF(ju), ONEOF(ju), ONEOF(ju) }), 
        ({ "fern", "ferns", "soil", "floor", "litter" }), 5);
}

void
add_grass()
{
    add_item(({"grass", "slope", "western slope", "tufts", "greenery"}),
        "The grass is the vibrant green of new growth. It is "+
        "close-cropped, probably by the small deer which graze "+
        "in the area.\n");
    set_up_herbs(({ GET_ONE(st), GET_ONE(st), GET_ONE(st) }), 
        ({ "grass", "slope", "western slope", "tufts", "greenery"}), 5);    
}

void
add_hedge()
{
    add_item(({"hedge","hedges"}),
        "Massive hedges have grown up on either side "+
        "of this path. They are thick with thorns.\n");
}

void
add_moss()
{
    add_item(({"moss"}),
        "Spongy and green, moss grows on every possible "+
        "surface here, relishing the moist environment.\n");        
    set_up_herbs(({ GET_ONE(ma), GET_ONE(ma), GET_ONE(ma) }), 
        ({ "moss"}), 5);    

}

void
add_sea()
{
   add_item(({"sea","ocean"}),
      "The sea surrounding the island is completely "
     +"lightless, so you have no indication of either how "
     +"deep it is, or what hides beneath the surface. "
     +"It gives you an uncomfortable feel, and "
     +"strange eddies swirl in eerie patterns.\n");
}

void
add_seawall()
{
    add_item(({"wall", "stone", "rock", "obsidian", "seawall"}),
        "Black volcanic glass from a long forgotten eruption, "+
        "this odd wall was probably formed by lava piling up as "+
        "it rapidly cooled in water. Presently, it acts as a "+
        "seawall, fortuitously protecting the jungle from the "+
        "dark waters of the Sybarus Sea.\n");
}

void
add_stream()
{
    add_item(({"stream", "water", "streambed"}),
        "The stream has been formed by water condensation from the "+
        "cliff wall towering overhead. It is possible, too, that "+
        "a spring supplies water from a low-point somewhere along "+
        "the streambed. It is cloudy and cold, and grows deeper in "+
        "the north, shallower in the south.\n");
    set_up_herbs(({ GET_ONE(st), GET_ONE(st), GET_ONE(st) }), 
        ({ "stream", "water", "streambed" }), 5);    
}

void
add_treefern()
{
    add_item(({"tree fern", "tree ferns", "fronds", "limb"}), "The tree "+
       "ferns jut out from the ground at odd angles, their trunks "+
       "shaggy with moss. Fronds like the plumage of exotic green "+
       "birds cast lacy shadows upon the ground.\n");
    add_cmd_item(({"tree fern", "tree ferns", "fronds", "limb"}),
        "climb", "It is too slippery with moss to climb.\n");
}

void
add_veg()
{
   add_item(({"vegetation","plants","canopy","undergrowth", "tree",
      "trees", "vines", "vine", "bush","bushes", "branches"}),
      "This area of the island seems to contain a myriad of plant "+
      "life, growing so thickly that it prevents any possibility of "+
      "movement except along existing paths.\n");
    add_cmd_item(({"tree"}), "climb", "It is too slippery with "+
       "moss to climb.\n");
    set_up_herbs(({ ONEOF(ju), ONEOF(ju), ONEOF(ju) }), 
        ({ "vegetation","plants","canopy","undergrowth", "tree",
        "trees", "vines", "vine", "bush","bushes", "branches"}), 5);

}


/* Start the room tells as soon as someone enters the room */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}
/* This is for the anaconda...decided not to make it follow
void
leave_inv(object ob, object to)
{
    object master_worm;
    ::leave_inv(ob, to);
    if (!to || !ob || !interactive(ob))
        return;
    if (!(master_worm = present("serpent", TO)) ||
        environment(master_worm) != TO)
        return;
    master_worm->notify_leave_env(ob, to);
}
*/
/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
