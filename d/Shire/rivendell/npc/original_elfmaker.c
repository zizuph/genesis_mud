/* Rivendell elf npc base.
 * Based on the Hobbitmaker
 * Coded by Finwe, March 1998
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <formulas.h>

inherit SHIRE_MONSTER;
inherit "/d/Shire/rivendell/npc/names";

#define NUM_TYPES       3 /* Number of types of elves */
#define CITIZEN         0
#define TRAVELLER       1
#define GUARD           2

#define ELF_WEP         RWEP_DIR
#define ELF_ARM         RARM_DIR
#define ELF_OBJ         ROBJ_DIR

#define CITIZEN_WEP     ({"dagger"})
#define TRAV_WEP        ({"longsword"})
#define GUARD_WEP       ({"longsword"})

#define CITIZEN_ARMOUR  ({"chainmail"})
#define TRAV_ARMOUR     ({"chainmail", "chainmail"})
#define GUARD_ARMOUR    ({"chainmail"})

#define SHIRE_NPC   "_riv_elf_"

int attack_alarm;

static  object  Victim;


// Prototypes
string get_adjective();

// Global Vars
int npc_power, npc_type = -1;

void create_elf() {}
void test_can_see(object victim);
void help_friend(object ob, object friend);

nomask void
create_shire_monster()
{
    set_race_name("elf");
    set_name("elf");
    add_name("_elfmaker_elf");
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

    set_act_time(NPC_TELL_TIME);
    set_cact_time(5);

    add_act("emote sings a cheerful song.");
    add_act("emote giggles merrily.");
    add_act("emote sighs happily.");
    add_act("emote looks to the west and sighs forlornly.");
    add_act("emote sighs deeply.");

    add_act("emote sings a cheerful song.");
    add_act("emote giggles merrily.");
    add_act("emote sighs happily.");
    add_act("emote looks to the west and sighs forlornly.");
    add_act("emote sighs deeply.");
    add_act("say I seek for peace and rest.");
    add_act("say Never trust a dwarf. They are foul creatures.");

    add_cact("say Begone foul one!");
    add_cact("shout Help! Help! Servants of the Dark One are " +
        "attacking us!");
    add_cact("say How dare you attack me!");
    add_cact("emote stares at you in disbelief.");
    add_cact("emote prays to Elbereth for strength.");

    create_elf();
}


