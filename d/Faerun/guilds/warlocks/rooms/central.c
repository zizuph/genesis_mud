/* /d/Faerun/guilds/warlocks/rooms/central.c
 *
 * Room in the guildhall.
 *
 * Nerull 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;


string tapestry()
{
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        return "The large tapestry hangs on the south wall, covering a "
        +"portion "
        +"of that wall from ceiling to floor. It seems quite old and in "
        +"your mind it resembles a gate or a portal to somewhere else. Maybe "
        +"you should go 'south', and see?\n";
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        return "The large tapestry hangs on the south wall, covering a "
        +"portion "
        +"of that wall from ceiling to floor. It seems quite old and in "
        +"your mind it resembles a gate or a portal to somewhere else. Maybe "
        +"you should go 'south', and see?\n";
    }
    
    return "The large tapestry hangs on the south wall, covering a portion "
    +"of that wall from ceiling to floor. It seems quite old and doesn't "
    +"depict anything else but random colour patterns. Some kind "
    +"of art maybe?\n";
}


public int
exit_guild()
{
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        write("\n\nYou enter the large tapestry as it were a "
        +"magical door, and end up somewhere on the other side!\n\n");
        
        return 0;
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        write("\n\nYou enter the large tapestry as it were a "
        +"magical door, and end up somewhere on the other side!\n\n");
        
        return 0;
    }
      
    write("There is no obvious exit south.\n");
        
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    object board;

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Somewhere in a large rough claystone cave");
    
    set_long("Somewhere in a large rough claystone cave. Shadows "
    +"flicker in unison with the light emitted from "
    +"the demon-shaped iron sconces hanging from the ceiling. Judging "
    +"by the marine fossils embedded everywhere, you believe this "
    +"particular place was once submerged in water for an extended "
    +"period of time. In close proximity to the southwestern wall, "
    +"you see a secured bulletin board and a leather book that floats "
    +"in mid air. A large tapestry decorates the south wall.\n");
    
    add_item(({"cave"}),
    "This cave is made of regular claystone and has several exits to "
    +"adjacent rooms. You think it's a result of natural erosion, and "
    +"the walls here are filled with marine fossils.\n");
    
    add_item(({"ceiling", "roof"}),
    "The claystone ceiling is uneven and jagged, but has no other apparent "
    +"visible features except flickering shadows created by the light.\n");
    
    add_item(({"wall", "walls"}),
    "The claystone walls are uneven, jagged and filled with tiny marine "
    +"fossils. A secured bulletin board and a floating leather book are "
    +"next to the southwestern part of the wall here.\n");
    
    add_item(({"ground", "floor"}),
    "The claystone ground is flat and dusty. You notice some footprints "
    +"heading in various directions in the cave.\n");
    
    add_item(({"fossils", "marine fossils"}),
    "Perpetually petrified, these small strange creatures once roamed the "
    +"ocean floor eons ago. Strangely, you can swear that some of these "
    +"fossils resemble the shape of the immortals like Gorboth, Mercade "
    +"and Stern, or it's just your mind playing tricks with you. Regardless, "
    +"you think this part of the cave complex once was submerged "
    +"in water.\n");
    
    add_item(({"footprints"}),
    "You believe it's footprints from various members of this "
    +"secret establishment. They head in virtually every direction.\n");
    
    add_item(({"shadows", "flickering shadows"}),
    "The light emitted from the demon-shaped iron sconces create shadows on "
    +"the uneven jagged surface of the ceiling and walls here. They dance "
    +"with the movement of the flames from the sconces.\n");
    
    add_item(({"light"}),
    "The light emitted from the demon-shaped iron sconces are a product of "
    +"the natural combustion of air and oil. It illuminates the area quite "
    +"efficiently, and creates many flickering shadows in the process.\n");
    
    add_item(({"demon-shaped iron sconces", "iron sconces", 
    "demon-shaped sconces", "sconce", "sconces"}),
    "The iron sconces line the top of the walls and they are shaped like "
    +"the pit-fiends of Baator. Flames emitting light spill out from "
    +"the eyes and mouth of the pit-fiends, illuminating the cave.\n");
        
    add_item(({"tapestry", "large tapestry"}), tapestry);
    
    if (!objectp(board))
    {
        board = clone_object("/std/board");
        board->set_board_name(WARLOCK_BOARDS_DIR + "guild");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_short("bulletin board");
        board->set_long("This is a wooden discussion board set firmly " +
            "against the southwestern wall. It is where warlocks can post " +
            "notes of their travels, and anything else they deem necessary " +
            "for others to know of.\n\n");
        board->move(this_object());
    }
    
    room_add_object(WARLOCK_OBJ_DIR + "patron_book");

    add_exit(WARLOCK_ROOMS_DIR + "patron", "north");
    add_exit(WARLOCK_ROOMS_DIR + "hall03", "east");
    add_exit(WARLOCK_ROOMS_DIR + "hall02", "west");
    add_exit(WARLOCK_ROOMS_DIR + "join", "south", exit_guild,0,1);

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
            +"if something in the teleportation chamber to the north beckons you!\n");
            
            return;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers, as "
            +"if something in the teleportation chamber to the north beckons you!\n");
            
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
