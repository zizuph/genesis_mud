/*
 * Dragonarmy monster base file
 * Coded by Milan
 *
 * Usage:

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";

// mask function create_da_monster()
void
create_da_monster()
{
    // if set_color() is not called, color is random
    set_color("color_i_want_to_have");

    // if set_dragonarmy_rank() is not called, rank and subrank is random
    set_dragonarmy_rank();

    //clone, wield and wear armours and weapons
}

 */

#pragma save_binary
#pragma strict_types

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <std.h>
#include <math.h>
#include <macros.h>
#include <ss_types.h>
#include <login.h>

#define ARM_DIR ACOMMON_DIR + "arm/"
#define WEP_DIR ACOMMON_DIR + "wep/"

inherit AM_FILE

#include "/d/Ansalon/common/hunt.c"

object gShadow, uniform;
string gSoul = "";
int is_old = 0;
int race_set = 0;

/* prototypes */
void set_color(string str);
varargs void set_dragonarmy_rank(int rank, int subrank = -1, int no_stats = 0);

#define RA (a[random(sizeof(a))])
#define RB (b[random(sizeof(b))])

void
set_random_name()
{
    string *a = ({ "a","e","y","u","i","o","io","au","ie","ra","re" });
    string *b = ({ "q","w","r","t","p","s","d","f","g","h","j","k","l","z",
      "x","c","v","b","n","m","ll" });
    string name = "";

    if (random(3))
	name += RB;
    name += RA + RB + RA;

    if (random(3))
    {
	name += RB;
	if (random(2))
	{
	    name += RA;
	    if (random(2))
		name += RB;
	}
    }
    while (SECURITY->exist_player(name) ||
      SECURITY->query_banished(name) ||
      find_living(name))
    {
	if (random(2))
	    name += RA;
	else
	    name += RB;
    }

    this_object()->set_name(name);
    this_object()->set_living_name(name);
}

void
set_race_name(string race)
{
    int h, w;

    ::set_race_name(race);
    if (query_prop(CONT_I_WEIGHT) == 70000 &&
      query_prop(CONT_I_HEIGHT) == 160 &&
      member_array(race, RACES) >= 0)
    {
	h = RACEATTR[race][0];
	h = (h * (80+random(40))) / 100;
	w = RACEATTR[race][5];
	w = (w * (80+random(40))) / 100;
	add_prop(CONT_I_HEIGHT, h);
	add_prop(CONT_I_WEIGHT, w*h);
	add_prop(CONT_I_VOLUME, w*h);
    }
    race_set = 1;
}

void
fix_da_stuff()
{
    int r;
    mixed *categories;
    string *list, cat;

    if (!race_set)
	set_race_name("human");

    if (!query_scar())
	set_scar(random(2048));

    if (!sizeof(query_adjs()))
    {
	categories = get_dir(ATTRIBS);
	for(r=0; r<2; r++)
	{
	    cat = categories[random(sizeof(categories))];
	    list = explode(read_file(ATTRIBS + cat), "\n");
	    add_adj(list[random(sizeof(list))]);
	    categories -= ({ cat });
	}
    }
}

void
set_old()
{
    is_old = 1;
    fix_da_stuff();
}

public void
create_da_monster()
{
}

public nomask void
create_krynn_monster()
{
    setuid();
    seteuid(getuid());

    set_alarm(1.0, 0.0, set_old);

    create_da_monster();

    uniform = clone_object(DRAGONARMY_OBJ + "uniform");
    uniform->move(TO,1);
    uniform->set_color(gColor);
    uniform->set_dalevel(TO->query_dragonarmy_promotions());
    uniform->set_condition(random(5));
    uniform->set_repair(random(2));
    command("wear all");
}

/*
 * Function name: set_color         (also set_colour)
 * Arguments:     string str  - color to set (only one of dragonarmy colors accepted)
 * Description:   This function add dragonarmy shadow and soul (NPC is real member)
 *                It also colors all inventory to the same color as set.
 */
varargs void
set_color(string str = "")
{
    int rank = 0;

    if (member_array(str, DA_COLORS) == -1)
	str = DA_COLORS[random(5)];

    gColor = str;

    /* First we remove any old shadow used */
    if(objectp(gShadow))
    {
	rank = gShadow->query_dragonarmy_promotions();
	gShadow->remove_da_shadow();
    }
    /* Now we add desired shadow */
    gShadow = clone_object(DRAGONARMY_DIR+"shadow/dragonarmy_"+str+"_sh");
    if(gShadow->shadow_me(TO, "occupational", GUILD_STYLE, GUILD_NAME) != 1)
    {
	"secure/master"->do_debug("destroy",gShadow);
    }
    else
    {
	gShadow->set_promotion_level(rank);
    }

    /* We add also soul and initialize commands */
    remove_cmdsoul(gSoul);
    gSoul = DRAGONARMY_SOUL+"dragonarmy_"+str+"_soul";
    add_cmdsoul(gSoul);
    load_command_souls();

    /* Finaly color all inventory also */
    all_inventory()->set_color(gColor);
    all_inventory()->set_colour(gColor);
}

