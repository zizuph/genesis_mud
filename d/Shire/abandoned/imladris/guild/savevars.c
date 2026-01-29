/*
 *  /std/living/savevars.c
 *
 *  This file contains all player variables that are saved in the 
 *  player save file. The corresponding set- and query functions
 *  can also be found here.
 *
 *  This file is included into /std/living.c
 */

#include <const.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <std.h>

private string m_in,	        /* Messages when entering or leaving a room. */
	       m_out,   	/* Messages when entering or leaving a room. */
	       mm_in,	        /* Message when arriving by teleport. */
	       mm_out,		/* Message when leaving by teleport. */
               race_name,	/* The name of the race */
               title,		/* Title of the living */
	       *cmdsoul_list,	/* The command souls */
	       *tool_list,	/* Names of tool souls I want */
#ifndef NO_ALIGN_TITLE
               al_title,	/* Alignment title of the living */
#endif
	       *textgivers;     /* Filenames of objects giving names for
	       			   stats, skills etc */

private int    wiz_level,	/* The level of a wizard. */
               hit_points,	/* The hitpoints of this lifeform. */
               mana,            /* The magic points of this lifeform */
               fatigue,         /* How easily this lifeform is fatigued */
	       exp_points,	/* The experience points of this lifeform. */
               exp_combat,	/* Amount of exp gained in combat */
	       is_ghost,	/* If lifeform is dead */
	       see_blood,	/* True if player wants to see fightings */
	       age_heart,	/* Number of heart beats of this character. */
	       is_whimpy,	/* Automatically flee when low on HP */
	       alignment,	/* Depends on good or chaotic lifeform */
	       gender,          /* 0 neut("it"),1 male("he"),2 female("she") */
               appearance,    	/* What we look like (0-99) */
               opinion,         /* What we think of others appearance */
               headache,	/* Hangover coefficient */
    	       intoxicated,     /* How drunk are we? */
    	       stuffed,         /* Are we fed up or not */
	       soaked,		/* How soaked are we ? */
	       *learn_pref,	/* Prefered % to learn / stat */
	       *acc_exp,	/* Accumulated exp / stat */
               scar;            /* The marks of death */
private mapping
               skillmap;        /* Our skills in a mapping */
static	mapping
	       skill_extra_map; /* Extra skills added by items for example */

/*
 * Prototypes
 */

void set_max_headache(int h);
int query_max_headache(); 
int query_stuffed();
int query_intoxicated();
int query_stat(int stat);
void set_hp(int hp);
nomask public int remove_cmdsoul(string soul);
nomask public int remove_toolsoul(string soul);

/*
 *  These vars keep track of the last time the appropriate var was updated.
 */
static private int headache_time;
static private int intoxicated_time;
static private int stuffed_time;
static private int soaked_time;
static int hp_time;
static int mana_time;
static int fatigue_time;
static int age_time;
static int last_intox;
static int last_con;
static int last_stuffed;

/*
 * Function name:   save_vars_reset
 * Description:     Resets some variables which are used to keep track
 *                  of how variables change with time.
 */
private void 
save_vars_reset()
{
    int t;
    PROFILE("save_vars_reset");
    t = time();

    age_time          = t;
    headache_time     = t;
    intoxicated_time  = t;
    stuffed_time      = t;
    soaked_time       = t;
    hp_time           = t;
    mana_time         = t;
    fatigue_time      = t;
    call_out("savevars_delay_reset",1);

    skill_extra_map = ([]);
}

void
savevars_delay_reset()
{
    last_stuffed = query_stuffed();
    last_intox = query_intoxicated();
    last_con = query_stat(SS_CON);
}

/* 
 * Moving messages 
 */

/*
 * Function name:   set_m_in
 * Description:     Set the normal entrance message of this living. You 
 *                  should end the string with a "."
 *                  E.g.: "waddles into the room."
 * Arguments:       m: The message string
 */
public void
set_m_in(string m)
{
    PROFILE("set_m_in");
    m_in = implode(explode(m, "   "), " ");
}

/*
 * Function name:   query_m_in
 * Description:     Gives the normal entrance message of this living.
 * Returns:         The message string
 */
public string
query_m_in()
{
    PROFILE("query_m_in");
    return m_in;
}

/*
 * Function name:   set_m_out
 * Description:     Set the normal exit message of this living. Remember
 *                  that the direction is appended to this string, so do
 *                  not end the string with a "."
 *                  E.g.: "waddles"
 * Arguments:       m: The message string
 */
public void
set_m_out(string m)
{
    PROFILE("set_m_out");
    m_out = implode(explode(m, "   "), " ");
}

/*
 * Function name:   query_m_out
 * Description:     Gives the normal exit message of this living.
 * Returns:         The message string
 */
public string
query_m_out()
{
    PROFILE("query_m_out");
    return m_out;
}

/*
 * Function name:   set_mm_in
 * Description:     Set the magical entrance message of this living. You 
 *                  should end the string with a "."
 *                  E.g.: "falls out of the sky with his mouth full of spam."
 * Arguments:       m: The message string
 */
public void
set_mm_in(string m)
{
    PROFILE("set_mm_in");
    mm_in = implode(explode(m, "  "), " ");
}

