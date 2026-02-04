/*

    Modified 30 Apr 2003, by Bleys:
        - Changed to use /d/Terel/include/recover.h
        - Now includes /d/Terel/cedric/thane/defs.h
        - tried to change the old terel_defs.h to the new
            ~Terel/include/Terel.h, but the file wet the
            bed when I tried that for no reason that was
            clear to me after an hour's investigation. There
            is no apparent use of constants from the old
            file that would be necessary, but clearly
            something is fishy.
        - Changed the set_long() and added long_extra()
            so that the corpse only describes the axe when
            the axt is actually present in the corpse.
        - Added adjectives to the corpse

    Modified 18 May 2003, by Bleys:
        - Uh, not sure why I added recover.h on 30 Apr, but that
            was profoundly stupid. Corpses don't support
            some of our standard recover functionality, nor should
            they. I think I just grabbed the same includes that I
            put into the ice_axe.c without thinking. Fixed now.

*/

inherit "/std/corpse.c";
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/thane/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object

// Prototypes
string long_extra();

void
create_corpse()
{
    object ob;

    seteuid(getuid(TO()));
    set_name("corpse");
    set_short("frozen corpse of a female human");
    set_adj(({"frozen", "female", "human"}));
    set_long(BS("Lying fallen by the block of ice, this is the frozen corpse "
    + "of a female human, "
    + "obviously quite old and preserved only by the icy cold. "
    + "@@long_extra@@" + "\n"));

    change_prop(CONT_I_WEIGHT, 0);
    change_prop(CONT_I_VOLUME, 0);
    change_prop(CONT_I_MAX_VOLUME,500000);
    change_prop(CONT_I_MAX_WEIGHT,500000);
    ob = clone_object("/d/Terel/cedric/thane/ice_axe.c");
    ob->move(TO());
}

string
long_extra()
{
    if ( present(THANE_ICE_AXE_NAME) )
    {
        return "The corpse holds some sort of axe in its hand, as if " +
               "the woman died trying to chip away at the block and " +
               "its treasure.";
    }

    return "";
}
