/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <stdproperties.h>
#include <macros.h>

#define TO      this_object()
#define TP      this_player()
#define ETO     environment(TO)
#define NF(xx)  notify_fail(xx + "\n")
#define MIN_DUR 4
#define MAX_DUR 2000

static object caster;
int aid=0;

public void   set_caster(object ob);
public object query_caster();
public void   remove_ear();

public void
create_creature()
{
    set_name("spirit");
    set_adj("mysterious");
    set_long("It's a faint and mysterious spirit. It has a " +
	     "human shape and it seems to watch you closely.\n");
    set_tell_active(1);
    add_prop(OBJ_I_INVIS, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (aid) remove_alarm(aid);
    remove_ear();
}

public void
set_caster(object ob)
{
    caster = ob;
}

public object
query_caster()
{
    return caster;
}

public void
catch_tell(string str)
{
    if (caster && ETO != environment(caster)) {
	tell_object(caster,  "---"+str);
    }
    ::catch_tell(str);
}

public int
query_met(mixed name)
{
    if (caster) return caster->query_met(name);
    return 0;
}

public int
query_see_blood()
{
    if (caster) return caster->query_see_blood();
    return 0;
}

public void
remove_ear()
{
    int i;
    object *all;

    if (caster) caster->catch_msg("The "+short()+" ceases to exist.\n");
    all = all_inventory(ETO);
    for (i=0; i<sizeof(all); i++) {
	if (all[i] != caster && living(all[i]) &&
	    CAN_SEE_IN_ROOM(all[i]) && CAN_SEE(all[i], TO))
            all[i]->catch_msg("The " + short() +
			      " dissolves into nothing.\n");
    }
    aid = 0;
    remove_object();
}

public void
set_duration(int t)
{
    if (t < MIN_DUR) t = MIN_DUR;
    if (t > MAX_DUR) t = MAX_DUR;
    aid = set_alarm(itof(t), -1.0, remove_ear);
}

public int
query_see_special_msg()
{
    return 1;
}