/*
 * Function name:   query_mm_in
 * Description:     Gives the magical entrance message of this living.
 * Returns:         The message string
 */
public string
query_mm_in()
{
    PROFILE("query_mm_in");
    return mm_in;
}

/*
 * Function name:   set_mm_out
 * Description:     Set the magical exit message of this living. You should
 *                  end the string with a "."
 *                  E.g.: "disappears in a puff of smoke."
 * Arguments:       m: The message string
 */
public void
set_mm_out(string m)
{
    PROFILE("set_mm_out");
    mm_out = implode(explode(m, "  "), " ");
}

/*
 * Function name:   query_mm_out
 * Description:     Gives the magical exit message of this living.
 * Returns:         The message string
 */
public string
query_mm_out()
{
    PROFILE("query_mm_out");
    return mm_out;
}

/*
 * Function name:   set_race_name
 * Description:     Sets the race name of this living.
 * Arguments:       str: race string
 */
public void
set_race_name(string str)
{
    PROFILE("set_race_name");
    if (id(race_name))
	remove_name(race_name);
    race_name = str;
    add_name(race_name);
}

/*
 * Function name:   query_race_name
 * Description:     Gives the race name of this living
 */
public string
query_race_name()
{
    PROFILE("query_race_name");
    return race_name;
}

/*
 * Function name:   set_title
 * Description:     Sets the title of a living to something else.
 * Arguments:       t: The new title string
 */
public void
set_title(string t)
{
    PROFILE("set_title");
#ifdef LOG_TITLE
    if (this_player() && this_player() != this_object() &&
		interactive(this_object()))
	log_file(LOG_TITLE, query_real_name() + " new title " + t + " by " +
		 this_player()->query_real_name() + "\n");
#endif
    title = t;
}

#ifndef NO_ALIGN_TITLE
/*
 * Function name:   set_al_title
 * Description:     Sets the alignment title of a living to something else
 * Arguments:       t: The new alignment title string
 */
public void
set_al_title(string t)
{
    PROFILE("set_al_title");
#ifdef LOG_AL_TITLE
    if (this_player() && 
	this_player() != this_object() && interactive(this_object()))
	log_file(LOG_AL_TITLE, query_real_name() + " new title " +
		 t + " by " + this_player()->query_real_name() + "\n");
#endif
    al_title = t;
}
#endif
/*
 * Function name:   query_title
 * Description:     Gives the title of a living.
 * Returns:         The title string
 */
public string
query_title()
{
    string dom, name;
    PROFILE("query_title");

    if (!strlen(title))
	title = "";

    if (wiz_level)
    {
	name = query_real_name();
	dom = SECURITY->query_wiz_dom(name);
	if (SECURITY->query_domain_madwand(dom) == name)
	    return LD_MADWAND_TITLE(title, dom);
	else
	    return title;
    }
    else
	return title; 
}

#ifndef NO_ALIGN_TITLE
/*
 * Function name:   query_al_title
 * Description:     Gives the alignment title of a living
 * Returns:         The alignment title string
 */
public string
query_al_title()
{
    PROFILE("query_al_title");
    return al_title;
}
#endif

/*
 * Function name: add_textgiver
 * Description:   Add a filename of an object that gives skill/stat
 *                descriptions to the living.
 * Arguments:     obfile: the filename string
 */
public void
add_textgiver(string obfile)
{
    PROFILE("add_textgiver");
    if (member_array(obfile, textgivers) < 0)
    {
	if (!sizeof(textgivers))
	    textgivers = ({ obfile });
	else
	    textgivers += ({ obfile });
    }
}

/*
 * Function name:   query_textgivers
 * Description:     Gives an array of filenames that give skill/stat
 *                  descriptions to the living
 * Returns:         The array with filenames
 */
public string *
query_textgivers()
{
    PROFILE("query_textgivers");
    return (sizeof(textgivers) ? textgivers + ({}) : ({}));
}

/*
 * Function name:   remove_textgiver
 * Description:     Remove a filename of an object that gives skill/stat
 *                  from the living.
 * Arguments:       obfile: The filename of the object to remove.
 * Returns:         True if succesfully removed.
 */
public int
remove_textgiver(string obfile)
{
    int pos;
    PROFILE("remove_textgiver");

    if ((pos = member_array(obfile, textgivers)) >= 0)
    {
	textgivers = exclude_array(textgivers, pos, pos);
	return 1;
    }
    return 0;
}

/*
 * Wizard level.
 */

/*
 * Function name:   set_wiz_level
 * Description:     Set the wizard level of the living to a new value
 * Arguments:       lev: The new level
 * Returns:         True if the change was succesfull
 */
public nomask int
set_wiz_level(int lev)
{
    PROFILE("set_wiz_level");
    if (!previous_object() || (file_name(previous_object()) != SECURITY
	&& extract(file_name(previous_object()), 0, 12) != "/secure/login"
	&& MASTER_OB(previous_object()) != LOGIN_NEW_PLAYER))
	return 0;

    wiz_level = lev;
    return 1;
}

/*
 * Function name:   query_wiz_level
 * Description:     Gives the wizard level of the living
 * Returns:         The level
 */
public int
query_wiz_level()
{
    PROFILE("query_wiz_level");
    return wiz_level;
}

