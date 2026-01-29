inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define DOWN_STREAM	(ITH_DIR + "emyn-arnen/rivr2")
#define SWIMMING	"_swimming"

int     current_alarm = 0;

void
create_room()
{
    set_short("Swimming in the rushing water of an underground duct");
    set_long(BSN("The water is too deep and rushing too fast to stand "
      + "in it. You are carried away with the current."));
    add_item(({"duct", "water", }), BSN(
        "The water is rushing through the narrow duct. You are "
      + "fighting to keep you head over water and have no time to "
      + "examine the duct any closer."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, -10);
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
                obs[i]->add_fatigue(-40);
                ff = 2;
                break;
            case 4..20:
                obs[i]->catch_msg("You are drifting in the rapid " +
                    "current, trying to keep your head above the water.\n");
                tell_room(QCTNAME(obs[i])+" is fighting the current.\n",
                    obs[i]);
                obs[i]->add_fatigue(-30);
                ff = 4;
                break;
            case 21..100:
                obs[i]->catch_msg("You are swimming with the current, " +
                    "trying to prevent being thrown against the walls.\n");
                tell_room(QCTNAME(obs[i])+" is swimming with the " +
                    "current.\n", obs[i]);
                obs[i]->add_fatigue(-20);
                ff = 6;
                break;
            default:
                break;
        }
        if (!(obs[i]->query_fatigue()) || !random(ss+1))
        {
            obs[i]->catch_msg("You are drowning!\n");
            obs[i]->heal_hp(- (obs[i]->query_max_hp()/ff) );
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
        if (obs[i]->query_prop(SWIMMING))
        {
            obs[i]->move_living("with the current", DOWN_STREAM);
            obs[i]->remove_prop(SWIMMING);
            obs[i]->catch_msg("The current carries you out "
              + "of the building.\n");
        }
        else
            obs[i]->add_prop(SWIMMING, 1);
    }
}

string
do_search(object ob, string str)
{
    return "You cannot search anything while fighting the rapid current.\n";
}
