/* 
 * Mortis 09.2014
 *
 * Standard base for all Tower of Arms guards.
 *
 * If players can become Constable, these will change
 * to match their guild, but this is the default guard.
 *
 */

#pragma strict_types

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include "../../../local.h"

#define MY_CLOTHING       NOBLE + "arms/parmour"
#define MY_ARMOUR         MERCH + "arms/larmour"
#define MY_GENERAL        MERCH + "obj/lgeneral"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/act/actions";

/*prototype*/
void adjects();

int gender;
string adjstr1, adjstr2;

public void
create_toa_guard()
{
}

void
create_krynn_monster()
{
    set_name("guard");
    add_name(({"guardsman"}));

    adjects();
    
    set_short("@@my_short");
    set_long("A young guardsman of the city of Palanthas sworn to uphold "
    + "the laws and treat the citizenry with respect.  The guard's open "
    + "white tunic bears " + "@@constable_symbol@@" + " above its left "
    + "breast.\n");
    set_race_name("human");
    
    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_AWARENESS,    25);
    set_skill(SS_WEP_SWORD,    50);
    set_skill(SS_WEP_CLUB,     50);
    set_skill(SS_WEP_POLEARM,  45);
    set_skill(SS_BLIND_COMBAT, 20);

    set_stats((({140, 140, 140, 140, 140, 140})), 7);
    set_all_attack_unarmed(12, 8);
    set_all_hitloc_unarmed(5);

    set_alignment(400);
    set_knight_prestige(-75);

    set_pick_up_team("guard");
    set_max_team_size_auto_join(5);

    set_act_time(50);
    add_act("emote polishes a heap of armour.");
    add_act("emote polishes a rack of weapons.");
    add_act("emote straightens an open white tunic.");
    add_act("time");
    add_act("smell");
    add_act("emote ponders visiting the Plaisir district when the shift "
    + "ends.");
    add_act("emote contemplates doing some reading in the Great Library "
    + "when the shift ends.");
    add_act("say Any of you want to peruse the shops of the Arms district "
    + "when the shift ends?");
    add_act("say Who's up for a drinking contest at the Green Twitch Inn "
    + "after the shift ends?");
    add_act("say I heard Chief Constable Hagen jailed another thief.  He's "
    + "relentless.");
    add_act("say Miscreants in the marble city do not prosper, not with "
    + "Hagen around.");

    set_cact_time(8);
    add_cact("shout Violent offender! Prepare the shackles!");
    add_cact("emote blocks the exit decrying: It's jail or Lars for you, "
    + "miscreant.");
    add_cact("emote pulls a pair of iron shackles from " + HIS(TO) + " belt.");
    add_cact("emote attempts to shackle you with a pair of iron shackles.");
    // Monks
    add_cact("asay laugh So this dark stygian lotus monk of Twilight the "
    + "Series came in brandishing a tower shield on each arm. He got stuck "
    + "in the doorway where we pummeled him to a quivering pulp. We went to "
    + "tie him up with his own rope belt only to find he wore no loincloth. "
    + "It was gross.");
    add_cact("asay humor I was talking to this monk the other day and asked "
    + "him, So how are you a monk? And he shrugged and all and was like, "
    + "well, I wear shields on both my arms and take a vow of... ummm, well, "
    + "I kill stuff with people and tank a lot, you know, cause I have all "
    + "these shields. And I was like, Uhhh, yeah I think I get it. He was "
    + "sad after that.");
    // Dragonarmy
    add_cact("asay disg Some admiral in the beige dragonarmy came in and "
    + "asked us to ride his dragon. I told him, Sorry sailor, that's gross.");
    add_cact("asay unfavo These dragonarmy guys got into the city somehow "
    + "and came in here looking for a fight. So I brain them with my hemp "
    + "bagged clubber, and they're all blowing each others horns. That was "
    + "gross, but then this dragon flies into the tower, gets his head "
    + "stuck in the corridor, and we're all dying laughing, know what I "
    + "mean? Long story short, I'm wearing a dragonscale loincloth.");
    add_cact("asay whimsi Hey, dragonarmy guys! Want to blow MY "
    + "warhorn?");
    // Morgul Mages
    add_cact("asay merr So this black-robed hooded guy came in last week "
    + "all hissing and moaning about if I'd seen this one ring of his. I "
    + "told him, No pal I ain't seen your cock ring! We all died laughing. "
    + "He left forlornly so much as I could tell under that hood.");
    add_cact("asay theor Hey, know what Smelkor smells like? Or whatever "
    + "his name is? Poop. Yeah, poop. A HAHAHAHAHAHAHAHA!");
    add_cact("asay wonderi Question: How are Morgul Mages like wraiths? "
    + "Answer: Cause they're never around, and you can just abuse their "
    + "minions and take a dump in their tower!");
    // Takhisans
    add_cact("asay helpf You need a better guild? I hear the Temple of "
    + "Takhisis in Neraka is so empty, you can hear the crying of its "
    + "priestesses from anywhere.");
    add_cact("asay wonderi Hey, do you know who the saddest Takhisis "
    + "priestesses are? Uhh, I don't know. Is there more than one?");
    // Thieves
    add_cact("asay quest You hear about the thieves in town? Yeah, they all "
    + "have dick rot. True story.");
    add_cact("asay positi The thieves all have t-hole leakage. Wanna know "
    + "how? Too much rot, you know, down there?");
    add_cact("asay polite Don't join the thieves, not unless you -like- "
    + "sleeping on urine soaked mattresses. They're gross.");
    // Necromancers
    add_cact("asay sick Man, this necromancer poofed into town. He was "
    + "asking around about body parts. Turns out he had clap balls and "
    + "was just looking for a cure. I told him, That's gross.");
    add_cact("asay noncha So we got called in to arrest this guy in the "
    + "morgue. He was all gyrating all over the corpses. Turns out he was "
    + "a necroromancer or something. He was gross.");
    // Gladiators
    add_cact("asay amaz So we responded to this call in the Plaisir district. "
    + "Apparently, this gladiator was trying to get girls to oil down his "
    + "body. Turns out the hot Athasian sun had baked the crap in his "
    + "pants hard as stone, and he was trying to get them off. Gross, "
    + "right?");
    add_cact("asay indiff So this gladiator comes in and is all like, Do you "
    + "like to eat oysters -and- snails and all? And I'm like, uhh dude "
    + "there are only four months I'll eat oysters in, and this ain't one of "
    + "them! Right? You know what I mean? HAHAHAHAHAHA! ...now you got me "
    + "thinking about oysters. Man!");
    // Mercenaries
    add_cact("asay uproar Those mercs in Sparkle are all talkin' about how "
    + "they can use any weapon. Turns out it's true. They're equally "
    + "unproficient in all weapons!");
    add_cact("asay piti Nothing sadder than a merc with superior guru in "
    + "Being Ridden.");
    add_cact("asay explan So this merc from Sparkle comes in and is all "
    + "going on about how Limitless he is and all and tells me how he "
    + "had superior guru in Location Sense. Well, he couldn't find his "
    + "t-hole again after I mangled him!");
    // Shadow Union
    add_cact("asay superf This guy wearing head rags comes in and shows me "
    + "his knife while doing this freaky pose. Well, I showed him my SWORD, "
    + "and he was all drooling all over it. Classic sword envy, know what I "
    + "mean?");
    add_cact("asay digust One of those shadowy rag-heads came in here and "
    + "tried to draw a knife on me. Turns out he had prune hands from "
    + "bathing all day, and he couldn't draw straight. Then he started "
    + "spraying perfume all over and trying to wash his cape in the "
    + "ocean. I was like, You're gross, but who washes their clothes in the "
    + "ocean? It's all salty. Stuuuupid!");
    add_cact("asay judic Shadow Grunions should put some pants on. It's gross "
    + "when they come in here with those hip-length leather boots and "
    + "naked butts. I don't need to see that, dude.");
    // Angmar
    add_cact("asay jeer So this hangmar soldier or whatever comes in and is "
    + "like Join us and we'll shield you with our covers or something, and "
    + "I'm like, Uh no, I already have a man, and I'm not getting under the "
    + "covers with a skank like you, SNAAAAAAP!");
    add_cact("asay laugh Angmar?!? More like STANK-mar!");
    // Templars
    add_cact("asay casua So this Templard of Texas or wherever comes in and "
    + "I'm like, I never heard of you, and he's all like, Well we don't do "
    + "anything but the Templards teach you to slap people on the back of "
    + "the head, or something like that, and I'm like, How about I cut you? "
    + "And he basically shut up at that point. I heard he quit and that their "
    + "priestess was all crying about it or something.");
    add_cact("asay aggress So this Templar of LaQuishus or something comes "
    + "in all disrespecting Palanthas, and I'm like, well, you wanna know "
    + "what I did to his -A-?!? I was like, BAM and then BAM and then oh "
    + "BAM man, and...\nThe Guard starts banging " + HIS(TO) + " hips "
    + "against the wall hard enough to make you think he's probably "
    + "jeopardizing " + HIS(TO) + " reproductive ability.");

    add_ask(({"hagen", "chief", "constable"}), "say Hagen is the Chief "
    + "Constable of Palanthas.  He's unstoppable and will throw any "
    + "miscreants in jail without a moment's hesitation.  They either "
    + "<surrender> or die, and that's always been the case.", 1);
    add_ask("jail", "say The jail is still in the Palace, but they're "
    + "building a newer, larger jail off the Palatial plaza.  I don't "
    + "think Lord Amothus appreciates using the palace as a jail.", 1);
    add_ask(({"city", "palanthas"}), "say Palanthas' majesty is unrivaled!  "
    + "The marble city is the best place to live in all the realms, and we "
    + "keep it completely safe.  The city has never been compromised.", 1);
    add_ask(({"guard", "guards", "guardsman"}), "say The city guard is well-"
    + "trained, competent, and motivated to keep Palanthas completely safe.  "
    + "That I promise.", 1);

    set_default_answer("@@def_answer");

    create_toa_guard();
}

