/* 
 * Kirk's "doc" in the Brix gang in the back
 * alleys of Jems Court in the Aesthetics quarter
 * of Palanthas.
 *
 * Mortis 06.2006
 *
 * Mortis 09.2014 - Changed attacked by messages.
 */

#include "../../local.h"
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit BRIX_GANGER;
inherit "/lib/unique";

/*prototype*/
void arm_me();
void wield_fists(object doc);
string quaff_it();
void troll_heal(object doc);
void speed_up(object doc);
void speed_down(object doc);

void
create_brix_ganger()
{
    seteuid(getuid(TO));

    set_name("doc");
    add_name(({"_brix_ganger", "ganger", "gangster", "hoodlum"}));
    set_adj("saggy-eyed");
    add_adj("frayed-haired");
    set_gender(G_MALE);
    set_short("saggy-eyed frayed-haired male human");
    set_long("This middle-aged man's skin is wrinkled and weathered for his "
    + "age, and his eyes, sunken atop dark, saggy circles, are hollow and "
    + "blank yet stare out at you with a crazed glint.  His wispy, brown "
    + "hair stands out in frayed tufts that fail to cover parts of his "
    + "scalp.\n"
    + "He has a tattoo of a crazily laughing demon with a long face, horns, "
    + "green fangs, and a jester's hat on his left bicep.\n"
    + "He is wearing a cork hanging from a leather string around his neck.\n");
    set_race_name("human");
    set_living_name("doc");
    set_title("the Mikser, Underfriend of the Brix");
    
    set_size_descs("of normal length", "lean");
    set_appearance(0);

    set_all_hitloc_unarmed(5);

    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        20);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS,    65);
    set_skill(SS_WEP_KNIFE,    50);

    set_stats((({70, 50, 80, 190, 200, 125})), 8);

    add_prop(LIVE_I_SEE_DARK, 1);

    set_alignment(-950);
    set_knight_prestige(50);

    set_introduce(1);

    set_default_answer("@@def_answer");

    add_ask(({"palanthas", "city"}), "asay blank What a city... what a "
    + "time... a time we've had... I've had.  Palanthas.", 1);
    add_ask(({"chief", "constable", "hagen"}), "asay aci Hagen?  He'd give "
    + "anything to... Hagen, yes...", 1);
    add_ask(({"brix", "gang", "gangs", "hoodlum", "hoodlums", "ganger",
        "gangers"}), "asay nod Kirk is a blessing, a blessing for "
    + "business and a true friend.", 1);
    add_ask(({"brick", "bricks"}), "asay know The bricks were Kirk's idea.  "
    + "They started with nothin', now they have it all, but they don't forget "
    + "their roots.  That's what I like about them.", 1);
    add_ask(({"leader", "kirk"}), "asay quiet Kirk's head man around here.  "
    + "Not even Hagen wants a piece of him.", 1);
    add_ask(({"gamble", "gambling", "dice", "onjat", "game"}), "asay secret "
    + "Yes, they run a little game of onjat down west through the tunnel, "
    + "but you better not try your hand there if you're spoiling for "
    + "trouble.  You won't -walk- back out.", 1);
    add_ask(({"monk", "monks", "aesthetic", "aesthetics"}), "asay amus Yeah, "
    + "the scroll heads come down here for a game every once in a while.  "
    + "Kirk doesn't mind.  They don't cause trouble.  And some like to "
    + "enjoy themselves if you know what I mean, expand their horizons?", 1);

    set_act_time(45);
    add_act("smile greed");
    add_act("smile drool");
    add_act("asay inq Anyone up for a game later?");
    add_act("asay gre Yeah, well I won fifty in last night's onjat.");
    add_act("asay grave Last time I saw someone pull that, they dragged "
    + "him out of the tunnel...  one sackfull at a time.");
    add_act("emote stares blankly, his left eye nearly closing, as he lets "
    + "out a fart with a bizarre, squirty \"pfffflllsss\" noise that stops "
    + "and starts sporadically.");
    add_act("asay menac In the market?");
    add_act("asay amus Gambling?  Whoever said anything about "
    + "gambling?");

    set_cact_time(40);
    add_cact("@@quaff_it");

    set_alarm(1.0, 0.0, arm_me);
}

string
def_answer()
{
    command("say However should I know?  " + one_of_list(({"Oh, I see.  "
    + "Are you in the market?", "You ask too many questions."})));
    return "";
}

string
quaff_it()
{
    object myenemy = TO->query_enemy();

    if (!myenemy)
        command("say What the..!?!");

    switch (random(4))
    {
        case 0:
            command("emote pulls a smoked-glass vial of green liquid "
            + "from his belt and throws the gunky mixture back in one "
            + "gulp!");
            set_alarm(5.0, 3.0, "troll_heal", TO);
            break;
        case 1:
            command("emote pulls a chalk-dusted ceramic vial, pops the "
            + "cork, and throws back the clear liquid within in one gulp!");
            set_alarm(4.0, 0.0, "speed_up", TO);
            break;
        default:
            string kneewho = L((myenemy)->query_name());

            command("asay angr Take this, knobbler!");
            myenemy->command("shout Aiyeeeeee!");
            command("knee " + kneewho);
            break;
    }

    return "";
}

