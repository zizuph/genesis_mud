
/*
 * Magic Trident for the King of Thalassia
 *
 * This is the magic trident that the King of Thalassia wields.
 * Special thanks to Mayhem and all others who worked on Magebane,
 *     where some of this code is based off of.
 *
 * Additional thanks to Shiva for being so kind as to help me
 *     out with a different way to get this thing to scream
 *     at people.
 *
 * Copyright (C): Jaacar, Jul 22, 2003
 *
 *
 * Change log:   Baldacin, May 10, 2004. 
 *                  Fixed a runtime in farewell_message(), it was
 *                  sending the messages to TP's environment instead
 *                  of the 'closest' room of the trident.
 *                  Also did a check in trident_talk() to see if
 *                  query_wielded() is valid before sending messages
 *                  to it.
 *                  In tri_unwield_msg() it sent messages to TP which
 *                  most likely could be someone else after a few hundred
 *                  seconds of alarming. Changed it to env of TO, if it
 *                  was a living.
 *               Petros, September 5, 2008
 *                  tell_watcher removed. Should use the mudlib one
 *                  instead. 
 *               Petros, June 2009
 *                  fixed another runtime in farewell_message with
 *                  no actual room environment available.
 *
 * Carnak: September 8th 2017.
 * - Added a prop to allow for altering the weapon to a hoopak.
 */

#pragma strict_types
#pragma save_binary

inherit "/std/weapon";

#include <filter_funs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>
#include <files.h>
#include "/d/Calia/abbrev.h"
#include "defs.h"

object wielder;
int talk_alarm_id, unwield_alarm_id, farewell_alarm_id;
public void farewell_message();
int message_alarm_id = 0;

#define  PARRY_PENALTY     10
#define  DEFENCE_PENALTY   10
#define  TRIDENT_DEF_PENALTY "_trident_def_penalty"
#define  TRIDENT_PAR_PENALTY "_trident_par_penalty"

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

void
create_weapon()
{
    set_name("trident");
    set_short("golden trident");
    set_long("It is a very large golden trident.  You can see it "+
        "pulsing with power.  The shaft is decorated with cryptic "+
        "runes which you do not understand.\n");
    set_adj("golden");
    add_item("cryptic runes","These runes are written in an ancient "+
        "language that you just can't seem to understand.\n");
    set_hit(50 + random(10));
    set_pen(50 + random(10));
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);
    
/* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
   
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(55,55) + 1500);
    add_prop(OBJ_I_WEIGHT, 28000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(MAGIC_AM_MAGIC,({40, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This enchanted weapon will only allow "+
        "a person with certain attributes to wield it.",10,
        "The wielder must have great strength, intelligence and skill to use "+
        "this enchanted weapon. It is also especially effective against "+
        "certain types of foes.",25,
        "The wielder must have great strength and intelligence plus the "+
        "polearm skill of a confident professional to wield this "+
        "magnificent enchanted weapon of kroug slaying.",50,
        "The wielder of this intelligent and enchanted trident must "+
        "have hefty strength, be quick-minded and a skill in polearms "+
        "of at least confident professional. This trident possesses "+
        "the soul of an ancient Kyrulian who lost his life fighting "+
        "krougs, defending his island homelands.",70}));

    add_prop(OBJ_S_WIZINFO,"The user must have a 65 strength, "+
        "80 intelligence and a 65 polearm to wield this. It "+
        "is an intelligent and magical trident that harnesses "+
        "the soul of an ancient Kyrulian that has a bitter "+
        "hatred for krougs (afterall, they destroyed his entire "+
        "way of life when they attacked the islands and forced "+
        "the Elementals to sink them into the sea). The wielder "+
        "gets a decrease in both parry and defence skills (10 "+
        "points each) if they have them. It does extra (10-40%) "+
        "damage to krougs.\n");

    seteuid(getuid(TO));
}

static void
tell_watcher(string str, object enemy)
{
    object wielder, *ob;
    int i;

    wielder = query_wielded();
    wielder->tell_watcher(str, enemy);
}

/*
 *  FUNCTION: did_hit
 *  Arguments: int aid, string hdesc, int phurt, object enemy, int dt,
               int phit, int dam 
 *  Returns  : int (0,1) 
 * 
 * This is the special attack function
 *
 */

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   
    if ((enemy->query_race_name() == "kroug") ||
        (enemy->query_race_name() == "water-kroug"))
    {
        enemy->heal_hp(-(((dam*(random(4)+1))/10)));
    }

    switch(phurt)
        {
        case -1:
            wielder->catch_msg("You thrust your " + short() + ", just "+
                "barely missing "+QTNAME(enemy)+".\n");
            enemy->catch_msg(QCTNAME(wielder)+"'s " + short() + " thrusts at "+
                "you forcefully.  You barely manage to escape its blow.\n");
            tell_watcher(QCTNAME(wielder)+"'s " + short() + " barely "+
                "misses "+QTNAME(enemy)+".\n",enemy);
            break;

         case 0:
             wielder->catch_msg("You thrust the " + this_object()->query_name() +
                " very close to " + QTNAME(enemy) + ", only narrowly missing " +
                "your victim.\n");
             enemy->catch_msg(QCTNAME(wielder) + " thrusts the " +
                this_object()->query_name() + " very close to you, " +
                "only narrowly missing you.\n");
             tell_watcher(QCTNAME(wielder) + " thrusts the " +
                this_object()->query_name() + " at " + QTNAME(enemy) +
                " and narrowly misses.\n", enemy);
             break;

         case 1..4:
             wielder->catch_msg("You graze the flesh of "+
                 QTNAME(enemy)+" with your " + short() + ".\n");
             enemy->catch_msg(QTNAME(wielder)+" grazes your flesh "+
                 "with "+wielder->query_possessive()+" " + short() + ".\n");
             tell_watcher(QTNAME(wielder)+" grazes the flesh of "+
                 QTNAME(enemy)+" with "+wielder->query_possessive()+" " + short() +
                 ".\n",enemy);
             break;
         
         case 5..9:
             wielder->catch_msg("You violently slash the skin of "+QTNAME(enemy)+
                 " with your " + short() + ".\n");
             enemy->catch_msg(QCTNAME(wielder)+" violently slashes your skin "+
                 "with "+wielder->query_possessive()+" " + short() + ".\n");
             tell_watcher(QCTNAME(wielder)+ " violently slashes "+QTNAME(enemy)+
                 "'s skin with "+wielder->query_possessive()+" " + short() +
                 ".\n",enemy);
             break;
         
         case 10..14:
             wielder->catch_msg("Your " + short() + " glows brightly as "+
                 "it cuts deeply into "+QTNAME(enemy)+".\n");
             enemy->catch_msg("You see "+QTNAME(wielder)+"'s " + short() + " glow "+
                 "brightly as it cuts deeply into you.\n");
             tell_watcher("You see "+QTNAME(wielder)+"'s " + short() + " "+
                 "glow brightly as it cuts deeply into "+
                 QTNAME(enemy)+".\n",enemy);
             break;
         
         case 15..19:
             wielder->catch_msg("Your " + short() + " vibrates rapidly as it "+
                 "tears a large gash in "+QTNAME(enemy)+"'s side.\n");
             tell_watcher(QTNAME(wielder)+"'s " + short() + " vibrates rapidly "+
                 "as it tears a large gash in "+QTNAME(enemy)+"'s "+
                 "side.\n",enemy);
             enemy->catch_msg(QCTNAME(wielder)+"'s " + short() + " vibrates rapidly "+
                 "as it tears a large gash in your side.\n");
             break;
         
         case 20..24:
             wielder->catch_msg("Your " + short() + " seems to come to life "+
                 "and burrows itself far within "+QTNAME(enemy)+"'s body.\n");
             enemy->catch_msg(QCTNAME(wielder)+"'s " + short() + " seems to come "+
                 "to life and burrows itself far within your body.\n");
             tell_watcher(QCTNAME(wielder)+"'s " + short() + " seems to come to "+
                 "life as it burrows itself far within "+QTNAME(enemy)+
                 "'s body.\n",enemy);
             break;
         
         case 25..30:
             wielder->command("cackle sadistically");
             wielder->catch_msg("You thrust the " + short() + " into "+
                 QTNAME(enemy)+"'s chest, leaving large, gaping wounds.\n");
             enemy->catch_msg(QCTNAME(wielder)+" thrusts "+
                 wielder->query_possessive()+" " + short() + " into your chest, "+
                 "leaving large, gaping wounds.\n");
             tell_watcher(QCTNAME(wielder)+" thrusts "+wielder->query_possessive()+
                 " " + short() + " into "+QTNAME(enemy)+"'s chest, leaving "+
                 "large, gaping wounds.\n",enemy);
             break;
         
         case 31..50:
             wielder->command("laugh violently");
             wielder->catch_msg("You laugh out loud as your " + short() + " "+
                 "rams into the arm of "+QTNAME(enemy)+".\n");
             enemy->command("scream");
             enemy->catch_msg("You scream out in pain as "+QTNAME(wielder)+
                 "'s " + short() + " rams itself into your arm.\n");
             tell_watcher(QCTNAME(enemy)+" screams out in pain as "+
                 QTNAME(wielder)+"'s " + short() + " rams into "+
                 QTNAME(enemy)+"'s arm.\n",enemy);
             break;
         
         default:
             wielder->catch_msg("You thrust your " + this_object()->query_name() +
                " heartlessly into "+ QTNAME(enemy)+"'s head, causing it to " +
                "glow very brightly.\n");
             enemy->catch_msg(QCTNAME(wielder)+" heartlessly thrusts "+
                 wielder->query_possessive()+" " + this_object()->query_name() +
                 " into your head, causing it to glow very brightly.\n");
             tell_watcher(QCTNAME(wielder)+" heartlessly thrusts "+
                 wielder->query_possessive()+" " + short() + " into "+QTNAME(enemy)+
                 "'s head, causing it to glow very brightly.\n",enemy);
             break;
        }

        if(enemy->query_hp()<=0)
        {
            enemy->command("scream");
            enemy->catch_msg(QCTNAME(wielder)+" drives "+wielder->query_possessive()+
                short() + " right through the centre of your body, "+
                "causing you to go into massive convulsions before dying.\n"+
                QCTNAME(wielder)+" coldly pushes your lifeless body off "+
                wielder->query_possessive()+" " + this_object()->query_name() +
                " with " + wielder->query_possessive()+" foot.\n");
            wielder->catch_msg("You drive your " + this_object()->query_name() +
                " right through the centre of "+QTNAME(enemy)+", causing them " +
                "to go into massive convulsions before dying.\nYou coldly push "+
                "the corpse off of your " + this_object()->query_name() +
                " with your foot.\n");
            tell_watcher(QCTNAME(wielder)+" drives "+wielder->query_possessive()+
                short() + " right through the centre of "+
                QTNAME(enemy)+" causing them to go into massive convulsions "+
                "before dying.\n"+QCTNAME(wielder)+" coldly pushes the corpse "+
                "off of "+wielder->query_possessive()+" " +
                this_object()->query_name() + " with "+
                wielder->query_possessive()+" foot.\n",enemy);
            
            if(enemy->query_average_stat() < wielder->query_average_stat()-30)
                set_alarm(1.0,0.0,"easy_win");
            if(enemy->query_average_stat() > wielder->query_average_stat()-29
             && enemy->query_average_stat() < wielder->query_average_stat()+10)
                    set_alarm(1.0,0.0,"avg_win");
            if(enemy->query_average_stat() > wielder->query_average_stat()-30)
                set_alarm(1.0,0.0,"hard_win"); 
            enemy->do_die(wielder);

        }
    return 1;
}

