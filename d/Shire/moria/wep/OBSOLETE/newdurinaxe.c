//
// durinaxe.c	- Durin's Axe.
//
// This is first of all a quest item. For further info see ~doc/OgressQuest
// A difficult quest, but the weapon is *very* good,
// especially against some kinds. It is inteligent, see the magic description.
//
// It also has a special way of command, you can 'throw axe [at someone]'.
// Then it will float in the air hitting a target, returning instantly in
// the wielders hand. You can also do a 'Longdoor' call to it. And the axe
// will be retrieved to the last wielder. -edited out by Dunstable
//  on reviewing the quest and the axe. 3-21-95
//
// The main purpose of this weapon is to besiege the balrog. It will go 
// crazy when it meets the Balrog of Moria, thus giving the mortals a 
// *chance* to kill the balrog at all. -Agree here :) D.

#include "defs.h"
#include "/d/Immortal/rogon/include/lib.h"

inherit BASE_WEAPON;
inherit IM_TELL_FILE;

#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

#define WC_PEN 60
#define WC_HIT 60

int state;

CONSTRUCT_WEAPON {
   set_name("axe");
   add_name("_durins_axe_");
   add_name("waraxe");
   set_short("@@my_short@@");
   set_pshort("twinkling waraxes"); /* should never be needed! */
   set_adj(({"twinkling","durin's","dwarven","mithril","magical", "enchanted"}));
   set_long("@@my_long");
   set_hit(WC_HIT);
   set_pen(WC_PEN);
   set_pm(({0,4,-4}));
   set_wt(W_AXE);
   set_wf(TO);
   set_dt(W_SLASH | W_BLUDGEON);
   set_hands(W_ANYH);
   add_item(({"runes", "axe's runes", "runes on axe", "ornaments"}),
	"They say: Dare not touch me if thou art not worthy!\n");
   add_prop(MAGIC_AM_MAGIC,
       ({
     	  25, "undead-slaying",
	      22, "enchantment",
	     20, "evil-slaying",
   	  30, "magical artifact",
	    70, "balrog-slaying",
	    20, "dragon-slaying"
       })
   );
   add_prop(MAGIC_AM_ID_INFO,
       ({ "The dwarven waraxe seems to be very well crafted.\n", 1,
	  "It is shining and seems to be magical.\n", 13,
	  "It is made of mithril, so it is very powerful and even light.\n", 26,
	  "It is of slaying versus evil.\n", 38,
	  "It is also of slaying versus Balrogs and Dragons.\n", 58,
	  "It does extra damage against evil, Balrogs and Dragons.\n", 67,
	  "It is intelligent and connected with the land, so it will travel\n"+
	  "back to it's origin in the Mines of Moria if it is outside Middle-Earth.\n", 83,
   }) );
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_LIGHT, 1);

   add_prop(OBJ_I_VOLUME, 2200);
   add_prop(OBJ_I_WEIGHT, 2600); /* 2.6 kg: It is of Mithril & magic. */
   add_prop(OBJ_I_VALUE,  12*F_VALUE_WEAPON(60, 60) + random(1000) - 500);
   add_prop(OBJ_M_NO_SELL,
	"The waraxe seems very unhappy at being sold.\n");
}

/*
#include "recover"
*/

int query_usable(object who) {
    return (who->query_race()=="dwarf" ||
	    who->query_stat(SS_WIS)>60 ||
	    who->query_stat(SS_INT)>60 ) && (who->query_alignment()>250 &&
	    who->query_skill(SS_WEP_AXE)>39);
}

