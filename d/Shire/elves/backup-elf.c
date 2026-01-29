/*
 * The leader of the group of elves wandering
 *
 */

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/rivendell/local.h"
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>

inherit "/d/Shire/std/active_monster_base.c";
inherit "/d/Shire/rivendell/npc/names";

#define FIGHT_SHIELD_WEP 1
#define FIGHT_WEP_WEP    2
#define ELF_NUM_TYPES    3 /* Number of types of elves */
#define CITIZEN          0
#define TRAVELLER        1
#define GUARD            2

#define ELF_WEP         RWEP_DIR
#define ELF_ARM         RARM_DIR
#define ELF_OBJ         ROBJ_DIR

#define CITIZEN_WEP     ({"dagger"})
#define TRAV_WEP        ({"longsword"})
#define GUARD_WEP       ({"longsword","c_longsword"})

#define CITIZEN_ARMOUR  ({"chainmail"})
#define TRAV_ARMOUR     ({"chainmail", "chainmail"})
#define GUARD_ARMOUR    ({"chainmail","shield"})
#define WANDERING       "_wandering_elf_"
// Prototypes
string get_adjective();
// shire_npc_name = 'name' of area npcs
string shire_npc_name = "_shire_npc_";
void arm_shire_npc();
static mixed *gFilenames = ({});

// Global Vars
int npc_power, npc_type = -1;
string adj1 = "";
void set_type(int some_num);
void set_elf_average(int level);
int query_elfmaker_elf();




void
create_active_monster()
{
    add_name("_is_elf_gr_traveller");
    set_type(random(4)-1);
    set_elf_average(150+random(70));
     
    set_prospective_cluster(({ "_is_elf_gr_traveller" }));
    
    shire_npc_name = WANDERING;
    set_race_name("elf");
    // set_name("elf");
    add_name(shire_npc_name);
    set_adj(({get_adjective(), get_adjective()}));
    set_appearance_offset(-50);

    add_prop(CONT_I_HEIGHT, 200);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_WEIGHT, 0);
    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_QUICKNESS, 150); /* speed up attacks */
    add_prop(NPC_I_NO_LOOKS, 500); /*sets visual looks */
    set_long("@@elf_long@@");
    set_skill(SS_SNEAK, 75 + random(25));
    set_skill(SS_HIDE,  75 + random(25));
    
    set_autosneak(1);

    set_cact_time(5);
    add_cact("say Begone foul one!");
    add_cact("shout Help! Help! Servants of the Dark One are " +
        "attacking us!");
    add_cact("say How dare you attack me!");
    add_cact("emote stares at you in disbelief.");
    add_cact("emote prays to Elbereth for strength.");
    equip(({}));
}


public int
check_seen(object for_obj)
{
    if (member_array(for_obj, this_object()->query_team_others()) > -1)
        return 1;
    
    return ::check_seen(for_obj);
} /* check_seen */


/*
 * Function name: add_equipment
 * Description:   Adds equipment to Npcs.
 * Arguments:     filenames - An array of filenames of the equipment
 *                            we want to clone.
 */
void
add_equipment(mixed filenames)
{
    if (stringp(filenames))
	filenames = ({filenames});
    if (!sizeof(filenames))
	return;
    gFilenames = filenames;
    if (environment(this_object()))
	arm_shire_npc();
}

void
arm_shire_npc()
{
    if (!sizeof(gFilenames))
	return;
    setuid(); seteuid(getuid());
    map(gFilenames, clone_object)->move(this_object());
    command("wield all");
    command("wear all");
    gFilenames = ({});
}
public string
get_adjective()
{
    string *adjectives, adj;

    adjectives = ({ "proud", "strong", "wise", "knowledgeable",
      "cheerful", "musical", "pensive", "melodious", "noble",
      "thoughtful", "contemplative", "solemn", "happy",
      "merry", "joyful", "curious", "gentle", "glorious"});
    adj = adjectives[random(sizeof(adjectives))];
    // Make sure both adjectives aren't the same:
    while (adj == adj1)
    {
        adj = adjectives[random(sizeof(adjectives))];
    }
    adj1 = adj;
    return adj;
}

void
enter_env(object env, object from)
{
    ::enter_env(env,from);
    if (!objectp(from))
	arm_shire_npc();
}

