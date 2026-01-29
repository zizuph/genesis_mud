/*
 * A standard draconian.
 *
 * By Rastlin
 *
 * Altered 23/8/98 by Arman who disabled the
 * alternate hit messages and gave them racial
 * adjectives.
 *
 * Altered 1/11/98 by Milan
 * it is now possible to call directly after cloning arm_draconian()
 * without danger that it would be called twice
 *
 * 27/11/98 by Milan
 * Aded smart fighting routine (kill weakest first)
 *
 * 2/9/00 by Stralle
 * Added more easily configurable weapon and armour selecting routine
 *
 * 17/09/02 by Cotillion
 * Brought down eval cost at creation
 */
#pragma strict_types
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "draconian.h"
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <const.h>
#include <options.h>

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/equip";

static int gType;                  /* The type of the Draconian */
static string gColor = "blue";     /* Color of the dragonarmy */
static int gSmartFighting = 0;     /* smart fighting strategy */
static int gSmartFightingCounter = ROUNDS_INBETWEEN_SMART_FIGHTING;
static int arm_draconian_called = 0;

public void set_default_long();
static void set_draconian_acts();
public void arm_draconian();
static void do_smart_fighting();
public string query_color();
public void when_met(object pl);
public void delayed_draconian();

string
query_dragonarmy_division()
{
    return query_color();
}

public varargs void
set_smart_fighting(int smart = 1)
{
    gSmartFighting = smart;
}

public int
query_smart_fighting()
{
    return gSmartFighting;
}

void
init_living()
{
    ::init_living();
    if (interactive(TP))
        set_alarm(0.5, 0.0, &when_met(TP));
}

/*
 * Function name: create_draconian
 * Description:
 */
public void
create_draconian()
{
    
}

/*
 * Function name: create_monster
 * Description:
 */
nomask public void
create_krynn_monster()
{
    setuid();
    seteuid(getuid());

    set_race_name("draconian");
    add_name("draconian");

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "transmutation" }) );
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    set_gender(G_NEUTER);
    
    create_draconian();
    
    if (!query_long())
        set_default_long();
    
    if (!sizeof(query_prospective_team()))
        set_pick_up_team(({"aurak", "sivak", "bozak", "kapak", "baaz"}));
    
    set_alarm(0.0, 0.0, &delayed_draconian());
}

/*
 * We do some setup here to lower eval cost at creation.
 */
public void
delayed_draconian()
{
    set_draconian_acts();
    arm_draconian();
    
    if (query_color())
    {
        if (!LOAD_ERR(DSOUL(query_color())))
        {
	    add_cmdsoul(DSOUL(query_color()));
	    update_hooks();
	}
    }
}

/*
 * Function name: set_draconian_type
 * Description:   Set the draconian type.
 * Arguments:     type - The type of the draconian
 */
public void
set_draconian_type(int type)
{
    gType = type;
}

public void
set_color(string str)
{
    gColor = str;
    all_inventory(TO)->set_color(gColor);
}

public string
query_color()
{
    return gColor;
}

public string
query_draconian_type()
{
    return DRAC_RACE[gType];
}

/*
 * Function name: query_draconian_level
 * Description:   Calculate the level
 * Returns:       The level
 */
public int
query_draconian_level()
{
    int t;

    t = (query_average_stat() / 10) - 1;

    return max(min(t, 15), 0);
}