/*
 * Function name:   query_npc
 * Description:     Checks whether the living is a non-player character
 * Returns:         True if non-player character
 */
public int
query_npc()
{
    PROFILE("query_npc");
    return 1;
}

static void
calculate_hp()
{
    int n, con, intox;
    int tmpcon, tmpintox;

    n = F_NUM_BEATS(time() - hp_time) / F_INTERVAL_BETWEEN_HEALING;
    if (n > 0)
    {
        con = query_stat(SS_CON);
        intox = query_intoxicated();
        tmpcon = (con + last_con) / 2;
        tmpintox = (intox + last_intox) / 2;
        set_hp(hit_points + n * F_HEAL_FORMULA(tmpcon, tmpintox));
        last_con = con;
        last_intox = intox;
        hp_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    }
}

/*
 * Function name:   query_hp
 * Description:     Gives the number of hitpoint left for the living
 * Returns:         The number
 */
public int
query_hp()
{
    PROFILE("query_hp");
    calculate_hp();
    return hit_points;
}

/*
 * Function name:   query_max_hp
 * Description:     Calculates the maximum number of hitpoints that the
 *                  living can achieve.
 * Returns:         The maximum
 */
public int
query_max_hp()
{
    int con;
    PROFILE("query_max_hp");
    con = query_stat(SS_CON);
    return F_MAX_HP(con);
}

/*
 * Function name:   set_hp
 * Description:     Sets the number of hitpoints of a living. The number
 *                  can not exceed the maximum calculated by query_max_hp.
 * Arguments:       hp: The new number of hitpoints
 */
void
set_hp(int hp)
{
    int max;
    PROFILE("set_hp");

    hit_points = hp;

    if (hit_points < 0)
	hit_points = 0;

    if (hit_points > (max = query_max_hp()))
	hit_points = max;
}


/*
 * Function name:   heal_hp
 * Description:     Increase the number of hitpoints with a few.
 * Arguments:       hp: The difference
 */
void
heal_hp(int hp)
{
    object o;
    int hit_points;
    PROFILE("heal_hp");

    hit_points = query_hp(); /* Call the function to make sure we update.*/

#ifdef LOG_REDUCE_HP
    if (!query_npc() && hp < 0 && (100 * -hp / (hit_points - hp)) > 50)
    {
	log_file(LOG_REDUCE_HP,
		 sprintf("%s %d->%d by ",
			 query_name(), hit_points, hit_points + hp));

	if (!this_interactive())
	    log_file(LOG_REDUCE_HP, "?\n");
	else
	    log_file(LOG_REDUCE_HP, this_interactive()->query_name());

	o = previous_object();

	if (o)
	    log_file(LOG_REDUCE_HP, " " + file_name(o) + ", " +
		     o->short () + " (" + creator(o) + ")\n");
	else
	    log_file(LOG_REDUCE_HP, " ??\n");
    }	
#endif
    set_hp(hit_points + hp);

}

/*
 * Function name:   reduce_hit_point
 * Description:     Reduce the number of hitpoints with a few.
 * Arguments:       dam: The number of damage hitpoints.
 */
public int
reduce_hit_point(int dam) 
{
    PROFILE("reduce_hit_point");
    heal_hp(-dam); 
}


/*
 * Function name:   query_max_mana
 * Description:     Calculates that maximum of mana points that a living
 *                  can get.
 * Returns:         The maximum.
 */
public int
query_max_mana()
{
    PROFILE("query_max_mana");
    return query_stat(SS_INT) * 10;
}

/*
 * Function name:   set_mana
 * Description:     Set the number of mana points that a player has. Mana
 *                  points are more commonly known as spellpoints. The
 *                  mana points can not bet set to more than the amount
 *                  that is calculated by query_max_mana.
 * Arguments:       sp: The new amount of mana points.
 */
void
set_mana(int sp)
{
    PROFILE("set_mana");
    mana = sp;

    if (mana < 0)
	mana = 0;

    if (mana > query_max_mana())
	mana = query_max_mana();
}

/*
 * Function name:   add_mana
 * Description:     Add a certain amount of mana points
 * Arguments:       sp: The number of mana points to change.
 */
void
add_mana(int sp)
{
    PROFILE("add_mana");
    set_mana(mana + sp);
}

/*
 * Function name:   query_mana
 * Description:     Gives the number of mana points that the living has
 * Returns:         The number of mana points.
 */
public int
query_mana()
{
    int n;
    PROFILE("query_mana");

    n = F_NUM_BEATS(time() - mana_time) / F_INTERVAL_BETWEEN_HEALING;
    if (n > 0)
    {
        set_mana(mana + n * F_MANA_HEAL_RATE);
        mana_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    }
    return mana;
}

/*
 * Function name:   query_max_fatigue
 * Description:     Calculates the maximum number of fatigue points that
 *                  the living can have.
 * Returns:         The maximum.
 */
public int
query_max_fatigue()
{
    PROFILE("query_max_fatigue");
    return query_stat(SS_CON) + 50;
}

/*
 * Function name:   add_fatigue
 * Description:     Add an amount of fatigue points to the current amount
 *                  of the living. Observe, negative argument makes a player
 *		    more tired.
 * Arguments:       f: the amount of change
 */
