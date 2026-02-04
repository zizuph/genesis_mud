/* By Novo May - June 2008
 *
 * Modifications:
 *  Lilith, 16 Nov 2008
 *    -removed quickness by setting max_borrowed_quickness & max_used_quickness to 0;
 *  Balance Team, February 2009
 *    - moved resistance and skill drain to object
 *  Petros, August 2009
 *    - food and drinks have no effect. Actual blood loss will occur if
 *      vampire eats food or drinks drink.
 *  Petros, September 2009
 *    - VOTE_MANAGER->login_player was passing shadow object rather than
 *      the person. This caused voting to fail.
 */
 
inherit "/std/guild/guild_occ_sh";
inherit "/lib/commands";

#include <files.h>
#include "../guild.h"
#include "../voptions.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include "options.c"
#include "stalk.c"
#include "move.c"
#include "drain.c"
#include "blood.c"
#include "incognito.c"
#include "combat.c"
#include "sunlight.c"
#include "heal.c"
#include "desc.c"
#include "death.c"
#include "titles.c"

#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <stdproperties.h> /* For standard properties */
#include <macros.h> /* For macros */
#include <filter_funs.h> /* For easy filters */
#include <std.h> /* For easy filters */

#define OLD_VAMP_CMDSOUL "/d/Emerald/common/guild/vamp/soul/vamp_soul"
#define OLD_CM_CMDSOUL "/d/Emerald/common/guild/vamp/soul/cm_soul"
#define OLD_ABL_CMDSOUL "/d/Emerald/common/guild/vamp/soul/abilities"
#define OLD_VAMP_SHADOW "/d/Emerald/common/guild/vamp/shadow/vamp_sh"

#define VAMP_CMDSOUL        (SOUL_DIR+"occ_soul")
#define FOOD_DRINK_SHADOW   (SHADOW_DIR + "food_drink_shadow")

object * Dominated=({ });

void
log()
{
    send_debug_message("terel_vamp_shadow", "Created: " + (calling_object(-1) ? file_name(calling_object(-1)) : "unkown")); 
}

mixed foo = log();

public nomask object query_manager()
{
    setuid();
    seteuid(getuid());
    LOAD_ERR(OCC_MANAGER);
    return find_object(OCC_MANAGER);
}

object
query_vamp_shadow()
{
    return this_object();
}

/* 
 * Function name: query_sire
 * Description:   Get the name of the sire of this vampire
 * Returns:       This vampire's sire's name.
 */
string
query_sire()
{
    setuid();
    seteuid(getuid());
  
    return lower_case(query_manager()->query_sire(SW));
}


public string
query_guild_name_occ()
{
    return OCC_GUILD_NAME;
}

public string
query_guild_name_lay()
{
    // Vamps are Race, Occ, Lay
    return query_guild_name_occ();
}

public string
query_guild_name_race()
{
    // Vamps are Race, Occ, Lay
    return query_guild_name_occ();
}

public string
query_guild_style_occ()
{
    return OCC_GUILD_STYLE;
}

public string
query_guild_leader_occ()
{
    return query_manager()->is_covenmaster(QSW);
}

public int query_vamp_covenmaster()
{
    return query_manager()->is_covenmaster(QSW);
}

public int query_vamp_generation()
{
    return query_manager()->query_generation(QSW);
}

public int
query_guild_not_allow_join_occ(object player, string type, string style,
			       string name)
{
    if (type=="occupational" || type=="race" || type=="layman" )
    {
        notify_fail("Your path is already defined.\n");
        return 1;
    }
    return 0;
}

mixed
query_guild_trainer_occ()
{
    return ({ 
            LIB_DIR+"occ_train",
           });
}

public int
query_guild_tax_occ()
{
    return OCC_GUILD_TAX;
}

public int
query_guild_tax_race()
{
    return OCC_GUILD_TAX_2;
}

public int
query_guild_tax_lay()
{
    return OCC_GUILD_TAX_3;
}

