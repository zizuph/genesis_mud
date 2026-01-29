/*
 * /d/Faerun/guilds/fire_knives/obj/quest_ulaks.c
 *
 * A pair of ulakses, quest object.
 *
 * Coded by Nerull, 2019
 *
 */

#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "std/object";


int
destroy_ulaks()
{
    write("You destroy the pair of steel ulaks!\n");
    set_alarm(1.0, 0.0, &remove_object());
    
    return 1;
}


int
wield_ulaks(string str)
{
    if (str == "ulaks" || str == "steel ulaks" || str == "pair of steel ulaks")
    {
        write("Upon closer inspection, you realize "
        +"these pair of steel ulaks are not ment for "
        +"wielding but rather for decor.\n");
        
        return 1;
        
    }

    return 0;
}


/*
 * Function name: create_object()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("_quest_ulaks");
    add_name("ulaks");
    add_name(({"weapon","pair of ulaks","pair of steel ulaks"}));
    
    add_pname(({"pairs of ulaks","pairs of steel ulaks"}));
    
    set_adj("steel");
    
    set_short("pair of steel ulaks");
    set_pshort("pairs of steel ulaks");
   
    set_long("This is a pair of swingblades, or ulaks made of plain steel "
    +". The hilts have a tight twisted steel wire wrap that gives them "
    +"an almost ornamental look. The blade bends down from the hilt "
    +"and almost wraps over the the hand before ending in a reverse "
    +"grip, the top of the blades having a nasty serrated edge and the "
    +"lower part of the blades a keen cutting edge. The blades "
    +"have ornamental copper runes engraved.\n");
    
    add_item(({"runes", "copper runes", 
    "ornamental copper runes", "ornamental runes"}),
    "The runes says: The fury is ours!\n");

    add_prop(CONT_I_WEIGHT, 3400);
    add_prop(CONT_I_HEIGHT, 25);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
}


/*
 * Function name: init_living()
 * Description  : Enables commands for the player when encountering
 *                this npc.
 */
void init()
{
    ::init();

    add_action(destroy_ulaks, "destroy");
    add_action(wield_ulaks, "wield");
}


string
query_recover()
{
    return 0;
}
