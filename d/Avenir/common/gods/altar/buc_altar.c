// file name:   /d/Avenir/common/holm/obj/buc_altar.c
// creator(s):  Lilith, May '97
// revision(s): 
// purpose:     Altar for worship of Bucaphi
// note:             
// bug(s):           
// to-do:


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
    set_adj(({"singing"}));
    add_name(({"circle", "stones"}));
    set_altar_name("bucaphi");
    set_god("bucaphi");
    set_altar_short("circle of singing stones");    
    
    set_id_long("This is a small circle of irridescent stones, "+
        "each emitting a pleasing hum reminiscent of tuning forks. "+
        "Symbols representing musical instruments have been carved "+
        "into the stones, along with the single flowing glyph repre"+
        "senting the goddess Bucaphi.");
    set_unid_long("This is a small circle of irridescent stones, "+
        "each emitting a pleasing hum reminiscent of tuning forks. "+
        "Symbols representing musical instruments have been carved "+
        "into the stones, along with a single flowing glyph.\n");
    add_item(({"rune", "glyph", "flowing glyph"}), "@@my_symbol");
    add_item(({"symbols", "symbol", "instruments" }),
        "There are many musical instruments carved into the "+
        "stones. Some of them you recognize as flutes, harps, "+
        "lyres, and sitars.\n");

    set_bless_command(({"bless", "sanctify"}));
    set_offer_command(({"offer", "sacrifice", "donate"}));
    set_offering_prop(({UNIVERSAL_OFFERING}));
    set_pray_command(({"pray", "supplicate", "chant"}));
    set_worship_command(({"worship", "genuflect"}));

    set_offer_max(10);
    add_prop(OBJ_M_NO_GET, "The stones are far too heavy to be gotten.\n");
}                                                                            

string
my_symbol()
{
    /*    check if player identifies the altar */
    if  (!id_altar_check(this_player()))
        return "This glyph is unique to Bucaphi, Goddess of music. "+
               "It begins as an oval, with a tail that bends away "+
               "at a right angle and seems to flutter before your "+
               "eyes.\n";
    else
        return "This rune begins as an oval, with a tail that "+
               "bends away at a right angle and seems to flutter "+
               "before your eyes.\n";
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
    pl->catch_msg("The "+ short() +" responds to the sound of your voice "+
       "with an increase in sound that is very pleasant to your ears.\n");
    say(QCTNAME(pl) +" chants before the "+ short() +", causing the stones "+
       "to sing more loudly.\n");
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
    pl->catch_msg("As you genuflect before the "+ short() +", music "+
       "washes over and through you, sending you soaring "+
       "on a tide of elation.\n");
    pl->command("$ smile elate");
    say(QCTNAME(pl) +" genuflects before the "+ QSHORT(TO) +", causing "+
       "beautiful music to flood the garth.\n");
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
        write("You raise your voice in a chant as you "+ qvb +" to "+
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
        write("You raise your voice in a chant as you "+ qvb +" "+
            capitalize(query_god()) +".\n");
        wor_text(pl, qvb);        
        altar_result_pos(pl, qvb);
        return 1;
    }
    write("You take a moment to "+ qvb +" the diety to whom this "+
        "altar was erected.\n");
    return 1;

}