/*
 *  FUNCTION: wield
 *  Arguments: object ob
 *  Returns  : int (0,1)
 * 
 * This function is called when someone wields the trident
 *
*/

mixed
wield(object ob)
{
    if(ob!=TO)
        return 0;
   
    if(TP->query_base_stat(SS_STR)>64)
    {
        if(TP->query_base_stat(SS_INT)>79)
        {
            if(TP->query_skill(SS_WEP_POLEARM)>64)
            {
                wielder = this_player();
                write("You struggle momentarily, then take control of "+
                    "the "+short()+". As you grip it tightly, "+
                    "the cryptic runes glow briefly. You hear a voice "+
                    "in your head saying: \"Yes, finally someone who "+
                    "is worthy of my skills.\"\n");
                if ( TP->query_skill(SS_DEFENCE) > 10 )
                {
                    TP->set_skill_extra(SS_DEFENCE,
                        TP->query_skill_extra(SS_DEFENCE) - DEFENCE_PENALTY);
                    TP->add_prop(TRIDENT_DEF_PENALTY,1);
                }
                if (TP->query_skill(SS_PARRY) > 10 )
                {
                    TP->set_skill_extra(SS_PARRY,
                        TP->query_skill_extra(SS_PARRY) - PARRY_PENALTY);
                    TP->add_prop(TRIDENT_PAR_PENALTY,1);
                }
                remove_alarm(unwield_alarm_id);
                talk_alarm_id = set_alarm(90.0,145.0,"trident_talk");
                return 0;
            }
        }
    }

    TP->heal_hp(-random(150)-20);
    return "The " + this_object()->query_name() + " glows brightly and gets " +
        "so hot that it burns you severely. You hear a voice in your head " +
        "that says: "+
        "\"You do not possess the skills needed to wield me! Give me "+
        "to someone more worthy of my power!\"\n";
}

