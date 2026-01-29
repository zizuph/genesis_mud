inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"

#define DOWN_STREAM	(ITH_DIR + "emyn-arnen/palace/in_well")

int     current_alarm = 0;

void
create_room()
{
    set_short("In a river in Emyn Arnen");
    set_long(BSN("The river is too deep to stand in it. It is flowing " +
       "rather rapidly towards the thick iron rods which block the " +
       "duct leading into the basement of the building."));
  add_item(({"building", "large building", "palace"}), BSN(
    "The large building is almost a small palace. It rises high " +
    "above you. From your position in the river, you cannot see " +
    "much more than the part of the fundaments right in front of " +
    "you in which there is the opening into which the river disappears."));
  add_item(({"duct", "opening", }), BSN(
    "The small river is several feet across and it must be quite deep. " +
    "It is quickly disappearing into the duct under the building. " +
    "Probably the river was meant to supply the inhabitants of the " +
    "building with water. You can see that at the entrance of the duct " +
    "several thick iron rods prevent anything larger than a small " +
    "animal from entering the building through the water."));
  add_item(({"river", "bank"}), BSN(
    "The small river is several feet across and it must be quite deep, " +
    "since you cannot stand in the water. " +
    "The river is quickly disappearing into the duct under the building. " +
    "The bank of the river is rather low, so that it might be possible " +
    "to climb out of the river here."));
  add_item(({"rods", "iron rods"}), BSN(
    "The iron rods block the entrance into the duct for driftwood, " +
    "large animals, and enemies of the inhabitants of the building " +
    "alike. They look extremly thick and strong."));
    
  add_exit(ITH_DIR + "emyn-arnen/rrd1", "north", "@@leave_river@@", 5);
}

void
init()
{
    ::init();
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
        current_alarm = set_alarm(4.0, 8.0, "current");
}

int
filter_living(object x) { return living(x); }

void
current()
{
    int     i,
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
                if (!(obs[i]->query_fatigue()) || !random(ss+1))
                {
                    obs[i]->catch_msg("You are drowning!\n");
                    obs[i]->heal_hp(- (obs[i]->query_max_hp()/2) );
                }
                break;
            case 4..20:
                obs[i]->catch_msg("You are drifting in the rapid " +
                    "current which threatens to smash you against " +
                    "the iron rods at the opening of the duct.\n");
                tell_room(QCTNAME(obs[i])+" is fighting the current.\n",
                    obs[i]);
                obs[i]->add_fatigue(-30);
                if (!(obs[i]->query_fatigue()) || (!random(ss/2 + 1)))
                {
                    obs[i]->catch_msg("The current throws you against " +
                        "the iron rods. You are hurt!\n");
                    obs[i]->heal_hp(- (obs[i]->query_max_hp()/4) );
                }
                break;
            case 21..100:
                obs[i]->catch_msg("You are swimming against the current, " +
                    "trying to prevent being thrown against the iron " +
                    "rods at the opening of the duct.\n");
                tell_room(QCTNAME(obs[i])+" is swimming against the " +
                    "current.\n", obs[i]);
                obs[i]->add_fatigue(-20);
                if (!(obs[i]->query_fatigue()) || (!random(ss/4 + 1)))
                {
                    obs[i]->catch_msg("The current throws you against " +
                        "the iron rods. You are hurt!\n");
                    obs[i]->heal_hp(- (obs[i]->query_max_hp()/6) );
                }
                break;
            default:
                break;
        }
        if (obs[i]->query_hp() <= 0)
        {
            obs[i]->catch_msg("You lose your fight against " +
                "the rapid current and are pulled under.\n");
            tell_room(TO, QCTNAME(obs[i])+" is pulled under by the " +
                "rapid current and drowns.\n", obs[i]);
            obs[i]->do_die(TO);
        }
    }
}

int
leave_river()
{
    if (TP->query_fatigue() < 10)
    {
        write(BSN("You try to climb out of the river, but exhausted " +
            "as you are, you slip and fall back into the water."));
        return 1;
    }
    if ((TP->resolve_task(TASK_ROUTINE, ({TS_DEX, TS_STR}))) <= 0)
    {
        write(BSN("When you try to climb out of the river, you slip " +
            "and fall back into the water."));
        return 1;
    }
    write("With some effort, you manage to climb out of the river.\n");
    TP->add_fatigue(-10);
    return 0;
}
