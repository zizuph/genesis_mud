// file name:        /d/Avenir/common/dark/mon/ogre_base.c
// creator(s):       Denis, based on Lilith's and Cirion's code.
// revision history:
//   Lilith, Jan'98 - Added gem to inventory.
//   Lilith, Mar'02 - Added leadership qualities for raiding.
//   Denis,  Feb'03 - Made one base file for the ogre base and two ogres
//                    (ogre.c and ogre_raider.c) inheriting it, as the two
//                    had 95% of the code the same.
//   Lucius, May'07 - Modified the guild code, changed "Kaheda" to "Monk"
//                    and removed the Druid and Angmar checks since both
//                    are long, long gone.
//   Lilith, Aug 14   Bumped up the largest ogres to provide more challenge
//                    Since the average player is much larger these days
//                    Removed the annoying run_away function. Players hate
//                    hunting ogres because of it.
//   Lilith, Oct 14   Added some magic resistance to the larger ogres.
//   Lilith, Feb 15   Updated cloning to be uniform across sizes/types
//                    Reduced exp modifier from 150 to 120
//   Lilith, Feb 15   Reduced exp modifier to 0, updated skills base to 40
//                    (max 90). Setting intox to max during combat.
//   Lucius, Jun 16   Removed mana drain.
//   Zizuph, Jun 21   Added unarmed, standardized NPC special and
//                    returned many white hits back.  Dropped exp penalty.
//
// purpose:
//   Is a base for  ogre.c and ogre_raider.c
//   ogre.c would be your basic ogre, while
//   ogre_raider.c would be the leader of the Shadow Union uninvited party.
//
//   Random Ogre for the L5 Utterdark Tunnels. They are pretty clever, they
//   follow, wimpy, try to use the best weapon, search for hidden players,
//   etc.
// note:
// bug(s):
// to-do:
//   Do something about the players' guild determination code. Maybe
//   generalize it?

#pragma strict_types
#pragma no_clone

#include <formulas.h>
#include <money.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/relation.h"

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/insult";
inherit "/d/Avenir/inherit/wsmap";

object weap;
int armnum, break_alarm;

// Define the different mob types
#define MOB_0     0
#define MOB_1     1
#define MOB_2     2
#define MOB_3     3
#define MOB_4     4
#define MOB_5     5

// Global Variables
public int      Strength = 0;
public string   mob_desc;

/*
 * Function:    set_mob_strength
 * Description: Called inside setup_random_mob, it indicates
 *              which monster type this is.
 */
public void
set_mob_strength(int strength)
{
    Strength = strength;
}

/*
 * Function:    get_mob_strength
 * Description: Returns the value set during the random generation.
 */
public int
get_mob_strength()
{
    return Strength;
}

/*
 * Function:    setup_random_mob
 * Description: Randomly select a type of mob to generate.
 *              They range from 50-300 stat at intervals of 50
 *              Adjective desc helps mortals figure out at a
 *				glance what size their opponents are.
 */
