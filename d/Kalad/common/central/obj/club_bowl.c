inherit  "/std/container";
inherit "/sys/global/money";
inherit "/cmd/std/command_driver";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>


query_auto_load()
{
    return MASTER;
}

create_container()
{
    set_name("bowl");
    set_adj("wooden");
    add_adj("cracked");
    add_name("beggarmember");
    set_short("cracked wooden bowl");
    set_long("This bowl shows sign of hard use with all those cracks "+
        "in the wood, making it useless to hold any liquid. It can carry "+
        "some solid objects though. There are some words engraved in "+
        "the bottom of the bowl.\n");
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(OBJ_I_NO_DROP,"Nahh, what would you use to beg with then?\n");
    
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    int heartbeat_age;
    int day;
    
    day = 44000; /* a day in heart_beats */
    
    if (for_obj == on)
        data = "You are ";
    else
        data = capitalize(environment(TO)->query_pronoun()) + " is ";
    
    if (on->query_npc())
        heartbeat_age = random(day*18);
    else
        heartbeat_age = on->query_age();
    if(heartbeat_age < day*1)
        data+="a juvenile almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*2)
        data+="a youthful almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*3)
        data+="a mature almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*4)
        data+="an experienced almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*6)
        data+="a senior almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*8)
        data+="an elderly almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*10)
        data+="an ancient almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*14)
        data+="a patriarchal almsman of the Beggars Club of Kabal.\n";
    else
        if(heartbeat_age < day*20)
        data+="an archaic almsman of the Beggars Club of Kabal.\n";
    else
        data+="a soon retired almsman of the Beggars Club of Kabal.\n";
    
    return data;
}

enter_env(object dest,object old)
{
    remove_name("beggarmember");
    if(present("beggarmember",environment(TO)))
        {
        tell_room(environment(TO),"Suddenly one of the bowls breaks "+
            "into thousands of pieces.\n");
        remove_object();
        return;
    }
    
    add_name("beggarmember");
    if(living(environment(TO)))
        dest->add_subloc("beggarmember", this_object());
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc("beggarmember");
}
void
init()
{
    ::init();
    add_action("do_fill","bgrab");       /* grad coins around you */
    add_action("do_beg","bbeg");         /* beg for coins with the bowl */
    add_action("do_empty","bempty");     /* empty the bowl */
    add_action("read_label","read");        /* read the emote-commands */
    add_action("do_nap","bnap");       /* nap on the edge of xx's robe */
    add_action("do_count","bcount");   /* count coins collected */
    add_action("do_search","bsearch"); /* search for victims */
    add_action("do_put","bput"); /* put coins in bowl */
}


/*
* Function name: tell_watcher
* Description:   Send the string from the fight to people that want them
* Arguments:     The string to send
* This function is copied from Magebane (jagged scimitar) by Mercade.
*/
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
    me = TP;
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({me});
    ob -= ({enemy});
    for (i=0;i<sizeof(ob); i++)
    ob[i]->catch_msg(str);
}

int
do_nap(string str)
{
    /* make routine for napping on somebody's robe */
    object who;
    object *victims;
    if (!str)
        {
        write("Nap who?\n");
        return 1;
    }
    victims = parse_this(str,"%l");
    if (sizeof(victims)==0)
        {
        write("You look around, but find nobody to nap on.\n");
        return 1;
    }
    if (sizeof(victims)>1)
        {
        write("Who do you want to nap on? Be more precise.\n");
        return 1;
    }
    who = victims[0];
    TP->catch_msg("You start to nap on the robe of "+QTNAME(who)+
        ", in the hope that "+who->query_pronoun()+" will see "+
        "your need for some coins.\n");
    who->catch_msg("You suddenly notice that "+QTNAME(TP)+" "+
        "is napping on your robe to catch your attention. "+
        "Looking at "+TP->query_possessive()+" dirty face, you feel "+
        "that some spare coins would help "+TP->query_objective()+
        " a lot.\n");
    tell_watcher("You notice that "+QTNAME(TP)+" naps at "+QTNAME(who)+"'s robe, "+
        "looking up at "+who->query_objective()+" with some "+
        "begging eyes.\n",who);
    return 1;
}

do_count()
/* count coins in inventory */
{
    write("You start to count how much you have earned from your begging.\n");
    say(QCTNAME(TP) + " starts eagerly to count " + TP->query_possessive() + 
        " profit from the begging.\n");
    set_alarm(2.0,0.0,"count_result");
    return 1;
}
count_result()
{
    /* make routine for counting coins */
    int coins;
    coins=total_money(TP);
    write("After a short time you think you have managed to earn "+
        coins+" copper coins in total.\n");
}

