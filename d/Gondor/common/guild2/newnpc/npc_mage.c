/*
 *  /d/Gondor/common/guild2/newnpc/npc_mage.c
 *
 *  A npc member of the Society of Morgul Mages. Based upon Olorin's 
 *  original implementation. Adjusted to work with the new spell 
 *  system.
 *
 *  Original by Olorin, July 1994
 *  Partially rewritten by Eowul, September 2004
 */

#pragma save_binary
#pragma strict_types

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define ARM_ARRAY1 ({MORGUL_DIR + "obj/blackcap", }) 

inherit "/d/Gondor/morgul/npc/ithil_monster";

//      Prototypes:
public  string  long_desc();
public  int     query_undead();
        object  *query_mage_list_by_rank();
        object  *query_mage_list();

//      Variables
static  int     nazgul;
static  string  weapon_name;
static  int     cast_sulambar = 1;

/*
 * Function name: create_mage
 * Description  : Redefine this function to customize your mage NPC
 */
public void create_mage()
{
}

/*
 * Function name: create_ithil_monster
 * Description  : Construct an ithil monster. Will call create_mage
 */
nomask void create_ithil_monster()
{
    set_name("magus");
    set_race_name("human");

    set_alignment(MORGUL_I_ALIGN_JOIN - 200);
    add_subloc(MORGUL_S_SUBLOC, TO);
    add_prop(LIVE_I_UNDEAD, query_undead);

    default_config_npc(60);
    set_learn_pref(({1, 1, 1, 2, 1, 1, 0, 1, 0, }));

    // Set up the skills for our mage
    set_skill(SS_WEP_SWORD,	    50);
    set_skill(SS_WEP_POLEARM,	50);
    set_skill(SS_WEP_AXE,	    50);
    set_skill(SS_WEP_KNIFE,	    50);
    set_skill(SS_WEP_CLUB,	    50);
    set_skill(SS_DEFENCE,	    50);
    set_skill(SS_PARRY,		    50);

    set_skill(SS_SPELLCRAFT,	90);
    set_skill(SS_HERBALISM,	    60);

    set_skill(SS_FORM_TRANSMUTATION,	40);
    set_skill(SS_FORM_ENCHANTMENT,	    80);
    set_skill(SS_FORM_CONJURATION,	    80);

    set_skill(SS_ELEMENT_FIRE,	    40);
    set_skill(SS_ELEMENT_AIR,	    70);
    set_skill(SS_ELEMENT_DEATH,	    90);

    set_skill(SS_SNEAK,		        50);
    set_skill(SS_HIDE,		        50);

    set_skill(SS_LANGUAGE,	50);

    set_skill(SS_SWIM,		50);
    set_skill(SS_CLIMB,		50);
    set_skill(SS_AWARENESS,	50);

    add_prop(CONT_I_HEIGHT,    185);
    add_prop(CONT_I_WEIGHT,  72000);
    add_prop(CONT_I_VOLUME,  60000);

    add_prop(LIVE_I_NO_CORPSE, 1);

    // Allow the coder to redefine their mage
    create_mage();

    // Make sure some default names are set
    add_name("mage");
    if (!sizeof(query_adjs()))
	set_adj(({"dark-skinned", "red-eyed"}));

    if (query_base_stat(SS_OCCUP) == 0)
      set_base_stat(SS_OCCUP, query_average_stat() + random(10) -5);

    // Standard mage emote behaviour ;)
    set_act_time(7);
    add_act("gaze");
    add_act("mleer");
    add_act("mremember");
    add_act("mscoff");
    add_act("torture");
    add_act("withdraw");

    set_cact_time(2);
    add_cact("mcurse");
    add_cact("shriek");
    add_cact(&emote_enemy("mcurse"));
    add_cact(&emote_enemy("sneer"));
    add_cact(&emote_enemy("mscoff"));
    add_cact("mwail");
    add_cact("rasp Die you sucker!");
}