mixed
wield(object to)
{
    object wielder = ENV(to);
    string wield_msg;

    if(!wielder) return -1;

    switch(wielded_in_hand)
    {
	case W_BOTH:
	    wield_msg = "in both your hands";
	    break;
	case W_LEFT:
	    wield_msg = "in your left hand";
	    break;
	case W_RIGHT:
	    wield_msg = "in your right hand";
	    break;
    }

    if(!query_usable(wielder)) {
	write(
	    "As you try to wield the dwarven waraxe, a sting of pain hits you!!\n"
	);
	say(QCTNAME(TP)+" gets a funny look in "+HIS_HER(TP)+" face while trying to wield the waraxe.\n");
	if(HP(TP)>2000)
	    TP->heal_hp(2000-HP(TP)-random(1000));
       if(HP(TP) <= 0) TP->do_die(this_object());
	else if(HP(TP)>200)
	    TP->heal_hp(200-HP(TP)-random(100));
      if(HP(TP) <= 0) TP->do_die(this_object());
	else
	    TP->heal_hp(-random(HP(TP)));
	TP->command("drop _durins_axe_");
      if(HP(TP) <= 0) TP->do_die(this_object());
	return "The axe did not approve your attempt to wield it!\n";
    }
    if(wielder->query_race_name()=="dwarf") {
	write(
	    "As you wield the dwarven waraxe "+wield_msg+", you awesomly realize the power of "+
	    "this magical artifact! It swings lightly in the air, as if it has its own life!\n");
	say(QCTNAME(TP)+" wields the dwarven waraxe.\n"+
	    CAP(HE_SHE(TP))+" swings it around, and "+QTNAME(TP)+" looks powerful and strong "+
	    "with it.\n");
	wielder->command("grin");
   wielder->command("shout Hail Durin! Khazad! Khazad! Khazad!!!");
	return 1;
    }
    write(
	"You wield the dwarven waraxe "+wield_msg+".\n"+
	"Although not so adept with the dwarven fashion of warcraft, you realize "+
	"the powers that lies within this blade of old.\n");
    say(QCTNAME(TP)+" wields "+HIS_HER(TP)+" dwarven waraxe.\n");
    return 1;
}

int
unwield()
{
    return 0;
}


string
my_short()
{
    if (state <= 25)
	return "dwarven waraxe";
    else if (state <= 125)
	return "twinkling dwarven waraxe";
    else if (state <= 250)
	return "red glowing waraxe";
    else if (state <= 500)
	return "awesome dwarven waraxe";
    else
	return "red-flashing dwarven waraxe";
}


string
my_long() {
  if(query_usable(this_player()))
    return
      "This is Durin's Axe!\n"+
      "    Manufactured in the First Age by dwarven smiths in the depths of "+
      "Khazad-dum, this artifact is probably the most valuable of all "+
      "items made by the Dwarves. It is quite light, and shines in the "+
      "light, as it is made of mithril and other components unknown now "+
      "for ages. The edges are covered in blood, and it is ornamented "+
      "with posh golden runes.\n"+
      "    You feel that this weapon contains powers unimaginable.\n";
  else
    return
      "This is a small waraxe with posh golden ornaments.\n"+
      "The edge is covered with blood.\n";
}

int
try_hit(object enemy)
{
    object tp=query_wielded();

    if(enemy->query_alignment()>100)
	tp->catch_msg("The dwarven waraxe refuses to hit "+QTNAME(enemy)+"!!\n");

    if(enemy->query_alignment()>200)
    {
	tp->catch_msg(
	    "You feel a sting through your heart attempting to "+
	    "meddle the honour of Durin's Axe!\n");
	tp->heal_hp(-random(enemy->query_alignment()/5));
	tellem(tp, enemy, "(You) loose[s] the grip of [your] dwarven waraxe!\n");
	TO->move(ETP);
    }
    if (enemy->query_race_name() == "balrog")
    {
   	call_out("go_crazy", 1, enemy);
   	return 1;
    }
    return enemy->query_alignment()<=0;
}

