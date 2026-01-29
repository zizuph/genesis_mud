inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define DOWN_STREAM	(ITH_DIR + "emyn-arnen/bank1")
#define SWIMMING	"_swimming"

int     current_alarm = 0;

void
create_room()
{
    set_short("Swimming in the rushing water of a river");
    set_long(BSN(
        "The river is runing west with a swift current. "
      + "It makes a gentle bend here. "
      + "To the north is a shallow bank. "
      + "The water is too deep and rushing too fast to stand "
      + "in it."));
    add_item(({"bank", "banks", "river", "water", }), BSN(
        "You are fighting to keep you head over water and have no time to "
      + "examine the river or the banks any closer."));
    add_item(({"bend"}), BSN(
        "The river makes a gentle bend here. If you do not "
      + "manage to reach the bank alone, you might be lucky and you will be "
      + "thrown onto the shallow bank by the current."));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, -10);

    add_exit(ITH_DIR + "emyn-arnen/bank1", "north", 0, 5);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob))
        return;

    if (!living(ob))
    {
        if (ob->query_prop(OBJ_I_WEIGHT) > ob->query_prop(OBJ_I_VOLUME))
        {
            ob->set_noshow(1);
            tell_room(TO, "The "+ob->short()+" quickly drops to the " +
                "bottom of the river.\n");
        }
        else
        {
            tell_room(TO, "The current carries the "+ob->short()+
                "into the duct.\n");
            ob->remove_object();
        }
        return;
    }
    if (!current_alarm)
        current_alarm = set_alarm(5.0, 4.0, "current");
}

int
filter_living(object x) { return living(x); }

void
current()
{
    int     i,
            ff,
            so,
            ss;
    object *obs = all_inventory(TO);

    obs = filter(obs, "filter_living", TO);

    if (!(so = sizeof(obs)))
    {
        remove_alarm(current_alarm);
        current_alarm = 0;
        return;
    }

    FIX_EUID

    for (i = 0; i < so; i++)
    {
        switch((ss = obs[i]->query_skill(SS_SWIM)))
        {
            case 0..3:
                obs[i]->catch_msg("You are drifting helplessly in " +
                    "rapid current, trying to keep your head above " +
                    "the water.\n");
                tell_room(QCTNAME(obs[i])+" is desperately fighting " +
                    "the current.\n", obs[i]);
                obs[i]->add_fatigue(-20);
                ff = 2;
                break;
            case 4..20:
                obs[i]->catch_msg("You are drifting in the rapid " +
                    "current, trying to keep your head above the water.\n");
                tell_room(QCTNAME(obs[i])+" is fighting the current.\n",
                    obs[i]);
                obs[i]->add_fatigue(-10);
                ff = 4;
                break;
            case 21..100:
                obs[i]->catch_msg("You are swimming with the current.\n");
                tell_room(QCTNAME(obs[i])+" is swimming with the " +
                    "current.\n", obs[i]);
                obs[i]->add_fatigue(-5);
                ff = 6;
                break;
            default:
                break;
        }
        if (!(obs[i]->query_fatigue()) || !random(ss+1))
        {
            obs[i]->catch_msg("You are drowning!\n");
            obs[i]->heal_hp(- (obs[i]->query_max_hp()/ff/3) );
        }
        if (obs[i]->query_hp() <= 0)
        {
            obs[i]->catch_msg("You lose your fight against " +
                "the rapid current and are pulled under.\n");
            tell_room(TO, QCTNAME(obs[i])+" is pulled under by the " +
                "rapid current and drowns.\n", obs[i]);
            obs[i]->do_die(TO);
            return;
        }
        if (obs[i]->query_prop(SWIMMING) > 3)
        {
            obs[i]->move_living("onto the bank", DOWN_STREAM);
            obs[i]->remove_prop(SWIMMING);
        }
        else
            obs[i]->add_prop(SWIMMING, obs[i]->query_prop(SWIMMING)+1);
    }
}

string
do_search(object ob, string str)
{
    return "You cannot search anything while fighting the rapid current.\n";
}
