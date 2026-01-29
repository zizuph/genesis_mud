inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define DOWN_STREAM	(ITH_DIR + "emyn-arnen/rivr3")
#define SWIMMING	"_swimming"

int     current_alarm = 0;

void
create_room()
{
    set_short("Swimming in the rushing water of a river");
    set_long(BSN(
        "The river is coming with a swift current out of a culvert "
      + "under a large building. West of here it makes a gentle bend. "
      + "To the north is a shallow bank. "
      + "The water is too deep and rushing too fast to stand "
      + "in it. You are carried away with the current."));
    add_item(({"bank", "banks", "river", "water", }), BSN(
        "The water is rushing out of the culvert. You are "
      + "fighting to keep you head over water and have no time to "
      + "examine the river or the banks any closer."));
    add_item(({"culvert", "duct", }), BSN(
        "The current that carried you out of the culvert prevents "
      + "from throwing a leisurely look backwards. You have to fight "
      + "for you life!"));
    add_item(({"bend"}), BSN(
        "The river makes a gentle bend west of here. If you do not "
      + "manage to reach the bank here, chances are you will be "
      + "thrown onto the shallow bank at the bend."));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, -10);

    add_exit(ITH_DIR + "emyn-arnen/bank2", "north", 0, 5);
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
            ob->move(DOWN_STREAM);
            tell_room(TO, "The current carries the "+ob->short()+
                "into the duct.\n");
        }
        return;
    }
    if (!current_alarm)
        current_alarm = set_alarm(4.0, 3.0, "current");
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
                obs[i]->add_fatigue(-30);
                ff = 2;
                break;
            case 4..20:
                obs[i]->catch_msg("You are drifting in the rapid " +
                    "current, trying to keep your head above the water.\n");
                tell_room(QCTNAME(obs[i])+" is fighting the current.\n",
                    obs[i]);
                obs[i]->add_fatigue(-20);
                ff = 4;
                break;
            case 21..100:
                obs[i]->catch_msg("You are swimming with the current.\n");
                tell_room(QCTNAME(obs[i])+" is swimming with the " +
                    "current.\n", obs[i]);
                obs[i]->add_fatigue(-10);
                ff = 6;
                break;
            default:
                break;
        }
        if (!(obs[i]->query_fatigue()) || !random(ss+1))
        {
            obs[i]->catch_msg("You are drowning!\n");
            obs[i]->heal_hp(- (obs[i]->query_max_hp()/ff/2) );
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
            obs[i]->move_living("with the current", DOWN_STREAM);
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