public void
set_default_long()
{
    string str;
    string drac_type_adj;

// Original long description was way too long. I've reduced it.
// Arman, Sept 2018

/*
    str = "A draconian is a scaly humanoid, and this one is " +
        "flicking a forked tongue from its fang-studded mouth. It's " +
        "as tall as a man, and it walks on powerful hindlegs. Each leg " +
        "bears a talon. Rounding out the monstrosity are its other " +
        "noticeable features: studded forepaws, reptilian eyes, and a " +
        "baleful glare.\n";
*/

    str = "Before you stands a scaly humanoid with a " +
        "fang-studded snout and a short stubby tail. ";

    switch(gType)
    {
    case BAAZ:
        str += "This particular draconian stands as tall as a man " +
            "and has small leathery wings that stretch awkwardly " +
            "from the shoulders. It has a narrow reptilian face with " +
            "glistening eyes that dart about. ";
        break;
    case KAPAK:
        str += "This draconian stands as tall as a man and has a mean " +
            "reptilian face, which looks sly and cunning. It has leathery " +
            "wings that stretches awkwardly from the shoulders. ";
        break;
    case BOZAK:
        str += "This draconian stands taller than a man and has a cruel " +
            "broad reptilian face with eyes baleful and intelligent. " +
            "Bronze-hued leathery wings stretch from its shoulders. ";
        break;
    case SIVAK:
        str += "This draconian stands almost nine feet in height and " +
            "has an ugly reptilian face, with black beady eyes " +
            "as dark and corrupt as its soul. Large strong wings " +
            "extend from its shoulders, indicating it is a capable " +
            "flier. ";
        break;
    case AURAK:
        str += "Standing seven feet tall with thin limbs and no wings, " +
            "you could be fooled to think this golden-scaled draconian was " +
            "anything other than the most powerful of dragonmen and a most " +
            "accomplished magic user. ";
        break;
    }

    switch (gType)
    {
    case BAAZ:
        drac_type_adj = "narrowfaced";
        break;
    case KAPAK:
        drac_type_adj = "meanfaced";
        break;
    case BOZAK:
        drac_type_adj = "broadfaced";
        break;
    case SIVAK:
        drac_type_adj = "uglyfaced";
        break;
    case AURAK:
        drac_type_adj = "evilfaced";
        break;
    }

    switch (query_draconian_level())
    {
    case 1..2:
        str += "It doesn't look very threatening.";
        break;
    case 3..4:
        str += "It looks threatening.";
        break;
    case 5..6:
        str += "You better not mess with it.";
        break;
    case 7:
        str += "It looks like this draconian is a good fighter.";
        break;
    case 8..9:
        str += "It looks like it is a very good fighter.";
        break;
    case 10..11:
        str += "It seems to be able to kill you easily.";
        break;
    case 12..13:
        str += "It looks like it's an extremely good fighter.";
        break;
    case 14..15:
        str += "It looks like it can crush you in no time!";
        break;
    }

    set_adj( ({ drac_type_adj, GET_DRAC_ADJ(DRAC_ADJS2) }) );
    set_long(str + "\n");
}

public string
query_race()
{
    return "draconian";
}

public string
query_race_name()
{
    if (TP->test_bit("Krynn", 2, 6))
        return DRAC_RACE[gType];

    return "draconian";
}

/*
 * Function name: set_draconian_acts
 * Description:   Give the draconian a few add_act's
 */
static void
set_draconian_acts()
{
    string *acts = DRAC_ACTS;
    int count, size, nr;

    set_act_time(random(15) + 7);

    size = sizeof(acts);

    while (count < 7 && size)
    {
        /* Randomly add 7 of the available acts, or if less than 7,
         * that number
         */
        nr = random(size);
        add_act(acts[nr]);
	acts = exclude_array(acts, nr, nr);
	size--; count++;
    }

    set_cact_time(random(13) + 5);
    add_cact("emote snarls: You really think you can defeat me?");
    add_cact("emote grunts: Ahhh, now I can test my battle skill.");
    add_cact("emote snarls: I didn't even feel that!");
    add_cact("emote snarls: Is that all you can do?");
    add_cact("emote whispers: Don't take it personally but I'll kill you.");
    add_cact("grin");
}

/*
 * Function name: set_draconian_alignment
 * Description:   Calculate the alignment of the draconian.
 */
public void
set_draconian_alignment()
{
    int i;

    i = query_average_stat();
    i = i * i / 10;
    set_alignment((i > 950) ? (-1000) : (-i - 50));
    set_knight_prestige(i + 100);
}

/* Function name: when_met
 * Description:   Gets called whenever we meet a living. Depending on
 *                DRAC_MEET we do different things towards individuals
 *                of certain guilds.
 * Arguments:     object pl - the living
 */
