/* /d/Faerun/guilds/fire_knives/rooms/herb.c
 *
 * Nerull 2019
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";


inherit FIREKNIVES_STD_ROOM;
inherit "/d/Faerun/guilds/fire_knives/rooms/herb_b.c";

object herbalist;

string read_plaque();


/*
 * Function name: create_fireknives_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Apothecary");
     
    set_long("The compact room is dense with a thousand "
    +"different aromas that "
    +"permeate the area. Wall shelves "
    +"decorate the walls with jars and cups of "
    +"various size and styles, some labeled "
    +"while others not. A wooden counter "
    +"separates the wall to the north from the "
    +"rest of the area where a simple "
    +"chair serves as a resting place for the "
    +"operator of the shop. To the right "
    +"side of the table is a wooden pedestal "
    +"with a massive tome opened on it, "
    +"serving as a catalogue of the various herbs "
    +"available throughout the lands.\n");
     
    add_item(({"shop","room","compact room","area"}),
    "The shop is rather small and compact. The scent "
    +"arising from the various herbs "
    +"permeates the room. \n");

    add_item(({"aroma"}),
    "The aroma from the herbs is varied, ranging "
    +"from acrid to sweet. The combination "
    +"of them all is enough to make anyone woozy, and "
    +"it makes you wonder how someone "
    +"might be able to spend their days here.\n");
    
    add_item(({"wall shelves","shelves"}),
    "Shelves on the walls hold jars and cups of "
    +"various sizes and styles. They are of "
    +"a simple wooden material, sturdy and well dried.\n");
    
    add_item(({"walls"}),
    "The walls are decorated with shelves that contain "
    +"the various containers in which "
    +"herbs are kept.\n");
    
    add_item(({"jars","cups","containers"}),
    "The containers come in all shapes and sizes, varying "
    +"in color as well.\n");

    add_item(({"chair"}),
    "The chair is currently empty, standing in front "
    +"of the counter where the herbalist "
    +"works. It is simple and made of wood, functional "
    +"rather than decorative.\n");
    
    add_item(({"operator"}),
    "The operator isn't here at the moment, and "
    +"must be in the back room.\n");
    
    add_item(({"pedestal"}),
    "The pedestal is wide at the base, narrowing "
    +"down as it goes upwards then widening again. "
    +"Atop it is a massive tome.\n");
    
    add_item(({"catalogue","tome","massive tome"}),
    "The tome depicts coloured drawings of various "
    +"herbs along with information on where they "
    +"grow and what their effects are.\n");
    
    add_item(({"floor"}),
    "The floor is clean and bare, made of a cold "
    +"stone that is refreshing and soothing amidst "
    +"the intense collision of smells.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is high and lost in the darkness "
    +"that engulfs it, impossible to see in detail "
    +"from here.\n");
    
    config_default_trade();

    set_money_greed_buy(60);
    set_money_greed_sell(150);
    set_money_give_out(   ({ 10000,   700,  50,   10 }));
    set_money_give_reduce(({     0,     2,   4,    6 }));
    
    /* set the room to be used as storage room for this shop */
    set_store_room(FIREKNIVES_ROOMS_DIR + "herb_stor");
    call_other(store_room, "load_me");
    
    add_item(({"sign", "poster"}), read_sign());
    add_cmd_item(({"sign", "poster"}), "read", read_sign());
    
    add_item(({"plaque", "small plaque", "small copper plaque", 
    "copper plaque"}), "@@read_plaque");
    
    add_cmd_item(({"plaque", "small plaque", 
    "small copper plaque", "copper plaque"}), "read", "@@read_plaque");

    add_exit(FIREKNIVES_ROOMS_DIR + "o3", "west");
    
    setuid();
    seteuid(getuid());

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!herbalist)
    {
        herbalist = clone_object(FIREKNIVES_GUILD_DIR + "npc/herbalist");
        herbalist->move(this_object(), 1);
    }
}


void
init()
{
    ::init();

    init_herb_shop();
}


string
read_plaque()
{  
    return "The small copper plaque looks well polished.\n";
}


int
query_shop_no_business(mixed pl)
{
    if (stringp(pl))
        
	pl = find_living(pl);
    
    if (pl->query_wiz_level())
    {
        return 0;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1)
    {
        return 0;
    }

    return 1;
}


int
query_shop_hook_restricted_herb(object pl, string str)
{
	return 0;
}


void
shop_hook_restricted_herb(object pl, string str)
{
    notify_fail("The Council forbid the selling of "
    +"that herb to non-members!\n");
}