/*
 * Function name: query_undead
 * Description  : Return our undead percentage, it's based on our OCCUP stat
 * Returns      : an integer between 10 and 100
 */
public int query_undead()
{
    return MAX(10, MIN(100, query_stat(SS_OCCUP)));
}

/* 
 * Function name: long_desc
 * Description  : Generate a default long description for the NPC's
 * Returns      : a string, describing the mage
 */
string long_desc()
{
    string  desc;

    desc = "He is "+LANG_ADDART(implode(query_adjs(), " "))+" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        desc = CAP(query_real_name()) + " is " + 
            LANG_ADDART(implode(query_adjs(), " ")) + " " + query_race_name() + 
            ", presenting himself as:\n" + CAP(query_real_name()) + " " + 
            query_title() + ", " + query_exp_title() + ", male " + 
            query_race_name() + ".\n";
    }

    desc += "He is tall and lean for a human.\n";

    return desc;
}

/*
 * Function name: query_guild_style_occ
 * Description  : Returns the style of our OCCUP guild
 * Returns      : The guild style as string
 */
string query_guild_style_occ() 
{ 
    return GUILD_STYLE; 
}

/* 
 * Function name: query_guild_name_occ
 * Description  : Returns the name of our OCCUP guild
 * Returns      : a string with the name
 */
string query_guild_name_occ() 
{ 
    return GUILD_NAME; 
}

/*
 * Function name: set_nazgul
 * Description  : Set if this NPC is a nazgul. 
 * Arguments    : i - 0 for normal mage, 1 for nazgul, 2 for king
 */
void set_nazgul(int i)
{
    nazgul = i;
}

/*
 * Function name: query_nazgul
 * Description  : Return the value set by set_nazgul
 * Returns      : an integer (1 - nazgul, 2 - king)
 */
int query_nazgul()
{
    return nazgul;
}

/*
 * Function name: set_morgul_penalty
 * Description  : Set the guild penalty
 *              : effective morgul_level = morgul_level - morgul_penalty
 * Arguments    : i - the penalty value
 */
int set_morgul_penalty(int i)
{
    set_skill(SS_MORGUL_PENALTY, i);
    return 1;
}

/*
 * Function name: query_morgul_penalty
 * Description  : Get the value of the guild penalty as set by 
 *              : set_morgul_penalty
 * Returns      : an integer
 */
int query_morgul_penalty()
{
    return query_skill(SS_MORGUL_PENALTY);
}

/*
 * Function name: query_morgul_level
 * Description  : Calculate our rank based on our stat and the penalty skill
 * Returns      : the rank of this mage
 */
int query_morgul_level()
{
    int     m_stat = query_stat(SS_OCCUP),
            mlevel,
            nlevels;

    FIX_EUID
    nlevels = MAX_NORMAL_LEVELS;

    if (m_stat > 100)
        m_stat = 100;

    mlevel = ((m_stat * MAX_NORMAL_LEVELS) / 100);
    mlevel += query_morgul_penalty();
    if (mlevel < 0)
        mlevel = 0;
    mlevel += (nazgul * MAX_NORMAL_LEVELS);
    if (mlevel > MAX_NORMAL_LEVELS) return ARCHMAGE_LEVEL;
    return mlevel;
}

/*
 * Function name: query_morgul_title
 * Description  : Returns the title of this mage, based on their rank
 * Returns      : a string with the title
 */
string query_morgul_title()
{
    FIX_EUID

    int index = nazgul ? sizeof(MORGUL_QUENYA_MALE_TITLES) - 3 + nazgul :
        query_morgul_level();
        
    if (query_gender() == 1)
        return MORGUL_QUENYA_FEMALE_TITLES[index];
    else
        return MORGUL_QUENYA_MALE_TITLES[index];
}

/*
 * Function name: query_guild_title_occ
 * Description  : Returns the same value as query_morgul_title
 * Returns      : a string
 */