public void
setup_random_mob()
{
    int base_stat, mob_type;
    string short_desc;

    /* The random generation type will take all the existing types
     * and try to do an equal distribution.
	 */
    object * instances = object_clones(find_object(MASTER));
    if (!sizeof(instances))
    {
        mob_type = random(6);
    }
    else
    {
        int * counts = ({ 0, 0, 0, 0, 0, 0 });
        foreach (object instance : instances)
        {
            int strength = instance->get_mob_strength();
            ++counts[strength];
        }
        int mincount = applyv(min, counts);
        mob_type = max(0, member_array(mincount, counts));
    }
    // Set the strength so that it can be looked up later.
    set_mob_strength(mob_type);

    switch (mob_type)
    {
		case MOB_0:
			add_adj(({"young", "petty"}));
			mob_desc = "It is a rather small ogre. He doesn't " +
		        "look very friendly, though.\n";
			armnum = 1;
			break;

		case MOB_1:
			add_adj(({"hairy", "cruel"}));
			mob_desc ="Ugly, smelly and hostile, this ogre is "+
				"near the bottom of the pecking order.\n";
			armnum = 2;
			break;

		case MOB_2:
			add_adj(({"awful", "red-eyed"}));
			mob_desc ="This awful, red-eyed ogre is of medium stature. "+
			    "He towers over you and stares with menacing eyes.\n";
			armnum = 3;
			break;

		case MOB_3:
			add_adj(({"terrible", "massive"}));
			mob_desc ="Terrible and massive, he is average-sized for an ogre, "+
					 "and the way he's looking at you, you get the "+
					 "distinct feeling he's hungry enough to eat you, alive.\n";
			armnum = 4;
            break;

		case MOB_4:
			add_adj(({"titanic", "horrifying"}));
			mob_desc ="A titanic, horrifyingly huge creature, he rises before you, "+
			    "savage and brutal. To think he does not look overly pleased "+
			    "to see you would be an understatement.\n";
			armnum = 5;
			break;

		case MOB_5:
			add_adj(({"monstrous", "unearthly"}));
			mob_desc ="This monstrous creature is so massive that he dwarfs "+
				"everything around him. He stands before you like " +
				"a terrible nightmare, looking as though he could snap " +
				"you like a twig.\n";
			armnum = 6;
			break;

    }

    // Set up the actual stats
    base_stat = 30 + (mob_type * 50) + random(20);
    default_config_npc(base_stat);

    short_desc = implode(query_adjs(), " ") + " ogre";
    set_short(short_desc);
    set_name(short_desc);
}

string *sounds = ({ "moans", "screams", "snarls", "cries", "grates" });

void
config_ogre(void)
{
    string str1, str2, str3, adj;

    setuid();
    seteuid(getuid());

	setup_random_mob();
	set_attack_chance(10); /* usually 15% but caves can be a death trap */

    set_name("ogre");
    set_race_name("ogre");

	set_long(mob_desc +" He looks to you like he is a "+query_exp_title() +".\n");
	// Set up base ac for npc according to mob size
	set_all_hitloc_unarmed(Strength * 12); // native ac runs 0-60, plus armour.

	// Skills based on type of mob
	int skill_mod = Strength * 10;
    set_skill(SS_PARRY,		  40 + skill_mod);
    set_skill(SS_DEFENCE,	  40 + skill_mod);
    set_skill(SS_WEP_SWORD,	  40 + skill_mod);
	set_skill(SS_WEP_CLUB,	  40 + skill_mod);
	set_skill(SS_WEP_AXE,	  40 + skill_mod);
    set_skill(SS_WEP_POLEARM, 40 + skill_mod);
    set_skill(SS_WEP_KNIFE,	  40 + skill_mod);
    set_skill(SS_2H_COMBAT,	  40 + skill_mod);
    set_skill(SS_AWARENESS,	  40 + skill_mod);
    set_skill(SS_UNARM_COMBAT,	  40 + skill_mod);
    set_skill(SS_SPELLCRAFT,  60);

	// Set up magic resistance based on mob size
	// magic users are scything through them
	int resistance = Strength + 5;
	add_prop(OBJ_I_RES_ACID, resistance);
    add_prop(OBJ_I_RES_AIR, resistance);
    add_prop(OBJ_I_RES_COLD, resistance);
    add_prop(OBJ_I_RES_DEATH, resistance);
    add_prop(OBJ_I_RES_EARTH, resistance);
    add_prop(OBJ_I_RES_ELECTRICITY, resistance);
    add_prop(OBJ_I_RES_FIRE, resistance);
    add_prop(OBJ_I_RES_ILLUSION, resistance);
    add_prop(OBJ_I_RES_LIFE, resistance);
    add_prop(OBJ_I_RES_LIGHT, resistance);
    add_prop(OBJ_I_RES_MAGIC, resistance);
    add_prop(OBJ_I_RES_POISON, resistance);
    add_prop(OBJ_I_RES_WATER, resistance);

	add_prop(LIVE_I_SEE_DARK, 2 + Strength);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, random(300));

	// set height and weight to align with size and descs
	add_prop(CONT_I_HEIGHT, TO->query_average_stat() * 200);
	add_prop(CONT_I_WEIGHT, TO->query_average_stat() * 125);


    set_act_time(5 + random(20));
    if (random(2))
	add_act("say Get lost, you@@insult@@.");
    if (random(2))
	add_act("poke @@anum@@ ogre in the eye");
    if (random(2))
	add_act("kick @@anum@@ ogre");
    add_act("snarl @@anum@@ ogre");
    add_act("say Hey@@insult@@! Beat it!");
    // add_act("@@break_gate@@");

    set_cact_time(10 + random(10));
    add_cact("shout I'm going to kill this@@insult@@!");
    add_cact("say Die you@@insult@@!");
    add_cact("shout Looky here! Some@@insult@@ wants to kill me! HAHAHAHA!");
    add_cact("say We'll have you for dinner tonight!");
    add_cact("@@threat@@");

    set_restrain_path(L5);
    set_helper_friends ( ({"ogre"}) );

    str1 = ONEOF(({"shout Hey! Some" + insult() + " is trying to kill me!",
	"shout Hah! This" + insult() + " thinks it can fight!",
	"shout Help! Help!", "shout Come and assist me you idiots!",
	"shout Where the hell are you guys? Some" + insult() + " wants " +
	"me to kill it!", "shout Dinner is served!!"}));

    str2 = ONEOF(({"shout I Coming!", "shout Wait, I want to kill it too!",
	"shout What's that? Dinner already?!?", "shout I'll " +
	"come and crush the" + insult() + "!", "", "" }));


    str3 = ONEOF(({"say Ahh ... it does look tasty!", "say Why, is this " +
	"little" + insult() + " causing you problems? HAHAHAHAHA!",
	"say C'mere you little rat! I'll eat you!",
	"say You're dead now!", "", ""}));

    set_helper_actions(({ str1, str2, str3 }));

    set_pick_up(1);
    KILL_THIEF;
    MAKE_INFIDEL;
    set_alignment(0);

    refresh_living();
}

