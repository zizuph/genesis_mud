/* This is an underground room with a vent blowing heated air
inside, and players with high fire
magic skill can regain mana at intervals
from this. By Bishop of Calia, 5.2.99. */


inherit "/d/Calia/std/room_tell_room";


#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include <filter_funs.h>

public string room_descrip();
public void start_mana_alarm(object ob, object here);
public void do_mana(object ob, object here);
public int do_stand(string str);
public int do_step(string str);


mapping mana_log = ([ ]);

create_room()
{
    set_short("In a very hot room");

    set_long("@@room_descrip@@\n");

    add_item(({"wall","walls"}), "The walls are made of dry rock," +
        " and set with glowstones.\n");
    add_item("glowstones", "Glowstones are a naturally occuring" +
        " but rare type of rock that emit a soft light.\n");
    add_item("vent", "The vent leads up into a thin tunnel," +
        " only a foot in diameter. It gets dark quick, so you can't"+
        " see far up.\n");

    add_prop(ROOM_I_HIDE, 80);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(FPATH + "und_corridor", "west", 0, 1);
}

string
room_descrip()
{
    if (TP->query_skill(SS_ELEMENT_FIRE) < 60)
    {
        return "This room is incredibly hot! You are standing" +
            " at the end of the corridor in a small cave. The" +
            " walls are set with glowstones, giving the room a" +
            " reddish hue. The source of the heat seems to be a" +
            " vent of some kind on the ceiling. Hot air is"+
            " streaming" +
            " out of it, causing a trail of sweat to run down your" +
            " forehead.";
    }
    else
    {
        return "This room is very hot, but that doesn't bother you" +
            " at all. Your skill in fire magic enables you to" +
            " easily diffuse the heat, drawing it into yourself." +
            " You are standing at the end of the corridor in a" +
            " small cave. The walls are set with glowstones, giving"+
            " the room a reddish hue. The source of the heat here" +
            " seems to be a vent of some kind on the ceiling. Hot" +
            " air is streaming out of it." +
            " You think that if you were to stand under the vent," +
            " you might be able to harness the power of this place."+
            " You feel that this place is particularly close to the"+
            " plane of elemental fire.";
    }
}

int
do_stand(string str)
{
    object here = environment(TP);

    if (str == "under vent" || str == "underneath vent"
        || str == "beneath vent")
    {
        if (TP->query_prop(CALIA_I_MANA_GAIN) > 0)
        {
            notify_fail("You are already standing underneath" +
                " the vent.\n");
            return 0; 
        }
        else
        if (TP->query_skill(SS_ELEMENT_FIRE) > 59)
        {
            write("You stand underneath the vent, and" +
                " suddenly a stream of glowing sparks comes out" +
                " of it, filling you with power! You could step" +
                " away from the vent if you like.\n");
            tell_room(TO, QCTNAME(TP) + " places " +
                TP->query_objective() + "self underneath the" +
                " the vent and suddenly a stream of glowing" +
                " sparks comes out of it, hitting " +
                TP->query_objective() + ".\n", TP);
            TP->add_prop(LIVE_S_EXTRA_SHORT, " is standing in a" +
                " cloud of sparks");
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
            notify_fail("You stand underneath the vent, but nothing"+
                " happens.\n");
            tell_room(TO, QCTNAME(TP) + " places " +
            TP->query_objective() + "self underneath the vent, but" +
                " nothing happens.\n", TP);
            return 0;
        }
    }
    else
    {
        notify_fail("Stand where?\n"); 
        return 0;
    }
}

int
do_step(string str)
{
    if (str == "away from the vent" || str == "away from vent" ||
        str == "away")
    {
        if (TP->query_prop(CALIA_I_MANA_GAIN))
        {
           write("You step away from the vent, and the shower" +
               " of sparks ceases.\n");
           tell_room(TO, QCTNAME(TP) + " steps away from" +
               " underneath the went, and the shower of sparks" +
               " hitting him ceases.\n", TP);
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
           notify_fail("You're not standing underneath the vent!\n");
           return 0;
       }
    }
    else
    {
        notify_fail("Step where?\n");
        return 0;
    }
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
        skill = ob->query_skill(SS_ELEMENT_FIRE);
        
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
    add_action(do_stand, "stand");
    add_action(do_step, "step");
    ::init();
}