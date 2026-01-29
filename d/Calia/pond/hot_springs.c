/* Created 28.1.99 by Bishop, of Calia. This is a a pool, where
players resting that have enough spellcraft skill get healed at
intervals.*/

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <pond.h>
#include <filter_funs.h>
#include <composite.h>

public string extra_desc();
public string climbers();
public void start_heal_alarm(object ob, object here);
public void do_heal(object ob, object here);
public void do_swim(string str);
public void do_climb(string str);

create_room()
{
    set_short("Hot spring");

    set_long("You are sitting in the shallow end of a hot spring" +
        " that lies at the bottom of a cliff. The waters seem to" +
        " deepen closer to where the cliff rises to the west." +
        " Even though it's in the" +
        " shade most of the time, you're still comfortably warmed" +
        " by the water. Bubbles rise up from below from time to" +
        " time to tickle you. To the north mountains rise up, and" +
        " to your south and east a forest ends not far from" +
        " where this pool begins.@@extra_desc@@\n");

    add_item(({"water", "waters"}), "The water is clear as crystal,"+
        " but the shadow from the cliff still makes the water too" +
        " dim for you to see the bottom in the deeper end of the" +
        " pool.\n");
    add_item("bottom", "The bottom of the pool itself is warm" +
        " to the touch.\n");
    add_item(({"cliff face", "cliff"}), "The cliff is jagged, and" +
        " you see @@climbers@@. There" +
        " seems to be a plateau on the top of the cliff.\n");
    add_item("plateau", "The angle is all wrong, you can't get a" +
        " good look at it from down here.\n");
    add_item("bubbles", "The bubbles seem to be coming from the" +
        " deep end of the pool.\n");
    add_item("mountains", "The mountains connect with the cliff," +
        " though it doesn't look possible to climb further up" +
        " from there.\n");
    add_item("forest", "It's fairly dense, and is made out of" +
        " bushes, shrubs and trees. A path leaves into it.\n");
    add_item("path", "It's fairly narrow, other than that you don't"+
        " notice anything special about it from here.\n");

    add_cmd_item("cliff", "climb", "You'd have to get out of the" +
        " pool to climb the cliff.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_exit(FPATH + "env_hot_springs", "_no_exit_", 1, 1, 1);
}

string
extra_desc()
{
    if (TP->query_skill(SS_SPELLCRAFT) > 59)
    {
        return " The water feels soothing to your aching body.";
    }
    else
    {
        return "";
    }
}

string
climbers()
{
    object half = find_object("/d/Calia/pond/cliff_halfway");
    object *half_live;

    if (!half)
    {
        return "a ledge about halfway up the cliff";
    }    
    else
    if (half->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        half_live = FILTER_LIVE(all_inventory(half));

        if(sizeof(half_live))
        {
            return "a ledge about halfway up the cliff, with " +
            COMPOSITE_ALL_LIVE(half_live) + " standing on it";
        }
        else
        {
            return "a ledge about halfway up the cliff";
        }
    }
    else
    {
        return "that there's a dark spot about halfway up the cliff";
    }
}


void
enter_inv(object ob, object from)
{
    object here;
    here = environment(ob);
    start_heal_alarm(ob, here);

    ::enter_inv(ob, from);
}

void
start_heal_alarm(object ob, object here)
{
    int skill;

    if(living(ob) && environment(ob) == here)
    {
        skill = ob->query_skill(SS_SPELLCRAFT);
        
        if(skill > 59)
        {
            set_alarm(10.0, 0.0, &do_heal(ob, here));
        }
    }
}

void
do_heal(object ob, object here)
{
    int skill;

    if(living(ob) && environment(ob) == here)
    {
        skill = ob->query_skill(SS_SPELLCRAFT);
        ob->heal_hp(skill);
        if(random(10) == 0)
        {
            ob->catch_msg("You feel soothed and relaxed by the" +
                " bubbling waters.\n");
        }
    }
    start_heal_alarm(ob, here);
}

int
do_climb(string str)
{
    if (str == "out" || str == "out of pool" 
        || str == "out of the pool")
    {
        write("You climb out of the pool.\n");
        tell_room(environment(TP), QCTNAME(TP) + " climbs out of" +
            " the pool.\n", TP);
        TP->move_living("M", FPATH + "env_hot_springs", 1);
        tell_room(environment(TP), QCTNAME(TP) + " arrives climbing"+
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
            write("You start to swim into the depths of the pool" +
                " and through the hole in the bottom. You pass" +
                " through a short tunnel that leads downwards, and" +
                " enter a larger body of water. You don't feel any" +
                " particular need for air, so you take your time," +
                " and finally break the surface in a larger body" +
                " of water after having swum down for a while," +
                " then up.\n");
            tell_room(environment(TP), QCTNAME(TP) + " dives into" +
                " the depths of the pool.\n", TP);
            TP->move_living("M", FPATH + "underground_pool", 1);
            tell_room(environment(TP), QCTNAME(TP) + " breaks the" +
                " surface of the pool.\n", TP);
            return 1;
        }
        else
        if (skill > 29)
        {
            write("You start to swim into the depths of the pool" +
                " and through the hole in the bottom. You pass" +
                " through a short tunnel that leads downwards and" +
                " enter a larger body of water. Feeling the need" +
                " to breathe, you race for the surface and break" +
                " it, gasping for air.\n");
            tell_room(environment(TP), QCTNAME(TP) + " dives into" +
                " the depths of the pool.\n", TP);
            TP->move_living("M", FPATH + "underground_pool", 1);
            tell_room(environment(TP), QCTNAME(TP) + " breaks the" +
                " surface of the pool, gasping for air.\n", TP);
            return 1;
        }
        else
        {
            notify_fail("You start to swim into the depths of the" +
                " pool" +
                " and through the hole in the bottom. Then you" +
                " start swimming through a tunnel downwards, but" +
                " feel a burning need for air, and have no choice" +
                " but returning to the surface of the hot" +
                " springs.\n");
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
    add_action(do_climb, "climb");
    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
    ::init();
}

