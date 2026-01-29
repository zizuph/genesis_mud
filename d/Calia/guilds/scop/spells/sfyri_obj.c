/*
 * Spell object for the Sfyri spell. This object is a hammer that can be 
 * thrown in combat. It gets better as the caster uses it. 
 * It's a holdable object.
 *
 *
 * Bishop, May 2004.
 * December 2004: Removed resistance check from hammer throws.
 *                It's a physical weapon once it's been conjured.
 */


/* Navarre December 2006:
 *   Added a dispell on time, but the time only counts if the weapon is
 *   actually held.
 *   It takes quite a while to train the hammer up to be useful.
 *   It is quite bad to begin with. So after about 30 minutes the hammer
 *   has gotten good. So too fast dispel will ruin the spell.
 *
 * Navarre April 15th 2007:
 *   Due to long hiatus of AoB, AoD (Damaris) approved change to Sfyri from
 *   W_BLUDGEON to MAGIC_DT of the Sfyri hammer.
 *
 * Navarre January 8th 2008:
 *   Fixed bug that could cause the Scops to get 5 hits with the hammer per every one hit.
 *   It was caused because of the remove_prop in the start using hammer.
 *   I added a time value to the prop, to check if I should remove the prop or not.
 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";
inherit "/d/Genesis/newmagic/resist.c";
inherit "/lib/holdable_item";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include "defs.h"

#define I_CANT_THROW_SPIRIT_HAMMER "_i_cant_throw_spirit_hammer"
#define SCOP_I_USE_SFYRI "_scop_i_use_sfyri"

int recast_alarm;
int use_alarm;
int dispel_alarm;
int timeleft;
int hammer_level = 1;
int hammer_pen = 100;

string
hammer_short()
{
    string descrip;

    switch (hammer_level)
    {
        case 1:
            descrip = "dull grey hammer";
            break;
        case 2:
            descrip = "silvery grey hammer";
            break;
        case 3:
            descrip = "sparking shadowy hammer";
            break;
        case 4:
            descrip = "pulsating shadowy hammer";
            break;
        case 5:
            descrip = "whispering shadowy hammer";
            break;
        default:
            descrip = "roaring shadowy hammer";
    }
    
    return descrip;
}


string
hammer_long()
{
    string descrip;

    switch (hammer_level)
    {
        case 1:
            descrip = "This hammer is slightly warm to the touch. It does" +
                      " not appear to be made from any earthly material, " +
                      "but has been forged from a shadowy substance with " +
                      "a uniformly flat grey finish.";
            break;
        case 2:
            descrip = "This grey hammer has a faint silvery sheen to it." +
                      " Studying it closely, you can see the glow waxing " +
                      "and waning ever so slightly. It does not appear " +
                      "to be made from any earthly material, but has been " +
                      "forged from a shadowy substance.";           
            break;
        case 3:
            descrip = "This hammer, forged from a shadowy substance, is a" +
                      " strange sight. Tiny sparks appear on it at " +
                      "irregular times, travelling along the surface of " +
                      "the hammer a while, before disappearing again. " +
                      "They do not harm you at all, though the hammer is " +
                      "quite warm to the touch.";
            break;
        case 4:
            descrip = "This hammer, forged uniformly from a shadowy " +
                      "substance, is a marvel to behold. Shadows of " +
                      "varying darkness travel back and forth beneath " +
                      "its surface, producing complex and eerie " +
                      "patterns. It is hard to shake the feeling that " +
                      "this weapon is alive.";
            break;
        case 5:
            descrip = "This hammer emits a ghostly whispering sound that " +
                      "is hauntingly beautiful. Listening closely, you " +
                      "feel you are very close to understanding the " +
                      "whisper, but it is always just at the edge of " +
                      "coherence. The hammer itself is forged uniformly " +
                      "from a shadowy material and is alive with " +
                      "flickering shadows.";
            break;
        default:
            descrip = "This hammer fills your mind with song, the power " +
                      "and beauty of which stirs you and tugs at your " +
                      "soul. At times you feel you can recognize a single " +
                      "voice, other times it is a chorus. The hammer " +
                      "itself appears forged from a shadowy substance, " +
                      "and eldritch shadows dance across its surface.";
    }
    
    descrip += " Too light for melee use, it can be held in one hand and" +
               " thrown at an opponent.\n";
    
    return descrip;
}

void
create_object() 
{
    set_name("hammer");
    add_name("_sfyri_hammer_");

    add_adj("grey");
    add_adj("dull");
    set_short("@@hammer_short@@");
    set_long("@@hammer_long@@");

    add_prop(OBJ_I_VOLUME, 2000+random(1000));
    add_prop(OBJ_I_WEIGHT, 2000+random(1000));
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 3000+random(1000));
    add_prop(OBJ_M_NO_SELL, "Sell the " + TO->short() + "? You wouldn't" +
                            " dream of it.");
        
    add_prop(MAGIC_AM_MAGIC, ({"50","conjuration"}));
    add_prop(OBJ_S_WIZINFO, "This hammer is created from the Sfyri " +
                            "spell of the Spirit Circle of Psuchae. " +
                            "It's a holdable item, and works as a " +
                            "thrown weapon that returns to the " +
                            "holder's hand. Can't be given away. " +
                            "Extra damage vs the undead.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This hammer is a magical creation.\n", 20, 
                                "This throwing hammer performs better " +
                                "against undead foes.\n", 40}));  
    set_slots(W_ANYH);      
}

int
start()
{
    int gstat, wis; 
    spell_caster->add_prop(SCOP_I_USE_SFYRI, 1);
    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    timeleft = MIN(5700, 2700+5*gstat+5*wis+random(1000));
    return 1;
}

/* 
 * Return 1 if we hit the target.
 */
