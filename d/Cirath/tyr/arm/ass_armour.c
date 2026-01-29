inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("suit");
    add_name("mail");
    set_short("black shadow suit");
    set_long("This looks to be a one piece suit crafted from shadows. "
	+"Though it looks rather insubstantial, to the touch it feels like "
	+"a padded suit of leather armour, or a blackened suit of "
	+"fine elven chain mail.  It weighs almost nothing, and you "
	+"imagine that by putting it on, you would barely be visible.\n");
    set_adj("black");
    add_adj("shadow");

    set_ac(35);
    set_am(({1,1,1}));
    set_at(A_BODY|A_HEAD|A_LEGS|A_ARMS);

   add_prop(OBJ_I_WEIGHT, 6000);
  add_prop(OBJ_I_VOLUME, 4000);
    set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) + 20);
    wr->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) + 20);
    wr->catch_tell("You slip into the dark suit.\n");
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You quickly remove the dark suit.\n");
    wr->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) -20);
    wr->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) -20);
    return 1;
}