string query_guild_title_occ()
{
    return query_morgul_title();
} 

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		          me      - I
 *		          for_obj - The looker
 * Returns:	      The string the looker shall see
 */
string show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MORGUL_S_SUBLOC)
        return ::show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(me->query_pronoun()) + " is ";

    return str + "a Member of the Society of Morgul Mages.\n";
}

/*
 * Function name: get_mage_robe
 * Description  : Get ourselves a mage robe and wear it
 */
void get_mage_robe()
{
    object  robe;

    if (!objectp(robe = present("morgul_guild_object", TO)))
    {
        robe = clone_object(MAGES_DIR + "mage_robe");
        robe->move(TO);
    }

    if (member_array(MORGUL_COMMAND_SOUL, query_cmdsoul_list()) < 0)
    {
        add_cmdsoul(MORGUL_COMMAND_SOUL);
        update_hooks();
    }

    command("wear all");
    command("wear hood");
}

/*
 * Function name: arm_me
 * Description  : Equip the mage
 */
void arm_me()
{
    ::arm_me();

    // Equip us with our robe (and spells)
    get_mage_robe();

    // Store the name of our weapon so that we can wield it again 
    weapon_name = OB_NAME(query_weapon(-1)[0]);
}

/*
 * Function name: query_spells
 * Description  : Get a list of all active spells
 * Returns      : Active Morgul spells
 */
string *query_spells()
{
    object  spell_obj;

    if (!objectp(spell_obj = present(MORGUL_S_SPELL_OBJECT, TO)))
        return ({ });

    return m_indexes(spell_obj->query_spell_map());
}

/*
 * Function name: special_attack
 * Description  : Called when we need to execute a special attack, allows
 *              : the mage to cast spells.
 * Arguments    : target - who to kill
 * Returns      : 0 if we need to continue attacking normally, 1 if not
 */
int
special_attack(object target)
{
    object *mages;
    string *spells = query_spells(),
            spell,
            name;

    ::special_attack(target);

    // Wield our weapon again if we are not casting our spells
    if (!objectp(query_prop(LIVE_O_CONCENTRATE)) && !sizeof(query_weapon(-1)))
        command("wield " + weapon_name);

    if (random(3))
        return 0;

    // If we dont have spells, make sure we get a robe
    if (!sizeof(spells))
    {
        get_mage_robe();
        spells = query_spells();
    }

    // Remove the spells we dont want use
    spells -= ({ "narusse", "arhalgul", "mortirio", "nifarist", "ephessul", 
        "ringurth", "artirith", "dollost", "gostangwedh", "naro",
        "sauthacuith", "crabandir" });

    // Remove dramalgos for those who already have thunaur
    if(member_array("thunaur", spells) != -1)
        spells -= ({ "dramalgos" });

    // don't let him call for help outside Minas Morgul
    if (explode(file_name(ENV(target)), "/")[3] != "morgul")
        spells -= ({ "palanquendo" }); 

    // Dont use sulambar when that's defined
    if(!cast_sulambar)
        spells -= ({ "sulambar" });

    switch((spell = ONE_OF_LIST(spells)))
    {
        case "palanquendo":
            mages = query_mage_list();
            if (!sizeof(mages))
                break;
            name = ONE_OF_LIST(mages)->query_real_name();
            command("unwield all");
            command("palanquendo "+name+" Help, I'm under attack from "
              + LANG_ADDART(target->query_nonmet_name()));
            break;
        case "faugoroth":
            command("unwield all");
            command("cast " + spell + " at " + OB_NAME(target));
            break;
        case "dramalgos":
        case "morthul":
        case "thunaur":
        default:
            command("cast " + spell + " at " + OB_NAME(target));
            break;
        case "sulambar":
            command("unwield all");
            command("cast " + spell);
            break;
    }
}

/*
 * Function name: set_arm_arrays
 * Description  : Prepare our armour
 */