void
adjects()
{
    adjstr1 = one_of_list(({"young", "cleanly", "smooth-chinned",
    "watchful-eyed", "youthful", "thin"}));

    adjstr2 = one_of_list(({"blond-haired", "black-haired", "buzz-cut",
    "brown-haired", "side-burned", "moustachioed", "short-haired"}));

    gender = one_of_list(({G_MALE, G_MALE, G_FEMALE}));
    set_gender(gender);
}

string
my_short()
{
    string gend = "male";

    if (TO->query_gender() == G_FEMALE)
    {
        gend = "female";
    }

    return adjstr1 + " " + adjstr2 + " " + gend + " guard";
}

string
def_answer()
{
    command("say You should ask my commander, citizen.");
    return "";
}

string
constable_symbol()
{
    return "a symbol of an upturned sword over the white palatial tower";
}

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy))
    { return; }
    
    if (random(5) == 1)
    { command("shout Miscreant! Employ force!"); }

    action_attack(enemy);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();

    if (TP->query_prop(LIVE_I_ATTACKED_PALANTHAS) == 1)
    {
        set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }

}

void
attacked_by(object ob)
{
    ob->add_prop(LIVE_I_ATTACKED_PALANTHAS, 1);

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    int pen, att, wloc, weptype, damtype;
    string hitloc, attack, how, how2, weapon;
    mixed hitres;
    object *wep = query_weapon(-1);

    if (!sizeof(wep))
    {
        return 0;
    }

    weapon = wep[0]->query_short();
    weptype = wep[0]->query_wt();

    switch (weptype)
    {
        case W_POLEARM:
            attack = "catch";
            damtype = W_IMPALE;
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case W_SWORD:
            attack = "pierce";
            damtype = W_IMPALE;
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case W_CLUB:
            attack = "clobber";
            damtype = W_BLUDGEON;
            hitloc = "head";
            wloc = A_HEAD;
            break;
        default:
            attack = "strike";
            damtype = W_SLASH;
            hitloc = "legs";
            wloc = A_LEGS;
            break;
    }

    if (random(6) == 1)
    {
        pen = 25 + random(100);
        hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

        if (hitres[0] <= 0)
        {
            how = "but misses";
            how2 = how;
        }
        if(hitres[0] > 0)
        {
            how = "barely landing";
            how2 = how;
        }
        if(hitres[0] > 10)
        {
            how = "incapacitating you slightly";
            how2 = "incapacitating " + HIM(enemy) + " slightly";
        }
        if(hitres[0] > 20)
        {
            how = "incapacitating you greatly";
            how2 = "incapacitating " + HIM(enemy) + " greatly";
        }
        if (hitres[0] > 40)
        {
            how = "with well-trained power";
            how2 = how;
        }
        if (hitres[0] > 60)
        {
            how = "with deadening force";
            how2 = how;
        }

        enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " your "
        + hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
        + QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
        + " " + how2 + ".\n", ({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }

        return 1;
    }

    return 0;
}
