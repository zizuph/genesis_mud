/*
 * /d/Gondor/common/guild2/npc/npc_mage.c
 *
 * A npc member of the Society of Morgul Mages
 *
 * Olorin, July 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define ARM_ARRAY1 ({MORGUL_DIR + "obj/blackcap", }) 

//     Prototypes:
public string  long_desc();
public string  query_morgul_title();
public int     query_morgul_level();
public int     query_undead();

//     Global variables:
static int     Hooded,
               Cast_Sulambar = 1;
static string  Weapon_Name;

public void
create_mage()
{
}

nomask void
create_ithil_monster()
{
    set_name("magus");
    set_race_name("human");
    set_long(long_desc);

    set_alignment(MORGUL_I_ALIGN_JOIN - 200);
    add_subloc(MORGUL_S_SUBLOC, TO);
    add_prop(LIVE_I_UNDEAD, query_undead);

    default_config_npc(60);
    set_learn_pref(({1, 1, 1, 2, 1, 1, 0, 1, 0, }));

    set_skill(SS_WEP_SWORD,	50);
    set_skill(SS_WEP_POLEARM,	50);
    set_skill(SS_WEP_AXE,	50);
    set_skill(SS_WEP_KNIFE,	50);
    set_skill(SS_WEP_CLUB,	50);
    set_skill(SS_DEFENCE,	50);
    set_skill(SS_PARRY,		50);

    set_skill(SS_SPELLCRAFT,	90);
    set_skill(SS_HERBALISM,	60);

    set_skill(SS_FORM_TRANSMUTATION,	40);
    set_skill(SS_FORM_ENCHANTMENT,	80);
    set_skill(SS_FORM_CONJURATION,	80);

    set_skill(SS_ELEMENT_FIRE,	40);
    set_skill(SS_ELEMENT_AIR,	70);
    set_skill(SS_ELEMENT_DEATH,	90);

    set_skill(SS_SNEAK,		50);
    set_skill(SS_HIDE,		50);

    set_skill(SS_LANGUAGE,	50);

    set_skill(SS_SWIM,		50);
    set_skill(SS_CLIMB,		50);
    set_skill(SS_AWARENESS,	50);

    add_prop(CONT_I_HEIGHT,    185);
    add_prop(CONT_I_WEIGHT,  72000);
    add_prop(CONT_I_VOLUME,  60000);

    add_prop(LIVE_I_NO_CORPSE, 1);

    create_mage();

    add_name("mage");
    if (!sizeof(query_adjs()))
	set_adj(({"dark-skinned", "red-eyed"}));

    if (query_base_stat(SS_OCCUP) == 0)
      set_base_stat(SS_OCCUP, query_average_stat() + random(10) -5);

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
    add_cact("@@emote_enemy|sneer@@");
    add_cact("@@emote_enemy|mscoff@@");
    add_cact("mwail");
    add_cact("rasp Die you sucker!");

}

string
long_desc()
{
    string  desc;

    desc = "He is "+LANG_ADDART(implode(query_adjs(), " "))+" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
        desc = CAP(query_real_name()) + " is "+LANG_ADDART(implode(query_adjs(), " ")) +
               " "+query_race_name()+ ", presenting himself as:\n" +
               CAP(query_real_name())+" "+query_title()+", "+query_exp_title() +
               ", male "+query_race_name()+".\n";

    desc += "He is tall and lean for a human.\n";

    return desc;
}

static void
get_mage_robe()
{
    object  robe;

    if (!objectp(robe = present("morgul_guild_object", TO)))
    {
        robe = clone_object(MAGES_DIR + "npc/npc_robe");
        robe->move(TO);
    }
    robe->check_spell_object(TO);

    if (member_array(MORGUL_SOUL_FILE, query_cmdsoul_list()) < 0)
    {
        add_cmdsoul(MORGUL_SOUL_FILE);
        update_hooks();
    }

    command("wear all");
    command("wear hood");
}

void
arm_me()
{
    ::arm_me();

    get_mage_robe();

    Weapon_Name = query_weapon(-1)[0]->query_name();
}

/*
 * These functions taken from:
 * /d/Gondor/common/guild2/morgul_shadow.c
 *
 * The guild shadow for the Morgul Mages of Gondor
 */

#define GUILD_TAX             25
#define APPRENTICE_GUILD_TAX  15

/*
 * Global variables
 */
int     nazgul;			// = 1: Nazgul, = 2: Lord/Lady of the Nazgul

int
query_guild_tax_occ()
{
    if (query_morgul_level() < APPRENTICE_LEVEL)
        return APPRENTICE_GUILD_TAX;
    return GUILD_TAX;
}

string query_guild_style_occ() { return GUILD_STYLE; }

string query_guild_name_occ() { return GUILD_NAME; }

/*
 * set_nazgul(), query_nazgul()
 * nazgul = 1: Nazgul
 * nazgul = 2: Lord or Lady of the Nazgul
 */
void
set_nazgul(int i)
{
    nazgul = i;
}

int
query_nazgul()
{
    return nazgul;
}

/*
 * set_morgul_penalty(), query_morgul_penalty()
 * effective morgul_level = morgul_level - morgul_penalty
 */
int
set_morgul_penalty(int i)
{
    set_skill(SS_MORGUL_PENALTY, i);
    return 1;
}

int
query_morgul_penalty()
{
    return query_skill(SS_MORGUL_PENALTY);
}

int
query_morgul_level()
{
    int     m_stat = query_stat(SS_OCCUP),
            mlevel,
            nlevels;

    FIX_EUID
    nlevels = sizeof(MORGUL_MASTER->query_male_titles());

    if (m_stat > 100)
        m_stat = 100;

    mlevel = ((m_stat * (nlevels - 1)) / 100);
    mlevel += query_morgul_penalty();
    if (mlevel < 0)
        mlevel = 0;
    mlevel += (nazgul * nlevels);
    return mlevel;
}

