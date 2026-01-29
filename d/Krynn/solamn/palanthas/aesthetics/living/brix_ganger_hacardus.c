/* 
 * Mid level member of the Brix gang in the back
 * alleys of Jems Court in the Aesthetics quarter
 * of Palanthas.
 *
 * Mortis 05.2006
 *
 * Mortis 09.2014 - Changed attacked by messages. Increased special dmg ~10%
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

inherit BRIX_GANGER;

/*prototype*/
void arm_me();
int special_attack2(object enemy);

void
create_brix_ganger()
{
    seteuid(getuid(TO));

    set_name("hacardus");
    add_name(({"_brix_ganger", "ganger", "gangster", "thug"}));
    set_adj("fiendish-eyed");
    add_adj("malevolent");
    set_gender(G_MALE);
    set_short("fiendish-eyed malevolent male thug");
    set_long("Prominent browed with short cut, well-groomed black hair and "
    + "demonically slanted eyebrows, this thug's green-eyed gaze is "
    + "piercingly fiendish and aggressive.  His grin is pulled back "
    + "malevolently wide, revealing a row of perfect, white teeth.\n"
    + "He moves with a lanky grace and maintains a controlled posture.\n"
    + "He has a tattoo of a flaming knife spinning in motion on his left "
    + "hand and a rampant, one-winged blue dragon on his right arm.\n"
    + "He has burnt and scarred flesh on his left shoulder and bicep.\n");
    set_race_name("human");
    set_living_name("hacardus");
    set_title("the Former Blue Thug and Blade of the Brix");
    
    set_size_descs("of normal length", "of normal width");
    set_appearance(4);

    set_all_hitloc_unarmed(5);

    set_skill(SS_DEFENCE,      65);
    set_skill(SS_PARRY,        65);
    set_skill(SS_2H_COMBAT,    65);
    set_skill(SS_UNARM_COMBAT, 45);
    set_skill(SS_AWARENESS,    35);
    set_skill(SS_WEP_KNIFE,    70);
    set_skill(SS_BLIND_COMBAT, 50);

    set_stats((({107, 170, 117, 111, 98, 140})), 3);

    set_alignment(-850);
    set_knight_prestige(50);

    set_introduce(1);

    set_default_answer("@@def_answer");

    add_ask(({"palanthas", "city"}), "asay deris Palanthas is great?  "
    + "Palanthas is safe?  Who's looking out for the little man?  Hagen?  "
    + "Who's looking out for the hood?  The Brix.  That's who.", 1);
    add_ask(({"chief", "constable", "hagen"}), "asay aci Hagen?  Ol'red "
    + "better not show his face 'round here.  Course he knows already "
    + "not to mess with Brix.", 1);
    add_ask(({"brix", "gang", "gangs", "hoodlum", "hoodlums", "ganger",
        "gangers"}), "asay proud Kirk and The Brix, we own Jems court, "
    + "see?  We look out for our own and provide protection.  You tread "
    + "on our turf or cross us?  You get smashed?  Samma wagga kan?  "
    + "That's elf for \"Get it, hoser?\"", 1);
    add_ask(({"brick", "bricks"}), "asay know The bricks were Kirk's idea.  "
    + "We started with nothin', see?  Now we got it all, but we don't forget "
    + "our roots.  The Brix smash!", 1);
    add_ask(({"leader", "kirk"}), "asay quiet Kirk's head man around here.  "
    + "Not even Hagen wants a piece of him.", 1);
    add_ask(({"gamble", "gambling", "dice", "onjat", "game"}), "asay secret "
    + "Yeah, we run a little game of onjat downstairs through the tunnel, "
    + "but you better not try your hand there if you're spoiling for "
    + "trouble.  You won't -walk- back out.", 1);
    add_ask(({"monk", "monks", "aesthetic", "aesthetics"}), "asay amus Yeah, "
    + "the scroll heads come down here for a game every once in a while.  "
    + "Kirk doesn't mind.  They don't cause trouble.  They're smart like "
    + "that, see?", 1);

    set_act_time(45);
    add_act("get it");
    add_act("ffinger ganger");
    add_act("smile malev");
    add_act("asay inq Anyone up for a game later?");
    add_act("asay gre Yeah, well I won eighty in last night's onjat.");
    add_act("asay grave Last time I saw someone pull that, they dragged "
    + "him out of the tunnel...  one sackfull at a time.");
    add_act("fart");
    add_act("emote smashes what used to be a bug into goo with an old red "
    + "brick.");
    add_act("emote flashes his fiendish eyes in a malevolent gaze.");
    add_act("asay menac What are you doing in the court?");
    add_act("asay angr Gambling?  Who the frung said anything about "
    + "gambling?");
    add_act("asay hung What do you mean 'What's a T-hole?!?' It's the hole "
    + "your turds come out of, you chungalungo!");

    set_cact_time(40);
    add_cact("@@whip_it");

    set_alarm(1.0, 0.0, "arm_me");
}