int
try_to_hit (object thrower, object target)
{
    int task = TASK_ROUTINE;

    if (target->query_prop(LIVE_I_UNDEAD))
    {
        task -= 100;
    }

    return (thrower->resolve_task(task, ({TS_OCC, TS_DEX}), target, 
                                        ({TS_DEX, SS_DEFENCE})) > 0);
}


varargs public int
dispel_spell_effect(object dispeller)
{
    spell_caster->catch_msg("Your " + TO->short() +
                            " melds into nothingness.\n");
    spell_caster->remove_prop(I_CANT_THROW_SPIRIT_HAMMER);
            
    if(dispel_alarm)
    {
      remove_alarm(dispel_alarm);
    }
    remove_spell_effect_object();
    return 1;

}

public string
query_recover()
{
    return 0;
}


void
throw_again()
{
    if(use_alarm)
        return;
    spell_caster->remove_prop(I_CANT_THROW_SPIRIT_HAMMER);
    
    if (TO->query_held())
    {
        spell_caster->catch_msg("You feel ready to throw your " +
                                TO->short() + " again.\n");
    }
}

void
start_using_hammer()
{
    spell_caster->remove_prop(I_CANT_THROW_SPIRIT_HAMMER);
    remove_alarm(recast_alarm);
    remove_alarm(use_alarm);
    use_alarm = 0;
    
    if (TO->query_held())
    {
        spell_caster->catch_msg("You feel ready to start throwing your " +
                                 TO->short() + ".\n");
    }
}

void
improve_hammer_pen()
{
    int i, val = 0;
    
    i = spell_caster->query_stat(SS_OCCUP) + 
        spell_caster->query_stat(SS_WIS) +
        spell_caster->query_alignment()/12;
        
    switch (i)
    {
        case 0..200:
            val = 2;
            break;
        case 201..300:
            val = 3;
            break;
        case 301..400:
            val = 4;
            break;
        case 401..500:
            val = 5;
            break;
        default:    
            val = 6;
    }

    if (hammer_pen + val > 500)
    {
        val = 1;
        //Little improvement beyond this point.
    }
    
    hammer_pen += val;
}


