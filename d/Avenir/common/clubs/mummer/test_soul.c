// -*-C++-*-
// file name: 	  /d/Avenir/common/clubs/mummer/test_soul.c
// creator(s):	  Lilith, October 1996
// last update:	  
// purpose:       Minor guild for male entertainers
// note:          emotes in /mummer/lib/* dir
// bug(s):
// to-do:
#pragma save_binary

inherit "/cmd/std/command_driver";
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/common/clubs/mummer/mummer_club.h"

#define ALLBBX(str)   tell_room( environment(tp),(QCTNAME(tp)+ str), ({tp}) )
#define TEST_LINK_DEATH if( !(living(tp) && interactive(tp)) ) \
		{ ld_clean(tp); return; }

private void
ld_clean(object tp) // linkdeath cleanup
{
    if (!living(tp)) return;

    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);

    /* Remove speech block if we added one */
    if (tp->query_prop(LIVE_M_MOUTH_BLOCKED))
        tp->remove_prop(LIVE_M_MOUTH_BLOCKED);
}

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Mum of Syb"; }

/********************************************************************
 * The list of verbs and functions. 
 *******************************************************************/
public mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
        "mshow"  :   "mshow",  "mumshow" :   "mshow",
        "mpull"  :   "mpull",  "mumpull" :   "mpull",
        "mlevi"  :   "levitate", "mumlevi" :  "levitate", 
        "levitate" : "levitate",
        
    ]);
}

int
mpull(string str)
{
    object *items, item;

    if (!strlen(str))   
    {
        notify_fail("What do you want to pull out of your cap?\n");
        return 0;
    }
    items = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(items))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    if (sizeof(items) > 1)
    {
        notify_fail("You can only pull one thing at a time from your cap.\n");
        return 0;
    }
    item = items[0];
    if (!living(item))
    {
        notify_fail("You must have something -alive- in your inventory "+
            "inorder to do this.\n");
        return 0;
    }
    write("You wave your hand over the cap, embellishing every movement.\n");    
    write("You reach into the cap, and feign a look of surprise as you "+
        "pull "+ LANG_ASHORT(item) +" from your cap.\n");
    allbb(" waves "+ POSSESS(TP) +" hand over the dark center of the cap, "+
        "reaches inside, and looks pleasantly surprised as "+ PRONOUN(TP) +" pulls "+
        LANG_ASHORT(item) +" out of "+ POSSESS(TP) +" cap.");
    ADD_A_LEVEL(this_player());
    return 1;
}

int
mshow(string str)
{
    object *cap;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        

    if (str == "hat" || str == "cap" || str == "mummers cap")
    {
        if (sizeof(cap = filter(all_inventory(TP), "cap_check", TO)))
            command("remove cap");

        write("With studied grace and a flourish of your hands, you "+
            "show your audience that you have nothing at all inside "+
            "your mummer's cap.\n");
        say("With studied grace and a flourish of "+ POSSESS(TP) +
            " hands, "+ QCTNAME(TP) +" demonstrates that "+ PRONOUN(TP) +
            " has nothing at all inside "+ POSSESS(TP) +" mummer's cap.\n");
        ADD_A_LEVEL(this_player());
        return 1;       
    }
    write("With great flair and deliberate grace, you show your "+
        "audience that you have nothing at all up your sleeves.\n");
    allbb(" extends "+ POSSESS(TP) +" arms and, with great flair "+
        "and deliberate grace, shows you that "+ PRONOUN(TP) +
        " has nothing at all up "+ POSSESS(TP) +" sleeves.");
    ADD_A_LEVEL(this_player());
    return 1;
}


/* 
 *   Levitate 
 */
private void
levi_one(object tp, object who)
{
    TEST_LINK_DEATH
 
    if (!who)
    {
        write("It seems that whatever it was that you were going to "+
            "levitate is no longer here!\n");
        tp->command("$mstop");
        if (tp->query_wiz_level())
            write("You will need to use <mstop> to end this performance.\n");
        return;
    }
    if (living(who))
    {
        tell_object(who, tp->query_The_name(who) +" "+
            "extends "+ POSSESS(tp) +" hands toward you, palm up, and "+
            "begins making slow, lifting motions.\n");       
        tell_object(tp, 
            "You extend your hands, palms up, toward "+
            who->query_The_name(tp) +" and make slow, lifting motions.\n");
        tell_room(environment(TP), (QCTNAME(tp) +" extends "+ POSSESS(tp) +
            " hands, palm up, toward "+ QCTNAME(who) +" and makes "+
            "slow, lifting motions.\n" ), ({tp, who}));
        return;
    }
    tell_object(tp, 
        "You extend your hands, palms up, toward the "+
        who->query_short() +" and make slow, lifting motions.\n");
    tell_room(environment(TP), (QCTNAME(tp) +" extends "+ POSSESS(tp) +
        " hands, palm up, toward the "+ who->query_short() +" and makes "+
        "slow, lifting motions.\n" ), ({tp, who}));
    
}