void
troll_heal(object doc)
{
    doc->command("emote cackles roughly as his skin turns lumpy and a dull "
    + "green for a moment.\nHis wounds seem to close on their own.");
    doc->heal_hp(250);
}

void
speed_up(object doc)
{
    doc->command("emote gurgles harshly as his eyes bulge out and jaw drops!");
    doc->command("emote begins to move with a jerky speed that almost seems "
    + "to blur his movements briefly.");
    doc->add_prop(LIVE_I_QUICKNESS, 100);
    set_alarm(25.0, 0.0, "speed_down", doc);
}

void
speed_down(object doc)
{
    doc->command("emote sputters as his eyes glaze over and his movements "
    + "become lethargic and drawn out.");
    doc->add_prop(LIVE_I_QUICKNESS, 1);
}

void
arm_me()
{
    object wpants, wshirt, wshoes;

    wshirt = clone_object(NOBLE + "arms/parmour");
    wshirt->set_armour_data("the Brix" + "&&"
                            + "tight" + "&&"
                            + "black" + "&&"
                            + "hemp" + "&&"
                            + "sleeveless-shirt");
    wshirt->set_condition(1);
    wshirt->move(TO);

    wshoes = clone_object(MONKS + "arms/lurr_shoes");
    wshoes->set_footwear_data("open-toed" + "&&" + "mottled-brown" + "&&"
                              + "leather" + "&&" + "slippers");
    wshoes->move(TO);

    clone_object(MONKS + "arms/brix_pants_mid")->move(TO);

    MONEY_MAKE_GC(random(6))->move(TO);
    MONEY_MAKE_SC(20 + random(20))->move(TO);

    command("wear all");
    command("wield all");

    clone_unique(MONKS + "arms/brix_fist_spikes", 5,
        MONKS + "arms/brix_brass_knuckles", 1, 70)->move(TO);

    set_alarm(1.0, 0.0, &wield_fists(TO));
}

void
wield_fists(object doc)
{
    doc->command("wear spikes");
    doc->command("wear knuckles");
}

void
attacked_by(object ob)
{
    switch (random(10))
    {
        case 0:
            command("asay obn Better check this one's loincloth.  I think "
            + HE(ob) + " just dropped a brick.");
            break;
        case 1:
            command("asay firm No one messes with the Brix.  Smash this ho!");
            break;
        case 2:
            command("say Guess where this goes!");
            command("show knife");
            break;
        case 3:
            string xname = L(ob->query_name());
            command("say Take this, fool!");
            command("slap " + xname);
            break;
        case 4:
            command("Brix gonna make bread from your bones and make you eat "
            + "it!");
            break;
        default:
            command("shout Hey, this \"" + ob->query_adj() + "\" "
            + ob->query_race_name() + " wants to kiss me!  Get off me, pig!");
            break;
    }

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
        weapon = "fists";
        weptype = W_BLUDGEON;
    }
    
    else
    {
        weapon = wep[0]->query_short();
        weptype = wep[0]->query_wt();
    }

    switch (weptype)
    {
        case W_KNIFE:
            attack = "stick";
            damtype = W_IMPALE;
            break;
        case W_CLUB:
            attack = "bash";
            damtype = W_BLUDGEON;
            break;
        default:
            attack = "bash";
            damtype = W_BLUDGEON;
            break;
    }

    switch (random(4))
    {
        case 0:
            hitloc = "head";
            wloc = A_HEAD;
            break;
        case 1:
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case 2:
            hitloc = one_of_list(({"right arm", "left arm"}));
            wloc = A_ARMS;
            break;
        case 3:
            hitloc = "legs";
            wloc = A_LEGS;
            break;
        default:
            hitloc = "nuglek";
            wloc = A_TORSO;
            break;
    }

    if (random(8) == 1)
    {
        pen = 135 + random(55);
        hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

        switch (hitres[0])
        {
            case -1..0:
                how = "but misses";
                how2 = how;
                break;

            case 1..6:
                how = "barely landing";
                how2 = how;
                break;

            case 7..14:
                how = "with cheap, underhanded moves";
                how2 = how;
                break;

            case 15..30:
                how = "in a display of backstreet cunning";
                how2 = how;
                break;

            case 31..49:
                how = "maiming you visibly";
                how2 = "maiming " + HIM(enemy) + " slightly";
                break;

            default:
                how = "maiming you greatly";
                how2 = "maiming " + HIM(enemy) + " greatly";
                break;
        }

        enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " your "
        + hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
        + QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
        + " " + how2 + ".\n", ({enemy, TO}));

        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);

        return 1;
    }

    return 0;
}