/* Don't follow if we are too hurt */
int mtrig_follow(string s1, string s2)
{
    if (query_hp() < query_max_hp() / 50)
	return 0;

    return ::mtrig_follow(s1, s2);
}

string anum()
{
    return LANG_WORD(random(5) + 1);
}

string threat()
{
    object ob = query_attack();

    if (!ob || !present(ob, ENV(TO)) ||
	!CAN_SEE(TO, ob) || !CAN_SEE_IN_ROOM(TO))
	return "";

    set_follow(ob->query_real_name());

    command("point " + ob->query_real_name());
    return "say I am going to hunt you until you are dead " +
    ob->query_race_name() + "!";
}

void equip_armour(string armour_file)
{
    object arm;

    arm = clone_object(armour_file);
    arm->move(this_object());
    arm->configure_me(armnum - random(2));
    arm->wear_me();
}

void equip_me()
{
    object arm, gem, old_this_player;
    int    coins;

    seteuid(getuid());
    old_this_player = this_player();
    set_this_player(this_object());

    gem = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
    gem->move(this_object());

    coins = random(query_stat(SS_CON));
    if (coins)
	MONEY_MAKE_CC(coins)->move(TO);
    coins = random(query_stat(SS_CON) - 60);
    if (coins)
	MONEY_MAKE_SC(coins)->move(TO);

    switch (random(6))
    {
    case 0:
	weap = clone_object( OBJ + "osword");
	break;
    case 1:
	weap = clone_object( OBJ + "oknife");
	break;
    case 2:
	weap = clone_object( OBJ + "oclub");
	break;
    case 3:
	weap = clone_object( OBJ + "oaxe");
	break;
    default:
	weap = clone_object( OBJ + "opole");
	break;
    }

    weap->move(this_object());
    weap->configure_me(armnum);
    weap->wield_me();

    if (random(armnum))
	equip_armour(OBJ + "ochain");

    if (random(armnum) && !query_weapon(W_BOTH))
	equip_armour(OBJ + "oshield");

    if (random(armnum))
	equip_armour(OBJ + "obracers");

    if (!random(5))
	clone_object(OBJ + "bones")->move(this_object());

    if (armnum >= 4)
    {
	gem = RANDOM_GEM(GEM_EXTREMELY_RARE);
	gem->move(this_object());
    }

    set_this_player(old_this_player);
}

public string race_sound()
{
    return sounds[random(sizeof(sounds))];
}


/*
 * Function name: aggressive_attack
 * Description:   We are aggressive, let us attack
 * Arguments:     ob - the object to attack
 */
