
/*
   This is the main guild object for the 
   granted members of the Elemental Worshippers guild.

   Coded by Jaacar

   Modifications by Maniac 27/9/96.
   Emotes added by Jaacar 25/2/97. 
*/

#pragma save_binary

#include "defs.h"

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include WORSHIP_HEADER

#define LAY_CMDSOUL "/d/Calia/worshippers/specials/worshipsoul"
#define HIS this_player()->query_possessive()
#define HE this_player()->query_pronoun()
#define HIM this_player()->query_objective()

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

void
check_soul(object tp)
{
    seteuid(getuid());
    if (member_array(LAY_CMDSOUL, tp->query_cmdsoul_list()) == -1)
    {
        tp->add_cmdsoul(LAY_CMDSOUL);
        tp->update_hooks();
    }
}

string
query_auto_load()
{
    return MASTER + ":";
}

int
sbackscratch(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (!str)
    {
        write("You scratch your back with your sceptre.\n");
        say(QCTNAME(tp)+" scratches "+HIS+" back with "+HIS+
            " sceptre.\n");
        return 1;
    }
    
    notify_fail("Scratch who's back with your sceptre?\n");

    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1)  
        return 0;
    else  
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You scratch "+QTNAME(who)+"'s back with your "+
        "sceptre.\n");
    who->catch_msg(QCTNAME(tp)+" scratches your back with "+HIS+
        " sceptre.\n");
    tell_room(environment(tp), QCTNAME(tp)+" scratches "+QTNAME(who)+"'s "+
        "back with "+HIS+" sceptre.\n",({tp,who}));
    return 1;
}

int
sbonk(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (!str)
    {
        notify_fail("Bonk who with your sceptre?\n");
        return 0;
    }
    
    notify_fail("Bonk who with your sceptre?\n");

    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1) 
        return 0;
    else  
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You bonk "+QTNAME(who)+" on the head with your sceptre.\n");
    who->catch_msg(QCTNAME(tp)+" bonks you on the head with "+HIS+
        " sceptre to let you know how foolish you are acting.\n");
    tell_room(environment(tp), QCTNAME(tp)+" bonks "+QTNAME(who)+" on the "+
        "head with "+ HIS+" sceptre to let them know how foolish "+
        "they are acting.\n",({tp,who}));
    return 1;
}

int
sbrandish()
{
    object tp;
    tp = this_player();
    
    write("You brandish your sceptre overhead in defiance.\n");
    say(QCTNAME(tp)+" brandishes "+HIS+" sceptre above "+
        HIS+" head defiantly.\n");
    return 1;
}

int
sbuttscratch(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (!str)
    {
        write("You scratch your butt with your sceptre.\n");
        say(QCTNAME(tp)+" scratches "+HIS+" butt with "+HIS+
            " sceptre.\n");
        return 1;
    }
    
    notify_fail("Scratch who's butt with your sceptre?\n");

    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1)  
        return 0;
    else  
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You scratch "+QTNAME(who)+"'s butt with your "+
        "sceptre.\n");
    who->catch_msg(QCTNAME(tp)+" scratches your butt with "+HIS+
        " sceptre.\n");
    tell_room(environment(tp), QCTNAME(tp)+" scratches "+QTNAME(who)+"'s "+
        "butt with "+HIS+" sceptre.\n",({tp,who}));
    return 1;
}

int
seye()
{
    object tp;
    tp = this_player();
    write("You turn your eyes to your sceptre, losing yourself "+
        "in thought as you run your fingers caressingly down its "+
        "length.\n");
    say(QCTNAME(tp)+" turns "+HIS+" eyes to "+HIS+" sceptre, lost in "+
        "thought as "+HE+" runs "+HIS+" fingers caressingly down its "+
        "length.\n");
    return 1;
}

int
spalm()
{
    object tp;
    tp = this_player();
    write("You repeatedly slap your sceptre in the palm of "+
        "your hand while thinking violent thoughts.\n");
    say(QCTNAME(tp)+" repeatedly slaps "+HIS+" sceptre in the "+
        "palm of "+HIS+" other hand while "+HE+" thinks "+
        "violent thoughts.\n");
    return 1;
}

int
shelp()
{
    write("The following emotes are available with this staff:\n"+
        "   sbonk, sbackscratch, sbrandish, spalm, seye, spoke,\n"+
        "   spoint, sshove, stap, and stwirl.\n");
    return 1;
}