void set_colour(string str = "") { set_color(str); }
string query_color() { return gColor; }
string query_colour() { return gColor; }

/*
 * Function name: set_dragonarmy_rank
 * Arguments:     int rank     - dragonarmy rank (values 0..4 accepted)
 *                int subrank  - dragonarmy subrank, if negative random(6) is used
 *		                 default == -1
 *		  int no_stats - if nonzero stats and skills are not set
 *		                 defaut == 0
 * Description:   This function sets dragonarmy rank. If (no_stat == 0) then also skills
 *                are set according to required rank and subrank and also skills are set
 *		  to trainable level.
 *		  !!! This function should be called AFTER set_color() !!!
 */
varargs void
set_dragonarmy_rank(int rank = -1, int subrank = -1, int no_stats = 0)
{
    int *skills,i,min,ran,occ,s = 0;

    if (rank == -1)
    {
	if (!random(4))
	{
	    rank = (random(3) ? 2 : 3);
	}
	else
	{
	    rank = (random(3) ? 1 : 0);
	}
    }

    TO->set_promotion_level(rank);
    if (objectp(uniform))
	uniform->set_dalevel(TO->query_dragonarmy_promotions());

    switch(rank)
    {
    case 1:
	set_knight_prestige(700);
	set_alignment(-700);
	break;
    case 2:
	set_knight_prestige(900);
	set_alignment(-900);
	break;
    case 3:
	set_knight_prestige(1000);
	set_alignment(-1000);
	break;
    case 4:
	set_knight_prestige(1200);
	set_alignment(-1200);
	break;
    default:
	set_knight_prestige(400);
	set_alignment(-400);
    }

    if(no_stats)
	return;

    /* Now se set the stats so that desired subrank is achieved */
    rank = TO->query_dragonarmy_promotions();
    if(subrank < 0)
	subrank = random(6);

    switch(rank)
    {
    case 4:
	s += 4;
    case 3:
	s += 6;
    case 2:
	s += 5;
    case 1:
	s += 7;
    default:
	s += subrank;
    }
    s *= 960;
    occ = (SQUARE_ROOT(s + 960) * 9) / 10;
    min = MAX(occ, s / occ);
    ran = ((s + 960) / occ) - min;

    set_base_stat(SS_OCCUP, occ);
    for (i = 0; i < 6; i++)
	set_base_stat(i, min + random(ran));

    stats_to_acc_exp();

    /* Refresh HP and mana to full value */
    heal_hp(query_max_hp());
    add_mana(query_max_mana());

    /* Finally set up trainable skills to apropriate levels */
    occ = 20 + ((13 * occ) / 10);
    set_skill(SS_AWARENESS,    occ);
    set_skill(SS_BLIND_COMBAT, occ);
    skills = (TO->query_guild_trainer_occ())->sk_query_train();
    for (i = 0 ; i < sizeof(skills); i++)
	set_skill(skills[i], occ);
}

void
cut_special_skill()
{
    if (query_skill(SS_DRAGONARMY_ATTACK) > 100)
	set_skill(SS_DRAGONARMY_ATTACK, 100);
}

/*
 * Function name: special_attack
 * Arguments:     object ob - Object we are going to hit
 * Description:   With this our NPC will use guild special attack
 */
int
special_attack(object ob)
{
    if(gSoul != "" && !query_prop("_dragonarmy_dattack_prop"))
    {
	switch(gColor)
	{
	case "red":
	    command("impale");
	    break;
	case "blue":
	    command("slash");
	    break;
	default:
	    command("slash");
	}
    }

    if (gSoul != "" && TO->query_dragonarmy_promotions() > 1 &&
      !query_prop("_dragonarmy_summon_dragon_prop") &&
      !E(TO)->query_prop(ROOM_I_INSIDE))
    {
	command("summon dragonfear");
    }
    else if (!random(15))
	command("blow _dragonarmy_horn");

    if (!random(3))
	all_inventory(E(TO))->help_da_fight(TO, ob);

    /* We return 0 so normal hit goes off.
	Special attack is handled by guild code */
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!is_old)
    {
	ob->set_color(gColor);
	ob->set_colour(gColor);
    }
}

#include "arm_me_sword.c"
#include "arm_me_pole.c"
#include "arm_me_armour.c"

void
arm_me()
{
    switch(gColor)
    {
    case "red":
	arm_me_pole();
	break;
    case "blue":
	arm_me_sword();
	break;
    default:
	arm_me_sword();
    }

    arm_me_armour();

    command("wield all");
    command("wear all");
}

void
do_die( object killer )
{
    if (objectp(uniform))
	uniform->remove_object();

    ::do_die(killer);
}

void
help_da_fight(object friend, object enemy)
{
    string c;
    object ob = query_attack();

    if (ob)
    {
	if (random(5))
	    return; /* we are busy ourselves */
	if (ob->query_hp() < enemy->query_hp())
	    return; /* kill your enemy first */
    }
    c = enemy->query_color();
    if ((!c) || (member_array(c, DA_COLORS) == -1) ||
      ((c != gColor) && interactive(enemy) &&
	(gColor == friend->query_color())))
	command("kill "+OB_NAME(enemy));
}