public void
when_met(object pl)
{
    mapping gMeet = DRAC_MEET;
    string *arr, cmd;
    int i, size;

    if ((!objectp(pl)) || (E(TO) != E(pl)))
        return;
    
    set_this_player(pl);
    
    if (!interactive(pl))
    {
	init_team_pickup();
	return;
    }

    if (random(3))
	return;

    if ((!CAN_SEE_IN_ROOM(TO)) || (!CAN_SEE(TO, pl)))
        return;

    if (!pointerp(arr = gMeet[pl->query_guild_name_occ()]))
        arr = gMeet["*"];

    for (i = 0, size = sizeof(arr) ; i < size ; i++)
    {
        cmd = sprintf(arr[i], pl->query_real_name());
        command(cmd);
    }
}

/*
 * Equip Related Stuff
 */

public string
color_unique(string item, int limit, string alternative)
{
    object ob, *obs;
        
    if (!objectp(ob = find_object(item)))
        return item;
    
    obs = object_clones(ob);
    obs -= filter(obs, &->query_prop(OBJ_I_BROKEN));

    /* We want the limits to be color specific */
    if (gColor && ob->query_prop(OBJ_I_COLORABLE) && ob->query_color())
        obs = filter(obs, &operator(==)(gColor) @ &->query_color());
    
    if (sizeof(obs) < limit)
        return item;
    
    return alternative;
}

public string
unique_check(string str)
{
    string new;
    mapping limits = LIMITS;

    if (!pointerp(limits[str]))
	return str;
    
    while (limits[str])
    {
	new = color_unique(str, limits[str][0], limits[str][1]);
        
        if (new == str)
	    return str;
	str = new;
    }
    return str;
}

/* Function name: equip_draconian
 * Description  : Recurses over an array of the form ({ "element", 20%, ..
 *                And picks a good item to return. Supports unlimited depth.
 * Arguments:     mixed *arr - an array of the levelbased weapons
 *                             or armours as defined in draconian.h
 */
mixed *
equip_draconian(mixed *arr)
{
    int i, size, sum, ran;
    mixed ret;

    size = sizeof(arr);
    if (!size)
	return ({ });

    /* Shortcut for non percentage stuff */
    if (size < 2 || !intp(arr[1]))
    {
	ret = ({ });
	while (size--)
	{
	    if (pointerp(arr[size]))
		ret += equip_draconian(arr[size]);
	    if (stringp(arr[size]))
		ret += ({ unique_check(arr[size]) });
	}
	return ret;
    }
    
    /* Must be 100 */
    ran = random(100);
    i = size;
    while (i)
    {
	i -= 2;

	sum += arr[i + 1];
	if (sum >= ran)
	{
	    if (pointerp(arr[i]))
		return equip_draconian(arr[i]);
	    if (stringp(arr[i]))
		return ({ unique_check(arr[i]) });
	}
    }
    return ({ });
}    


/*
 * Function name: arm_draconian
 * Description:   Clone and set up armours and weapons for the
 *                draconian.
 */
public void
arm_draconian()
{
    string *wep, *arm;
    object *obs;
    mixed weapons, armours;
    int i, level;

    if (arm_draconian_called)
        return;
    
    /* No point in initilizing these rather complex variables in
     * the definition if only to break out.
     */
    weapons = WEAPONS;
    armours = ARMOURS;

    level = query_draconian_level();

    arm_draconian_called = 1;
 
    /*
     * Relatively Simple Loops, loop downwards until we get >= level. 
     */
    i = sizeof(armours);
    while (i && !sizeof(arm))
    {
	i -= 2;
	if (level >= armours[i])
	{
            arm = equip_draconian(armours[i + 1]);
	    arm -= ({ "" });
        }
    }

    i = sizeof(weapons);
    while (i && !sizeof(wep))
    {
	i -= 2;
	if (level >= weapons[i])
	{
            wep = equip_draconian(weapons[i + 1]);
	    wep -= ({ "" });
        }
    }
    

    /* wep + arm order is important, better to be without shield than weapon */
    obs = equip(wep + arm);
    obs->set_color(gColor);
}

/*
 * Function name: stat_living
 * Description:   A mask to the original stat_living
 *                To get the info about army type and level.
 * Returns:       A nice looking string
 */
public string
stat_living()
{
    string str = ::stat_living();

    str += sprintf("Army:  %-6s  Level:    %-3d\n", C(gColor),
        query_draconian_level());

    return str;
}

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object victim)
{
    return 0;
}