public void
add_fatigue(int f)
{
    PROFILE("add_fatigue");
    fatigue += f;
    if (fatigue < 0)
	fatigue = 0;
    if (fatigue > query_max_fatigue())
	fatigue = query_max_fatigue();
}

void
calculate_fatigue()
{
    int n, stuffed, tmpstuffed;

    n = F_NUM_BEATS(time() - fatigue_time) / F_INTERVAL_BETWEEN_HEALING;
    if (n > 0)
    {
        stuffed = query_stuffed();
        tmpstuffed = (stuffed + last_stuffed) / 2;
        add_fatigue(n *
            F_FATIGUE_FORMULA(tmpstuffed, query_prop(LIVE_I_MAX_EAT)));
        last_stuffed = stuffed;
        fatigue_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    } 

}

/*
 * Function name:   set_fatigue
 * Description:     Set the fatigue points of the living to a certain amount.
 * Arguments:       f: The amount to set.
 */
public void
set_fatigue(int f)
{
    PROFILE("set_fatigue");
    fatigue = 0;
    add_fatigue(f);
}

/*
 * Function name:   query_fatigue
 * Description:     Gives the amount of fatigue points of a living
 * Returns:         The number of fatigue points
 */
public int
query_fatigue()
{
    PROFILE("query_fatigue");
    calculate_fatigue();
    return fatigue;
}

/* 
 * Experience
 */

/* 
 * Function name:   modify_exp
 * Description:     This is a service function, to be used only by the mud
 *                  admins. You should never call it, for any reason
 *                  whatsoever.
 * Arguments:       e: Amount of exp to add, may be negative
 *                  battle: 0 = quest exp (== total exp),
 *			    1 = combat exp and total exp,
 *			    2 = combat exp without changing total exp.
 *                  msg: message stating why the change was made
 * Returns:	    1 upon success; 0 upon failure.
 */
public nomask int
modify_exp(int e, int battle, string msg)
{
    PROFILE("modify_exp");

    if (!this_interactive())
	return 0;

    if (!msg)
    {
        this_interactive()->catch_msg("You forgot to add a reason." +
            "Type \"sman modify_exp\" for more info.\n");
        return 0;
    }

    if (battle == 0 || battle == 1)
	exp_points += e;

    if (battle == 1 || battle == 2)
	exp_combat += e;

    /* Sanity checks */
    if (exp_points < 0)
        exp_points = 0;
    if (exp_combat < 0)
        exp_combat = 0;
    if (exp_points < exp_combat)
	exp_points = exp_combat;

    log_file("ADD_EXP", ctime(time()) + " on " +
	     this_object()->query_real_name() + " " +
             (battle == 0 ? "total           " :
             (battle == 1 ? "combat and total" : "combat          ")) + e +
             " (" + exp_points + "," + (exp_points - exp_combat) + ") by " +
             capitalize(this_interactive()->query_real_name()) + ", " + msg +
	     "\n");

    update_acc_exp();
}


/*
 * Function name:   add_exp
 * Description:     Add a certain amount of experience to the living. If the
 *                  battle-flag is true, use another formula to add the
 *                  experience points than with the flag false.
 * Arguments:       e: The amount of experience
 *                  battle: True if the experience was gained in battle.
 */
public void
add_exp(int e, int battle)
{
    float fact;
    PROFILE("add_exp");

    /* Exp tax are gathered in update_acc_exp()
     */

    if (battle && e > 0)
    {
	fact = itof(exp_combat) / itof(exp_points + 1);

#ifdef MAX_EXP_RED_FRIENDLY
	if (exp_points < MAX_EXP_RED_FRIENDLY && fact > MAX_COMB_EXP_RED)
	    fact = MAX_COMB_EXP_RED;
#endif
	
	e = e - ftoi(itof(e) * fact);
    
	exp_combat += e;
	exp_points += e;
	if (objectp(environment()))
	    SECURITY->bookkeep_exp(geteuid(environment()), 0, e);
    }
    else if (e < 0)
    {
	e = -e;
	if (exp_combat < e)
	    e = exp_combat;
	
	exp_combat -= e;
	exp_points -= e;
	if (objectp(environment()))
	    SECURITY->bookkeep_exp(geteuid(environment()), 0, -e);
    }
    else if (!battle && e > 0) /* Nonbattle positive xp, wee! */
    {
	exp_points += (QUEST_FACTOR * e) / 10;
	if (objectp(environment()))
	    SECURITY->bookkeep_exp(geteuid(environment()), e, 0);
    }
    
    /* This should never ever occur
     */
    if (exp_points < 0)
	exp_points = 0;

    update_acc_exp();
}

/*
 * Function name:   set_exp
 * Description:     Set the total number of experience points the living
 *                  currently has.
 * Arguments:       e: The total number of experience
 */
static void
set_exp(int e)
{
    PROFILE("set_exp");
    exp_points = e;
}

/*
 * Function name:   query_exp
 * Description:     Gives the total amount of experience of the living.
 *                  (Both combat and quest experience)
 * Returns:         The experience points.
 */
public int
query_exp()
{
    PROFILE("query_exp");
    return exp_points;
}

/*
 * Function name:   set_exp_combat
 * Description:     Set the amount of combat experience the living has.
 * Arguments:       e: The amount of combat experience
 */
