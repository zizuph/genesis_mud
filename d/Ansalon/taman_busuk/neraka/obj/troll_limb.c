/* Ashlar, 19 Jul 97
   a limb of a troll, which will grow into a new troll after
   a short while, unless it is burned. */

inherit "/std/object";
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

object gWeapon = 0;
int gRegenAlarm = 0;
private object *gFail;

#define NERAKA_TEMP_LIMB_CHECKED    "_neraka_temp_limb_checked"

#define DEBUG(x)    (find_player("ashlar")->catch_msg("LIMB: " + x + "\n"))

create_object()
{
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "The troll limb twitches and turns so fiercly, " +
        "that you cannot get a hold of it.\n");
}

mixed
find_fire_object(object pl)
{
    object *ol;
    int i,sz;

    ol = deep_inventory(pl) + ({ E(pl) });
    sz = sizeof(ol);
    for(i=0; i<sz; i++)
        if (ol[i]->query_prop(OBJ_I_HAS_FIRE))
            return ol[i];

    return 0;
}

/*
 * Function name: do_burn
 * Description:   The player tries to burn a limb
 * Arguments:	  str - the string describing what he  wants to burn
 * Returns:	  1/0
 */
public int
do_burn(string str)
{
    object *a,fire;
    string str2, vb;

    if (this_player()->query_prop(NERAKA_TEMP_LIMB_CHECKED))
        return 0;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!strlen(str))
	    return 0;

    if(!(fire = find_fire_object(TP)))
    {
        NF("There is no fire nearby.\n");
        return 0;
    }

    seteuid(getuid(this_object()));

    gFail = ({});
    a = CMDPARSE_ONE_ITEM(str, "burn_one_thing", "burn_access");
    if (sizeof(a) > 0)
    {
	    str2 = COMPOSITE_DEAD(a);

        if (fire->query_prop(ROOM_I_IS))
        {
            say(QCTNAME(TP) + " throws " + str2 + " into the " +
                "nearby fire.\n");
            write("You throw " + str2 + " into the nearby fire.\n");
        }
        else
        {
            say(QCTNAME(TP) + " burns " + str2 + " with " + HIS(TP) +
                " " + fire->short() + ".\n");
            write("You burn " + str2 + " with your " + fire->short() + ".\n");
        }
        return 1;
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(NERAKA_TEMP_LIMB_CHECKED));
    this_player()->add_prop(NERAKA_TEMP_LIMB_CHECKED, 1);
    if (sizeof(gFail))
	    notify_fail("@@burn_fail:" + file_name(this_object()) + "@@");

    return 0;
}

public string
burn_fail()
{
    int i;
    string str;

    str = "";
    for (i = 0; i < sizeof(gFail); i++)
        str += gFail[i]->query_burn_fail();

    return str;
}

public string
query_burn_fail()
{
    return "You can't burn that.\n";
}

public int
burn_access(object ob)
{
    if ((environment(ob) == this_player() ||
	    environment(ob) == environment(this_player())) &&
	    function_exists("create_object", ob) == (NOBJ+"troll_limb"))
	return 1;

    return 0;
}

public int
burn_one_thing(object ob)
{
    if (!ob->burn_me())
    {
	    gFail += ({ ob });
	    return 0;
    }
    return 1;
}

public int
burn_me_after_delay()
{
    add_adj("burned");
    if (gWeapon)
    {
        gWeapon->move(E(TO));
        gWeapon = 0;
    }
    set_short("burned " + query_adj(0) + " " + query_name() + " of a troll");
    set_long("This is the " + short() + ".\n");
    remove_prop(OBJ_M_NO_GET);
}

public int
burn_me()
{
    /* It is no failure to burn twice */
    if (!gRegenAlarm)
        return 1;

    remove_alarm(gRegenAlarm);
    gRegenAlarm = 0;
    set_alarm(0.0, 0.0, burn_me_after_delay);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_burn,"burn");
}

void
set_limb(string limb)
{
    string *l = explode(limb, " ");

    set_name(l[1]);
    set_adj(l[0]);
    add_adj("troll");

    set_short(limb + " of a troll");
    set_long("This is the " + limb + " of a troll.\n");
}

void
set_weapon(object w)
{
    gWeapon = w;
    set_short(query_short() + ", clutching " + LANG_ADDART(w->short()));
    set_long(query_long() + "It is clutching " + LANG_ADDART(w->short()) +
        " in a tight grip.\n");
}

void
do_regen()
{
    object troll;

    setuid();
    seteuid(getuid(this_object()));

    troll = clone_object(NNPC + "troll");
    if (!troll)
        return;
    tell_room(E(TO),"With a ripping and tearing sound, the " + short() +
        " grows into " + QNAME(troll) + "!\n");
    troll->set_arms(gWeapon);
    if(gWeapon)
        gWeapon->move(troll,1);
    troll->move_living("M",E(TO));
    troll->set_regens(0);
    remove_object();
}       

void
set_regen(int time)
{
    if (!gRegenAlarm)
        gRegenAlarm = set_alarm(itof(time),0.0,do_regen);
}