public void
aggressive_attack(object ob)
{
    if (!present(ob, environment(this_object())) || !interactive(ob) ||
	!CAN_SEE(TO, ob) || query_attack())
	return;

    set_alarm(itof(random(8)), 0.0, &command("kill " + OB_NAME(ob)));
}

void notify_you_killed_me(object ob)
{
    set_alarm(1.0 + itof(random(10)), 0.0, &command("get all from corpse"));
    set_alarm(1.0 + itof(random(5)), 0.0, &command("shout Ha! I killed that" +
	insult() + "!!"));
}

/* Lets not get too loaded down */
void get_all()
{
    if (query_encumberance_weight() > 60)
	return;

    if (present("corpse", ENV(TO)))
	command("get all from corpse");
    else
	command("get all");
}

public void run_away()
{

    string cmd = ONEOF(({"say Ahh! This" + insult() + " is going to kill me!",
	"scream", "panic", "cringe", "shout Help me! Help me!",
	"", "say No! Death!"}));

    command(cmd);
   // These guys are running amok. Lets stop it.
   // ::run_away();

}

/*
 * If we pick up food, eat it. If we pick up alco, drink it.
 */
void enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (function_exists("create_food", to))
    {
	set_alarm(1.0, 0.0, &command("eat all"));
	if (!random(10))
	    set_alarm(1.2, 0.0, &command("burp"));
    }

    if (function_exists("create_drink", to))
    {
	set_alarm(1.0, 0.0, &command("drink all"));
	if (!random(10))
	    set_alarm(1.2, 0.0, &command("hiccup"));
    }

    if (query_attack() || (query_encumberance_weight() < 90 &&
	query_encumberance_volume() < 90))
	return;

}

void enter_env(object to, object from)
{
    ::enter_env(to, from);
    set_alarm(1.0 + itof(random(20)), 0.0, get_all);
}

/*
 * Curse at the enemy based on what he does for  a living
 */