/*
 * This magically enchanted and intelligent weapon, is in fact a legendary
 * dwarven (magical) artifact. In order to simulate this I have added extra
 * hits, though only up to the damage already done in the combat system.
 *
 * The extra_dam variable is the percentile amount of extra damage.
 *
 * Note: The tellem routine is just for printing out messages to the involved
 *	 parties. See /d/Shire/common/lib/tellem.c for syntax.
 *
 */
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object tp;
    string you_x_him, you_x_axe, land_x, wound_x, where, place;
    int extra_dam = 0;

    tp = query_wielded();
    if(!query_usable(tp))
        return 0;

    if(enemy->query_race_name()=="dragon")
	extra_dam += 150;
    if(enemy->query_race_name()=="balrog")
	extra_dam += 433;
    if(enemy->query_alignment()<0)
	extra_dam += -enemy->query_alignment()/20;
    if(enemy->query_prop(LIVE_I_UNDEAD))
	extra_dam += 100;

   state = extra_dam + random(150);

    extra_dam = random(extra_dam);

   place == environment(this_player())->query_domain();

   if((place != "Shire") && (place != "Gondor") && (place != "Rhovanion"))
    {
   	extra_dam = 0;
    	if(!random(5))
   	{
	    tellem(tp, enemy,
		"$N's waraxe seems unhappy! It wants to go home!\n"+
		"In a sudden flash of fire, the waraxe of Durin disappears!!\n");
	    call_out("remove_object", 0);
	    }
    }

    if (dam <= 0)
	extra_dam = 0;

    extra_dam = MIN(extra_dam,800);

    if (extra_dam>300)
	tellem(tp, enemy,
	    "$N's waraxe flashes in fire!!!\n");
    else if (extra_dam>150)
	tellem(tp, enemy,
	    "$N's waraxe sings in the air!!\n");
    else if (extra_dam>65)
	tellem(tp, enemy,
	    "$N's waraxe shines deeply in red!\n");
    else if (extra_dam>25)
	tellem(tp, enemy,
	    "$N's waraxe seems delighted.\n");


    enemy->heal_hp(-extra_dam);

    phurt += extra_dam + dam /MAX_HP(enemy);

    if (HP(enemy) <= 0)
    {
	if (hdesc=="head")
	    dam = "brain-matter";
	else
	    dam = "blood";

	tp->catch_msg(
	    "You cleave "+QTNAME(enemy)+" deeply into "+HIS_HER(enemy)+" "+hdesc+"!\n"+
	    QCTNAME(enemy)+" staggers as "+ dam +" gushes out of the cut!\n"+
	    QCTNAME(enemy)+" screams loudly in pain!\n"+
	    QCTNAME(enemy)+"'s face grows pale.\n"+
	    QCTNAME(enemy)+" drops flat over, falling like a gory pulp of meat by your feet.\n");
	enemy->catch_msg(
	    QCTNAME(tp)+" cleaves deeply into your "+hdesc+"!\n"+
	    "You stagger as you watch your " + dam +" gushing out of the cut!\n"+
	    "You scream loadly in pain as you drop flat over.\n"+
	    "Facing the blood-covered floor, you feel your last heartbeats die out...\n");
	tell_room(ENV(tp),
	    QCTNAME(tp)+" cleaves "+QTNAME(enemy)+" deeply into "+HIS_HER(enemy)+" "+hdesc+"!\n"+
	    QCTNAME(enemy)+" staggers as " + dam + " gushes out of the cut!\n"+
	    QCTNAME(enemy)+" screams loudly in pain!\n"+
	    QCTNAME(enemy)+"'s face grows pale.\n"+
	    QCTNAME(enemy)+" drops flat over, falling like a gory pulp of meat by "+QTNAME(tp)+" feet.\n",
	    ({ tp, enemy }));

	enemy->do_die(tp);
	return 1;
    }

#define YOU_S_HIM     ({ "slash", "cut", "slay", "slate", "slaughter" })
#define YOU_C_HIM     ({ "crush", "hurt", "schmack", "shatter" })

#define YOU_S_AXE     ({ "swing", "hurl", "cleave" })
#define YOU_C_AXE     ({ "swing", "hurl" })

#define LAND_S        ({ "yawn", "moan", "crush", "blow", "hurl", "strike", "schmack" })
#define LAND_C        ({ "land", "crush", "blow", "hurl", "paralyze","leap", "shatter" })

#define WOUND_S       ({ "slash", "cut" })
#define WOUND_C       ({ "blow", "crush" }) 

