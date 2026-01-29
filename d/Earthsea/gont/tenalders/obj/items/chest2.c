inherit "/std/receptacle";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"

object scroll;
int scroll_in = 0;

void
create_receptacle()
{

    set_name("chest");
    set_adj(({"large", "cedar"}));
    set_short("large cedar chest");
    set_long(BS("The chest, which is probably used as a "+
	"foot locker, is fashioned from old cedar which gives off "+
	"a pleasant scent. There is a brass lock on it, and "+
	"it seems to be bolted down at the foot of the bed.\n", 70));
    add_item("lock",
      "The chest has a brass lock.\n");

    add_cmd_item("lock", "pick", "@@pick_lock");
    add_cmd_item("chest", "open", "@@open_chest");
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_WEIGHT, 1800);
    add_prop(OBJ_M_NO_GET, "The chest is bolted down.\n");
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
set_pick(18);
}

int
pick_lock()
{

    object tp = this_player();

    if (tp->query_skill(SS_OPEN_LOCK) > 18)
    {
	tp->catch_msg("After fumbling a bit, you manage to pick the lock!\n");
	tell_room(TO, QCTNAME(tp) + " fumbles with the lock on "+
	  "the chest.\n", ({tp}));
	tell_room(TO, "You hear a soft click.\n", ({}));
	TO->change_prop(CONT_I_LOCK, 0);
	return 1;
    }
    tp->catch_msg("You don't have the necessary skill to pick "+
      "the lock.\n");
    return 1;
}

int
open_chest()
{
    object tp = this_player();

    if (TO->query_prop(CONT_I_LOCK))
    {
	tp->catch_msg("The chest is locked.\n");
	return 1;
    }
    if (!scroll_in)
    {
	scroll_in = 1;
	seteuid(getuid(TO));
	TO->change_prop(CONT_I_CLOSED, 0);
	scroll = clone_object(EA_SCROLL);
	scroll->move(TO);
	tp->catch_msg("You open the chest.\n");
	return 1;
    }
}

