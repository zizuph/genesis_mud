/*********************************************************************
 * - lamp.c                                                        - *
 * - A lamp that will burn oil                                     - *
 * - Flask of oil is needed. (foil.c)                              - *
 * - Much of this lamp is taken from various lamp examples found.  - *
 * - Special contribrutions/credit found in such code belong to:   - *
 * - Lord Elessar Telcontar, Mercade, Zima and Maniac              - *
 * - Created by Damaris@Genesis 04/24/2003                         - *
 *********************************************************************/
#pragma strict_types
inherit "/std/torch";
inherit "/lib/keep"; 
#include "/d/Khalakhor/sys/basic.h"
#include "lamp.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
 
string lamp_desc;
 
int oil_alarm; 

/* It is a lamp so it should not decay. */
public int
query_torch_may_decay()
{
 return 0;
}

void
create_torch()
{
    set_name("lamp");
    add_name(({"oil-lamp"}));
    add_adj("crystal");
    add_adj("oil");
    set_pname("lamps");
    add_pname("oil-lamps");
    set_short("crystal oil-lamp");
    set_pshort("crystal oil-lamps");
    set_long("@@long_description");
    add_item("wick", "@@wick_description");

    set_time(1000);
    set_time_left(500); /* Lets give them some oil to start */

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 800);
    set_keep(1); 
}
 
string
long_description()
{
    string longstr;
    if (!strlen(lamp_desc))
        longstr = "This is a lovely crystal oil-lamp. The base is "+
          "a nicely rounded bowl made of crystal that shimmers with "+
          "rainbow colours whether filled or empty of oil. The "+
          "crystal bowl of the lamp is surrounded by highly "+
          "polished brass fittings along the edge. It has a "+
          "wick on one end and a curved polished brass handle "+
          "on the other. ";
    else longstr = lamp_desc;
 
    if (!query_time(1))
    {
        longstr += "The "+ short() +" does not contain any oil. ";
    }
    else
    {
        longstr += "The "+ short() +" contains some oil. ";
    }
 
    return (longstr + "\n");
}
 

string
wick_description()
{
    return ("The wick of the "+ short() +" sticks out from a hole in "+
           "one end. " + (query_prop(OBJ_I_LIGHT) ?
           "Flames are dancing along the wick since the lamp is "+
           "burning.\n" :
           "The wick is not lit.\n"));
}
 

int
torch_value()
{
    /* The value of the lamp itself is 150 cc */
    /* Oil is worth 1 cc per 30 ml oil        */
    return 150 + (query_time(1) / 30);
}

int
light_me_after_delay()
{
     ::light_me_after_delay();
     this_object()->oil_alarm_check();  
}

int
extinguish_me()
{
    int r;

    r = ::extinguish_me(); 
    if (r) {
        remove_alarm(oil_alarm);
        oil_alarm = 0; 
    }
    return r;
}


void
set_time_left(int time)
{
    int l = (query_lit(0) != 0); 

    /* Next two lines update the burn out alarm. */ 
    if (l)  
        extinguish_me(); 

    ::set_time_left(time); 

    if (l) 
        command_light();
}


int
do_refill(string str)
{
    object oil_flask;
 
    if (!strlen(str))
    {
        notify_fail(CAP(query_verb()) + " what with what?");
        return 0;
    }

    if (!parse_command(str,TP," [the] [crystal] [oil] 'lamp' / 'oil-lamp' "+
                              "[with] [lamp] [oil] / [lamp-oil] "))
    {
        notify_fail(CAP(query_verb()) + " what with what?\n");
        return 0;
    }
 
    if (!objectp(oil_flask = present("_flask_of_oil_", TP)))
    {
        notify_fail("You have no extra oil to fill the "+ short() +" with!\n");
        return 0;
    }

    if (!(oil_flask->query_amount()))
    {
        notify_fail("The " + oil_flask->short() + " is empty.\n");
        return 0; 
    }
 
    if (query_time(1) == query_max_time())
    {
        notify_fail("The "+ short() +" is already filled with oil!\n");
        return 0; 
    }
 
    if ((query_time(1) + oil_flask->query_amount()) > query_max_time())
    {
        oil_flask->remove_oil(query_max_time() - query_time(1));
        set_time_left(query_max_time());

        write("You fill the "+ short() +" with as much oil as "+
          "it can hold.\n");
        say(QCTNAME(TP)+" fills the "+ short() +" with as "+
          "much oil as it can hold.\n");
 
        return 1;
    }

    set_time_left(query_time(1) + oil_flask->query_amount());
    oil_flask->remove_oil(oil_flask->query_amount());

    write("You fill the "+ short() +" with all the oil in the flask. "+
      "The "+ short() +" is not completely filled with oil.\n");
    say(QCTNAME(TP)+" fills extra oil into the "+ short() +".\n");
    return 1;
}




mixed
query_light_fail()
{
    if (!query_time(1))
    {
        return "You try to light your " + short() +
            ", but it does not contain any oil!\n";
    }
    return ::query_light_fail();
}

 

void
notify_low_on_oil()
{
    object env = ENV(TO);
 
    if ((query_time(1) > 30) ||
        (!query_lit(0)) ||
        (!objectp(env)))
    {
        return;
    }

    if (living(env))
    {
        env->catch_msg("Your "+ short() +" flickers briefly. It seems "+
        "to be running out of oil.\n");
        LTELL_ROOM(ENV(env), env, "The "+ short() +" that ", " holds, "+
          "flickers briefly. It seems to be running out of oil.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The " + short() + " flickers briefly. It seems " +
            "to be running out of oil.\n");
    }
}


int
compute_weight()
{
    /* 300 for the oil-lamp and 2 grams per 6 ml oil */
    return 300 + (2 * query_time(1) / 6);
}
 

void
oil_alarm_check()
{
    if (!query_lit(0)) 
        return;

    if (query_time(1) > 30) {
        remove_alarm(oil_alarm); 
        oil_alarm = 
           set_alarm(itof(query_time(1) - 30), 0.0, notify_low_on_oil);  
    }
}



void
appraise_object(int num)
{
    int perc = ((query_time(1) * 100) / query_max_time());
    int skill;
    int seed;
    string extra_desc = "is empty.";
 
    ::appraise_object(num);
 
    if (!num)
    {
      skill = TP->query_skill(SS_APPR_OBJ);
    }
    else
    {
      skill = num;
    }
 
    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random((1000 / (skill + 1)), seed);
    perc = cut_sig_fig(perc + (skill % 2 ? -skill % 70 : skill) * perc / 100);
 
    if (perc >= 100)
        extra_desc = "is completely filled with oil.\n";
    else if (perc > 80)
        extra_desc = "is almost completely filled with oil.\n";
    else if (perc > 60)
        extra_desc = "filled with oil for about two-thirds.\n";
    else if (perc > 40)
        extra_desc = "is about half-full of oil.\n";
       else if (perc > 20)
        extra_desc = "filled with oil for about one-third.\n";
    else if (perc > 0)
        extra_desc = "hardly contains any oil.\n";
 
    write("You appraise that it " + extra_desc);
}

string
query_recover()
{
    return MASTER + ":" + query_torch_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    string foobar;
 
    init_torch_recover(arg);
    init_keep_recover(arg); 
}

void
set_lamp_desc(string str)
{
  if (stringp(str) && strlen(str)) lamp_desc = str;
}

void
init()
{
    ::init();
 
    add_action("do_refill", "fill");
    add_action("do_refill", "refill");
}