static void
set_exp_combat(int e)
{
    PROFILE("set_exp_combat");
    exp_combat = e;
}

/*
 * Function name:   query_exp_combat
 * Description:     Gives the amount of combat experience the living has.
 * Returns:         The combat experience points
 */
public int
query_exp_combat()
{
    PROFILE("query_exp_combat");
    return exp_combat;
}

/*
 * Function name:   set_ghost
 * Description:     Change the living into a ghost or change the ghost-status
 *                  of a player.
 * Arguments:       flag: A flag to recognise the ghost-status. If flag is 0,
 *                        make the ghost a living again.
 */
set_ghost(int flag)
{
    string ostr;
    PROFILE("set_ghost");
    is_ghost = flag;
    if ((flag) && (!id(LD_GHOST)))
    {
	add_name(LD_GHOST);
    }
    else if ((!flag) && (id(LD_GHOST))) 
	remove_name(LD_GHOST);
}

/*
 * Function name:   query_ghost
 * Description:     Return the ghost-status of a living.
 * Returns:         0 if the living is not a ghost, the status otherwise.
 */
public int
query_ghost()
{
    PROFILE("query_ghost");
    return is_ghost;
}

/* 
 * Invisible
 */

/*
 * Function name:   set_invis
 * Description:     Change the visibility of the living
 * Arguments:       flag: If true turn the living invisible, else make the
 *                        living visible again.
 */
public void
set_invis(int flag)
{
    PROFILE("set_invis");
    if (!flag)
	add_prop(OBJ_I_INVIS, 0);
    else if (this_object()->query_wiz_level())
	add_prop(OBJ_I_INVIS, 100);
    else
	add_prop(OBJ_I_INVIS, flag);
}

/*
 * Function name:   query_invis
 * Description:     Gives back the current visibility of the living
 * Returns:         True if invisible
 */
public int
query_invis()
{
    PROFILE("query_invis");
    return this_object()->query_prop(OBJ_I_INVIS);
}

/*
 * Function name:   set_see_blood
 * Description:     Change the see blood flag, player will see fighting if
 *		    it is set.
 * Arguments:       flag
 */
public void
set_see_blood(int flag)
{
    PROFILE("set_see_blood");
    see_blood = flag;
}

/*
 * Function name:   query_see_blood
 * Description:     Gives back the blood watching status
 * Returns:         True if like ot watch fights
 */
public int
query_see_blood()
{
    PROFILE("query_see_blood");
    return see_blood; 
}

/*
 * Function name:   query_age
 * Description:     Gives the age of the living in heart_beats.
 * Returns:         The age.
 */
public int
query_age()
{
    int t;
    PROFILE("query_age");
    t = time();
    age_heart += F_NUM_BEATS(t - age_time);
    age_time = t;
    return age_heart;
}

/*
 * Whimpy mode.
 */

/*
 * Function name:   set_whimpy
 * Description:     Set the state of the whimpy flag, which makes livings
 *                  run away automatically if they are under a certain
 *                  amount of hitpoints.
 * Arguments:       flag: If true, set whimpy mode on.
 */
public void
set_whimpy(int flag)
{
    PROFILE("set_whimpy");
    is_whimpy = flag;
}

/*
 * Function name:   query_whimpy
 * Description:     Gives the state of the whimpy flag
 * Returns:         True if whimpy mode is on.
 */
public int
query_whimpy()
{
    PROFILE("query_whimpy");
    return is_whimpy;
}

/*
 * Alignment
 */

/*
 * Function name:   set_alignment
 * Description:     Set the amount of alignment points of the living.
 * Arguments:       a: The amount of points
 */
public void
set_alignment(int a)
{
    PROFILE("set_alignment");
    if (!intp(a))
	return;

    alignment = a;
}

/*
 * Function name:   query_alignment
 * Description:     Gives the current amount of alignment points of a living
 * Returns:         The amount.
 */
public int
query_alignment()
{
    PROFILE("query_alignment");
    return alignment;
}

/*
 * Gender
 */

/*
 * Function name:   set_gender
 * Description:     Set the gender code (G_MALE, G_FEMALE or G_NEUTER)
 * Arguments:       g: The gender code
 */
public void
set_gender(int g)
{
    PROFILE("set_gender");
    if (g == G_MALE || g == G_FEMALE || g == G_NEUTER)
	gender = g;
}

/*
 * Function name:   query_gender
 * Description:     Returns the gender code of the living.
 * Returns:         The code. (0 - male, 1 - female, 2 - netrum)
 */
public int
query_gender()
{
    PROFILE("query_gender");
    return gender;
}

/*
 * Appearance
 */

/*
 * Function name:   set_appearance
 * Description:     Set the appearance variable
 * Arguments:       a: The new value
 */
public void
set_appearance(int a)
{
    PROFILE("set_appearance");
    if (a < 0 || a > 99)
	a = random(99) + 1;
    appearance = a;
}

/*
 * Function name:   query_appearance
 * Description:     Gives the current value of the appearance variable.
 * Returns:         The appearance value
 */
public int
query_appearance()
{
    PROFILE("query_appearance");
    if (!appearance)
	set_appearance(0);
    return appearance;
}

/*
 * Opinion
 */