void set_arm_arrays()
{
    ::set_arm_arrays();
    Arm1 = ARM_ARRAY1;
}

/*
 * Function name: loot_corpse
 * Description  : Get the loot from the corpse
 */
void loot_corpse()
{
    command("get all from corpse");
    command("spit");
    command("think how the corpse isn't even worth scavenging for food.");
}

/*
 * Function name: emote_enemy
 * Description  : Perform an emote on an enemy
 * Arguments    : str - the command to execute
 * Returns      : The command with parameters
 */
string emote_enemy(string str)
{
    object  pl;

    if (!objectp(pl = query_attack()))
        return "";

    command(str+" "+pl->query_real_name());

    return "";
}

/*
 * Function name: do_attack
 * Description  : Attack our victim
 * Arguments    : victim - who to kill
 */
void do_attack(object victim)
{
    if(query_attack())
        return;
    if (!present(victim,ENV(TO)))
        return;
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,victim))
        return;
    command("kill " + OB_NAME(victim));
}

/*
 * Function name: attacked_by
 * Description  : Someone actually dares to attack us
 * Arguments    : ob - the soon dead player that attacked us
 */
void attacked_by(object ob)
{
    ::attacked_by(ob);

    // Start with a little cloud when attacked, will be fun
    if (cast_sulambar)
    {
        command("unwield all");
    	command("cast sulambar");
    }
    else
	    command("cast thunaur at " + OB_NAME(ob));
}

/*
 * Function name: set_cast_sulambar
 * Description  : Make it possible to stop casting sulambar
 * Arguments    : i - 1 to cast sulambar, 0 to not
 */
public void set_cast_sulambar(int i = 1)
{
    cast_sulambar = i;
}

/*
 * Function name: query_mage_list
 * Description  : Get all mortal mages 
 * Returns      : an array
 */
object *query_mage_list()
{
    object *mages;

    mages = users() - ({ 0 });
    mages = filter(mages, "member_filter", MORGUL_COMMAND_SOUL);
    mages = filter(mages, &not() @ &->query_wiz_level());

    return mages;
}

/*
 * Function name: query_mage_list_by_rank
 * Description  : Get the list of mortal mages, sorted by rank
 * Returns      : an array
 */
object *query_mage_list_by_rank()
{
    object *mages;

    mages = query_mage_list();
    mages = sort_array(mages, &MORGUL_COMMAND_SOUL->compare_rank());

    return mages;
}

/*
 * Function name: mage_address
 * Description  : How to address a mage (if only we could teach this to 
 *              : apprentices)
 * Arguments    : mage - the mage to address
 * Returns      : the proper title
 */
public string mage_address(object mage)
{
    int     nl;
    string  mage_name;

    if ((nl = mage->query_nazgul()) > 1)
	return ((mage->query_gender() == G_FEMALE) ? "M'Lady" : "Sire");

    mage_name = MORGUL_MASTER->query_mage_name(mage->query_real_name());
    if (strlen(mage_name))
    {
	if (mage->query_nazgul())
	    return ((mage->query_gender() == 1) ? "Lady " : "Lord ") + mage_name;
	else
	    return mage_name;
    }
    return mage->query_morgul_title();
}

/*
 * Function name: notify_you_killed_me
 * Description  : Called whenever we have killed something
 * Arguments    : victim - the unfortunate living that met it's doom
 */
public void
notify_you_killed_me(object victim)
{
    object  *mages;
    string  msg;

    // Notify a mage of our victory
    mages = query_mage_list_by_rank();
    if (sizeof(mages))
    {
        msg = "Hail Melkor! " + 
            capitalize(LANG_ADDART(victim->query_nonmet_name())) + " met " +
            victim->query_possessive() + " doom at my hands!";
        command("unwield all");
        set_alarm(7.0, 0.0, &command("wield "+weapon_name));
        command("cast palanquendo "+mages[0]->query_real_name()+" "+msg);
    }

    ::notify_you_killed_me(victim);
}