public string
get_adjective()
{
    string *adjectives;

    adjectives = ({ "proud", "strong", "wise", "knowledgeable",
      "cheerful", "musical", "pensive", "melodious", "noble",
      "thoughtful", "contemplative", "solemn", "happy",
      "merry", "joyful", "curious", "gentle", "glorious"});

    return adjectives[random(sizeof(adjectives))];
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
set_type(int some_num)
{
    if (some_num < 0 || some_num > NUM_TYPES)
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

nomask public void
set_elf_average(int level)
{
    int *npc_stats, i, ran_num;

    if (level > 200)
    {
	level = 200;
    } 
    npc_stats = allocate(6);
    ran_num = random(10);

    npc_stats[0] = level - (ran_num * 3);   // STR
    npc_stats[1] = level + (ran_num * 3);   // DEX
    npc_stats[2] = level - (ran_num * 2);   // CON
    npc_stats[3] = level + ran_num;         // INT
    npc_stats[4] = level + (ran_num * 2);   // WIS
    npc_stats[5] = level - ran_num;         // DIS

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

void
introduce_elf(string who)
{
    object obj;

    if (query_attack())
    {
	if (query_attack()->query_real_name() == lower_case(who))
	    command("say Begone, you murdering " +
	      query_attack()->query_race_name() +
	      " servant of the Nameless One!");
	else
	    command("say A servant of the Dark One, a " +
	      query_attack()->query_nonmet_name() +  "is in the valley. "+
	      "Be on the look out!");
	return;
    }
    if (interactive(obj = present(who, environment())))
    {
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
	    command("say `Elen sila lumenn omentielvo' " +
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
	RIVENDELL_MASTER->add_elf_killer(killer);
/*
    tell_room(room, "The elf sighs sadly and then dies "+
      "before you. " + CAP(HIS_HER(TO)) + " body suddenly melts " +
      "into the earth, disappearing forever.\n", ({ TO }));
	all_inventory()->remove_object();
*/
    tell_room(room, "The elf sighs sadly and then dies "+
      "before you.\n", ({ TO }));

    }
    return ::do_die(killer);

}

void
elf_attacker_hook(object player)
{
    command("peer susp at "+player->query_real_name());
}

void
elf_killer_hook(object player)
{
    command("kill "+player->query_real_name());
}


void
attacked_by_hook(object player)
{
   if (player->query_race() == "elf")
   {
        player->stop_fight(this_object());
        write("A feeling of dispair comes over you at the " +
            "thought of attacking another elf. You decide not to " +
            "and the feeling leaves you.\n");
        say ("A shadow passes over " + player->query_nonmet_name() + 
            ". Suddenly, it's gone.\n");
    }
    else
    {
        command("shout Call to arms!! This " + player->query_nonmet_name() + 
            " is an elf attacker!!");
        command("wield all");
    }
}


void
init_living()
{
    ::init_living();
setuid();
seteuid(getuid());
    if (IS_ATTACKER(this_player()))
	set_alarm(1.0,0.0,&elf_attacker_hook(this_player()));
    if (IS_KILLER(this_player()))
	set_alarm(1.0,0.0,&elf_killer_hook(this_player()));
}

int
query_elfmaker_elf()
{
    return 1;
}

object *
find_my_friends()
{
    return filter(all_inventory(ENV(TO)), &->query_elfmaker_elf());
}

void
attacked_by(object ob)
{
    if (!objectp(query_attack()))
    {
	attacked_by_hook(ob);
    }
    ::attacked_by(ob);
    RIVENDELL_MASTER->add_elf_attacker(ob);
    find_my_friends()->notify_friend_attacked_by(ob);
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    RIVENDELL_MASTER->add_elf_attacker(ob);
    find_my_friends()->notify_friend_attacked_by(ob);
}

void
assist_friend(object ob)
{
    if (!present(ob, environment()) || objectp(query_attack()))
	return;
    if (!F_DARE_ATTACK(TO,ob))
    {
	command("shout To arms!! This "+ob->query_nonmet_name() + 
	  " is murdering our kin!!");
	return;
    }
    switch(random(5))
    {
    case 0:
	command("say Die, foul Servant of the Dark One!");
	break;
    case 1:
	command("shout A Elbereth Gilthoniel!");
	break;
    case 2:
	command("shout A tiro nin, Fanuilos!");
	break;
    case 3:
	command("shout You will not see another day!");
	break;
    case 4:
	command("shout I will destroy you, foul "+ob->query_race_name()+"!!");
	break;
    }
    if (!command("kill "+ob->query_real_name()))
	command("assist _elfmaker_elf");
}

void
notify_friend_attacked_by(object ob)
{
    if (!present(ob, environment()) || objectp(query_attack()))
	return;
    set_alarm(itof(random(3) + 1), 0.0, &assist_friend(ob));
}

public int
special_attack(object enemy)
{
    if (!present("_imladris_elf_paralyze_", enemy) && !random(10)) 
    { 
	clone_object(ROBJ_DIR + "stun.c")->move(enemy, 1); 
	enemy->catch_tell("\nYou are hit on the head by " + short()+".\n"+
	  "You are knocked unconcious!\n\n");
    }  
}


/*
 * Function name:   start_follow
 * Description:     Start following the enemy.
 * Arguments:       The object to follow.
 */
public void
start_follow(object ob)
{
    object *follower,
            shadow;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))) || 
	(ob != query_attack()) || (Victim == ob))
	return;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->follow(ob, TO);
    }
    Victim = ob;
}