string
query_morgul_title()
{
    FIX_EUID

    if (nazgul)
    {
        if (query_gender() == 1)
            return (MORGUL_MASTER->query_female_nazgul_titles())[nazgul-1];
        else
            return (MORGUL_MASTER->query_male_nazgul_titles())[nazgul-1];
    }

    if (query_gender() == 1)
        return (MORGUL_MASTER->query_female_titles())[query_morgul_level()];
    else
        return (MORGUL_MASTER->query_male_titles())[query_morgul_level()];
}

string
query_guild_title_occ()
{
    return query_morgul_title();
} 

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MORGUL_S_SUBLOC)
//        return ::show_subloc(subloc, me, for_obj);
        return ::show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(me->query_pronoun()) + " is ";

    return str + "a Member of the Society of Morgul Mages.\n";
}

public int 
query_undead()
{
    return query_stat(SS_OCCUP);
}

/*
 * Function name:	query_spells
 * Returns:		Active Morgul spells
 */
string *
query_spells()
{
    object  spell_obj;

    if (!objectp(spell_obj = present(MORGUL_S_SPELL_OBJECT, TO)))
        return 0;

    return (spell_obj->query_verbs() + ({}));
}

int
special_attack(object target)
{
    object *mages;
    string *spells = query_spells(),
            spell,
            name;

    ::special_attack(target);

    if (!sizeof(query_weapon(-1)))
        command("wield "+Weapon_Name);

    if (random(3))
        return 0;

    if (!sizeof(spells))
        get_mage_robe();
    spells = query_spells();
    spells -= ({ "arhalgul", "mortirio", "nifarist", "ephessul", });

    // don't let him call for help outside Minas Morgul
    if (explode(file_name(ENV(target)), "/")[3] != "morgul")
        spells -= ({ "palanquendo" });

    switch((spell = ONE_OF_LIST(spells)))
    {
        case "arhalgul":
        case "artirith":
        case "crabandir":
        case "mortirio":
        case "nifarist":
            break;
        case "palanquendo":
            mages = users() - ({ 0 });
            mages = filter(mages, "member_filter", MORGUL_SOUL_FILE);
            mages = filter(mages, &not() @ &->query_wiz_level());
            if (!sizeof(mages))
                break;
            name = ONE_OF_LIST(mages)->query_real_name();
            command("unwield all");
            command("palanquendo "+name+" Help, I'm under attack from "
              + LANG_ADDART(target->query_nonmet_name()));
            break;
        case "dollost":
        case "faugoroth":
            command("unwield all");
            command(spell+" "+target->query_real_name());
            break;
        case "naro":
            command("unwield all");
            if (random(2))
                command(spell+" "+target->query_real_name()+" libo makil!");
            else
                command(spell+" "+target->query_real_name()+" drego nin!");
            break;
        case "dramalgos":
        case "morthul":
        case "thunaur":
        default:
            command(spell+" "+target->query_real_name());
            break;
        case "ringurth":
            command("unwield all");
            command(spell+" me");
            break;
        case "sulambar":
            if (Cast_Sulambar)
                command(spell);
            else
                command("faugoroth");
            break;
    }
    /* Re-arm as necessary. */
    command("wield "+Weapon_Name);
    return 0;
}

void
set_arm_arrays()
{
    ::set_arm_arrays();
    Arm1 = ARM_ARRAY1;
}

void
loot_corpse()
{
    command("get all from corpse");
    command("spit");
    command("think how the corpse isn't even worth scavenging for food.");
}

string
emote_enemy(string str)
{
    object  pl;

    if (!objectp(pl = query_attack()))
        return "";

    command(str+" "+pl->query_real_name());

    return "";
}

void
do_attack(object victim)
{
    if(query_attack())
        return;
    if (!present(victim,ENV(TO)))
        return;
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,victim))
        return;
    command("kill "+victim->query_real_name());
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (Cast_Sulambar)
	command("sulambar");
    else
	command("thunaur");
}

public void set_hooded(int i = 1) { Hooded = i; }
public int  query_hooded() { return Hooded; }

public string
mage_address(object mage)
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
 * Function name: send_report
 * Description:   Send a string to a player mage using palanquendo
 *                The message is sent to the highest ranking
 *                mortal mage logged in.
 * Argument:      msg - the string message or VBFC (only function vars!)
 * Returns:       1   - if message was sent
 *                0   - no mortal mages present
 */
static int
send_report(mixed msg)
{
    object *mages,
	   *wep;

    mages = users() - ({ 0 });
    mages = filter(mages, &operator(==)(MORGUL_S_GUILD_NAME) @ &->query_guild_name_occ());
    mages = filter(mages, not @ &->query_wiz_level());
    if (!sizeof(mages))
        return 0;
    mages = sort_array(mages, &MORGUL_SOUL_FILE->compare_rank());

    if (sizeof(wep = query_weapon(-1)))
    {
	Weapon_Name = OB_NAME(wep[0]);
	command("unwield all");
    }
    set_alarm(7.0, 0.0, &command("wield " + Weapon_Name));
    command("palanquendo "+mages[0]->query_real_name()+" "+msg+mage_address(mages[0])+"!");
    log_file("mm_report", TO->query_name() + " sent a report to " +
        mages[0]->query_name() + " in " + file_name(environment(TO)) +
        " on " + ctime(time()) + ": " +
        msg + ".\n", -1);
    return 1;
}

public void
set_cast_sulambar(int i = 1)
{
    Cast_Sulambar = i;
}