void
check_hammer_upgrade()
{
    if (hammer_level == 1 && hammer_pen >= 170)
    {
        hammer_level = 2;
        remove_adj("dull");
        add_adj("silvery");
        spell_caster->catch_tell("Your dull grey hammer begins " +
                                 "to glow with a silvery colour!\n");
        tell_room(environment(spell_caster), LANG_POSS(QCTNAME(spell_caster)) + 
                  " dull grey hammer begins to glow with a silvery " +
                  "colour!\n", spell_caster);
    }
    else
    if (hammer_level == 2 && hammer_pen >= 240)
    {
        remove_adj("silvery");
        remove_adj("grey");
        add_adj("shadowy");
        add_adj("sparking");
        spell_caster->catch_tell("Your silvery grey hammer begins to trail" +
                                 " sparks!\n");  
        tell_room(environment(spell_caster), LANG_POSS(QCTNAME(spell_caster)) + 
                  " silvery grey hammer begins to trail sparks!\n",
                  ({spell_caster}));              
        hammer_level = 3;
    }
    else
    if (hammer_level == 3 && hammer_pen >= 320)
    {
        remove_adj("sparking");
        add_adj("pulsating");
        spell_caster->catch_tell("Your sparking shadowy hammer begins to" +
                                 " pulsate brightly!\n");
        tell_room(environment(spell_caster), LANG_POSS(QCTNAME(spell_caster)) + 
                  " sparking shadowy hammer begins to pulsate brightly!\n",
                  spell_caster);            
        hammer_level = 4;
    }
    else
    if (hammer_level == 4 && hammer_pen >= 400)
    {
        remove_adj("pulsating");
        add_adj("whispering");
        spell_caster->catch_tell("Your pulsating shadowy hammer begins to" +
                                 " emit a whispering sound!\n"); 
        tell_room(environment(spell_caster), LANG_POSS(QCTNAME(spell_caster)) + 
                  " pulsating shadowy hammer begins to emit a whispering " +
                  "sound!\n", spell_caster);        
        hammer_level = 5;
    }
    else
    if (hammer_level == 5 && hammer_pen >= 500)
    {
        remove_adj("whispering");
        add_adj("roaring");
        spell_caster->catch_tell("Your whispering shadowy hammer begins to" +
                                 " sing!\n");
        tell_room(environment(spell_caster), LANG_POSS(QCTNAME(spell_caster)) + 
                  " whispering shadowy hammer begins to roar!\n", 
                  ({spell_caster})); 
        hammer_level = 6;
    }
}