public string
elf_long()
{
    string str = "";
    int ran;

    str = query_The_name(TP);

    ran = random(4);

    // defines what elves look like
    switch(ran)
    {
    case -1:
	str += " is a bad elf with out a description. Let a " +
	"Shire wizard know about this gross error.\n ";
	break;
    case 0:
	str += " has the look of wisdom in " +HIS_HER(TO)+
	" eyes, an understanding which is earned after countless " +
	"ages of learning. " + CAP(HE_SHE(TO))+
	" is tall and slender with piercing gray " +
	"eyes. A faint light seems to emanate from " +
	HIM_HER(TO) + ".\n";
	break;
    case 1:
	str += " is majestic looking. " +CAP(HE_SHE(TO)) + " looks " +
	"proud and ageless but still full of mirth and life. A " +
	"faint light seems to radiate gently from " +
	HIM_HER(TO) + ".\n";
	break;
    case 2:
	str += " is fair and slender. " + CAP(HE_SHE(TO)) +
	" looks battleworn but still full of life and mirth and " +
	"would probably sing a song or two. A feeling of peace " +
	"seems to surround " + HIM_HER(TO) + ". " + CAP(HE_SHE(TO)) +
	" proudly defends " + HIS_HER(TO) + " lands against danger.\n";
	break;
    case 3:
    str += " is dark haired and has piercing grey eyes. " +
    CAP(HE_SHE(TO)) + " looks proud and fair, and tall for " +
    "one of the First-born. A sense of wisdom can be seen in " +
    HIS_HER(TO) + " fair face.\n";
    break;
    }
    return str;
}

void
arm_elf()
{
    string *filenames = ({});
    int arm_num;
    setuid(); seteuid(getuid());

    switch(npc_type)
    {
    case CITIZEN:
	filenames += ({ELF_WEP + ONE_OF_LIST(CITIZEN_WEP)});
	filenames += ({ELF_ARM + ONE_OF_LIST(CITIZEN_ARMOUR)});
	break;
    case GUARD:
	filenames += ({ELF_WEP + ONE_OF_LIST(GUARD_WEP)});
	filenames += ({ELF_ARM + ONE_OF_LIST(GUARD_ARMOUR)});
	filenames += ({ELF_ARM + "bracers.c"});
	filenames += ({ELF_ARM + "greaves.c"});
	break;
    case TRAVELLER:
	filenames += ({ELF_WEP + ONE_OF_LIST(TRAV_WEP)});
	filenames += ({ELF_ARM + ONE_OF_LIST(TRAV_ARMOUR)});
	break;
    }
    if (sizeof(filenames))
	add_equipment(filenames);

}

nomask public void
set_elf_skills()
{
    int ran_num2,
    npc_stat_avg = query_average_stat(),
    mod_skills,
    com_skill,
    spe_skill,
    gen_skill;


    set_alignment(500 + 2 * npc_stat_avg);

    if (npc_stat_avg > 50)
    {
	mod_skills = npc_stat_avg/3 + 100;
    }
    else
    {
	mod_skills = npc_stat_avg * 2;
    }

    com_skill = mod_skills * 90 / 100;
    spe_skill = mod_skills * 95 / 100;
    gen_skill = mod_skills * 90 / 100;

    if(spe_skill > 150)
	spe_skill = 150;
    else if(spe_skill < 5)
	spe_skill = 5;

    if(com_skill > 140)
	com_skill = 140;
    else if(com_skill < 5)
	com_skill = 5;

    if(gen_skill > 140)
	gen_skill = 140;
    else if(gen_skill < 10)
	gen_skill = 10;

    set_skill(SS_WEP_SWORD,   100);
    set_skill(SS_WEP_KNIFE,   100);
    set_skill(SS_WEP_AXE,     100);
    set_skill(SS_WEP_MISSILE, 100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_SNEAK,       100);
    set_skill(SS_HIDE,        100);
    set_skill(SS_AWARENESS,   100);
    set_skill(SS_ACROBAT,     100);
    arm_elf();
}

nomask public void
set_elf_average(int level)
{
    int *npc_stats, i, ran_num;

    if (level > 200)
    {
	level = 200;
    }
    npc_stats = allocate(6);
    ran_num = random(5);

    npc_stats[0] = level - (ran_num * 5);   	// STR
    npc_stats[1] = level + (ran_num * 3);  	// DEX
    npc_stats[2] = level - (ran_num * 5);   	// CON
    npc_stats[3] = level + (ran_num * 10);	// INT
    npc_stats[4] = level + (ran_num * 10);   	// WIS
    npc_stats[5] = level - ran_num;         	// DIS

    i = -1;
    while (++i < 6)
    {
	if (npc_stats[i] < 10)
	    npc_stats[i] = 10;
    }

        command("wear armours");
    set_stats(npc_stats);
    refresh_mobile();
    set_alarm(0.5,0.0, &set_elf_skills());
}



nomask public void
set_type(int some_num)
{
    if (some_num < 0 || some_num > ELF_NUM_TYPES)
	some_num = 0;

    npc_type = some_num;
    set_gender(random(2));  //  Could be male or female
    if (!query_gender())
	set_name(get_male_name());
    else
	set_name(get_female_name());

    switch(npc_type)
    {
    case CITIZEN:
	add_name("citizen");
	break;
    case TRAVELLER:
	add_name("traveller");
	break;
    case GUARD:
	add_name("guard");
	break;
    }
}


