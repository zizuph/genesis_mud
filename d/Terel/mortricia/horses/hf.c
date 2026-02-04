inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <living_desc.h>
#include <formulas.h>
#include <state_desc.h>

#define TO           this_object()
#define TP           this_player()
#define ETO          environment(TO)
#define ETP          environment(TP)
#define NF(xx)       notify_fail(xx + "\n")

static object horse;

public void set_horse(object ob);
public object query_horse();

public void
create_creature()
{
    set_name("horse flea");
    set_tell_active(1);
    set_no_show();
}

public void
set_horse(object ob)
{
    horse = ob;
}

public object
query_horse()
{
    return horse;
}

void
catch_tell(string str)
{
    object rider;
    string s, dummy;

    if (horse) {
	rider = horse->query_mounted();
	s = str;
	if (sscanf(s, "Horse arrives%s", dummy) == 1) s = "";
	if (sscanf(s, capitalize(LANG_ADDART(horse->short())) +
		      " arrives%s",      dummy) == 1) s = "";
	if (rider && strlen(s)) tell_object(rider, s);
    }
    ::catch_tell(str);
}

public int
query_met(mixed name)
{
    object rider;

    if (horse) rider = horse->query_mounted();
    if (rider) return rider->query_met(name);
    return 0;
}

public int
query_see_blood()
{
    object rider;

    if (horse) rider = horse->query_mounted();
    if (rider) return rider->query_see_blood();
    return 0;
}
    
/*
 * Function name:   do_glance
 * Description:     This is the routine describing rooms to livings
 * Arguments:       brief: if true, do write the short-description,
 *                  else write the long-description.
 * Returns:         always 1.
 */
public int
do_glance(int brief)
{
    object          rider,
		    ob,
                    *ob_list,
                    *lv,
                    *dd;
    string          tmp,
                    item,
                    it,
                    *ctants;
    int             i,
		    max;

/*    PROFILE("do_glance"); */
    if (query_wiz_level())
    {
	tmp = file_name(environment());
	if (strlen(environment()->query_prop(OBJ_S_WIZINFO)))
	    tmp = "Wizinfo " + tmp;

	tell_object(this_object(), tmp + "\n");
    }

    /*
     * It is dark.
     */
    if (!CAN_SEE_IN_ROOM(this_object()))
    {
	write(LD_DARK_LONG);
	return 1;
    }

    /*
     * Describe the room and its contents.
     */
    ob = environment(this_object());

    if (!ob->check_seen(this_object()))
	write(LD_CANT_SEE);
    else
    {
	if (horse) rider = horse->query_mounted();
	if (rider && rider->query_brief())
  	{
	    write(ob->short() + ".\n");
	    if (!ob->query_noshow_obvious())
		write(ob->exits_description());
	} else
	    write(ob->long());
    }

    ob_list = all_inventory(environment(this_object()));
    lv = FILTER_OTHER_LIVE(ob_list);
    if (horse && (i = member_array(horse, lv)) >= 0)
	lv = exclude_array(lv, i, i);

    dd = FILTER_DEAD(ob_list);
    dd = FILTER_SHOWN(dd);

    item = (string) COMPOSITE_FILE->desc_dead(dd, 1);
    if (item)
	write(capitalize(item) + ".\n");

    item = (string) COMPOSITE_FILE->desc_live(lv, 1);
    if (item)
	write(capitalize(item) + ".\n");

    /*
     * Describe possible combats going on.
     */
    for (max = 0; max < sizeof(lv); max++)
    {
	ctants = map(lv[max]->query_enemy(-1), "fights", 
		    this_object(), lv[max]);
	if (sizeof(ctants))
	    ctants -= ({0});

	if (sizeof(ctants) == 1)
	    item = LD_FIGHT1(ctants[0]);
	else if (sizeof(ctants) > 1)
	    item = LD_FIGHT_MANY(ctants);
	else
	    item = 0;
	if (item)
	    write(LD_FIGHT_DESC(item, lv[max]));

    }
    return 1;
}

int query_see_special_msg() { return 1;}