int
splant()
{
    object tp;
    int section;
    tp = this_player();
    
    if (environment(tp)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        notify_fail("You can't plant your sceptre underwater!\n");
        return 0;
    }

    section = tp->query_skill(SS_PATRON_ELEMENTAL);
    switch(section)
    {
        case FIRE_FLAG:
            write("You firmly plant your sceptre into the ground.\n"+
                "The orb suddenly begins to glow red hot, then "+
                "shoots forth a three foot pillar of coalescing flames "+
                "into the sky.\nAs you lift your sceptre from the ground, "+
                "the flames vanishes without a trace, save the small cloud "+
                "of smoke where they once stood.\n");
            say(QCTNAME(tp)+" firmly plants "+HIS+" sceptre into the "+
                "ground before "+HIM+".\nThe orb on the tip of the sceptre "+
                "suddenly begins to glow red hot, then shoots forth a "+
                "three foot pillar of coalescing flames into the sky.\n"+
                "As "+HE+" lifts "+HIS+" sceptre, the flames vanish without "+
                "a trace, save the small cloud of smoke where they once stood.\n");
            break;
        case EARTH_FLAG:
            write("You firmly plant your sceptre into the ground.\n "+
                "The orb suddenly begins to glow dark green.  The shaft "+
                "begins to vibrate as the orb becomes brighter.  With "+
                "a sudden flash of light from the orb, the vibration is "+
                "sent into the ground, causing it to rumble and tremor "+
                "violently.\nAs you lift your sceptre from the ground, it "+
                "gives one last reverberation, then ceases.\n");
            say(QCTNAME(tp)+" firmly plants "+HIS+" sceptre into the "+
                "ground before "+HIM+".\nThe orb on the tip of the "+
                "sceptre suddenly begins to glow dark green.  The shaft "+
                "seems to begin vibrating.  In a sudden flash of light, "+
                "the ground begins to rumble and tremor violently all "+
                "around you.\nAs "+HE+" lifts "+HIS+" sceptre from the "+
                "ground, the earth gives one last reverberation, then "+
                "ceases.\n");
            break;
        case WATER_FLAG:
            write("You firmly plant your sceptre into the ground.\n "+
                "The orb suddenly begins to glow bright blue.  The shaft "+
                "below the orb begins changing colour to a bright blue as "+
                "if water was flowing down the inside of it.  As the "+
                "colour reaches the end of the shaft and enters the ground, "+
                "water starts spouting forth from the depths of the earth, "+
                "shooting into the air above your head.\nAs you lift "+
                "your sceptre from the ground, the water vanishes without "+
                "a trace.\n");
            say(QCTNAME(tp)+" firmly plants "+HIS+" sceptre into the "+
                "ground before "+HIM+".\nThe orb on the tip of the "+
                "sceptre suddenly begins to glow bright blue.  The shaft "+
                "below the orb begins to change colour to a bright blue "+
                "as if water was flowing down the inside of it.  As the "+
                "colour reaches the end of the shaft and enters the ground, "+
                "water starts spouting forth from the depths of the earth, "+
                "shooting into the air above your head.\nAs "+HE+" lifts "+
                HIS+" sceptre from the ground, the water vanishes without "+
                "a trace.\n");
            break;
        default:
            write("You firmly plant your sceptre into the ground.\n "+
                "The orb suddenly begins to glow bright white.  Winds form, "+
                "encompassing you, swirling aggressively around your body.  "+
                "They suddenly rise into the air forming a large funnel "+
                "standing twenty feet above you.\nAs you lift your sceptre "+
                "from the ground, the funnel explodes, sending winds in "+
                "all directions around you.\n");
            say(QCTNAME(tp)+" firmly plants "+HIS+" sceptre into the "+
                "ground before "+HIM+".\nThe orb on the tip of the "+
                "sceptre suddenly begins to glow bright white.  Winds form, "+
                "encompassing "+HIM+", swirling aggressively around "+HIS+
                " body.  They suddenly rise into the air forming a large "+
                "funnel standing twenty feet above "+HIM+".\nAs "+HE+
                " lifts "+HIS+" sceptre from the ground, the funnel "+
                "explodes, sending winds in all directions around you.\n");
            break;
    }
    return 1;
}

