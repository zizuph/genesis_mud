// file name:        /d/Avenir/common/holm/shore_base.c
// creator(s):       Lilith, April '96
// revisions: 
// purpose:          
// note:             This file is to be inherited in all shore rooms.  
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
#include "../holm.h"

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"

string *sea = HERB_MASTER->query_herbs( ({"sea"}) );
string *beach = HERB_MASTER->query_herbs( ({"beach", "saltmarsh"}) );

/* Prototypes */
/* These are the add_items and add_cmd_items for the shore rooms 
 * (see below)
 */
void add_air(); 
void add_beachg();
void add_beachp();
void add_beachs();
void add_flotsam();
void add_grass();
void add_promontory();
void add_rocks();
void add_salt();
void add_sea();
void add_seawall();
void add_source();
void add_waves();
/*
 * Function name: create_shore_room
 * Description:   This function should be used for creating shore rooms.
 */
void create_shore_room() { }

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting shore rooms.
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
    set_area("shorep"); /* The module that runs the area */
    set_tell_time(150);

    /* Tells made to player when a room is occupied */
    add_tell("Diffuse light plays over the dark waters of the sea.\n"); 
    add_tell("The cry of a shorebird echos in your ears.\n");
    add_tell("Waves thunder against the stone of the promontory.\n");
    add_tell("A sea breeze whistles over the stones, tickling your "+
        "brow with tender fingers.\n");
    add_tell("The sea crashes against the rocks in timeless "+
        "antagonism.\n");
    add_tell("The dark sea, pregnant with mystery, seems to speak "+
        "to you in a wordless, enticing voice.\n");
    add_tell("A strong breeze blows over you, sprinkling your skin "+
        "with salt-spray.\n");

    /* If an add_item will be in every room, add it here */
    add_air();
    add_promontory();
    add_sea();
    add_seawall();
    add_source();
    add_waves();
      
    /* There is light in this area (see ~Avenir/include/defs.h 
     * for this define and the one following) */
    LIGHT;
    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_up_herbs(({ ONEOF(beach), ONEOF(beach), ONEOF(beach) }), 
        ({ "shore", "sand", "beach", "grass" }), 5);
    set_up_herbs(({ ONEOF(sea), ONEOF(sea), ONEOF(sea) }), 
        ({ "sea", "water", "rock", "seaweed", "flotsam", 
           "driftwood", "pool", "intertidal pool" }), 5);

    create_shore_room();
    reset_domain_room();
}

/* These are the add_items and add_cmd_items for the shore rooms 
 * (Those used more than once in the area)
 */
void add_air()
{
    add_cmd_item("air", "smell", "It is thick with moisture and "
       +"pungent with the tangy smell of salt from the sea.\n");
}
void add_beachg()
{
    add_item(({"beach", "shore", "gravel"}),
        "This beach is composed mostly of rough gravel broken off of "+
        "the nearby stones and swept ashore by the waves.\n");
    set_up_herbs(({ ONEOF(sea), ONEOF(sea), ONEOF(sea) }), 
        ({ "beach", "water", "shore", "seaweed", "flotsam", 
           "driftwood", "gravel" }), 5);

}
void add_beachp()
{
    add_item(({"beach", "shore", "pebble", "pebbles"}),
        "This beach is composed mainly of small pebbles that have been "+
        "rounded and polished by years of wave-action.\n");
    set_up_herbs(({ ONEOF(sea), ONEOF(sea), ONEOF(sea) }), 
        ({ "beach", "water", "shore", "seaweed", "flotsam", 
           "driftwood", "pebble", "pebbles" }), 5);

}
void add_beachs()
{
    add_item(({"beach", "sand", "black sand", "strand", "shore"}),
        "This sand is black and very fine. It glitters in the "+
        "light of the Source.\n");
    set_up_herbs(({ ONEOF(beach), ONEOF(beach), ONEOF(beach) }), 
        ({ "shore", "sand", "beach", "grass" }), 5);
}
void add_flotsam()
{
    add_item(({"seaweed", "flotsam", "driftwood", "hump"}),
        "Still moist with seawater, it has been recently washed "+
        "ashore by the tide. \n");
}
void add_grass()
{
    add_item(({"grass", "seagrass", "tuft", "tufts", "hillock", 
        "hillocks", "beachgrass", "beach grass"}),
        "Very hardy plants that grow sparsely in the sand.\n");
    set_up_herbs(({ ONEOF(beach), ONEOF(beach), ONEOF(beach) }), 
        ({ "grass" }), 5);

}
void add_promontory()
{
    add_item(({"promontory", "leviathan"}), 
        "The promontory is rather small, composed of mostly geometric "+
        "stones jutting defiantly out of the sea. It is continually "+
        "battered by the sea.\n");
}
void add_rocks()
{
    add_item(({"rock", "rocks", "boulder", "boulders", "stone", "stones"}),
        "Dark and unclimbable, slippery with algae and water.\n");
    set_up_herbs(({ ONEOF(sea), ONEOF(sea), ONEOF(sea) }), 
        ({  "rock", "rocks", "boulder", "boulders", "stone", "stones",
            "water", "algae" }), 5);
}
void add_salt()
{
    add_item(({"salt", "stain", "stains", "lines", "wavy lines", 
        "white lines"}),
        "In some spots you can see where salt accumulated as the "+
        "tide withdrew. It stains the black sand with wavy white "+
        "lines.\n");
}
void add_sea()
{
    add_item(({"sea","ocean", "sybarus sea", "water", "brackish water"}),
        "The sea surrounding the island is completely "
       +"lightless, so you have no indication of either how "
       +"deep it is, or what hides beneath the surface. "
       +"It gives you an uncomfortable feel, and "
       +"strange eddies swirl in eerie patterns.\n");

    add_cmd_item(({"sea","ocean", "sybarus sea"}), 
        ({"enter", "jump", "dive"}), "On second thought, maybe not. "+
        "You would surely be sucked beneath the water's surface and "+
        "against the rocks.\n");

}
void add_seawall()
{
    add_item(({"wall", "stone", "rock", "obsidian", "seawall"}),
        "Black volcanic glass from a long forgotten eruption, "+
        "this odd wall was probably formed by lava piling up as "+
        "it rapidly cooled in water. Presently, it acts as a "+
        "seawall, fortuitously protecting the inland jungle "+
        "from the dark waters of the Sybarus Sea.\n");
}
void add_source()
{
    add_item(({"Source", "source", "light", "illumination", "skein", 
        "glow", "above", "sky"}),
        "High above, in the ceiling of this great cavern, is "+
        "a glowing skein of mineral that emits light.\n");
}   
void add_waves()
{
    add_item(({"waves", "tide"}),
        "The waves, white-capped, tumble and churn against "+
        "offshore rocks and the black sand beach.\n");
}

/* Start the room tells as soon as someone enters the room */
void enter_inv(object ob, object from)
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