/*
 *  FUNCTION: unwield
 *  Arguments: N/A
 *  Returns  : int (0,1)
 * 
 *  This is called when someone unwields the trident
 *
*/

int 
unwield()
{
    object wielder = query_wielded();
    remove_alarm(talk_alarm_id);
    wielder->catch_msg("As you release your grip on the "+short()+" it "+
        "glows briefly and you hear a voice in your head saying: "+
        "\"Wait! What are you doing? I need more blood! Do not "+
        "leave me!\"\nYou unwield the "+short()+".\n");
    say(QCTNAME(wielder)+" unwields the "+short()+".\n");
    
    if (TP->query_prop(TRIDENT_DEF_PENALTY))
    {
        TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE)+
            DEFENCE_PENALTY);
        TP->remove_prop(TRIDENT_DEF_PENALTY);
    }
    
    if (TP->query_prop(TRIDENT_PAR_PENALTY))
    {                                       
        TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY)+
            PARRY_PENALTY);
        TP->remove_prop(TRIDENT_PAR_PENALTY);
    }
    
    unwield_alarm_id = set_alarm((itof(random(30)+30)),145.0,"tri_unwield_msg");
    return 1;
}

/*
 *  FUNCTION: tri_unwield_msg
 *  Arguments:   N/A
 *  Returns  :   N/A
 * 
 *  This function gives messages to the player when they unwield the
 *  trident but don't drop it. 
 *
*/

void
tri_unwield_msg()
{
    object who;
    
    who = environment(TO);
    
    if (!living(who))
        return;
        
    switch(random(4))
    {
        case 0:
            who->catch_tell("The " + short() + " you are holding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"What are you doing? Wield me! I shall help you "+
                "vanquish your foes!\"\n");
            break;
        case 1:
            who->catch_tell("The " + short() + " you are holding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"I must feed! Give me blood!\"\n");
            break;
        case 2:
            who->catch_tell("The " + short() + " you are holding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"The krougs! All krougs must pay! Wield me and "+
                "take me to the krougs!\"\n");
            break;
        default:
            who->catch_tell("The " + short() + " you are holding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"I am the most powerful weapon you have. Wield "+
                "me!\"\n");
            break;
    }
    
}

public string
query_recover()
{
    return MASTER+":"+query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}

/*
 *  FUNCTION: trident_talk
 *  Arguments: N/A
 *  Returns  : N/A
 * 
 * This function gives messages to the wielder while they are wielding
 * the trident
 *
*/

void 
trident_talk()
{           
    object wielder = query_wielded();
    
    if(!wielder)
    {
        remove_alarm(talk_alarm_id);
        return;
    }
    
    if(wielder->query_attack())
        return;

    if(TO->query_prop(OBJ_I_BROKEN)) 
    {
        remove_alarm(talk_alarm_id);
        return;
    }

    switch(random(7))
    {
        case 0:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"I must feed! Give me blood!\"\n");
            break;
        case 1:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"With my help, you shall vanquish all of your foes!\"\n");
            break;
        case 2:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"It is good to be in the hands of someone with "+
                "skill enough to use my powers.\"\n");
            break;
        case 3:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"Krougs! Give me the blood of krougs!\"\n");  
            break;
        case 4:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"Yes, we shall make a fine team, you and I.\"\n");
            break;
        case 5:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"Attack something and I shall show you true power!\"\n");
            break;
        default:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a voice in your head saying: "+
                "\"Your enemies do not stand a chance as long as you "+
                "possess me.\"\n");
            break;
    }         
}

/*
 *  FUNCTION: enter_env
 *  Arguments: object env, object from
 *  Returns  : N/A
 * 
 * This function is called when the trident enters a new environment
 *
*/

public void
enter_env(object env, object from)
{
    object next_env;

    ::enter_env(env, from);

    next_env = env;
    do
    {
        if (!env || living(env))
        {
             // item is possessed by a living, so no messages
            if (message_alarm_id != 0)
            {
                remove_alarm(message_alarm_id);
                message_alarm_id = 0;
            }

            return;
        }
    } while (next_env = environment(next_env));
    remove_alarm(unwield_alarm_id);
    message_alarm_id = set_alarm(60.0, 120.0, farewell_message);
}