/*
 * Function name:   set_opinion
 * Description:     Set the value of the opinion variable
 * Arguments:       o: The new value.
 */
public void
set_opinion(int o)
{
    PROFILE("set_opinion");
    if (o < 0 || o > 100)
	o = 0;
    opinion = o;
}

/*
 * Function name:   query_opinion
 * Description:     Gives the current value of the opinion variable
 * Returns:         The opinion value
 */
public int
query_opinion()
{
    PROFILE("query_opinion");
    return opinion;
}

/*
 * Function name:   query_headache
 * Description:     Gives the amount of headache of a living.
 *                  Updates the value when queried.
 * Returns:         The amount.
 */

public int
query_headache()
{
    int n;
    PROFILE("query_headache");

    n = F_NUM_BEATS(time() - headache_time) / F_INTERVAL_BETWEEN_HEALING;

    if (n == 0)
        return headache;

    if (headache) 
    {
        headache -= F_HEADACHE_RATE * n;
        headache = MAX(0, headache);
        if (headache == 0)
        {
            tell_object(this_object(), LD_GONE_HEADACHE);
            set_max_headache(query_max_headache() / 2);   /* Funny is it not */
        }
    }
    headache_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    
    return headache;
}

/*
 * Function name:   query_intoxicated
 * Description:     Gives the level of intoxication of a living.
 * Returns:         The intoxication level.
 */
public int
query_intoxicated()
{
    int n;
    PROFILE("query_intoxicated");

    n = F_NUM_BEATS(time() - intoxicated_time ) / F_INTERVAL_BETWEEN_HEALING;

    if (n == 0)
        return intoxicated;

    if (intoxicated > 0) 
    {
        intoxicated -= n * F_SOBER_RATE;
        intoxicated = MAX(0, intoxicated);
        if (intoxicated == 0)
        {
            headache = query_max_headache();   
            tell_object(this_object(), LD_SUDDEN_HEADACHE);
        }
    }
    intoxicated_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    
    return intoxicated;
}

/*
 * Function name:   query_stuffed
 * Description:     Gives the level of stuffedness of a living.
 * Returns:         The level of stuffedness.
 */
public int
query_stuffed()
{
    int t, n;

    PROFILE("query_stuffed");
    n = F_NUM_BEATS(time() - stuffed_time) / F_INTERVAL_BETWEEN_HEALING;

    if (n == 0)
        return stuffed;

    stuffed -= F_UNSTUFF_RATE * n;
    stuffed = MAX(0, stuffed);

    stuffed_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    
    return stuffed;
}

/*
 * Function name:   query_soaked
 * Description:     Gives the level of soakedness of  a living.
 * Returns:         The level of soakedness.
 */
public int
query_soaked()
{
    int n;
    PROFILE("query_soaked");

    n = F_NUM_BEATS(time() - soaked_time) / F_INTERVAL_BETWEEN_HEALING;

    if (n == 0)
        return soaked;

    soaked -= F_UNSOAK_RATE * n;
    soaked = MAX(0, soaked);

    soaked_time += F_SECONDS_PER_BEAT * n * F_INTERVAL_BETWEEN_HEALING;
    
    return soaked;
}

/*
 * Function name:   set_intoxicated
 * Description:     Set the level of intoxication of a living.
 * Arguments:       i: The level of intoxication.
 */
static void
set_intoxicated(int i)
{
    calculate_hp();
    intoxicated = i;
}

/*
 * Function name:   set_headache
 * Description:     Set the level of headache of a living
 * Arguments:       i: The level of headache
 */
public void
set_headache(int i)
{
    PROFILE("set_headache");
    headache = i;
}

/*
 * Function name:   set_stuffed
 * Description:     Set the level of stuffedness of a living
 * Arguments:       i: The level of stuffedness
 */
static void
set_stuffed(int i)
{
    PROFILE("set_stuffed");
    calculate_fatigue();
    stuffed = i;
}

/*
 * Function name:   set_soaked
 * Description:     Set the level of soakedness of a living
 * Arguments:       i: The level of soakedness
 */
static void
set_soaked(int i)
{
    PROFILE("set_soaked");
    soaked = i;
}



/*
 * Learning preferences on stats
 */

/*
 * Function name:   set_learn_pref
 * Description:     Calculate learning preferences summing up to 100
 *                  from an array containing arbitrary numbers. 
 * Arguments:       pref_arr: An array with relative preference settings
 */
void
set_learn_pref(int *pref_arr)
{
    int sum, i, mval, il;

    PROFILE("set_learn_pref");
    mval = 100;
    
    if (sizeof(pref_arr) < SS_NO_EXP_STATS)
	pref_arr = allocate(SS_NO_STATS);
        /* Yes, the rest of the array is used for guild taxes */
    
    /* Take away the tax
    */
    for(i = SS_NO_EXP_STATS + 1; i < SS_NO_STATS; i++)
	mval -= learn_pref[i];

    if (mval < 1)
    {
	for(i = 0; i < SS_NO_EXP_STATS; i++)
	    learn_pref[i] = 0;
	return;
    }

    for(i = 0, sum = 0; i < SS_NO_EXP_STATS; i++)
	sum += pref_arr[i];

    for (i = 0; i < SS_NO_EXP_STATS; i++)
	learn_pref[i] =
	    (sum <= 0 ? mval / SS_NO_EXP_STATS : (mval * pref_arr[i]) / sum);
	
    for(i = 0, sum = 0; i < SS_NO_EXP_STATS; i++)
	sum += learn_pref[i];

    sum = mval - sum;
    i = 0;
    while (sum--)
    {
	learn_pref[i++]++;
	if (i >= SS_NO_EXP_STATS)
	    i = 0;
    }
}