void hammer_effect(object spell_caster, object enemy, object hammer)
{
    string msg1, msg2, msg3;
    mixed* hitresult;
    int reset_time;
    int real_pen = hammer_pen;
   

    if (!objectp(present(enemy, environment(spell_caster))))
    {
        spell_caster->catch_tell("Your enemy is not present!\n");
        remove_alarm(recast_alarm);
        recast_alarm = set_alarm(3.0, 0.0, &throw_again());
        return;
    }

    if (!TO->query_held())
    {
        spell_caster->catch_tell("You cannot throw the hammer unless " +
                                 "you are holding it!\n");
        remove_alarm(recast_alarm);
        recast_alarm = set_alarm(3.0, 0.0, &throw_again());
        return;
    }

    if (!objectp(enemy))
    {
        spell_caster->catch_tell("Your enemy escaped.\n");
        remove_alarm(recast_alarm);
        recast_alarm = set_alarm(3.0, 0.0, &throw_again());
        return;
    }

    if (!CAN_SEE(spell_caster, enemy))
    {
        spell_caster->catch_tell("You cannot see your enemy!\n");
        remove_alarm(recast_alarm);
        recast_alarm = set_alarm(3.0, 0.0, &throw_again());
        return;
    }

    if (spell_caster->query_prop(LIVE_I_STUNNED))
    {
        spell_caster->catch_tell("You are too stunned to throw " +
                                 "the hammer!\n");
        set_alarm(3.0, 0.0, &throw_again());
        return;
    }

    if (spell_caster->query_prop(LIVE_O_CONCENTRATE))
    {
        spell_caster->catch_tell("You cannot throw the hammer " +
                                 "while preparing a spell!\n");
        remove_alarm(recast_alarm);
        recast_alarm = set_alarm(3.0, 0.0, &throw_again());
        return;
    }

    spell_caster->add_mana(-8);
    spell_caster->add_fatigue(-5);
    
    switch (random(4))
    {
        case 0:
            msg1 = "You pull your arm back to gather force for the throw," +
                   " then whip it back again to launch your " + TO->short() + 
                   " at " +  enemy->query_the_name(spell_caster) + "!";
            msg2 = QCTNAME(spell_caster) + " pulls " + 
                   spell_caster->query_possessive() + " arm back to gather" +
                   " force, then whips it back again to launch " + 
                   spell_caster->query_possessive() + " " + TO->short() + 
                   " at " + QTNAME(enemy) + "!";
            msg3 = spell_caster->query_the_name(enemy) + " pulls " + 
                   spell_caster->query_possessive() + " arm back to gather" +
                   " force, then whips it back again to launch " + 
                   spell_caster->query_possessive() + " " + TO->short() + 
                   " at you!";
            break;
        case 1:
            msg1 = "Swinging your " + TO->short() + " in a wide arc, you" +
                   " release it, propelling it forcefully towards " + 
                   enemy->query_the_name(spell_caster) + "!";
            msg2 = "Swinging " + spell_caster->query_possessive() + " " + 
                   TO->short() + " in a wide arc, " + QTNAME(spell_caster) +
                   " releases it, propelling it forcefully towards " + 
                   QTNAME(enemy) + "!";
            msg3 = "Swinging " + spell_caster->query_possessive() + " " + 
                   TO->short() + " in a wide arc, " + 
                   spell_caster->query_the_name(enemy) + " releases it," +
                   " propelling it forcefully towards you!";
            break;
        case 2:
            msg1 = "Twirling your " + TO->short() + " in your hand," +
                   " you fling it abruptly at " + 
                   enemy->query_the_name(spell_caster) + "!";
            msg2 = "Twirling " + spell_caster->query_possessive() + " " +
                   TO->short() + " in " + spell_caster->query_possessive() + 
                   " hand, " + QTNAME(spell_caster) + " flings it abruptly" +
                   " at " + QTNAME(enemy) + "!";
            msg3 = "Twiling " + spell_caster->query_possessive() + " " +
                   TO->short() + " in " + spell_caster->query_possessive() + 
                   " hand, " + spell_caster->query_the_name(enemy) +
                   " flings it abruptly at you!";
            break;
        default:
            msg1 = "You distract " + enemy->query_the_name(spell_caster) + 
                   " with a feint, before casting your " + TO->short() +
                   " at " + enemy->query_objective() + " with a sudden " +
                   "underarm throw!";
            msg2 = QCTNAME(spell_caster) + " distracts " + QTNAME(enemy) +
                   " with a feint, before casting " + 
                   spell_caster->query_possessive() + " " + TO->short() +
                   " at " + enemy->query_objective() + " with a sudden " +
                   "underarm throw!";
            msg3 = spell_caster->query_The_name(enemy) + " distracts you" +
                   " with a feint, before casting " + 
                   spell_caster->query_possessive() + " " + TO->short() +
                   " at you with a sudden underarm throw!";
    }

    if (!try_to_hit(spell_caster, enemy))
    {
        switch (random(3))
        {
            case 1:
                msg1 += " " + capitalize(enemy->query_pronoun()) + " manages" +
                        " to avoid the " + TO->short() + " with a timely" +
                        " duck.";
                msg2 += " " + capitalize(enemy->query_pronoun()) + " manages" +
                        " to avoid the " + TO->short() + " with a timely" +
                        " duck.";
                msg3 += " You manage to avoid the " + TO->short() + 
                        " with a timely duck.";
                break;
            case 2:
                msg1 += " " + capitalize(enemy->query_pronoun()) + " manages" +
                        " to avoid the " + TO->short() +" with a well-timed"+
                        " dodge.";
                msg2 += " " + capitalize(enemy->query_pronoun()) + " manages" +
                        " to avoid the " + TO->short() +" with a well-timed"+
                        " dodge.";
                msg3 += " You manage to avoid the " + TO->short() + 
                        " with a well-timed dodge.";
                break;
            default:
                msg1 += " The " + TO->short() + " misses " + 
                        enemy->query_objective() + " completely.";
                msg2 += " The " + TO->short() + " misses " + 
                        enemy->query_objective() + " completely.";
                msg3 += " The " + TO->short() + " misses you" +
                        " completely.";
        }
    }
    else
    {
        switch (random(4))
        {
            case 1:
                msg1 += " The " + TO->short() + " misses " + 
                        enemy->query_objective() + " on the first pass, but" +
                        " turns around in midair, hitting " +
                        enemy->query_objective() + " from behind.\n";
                msg2 += " The " + TO->short() + " misses " + 
                        enemy->query_objective() + " on the first pass, but" +
                        " turns around in midair, hitting " +
                        enemy->query_objective() + " from behind.\n";
                msg3 += " The " + TO->short() + " misses you on the" +
                        " first pass, but turns around in midair, hitting you" +
                        " from behind.\n";
                break;
            case 2: 
                msg1 += " The " + TO->short() + " appears to be" +
                        " headed in the wrong direction, but changes course in" +
                        " midair to hit " + enemy->query_objective() + 
                        " straight on.\n";
                msg2 += " The " + TO->short() + " appears to be" +
                        " headed in the wrong direction, but changes course in" +
                        " midair to hit " + enemy->query_objective() + 
                        " straight on.\n";         
                msg3 += " The " + TO->short() + " appears to be" +
                        " headed in the wrong direction, but changes course in" +
                        " midair to hit you straight on.\n";
                break;
            case 3: 
                msg1 += " The " + TO->short() + " flies straight and" +
                        " true towards " + enemy->query_objective() + ", hitting" +
                        " " + enemy->query_objective() + " cleanly.\n";
                msg2 += " The " + TO->short() + " flies straight and" +
                        " true towards " + enemy->query_objective() + ", hitting" +
                        " " + enemy->query_objective() + " cleanly.\n";
                msg3 += " The " + TO->short() + " flies straight and" +
                        " true towards you, hitting you cleanly.\n";
                break;
            default:
                msg1 += " The " + TO->short() + " follows " + 
                        enemy->query_possessive() + " movements as " + 
                        enemy->query_pronoun() + " attempts to dodge, hitting " +
                        enemy->query_objective() + " squarely.\n";
                msg2 += " The " + TO->short() + " follows " + 
                        enemy->query_possessive() + " movements as " + 
                        enemy->query_pronoun() + " attempts to dodge, hitting " +
                        enemy->query_objective() + " squarely.\n";
                msg3 += " The " + TO->short() + " follows your" +
                        " movements as you attempt to dodge, hitting you" +
                        " squarely.\n";
        }
        hitresult = enemy->hit_me(real_pen, MAGIC_DT, spell_caster, -1);

        switch (hitresult[0])
        {
            case 0..1:
                msg1 += "The " + TO->short() + " bounces lightly" +
                        " off " + enemy->query_the_name(spell_caster) + 
                        ", causing no real damage.";
                msg2 += "The " + TO->short() + " bounces lightly" +
                        " off " + QTNAME(enemy) + ", causing no real damage.";
                msg3 += "The " + TO->short() + " bounces lightly" +
                        " off you, causing no real damage.";
                break;
            case 2..6:
                msg1 += "The " + TO->short() + " hits " +
                        enemy->query_the_name(spell_caster) + " with a thump," +
                        " leaving a few bruises.";
                msg2 += "The " + TO->short() + " hits " +
                        QTNAME(enemy) + " with a thump, leaving a few bruises.";                    
                msg3 += "The " + TO->short() + " hits you with a thump" +
                        ", leaving a few bruises.";
                break;
            case 7..11:
                msg1 += "The " + TO->short() + " strikes " +
                        enemy->query_the_name(spell_caster) + " hard, breaking" +
                        " the skin and leaving a shallow wound.";
                msg2 += "The " + TO->short() + " strikes " +
                        QTNAME(enemy) + " hard, breaking" +
                        " the skin and leaving a shallow wound.";
                msg3 += "The " + TO->short() + " strikes you hard," +
                        " breaking the skin and leaving a shallow wound.";
                break;
            case 12..18:
                msg1 += "The " + TO->short() + " connects solidly with "+
                        enemy->query_the_name(spell_caster) + ", leaving a nasty" +
                        " abrasion.";
                msg2 += "The " + TO->short() + " connects solidly with "+
                        QTNAME(enemy) + ", leaving a nasty" +
                        " abrasion.";
                msg3 += "The " + TO->short() + " connects solidly with" +
                        " you, leaving a nasty abrasion.";
                break;
            case 19..25:
                msg1 += "Bones break as the " + TO->short() + " smites "+
                        enemy->query_the_name(spell_caster) + ", digging into " +
                        enemy->query_possessive() + " flesh.";
                msg2 += "Bones break as the " + TO->short() + " smites "+
                        QTNAME(enemy) + ", digging into " +
                        enemy->query_possessive() + " flesh.";
                msg3 += "Bones break as the " + TO->short() + " smites"+
                        " you, digging into your flesh.";
                break;
            case 26..35:
                msg1 += "The " + TO->short() + " impacts resoundingly" +
                        " with " + enemy->query_the_name(spell_caster) + 
                        ", shattering bone and cartilage.";
                msg2 += "The " + TO->short() + " impacts resoundingly" +
                        " with " + QTNAME(enemy) + 
                        ", shattering bone and cartilage.";
                msg3 += "The " + TO->short() + " impacts resoundingly" +
                        " with you, shattering bone and cartilage.";
                break;
            case 36..60:
                msg1 += "The " + TO->short() + " mauls " +
                        enemy->query_the_name(spell_caster) + " brutally," +
                        " crumpling " + enemy->query_possessive() + " flesh.";
                msg2 += "The " + TO->short() + " mauls " +
                        QTNAME(enemy) + " brutally," +
                        " crumpling " + enemy->query_possessive() + " flesh.";
                msg3 += "The " + TO->short() + " mauls you brutally," +
                        " crumpling your flesh.";
                break;
            default:
                msg1 += "The " + TO->short() + " delivers a" +
                        " devastating blow to " + 
                        enemy->query_the_name(spell_caster) + ", then pulls" +
                        " back and strikes " + enemy->query_objective() + 
                        " again!";
                msg2 += "The " + TO->short() + " delivers a" +
                        " devastating blow to " + QTNAME(enemy) + ", then pulls" +
                        " back and strikes " + enemy->query_objective() + 
                        " again!";
                msg3 += "The " + TO->short() + " delivers a" +
                        " devastating blow to you, then pulls back and strikes" +
                        " you again!";
        }
        
        if (enemy->query_prop(LIVE_I_UNDEAD))
        {
            msg1 += " " + capitalize(enemy->query_pronoun()) + 
                    " goes ashen as the " + TO->short() + " drinks hungrily"+
                    " from " + enemy->query_possessive() + " life-force.";
            msg2 += " " + capitalize(enemy->query_pronoun())  +
                    " goes ashen as the " + TO->short() + " drinks hungrily"+
                    " from " + enemy->query_possessive() + " life-force.";
            msg3 += " You go ashen as the " + TO->short() + 
                    " drinks hungrily from your life-force.";
            
            enemy->hit_me(real_pen/5, MAGIC_DT, spell_caster, -1);

            improve_hammer_pen();
        }
        
        improve_hammer_pen();
    }
    
    spell_caster->catch_msg(msg1 + "\n");
    spell_caster->tell_watcher(msg2 + "\n", ({spell_caster, enemy}));
    enemy->catch_msg(msg3 + "\n");

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_msg("Hammer pen was : " + real_pen + ".\n");
    }
          
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(spell_caster);
    }
    
    spell_caster->catch_msg("The " + TO->short() + " returns to your" +
                            " hand.\n");
    spell_caster->tell_watcher("The " + TO->short() + " returns to " + 
                               LANG_POSS(QTNAME(spell_caster)) +
                               " hand.\n", ({spell_caster}));
    check_hammer_upgrade();
    
    reset_time = 11+random(6);
    recast_alarm = set_alarm(itof(reset_time), 0.0, &throw_again());
    
}