/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
public int
special_attack(object victim)
{
    /* 
     * Only do smart fighting every DEFINE combat round if enabled.
     */
    if (gSmartFighting && !gSmartFightingCounter--)
    {
        gSmartFightingCounter = ROUNDS_INBETWEEN_SMART_FIGHTING;
        do_smart_fighting();
    }   
    
    if (random(5))
        return 0;

    return special_draconian_attack(victim);
}

/*
 * Function name: do_draconian_die
 * Description:   REDEFINE THIS FUNCTION.
 *                It is called from do_die().
 * Arguments:     killer - The one who killed me.
 */
public void
do_draconian_die(object killer)
{
}

/*
 * Function name: do_die
 * Description:   Another one bits the dust..:)
 * Arguments:     obj - The killer
 */
public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;

    if (query_alignment() > 0)
        log_file("drac",file_name(TO) + "\n",100000);
    do_draconian_die(killer);
    ::do_die(killer);
}

/*
 * Draconian Personality
 */

/*
 * Function Name: action_insult
 * Description  : Should make the npc insult the target.
 *                The insult should depend upon the characther
 *                of the npc.
 */
public void
action_insult(object attacker)
{
    if (attacker && (E(attacker) == E(TO)) &&
	CAN_SEE(this_object(), attacker))
    {
	/* Milan targeted messages and increased random so they are 
	 * not always produced.
	 */
        switch(random(10))
        {
        case 0:
            command("say to "+OB_NAME(attacker)+" You'll pay for that!");
            break;
        case 1:
            command("growl "+OB_NAME(attacker));
            break;
        case 2:
            command("snarl "+OB_NAME(attacker));
            break;
        case 3:
            command("shout Die like the gully-dwarf you are!");
            break;
        case 4:
            command("say to "+OB_NAME(attacker)+" I will kill you!");
            break;
        }

        action_attack(attacker);
    }
}

/*
 * Function name: help_friend
 * Description:   Help my friend
 * Arguments:     attacker - The attacker
 */
void
assist_friend(object friend, object attacker)
{
    if (attacker && !TO->query_attack() &&
        present(attacker, E(TO)) && CAN_SEE(TO, attacker))
    {
        command("shout You scum stop fighting my friend, you puny " +
            attacker->query_race_name() + "!");
        action_assist(friend);
    }
}

/*
 * Function name: hook_friend_attacked
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *		  attacker - The attacker
 */
public void
hook_friend_attacked(object attacked, object attacker)
{
    if (TO->query_attack())
        return;
    
    set_alarm(itof(random(3)), 0.0, &assist_friend(attacked, attacker));
}

public void
hook_friend_attack(object friend, object enemy)
{
    if (TO->query_attack())
        return;
    
    set_alarm(itof(random(3)), 0.0, &assist_friend(friend, enemy));
}

/*
 * Function Name: hook_attacked
 * Description  : Called when someone attacks me.
 */
public void
hook_attacked(object attacker)
{
    if (TO->query_attack())
        return;
    
    set_alarm(itof(random(2)), 0.0, &action_insult(attacker));
}



static void
do_smart_fighting()
{
    object *drac, *enemy, target;
    int hp, size;

    enemy = ({ });
    
    if (!CAN_SEE_IN_ROOM(TO) || random(3))
        return;
    
    drac = filter(all_inventory(E(TO)), 
        &operator(==)("draconian") @ &->query_race_name());
    
    size = sizeof(drac);
    
    while (size--)
        enemy |= drac[size]->query_enemy(-1);
    
    enemy = filter(enemy, &operator(==)(E(TO)) @ environment);
    enemy = filter(enemy, &->check_seen(TO));
    

    size = sizeof(enemy);

    while (size--)
    {
        if (!hp || 
            (hp > (enemy[size]->query_hp() * 100) / 
                enemy[size]->query_max_hp()))
        {
            target = enemy[size];
            hp = (target->query_hp() * 100) / target->query_max_hp();
        }
    }
    
    if (target && (query_attack() != target))
    {
        action_attack(target);
	    
        if (sizeof(drac))
        {
            command("shout Kill this one first!");
            command("point at " + OB_NAME(target));
            drac->action_attack(target);
        }
    }
}