/*
 * Function name:   query_learn_pref
 * Description:     Return one or all values of the learn preferences, this
 *		    includes the 'guildtax' learn_prefs of race, occup, layman
 * Arguments:       Index of learn_pref or -1
 * Returns:         learn_pref value if arg >= 0, 
 *                  entire learn_pref array if arg < 0
 */
public mixed
query_learn_pref(int stat)
{
    PROFILE("query_learn_pref");
    if (stat < 0) return learn_pref;

    if (stat < 0 || stat >= SS_NO_STATS)
	return -1;

    return learn_pref[stat];
}

/*
 * Function name:   set_guild_pref
 * Description:     Sets the guild tax/learn_pref for a specific guild.
 * Arguments:       guildstat: SS_RACE / SS_OCCUP / SS_LAYMAN
 *		    tax: taxrate for guild (in %)
 */
public void
set_guild_pref(int guildstat, int tax)
{
    PROFILE("set_guild_pref");
    if (guildstat >= SS_NO_EXP_STATS && 
	guildstat < SS_NO_STATS &&
	tax >= 0)
	learn_pref[guildstat] = tax;
}

/*
 * Function name:   set_acc_exp
 * Description:     Set the accumulated experience for each of the stats
 * Arguments:       stat: The stat to set
 *                  val:  The amount of experience to set the stat to
 * Returns:         0
 */
static int
set_acc_exp(int stat, int val)
{
    PROFILE("set_acc_exp");
    if (stat < 0 || stat >= SS_NO_STATS || val < 0)
	return 0;

    acc_exp[stat] = val;
}  

/*
 * Function name:   query_acc_exp
 * Description:     Get the accumulated experience points for a given stat.
 * Arguments:       stat: The stat to check
 * Returns:         The amount of experience belonging to the stat.
 */
public int
query_acc_exp(int stat)
{
    PROFILE("query_acc_exp");
    if (stat < 0 || stat >= SS_NO_STATS)
	return -1;

    return acc_exp[stat];
}

/*
 * Function name:   set_skill
 * Description:     Set a specific skill to a specific value.
 * Arguments:       skill: The skill-number to set
 *                  val:   The value to set the skill to.
 * Returns:         True is successfull, else 0.
 */
int
set_skill(int skill, int val)
{
    PROFILE("set_skill");
    if (!mappingp(skillmap))
	skillmap = ([]);

    if (!intp(skill))
	return 0;

    skillmap[skill] = val;
    return 1;
}

/*
 * Function name: set_skill_extra
 * Description:   This is the function to call if you have an object that wants
 * 		  to temporarily change the skill of someone. Perhaps some
 *		  grappling hooks to help climbing skill, or a fumble spell to
 *		  lower fighting skills?
 * Arguments:	  skill - Number of skill
 *		  val   - The new val of the extra variable
 */
public void
set_skill_extra(int skill, int val)
{
    PROFILE("set_skill_extra");
    skill_extra_map[skill] = val;
}

/*
 * Function name: query_skill_extra
 * Description:	  Query how much extra skill (or less) someone has in a particular
 *		  skill.
 * Arguments:     skill - What skill to query
 * Returns:	  The extra modifying value
 */
public int
query_skill_extra(int skill)
{
    PROFILE("query_skill_extra");
    return skill_extra_map[skill];
}

/*
 * Function name:   remove_skill
 * Description:     Remove a specific skill from a player
 * Arguments:       skill: The skill number to remove
 */
void
remove_skill(int skill)
{
    PROFILE("remove_skill");
    if (mappingp(skillmap))
	skillmap = m_delete(skillmap, skill);
}

/*
 * Function name:   query_base_skill
 * Description:	    Gives the value of a specific skill. If there is need to
 *		    know the true skill of the player call this since it is
 *		    unshadowable.
 * Arguments:       skill: The number of the skill to check
 * Returns:	    The true value of the skill
 */
nomask int
query_base_skill(int skill)
{
    PROFILE("query_base_skill");
    if (!mappingp(skillmap))
	return 0;

    return skillmap[skill];
}

/*
 * Function name:   query_skill
 * Description:     Gives the value of a specific skill.
 * Arguments:       skill: The number of the skill to check
 * Returns:         The value of the skill
 */
public int
query_skill(int skill)
{
    if (!mappingp(skillmap))
	return 0;

    return skillmap[skill] + skill_extra_map[skill];
}

/*
 * Function name:   query_all_skill_types
 * Description:     Gives list of all current skills != 0
 * Returns:         an array with all skill-values
 */
public int *
query_all_skill_types()
{
    PROFILE("query_all_skill_types");
    if (!mappingp(skillmap))
	return 0;
    return m_indexes(skillmap);
}

/*
 * Function name:   query_scar
 * Description:     Gives the scar bitmask of the living
 * Returns:         The scar bitmask
 */