int
throw_hammer(string str)
{
    int reset_time;
    object enemy = spell_caster->query_attack();
    string *s;    

    
    if (!strlen(str))
    {
        notify_fail("Throw what?\n");
        return 0;
    }

    s = explode(str, " ");

    if (!sizeof(s))
    {
        notify_fail("Throw what?\n");
        return 0;
    }

    if (s[0] != "hammer")
    {
        notify_fail("Throw what?\n");
        return 0;
    }

    if (!TO->query_held())
    {
        notify_fail("You cannot throw the hammer unless you are holding" +
                    " it!\n");
        return 0;
    }

    if (!objectp(enemy))
    {
        notify_fail("You are not fighting anyone!\n");
        return 0;
    }

    if (!objectp(present(enemy, environment(spell_caster))))
    {
        notify_fail("Your enemy is not present!\n");
        return 0;
    }

    if (spell_caster->query_prop(I_CANT_THROW_SPIRIT_HAMMER))
    {
        notify_fail("You are not yet ready to throw your hammer!\n");
        return 0;
    }

    if (spell_caster->query_prop(LIVE_I_ATTACK_DELAY))
    {
        notify_fail("You are not ready to attack yet!\n");
        return 0;
    }

    if (!CAN_SEE(spell_caster, enemy))
    {
        notify_fail("You cannot see your enemy!\n");
        return 0;
    }

    if (spell_caster->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You are too stunned to throw the hammer!\n");
        return 0;
    }

    if (spell_caster->query_prop(LIVE_O_CONCENTRATE))
    {
        notify_fail("You cannot throw the hammer while preparing a spell!\n");
        return 0;
    }

    if (spell_caster->query_fatigue() < 2)
    {
        notify_fail("You are too tired to throw the hammer!\n");
        return 0;
    }

    if (spell_caster->query_mana() < 5)
    {
        notify_fail("You lack the mental strength to throw the hammer.\n");
        return 0;
    }

    spell_caster->catch_tell("You prepare to throw your hammer.\n");
    spell_caster->add_prop(I_CANT_THROW_SPIRIT_HAMMER, 1);
    set_alarm(itof(3+random(2)), 0.0, &hammer_effect(spell_caster, enemy, this_object()));
    return 1;
}

