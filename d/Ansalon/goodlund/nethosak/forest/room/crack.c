#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_IN;
inherit "/lib/unique.c";

object corpse, weapon, scroll;

void
reset_treasure()
{
    if(!objectp(corpse) || !present(corpse))
    {
        corpse = clone_object(MOBJ + "kender");
        corpse->move(this_object());
    }
    
    if (!present(weapon, corpse))
    {
        if (!random(2))
            weapon = clone_unique(MWEP + "wound_halberd", 6);
        else
            weapon = clone_unique(MWEP + "hoopak", 6);
        
        /* These are fairly common but no always here */
        if (!objectp(weapon))
            weapon = clone_unique(MWEP + "spear", 25);

        if (objectp(weapon))
            weapon->move(corpse, 1);
    }

    if (!present(scroll, corpse))
    {
       scroll = clone_object("/d/Krynn/common/scrolls/blur_scroll");
       scroll->move(corpse, 1);
    }

}

void
create_mithas_room()
{
    set_short("Small stone crack");
    set_long("@@long_descr"); 

    add_exit(MROOM + "main_cave","out",0);

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_I_LIGHT,0);  
}

string
long_descr()
{ 
    return
        "You are standing inside small stone crack. It's extremely tight in "+
        "here, and you begin to get a claustrophobic feeling. A few thin roots "+
        "twists themselves down from above.\n";
}