int
spoint(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (!str)
    {
        notify_fail("Point at who with your sceptre?\n");
        return 0;
    }
    
    notify_fail("Point at who with your sceptre?\n");

    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1)  
        return 0;
    else
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You point at "+QTNAME(who)+" with your sceptre.\n");
    who->catch_msg(QCTNAME(tp)+" points at you with "+HIS+" sceptre.\n");
    tell_room(environment(tp), QCTNAME(tp)+" points at "+QTNAME(who)+" with "+
        HIS+" sceptre.\n",({tp,who}));
    return 1;
}

int
spoke(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (!str)
    {
        notify_fail("Poke who with your sceptre?\n");
        return 0;
    }
    
    notify_fail("Poke who with your sceptre?\n");

    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1)  
        return 0;
    else  
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You poke "+QTNAME(who)+" with your sceptre.\n");
    who->catch_msg(QCTNAME(tp)+" pokes you with "+HIS+" sceptre.\n");
    tell_room(environment(tp), QCTNAME(tp)+" pokes "+QTNAME(who)+" with "+
        HIS+" sceptre.\n",({tp,who}));
    return 1;
}

int
sshove(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (!str)
    {
        notify_fail("Shove your sceptre down who's throat?\n");
        return 0;
    }
    
    notify_fail("Shove your sceptre down who's throat?\n");

    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1)  
        return 0;
    else  
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You shove your sceptre down "+QTNAME(who)+"'s throat "+
        "in anger.\n");
    who->catch_msg(QCTNAME(tp)+" shoves "+HIS+" sceptre down your "+
        "throat in anger.\n");
    tell_room(environment(tp), QCTNAME(tp)+" shoves "+HIS+" sceptre "+
        "down "+QTNAME(who)+"'s throat in anger.\n",({tp,who}));
    return 1;
}

int
stap(string str)
{
    object tp, who, *obs;
    
    tp = this_player();
    if (environment(tp)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        notify_fail("You can't tap your sceptre underwater!\n");
        return 0;
    }

    if (!str)   
    {
        write("You tap your sceptre on the ground attempting to "+
            "get everyone's attention.\n");
        say(QCTNAME(tp)+" taps "+HIS+" sceptre on the ground in an "+
            "attempt to get everyone's attention.\n");
        return 1;
    }
    
    notify_fail("Tap your sceptre at who?\n");
    if (!parse_command(lower_case(str), environment(tp), " %l ", obs))
        return 0;
    if (sizeof(obs) <= 1)  
        return 0;
    else  
    {
        who = obs[1];
        if (!CAN_SEE(TP, who)) return 0; 
        else if (who == tp) return 0;
    }

    tp->catch_msg("You tap your sceptre on the ground in an attempt to "+
        "get "+QTNAME(who)+"'s attention.\n");
    who->catch_msg(QCTNAME(tp)+" taps "+HIS+" sceptre on the "+
        "ground in an attempt to get your attention.\n");
    tell_room(environment(tp), QCTNAME(tp)+" taps "+HIS+" sceptre on the "+
        "ground in an attempt to get "+QTNAME(who)+"'s attention.\n",
        ({tp,who}));
    return 1;
}

int
stwirl()
{
    object tp;
    tp = this_player();
    write("You twirl your sceptre around your hand.\n");
    say(QCTNAME(tp)+" twirls "+HIS+" sceptre around "+HIS+" hand.\n");
    return 1;
}

void
create_object()
{
    set_name("sceptre");
    add_name("worshipper_sceptre");
    set_short("long sceptre");
    set_long("This long sceptre is carved from a fine wood, "+
        "sheathed in a swirling mixture of platinum, gold, "+
        "silver and copper, and stands about five feet in length.  "+
        "Atop of the sceptre is a large golden orb "+
        "with the words Pyros, Diabrecho, Gu, and Aeria carved around "+
        "the outer edges of it.  Carved just below the orb in elemental "+
        "runes is 'shelp' and 'help worshippers'.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,5);
    add_prop(OBJ_M_NO_STEAL,1);
}

init()
{
    object tp = this_player();
    ::init();
    if (is_worship(tp))
        set_alarmv(0.5,0.0,"check_soul",({tp}));
    add_action("sbonk","sbonk");
    add_action("sbackscratch","sbackscratch");
    add_action("sbrandish","sbrandish");
    add_action("sbuttscratch","sbuttscratch");
    add_action("seye","seye");
    add_action("shelp","shelp");
    add_action("spalm","spalm");
    add_action("splant","splant");
    add_action("spoke","spoke");
    add_action("spoint","spoint");
    add_action("sshove","sshove");
    add_action("stap","stap");
    add_action("stwirl","stwirl");
}