public string
query_guild_style_lay()
{
    return "ranger";
}

public string
query_guild_style_race()
{
    return "ranger";
}

public int query_base_vamp_stat()
{
    return QSW->query_stat(SS_OCCUP);
}

public int query_vamp_stat()
{
    int val=query_base_vamp_stat();
    if (QSW)
    {
        val-=query_sunlight_level(environment(QSW));
    }
    val-=query_blood_modifier();
    return val;
}

public int query_vampire()
{
    return 1;
}

string
full_adverb(string str)
{
    string adverb;

    setuid();
    seteuid(getuid());

    if (strlen(adverb = (OBJ_DIR+"adverbs")->full_adverb(str)))
    {
        return adverb;
    }

    return QSW->full_adverb(str);
}

/*
 * Function:    add_food_drink_shadow
 * Description: This adds the food/drink shadow to the food item
 *              so that the special effects from the food never
 *              occur.
 */
public void
add_food_drink_shadow(object item)
{
    if (!objectp(item))
    {
        return;
    }
        
    if (IS_FOOD_OBJECT(item) || IS_DRINK_OBJECT(item))
    {
        if (!item->has_food_drink_shadow())
        {
            setuid();
            seteuid(getuid());
            clone_object(FOOD_DRINK_SHADOW)->shadow_me(item);
        }
    }
}

public int
drink_alco(int strength, int ask)
{
    int can_consume;
    int vamp_strength;
    object item;
    
    vamp_strength = strength * 3;    
    if (!ask)
    {
        // Drinking alcohol will cause a vampire to lose blood
        int blood_loss = max(1, vamp_strength / 500);
        add_blood(-blood_loss);
    }
    
    can_consume = QSW->drink_alco(vamp_strength, 1); // ask only
    if (can_consume && objectp(item = calling_object())
        && IS_DRINK_OBJECT(item))
    {
        add_food_drink_shadow(item);
    }
    
    return can_consume;
}

public int
drink_soft(int strength, int ask)
{
    int can_consume;
    int vamp_strength;
    object item;
    
    vamp_strength = strength * 3;    
    if (!ask)
    {
        // Drinking liquids will cause a vampire to lose blood
        int blood_loss = max(1, vamp_strength / 500);
        add_blood(-blood_loss);
    }
    
    can_consume = QSW->drink_soft(vamp_strength, 1); // ask only
    if (can_consume && objectp(item = calling_object())
        && IS_DRINK_OBJECT(item))
    {
        add_food_drink_shadow(item);
    }
    
    return can_consume;
}

public int
eat_food(int strength, int ask)
{
    int can_consume;
    int vamp_strength;
    object item;
    
    vamp_strength = strength * 3;    
    if (!ask)
    {
        // Eating food will cause a vampire to lose blood
        int blood_loss = max(1, vamp_strength / 500);
        add_blood(-blood_loss);
    }
    
    can_consume = QSW->eat_food(vamp_strength, 1); // ask only
    if (can_consume && objectp(item = calling_object())
        && IS_FOOD_OBJECT(item))
    {
        add_food_drink_shadow(item);
    }
    
    return can_consume;
}

public void set_intoxicated(int i)
{
    //Do not set it
}

public object * query_dominated()
{
    Dominated=Dominated-({ 0 });
    return Dominated;
}

public void add_dominated(object obj)
{
    Dominated+=({ obj });
}

public void remove_dominated(object obj)
{
    Dominated-=({ obj });
}

/*
 * Function name: login_vampire
 * Description:   This is called only when a vampire logs in.
 */
