inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("mail");
    add_name("suit");
   set_adj("shimmering");
   add_adj("mithril");
   set_short("shimmering suit of mithril mail");
   set_long("This is a suit of fine mithril mail.  The mail is "
	+"made of small overlapping leaf shaped scales.  It is "
	+"light and thin enough to fit under your clothes without "
	+"anyone noticing it.  It is beautifully worked and must "
	+"be worth a fortune.\n");
   set_ac(45);
   set_at(A_BODY|A_ARMS);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "Protection" }));
   add_prop(MAGIC_AM_ID_INFO, ({"It has been enhanced to provide "
	+"better protection.\n",5,}));
   add_prop(OBJ_S_WIZINFO, "This suit of mail has been enchanted "
	+"so that it provides better protection.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_I_WEIGHT,5000);
   set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->catch_tell("You put on the shimmering suit of mithril mail, "
	+"which covers both your arms and body.\n");
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You remove the shimmering suit of mail.\n");
    return 1;
}


