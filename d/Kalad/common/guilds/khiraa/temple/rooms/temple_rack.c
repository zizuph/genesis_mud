#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In the equipment storage room");
    
    set_long("\n   You have entered a small room with a low "+
    "ceiling. The walls here glow with an eerie green light. You "+
    "see a finely crafted equipment storage rack at the end of "+
    "the room. There is an inscription on the wall here.\n\n");
    add_item("inscription","The inscription is written in silver runes.\n");

    add_cmd_item("inscription","read","The inscription is written in silver "+
    "runes and reads:\n"+
    "Here, you may use the equipment rack with these commands:\n"+
    "unrack <items> -- Unrack items from the rack.\n"+
    "rack all  -- this will rack everything in your inventory.\n"+
    "rack weapons -- store only weapons.\n"+
    "rack armours -- store only armours.\n"+
    "rack other -- store anything not a weapon or armour.\n");

    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, and "+
    "they seem to glow with a magical eerie green light.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    clone_object(KHIRAA_DIR(temple/doors/rackdoor2))->move(TO); 
    clone_object(KHIRAA_DIR(temple/obj/eq_rack))->move(TO);
}