static nomask void
login_vampire()
{
    mixed sire;
    object *vamps;
    string name, coven;
    int i;
    int time_logged_out;

    /* Notify other vampires of login */
    if (!IS_WIZ(QSW) && !IS_JR(QSW))
    {
        vamps = VAMPS(users());
        name = QSW->query_real_name();
        sire = query_sire();

        for (i = 0; i < sizeof(vamps); i++)
        {
            if (!vamps[i]->query_vamp_option(VOPT_NOTIFY_LOGIN))
    	    {
                continue;
	        }

            if (!IS_WIZ(vamps[i]) &&
                ((name == vamps[i]->query_sire()) ||
                (vamps[i]->query_real_name() == sire)))
	        {
                continue;
	        }

            tell_object(vamps[i], "Your sensitive mind detects " +
    	  	LANG_POSS(SW->query_name()) + " awakening.\n");
        }

    }
    QSW->set_guild_pref(SS_LAYMAN, query_guild_tax_lay());
    QSW->set_guild_pref(SS_RACE, query_guild_tax_race());
    setuid();
    seteuid(getuid());
    VOTE_MANAGER->login_player(QSW);
}

public void update_vamp_souls()
{
    if (!SECURITY_CHECK(SW))
    {
    	SECURITY_LOG(SW, "Illegal shadow.");
    	remove_guild_occ();
    	return;
    }
    if (query_manager()->is_covenmaster(QSW))
    {
        QSW->add_cmdsoul(SOUL_DIR+"cm_soul");
    }
    else
    {
        QSW->remove_cmdsoul(SOUL_DIR+"cm_soul");
    }
        
    string *list = query_shadow_who()->query_cmdsoul_list();

    QSW->add_cmdsoul(VAMP_CMDSOUL);
    VAMP_CMDSOUL->add_spells(QSW);

    for(int i=0; i<sizeof(list); i++)
    if((list[i] != VAMP_CMDSOUL))
    {
        query_shadow_who()->add_cmdsoul(list[i]);
    }
    QSW->update_hooks();
    
    string * shadows=QSW->query_autoshadow_list();
    
    if (!sizeof(shadows))
    {
        return;
    }
    
    if (shadows[sizeof(shadows)-1]!=SHADOW_DIR+"occ_shadow:")
    {
        //Reordering shadows - occ shadow works best when
        //It comes after the hair/eyes shadows
        QSW->remove_autoshadow(SHADOW_DIR+"occ_shadow:");
        QSW->add_autoshadow(SHADOW_DIR+"occ_shadow:");
    }
}

public void start_player()
{
    QSW->start_player();
    login_vampire();
    string news = (HELP_DIR + "news.help");

    if ((file_size(news) > 0) &&
        (file_time(news) >= QSW->query_login_time()))
    {
        set_alarm(2.0, 0.0, &(QSW)->catch_tell(
                "\n=============================================\n"+
                "  Your blood sings to you of new knowledge.\n"+
                "  Check \"help vampire news\" for updates.\n"+
                "=============================================\n\n"));
    }

}

public void start_vampire()
{
    QSW->add_prop(LIVE_I_UNDEAD,query_vamp_stat);

    if (environment(QSW))
    {
        QSW->add_prop(LIVE_I_SEE_DARK,
            QSW->query_prop(LIVE_I_SEE_DARK)+
            environment(QSW)->query_prop(VAMP_FREE_SEE_DARKNESS));
        QSW->add_prop(VAMP_FREE_SEE_DARKNESS,
            environment(QSW)->query_prop(VAMP_FREE_SEE_DARKNESS));
            
    }
    
    QSW->add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON,
        QSW->query_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON)+15);

    load_drains();
    load_disguises();
    init_vamp_options();

    QSW->add_subloc(HAIR_SUBLOC,TO);
    QSW->add_subloc(EYES_SUBLOC,TO);
    QSW->add_subloc(INCOGNITO_SUBLOC,TO);
    QSW->add_subloc(SKIN_SUBLOC,TO);
    set_alarm(itof(min(60,query_vamp_stat()*2)),0.0,reduce_blood);
    
    set_alarm(5.0,5.0,check_sunlight);
    // Set up the healing variables
    start_heal();
}

public void
init_occ_shadow(string arg)
{
    
    set_alarm(2.0,0.0,update_vamp_souls);
        
    start_vampire();    
}