do_put()
{
    write("You collect all your coins and with a grin of content put them in your bowl.\n");
    say(QCTNAME(TP)+" starts to empty all the pockets with "+
        "a happy look on the face.\n");
    TP->command("put platinum coins in bowl");
    TP->command("put gold coins in bowl");
    TP->command("put silver coins in bowl");
    TP->command("put copper coins in bowl");
    return 1;
}

do_search()
{
    write("You start to appraise the people around you thoroughly.\n");
    say("You barely notice that "+QTNAME(TP)+" starts to look "+
        "around with some greedy, scrutinizing eyes.\n");
    set_alarm(3.0,0.0,"search_effect");
    return 1;
}
search_effect()
{
    object good_victim, evil_victim, next_victim;
    object *victim;
    object *people;
    int i;
    int size;
    string str;
    
    /* make a search-routine here */
    people=all_inventory(environment(TP));
    people=FILTER_OTHER_LIVE(people);
    if(sizeof(people)==0)
        {
        write("You look around, but all you see is yourself.\n");
        return;
    }
    
    victim = people;
    size = sizeof(victim);
    evil_victim=victim[random(size)];
    good_victim = victim[random(size)];
    
    str = "";
    if (sizeof(victim)==1)
        {
        write("After a while you realise that there is just one "+
            "around here to beg from.\n");
        good_victim->catch_msg("You notice that the eyes of "+QTNAME(TP)+
            " seems to linger a bit on your money pouch.\n");
        return;
    }
    if (good_victim==evil_victim)
        {
        write("You observe that no one around you is "+
            "especially likely to give you coins.\n");
        return;
    }
    if (random(2)==0)
        {
        str = "You think that "+QTNAME(good_victim)+" seems to "+
        "be a very good victim for some begging. ";
        good_victim->catch_msg("You notice that "+QTNAME(TP)+
            "'s begging eyes seems to linger abit on your money pouch.\n");
    }
    else
        {
        str = "You observe that no one around you is "+
        "especially likely to give you any coins. ";
    }
    if (random(2)==0)
        {
        str=str+QCTNAME(evil_victim)+" looks like a person to avoid!";
        evil_victim->catch_msg("You notice that the eyes of "+QTNAME(TP)+
            " tries to avoid you and your items.\n");
    }
    else
        {
        str = str+"Fortunately, no one around you looks quite "+
        "like a bad target, either.";
    }
    
    TP->catch_msg("Your scrutinizing eyes sweep over all the people "+
        "around you..."+str+"\n");
    
}

do_empty()
{
    seteuid(getuid());
    if (sizeof(all_inventory(TO))==0)
        {
        write("You turn the bowl upside down and see some "+
            "dust fall slowly down to the ground.\n");
        say(capitalize(QCTNAME(TP))+ " turns a wooden bowl "+
            "upside down and watches the dust fall slowly down to the "+
            "ground with a sad look.\n");
        TP->command("smile sadly");
    }
    
    else
        {
        write("You turn the bowl upside down, watching the contents "+
            "of it fall down into your other hand.\n");
        say(capitalize(QCTNAME(TP))+ " turns "+
            TP->query_possessive() + " bowl upside down and catches "+
            "the contents of it with the other hand.\n");
        TP->command("get all from bowl");
    }
    return 1;
}

do_fill()
{
    seteuid(getuid());
    TP->command("emote grabs all the coins around "+
        TP->query_objective()+ "self with a greedy grin on "+
        TP->query_possessive()+ " face.");
    TP->command("get coins");
    TP->command("put coins in bowl");
    TP->command("grin greedily");
    return 1;
}

do_beg()
{
    write("With both of your hands, you stretch the bowl outwards "+
        "towards all around you with a begging look on your face.\n");
    say(capitalize(QCTNAME(TP)) + " stretches out a cracked "+
        "wooden bowl with a pleading look on "+ TP->query_possessive() +
        " face. You feel sorry for this poor creature...\n");
    return 1;
}

int
read_label(string str)
{
    notify_fail("Read what?\n");
    if (!str || str != "words")
        return 0;
    write("You try to decipher the engraved letters on the "+
        "bottom of the bowl: \n\n"+
        "To beg for coins, just bbeg. If you see some coins around "+
        "then you bgrab, to empty the bowl ... bempty. You can "+
        "also nap on the edge of them rich folks robes with bnap, but "+
        "before doing that, you better search for good victims with "+
        "bsearch! Finally, after a long day of begging you can "+
        "check how much you have earned with bcount and "+
        "fill your bowl with all the earnings with bput.\n\n"+
        "      Product of the beggars guild. (tm) \n");
    return 1;
}

