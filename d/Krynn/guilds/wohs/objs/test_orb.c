/* An orb for refreshing memorisation times, 
 * used for testing, and the Test - Arman 2017     */


inherit "/std/object";
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"

public void
create_object()
{
    set_name("orb");
    add_name("_wohs_test_orb");
    set_short("swirling crimson orb");
    set_adj(({"swirling","crimson"}));
    set_long("This swirling crimson orb sits on an elegant silver " +
        "frame. Any Wizard who rubs it will have their mind refreshed, " +
        "allowing them to re-memorise spells.\n");

    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_GET, "The orb is too big to pick up.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This orb is magical, allowing a mage " +
        "who rubs it to be mentally refreshed, and able to re-memorise " +
        "spells.\n", 75 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}

int 
rub(string str)
{

    object * active_effect_spells = filter(TP->query_prop(LIVE_O_MAINTAINED_EFFECTS),
                              &->query_spell_effect_object());

    if (!pointerp(active_effect_spells))
    {
        active_effect_spells = ({ });
    }
    else
    {        
        active_effect_spells -= ({ 0 });
    }

    // write("Active spells: " +sizeof(active_effect_spells)+ ".\n");

    if (sizeof(active_effect_spells) > 0)
    {
         write("You rub the orb, yet feel the spells you are " +
             "maintaining interfere with the magic of the orb. Dispel " +
             "your active spells and try again.\n");
         say(QCTNAME(TP)+ " rubs the swirling crimson orb.\n");
         return 1;
    }

    if ((str=="orb")||(str=="crimson orb")) 
    {
         write("You rub the orb and feel mentally refreshed and able " +
             "to re-memorise spells.\n");
         say(QCTNAME(TP)+ " rubs the swirling crimson orb.\n");
         WOHS_MANAGER->clear_memorise_time(TP);
         return 1;
    }

    notify_fail("Rub what?\n");
    return 0;
}

void
init()
{
   ::init();
   add_action(rub, "rub");

}