void
leave_env(object from, object to)
{
     ::leave_env(from, to);
     holdable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}


public mixed
release()
{
    remove_alarm(recast_alarm);
    remove_alarm(use_alarm);
    use_alarm = 0;
    timeleft = ftoi(get_alarm(dispel_alarm)[2]);
    remove_alarm(dispel_alarm);
    spell_caster->add_prop("_i_released_sfyri_last_at", time());
    return 0;
}


public mixed
hold()
{
    string hold_desc;
    
    switch (hammer_level)
    {
        case 1:
            hold_desc = "As you grasp the " + TO->short() + ", you" +
                        " feel a mystical rapport with it.\n";
            break;
        case 2:
            hold_desc = "As you grasp the " + TO->short() + ", you" +
                        " feel a sympathetic presence stir within it.\n";
            break;
        case 3:
            hold_desc = "The sparks on the " +TO->short() + " play" +
                        " across your hand as you grasp it. A sense of approval" +
                        " emanates from within.\n";
            break;
        case 4: 
            hold_desc = "As you grasp the " + TO->short() + ", the" +
                        " pulsating quickens, synchronizing perfectly with the beat" +
                        " of your heart. A benevolent presence inside the hammer" +
                        " touches your mind.\n";
            break;
        case 5:
            hold_desc = "As you grasp the " + TO->short() + ", images" +
                        " of yourself using it to obliterate the soulless flood your" +
                        " mind. You feel a presence inside the hammer acknowledging" +
                        " and welcoming you.\n";
            break;
        default:
            hold_desc = "The " + TO->short() + " is a feather in your" +
                        " hand as you grasp it. You feel a great presence inside" +
                        " reaching out and connecting with you.\n";;
    }
     
    spell_caster->catch_msg(hold_desc);
    tell_room(environment(spell_caster), QCTNAME(spell_caster) + " grasps" +
                          " a " + TO->short() + ".\n", spell_caster);       

    spell_caster->add_prop(I_CANT_THROW_SPIRIT_HAMMER, 1);
    remove_alarm(recast_alarm);
    if(time() - spell_caster->query_prop("_i_released_sfyri_last_at") < 17)
    {
        remove_alarm(use_alarm);
        use_alarm = set_alarm(17.0, 0.0, &start_using_hammer());
    }
    else
    {
        remove_alarm(use_alarm);
        use_alarm = set_alarm(5.0, 0.0, &start_using_hammer());
    }
    
    dispel_alarm = set_alarm(itof(timeleft),
                             0.0, &dispel_spell_effect(spell_caster));
    return 1;
}

int
dispel_hammer(string str)
{
    dispel_spell_effect(spell_caster);
    return 1;
}

void
init()
{
    ::init();
    add_action(throw_hammer,"throw");
    add_action(dispel_hammer, "hammerdispel");
}
