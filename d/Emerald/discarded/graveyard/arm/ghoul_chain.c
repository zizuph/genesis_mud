/* A ghoul chainmail - Another classic from Tulix's Armoury inc.       */
 
/* graveyard/arm/ghoul_chainmail.c  is clone by graveyard/npc/ghoul.c */
 
/* Coded 28/3/1993 */
 
inherit "/std/armour";
#include "/d/Emerald/defs.h"
#include <wa_types.h>
 
void
create_armour()
{
    set_name("chainmail");
    set_short("ghoul chainmail");
    set_long(
        "It is a chainmail that used to belong to a ghoul. The ghoul "
        +
        "no longer seems to need it. The chainmail appears to be made "
        +
        "out of iron.\n");
    set_adj("ghoul");
 
    set_ac(25); /* Just standard chainmail */
    set_am(({ -2, 3, -1}));
    set_at(A_BODY);
 
    add_prop(OBJ_I_WEIGHT, 9000); /* weight 9kg */
    add_prop(OBJ_I_VOLUME, 2000); /* volume 2l  */
}