string react_enemy()
{
    object *enemies, enemy, thing;
    int     stat;
    string  nm, occ, lay, ostyle, lstyle, rn, his, boy, vb, oname, lname, str;

    enemies = query_enemy(-1);
    if (!sizeof(enemies))
	return "";

    enemy = enemies[random(sizeof(enemies))];

    stat = enemy->query_average_stat();
    nm = enemy->query_name();
    occ = enemy->query_guild_name_occ();
    lay = enemy->query_guild_name_lay();
    ostyle = enemy->query_guild_style_occ();
    lstyle = enemy->query_guild_style_lay();
    oname = enemy->query_guild_name_occ();
    lname = enemy->query_guild_name_lay();
    rn = enemy->query_race_name();
    his = enemy->query_possessive();
    boy = (enemy->query_gender() == G_FEMALE ? "girl" : "boy");
    vb = (random(2) ? "say " : "shout ");

    if (!interactive(enemy))
	return "";

    if (!enemy || !CAN_SEE(TO, enemy) || !CAN_SEE_IN_ROOM(TO))
	return vb + "Where did it go?";

    if (enemy->query_wiz_level()) /* Wizards */
	return "say Hey! Stupid wizards always killing things! " +
	"Bad Wizard! Baaaaaaad Wizard!!!!";

    if (random(2) && stat > 150) /* Superchamps */
    {
	switch (random(5))
	{
	case 0..2:
	    command("cry");
	    return "say Why don't you just clear out of here?";
	case 3:
	    command("spit " + enemy->query_real_name());
	    return "say I bet you think you are tough, eh " + nm +
	    "? I'll tear you apart just like the others!";
	default:
	    return vb + "Hey you big bully! Why don't you pick on " +
	    "someone your own size?";
	}
	return "";
    }

    if (!random(3))
	command("kill " + enemy->query_real_name());

    /* Magic Users */
    if (random(2) && (ostyle == "magic" || lstyle == "magic"))
	return vb + "Lookey! I'm a magician just like this little " +
	rn + " rat! Watch, I'll pull " + his + " heart out of my " +
	"helmet!!";

    /* Clerics */
    if (random(2) && (ostyle == "cleric" || lstyle == "cleric"))
	return vb + "Hey pious little " + rn + "! Better get praying " +
	"to your gods if you want to live!";

    /* Undeads */
    if (random(2) && enemy->query_prop(LIVE_I_UNDEAD))
	return vb + "Hey! This " + rn + " smells like " +
	enemy->query_pronoun() + " is already dead! What, did you " +
	"forget where your coffin was, smelly " + boy + "? HAHAHAHAHA!";

    /* Rangers / Druids */
//    if (!random(2) && strlen(oname) && (sscanf(oname, "%sRanger%s", str, str) ||
//	sscanf(oname, "%sDruid%s", str, str)))
    if (!random(2) && strlen(oname) && (sscanf(oname, "%sRanger%s", str, str)))
	return vb + "Hey nature " + boy + "! Yeah you, " + rn + "! " +
	"Come here and I'll show you " +
	"the nature of " + (weap->query_wielded() == TO ?
	  "my " + weap->short(TO) : "death") + "!";

    /* Knights */
    if (!random(2) && strlen(oname) && sscanf(oname, "%sKnight%s", str, str))
	return vb + "Oh no! A little knight " + boy + "! I'm " +
	"SOOOOO scared!";

    /* Gladiators */
    if (!random(2) && strlen(oname) && sscanf(oname, "%sGladiator%s", str, str))
	return vb + "Hey little gladiator " + boy + ", I thought you " +
	"were all still slaves? Why don't you get back to " +
	"your master? HAHA!";

    /* Monks */
    if (!random(2) && strlen(oname) && sscanf(oname, "%sMonk%s", str, str))
	return vb + "Ouch! When I get a hold of your solar plexus, " +
	"I'm gonna eat it, little monk!";

    /* Angmars */

    if (!random(2) && strlen(oname) && sscanf(oname, "%sAngmar%s", str, str))
	return vb + "If you smash me, I'll smash you back " +
	"little " + rn + " " + boy + "!";

	/* Minstrils */
    if (!random(2) && strlen(lname) && sscanf(lname, "%sMinstril%s", str, str))
    {
	thing = present("trumpet", enemy);
	if (!thing) thing = present("harp", enemy);
	if (!thing) thing = present("violin", enemy);
	if (!thing) thing = present("flute", enemy);
	if (!thing) thing = present("lute", enemy);
	if (!thing) return "";

	return vb + "Hey music " + boy + "! I'm gonna make you eat that " +
	thing->short(TO) + "!";
    }

    return "";
}

/*
 * They don't like smiles too much.
 */
int react_smile(string str)
{
    string  str1;

    if (!interactive(TP) || random(3))
	return 0;

    switch (QVB)
    {
    case "smile":   str1 = "smiling"; break;
    case "grin":    str1 = "grinning"; break;
    case "dance":   str1 = "dancing"; break;
    case "giggle":  str1 = "giggling"; break;
    case "smirk":   str1 = "smirking"; break;
    default:        str1 = "laughing"; break;
    }

    switch (random(5))
    {
    case 0: str = "You won't be " + str1 + " after I rip your " +
	"ears off " + TP->query_race_name() + "!";
	break;
    case 1: str = "Stop " + str1 + " you little worm! I'll have " +
	"you for dinner!";
	break;
    case 2: str = "Yeah, keep " + str1 + " little maggot. I'll wipe " +
	"that smile off your face with my " +
	(weap->query_wielded() == TO ? weap->query_name() :
	  "bare fist") + "!";
	break;
    case 3: str = "I hate" + insult() + " when they " + QVB + "! I'll " +
	"tear this one apart!";
	break;
    default: str = CAP(str1) + " little " +
	(TP->query_gender() == G_FEMALE ? "girl" : "boy") +
	", come here and I'll tear that cute little head off!";
	break;
    }

    set_alarm(0.5 + itof(random(7)), 0.0, &command((random(2) ? "say " : "shout ") + str));
    return 0;
}

int iswep(object ob)
{
    if (ob->query_dt())
	return 1;
    return 0;
}

/*
 * Logically, if  we have a better weapon in our possession than the
 * one we are using, switch  to that weapon.
 */
