#include "../default.h"
inherit (STD + "weapon");

#include <ss_types.h>
#include <wa_types.h>

/* this halberd has a better hit than normal. */
/* The halberd is also so big and sharp that only */
/* players with polearmskill above 50 can safely wield */
/* it. Failure will take away a little hp (they cut themselves) */

void
create_weapon()
{
    ::create_weapon();

    set_name("halberd");
    set_adj("large");
    add_adj("serrated");
    set_pname("halberds");
    set_short("large serrated halberd");
    set_pshort("large serrated halberds");
    set_long("A rather large and wickedly edged halberd that looks capable "+
      "of slicing most man-sized objects into ribbons of flesh. "+
      "On the handle of the weapon is engraved the symbol of the "+
      "trading company, A gold coin with lines radiating from it.\n");
    set_hit(29);
    set_pen(39);
    set_wf(TO);
    set_hands(W_BOTH);
    add_prop(OBJ_S_WIZINFO,
      "This halberd is so big and heavy that only players "+
      "with above 50 in polearmskill can wield it without cutting "+
      "themselves on its sharp blade.\n");
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE,700);
    add_prop(OBJ_I_WEIGHT,16000);
    add_prop(OBJ_I_VOLUME,16000);
}

mixed
wield(object what)
{
    if(TP->query_skill(SS_WEP_POLEARM) > 50)
    {
	write("You manage to wield the large serrated halberd.\n");
	say(QCTNAME(TP) + " manages to wield the large serrated halberd.\n");
	return 0;
    }
    TP->heal_hp(-random(50)-10);
    return "You clumsily attempt to wield the large serrated halberd and "+
    "only succeed in hurting yourself.\n";
}
