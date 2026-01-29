 /* This is a clifftop, where players with enough skill in
air magic can float on the winds, and regain mana at intervals
as they do so. Bishop of Calia, 30.1.99. */


inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>

public string extra_desc();
public string exa_pool();
public void start_mana_alarm(object ob, object here);
public void do_mana(object ob, object here);
public int start_float(string str);
public int stop_float(string str);
public int do_dive(string str);

mapping mana_log = ([ ]);

create_room()
{
    set_short("Top of a cliff");

    set_long("You are at the top of a jagged cliff. From here" +
        " you have a good view of the surrounding area. Directly" +
        " beneath the cliff lies a bubbling hot pool, its vapors" +
        " not quite reaching up to where you are standing, maybe" +
        " a hundred feet above. To the south and east you can make" +
        " out a pond in the distance and vast forested areas." +
        " To your north the mountains continue, and to the" +
        " northeast you see something of a barren area at the foot" +
        " of the mountains. Strong winds blow here, making their" + 
        " way up the cliff face. @@extra_desc@@\n");

    add_item(({"cliff", "cliff face"}), "The cliff face is jagged,"+
        " but still fairly straight. It might be possible" +
        " to manage a clean dive into the pool below.\n");
    add_item(({"bubbling hot pool", "hot pool",
        "pool", "waters"}), "The hot springs lie far below. It's" +
        " not possible" +
        " to tell how deep it might be.@@exa_pool@@\n");
    add_item("vapors", "It's steam rising up from the bubbling" +
        " waters of the springs below.\n");
    add_item("pond", "It's partly obscured by trees, but you can" +
        " see that it's not very big.\n");
    add_item(({"forest", "forested areas"}), "Trees dominate the" +
        " the terrain to the south and east.\n");
    add_item("trees", "You can't get a good look at them from up" +
        " here, they just blend together in a mass of green and" +
        " brown.\n");
    add_item("mountains", "The mountains rise steeply to your" +
        " north. A suicidal mountain goat would have second" +
        " thoughts about trying to scale them.\n");
    add_item(({"barren area"}), "As you look at the barren" +
        " area to your northeast, you see that earth is shifting" +
        " and moving down there.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);
}

string
extra_desc()
{
    int skill = TP->query_skill(SS_ELEMENT_AIR);

    if (skill < 60)
    {
        return "";
    }
    else
    {
        return "Through your mastery of wind magic, you realize" +
            " that this place is particularly close to the plane" +
            " of elemental air. The winds would probably carry you"+
            " if you tried to float on them.";
    }
} 

string
exa_pool()
{
    object pool = find_object("/d/Calia/pond/hot_springs");
    object *pool_live;

    if (!pool)
    {
        return "";
    }    
    else
    if (pool->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        pool_live = FILTER_LIVE(all_inventory(pool));

        if(sizeof(pool_live))
        {
            return "In the hot pool you see " +
            COMPOSITE_ALL_LIVE(pool_live) + ".";
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "It's dark down there.";
    }
}


void
leave_inv(object ob, object to)
{
    if (TP->query_prop(CALIA_I_MANA_GAIN))
    {
        log_file("grotto_mana_gain", 
            capitalize(ob->query_real_name()) + " left" +
            " at " + ctime(time()) + ", having" +
            " gained: " + 
            mana_log[ob->query_real_name()] + " mana.\n");
        mana_log = m_delete(mana_log, ob->query_real_name());
    }
 
    if (living(ob))
    {
        ob->remove_prop(CALIA_I_MANA_GAIN);
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
    }
    ::leave_inv(ob, to);
}

int
start_float(string str)
{
    object here = environment(TP);

    if (TP->query_skill(SS_ELEMENT_AIR) < 60)
    {
        notify_fail("How would you do that? You can't fly.\n");
        return 0;
    }
    else 
    if (TP->query_prop(CALIA_I_MANA_GAIN) == 1)
    {
        notify_fail("You are already floating on the winds.\n");
        return 0;
    }
    else
    {
        if (str == "on the winds" || str == "on the wind" ||
            str == "on wind" || str == "on winds" ||
            str == "wind" || str == "winds")
        {
            write("With your knowledge of elemental air, you reach" +
                " out and allow the wind to gently pick you up," +
                " suspending you in mid-air. You are floating on" +
                " the wind, soft breezes gently caressing you.\n");
            tell_room(environment(TP), QCTNAME(TP) + " starts" +
                " floating on the winds.\n", TP);
            TP->add_prop(LIVE_S_EXTRA_SHORT, " is floating on the" +
                " the winds");
            TP->add_prop(CALIA_I_MANA_GAIN, 1);
            log_file("grotto_mana_gain", 
                capitalize(TP->query_real_name()) + " starts" +
                " in " + file_name(TO) + " at " +
                ctime(time()) + ".\n");
            mana_log[TP->query_real_name()] = 0;
            start_mana_alarm(TP, here);
            return 1;
        }
        else
        {
            notify_fail("Float where?\n");
            return 0;
        }
    }
}

int
stop_float(string str)
{
    if (TP->query_prop(CALIA_I_MANA_GAIN) == 0)
    {
        notify_fail("What?\n");
        return 0;
    }
    else
    {
        if (str == "floating")
        {
            write("You stop floating and gently land on the top" +
                " of the cliff.\n");
            tell_room(environment(TP), QCTNAME(TP) + " stops" +
                " floating and gently lands.\n", TP);
            log_file("grotto_mana_gain", 
                capitalize(TP->query_real_name()) + " left" +
                " at " + ctime(time()) + ", having" +
                " gained: " + 
                mana_log[TP->query_real_name()] + " mana.\n");
            mana_log = m_delete(mana_log, TP->query_real_name());
            TP->remove_prop(LIVE_S_EXTRA_SHORT);
            TP->remove_prop(CALIA_I_MANA_GAIN);
            return 1;
        }
        else
        {
            notify_fail("Stop what?\n");
            return 0;
        }
    }
}
            
void
start_mana_alarm(object ob, object here)
{
    int skill;

    if(living(ob) && environment(ob) == here &&
        ob->query_prop(CALIA_I_MANA_GAIN) == 1)
    {
        skill = ob->query_skill(SS_ELEMENT_AIR);
        
        if(skill > 59)
        {
            set_alarm(30.0, 0.0, &do_mana(ob, here));
        }
    }
}

void
do_mana(object ob, object here)
{
    int x;

    if(living(ob) && environment(ob) == here &&
        ob->query_prop(CALIA_I_MANA_GAIN) == 1)
    {
        x = F_MANA_HEAL_FORMULA(TP->query_skill(SS_SPELLCRAFT), 
            ob->query_intoxicated() / ob->intoxicated_max(), 
            ob->query_stat(SS_INT));
        mana_log[ob->query_real_name()] = 
            mana_log[ob->query_real_name()] + 2*x;
        ob->add_mana(2*x);
        if(random(5) == 0)
        {
            ob->catch_msg("The wind gently caresses you, soothing your" +
                " mind.\n");
        }
    }
    start_mana_alarm(ob, here);
}

int
do_dive(string str)
{
    int weight = TP->query_prop(OBJ_I_WEIGHT);
    string how, how2;

    if (str == "into pool" || str == "pool" || str == "into the pool")
    {
        write("You steel yourself, take aim, and elegantly" +
            " dive off the cliff and into the hot springs below.\n");
        tell_room(environment(TP), QCTNAME(TP) + " takes aim, and" +
            " elegantly dives off the cliff and into the hot" +
            " springs below.\n", TP);
        TP->move_living("M", FPATH + "hot_springs", 1);

        switch (weight)
        {
            case 0..25000:
                how = "a pitiful splash";
                how2 = "slightly wet";
                break;
            case 25001..40000:
                how = "a minor splash";
                how2 = "somewhat wet";
                break;
            case 40001..60000:
                how = "a splash";
                how2 = "dripping wet";
                break;
            case 60001..80000:
                how = "a great splash";
                how2 = "soaking wet";
                break;
            default:
                how = "a splash to end all splashes";
                how2 = "wet as a fish";
                break;
        }

        write("You land with " + how + ", unharmed.\n");
        tell_room(environment(TP), QCTNAME(TP) + " dives into the" +
            " pool from the cliff above, landing with " + how + "!"+
            " You are left " + how2 + ".\n", TP);    
  
        return 1;
    } 
    else
    {
        notify_fail("Dive where?\n");
        return 0;
    }
}

int
do_climb(string str)
{
    int skill = TP->query_skill(SS_CLIMB);

    if (str == "down" || str == "cliff" || str == "the cliff")
    {
        if (skill > 29)
        {
            TP->catch_msg("You climb down the cliff face.\n");
            tell_room(environment(TP), QCTNAME(TP) + " climbs" +
                " down the cliff.\n", TP);
            TP->move_living("M", FPATH + "cliff_halfway", 1);
            tell_room(environment(TP), QCTNAME(TP) + " arrives" +
                " climbing from above.\n", TP);
            return 1;
        }
        else
        {
            notify_fail("It looks too steep.\n");
            return 0;
        }
    }
    else 
    if (str == "mountain" || str == "mountains")
    {
        TP->catch_msg("Scorning the little voice in the back of your"+
            " head telling you that climbing further up is" +
            " impossible, you start to climb the mountain." +
            " After a few feet of climbing though, you run out" +
            " of handholds, and grudgingly lower yourself down to" +
            " the top of the cliff.\n");
        tell_room(environment(TP), QCTNAME(TP) + " tries to climb" +
            " further up the mountain, but doesn't get further" +
            " than a few feet before having to admit defeat.\n", TP);
        return 1;
    }
    else
    {
        notify_fail("Climb where?\n");
        return 0;
    }
}

void
init()
{
    add_action(start_float, "float");
    add_action(stop_float, "stop");
    add_action(do_dive, "dive");
    add_action(do_climb, "climb");
    ::init();
}