void check_weapons()
{
    object *inv = filter(all_inventory(TO), iswep) - ({ weap }),
    good_weap;
    int     i;

    if (!sizeof(inv))
	return;

    if (present(weap))
	good_weap = weap;

    /* Run through and find the best weapon, except those with
     * wield functions - we wouldn't want them wielding magic
     * weapons that would kill them!
     */
    for (i=0;i<sizeof(inv);i++)
    {
	if ((inv[i]->query_hit() > good_weap->query_hit() &&
		inv[i]->query_pen() >= good_weap->query_pen()) &&
	    !inv[i]->query_wf())
	    good_weap = inv[i];
    }

    if (weap && good_weap != weap)
    {
	command("say Hey! This " + good_weap->query_name() + " is much " +
	  "better than my " +
	  (good_weap->query_name() == weap->query_name() ?
	    "lousy one" : "stupid " + weap->query_name()) + "!");
	command("unwield all");
	if (good_weap->query_hands() == W_BOTH)
	    command("remove shields");
	good_weap->add_name("ogre_good_weap");
	command("wield ogre_good_weap");
	weap = good_weap;
	good_weap->remove_name("ogre_good_weap");
    }
    else
    {
	command("wield all");
	command("wear all");
    }
}

/*
 * They are very frightened of magic --Not Anymore: Lilith Oct 2014

public mixed hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    if (dt == MAGIC_DT && attack_id == -1 && !random(5))
    {
	set_alarm(0.2, 0.0, &command("say Ahhhh! Magic! They are " +
	    "trying to fry me!"));
//	set_alarm(0.8, 0.0, &add_panic(300));
    }

//    if (dt == MAGIC_DT)
//	add_panic(random(200));

    return ::hit_me(wcpen, dt, attacker, attack_id);
}
*/

void check_light()
{
    if (!CAN_SEE_IN_ROOM(TO) && !present("torch", TO))
    {
	seteuid(getuid());
	command("say Hey! Who turned out the lights?");
	clone_object("/std/torch")->move(TO, 1);
	command("light torch");
    }
}

/*
 * Use our weapon in out own special attack.
 */