string
def_answer()
{
    command("say How the frung should I know? " + one_of_list(({"The Brix "
    + "don't give shit for that.", "Now get lost. This is our street.",
      "Don't mess with the Brix unless you like getting smashed.", "You ask "
    + "too many questions."})));
    return "";
}

string
whip_it()
{
    object myenemy = TO->query_enemy();

    if (!objectp(myenemy))
    {
        command("say Huh?");
        return "";
    }

//    string whipwho = L(myenemy->query_name());

    command("asay vicious Hoyr Yukesh!\n");
    myenemy->command("shout Noooooooo!");
//    command("knee " + whipwho); Don't think this worked.
    command("knee enemy");
    return "";
}

void
arm_me()
{
    object wpants, wshirt, wshoes, wchest, mywep1, mywep2, mypack;

    mypack = clone_object(MERCH + "obj/lgeneral");
    mypack->set_general_data("ornate" + "&&" + "blue" + "&&" + "soft" + "&&"
                            + "bandeleria");
    mypack->move(TO);
    
    wshirt = clone_object(NOBLE + "arms/parmour");
    wshirt->set_armour_data("the Brix" + "&&"
                            + "laced" + "&&"
                            + "black" + "&&"
                            + "hemp" + "&&"
                            + "vest");
    wshirt->move(TO);

    wchest = clone_object(MERCH + "arms/larmour");
    wchest->set_armour_data("plain" + "&&"
                            + "brown" + "&&"
                            + "leather" + "&&"
                            + "cuirasse");
    wchest->move(TO);

    wpants = clone_object(MERCH + "arms/larmour");
    wpants->set_armour_data("plain" + "&&"
                            + "brown" + "&&"
                            + "leather" + "&&"
                            + "leggings");
    wpants->move(TO);

    wshoes = clone_object(MONKS + "arms/lurr_shoes");
    wshoes->set_footwear_data("plain" + "&&" + "brown" + "&&"
                              + "leather" + "&&" + "slippers");
    wshoes->move(TO);

    mywep1 = clone_object(MERCH + "arms/smith_knife");
    mywep1->set_weapon_data("curved" + "&&" + "curved" + "&&" + "knife");
    mywep1->move(TO);

    mywep2 = clone_object(MERCH + "arms/smith_knife");
    mywep2->set_weapon_data("long" + "&&" + "wide" + "&&" + "machete");
    mywep2->move(TO);

    clone_object(MONKS + "arms/brix_star")->move(TO);
    if (random(2) == 1)
        clone_object(MONKS + "arms/brix_star")->move(TO);
    if (random(2) == 1)
        clone_object(MONKS + "arms/brix_star")->move(TO);

    MONEY_MAKE_GC(10 + random(6))->move(TO);
    MONEY_MAKE_SC(20 + random(40))->move(TO);

    command("wear all");
    command("wield all");
    command("fill band");
    
    clone_object(MONKS + "arms/brix_star")->move(TO);
}

