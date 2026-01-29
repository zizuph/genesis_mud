/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <formulas.h>

public string room_desc();
public int do_touch(string str);
public int do_release(string str);
public void start_mana_alarm(object ob, object here);
public void do_mana(object ob, object here);

mapping mana_log = ([ ]);

create_room()
{
    set_short("Area of tremors");

    set_long("In the middle of this area you see a standing stone" +
        " that seems completely unaffected by the moving earth." +
        " @@room_desc@@" +
        " In all directions save to the south, sheer mountains" +
        " rise. A good ways to the south and east you can see a" +
        " small pool.\n");

    add_item(({"earth", "ground"}), "The ground here is in motion," +
        " threatening to trip the careless.\n");
    add_item(({"crack", "cracks"}), "Cracks of varying size open" +
        " and close constantly here.\n");
    add_item(({"mountain", "mountains"}), "The sheer mountains" +
        " dominate the horizon in all directions except to the" +
        " south.\n");
    add_item(({"small hot pool", "hot pool", "pool"}),
        "Steam is rising from the warm waters.\n");
    add_item("steam", "It's evaporated water from from the pool.\n");
    add_item(({"rock", "rocks"}), "This area is strewn with rocks" +
        " of varying sizes.\n");
    add_item(({"standing stone", "stone"}), "The standing stone is" +
        " about the height of two men and seems be made out of" +
        " granite. It stands completely still in spite of the" +
        " tremors here.\n");

    set_tell_time(200);
    add_tell("A particularly violent tremor pulses through the" +
        " area.\n");
    add_tell("Some small rocks loosen on the mountainside and slide"+
        " down to ground level.\n");
    add_tell("You hear a hoarse cry from above. Sounds like some" +
        " kind of bird.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(FPATH + "epath3", "south", 0, 1);
}

string
room_desc()
{
    if (TP->query_skill(SS_ELEMENT_EARTH) < 60)
    {
        return "The earth under you gives the occasional tremble," +
            " forcing you to focus your attention downwards. You" +
            " have to watch your step to avoid tripping, and it's" +
            " hard to avoid stumbling when a particularly violent" +
            " tremor pulses through the area.";
    }
    else
    {
        return "The earth is indeed turbulent in this area, but" +
            " with your mastery of earth magic you easily soothe" +
            " it and can walk around in a small pocket of calm." +
            " You feel that this place is particularly close to" +
            " the plane of elemental earth and that if you were to"+
            " touch the stone, you might be able to harness the" +
            " power here.";
    }
}

int
do_touch(string str)
{
    object here = environment(TP);

    if (str == "stone" || str == "standing stone"
        || str == "the stone" || str == "the standing stone")
    {
        if (TP->query_prop(CALIA_I_MANA_GAIN) > 0)
        {
            notify_fail("You are already touching the stone.\n");
            return 0; 
        }
        else
        if (TP->query_skill(SS_ELEMENT_EARTH) > 59)
        {
            write("You touch the stone, and a soothing feeling" +
                " flows through" +
                " your body. The feeling is exhilarating, but you" +
                " could release the stone if you wish.\n");
            tell_room(TO, QCTNAME(TP) + " touches the standing" +
                " stone.\n", TP);
            TP->add_prop(LIVE_S_EXTRA_SHORT, " is touching the" +
                " standing stone");
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
            notify_fail("You touch the standing stone, but nothing" +
                " seems to happen, so you release it.\n");
            tell_room(TO, QCTNAME(TP) + " touches the standing" +
                " stone and releases it again.\n", TP);
            return 0;
        }
    }
    else
    {
        notify_fail("Touch what?\n"); 
        return 0;
    }
}

int
do_release(string str)
{
    if (str == "the standing stone" || str == "standing stone" ||
        str == "stone"  || str == "the stone")
    {
        if (TP->query_prop(CALIA_I_MANA_GAIN))
        {
           write("You release the stone, and the soothing feeling" +
               " abruptly ceases.\n");
           tell_room(TO, QCTNAME(TP) + " releases the standing" +
               " stone.\n", TP);
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
           notify_fail("You're not touching the stone.\n");
           return 0;
       }
    }
    else
    {
        notify_fail("Release what?\n");
        return 0;
    }
}

void
enter_inv(object ob, object from)
{
    if(living(ob) && ob->query_skill(SS_ELEMENT_EARTH) > 59)
    {
        ob->catch_msg("The earth seems to welcome you as you enter,"+
            " opening a small zone of calm around your feet," +
            " allowing you to walk steadily.\n");
        set_alarm(0.5, 0.0, 
        &tell_room(environment(ob), "As " + ob->query_pronoun() +
            " enters, a small zone of calm seems to open under " +
            ob->query_possessive() + " feet, allowing " +
            ob->query_objective() + " to walk steadily.\n", ob));
    }

    ::enter_inv(ob, from);
}

void
leave_inv(object ob, object to)
{
    if(living(ob) && ob->query_prop(CALIA_I_MANA_GAIN))
    {
        log_file("grotto_mana_gain", 
            capitalize(ob->query_real_name()) + " left" +
            " at " + ctime(time()) + ", having" +
            " gained: " + 
            mana_log[ob->query_real_name()] + " mana.\n");
        mana_log = m_delete(mana_log, ob->query_real_name());
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop(CALIA_I_MANA_GAIN);
    }
    ::leave_inv(ob, to);
}

void
start_mana_alarm(object ob, object here)
{
    int skill;

    if(living(ob) && environment(ob) == here &&
        ob->query_prop(CALIA_I_MANA_GAIN) == 1)
    {
        skill = ob->query_skill(SS_ELEMENT_EARTH);
        
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
            write("The heat flows into you, soothing your" +
                " mind.\n");
        }
    }
    start_mana_alarm(ob, here);
}

void
init()
{
    add_action(do_touch, "touch");
    add_action(do_release, "release");
    ::init();
}