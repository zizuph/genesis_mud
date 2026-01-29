/* /d/Faerun/guilds/warlocks/rooms/hall03.c
 *
 * Room in the guildhall.
 *
 * Nerull 2018
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;


string tapestry()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()) 
    || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
    {
        return "The large tapestry depicts nothing but swirling "
        +"colours, made from human hair.\n";
    }
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            return "The large tapestry depicts an Archfey with the appearance of "
            +"an old crone with gnarled arms like tree trunks clutching a "
            +"massive pestle and a spindly broom in dark brown claws. From "
            +"her satchel, you see a infant arm hanging limp. Protruding "
            +"from the top of a large flying mortar, the old crone squats, "
            +"her thin lips as downcast as her dark eyes. Wild strings of "
            +"mangy hair fly out behind her. Around her, toadstools rise "
            +"up, red and plump in contrast to her jerky-dry skin. The "
            +"forward tilt of her unorthodox vehicle and her hurried "
            +"expression indicate she's in pursuit of someone, or "
            +"something, while her eyes are fixed at...You! "
            +"At the bottom of the tapestry, you notice a name, "
            +"saying 'Baba Zirana'.\n";
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            return "The large tapestry depicts an Archfey with the appearance of "
            +"an old crone with gnarled arms like tree trunks clutching a "
            +"massive pestle and a spindly broom in dark brown claws. From "
            +"her satchel, you see a infant arm hanging limp. Protruding "
            +"from the top of a large flying mortar, the old crone squats, "
            +"her thin lips as downcast as her dark eyes. Wild strings of "
            +"mangy hair fly out behind her. Around her, toadstools rise "
            +"up, red and plump in contrast to her jerky-dry skin. The "
            +"forward tilt of her unorthodox vehicle and her hurried "
            +"expression indicate she's in pursuit of someone, or "
            +"something, while her eyes are fixed at...You! "
            +"At the bottom of the tapestry, you notice a name, "
            +"saying 'Baba Zirana'.\n";
        }
    }
    
    return "The large tapestry depicts nothing but swirling "
    +"colours made from human hair.\n";  
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Somewhere in a small plain claystone corridor");
    
    set_long("Somewhere in a small plain claystone corridor. A "
    +"green haze similar to what exist in damp swamps "
    +"occupies this area like a humid stinking blanket. The reek "
    +"of standstill swamp water is only matched by the sound of "
    +"irritating mosquitos that constantly swarms around your head, "
    +"threatening to sip some of your precious blood. The hanging "
    +"iron brazier gives away a green flickering flame that illuminates "
    +"the haze and the environment in a similar colour, creating a minor "
    +"illusion that you are no longer in a claystone corridor but rather "
    +"somewhere in a damp humid swamp. The ground is covered in soft "
    +"water-soaked moss. A woven tapestry hangs on the south "
    +"plain claystone wall.\n");
        
    add_item(({"tapestry", "large tapestry"}), tapestry);
    
    add_item(({"corridor"}),
    "The claystone corridor leads to other adjacent areas. You feel the "
    +"slight draft coming from other directions.\n");    
    
    add_item(({"mosquitos", "irritating mosquitos"}),
    "You hear their tiny wings buzzing around your head, but you can't "
    +"see nor feel none touching you. Still irritating though.\n");
    
     add_item(({"green haze", "haze", "blanket"}),
    "The air here feels thicker and more humid than normal, and it's "
    +"filled with tiny particles that illuminates by the green flickering "
    +"flame, giving it a slight opacity property.\n");

    add_item(({"reek", "smell"}),
    "It stinks like stagnant swamp water here. The smell of rotting "
    +"plant material and other things decaying starts to stick to "
    +"your clothes.\n");        
    
    add_item(({"wall", "walls"}),
    "The claystone walls here are quite smooth and barren, with the "
    +"exception of the south wall which is covered by a large "
    +"tapestry.\n");
    
    add_item(({"ground", "floor", "moss", "moss-covered ground"}),
    "The moss-covered ground is soaked in water and feels rather "
    +"soft, not entirely unlike what you find in swamps.\n");
    
    add_item(({"ceiling", "roof"}),
    "Uneven and jagged, the claystone ceiling contains one prominent "
    +"feature; A hanging iron brazier firmly anchored by an iron bolt.\n");
    
    add_item(({"iron bolt", "bolt"}),
    "The iron bolt is hammered into the ceiling. It holds the chain which "
    +"the iron brazier is attached to.\n");
    
    add_item(({"flame", "light", "green flame", "green flickering flame"}),
    "The flame erupting from the hanging iron brazier is rather small, but "
    +"flickers as if its drafty here. It is green in colour, and does a poor "
    +"job in actually illuminating the area.\n");
    
    add_item(({"hanging iron brazier", "iron brazier", "brazier"}),
    "The iron brazier hangs from a single chain attached to a bolt in the "
    +"ceiling. It has the shape of a black mortar, and fuels a small green "
    +"flame that flickers on top of it.\n");

    add_exit(WARLOCK_ROOMS_DIR + "post", "north");
    add_exit(WARLOCK_ROOMS_DIR + "start", "east");
    add_exit(WARLOCK_ROOMS_DIR + "central", "west");

    reset_faerun_room();
}


void
do_whispers()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()) 
    || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
    || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return;
    }
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers, as "
            +"if something or someone here is beckoning you!\n");
            
            return;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers, as "
            +"if something or someone here is beckoning you!\n");
            
            return;
        }
    }
    
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(0.5, 0.0, &do_whispers());
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}