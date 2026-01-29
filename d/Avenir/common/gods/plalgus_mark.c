// This mark is visible only in Sybarus.
// It is a potent curse in Sybarus.
// It acts as a mild poison that lasts a long time.
// Each level of infidel equates to one murder.
// Infidel levels are invoked by the code ONLY when 
//  a player commits a murder, thus being infidel is 
//  brought upon them by their OWN actions.
// Revision: Sept 2004 Lilith: updated comments
// Revision: June 2004 Lilith: made it time out if
//    someone isn't infidel.
// Revision: June 2004 Lilith: changes as follows
//    Interval lengthened, reduced poison damage to 5 / 5.
//    lift_judgment lifts 4 levels of infidel at a time.
    
inherit "/std/poison_effect";

#include "/sys/poison_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Avenir/include/relation.h"

#define LIST       ("/d/Avenir/union/list")
#define ENEMY(x)   (LIST->query_enemy(x))
#define FRIEND(x)  (LIST->query_friend(x))

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif
#ifndef SHORT_LOG
#define SHORT_LOG(file, entry)   ((file_size(file) > 3500) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, entry +" ("+ ctime(time()) + ")\n")))
#endif
 
/* This object acts like a mild poison */
void
create_poison_effect()
{    
    set_name(WRATHNAME);    
    set_short("Mark of Plalgus");
    set_long("Marks criminals as Judged by Plalgus.\n");
    set_time(18000);  // 5 hours of play time
    set_interval(900);
    set_damage(({ POISON_MANA, 5, POISON_HP, 5 }) );
    set_strength(100);
    set_poison_type("plalgus");
    set_silent(0); 
    set_no_cleanse();
    seteuid(getuid());
}

/*
 * Function name: enter_env
 * Description  : Run tests when we enter an environment.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{   
    object *obs;
    int i;
 
    ::enter_env(to, from);
    
    /* Adding aura subloc, logging clone */
    to->add_subloc("plalgus_subloc", this_object());
    SCROLLING_LOG(WRATH_LOG, "Curse was cloned to "+
        capitalize(to->query_real_name()) +".");        

    /* Only ever one at a time in a person's inventory */ 
    obs = all_inventory(to);
    for (i = 0; i < sizeof(obs); i++)
    {
        if (obs[i]->id(WRATHNAME) && obs[i] != this_object())
        {
            obs[i]->remove_object();
        }
    }

    /* If not an Infidel/murderer, remove it.
     * If Union enemy, it will be cloned on entering Sybarus
     */
    if (!IS_INFIDEL(to))
    {
        this_object()->timeout();    
    }
}

/*
 * Function name: leave_env
 * Description  : run checks on leving environment
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
void
leave_env(object from, object to)
{
    if (living(from)) 
    {
        from->remove_subloc("plalgus_subloc");
        from->remove_prop(LIVE_S_EXTRA_SHORT);
    }   

    ::leave_env(from, to);
}

/* 
 * Send message to player the terms of the curse.
 */
void
judge_tell(object enemy)
{
    tell_object(enemy, "A glorious, resonant voice echoes in your "+
        "mind:  Thus is my Judgement passed upon thee. By all of "+
        "Sybarus wilt thou be shunned.\n");
    tell_object(enemy, "The glorious, resonant voice whispers:  "+
       "Only by Death, the Gods' Mercy, or an Act of Contrition "+
       "shalt thou be freed.\n");   
}

/*
 *  Notify player he has been judged.
 *  Log the occurance.
 *  Take some hp.
 */
public void
hammer_him(object enemy)
{
    tell_room(environment(enemy), "A winged being swoops down "+
        "before you and stares at you with all-seeing eyes as "+
        "white as milk.\n");
    tell_room(environment(enemy), "Wielding a blue hammer, the "+
        "being smites "+ QTNAME(enemy) +" upon the head, then "+
        "disappears.\n", enemy);
    tell_object(enemy, "Wielding a blue hammer, the being smites "+ 
        "you upon the head, then disappears.\n");
    SCROLLING_LOG(WRATH_LOG, capitalize(enemy->query_real_name()) +
        " was judged by Plalgus.");

    /* Take one tenth max hp */
    enemy->heal_hp(-(enemy->query_max_hp() / 10));
    set_alarm(15.0, 0.0, &judge_tell(enemy));
}

