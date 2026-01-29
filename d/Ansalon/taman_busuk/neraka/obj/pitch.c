/* Ashlar, 12 Jul 97 - purning pitch */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit "/std/object";

int burn_alarm;

#define PERIOD  5.0
#define BURN_DAM    (100 + random(100))

void
create_object()
{
    set_name("pitch");
    set_short("burning pitch");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);

    burn_alarm = 0;
    set_no_show();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (env->query_prop(ROOM_I_IS))
        env->add_my_desc("The ground is covered with burning pitch.\n");
}

void
leave_env(object env, object to)
{
    ::leave_env(env,to);
    if (env->query_prop(ROOM_I_IS))
        env->remove_my_desc();
}

int
query_obj_ac(object ob)
{
    return ob->query_ac();
}

void
do_burn(int duration)
{
    object *list,l,*arm;
    int i,j,k,dam,res,phurt,*ac;
    string *s;

    if (duration <= 0)
    {
        tell_room(E(TO), "The pitch stops burning and leaves a few smoking " +
            "remains.\n");
        remove_object();
        return;
    }

    list = FILTER_LIVE(all_inventory(E(TO)));
    for (i=0; i<sizeof(list); i++)
    {
        l = list[i];
        res = l->query_magic_res(MAGIC_I_RES_FIRE);
        if (res>100)
            res = 100;
        if (res < 0)
            res = 0;
        dam = (BURN_DAM * (100 - res)) / 100;
        arm = l->query_armour(-1);
        if (sizeof(arm))
        {
            ac = map(arm,query_obj_ac);
            for (j=0,k=0; j < sizeof(ac); j++)
                k += ac[j];
            if (k > 1000)
                k = 1000;
            dam = (dam * (1000 - k)) / 1000;
        }
        if (l->query_hp())
            phurt = (dam * 100) / l->query_hp();
        else
            phurt = 100;
        switch (phurt)
        {
            case 0:
                s = ({ "The flames of the burning pitch do not hurt you " +
                    "at all.", QCTNAME(l) + " does not seem affected by " +
                    "the flames." });
                break;
            case 1..3:
                s = ({ "The smoldering flames of the burning pitch burn " +
                    "you slightly.", QCTNAME(l) + " seems slightly " +
                    "hurt by the flames." });
                break;
            case 4..9:
                s = ({ "The flames of the burning pitch burn you.",
                    QCTNAME(l) + " seems to be hurt by the flames." });
                break;
            case 10..20:
                s = ({ "The hot flames of the burning pitch burn you " +
                    "rather bad.", QCTNAME(l) + " is hurt rather bad by " +
                    "the flames." });
                break;
            case 21..45:
                s = ({ "You are badly burned by the flames of the " +
                    "burning pitch.", QCTNAME(l) + " is very badly hurt by " +
                    "the hot flames." });
                break;
            case 46..99:
                s = ({ "You are incinerated by the hot flames of the " +
                    "burning pitch.", QCTNAME(l) + " writhes in agony as " +
                    HE(l) + " is incinerated by the flames." });
                break;
            default:
                s = ({ "You scream in terrible agony as the incinerating " +
                    "fire of the burning pitch burns you to death.",
                    QCTNAME(l) + " screams in terrible agony as the fire " +
                    "consumes " + HIS(l) + " flesh and burns " + HIM(l) +
                    " to death." });
        }

        l->catch_msg(s[0]+"\n");
        if (l->query_wiz_level())
            l->catch_msg("DAM: " + dam + " PHURT: " + phurt + "\n");
        /* standing around in fire is panicking */
        l->add_panic(phurt);
        tell_room(E(TO), s[1]+"\n", l);
        l->reduce_hit_point(dam);
        if (l->query_hp() < 0)
        {
            l->set_hp(0);
            l->do_die(TO);
        }
    }

    burn_alarm = set_alarm(PERIOD, 0.0, &do_burn(duration-1));
}

int
start_burning(int duration)
{
    if (burn_alarm)
        return 0;

    tell_room(E(TO),
        "\nA cask of burning pitch hits the ground and explodes, making " +
        "the ground a raging inferno.\n\n");
    do_burn(duration);
    return 1;
}

