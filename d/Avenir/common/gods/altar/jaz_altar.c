// file name:   /d/Avenir/common/gods/obj/jaz_altar.c
// creator(s):  Lilith, Aug 2003
// revision(s): 
// purpose:     Altar for the Union
// note:             
// bug(s):           
// to-do:  add kneel, penance, and meditate, all of which require time.
//         ALSO tie this to the meeting room prop added when the
//         star is pushed.
//         perform ritual/ceremony

inherit "/d/Avenir/inherit/altar";
#include "/d/Avenir/include/deities.h"   /* Altar & diety-related defines */
#include "/d/Avenir/include/relation.h"  /* Sybarite status defines */
#include <composite.h>
#include <cmdparse.h> 
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define  TP this_player()
#define  TO this_object()

void
create_altar()
{
    set_name("altar");
    set_adj(({"spinning", "blue-black", "blue", "black"}));
    add_name(({"orb", "sphere", "slab", "alcintaron,","jazur_altar"}));
    set_altar_name("alcintaron");
    set_altar_hour("12");
    set_god("jazur");
    set_altar_short("orb spinning over a slab");    
    
    set_id_long("You marvel at the hand that created such a "+
       "numinous wonder.\n"+
       "Above a simple, circular slab spins an orb that appears "+
       "at first glance to be solid, but a moment later is revealed "+
       "to be a commingling of shadows dancing in complex fractal "+
       "harmony with uncountable points of light. From this angle "+
       "the flame seems to rise from the orb, its flickering light "+
       "set aswirl as it catches on the dark metals and gemstones "+
       "in the room. A simple phrase in curling, graceful script is "+
       "repeated around the base of the slab.");
    set_unid_long("A dark orb spins above a circular slab. Beyond "+
       "it rises a flame whose flickering light catches upon the "+
       "the metals and gems in the room, causing you to feel dizzy "+
       "and somewhat disoriented.\n");
    add_item(({"surface", "base", "slab", "circular slab", "phrase",
        "carvings", "script", "word", "words"}), 
        "@@my_symbol");
    add_cmd_item(({"surface", "base", "slab", "circular slab", "phrase",
        "carvings", "script", "word",  "words"}), "read",
        "@@my_symbol");
    add_cmd_item( ({"surface", "base", "slab", "circular slab", 
        "phrase", "carvings", "script", "word", "words", 
        "alcintaron"}),
        ({"touch", "feel"}),
        "You run your fingers over it, feeling the smooth grooves "+
        "of the script\n.");
    set_bless_command(({"bless", "sanctify"}));
    set_offer_command(({"offer", "sacrifice", "donate"}));
    set_offering_prop(({JAZUR_OFFERING, UNIVERSAL_OFFERING}));
    set_pray_command(({"pray", "supplicate", "petition"}));
    set_worship_command(({"worship", "respect", "revere", "honour",
        "celebrate"}));

    set_offer_max(20);
    set_no_show_composite(1);  //don't want it to show up in room desc.
    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be gotten.\n");
}                                                                            

/*
 * Function name: id_altar_check
 * Description:   Called to check if player identifies the altar.
 * Arguments:	  player - The player
 * Returns:       1 for identification, else 0.
 */
varargs int
id_altar_check(object player)
{
    return 1;
}


string
my_symbol()
{
    return "The base is smooth and perfectly circular. Along "+
           "the edge the following phrase is repeated: By my hand, "+
           "through Jazur's grace. Alcintaron.\n";
}

/*
 * Function name:  pray_text
 * Description:    Here the prayer/worship message is written. 
 *                 You may redefine it if you wish.
 * Arguments:      qvb  - The verb used (pray or worship)
 */
void
pray_text(object pl, string qvb)
{
    pl->catch_msg("You kneel before the "+ QSHORT(TO) +", and stare into "+
       "its depths.\nAs the words of your prayer flare within your mind "+
       "an intense heat passes through you, fading to pulsing warmth.\n");
    say(QCTNAME(pl) +" appears to be praying before the "+ QSHORT(TO) +".\n");
}


/*
 * Function name:  wor_text
 * Description:    Here the prayer/worship message is written. 
 *                 You may redefine it if you wish.
 * Arguments:      qvb  - The verb used
 */
void
wor_text(object pl, string qvb)
{
    pl->catch_msg("You cast yourself into a moment of sheer passion, "+
       "losing yourself on the tide of Jazur's grace.\nFor what could "+
       "be a moment, or an eternity, you are drawn into the orb.\n"+
       "Your essence merges with the others who came before you, those "+
       "other selves long gone, some whose names have faded beyond "+
       "memory, and you know unity, acceptance, and passionate joy.\n");
    pl->command("$ joy");
    say(QCTNAME(pl) +" appears to be worshipping before the "+ 
        QSHORT(TO) +".\n");
}


/*
 * Function name:  do_pray
 * Description:    It is possible to pray at the altar.
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_pray(string str)
{
    string qvb;
    object pl = this_player();

    notify_fail("The "+ QSHORT(TO) +" is defiled! You cannot "+ qvb +" here.\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;
    
    notify_fail("You pray.\n");
    if (!str || !strlen(str))    
        return 0;
    
    qvb = query_verb();
    notify_fail(capitalize(qvb) +" how?\n");
    if (!parse_command(str, ({ }), 
        "[me] / [myself] [at] / [to] [the] 'altar' / '"+ 
        query_god() +"' / '"+ query_altar_name() +"'"))
        return 0;    

    if (id_altar_check(this_player()))
    {      
        write("You clear your mind, preparing to "+ qvb +" to "+
            capitalize(query_god()) +".\n");
        pray_text(pl, qvb);        
        altar_result_pos(pl, qvb);
        return 1;
    }
    write("You take a moment to "+ qvb +" to the diety to whom this "+
        "altar was erected.\n");
    return 1;
}

/*
 * Function name:  do_worship
 * Description:    Default worship add_action (same as pray for now)
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_worship(string str)
{
    string qvb;
    object pl = this_player();

    notify_fail("The "+ QSHORT(TO) +" is defiled! You cannot "+ qvb +" here.\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;
    
    notify_fail(capitalize(qvb) +" whom?\n");
    if (!str || !strlen(str))    
        return 0;
    
    qvb = query_verb();
    notify_fail(capitalize(qvb) +" how?\n");
    if (!parse_command(str, ({ }), "[at] / [to] [the] 'altar' / '"+ 
        query_god() +"' / '"+ query_altar_name() +"'"))
        return 0;    

    if (id_altar_check(this_player()))
    {      
        write("You assume the proper posture to "+ qvb +" "+
            capitalize(query_god()) +", raising your arms "+
            "toward the orb and the flame.\n");
        wor_text(pl, qvb);        
        altar_result_pos(pl, qvb);
        return 1;
    }
    write("You take a moment to "+ qvb +" to the diety to whom this "+
        "altar was erected.\n");
    return 1;

}