public void
hammer_delay(object enemy)
{
    set_alarm(10.0, 0.0, &hammer_him(enemy));
}

/*
 *  This gets the time from the avenir_time object and returns the
 *  get_time_text string for purposes of logging.
 */
string 
get_time()
{
    string str;
    "/d/Avenir/inherit/avenir_time"->start_avtime();
    str = "/d/Avenir/inherit/avenir_time"->get_time_text();
    return str;
}

/*
 *  Called to lift the curse.
 *  Compares the number of infidel levels against the 
 *  judgement-lifted levels and determines if the curse
 *  is completely lifted or remains for the next round.
 */
public int
lift_judgement(int i)
{
    int s;
    s = IS_INFIDEL(this_player());

    if (!s)
    {
        remove_alarm(a_dam);
        set_alarm(2.0, 0.0, &remove_object());
        return 1;
    }    
    //Repeat offender? You're still cursed.
    if (s > i)
    {
        SCROLLING_LOG(WRATH_LOG, capitalize(this_player()->query_real_name()) +
        " had "+ i +" levels of judgement lifted but remains marked.");
        this_player()->set_skill(SS_INFIDEL, s - i);
        tell_object(this_player(), "A voice echoes in your mind: Your "+
           "blood-debt to Sybarus is too deep for you to be entirely "+
           "absolved of the Judgement of Plalgus. Your sentance is "+
           "extended for a little longer.\n");
        set_time(14400); // 4 hours play time.
        return 1;
    }
    // I'm no longer infidel, I've paid my dues.
    else
    {
        SCROLLING_LOG(WRATH_LOG, capitalize(this_player()->query_real_name()) +
            " was absolved.");        
        SHORT_LOG(ABSOLVE_LOG, capitalize(this_player()->query_real_name()) +
            break_string("in the "+ get_time(), 70, 2)); 
        this_player()->remove_skill(SS_INFIDEL);
        tell_object(this_player(), "With a flash of blue-white light "+
            "your headache lifts and your eyesight returns to normal.\n"+
            "The curse you have been living under has been lifted.\n");
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
        remove_alarm(a_dam);
        set_alarm(2.0, 0.0, &remove_object());
        return 1;
    }
}

/*
 * Function name: timeout
 * Description  : This is called when the poison duration has expired.
 *                It simply removes itself.
 */
public void
timeout()
{
    lift_judgement(4);
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string str, where;

    if (me->query_prop("_temp_subloc_show_only_things"))
        return "";

    if (subloc != "plalgus_subloc")
        return me->show_subloc(subloc, me, for_obj);

    where = file_name(environment(me));
    if (!wildmatch("/d/Avenir/*", where))
    {
        if (me->query_prop(LIVE_S_EXTRA_SHORT) == 
            " has a flickering blue aura")
            me->remove_prop(LIVE_S_EXTRA_SHORT);
         return "";
    }
    if (wildmatch("/d/Avenir/*", where))
    {

        if (!me->query_prop(LIVE_S_EXTRA_SHORT))
            me->add_prop(LIVE_S_EXTRA_SHORT,
            " has a flickering blue aura");

        if (for_obj == me)
            str = "Your head hurts and everything you see is faintly "+
                  "blue-tinted.\n";    
        else
            str = "Flickering above "+ me->query_possessive() +" head "+
                  "is the image of a blue hammer, a sign that Plalgus "+
                  "has Judged "+ me->query_objective() +" an Enemy of "+
                  "Sybarus.\n";
    }
    else
        str = "";   

    return str;
}