/*
 *  FUNCTION: leave_env
 *  Arguments: object from, object to
 *  Returns  : N/A
 * 
 * This function is called when the trident leaves an environment
 *
*/

public void
leave_env(object from, object to)
{
    ::leave_env(from,to);
    remove_alarm(unwield_alarm_id);
    remove_alarm(talk_alarm_id);
}

/*
 *  FUNCTION: farewell_message
 *  Arguments: N/A
 *  Returns  : N/A
 * 
 * This function gives messages to the room when the trident is
 * dropped somewhere (or racked)
*/

public void 
farewell_message()
{
    object env;

    env = this_object();
    
    while (objectp(env) && !IS_ROOM_OBJECT(env))
    {
        env = environment(env);
    }
    
    if (objectp(env))
    {
        switch(random(4))
        {
            case 0:
                tell_room(env,"You hear the words \"I hunger, "+
                    "feed me!\" from somewhere nearby.\n");
                break;
            case 1:
                tell_room(env,"You hear the words \"Pick me up, even "+
                    "for just a while. You will not regret it!\" "+
                    "from somewhere nearby.\n");
                break;
            case 2:
                tell_room(env,"You hear the words \"If you can wield "+
                    "me, my powers will help you. Try me!\" "+
                    "from somewhere nearby.\n");
                break;
            default:
                tell_room(env,"You hear the words \"I will rest "+
                    "comfortably in your hands. Try me!\" "+
                    "from somewhere nearby.\n");
                break;
        }
    }
}

/*
 *  FUNCTION: easy_win
 *  Arguments: N/A
 *  Returns  : N/A
 * 
 * Called when the wielder kills someone with stats alot lower than theirs
 *
*/

void 
easy_win()
{    
    object wielder = query_wielded();
    switch(random(5))
    {
        case 0:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a sarcastic voice in your head saying: "+
                "\"Well THAT was a well fought battle. I'll bet you planned "+
                "for hours and hours on how to get around those defences.\"\n");
            break;
        case 1:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a sarcastic voice in your head saying: "+
                "\"Unbelievable. I grant you the use of my fantastic "+
                "powers and you slay rats and mice. Pitiful.\"\n");
            break;
        case 2:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a sarcastic voice in your head saying: "+
                "\"All of the creatures of the realms are now absolutely "+
                "terrified of you after THAT showcase of your mighty "+
                "talents.\"\n");
            break;
        case 3:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a sarcastic voice in your head saying: "+
                "\"Oh, I'm sorry. Are we finished yet? I didn't notice. "+
                "Afterall you could have won that fight with your eyes "+
                "closed.\"\n");
            break;

        default:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a sarcastic voice in your head saying: "+
                "\"Oh please! What's next 'oh great slayer of gopheroos'?\"\n");
            break;
    }  
}

/*
 *  FUNCTION: avg_win
 *  Arguments: N/A
 *  Returns  : N/A
 * 
 * Called when the wielder kills someone with stats about the same as theirs
 *
*/

void 
avg_win()
{        
    object wielder = query_wielded();
    switch(random(3))
    {
        case 0:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a complacent voice in your head saying: "+
                "\"A good fight, not a great fight. I hope you have more "+
                "to offer than this for foes.\"\n");
            break;
        case 1:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a complacent voice in your head saying: "+
                "\"Indeed that fed SOME of my hunger, but I need more.\"\n");
            break;
        default:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a complacent voice in your head saying: "+
                "\"That fight was sufficient to appease my hunger, for now.\"\n");
            break;
    }      
}
 
/*
 *  FUNCTION: hard_win
 *  Arguments: N/A
 *  Returns  : N/A
 * 
 * Called when the wielder kills someone with stats higher than theirs
 *
*/

void 
hard_win()
{            
    object wielder = query_wielded();
    switch(random(3))
    {
        case 0:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a pleased voice in your head saying: "+
                "\"At last! A fight worthy of my usage. Thank you for "+
                "allowing me to help you vanquish your foes. You are truly "+
                "worthy of wielding me.\"\n");
            break;
        case 1:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a pleased voice in your head saying: "+
                "\"More! We need more foes of that strength! It feels "+
                "good to be used to my full extent!\"\n");
            break;
        default:
            wielder->catch_msg("The " + short() + " you are wielding glows "+
                "briefly and you hear a pleased voice in your head saying: "+
                "\"Ahhh! Together we shall vanquish all who stand before "+
                "us!\"\n");
            break; 
    }          
}