#define ONE_OF(arr) arr[random(sizeof(arr))]

    if (phurt > 0)
    {
   	if (dt == W_SLASH)
  	{
	    you_x_him = ONE_OF(YOU_S_HIM);
	    you_x_axe = ONE_OF(YOU_S_AXE);
            land_x    = ONE_OF(LAND_S);
            wound_x   = ONE_OF(WOUND_S);
   	} else {
	    you_x_him = ONE_OF(YOU_C_HIM); 
	    you_x_axe = ONE_OF(YOU_C_AXE);
            land_x    = ONE_OF(LAND_C); 
            wound_x   = ONE_OF(WOUND_C);
    	}
   }

    produce_message(tp, enemy, phurt, ({
	({
	    "$N $aim for #n's &body with $p &waraxe, but $miss.",
	    "$N's &waraxe leaps towards #n's &body, but it missed.",
	    "$N thought $s had a good attack at #n, but $s missed.",
	})[random(3)],
	({ "$N's &waraxe swings dangerously close to #n's &body!",
	   "$N's &waraxe grazes #n's &body." })[random(2)],

//-------------------------     Hits    ---------------------------------//

	"$N $:slash: #n with $your &waraxe. It :yawns: into #p &body.",
	"$N $:slash: #n with a brave :cut: which :yawns: into #p &body.",
	"$N swiftly $perform a :cut: with $p &waraxe which :yawns: into #n's &body.",
	"$N $:swing: $p &waraxe into #n! It :yawns: into #p body.",
	"$N's nasty :cut: with $p &waraxe :yawns: into #n's &body!",
	"Blood flows as $n's &waraxe :yawns: into #n's &body!",
	"In an utterly devastating :cut:, $n's &waraxe "+
	    ":yawns: into #n's &body!!",
	"$N's &waraxe :yawns: into #n's "+
	    "&body in a massacrating :cut:!!",
	"$N's &waraxe devastates #n with a breathtaking strike! "
	  + "It :yawns: into #p &body with extraordinary "
	  + "{beauty;anguish;anger}, leaving ${the poor #race;your sad remains} "
	  + "in shock and despair by $your mighty :cut:.",
	"$N's &waraxe sings in joy as it :yawns: into #n's &body! "
	  + "It cleaves deeply into {the poor #race's;your;"
	  + "the devastated #race's} &body with an unearthly "
	  + "massacrating and bone-crushing sound. #N #tremble "
	  + "in shock, and #p face grows pale with fear, "
	  + "realizing the power and the anger of $N's "
	  + "mighty dwarven artifact!"
    }), ([
	"&body"   : hdesc,
	"&waraxe" : short(),
	":slash:" : you_x_him,
	":swing:" : you_x_axe,
        ":yawns:" : verb_for_he_she_it(land_x),
	":cut:"   : wound_x
    ]));
    return 1;
}

int
do_hit(object enemy, object wielder)
{
    mixed ret;
    string TheAxe = "The " + QSHORT(TO);
    string TheAxeHurls = TheAxe + " hurls against #n";

    ret = enemy->hit_me(WC_PEN, W_SLASH, wielder, -1);

    if (HP(enemy) <= 0)
    {
	enemy->command("scream");
	enemy->catch_msg("Blood flows out of the cut and you faint instantly.\n");
	enemy->catch_msg(VCPOSS(wielder) + " " + QSHORT(TO) + " killed you.\n");
	tell_room(ENV(wielder),
	    VCPOSS(enemy) + " blood flows out of the cut and " + HE_SHE(enemy)
	  + " faints immediately, falling in " + HIS_HER(enemy) + " puddle "
	  + "of blood.\n"
	  + VCPOSS(wielder) + " " + QSHORT(TO) + " killed " + HIM_HER(enemy) + ".\n", enemy);
	enemy->do_die(wielder);
	return 0;
    }

    if (wielder->query_name() == "Rogon")
	write("do_hit: phurt = " + ret[0] + ", hdesc = '" + ret[1]
	    + "', phit = " + ret[2] + ", dam = " + ret[3] + "\n");

    produce_message(wielder, enemy, ret[0], ({
	TheAxeHurls + ", but it misses completely.",
	TheAxe + " whistles past #n's head!",
	TheAxeHurls + " and grazes #p &body!",
	TheAxeHurls + " slicing #p &body!",
	TheAxeHurls + " cleaving #p &body!",
	TheAxeHurls + " as it penetrates deeply into #p &body!!",
	TheAxeHurls + " hitting #o severely as it cleaves #p &body deeply!!!",
	TheAxeHurls + " and hurts #n badly with a deep hew!!!",
	TheAxeHurls + " as it sings slashing deep into #p &body!!!",
	TheAxeHurls + " penetrating #p &body, and #p blood begins to gush out!!!"
    }), ([ "&body": ret[1] ]));

    return 0;
}

int
is_potential_enemy(object who)
{
    return member_array(who, TP->query_team(-1)) == -1 && TP!=who;
}

