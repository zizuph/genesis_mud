// file name:        /d/Avenir/common/holm/hf_base.c
// creator(s):       Lilith, Oct '96
// revisions: 
// purpose:          
// note:             This file is to be inherited in all hf rooms.  
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

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"

string *plant = HERB_MASTER->query_herbs( ({"pine"}) );
string *rock = HERB_MASTER->query_herbs( ({"desert"}) );

/* Prototypes */
/* These are the add_items and add_cmd_items for the hf rooms 
 * (see below)
 */
void add_avalanche();
void add_cave();
void add_cliff();
void add_cone();
void add_coneget();
void add_crevice();
void add_hedge();
void add_hump();
void add_jump();
void add_jungle();
void add_lichen();
void add_moss();
void add_pine();
void add_ridge();
void add_sea();
void add_stone();
void add_source();

/*
 * Function name: create_hf_room
 * Description:   This function should be used for creating hf rooms.
 */
void create_hf_room()
{
}

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting  rooms.
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
    add_tell("Trees creak as the wind twists their limbs.\n");
    add_tell("The chittering of small animals comes from nearby.\n");
    add_tell("A refreshing gust of salty sea air blows over you.\n");
    add_tell("You can smell the pine-needles you have crushed "+
        "underfoot.\n");
    add_tell("A cry of pain suddenly echoes off the stone of the "+
        "cliff.\n");   

    /* If an add_item will be in every room, add it here */
    add_cone();
    add_coneget();
    add_jump();
    add_jungle();
    add_cliff();
    add_hump();
    add_pine();
    add_sea();
    add_stone();
    add_source(); 
    
    /* There is light in this area (see ~Avenir/common/common.h 
     * for this define and the one following) */
    LIGHT;
    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;

    set_up_herbs(({ ONEOF(rock), ONEOF(rock), ONEOF(rock) }), 
        ({ "moss", "rock", "cliff", "litter", "lichen" }), 5);
    set_up_herbs(({ ONEOF(plant), ONEOF(plant), ONEOF(plant) }), 
        ({ "tree", "vines", "trees", "pines", "lip"}), 5);

    create_hf_room();
    reset_domain_room();
}

/* These are the add_items and add_cmd_items for the hf rooms 
 * (Those used more than once in the area)
 */

void 
add_avalanche()
{
    add_item(({"avalanche", "weak place", "weak stone", "scar"}),
        "There is a weak place in the stone of the cliff. "+
        "Gravity pulls the weak stone away from the cliff "+
        "wall, and it falls, shattering into smaller pieces "+
        "which roll down toward the jungle's edge.\n");
}

void
add_cave()
{
    add_item(({"cave", "opening", "maw", "gap", "entrance",
        "mouth", "gaping maw", "cliff face"}), 
        "There appears to be an opening in the hump of stone."+
        "Irregularly shaped, it looks almost like the mouth of "+
        "a cave. You would have to try to enter it to be "+
        "sure though.\n");
}

void
add_cliff()
{
    add_item(({"cliff", "high cliff", "mountain", "cliffside"}), 
        "You are standing on the cliff, towering above "+
        "the jungle. It forms a large spiny hump that "+
        "seems to crest just before the cliff edge.\n");
}

void
add_cone()
{
    add_item(({"cone", "cones", "pine cones", "droppings"}),
        "They are tiny and golden-brown. Their circular "+
        "shape is reminiscent of deer droppings.\n");       
}

void
add_coneget()
{
    add_cmd_item(({"cone", "cones", "pine cones", "droppings"}),
       ({"get", "pick"}), "The cones have no value or useful"+
       "ness, they'll just clutter your inventory.\n");
}

void 
add_crevice()
{
    add_item(({"crevice", "crack", "rent", "cleft"}),
       "Some arcane force has caused the living stone to "+
       "separate from itself, creating a deep cleft large "+
       "enough to fit a person.\n");
}

void
add_hedge()
{
    add_item(({"hedge","hedges"}),
        "Massive hedges have grown up on either side "+
        "of this path. They are thick with thorns.\n");
}

void 
add_hump()
{
    add_item(({"hump", "crest", "spiny hump", "prow"}),
        "Rising like the crest of a wave above the "+
        "cliff edge, it is a spiny hump of stone."+
        "\n");
}

void
add_jump()
{
    add_cmd_item(({"cliff", "ledge"}), ({"jump", "jump off"}),
        "The only things to break your fall are the branches "+
        "of trees -- and it is such a long way down you'd "+
        "probably impale yourself on one.\n");
}

void
add_jungle()
{
    add_item(({"jungle", "carpet", "forest", "lowland forest"}),
        "Green. The jungle is incredibly green. "+
        "Every possible shade of green is laid out below you, "+
        "a living carpet which undulates in the sea breeze.\n");
}

void
add_lichen()
{
    add_item("lichen", "A hardy smybiotic plant which manages "+
        "to live somehow on open rock-face. This particular "+
        "lichen is a virulent yellow-green colour reminiscent "+
        "of pus from an infected wound.\n");
}

void
add_moss()
{
    add_item(({"moss", "vines", "vine", "fringe"}),
        "Spongy and green, moss grows along the cliff "+
        "edge, where warm air rises from the jungle, "+
        "carrying moisture.\n");        
}

void
add_pine()
{
    add_item(({"pine", "pines", "tree", "trees", "bark",
        "needle", "needles", "leaves"}),
        "Trees so stunted and twisted as to make their "+
        "age indeterminable, with scaly bark and slender "+
        "green needles for leaves. Tiny cones dangle from "+
        "the underside of the branches.\n");
}

void
add_ridge()
{
    add_item(({"ridge"}),
        "This ridge rises midway up the cliffside. You can "+
        "see the rest of the cliff towering above you.\n");
}

void
add_sea()
{
   add_item(({"sea","ocean", "shore"}),
      "The sea surrounding the island is completely "
     +"lightless, so you have no indication of either how "
     +"deep it is, or what hides beneath the surface. "
     +"It gives you an uncomfortable feeling, and "
     +"strange eddies swirl in eerie patterns.\n");
}

void
add_stone()
{
    add_item(({"wall", "stone", "rock", "obsidian", "living stone"}),
        "It is black volcanic glass and basalt from a long "+
        "forgotten eruption. It seems to resonate with an "+
        "ominous echo of its violent and fiery birth.\n");
}

void
add_source()
{
    add_item(({"source", "light", "ceiling", "roof", "veins", "glow"}),
        "The veins of light-producing mineral snaking across the "+
        "ceiling of this great cavern give off an unearthly glow "+
        "that illuminates this place.\n");
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
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