void
introduce_elf(string who)
{
    object obj;

    if (query_attack())
    {
	if (query_attack()->query_real_name() == lower_case(who))
	    command("say Begone, you murdering " +
	      query_attack()->query_race_name() +
	      ", servant of the Nameless One!");
	else
	    command("say A servant of the Dark One, a " +
	      query_attack()->query_nonmet_name() +  "is in the valley. "+
	      "Be on the look out!");
	return;
    }
    if (interactive(obj = present(who, environment())))
    {
    command("introduce myself to "+ who);
 	command("say Mae govannen!");

	switch (random(5))
	{
	case 0:
	    command("say Nice to meet you "+obj->query_name());
	    break;
	case 1:
	    command("greet "+who);
	    break;
	case 2:
	    command("say How do you do, kind " +
	      obj->query_race_name() + "?");
	    break;
	case 3:
	    command("say `Elen sila lumenn omentielvo', " +
	      "A star shines on the hour of our meeting'.");
	    break;
	case 4:
	    command("emote welcomes you to Imladris.");
	}
    }
}

public void
add_introduced(string name)
{
    set_alarm(2.0,0.0,&introduce_elf(name));
}

void
do_die(object killer)
{
    object room = E(TO);
    if (query_hp() < 1)
    {
    tell_room(room, "The elf sighs sadly and then dies "+
      "before you.\n", ({ TO }));

    }
    return ::do_die(killer);

}


int
query_elfmaker_elf()
{
    return 1;
}



private int fightmode = 0;
private int alarm_id = 0;

int get_alarm_id() 
{ 
	return alarm_id;
}

void set_alarm_id(int id) 
{
	alarm_id = id;
}

int use_two_weapons() ;
int use_shield_weapon();

void special_hit_msg(mixed hit, object enemy);
mixed special_hit(object enemy, int i);
void do_attack(object enemy);


void set_fightmode(int mode)
{
	fightmode=mode;
}

int get_fightmode ()
{
	return fightmode;	
}


int use_two_weapons() 
{
	command("remove shield");
	command("wield all");
	return 0;
}

int use_shield_weapon() 
{
	command("unwield all");
	command("wear shield");
	command("wield all");
	return 0;
}

int special_attack(object enemy)
{
	object *enemies;
	int es, i, how, loc;
	int flag=0;
	mixed *hitresult;

	// how many people do I defend from ?
	enemies = query_enemy(-1)->query_attack() & ({this_object()});
	//dump_array(enemies);
	
	es = sizeof (enemies);

	// switch to 2 handed fighting if not tanking	
	if (es == 0 && fightmode != FIGHT_WEP_WEP) {
		use_two_weapons();
		fightmode=FIGHT_WEP_WEP;
	} else if (es > 0 && fightmode != FIGHT_SHIELD_WEP) {
		use_shield_weapon();
		fightmode=FIGHT_SHIELD_WEP;
	}
	
	// lets punish mega tankers
   	//dump_array(query_attack()->query_enemy(-1));

	// if we are not tanking we may try to execute a special attack
	// random(2) = 50% chance
	// otherwise we have 25% chance for a weaker spec
	if (es == 0 && random(2) == 0) {
		// lets see what is our index on our targets enemy list
		i = member_array(TO, query_attack()->query_enemy(-1));

		hitresult = special_hit(enemy, i);
		special_hit_msg(hitresult, enemy);
		return 1;
	} else if (random(4) == 0) {
		special_hit_msg(hitresult, enemy);
		return 1;
	}
	
	return 0;
}

void
special_hit_msg(mixed hit, object enemy)
{
	tell_room(ENV(TO), QCTNAME(TO) + " smiles as he wickedly slashes " + QPNAME(enemy) + 
		" back with his " + TO->query_weapon(-1)[0]->query_name() + ".\n", enemy);
	enemy->catch_vbfc(QCTNAME(TO) + " smiles wickedly as he buries his " + 
		TO->query_weapon(-1)[0]->query_name() + " deep into your back.\n");
} 


mixed 
special_hit(object enemy, int i) 
{
	int dmg = 100;
	// i>1 means our target is already defending from two others
	// so we make him much more vulnerable
	// yes, someone tanking 5 of them is potentially really screwed
	if (i>1) {
		dmg = dmg*i;
	} 
	return enemy->hit_me(dmg, W_SLASH, TO, -1);
}



// perform attack but avoid calling attack_object defined in this file
void do_attack(object enemy) 
{
	//write("In do_attack...\n");
	if (ENV(TO) != ENV(enemy))
		command("emote sings a sorrowful song.");
        environment()->continue_patrol(TO);
		return;
	
	if (TO->query_combat_object()->cb_query_attack() != enemy)
	{
		command("shout Die fool!");
		tell_room(ENV(TO), QCTNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
		enemy->catch_vbfc(QCTNAME(TO) + " attacks you!\n");	
		::attack_object(enemy);
	}	
}