private void
levi_two(object tp, object who)
{
    TEST_LINK_DEATH
 
    if (!who)
    {
        write("It seems that whatever it was that you were going to "+
            "levitate is no longer here!\n");
        tp->command("$mstop");
        if (tp->query_wiz_level())
            write("You should use <mstop> to end this performance.\n");
        return;
    }
    if (living(who))
    {
        tell_object(who, tp->query_The_name(who) +"'s "+
            "extended hands begin to tremble, and "+ POSSESS(tp) +" face "+
            "contorts.\nYou suddenly feel lighter. You look down, and see "+
            "that your feet are a good hand-span above the ground!\n");       
        tell_object(tp, 
            "You make your hands tremble, and contort your face as though "+
            "you are lifting a heavy weight.\n"+ who->query_The_name(tp) +
            " rises a hand-span above the ground!\n");
        tell_room(environment(TP), (QCTNAME(tp) +"'s extended hands begin "+
            "to tremble, and "+ POSSESS(tp) +" face contorts.\n"+
            QCTNAME(who) +" rises gently into the air, stopping a hand-"+
            "span above the ground!\n"), ({tp, who}));
        return;
    }
    tell_room(environment(TP), (QCTNAME(tp) +"'s extended hands begin "+
        "to tremble, and "+ POSSESS(tp) +" face contorts.\nThe "+ 
        capitalize(who->query_short()) +" rises gently into the air, "+
        "stopping a hand-span above the ground!\n"), ({tp, who}));
    tell_object(tp, 
        "You make your hands tremble, and contort your face as though "+
        "you are lifting a heavy weight.\nThe "+ 
        who->query_short() +" rises a hand-span above the ground!\n");

}

private void
levi_end(object tp, object who)
{
    TEST_LINK_DEATH
 
    if (!who)
    {
        write("It seems that whatever it was that you were levitating "+
            "is no longer here!\n");
        tp->command("$mstop");
        if (tp->query_wiz_level())
            write("You should use <mstop> to end this performance.\n");
        return;
    }
    if (living(who))
    {
        tell_object(who, TP->query_The_name(who) +" "+
            "suddenly sags with exhaustion. "+ capitalize(POSSESS(tp)) +
            " hands drop to "+ POSSESS(tp) +" sides and you land back "+
            "on the ground with a thud!\n");       
        tell_object(tp, 
            "You pretend to sag with exhaustion, allowing "+ 
            who->query_The_name(tp) +
            " to fall to the ground with a thump.\n");
        tell_room(environment(TP), (QCTNAME(tp) +" suddenly sags with ex"+
            "haustion.\n"+ capitalize(POSSESS(tp)) +" hands drop to "+ 
            POSSESS(tp) +" sides and "+ QCTNAME(who) +" lands back "+
            "on the ground with a thump!\n"), ({tp, who}));
        ADD_A_LEVEL(this_player());
        tp->remove_prop(LEVI_INDEX);
        remove_alarm(tp->query_prop(MIME_ALARM));
        tp->remove_prop(MIME_ALARM);
        return;
    }
    tell_object(tp, 
        "You pretend to sag with exhaustion, allowing the "+ 
        who->query_short() +
        " to fall to the ground with a thump.\n");
    tell_room(environment(TP), (QCTNAME(tp) +" suddenly sags with exh"+
        "haustion.\n"+ capitalize(POSSESS(tp)) +" hands drop to "+ 
        POSSESS(tp) +" sides and the "+ who->query_short() +" lands back "+
        "on the ground with a thump!\n"), ({tp, who}));
    ADD_A_LEVEL(this_player());
    tp->remove_prop(LEVI_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);
}


private function* levitate = ({ levi_one, levi_two, levi_end, });

private void
do_levitate(object tp, object who)
{
    int index = tp->query_prop(LEVI_INDEX);
  
    tp->add_prop(LEVI_INDEX, index+1);
    applyv(levitate[index], ({tp, who}));
}

int 
levitate(string str)
{
    object *whos, who;
    object tpl;

    if (TP->query_prop(MIME_ALARM))
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }
    if (!strlen(str))
    {
        notify_fail("Who or what do you want to levitate?\n");
        return 0;
    }
    whos = FIND_STR_IN_OBJECT(str, environment(TP));
    if (!sizeof(whos))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    if (sizeof(whos) > 1)
    {
        notify_fail("You can only levitate one thing at a time.\n");
        return 0;
    }
    if (objectp(TP->query_attack()))
    {
        notify_fail("It is not wise to attempt this during combat. "+
            "You could be injured.\n");
        return 0;
    }
    who = whos[0];
    if (who->query_prop(HEAP_I_IS))
    {
        notify_fail("You are unable to levitate that for some odd "+
            "reason.\n");
        return 0;
    }
    if ((who->query_prop(OBJ_I_WEIGHT) / 2) > 
       (TP->query_prop(OBJ_I_WEIGHT) + (TP->query_mana() * 2)))
    {
        notify_fail("The "+ str +" is far too heavy for you "+
           "to levitate.\n");     
        return 0;
    }
    if (living(who))
    {
        tell_object(who, TP->query_The_name(who) +
            " stares intently at you.\n");       
        tell_object(TP, "You stare intently at "+ who->query_The_name(TP) +
            ".\n");
        tell_room(environment(TP), (QCTNAME(TP) +" stares intently at "+ 
             QCTNAME(who) +".\n" ), ({TP, who}));
        tpl = TP;
        TP->remove_prop(LEVI_INDEX);
        TP->add_prop(MIME_ALARM, set_alarm(2.0, 3.0, &do_levitate(tpl, who)));
        return 1;
    }
    tell_object(TP, "You stare intently at the "+ who->query_short() +
        ".\n");
    tell_room(environment(TP), (QCTNAME(TP) +" stares intently at the "+ 
         who->query_short() +".\n" ), ({TP, who}));
    
    tpl = TP;
    TP->remove_prop(LEVI_INDEX);
    TP->add_prop(MIME_ALARM, set_alarm(2.0, 3.0, &do_levitate(tpl, who)));
    return 1;

}