public int
query_scar()
{
    PROFILE("query_scar");
    return scar;
}

/*
 * Function name:   set_scar
 * Description:     Set the scar bitmask of the living
 * Arguments:       s: The scar bitmask
 */
public void
set_scar(int s)
{
    PROFILE("set_scar");
    scar = s;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */

 /*************************************************************************
 * 
 * Command soul routines.
 *
 */


/*
 * Function name:   add_cmdsoul
 * Description:	    Add a command soul to the list of command souls. Note
 *                  that adding a soul is not enough to get the actions
 *                  added as well. You should do player->update_hooks()
 *                  to accomplish that.
 * Arguments:       soul: String with the filename of the command soul.
 * Returns:         1 if successfull,
 *                  0 otherwise.
 */
nomask public int
add_cmdsoul(string soul)
{
    PROFILE("add_cmdsoul");
    if (query_wiz_level())
    {
	if (geteuid(previous_object()) != geteuid(this_object()) &&
	    geteuid(previous_object()) != (string)SECURITY->get_root_uid())
	    return 0;
    }
    if (!((int)soul->query_cmd_soul()))
	return 0;

    /*
     * There can only be one!
     */
    remove_cmdsoul(soul);

    if (!sizeof(cmdsoul_list))
	cmdsoul_list = ({ soul });
    else
	cmdsoul_list += ({ soul });
    return 1;
}

/*
 * Function name:   remove_cmdsoul
 * Description:	    Remove a command soul from the list.
 * Arguments:       soul: De filename of the soul to remove
 * Returns:         1 if successfull,
 *                  0 otherwise.
 */
nomask public int
remove_cmdsoul(string soul)
{
    int index;

    PROFILE("remove_cmdsoul");
    if (query_wiz_level())
    {
	if (geteuid(previous_object()) != geteuid(this_object()) &&
	    geteuid(previous_object()) != (string)SECURITY->get_root_uid())
	    return 0;
    }

    if ((index = member_array(soul, cmdsoul_list)) < 0)
	return 0;

    cmdsoul_list = exclude_array(cmdsoul_list, index, index);
    return 1;
}

/*
 * Function name:   update_cmdsoul_list
 * Description:	    Update the list of command souls
 * Arguments:       souls: The new filenames
 */
nomask void
update_cmdsoul_list(string *souls)
{
    PROFILE("update_cmdsoul_list");
    cmdsoul_list = souls;
}

/*
 * Function name:   query_cmdsoul_list
 * Description:	    Give back the array with filenames of command souls.
 * Returns:         The command soul list.
 */
nomask public string *
query_cmdsoul_list()
{
    PROFILE("query_cmdsoul_list");
    if (SECURE_ARRAYS)
	return slice_array(cmdsoul_list, 0, sizeof(cmdsoul_list));
    else 
	return cmdsoul_list; 
}

/*************************************************************************
 * 
 * Tool soul routines.
 *
 */

/*
 * Function name:   add_toolsoul
 * Description:	    Add a tool soul to the list of tool souls. Note that
 *                  adding a soul is not enough to get the actions added
 *                  as well. You should do player->update_hooks() to
 *                  accomplish that.
 * Arguments:       soul: String with the filename of the tool soul.
 * Returns:         1 if successfull,
 *                  0 otherwise.
 */
nomask public int
add_toolsoul(string soul)
{
    PROFILE("add_toolsoul");
    if (!((int)SECURITY->query_wiz_level(geteuid(this_object()))))
	return 0;

    if (!((int)soul->query_tool_soul()))
	return 0;

    if (geteuid(previous_object()) != geteuid(this_object()) &&
	geteuid(previous_object()) != (string)SECURITY->get_root_uid())
	return 0;

    /*
     * There can only be one!
     */
    remove_toolsoul(soul);

    if (!sizeof(tool_list))
	tool_list = ({ soul });
    else
	tool_list += ({ soul });
    return 1;
}

/*
 * Function name:   remove_toolsoul
 * Description:	    Remove a tool soul from the list.
 * Arguments:       soul: De filename of the tool soul to remove
 * Returns:         1 if successfull,
 *                  0 otherwise.
 */
nomask public int
remove_toolsoul(string soul)
{
    int index;
    PROFILE("remove_toolsoul");

    if (geteuid(previous_object()) != geteuid(this_object()) &&
	geteuid(previous_object()) != (string)SECURITY->get_root_uid())
	return 0;

    if ((index = member_array(soul, tool_list)) < 0)
	return 0;

    tool_list = exclude_array(tool_list, index, index);
    return 1;
}

/*
 * Function name:   update_tool_list
 * Description:	    Update the list of tool souls
 * Arguments:       souls: The new filenames
 */
nomask static void
update_tool_list(string *souls)
{
    PROFILE("update_tool_list");
    tool_list = souls;
}

/*
 * Function name:   query_tool_list
 * Description:	    Give back the array with filenames of tool souls.
 * Returns:         The tool soul list.
 */
nomask public string *
query_tool_list()
{
    PROFILE("query_tool_list");
    if (SECURE_ARRAYS)
	return slice_array(tool_list, 0, sizeof(tool_list));
    else
	return tool_list; 
}