/*  Nope, we're not going to use this function, just yet.
     Dunstable 3-21-95
int
do_throw(string arg)
{
    object obj;
    mixed livs = FILTER_PRESENT_LIVE(TP->query_enemy(-1));

    notify_fail(CAP(query_verb()) + " what?\n");

    if (parse_command(arg, INV(ETP) + INV(TP), "%o 'at' [the] %l", obj, livs))
    {
	livs = VISIBLE_ACCESS(livs, "is_potential_enemy", TO);
	if (!sizeof(livs))
	    return notify_fail(CAP(query_verb())+ " it at whom?\n");
    }
    else if (!parse_command(arg, INV(TP), "%o", obj))
	return 0;

    if (obj != TO)
	return 0;

    if (!sizeof(livs))
	return notify_fail(CAP(query_verb())+ " it at whom?\n");

    action("$N $hurl $p dwarven waraxe into the air!!!!\n");
    tell_room(ETP, "The " + QSHORT(TO) + " seems to float in thin air!!\n");
    map(livs, "do_hit", TO, wielder);
    tell_room(ETP, "The " + QSHORT(TO) + " returns back into "+VPOSS(TP)+" hands!!\n");
    return 1;
}
*/
//---------------- Going CRAZY!! --------------------

int alarm_id;

void
attack_balrog(object balrog)
{
    mixed res;
    tell_room(ENV(wielder),
	      "Durin's Axe flashes through the room hurling towards the Balrog!!!\n");

    res = balrog->hit_me(3*WC_PEN, W_SLASH, TO, -1);

    produce_message(balrog, balrog, res[0], ({
        "&It rushes against #n's &body, but misses!",
	"&It strikes #n in #his &body, but bounces off!",
	"&It slashes #n's &body, rather weakly however.",
	"&It leaps into the &body of #n, slicing #him neatly!",
	"In awesome speed, the waraxe slices deeply into #n's &body!!",
	"You watch Durin's Axe penetrating deeply into the Demon's &body!!",
	"In anger and anguish, the dwarven rage in the form of Durin's Axe avenges " 
	   + "the deeds of the past! It hurls deeply into #n's &body! Black blood "
	   + "streams out of the wound, and the balrog screams terribly!!!",
    }), ([ "&body": res[1], "&It" : "The dwarven waraxe" ]));
    if (HP(balrog) <= 0)
    {
   balrog->command("emote curses you in the name of Melkor the Great.");
	balrog->do_die(TO);
	remove_alarm(alarm_id);
    }
}

void
go_crazy(object balrog)
{
    tell_room(ENV(wielder), 
	      "The dwarven waraxe explodes in many colours!!\n" +
	      "The dwarven waraxe flies out of " + QTNAME(wielder) +
	      "'s hands and attacks " + QTNAME(balrog) + "!!!!\n");
    move(ENV(wielder));
    add_prop(OBJ_I_NO_GET, "You can't get it, when it is flying through the air!\n");
    alarm_id = set_alarm(0.0, 1.0, "attack_balrog", balrog);
}

init()
{
    ::init();
    /* Feelings using this axe. */
    if(!query_usable(TP))
	return;

    add_action("do_swing", "swing");
    add_action("do_kiss",  "kiss");
    add_action("do_praise",  "praise");

//    add_action("do_throw", "throw");
//    add_action("do_throw", "hurl");
}

int
do_swing(string s)
{
    if(!s || !id(s))
	return 0;
    TellRoom(TP, 0,
	"$N $swing $p mighty dwarfaxe in the air!\n"+
	"{You feel the powers of Durin's Axe lift you to new heights of power.;"+
	";You tremble of the sight of this. What a mighty waraxe!}\n");
    return 1;
}

int
do_kiss(string s)
{
    if(!s || !id(s))
	return 0;
    TellRoom(TP, 0,
	"$N $kneel, gracefully kissing $p mighty dwarven waraxe.\n");
    return 1;
}

int
do_praise(string s)
{
    if(!s || !id(s))
	return 0;
    TellRoom(TP, 0,
	"$N $praise $p dwarven waraxe, the Great dwarves, the Khazad, "+
	"and the Father of the Khazad, Durin, and the smiths which made the "+
	"great dwarven artifact.\n");
    return 1;
}
