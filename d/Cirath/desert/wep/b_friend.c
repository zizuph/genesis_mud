inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "../defs.h"
#include "/d/Cirath/common/defs.h"

void
create_weapon()
{
    set_name("dagger");
    set_adj("many-bladed");
    add_adj("pronged");
    set_short("many-bladed pronged dagger");
    set_long("With numerous razor-edged blades protruding in all "
    	+"directions, this is a wicked looking weapon.  As you "
    	+"inspect it further, though, you notice the strange "
    	+"design has purpose.  The blades form an almost perfect "
    	+"barrier over your hand, which would probably greatly "
    	+"increase your ability to parry blows.  In addition to "
    	+"this, the blades look more than capable of easily "
    	+"slicing through flesh, while the prongs that protrude "
    	+"from between your fingers could easily pierce "
    	+"most of the lighter forms of armour and inflict mortal "
    	+"wounds.\n");
    set_hit(30);
    set_pen(35);
   set_wt(W_KNIFE);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I'll just keep that, sorry.");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_S_WIZINFO,"This dagger gives a bonus of +5 to "
	+"SS_PARRY when wielded.  This is a non-magical bonus "
	+"illustrating the design of the weapon, which is to "
	+"aid the wielder in parrying as well as striking.");
}


mixed
wield(object ob)
{
    object wr = TP;
    wr->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) + 5);
    write("You carefully thread your fingers through the prongs "
    	+"on the bard's friend, gripping its hilt tightly.\n");
        return 1;
}

public mixed
unwield(object wep)
{
   object wr = TO->query_wielded();
   wr->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) - 5);
   write("You slip your fingers from the grip of the bard's friend, "
   	+"unwielding the many-bladed weapon.\n");
       return 1;
}