varargs int
create_new_vamp(object who)
{
    int lay_stat=who->query_acc_exp(SS_LAYMAN);
    string sire=who->query_master();
    
    if (!sire)
    {
        return 0;
    }
    
    who->remove_bloodguard(1);
    
    int result=
    TO->shadow_me(who, "occupational", OCC_GUILD_STYLE, 
        OCC_GUILD_NAME, "");

    write_file(VAMP_JOIN_LOG,ctime(time())+ ":  "+
    who->query_real_name()+ " has attempted to join the Vampires.   "+
    "Result: " + (result==1 ? "success" : "failure") + "\n");

    if (result== 1)
    {
    	setuid();
    	seteuid(getuid());
        QSW->clear_guild_stat(SS_OCCUP);
        QSW->clear_guild_stat(SS_LAYMAN);
        QSW->set_guild_stat(SS_OCCUP,lay_stat);
        query_manager()->remove_member(QSW->query_real_name());
        query_manager()->add_member(QSW);
        query_manager()->set_scars(QSW, QSW->query_scar());
        query_manager()->set_sire(QSW, sire);
        add_blood(query_max_blood());            
    }

    return result;
}

varargs int
convert_vamp(object who)
{
   	setuid();
  	seteuid(getuid());
    int result=query_manager()->convert_member(who->query_real_name());

    write_file(VAMP_JOIN_LOG,ctime(time())+ ":  "+
        who->query_real_name()+ " has attempted to convert " +
        "guilds.  Result: " + 
        (result==1 ? "success" : "failure") + "\n");
    if (!result)
    {
        return 0;
    }

    int old_stat=who->query_acc_exp(SS_OCCUP);

    if (!who->remove_guild_occ())
    {
        return 0;
    }

    result=
    TO->shadow_me(who, "occupational", OCC_GUILD_STYLE, 
        OCC_GUILD_NAME, "");

    write_file(VAMP_JOIN_LOG,ctime(time())+ ":  "+
        who->query_real_name()+ " has attempted to add the new" +
        "shadow.  Result: " + 
        (result==1 ? "success" : "failure") + "\n");

    if (result)
    {
        QSW->remove_cmdsoul(OLD_VAMP_CMDSOUL);
        QSW->remove_cmdsoul(OLD_CM_CMDSOUL);
        QSW->remove_cmdsoul(OLD_ABL_CMDSOUL);
        QSW->set_guild_stat(SS_OCCUP,old_stat);
        //Convert some favor for being a vampire a while
        QSW->set_skill(VAMP_FAVOR,QSW->query_stat(SS_OCCUP));
        //Convert slash to savage
        QSW->set_skill(VAMP_SKILL_BITE,QSW->query_skill(132004));
        add_blood(query_max_blood());            
        QSW->set_default_start_location(QSW->query_def_start());

    }

    return result;
}


string
query_def_post()
{
    return ROOM_DIR+"library";
}

/*
 * Function name: query_guild_title_occ
 * Description:   This is called to get the guild title for introductions
 *                and such.
 * Returns:       The title.
 */
string
query_guild_title_occ()
{
    /* Update the title on occasion in case the vampire has gained a level
     * recently.
     */
    if (!random(30))
    {
        update_title();
    }

	if (query_vamp_option(VOPT_INTRO_TITLE))
	{
	    if (query_vamp_option(VOPT_INTRO_PTITLE))
	    {
		return query_full_vamp_title();
	    }
    
 	    return query_vamp_title();
	}
    
	if (query_vamp_option(VOPT_INTRO_PTITLE))
	{
	    return query_personal_title();
	}

    return "";
}


/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    VAMP_CMDSOUL->remove_spells(QSW);    
    ::remove_shadow();    
}

/* function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
static int
query_guild_keep_player(object player)
{
    // As of February 2010, the Vampyr guild has been closed.
    // We set an alarm to remove them
    set_alarm(1.0, 0.0, remove_vampire);
    return 1;
}