int special_attack(object enemy)
{
    mixed   *hitres, *dbits;
    int      pen, phurt, dt, hurt;
    string  *how, act1, act2, hitloc, str;
    object   who;

	/* Let's keep them intoxicated for healing, just like players. */
	TO->set_intoxicated(500);

    if (!random(3) && !CAN_SEE_IN_ROOM(TO))
    {
	    check_light();
	    return 0;
    }

    if (!random(4) && query_prop(LIVE_I_SEE_INVIS) < 0)
    {
	command("say " + (random(2) ? "Ahhh! My eyes!" : "I'll get whoever " +
	    "just blinded me!"));
	add_panic(30);
	return 0;
    }

    if (!random(5) && enemy->query_prop(OBJ_I_INVIS))
    {
	command("shout Ahhh! Ghosts are killing me!");
	return 0;
    }


    if (!random(5) && enemy->query_prop(OBJ_I_HIDE) && CAN_SEE(TO, enemy))
    {
	command("say Hey! Think you can sneak around here, little " +
	  "worm? HAH!");
	command("poke " + enemy->query_real_name());
	return 0;
    }

    if (!random(6) && weap && (who = ENV(weap)) != TO && interactive(who))
    {
	command("shout Damn! Some wretched little " + who->query_race_name() +
	  " stole my " + weap->query_name() + "!");
	command("get weapon");
	command("wield all");
	return 0;
    }

    if (!random(5))
	    check_weapons();

    if (!random(6))
	    get_all();

    if (!random(10))
    {
        command(react_enemy());
        return 0;
    }

    if (random(3) || !CAN_SEE(TO, enemy))
	    return 0;       // Attack as normal

    if (!objectp(weap) || weap->query_wielded() != TO)
    {
	    weap = query_weapon(W_LEFT);
	    if (!weap) weap = query_weapon(W_RIGHT);
	    if (!weap) weap = query_weapon(W_BOTH);
    }

    if (!objectp(weap) || weap->query_wielded() != TO)
	    return 0; // Needs to be wielding his weapon for  this to work!


    /* The enemy may have been able to evade the attack. */
    if (enemy->query_not_attack_me(TO, -1))
    {
        return 1;
    }    

    dt = weap->query_dt();

    /* Pick one damage type, if , say, out sword has dt W_IMPALE | W_SLASH */
    dbits = ({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON }) - ({ 0 });
    dt = dbits[random(sizeof(dbits))];

    switch (dt)
    {
    case W_BLUDGEON:
	act1 = " swings his " + weap->short(TO) + " with all his might at ";
	act2 = "";
	how = ({ "just misses", "lightly taps", "bumps", "pounds", "bludgeons",
	  "smashes", "crushes" });
	break;
    case W_IMPALE:
	act1 = " stabs at ";
	act2 = " with his " + weap->short(TO);
	how = ({ "barely misses", "gently pokes into", "nicks", "jabs", "cuts", "pierces",
	  "impales" });
	break;
    default:
	act1 = " swings his " + weap->short(TO) + " at ";
	act2 = " with tremendous strength";
	how = ({ "just misses", "nicks", "slices into", "cuts deeply into", "slashes", "rips apart",
	  "nearly severs" });
	break;
    }

    // 66% chance of hit from cb_tohit table, roughly double the normal swings.
    if (query_combat_object()->cb_tohit(-1, 70, enemy) > 0)
	{
	
	  pen = F_PENMOD(weap->query_pen(), query_skill(weap->query_wt()))
    	  * F_STR_FACTOR(TO->query_average_stat()) / 100;
	}
	else
	{
	  // They missed.
	  pen = 0;
	}
    hitres = (mixed *)enemy->hit_me(pen, dt, TO, -1);
    phurt = (int)hitres[0];

    /* Lets make the hitlocs look a bit prettier and more descriptive */
    hitloc = (string)hitres[1];
    if (hitloc == "legs") // Get rid of the silly plurals
	hitloc = (random(2) ? "right" : "left") + " leg";

    if (hitloc == "head" && !random(5))
	hitloc = (random(2) ? "spine" : "neck");
    else if (strlen(hitloc) && sscanf(hitloc, "%s arm", str) && random(2))
	hitloc = (random(2) ? "lower " + hitloc : str + " shoulder");
    else if (strlen(hitloc) && sscanf(hitloc, "%s leg", str) && random(2))
	hitloc = (random(2) ? "lower " + hitloc : str + " thigh");
    else if (hitloc == "body" && random(2))
	hitloc = (random(2) ? "chest" : "stomach");

    /*
     * Now we have a choice from 18 humanoid hitlocs, instead of
     * the usual 5: right leg, left leg, lower left leg, lower right leg,
     * left thigh, right thigh, head, spine, neck, left arm,
     * right arm, lower right arm, lower left arm, left shoulder,
     * right shoulder, body, chest, and stomach.
     * Neat, huh?
     */

    switch (phurt)
    {
    case -1000 .. -1:  hurt = 0; break;
    case 0 .. 2:       hurt = 1; break;
    case 3 .. 7:       hurt = 2; break;
    case 8 .. 15:      hurt = 3; break;
    case 16 .. 40:     hurt = 4; break;
    default:           hurt = 5; break;
    }

    tell_watcher(QCTNAME(TO) + act1 + QTNAME(enemy) + act2 + " and " +
      how[hurt] + " " + POSSESS(enemy) + " " + hitloc + ".\n", enemy);
    enemy->catch_msg(QCTNAME(TO) + act1 + "you" + act2 + " and " + how[hurt] +
      " your " + hitloc + ".\n");
    if (!enemy->query_hp())
    {
	enemy->do_die(TO);
	set_alarm(0.2, 0.0, &command("shout HAHA! Come back real soon, " +
	    enemy->query_race_name() + "!"));
    }
    return 1;
}

/*
 * The prestige reward for  Knights of Solamnia, per info in ~Krynn/info/EXPORT/PRESTIGE
 */
int query_knight_prestige()
{
    int stat = query_average_stat();
    return stat * stat / 15;
}

string stat_living()
{
    string   str = ::stat_living();

    str += "Knight Prestige: " + query_knight_prestige() + "\n";
    return str;
}

string
break_gate()
{
    break_alarm = 0;

    if (!random(3))
	return "";

    command("wield all");
    if (command("break gate with wielded weapon"))
    {
	float delay = itof(30 + random(91));
	break_alarm = set_alarm(delay, 0.0, break_gate);
    }

    return "";
}
