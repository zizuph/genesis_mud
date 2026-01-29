/* Navarre September 2nd 2006, Added query_humanoid(){return 1;} 
 * to allow Dragon Order to use their plexus.
 * A yeti should be a humanoid anyway.
 *
 * Navarre, February 5th 2014, Changed Resistance Values.
 *          Magic Resist from 50 to 25.  - Are Yeti's particularly magical 
 *                                         resistant? No. 
 *          Poison Resist from 100 to 50 - I was tempted to set it to 0.
 *                                         thematically a yeti doesn't resist
 *                                         poison. Let's see how this goes.
 *          Cold Resist was left at 100, it makes sense.
 *
 * Carnak, February 19th 2016,  Fixed reported spelling error in description
 *                              and made the code more readable, it should
 *                              now be up to Genesis code standard.
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/icewall/castle2/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/d/Ansalon/std/creature";

#define A_BITE          0
#define A_LEFTCLAW      1
#define A_RIGHTCLAW     2
#define H_HEAD          0
#define H_TORSO         1
#define H_LEFTARM       2
#define H_RIGHTARM      3
#define H_ABDOMEN       4
#define H_LEFTLEG       5
#define H_RIGHTLEG      6


void
create_creature()
{
//  set_name("yeti");
    set_adj("arctic");
    add_adj("colossal");
    set_race_name("yeti");
    set_short("colossal arctic yeti");
    set_long("The race this creature belongs to was to the common " +
    "tundra yeti as the brutal and wild thanoi " +
    "are to the present-day friendly sea walruses - a huge, evil and " +
    "abominable incarnation. This specimen managed to survive in " +
    "the depths of Icewall's arctic climate since well before the " +
    "First Dragon War. Fueled by unholy energies, much like nowaday's " +
    "zombies, it fed upon murder, violence, and fresh blood, rampaging " +
    "first through the elven communities and later through ice folk " +
    "villages like a furred, insane nightmare reoccuring every " +
    "score of years. Something truly evil must have drawn it here from " +
    "the uncharted depths of the southern land. This ancient creature " +
    "could stand over five meters tall, but it prefers to walk hunched, " +
    "supporting its weight on massive, thicker than tree-trunks arms. " +
    "The yeti's hands end in razor sharp, half a meter long claws, " +
    "though the left one has been broken in midlength. A " +
    "wicked, semi-intelligent light gleams in the creature's dark eyes, " +
    "and it appears capable of gutting a careless dragon with one swipe.\n");
   
    set_aggressive(1);
   
    set_gender(G_MALE);
    set_stats(({ 350, 350, 350, 250, 250, 350}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    set_alignment(-1500);   
    add_prop(LIVE_I_QUICKNESS, 50);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_hp(query_max_hp());
    set_knight_prestige(1500);

    set_act_time(10);
    add_act("emote raises his head and sniffs the air hungrily.");
    add_act("emote licks his broken left claw.");
    add_act("emote roars mindlessly.");

    set_cact_time(1);
    add_cact("emote opens his gaping mouth wide and gurgles.");
    add_cact("emote crouches low, claws held wide, ready to " +
    "leap and wreak destruction!"); 
    add_cact("emote salivates generously. The thick, milky substance " +
    "freezes upon his furred chin and torso.");


    set_attack_unarmed(A_BITE, 50, 60, W_IMPALE, 20, "gaping toothy maw");
    set_attack_unarmed(A_LEFTCLAW, 40, 65, W_SLASH, 40, "broken left claw");
    set_attack_unarmed(A_RIGHTCLAW, 50, 80, W_SLASH, 40, "lethal right claw");

    add_prop(OBJ_I_RES_COLD, 100);
    add_prop(OBJ_I_RES_POISON, 50);

    set_hitloc_unarmed(H_HEAD, ({50,50,50,50}), 10,"head");
    set_hitloc_unarmed(H_TORSO, ({45,55,60,60}), 30,"torso");
    set_hitloc_unarmed(H_LEFTARM, ({40,50,55,55}), 15,"left arm");
    set_hitloc_unarmed(H_RIGHTARM, ({40,50,55,55}), 15,"right arm");
    set_hitloc_unarmed(H_ABDOMEN, ({20,30,30,30}), 10, "abdomen");
    set_hitloc_unarmed(H_LEFTLEG, ({40,50,55,55}), 10, "left leg");
    set_hitloc_unarmed(H_RIGHTLEG, ({40,50,55,55}), 10, "right leg");
    
    set_exp_factor(200);
}

public void
do_die(object killer)
{
    object room = E(TO);

    tell_room(room, "The yeti gurgles black blood and collapses.\n", ({ TO }));
    ::do_die(killer);   
}


int
special_attack(object enemy)
{
    int     attacktype,
            pen,
            att,
            wloc,
            hps;

    mixed   hitres;

    string *hitloc,
           *attack,
            weapon;

    attacktype = random(8);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if((attacktype == 3) && (TO->query_hp() < 1500))
    {
        TO->heal_hp(random(500) + 500);
        tell_room(E(TO), QCTNAME(TO) + "'s eyes alight with an ancient " +
        "unholy power and his wounds begin to heal!\n",({TO, TO}));
        return 1;
    }

    if (attacktype == 2)
    {
        pen = 600 + random(400);
        hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] > 60)
        {
            enemy->catch_msg("With an ear-bursting roar the " + QTNAME(TO) + 
            " leaps onto you, ripping your " + hitloc[wloc] + " apart with " +
            "his claws in a violent explosion of blood! You nearly lose " +
            "consciousness and feel death approaching fast.\n" +
            QCTNAME(TO) + "'s eyes burn with unholy power.\n");

            tell_room(E(TO), "With an ear-bursting roar " + QCTNAME(TO) + 
            " leaps at " + QTNAME(enemy) + ", ripping " + HIS(enemy) + " " + 
            hitloc[wloc] + " apart in a violent explosion of blood. " +
            QTNAME(enemy) + " appears on the verge of death.\n" +
            QCTNAME(TO) + "'s eyes burn with unholy power.",({enemy, TO}));

            TO->heal_hp(200);
        }

        if (hitres[0] > 50)
        {
            enemy->catch_msg("With an unstoppable thrust, the " + 
            QCTNAME(TO) + 
            " drives his titanic right claw straight through your " + 
            hitloc[wloc] + ", causing immense damage!\n" +
            QCTNAME(TO) + "'s eyes glow with an evil light.\n");

            tell_room(E(TO), "With an unstoppable thrust, the " + 
            QCTNAME(TO) + 
            " drives his titanic right claw straight through " + 
            QTNAME(enemy) + "'s " + hitloc[wloc] + " causing " +
            "immense damage!\n" + QCTNAME(TO) + "'s eyes glow with an " +
            "evil light.\n",({enemy, TO}));

            TO->heal_hp(150);
        }
        else if (hitres[0] > 40)
        {
            enemy->catch_msg("With a mighty overhead slice, " + 
            QCTNAME(TO) + 
            " rakes your " + hitloc[wloc] + " with his broken " +
            "left claw! Muscles and tendons snap apart, and blood " +
            "flows freely.\n" +
            QCTNAME(TO) + "'s eyes glitter wickedly.\n");

            tell_room(E(TO), "With a mighty overhead slice, " + 
            QCTNAME(TO) + 
            " rakes " + QTNAME(enemy) + "'s " + hitloc[wloc] + 
            " with his broken left claw! Muscles and tendons snap " +
            "apart, and blood flows freely.\n" + QCTNAME(TO) + "'s " +
            "eyes glitter wickedly.\n",({enemy, TO}));

            TO->heal_hp(100);
        }
        else if(hitres[0] > 30)
        {
            enemy->catch_msg(QCTNAME(TO) + "'s maw closes around your " +
            hitloc[wloc] + " and you feel the iron hard, sharp teeth " +
            "dig all the way to the bone. It hurts, badly.\n" +
            QCTNAME(TO) + "'s eyes alight with savage joy.\n");

            tell_room(E(TO), QCTNAME(TO) + "maw closes around " +
            QTNAME(enemy) + "'s " + hitloc[wloc] + 
            " ,the iron hard, sharp teeth of the abomination digging " +
            "deep! It must hurt.\n" + QCTNAME(TO) + "'s " +
            "eyes alight with savage joy.\n",({enemy, TO}));	

            TO->heal_hp(50);
        }
        else if (hitres[0] > 20)
        {
            enemy->catch_msg(QCTNAME(TO) + " backhands you with one of " +
            "his massive arms! Hit in the " + hitloc[wloc] + " you fly " +
            "away from the fight, but " + QTNAME(TO) + " follows, " +
            "his eyes devoid of anything but undead hunger.\n");

            tell_room(E(TO), QCTNAME(TO) + " backhands " + QTNAME(enemy) +
            " with one of his massive arms! Hit in the " + hitloc[wloc] + 
            " " + QTNAME(enemy) + " flies away from the fight, but " +
            QCTNAME(TO) + " follows, his eyes devoid of anything but undead " +
            "hunger.\n",({enemy, TO}));	
        }
        else if (hitres[0] > 10)
        {
            enemy->catch_msg(QCTNAME(TO) + " slaps you with his huge " +
            "hand! Pain spreads through your " + hitloc[wloc] + " but " +
            "at least you managed to avoid the lethal claws. You turn " +
            "to face " + QTNAME(TO) + " again, and the undead hunger " +
            "in his eyes makes your skin crawl.\n");

            tell_room(E(TO), QCTNAME(TO) + " slaps " + QTNAME(enemy) +
            " with his huge hand! Though hit in the " + hitloc[wloc] + ", " + 
            QTNAME(enemy) + " manages to avoid the lethal claws, and " +
            "turns back to face " + QTNAME(TO) + " and the undead " +
            "hunger in the abomination's eyes again.\n",({enemy, TO}));
        }
        else if (hitres[0] > 0)
        {
            enemy->catch_msg("You dodge in time, and " + QTNAME(TO) + 
            " barely scratches your " + hitloc[wloc] + " with a " +
            "blow capable of gutting a dragon! Having no time to " +
            "thank your Gods, you face the fury of the abomination " +
            "again.\n");

            tell_room(E(TO), QTNAME(enemy) + " dodges in time, and " +
            QTNAME(TO) + " barely scratches " + HIS(enemy) + " " +
            hitloc[wloc] + " with a blow capable of gutting a dragon! " +
            QCTNAME(enemy) + " has no time to thank his Gods as he " +
            "turns to face the fury of the abomination again.\n",({enemy, TO}));
        }
        else
        {
            enemy->catch_msg(QCTNAME(TO) + " pauses for a moment, " +
            "throws back his head and roars into the sky. The " +
            "sound of mindless rage and undead hunger thunders " +
            "down the ice fields. Your skin crawls with the " +
            "experience but you also catch a glimpse of softer, " +
            "thinner fur covering the creature's abdomen...\n");

            tell_room(E(TO), QCTNAME(TO) + " pauses for a moment, " +
            "throws back his head and roars into the sky. The " +
            "sound of mindless rage and undead hunger thunders " +
            "down the ice fields. Your skin crawls with the " +
            "experience but you also catch a glimpse of softer, " +
            "thinner fur covering the creature's abdomen...\n",({enemy, TO}));	
        }
	  
        if (enemy->query_hp() <= 0)
        {
            set_alarm(1.0, 0.0, "victory", enemy);
            tell_watcher(QCTNAME(enemy) + "'s blood clashes with the " +
            "purity of the white snow.\n", enemy);
            enemy->do_die(TO);
        }
        return 1;
    }
    return 0;
}

void
victory(object enemy)
{
    tell_room(E(TO),QCTNAME(TO) + " leaps onto the " +
    "lifeless corpse and brutally reaps it apart! " +
    "Limbs and pieces of flesh fly everywhere, " +
    "and blood showers everywhere! " + QTNAME(TO) +
    "is surrounded by a shadowy nimbus, and appears " +
    "to be growing stronger!\n");
    TO->heal_hp(1000);
}

int query_humanoid()
{
    return 1;
}

void
init_living()
{
    ::init_living();
}
