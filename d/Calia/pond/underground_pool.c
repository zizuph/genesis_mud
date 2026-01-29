/* This is an underground pool, where players with enough skill in
water magic can float, and regain mana at intervals
as they do so. Bishop of Calia, 5.2.99. */


inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>

public string extra_desc();
public string ledge();
public void start_mana_alarm(object ob, object here);
public void do_mana(object ob, object here);
public int start_float(string str);
public int stop_float(string str);
public int do_swim(string str);
public int do_climb(string str);

mapping mana_log = ([ ]);

create_room()
{
    set_short("Underground pool");

    set_long("You are at the surface of an underground pool. The" +
        " water is cool, but not freezing. It's quiet here, and" +
        " the gentle sound of the water lapping around you echoes" +
        " off the cave walls creating an eerie effect. Daylight" +
        " streams into the cave through a hole a long way up." +
        " At one end of the cave there is a ledge, and behind" +
        " it a corridor leads further into the mountain." +
        " @@extra_desc@@\n");

    add_item(({"underground pool", "pool"}), "The surface is only" +
        " broken by the small" +
        " ripples your movements make.\n");
    add_item("water", "The water is probably fairly deep, as you" +
        " can't see the bottom.\n");
    add_item(({"cave walls", "walls"}), "The walls of the cave are" +
        " smooth.\n");
    add_item("dayligh", "It's not a great deal of light that" +
        " reaches the pool, but enough to see clearly.\n");
    add_item("hole", "The hole doesn't look very big, it's at" +
        " least a hundred feet above.\n");
    add_item("ledge", "@@ledge@@\n");
    add_item("corridor", "The corridor is big enough that a large" +
        " human could walk without crouching down.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_exit(FPATH + "env_und_pool","_no_exit_ ",1, 1, 1);
}

string
extra_desc()
{
    if (TP->query_skill(SS_ELEMENT_WATER) > 59)
    {
        return "You feel that this place is particularly close" +
            " to the plane of elemental water. You think the water" +
            " would support you if you tried to float.";
    }
    else
    {
        return "";
    }
}

string
ledge()
{
    object ledge = find_object("/d/Calia/pond/env_und_pool");
    object *ledge_live;

    if (!ledge)
    {
        return "The ledge looks broad and solid.";
    }    
    else
    if (ledge->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        ledge_live = FILTER_LIVE(all_inventory(ledge));

        if(sizeof(ledge_live))
        {
            return "You see " +
            COMPOSITE_ALL_LIVE(ledge_live) + " standing on the" +
            " broad and solid ledge.";
        }
        else
        {
            return "The ledge looks broad and solid.";
        }
    }
    else
    {
        return "The ledge is cast in darkness.";
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

    if (TP->query_skill(SS_ELEMENT_WATER) < 60)
    {
        notify_fail("You try to float gently on the water, but end" +
            " up flailing wildly instead.\n");
        tell_room(environment(TP), QCTNAME(TP) + " tries to float" +
            " on the water, but ends up flailing wildly instead.\n",
            TP);
        return 0;
    }
    else
    if (TP->query_prop(CALIA_I_MANA_GAIN))
    {
        notify_fail("You are already floating on the water.\n");
        return 0;
    }
    else
    {
        write("With your knowledge of elemental water, you" +
            " allow yourself to be carefully lifted up by the" +
            " current. You are floating on the water," +
            " the gentle rocking soothing your soul.\n");
        tell_room(environment(TP), QCTNAME(TP) + " starts" +
            " floating on the water.\n", TP);
        TP->add_prop(LIVE_S_EXTRA_SHORT, " is floating on the" +
            " the water");
        TP->add_prop(CALIA_I_MANA_GAIN, 1);
        log_file("grotto_mana_gain", 
            capitalize(TP->query_real_name()) + " starts" +
            " in " + file_name(TO) + " at " +
            ctime(time()) + ".\n");
        mana_log[TP->query_real_name()] = 0;
        start_mana_alarm(TP, here);
        return 1;
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
            write("You stop floating and start treading water.\n");
            tell_room(environment(TP), QCTNAME(TP) + " stops" +
                " floating and starts treading water.\n", TP);
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
        skill = ob->query_skill(SS_ELEMENT_WATER);
        
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
            TP->query_intoxicated() / TP->intoxicated_max(), 
            TP->query_stat(SS_INT));
        mana_log[ob->query_real_name()] = 
            mana_log[ob->query_real_name()] + 2*x;
        ob->add_mana(2*x);
        if(random(5) == 0)
        {
            ob->catch_msg("The water laps gently around you," +
                " soothing your mind.\n");
        }
    }
    start_mana_alarm(ob, here);
}

int
do_climb(string str)
{
    if (str == "out" || str == "out of pool" 
        || str == "out of the pool" || str == "ledge"
        || str == "onto ledge")
    {
        write("You climb out of the pool.\n");
        tell_room(environment(TP), QCTNAME(TP) + " climbs out of" +
            " the pool.\n", TP);
        TP->move_living("M", FPATH + "env_und_pool", 1);
        tell_room(environment(TP), QCTNAME(TP) + " arrives climbing" +
            " out of the pool.\n", TP);
        return 1;
    }
    else
    {
        notify_fail("Climb where? Out of the pool perhaps?\n");
        return 0;
    }
}

int
do_swim(string str)
{
    int skill = TP->query_skill(SS_SWIM);

    if (str == "down" || str == "into depths" 
        || str == "into the depths")
    {
        if (TP->query_prop(MAGIC_I_BREATH_WATER) > 39)
        {
            write("You start to swim into the depths of the" +
                " underground pool and through the hole in" +
                " the bottom. You pass through a short tunnel" +
                " that leads downwards, then it starts heading" +
                " upwards. Finally you enter a larger body of" +
                " hot water and make your way to the surface" +
                " in a leisurely fashion, as you don't" +
                " feel any need to draw your breath.\n");
            tell_room(environment(TP), QCTNAME(TP) + " dives into" +
                " the depths of the pool.\n", TP);
            TP->move_living("M", FPATH + "hot_springs", 1);
            tell_room(environment(TP), QCTNAME(TP) + " breaks the" +
                " surface of the pool.\n", TP);
            return 1;
        }
        else
        if (skill > 29)
        {
            write("You start to swim into the depths of the" +
                " underground pool and through the hole in" +
                " the bottom. You pass through a short tunnel" +
                " that leads downwards, then it starts heading" +
                " upwards. Finally you enter a larger body of" +
                " hot water and race towards the surface, as" +
                " you feel a burning need to draw your breath.\n");
            tell_room(environment(TP), QCTNAME(TP) + " dives into" +
                " the depths of the pool.\n", TP);
            TP->move_living("M", FPATH + "hot_springs", 1);
            tell_room(environment(TP), QCTNAME(TP) + " breaks the" +
                " surface of the pool, gasping for air.\n", TP);
            return 1;
        }
        else
        {
            notify_fail("You start to swim into the depths of the" +
                " pool" +
                " and through the hole in the bottom. Then you" +
                " start swimming through a tunnel upwards, but" +
                " feel a burning need for air, and have no choice" +
                " other than returning to the surface of the" +
                " underground pool.\n");
            tell_room(environment(TP), QCTNAME(TP) + " dives into" +
                " the depths of the pool, but soon returns, gasping"+
                " for air.\n", TP);
            return 0;
        }
    }
    else
    {
        notify_fail("Swim where?\n");
        return 0;
    }
}

void
init()
{
    add_action(start_float, "float");
    add_action(stop_float, "stop");
    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
    add_action(do_climb, "climb");
    ::init();
}