void
attacked_by(object ob)
{
    switch (random(15))
    {
        case 0:
            command("asay obn Better check this one's loincloth.  I think "
            + HE(ob) + " just dropped a brick.");
            break;
        case 1:
            command("asay firm No one messes with the Brix.  Smash this ho!");
            break;
        case 2:
            command("shout Hey, this \"" + ob->query_adj() + "\" "
            + ob->query_race_name() + " wants to kiss me!  Get off me, pig!");
            break;
        case 3:
            command("say Take this, fool!");
            command("finger " + L(QNAME(ob)));
            break;
        case 4:
            command("Brix gonna make bread from your bones and make you eat "
            + "it!");
            break;
        default:
            command("say Guess where this goes!");
            command("show knife");
            break;
    }

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    if (random(5) != 1)
        return 0;

    enemy->catch_msg(QCTNAME(TO) + " draws a three-bladed throwing star " 
    + "from his ornate blue soft leather bandeleria and flings it in a "
    + "razor spinning arc at you.\n");

    tell_room(E(TO), QCTNAME(TO) + " draws a three-bladed throwing star " 
    + "from his ornate blue soft leather bandeleria and flings it in a "
    + "razor spinning arc at " + QTNAME(enemy) + "!\n", ({enemy, TO}));

    set_alarm(2.0, 0.0, "special_attack2", enemy);

    return 1;
}

int
special_attack2(object enemy)
{
    int pen, wloc, damtype = W_SLASH;
    string hitloc, how, how2;
    mixed hitres;

    switch (random(4))
    {
        case 0:
            hitloc = one_of_list(({"head", "forehead"}));
            wloc = A_HEAD;
            break;
        case 1:
            hitloc = one_of_list(({"body", "chest", "stomach", "gut",
                "ribs", "t-hole"}));
            wloc = A_TORSO;
            break;
        case 2:
            hitloc = one_of_list(({"right arm", "left arm",
                "right shoulder", "left shoulder", "right forearm",
                "left forearm", "right bicep", "left bicep"}));
            wloc = A_ARMS;
            break;
        case 3:
            hitloc = one_of_list(({"legs", "right thigh", "left thigh",
                "right knee", "left knee", "right shin", "left shin"}));
            wloc = A_LEGS;
            break;
        default:
            hitloc = "nuglek";
            wloc = A_TORSO;
            break;
    }

    pen = 61 + random(85); // Increased from 51 + random(75)
    hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

    switch (hitres[0])
    {
        case -1..0:
            enemy->catch_msg(QCTNAME(TO) + "'s three-bladed throwing star "
            + "goes spinning past your " + hitloc + " with a low whizz.\n");

            tell_room(E(TO), QCTNAME(TO) + "'s three-bladed throwing star "
            + " goes spinning past " + QTNAME(enemy) + "'s " + hitloc
            + " with a low whizz.\n", ({enemy, TO}));
            return 1;
            break;

        case 1..6:
            how = "leaving a shallow cut as it spinningly grazes by";
            how2 = how;
            break;

        case 7..14:
            how = "slicing it open as it spinningly flies by";
            how2 = how;
            break;

        case 15..30:
            how = "ripping it open sending blood spinning through the air "
            + "as it whizzes by";
            how2 = how;
            break;

        case 31..49:
            how = "ripping through flesh as it sticks into you";
            how2 = "ripping through flesh as it sticks into " + HIM(enemy);
            break;

        default:
            how = "eviscerating flesh as it sticks into you deeply";
            how2 = "eviscerating flesh as it sticks into " + HIM(enemy)
            + " deeply";
            break;
    }

    enemy->catch_msg(QCTNAME(TO) + "'s three-bladed throwing star spins "
    + "into your " + hitloc + " " + how + ".\n");

    tell_room(E(TO), QCTNAME(TO) + "'s three-bladed throwing star spins "
    + "into " + QTNAME(enemy) + "'s " + hitloc + " " + how2 + ".\n",
        ({enemy, TO}));

    if (enemy->query_hp() <= 0)
        enemy->do_die(TO);

    return 1;
}
