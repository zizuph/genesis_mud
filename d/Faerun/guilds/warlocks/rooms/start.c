/* /d/Faerun/guilds/warlocks/rooms/start.c
 *
 * Start room in the warlock guildhall.
 *
 * Nerull, 2018
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);

    set_short("In a large claystone sleeping chamber");
    
    set_long("In a large claystone sleeping chamber. Rows of simple "
    +"wooden cots are scattered about in random patterns on the "
    +"rugged floor, as if nobody really cares much about concepts such "
    +"as tidiness and symmetry. A single iron brazier hangs from "
    +"the claystone ceiling, providing some soft light and "
    +"lulling shadows for the weary warlock. Various murals "
    +"decorate the smooth claystone walls that helps creating "
    +"a rather cozy atmosphere. If you wish to rest here, you "
    +"may do so when you <start here>.\n");
    
    add_item(({"ceiling", "roof"}),
    "The claystone ceiling is smooth and symmetrical. Various "
    +"murals decorate it, giving the large chamber a slightly more "
    +"relaxed atmosphere than normal. An iron brazier hangs from "
    +"the ceiling by a small iron chain.\n");
    
    add_item(({"mural", "murals"}),
    "There are various murals. Some depict sceneries from deep green "
    +"forests, others depict bright lakes of fire and skies full of "
    +"bright and black stars. Looking at them makes you strangely more "
    +"tired and relaxed.\n");
    
    add_item(({"wall", "walls"}),
    "The walls here are smooth and featureless. There is nothing interesting "
    +"about them as far as you can tell.\n");
    
    add_item(({"blanket", "blankets"}),
    "The blankets you see in the cots are made of linen and dyed black. They "
    +"should keep a weary warlock warm during sleep.\n");
    
    add_item(({"warlocks", "sleeping warlocks"}),
    "Some of the cots are occupied by other sleeping warlocks, weary of "
    +"their recent travels.\n");
    
    add_item(({"ground", "floor"}),
    "The ground is covered with comfortable rugs. You also see "
    +"some clothes lying astray.\n");
    
    add_item(({"clothes", "floor", "sock", "underwear"}),
    "Some warlocks are less tidy than others, hence the occasional sock and "
    +"underwear lying around, cluttering the room.\n");
    
    add_item(({"rug", "rugs"}),
    "Several rugs carpet the floor, almost overlapping each other. They are "
    +"soft to the touch, looks comfortable and fasionable crimson in "
    +"appearance.\n");
    
    add_item(({"light", "soft light"}),
    "The hanging iron brazier gives off a soft light. It's not bright "
    +"enough to disturb those who are sleeping.\n");
    
    add_item(({"shadows", "lulling shadows"}),
    "The shadows created by the soft light are rather lulling. Their "
    +"soft movement makes you rather sleepy.\n");
    
    add_item(({"simple wooden cots", "wooden cots", "cots", "cot"}),
    "The chamber is filled with these simple improvised beds. They are made "
    +"from dried branches and ropes, and is just a few inches above the "
    +"ground. Some are barren, others have blankets in them. Several of "
    +"the cots are occupied by other sleeping warlocks.\n");  

    add_item(({"brazier", "iron brazier", "chain", "iron chain"}),
    "The iron brazier is square shaped and made of cast iron. It hangs "
    +"from the ceiling, attached to a small iron chain that is anchored "
    +"to the ceiling. The iron brazier gives off a warm glow and heat "
    +"the room.\n");
        
    add_exit(WARLOCK_ROOMS_DIR + "racks", "north");
    add_exit(WARLOCK_ROOMS_DIR + "hall03", "west");
    
    room_add_object(WARLOCK_GUILD_DIR +"obj/cupboard");
    room_add_object(WARLOCK_GUILD_DIR +"obj/cabinet");

    reset_room();
}


void
reset_room()
{
}


int
do_start(string str)
{
    if (str != "here")
    {

        write("<start here>, perhaps?\n");

        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        this_player()->set_default_start_location(file_name(this_object()));

        write("From now on, you will awake here when entering the game.\n");

        return 1;
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        this_player()->set_default_start_location(file_name(this_object()));

        write("From now on, you will awake here when entering the game.\n");

        return 1;
    }

    write("You are not a member of this guild!\n");
    return 1;
}


void init()
{
    ::init();

    add_action(do_start, "start");
}