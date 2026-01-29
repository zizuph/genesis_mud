/* /d/Faerun/guilds/vampires/shadows/vampires_sh_lay.c
 *
 * Guildshadow for Vampires of Faerun, Nerull 2020
 *
 */

inherit "/std/guild/guild_lay_sh";
inherit "/lib/commands";

#include <comb_mag.h>
#include <files.h>
#include <hooks.h>
#include <log.h>
#include <login.h>
#include <money.h>
#include <std.h>
#include <wa_types.h>
#include <macros.h>
#include <const.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"


#include "vampires_thirst.c"
#include "vampires_sunlight.c"
#include "vampires_combat_msg.c"

#define IVE_BEEN_VAMP_DRAINED  "_invevampdrained"

static int obj_no_show;


/*
 * Global variables
 */
public int      query_guild_not_allow_join_lay(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_lay_shadow(string str);
int             query_guild_level_lay();
static int      drain_alarm, times;
static          object drainee;

int vampire_occ_age;
int vampire_occ_age_cap;

void do_vamp_drink();
void release_vamp_drainee(int silent);
void desc_vamp_drink();

//int stop_vision();

string *test;
string *norm;
string * Current_vision;
int Vision_index;
int Vision_alarmid;

int ethereal;
int vamp_invis;
int vamp_daywalker;

int leave_ethereal;

static private string *dark_arr = 
    ({ 
      "The area is covered in a blanket of darkness.\n",
      "The area is submerged deep in a pool of darkness.\n",
      "The area is engulfed in a sea of darkness.\n"
    });

static private string *light_arr = 
    ({ 
      "The area is bathed in soft light.\n",
      "The area is brightly illuminated.\n",
      "The area is overwhelmed with brilliant light.\n"
    });
    
    
varargs string
light_desc(object env)
{
    int light_lvl;
    string *desc_arr, light_desc;

    if (!env)
    {
        env = environment(QSW);
    }

    /* If "_room_s_light_desc" is set, just use that */
    if (!stringp(light_desc = env->query_prop("_room_s_light_desc")))
    {
        /* Figure out the description based on OBJ_I_LIGHT */

        light_lvl = env->query_prop(OBJ_I_LIGHT);

        desc_arr = (light_lvl < 1 ? dark_arr : light_arr);

        light_lvl = (light_lvl > 0 ? light_lvl-- : -light_lvl);
        light_lvl = MIN(light_lvl / 2, sizeof(desc_arr) - 1);
        light_desc = desc_arr[light_lvl];
    }
    
    return light_desc;
}


varargs string
sunlight_desc(object env)
{
    string sunlight_desc, str;
    int sunlight_lvl;

    if (!env)
    {
        env = environment(QSW);
    }

    if (!stringp(sunlight_desc = env->query_prop("_room_s_sunlight_desc")))
    {
        sunlight_lvl = query_sunlight_level(env);

        if (sunlight_lvl < 1)
        {
            if (ethereal == 1)
            {
                return "You are in the ethereal realm.\nYou can sense "
                +"that the sun is not present in the normal realm.\n";
            }
            
            return "The area is sheltered from the sun's rays.\n";
        }

        switch (sunlight_lvl)
        {
            case 1..5:
                str =  "faint";
                break;
            case 6..10:
                str = "weak";
                break;
            case 11..20:
                str = "normal";
                break;
            case 21..30:
                str = "bright";
                break;
            default:
                str = "blazing";
                break;
        }
        
        if (ethereal == 1)
        {
            return "You are in the ethereal realm.\nYou can sense "
            +"that the normal realm is exposed to " + str + " sunlight.\n";
        }

        return "The area is exposed to " + str + " sunlight.\n";
    }

    return sunlight_desc;
}


int query_ethereal()
{
    return ethereal;
}


void leave_ethereal()
{
    ethereal = 0;
    
    shadow_who->catch_tell("You emerge from the ethereal realm.\n");
    
    shadow_who->tell_watcher(QTNAME(shadow_who) + " fades into view.\n");
    
    shadow_who->dec_prop(LIVE_I_SEE_INVIS, -1000);
    
    shadow_who->remove_prop(VAMPIRE_IS_ETHEREAL);
    
    leave_ethereal = 0;
    
    return;
}


int set_ethereal()
{
    if (ethereal == 1)
    {
        if (leave_ethereal == 1)
        {
            shadow_who->catch_tell("You have already started the process "
            +"of leaving the ethereal realm. Patience!\n");
            
            return 1;
        }
        
        shadow_who->catch_tell("You prepare to leave the ethereal realm.\n");
        
        set_alarm(30.0, 0.0, &leave_ethereal());
        
        //set_alarm(1.0, 10.0, &leave_ethereal());
        
        leave_ethereal = 1;
        
        return 1;
    }
    
    shadow_who->catch_tell("You fade into the ethereal realm\n");
    shadow_who->tell_watcher(QTNAME(shadow_who) + " fades from view.\n");
    ethereal = 1;
    
    shadow_who->inc_prop(LIVE_I_SEE_INVIS, -1000);
    shadow_who->add_prop(VAMPIRE_IS_ETHEREAL, 1);
    
    return 1;
}





public int 
check_seen(object for_obj)
{
    int shadow_result=query_shadow_who()->check_seen(for_obj);
    
    if (ethereal == 1)
    {
        if (!living(for_obj))
        {
            return shadow_result;
        }
        
        // We can see us
        if (for_obj==query_shadow_who())
        {
            return shadow_result;                                                 
        }
        
        // Wizards can always see us.
        if (for_obj->query_wiz_level())
        {
            return shadow_result;
        }
        
        // Ethereal vampires can see eachother
        if (for_obj->query_prop(VAMPIRE_IS_ETHEREAL))
        {
            return shadow_result;
        }
        
        return 0;
    }
    
    if (!objectp(for_obj) ||
        obj_no_show ||
        (!for_obj->query_wiz_level() &&
         (for_obj->query_prop(LIVE_I_SEE_INVIS) <
          this_object()->query_prop(OBJ_I_INVIS) ||
          for_obj->query_skill(SS_AWARENESS) <
          this_object()->query_prop(OBJ_I_HIDE))))
    {
        return 0;
    }
     
    return 1;
}

int query_vamp_daywalker()
{
    return vamp_daywalker;
}


int set_vamp_daywalker()
{
    if (vamp_daywalker == 1)
    {
        vamp_daywalker = 0;
        shadow_who->catch_tell("You are no longer a Daywalker! "
        +"Sunlight will be deadly to you.\n");

        shadow_who->remove_prop(VAMPIRE_IS_DAYWALKER);
        
        return 1;
    }
    
    shadow_who->catch_tell("You become a Daywalker! Sunlight "
    +"will not harm you.\n");
    
    vamp_daywalker = 1;
    
    shadow_who->add_prop(VAMPIRE_IS_DAYWALKER, 1);
    
    return 1;
}


public object
query_top_shadow()
{
    object last_me, me;
    me = shadow_who;
    last_me = me;
    
    while (me = shadow(me, 0))
    {
        last_me = me;
    }
    
    return last_me;
}


int
do_glance(int brief)
{
    if (!CAN_SEE_IN_ROOM(QSW))
    {
        return SW->do_glance(brief);
    }

    tell_object(SW, light_desc());

    tell_object(QSW, sunlight_desc());

    return QSW->do_glance(brief);
}


public object
query_vamp_drain()
{
    return drainee;
}


int
can_vamp_drink(object drainer, object drainee)
{
    mixed prop;
    object *livings;
    int i;
  
    if (prop = drainer->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        drainer->catch_msg(stringp(prop) ? prop : "Your mouth is blocked\n");
        return 0;
    }
  
    if (prop = drainee->query_prop(LIVE_M_NO_DRAIN))
    {
        drainer->catch_msg(stringp(prop) ? prop : "You can't seem to manage " +
            "to drain " + drainee->query_the_name(drainee) + ".\n");
        return 0;
    }
  
    livings = FILTER_OTHER_LIVE(all_inventory(drainer) - ({ drainee, drainer }));
    
    for (i = 0; i < sizeof(livings); i++)
    {
        if (livings[i]->query_attack() == drainer)
        {
            drainer->catch_msg("You can't drain from " + 
            drainee->query_the_name(drainer) + " while others are fighting " +
                "you.\n");
                
            return 0;
        }
    }
  
    /* Don't continue if the target is in combat */
    for (i = 0; i < sizeof(livings); i++)
    {
        if (livings[i]->query_attack() == drainee)
        {
            drainer->catch_msg("You can't drain from " + 
                drainee->query_the_name(drainer) +
                " while others are fighting " + OBJ(drainee) + ".\n");
            return 0;
        }
    }
    
    return 1;
}


void
start_vamp_drink(object who)
{
    who->add_prop(LIVE_O_VAMP_DRAINER, QSW);
    who->remove_prop(LIVE_O_OFFERED_BLOOD);
    drainee = who;
 
    if (drain_alarm)
    {
        remove_alarm(drain_alarm);
    }

    drain_alarm = set_alarm(DRINK_INTERVAL, DRINK_INTERVAL, do_vamp_drink);

    setuid();
    seteuid(getuid());

    drainee->add_subloc(DRAINEE_SUBLOC, this_object());
    QSW->add_subloc(DRAINER_SUBLOC, this_object());

    /* paralyze drainer and drainee */
    clone_object(VAMPIRES_OBJ_DIR + "bitten_paralysis")->move(drainee,1);
    clone_object(VAMPIRES_OBJ_DIR + "biter_paralysis")->move(QSW,1);
    
}


public void
do_vamp_drink()
{
    object drainer = QSW;

    if (!drainer || !drainee || 
        (environment(drainer) != environment(drainee)))
    {
        release_vamp_drainee(1);
        return;
    }

    if (!can_vamp_drink(drainer, drainee))
    {
        release_vamp_drainee(0);
        return;
    }

    if (drainee->query_prop(LIVE_I_NO_BODY) ||
        drainee->query_prop("_live_i_no_blood"))
    {
        drainer->catch_tell(drainee->query_The_name(drainer) +
          " doesn't seem to have any blood!\n");
          
        release_vamp_drainee(0);
        return;
    }

    if (drainee->query_prop(LIVE_I_UNDEAD))
    {    
        drainer->catch_msg(QCTNAME(drainee) + "'s blood tastes " +
            "bitter in your mouth. You try to swallow it down, but your " +
            "stomache churns and rejects it.\n");
        release_vamp_drainee(0);

        drainer->command("$spit");

        return;
    }

    if (times++ > (3 + random(3)))
    {
        times = 0;
    }

    if (!times)
    {
        desc_vamp_drink();
    }

    int thirstvalueocc = VAMPIRES_MAPPINGS->query_thirst_gauge(drainer->query_name());
    int agevalueocc = VAMPIRES_MAPPINGS->query_vampires_gauge(drainer->query_name());
    
    int thirstvalueaddocc;
    int thirstvaluecapocc;
    
    
    int drainsum = drainee->query_prop(IVE_BEEN_VAMP_DRAINED);
    int newsum = drainsum + 1;
    
    if (drainsum >= 20)
    {
        newsum = 20;
        
        thirstvalueaddocc = thirstvalueocc;
        
        drainer->catch_tell(drainee->query_The_name(drainer) +
          " will no longer yeld more points of blood!\n");
          
        if (!present("_vampire_drain_cooldown_ob", drainee))
        {
            clone_object(VAMPIRES_GUILD_DIR +"obj/vampire_drain_cooldown_ob")->move(drainee, 1);
        }
    }
    else
    {
        thirstvalueaddocc = thirstvalueocc + 1;
    }
    
    drainee->add_prop(IVE_BEEN_VAMP_DRAINED, newsum);
    
    
    switch(agevalueocc)
    {
        case 0..24:
        thirstvaluecapocc = 24;
        break;
        
        case 25..48:
        thirstvaluecapocc = 48;
        break;
        
        case 49..72:
        thirstvaluecapocc = 72;
        break;
        
        case 73..100:
        thirstvaluecapocc = 100;
        break;
        
        case 101..250:
        thirstvaluecapocc = 150;
        break;

        case 251..500:
        thirstvaluecapocc = 200;
        break;
        
        case 501..1000:
        thirstvaluecapocc = 250;
        break;
        
        case 1001..1440:
        thirstvaluecapocc = 300;
        break;
 
        case 1441..1450:
        thirstvaluecapocc = 350;
        break;
        
        case 1451..2000:
        thirstvaluecapocc = 400;
        break;
        
        case 2001..3000:
        thirstvaluecapocc = 450;
        break;
        
        case 3001..5000:
        thirstvaluecapocc = 500;
        break;
        
        case 5001..7000:
        thirstvaluecapocc = 550;
        break;
        
        case 7001..9000:
        thirstvaluecapocc = 600;
        break;
        
        case 9001..11000:
        thirstvaluecapocc = 700;
        break;
        
        case 11001..13000:
        thirstvaluecapocc = 800;
        break;
        
        case 13001..15000:
        thirstvaluecapocc = 900;
        break;
        
        case 15001..17529:
        thirstvaluecapocc = 1000;
        break;
        
        case 17530..999999:
        thirstvaluecapocc = 1200;
        break;
    }
    
    if (thirstvaluecapocc <= thirstvalueocc)
    {
        thirstvalueaddocc = thirstvaluecapocc;
    }
    
    
    
    VAMPIRES_MAPPINGS->set_thirst_gauge(drainer->query_name(), thirstvalueaddocc);
 
    drainee->heal_hp(-150);
    
    if (VAMPIRES_MAPPINGS->query_thrall_pool(drainee->query_name()) == 2)
    {      
        int vamppoints = VAMPIRES_MAPPINGS->query_vampires_resilience(drainer->query_name());
        
        vamppoints = vamppoints + 2;
               
        int cap = VAMPIRES_MAPPINGS->query_vampires_gauge(drainer->query_name());
        
        switch(cap)
        {
            case 1451..3000:
            if (vamppoints >= 2)
            {
                vamppoints = 2;
            }   
            break;
            
            case 3001..7000:
            if (vamppoints >= 3)
            {
                vamppoints = 3;
            }   
            break;
            
            case 7001..11000:
            if (vamppoints >= 5)
            {
                vamppoints = 5;
            }   
            break;
            
            case 11001..15000:
            if (vamppoints >= 7)
            {
                vamppoints = 7;
            }   
            break;
            
            case 15001..50000:
            if (vamppoints >= 9)
            {
                vamppoints = 9;
            }   
            break;
        }
        
        VAMPIRES_MAPPINGS->set_vampires_resilience(drainer->query_name(), vamppoints);
        
        drainer->catch_tell("Your Immortality points increases to "+vamppoints+".\n");
        
        // This sets the flag to 3, which renders the thrall inert for future
        // imm-point harvest. Vampire needs a new player.
        VAMPIRES_MAPPINGS->set_thrall_pool(drainee->query_name(), 3);
    }
    
    if (drainee->query_hp() <= 0)
    {
        // IF we are flagged for turning, victim turns
        // into a vampire spawn.
        if (drainer->query_prop(VAMP_TURN_ON) == 1)
        {
            if (drainee->query_race() == "human")
            {
                if (drainee->query_guild_name_race())
                {
                    drainer->catch_tell("The one you tried to turn has a "
                    +"racial guild.\n");
                    
                    drainee->set_hp(-1000);
                    drainee->do_die(drainer);
                                  
                    return;
                }
                
                if (drainee->query_guild_name_lay())
                {
                    drainer->catch_tell("The one you tried to turn has a "
                    +"laymanguild.\n");
                    
                    drainee->set_hp(-1000);
                    drainee->do_die(drainer);
                                  
                    return;
                }
                
                if (drainee->query_guild_name_occ())
                {
                    drainer->catch_tell("The one you tried to turn has an "
                    +"occupational guild.\n");
                    
                    drainee->set_hp(-1000);
                    drainee->do_die(drainer);
                                  
                    return;
                }
                
                // Requires 2 Immortality points to create a Vampire Spawn
                if (VAMPIRES_MAPPINGS->query_vampires_resilience(drainer->query_name()) < 2)
                {
                    drainer->catch_tell("You lack the Immortalitypoints "
                    +"required "
                    +"to turn your target.\n");
                    
                    drainee->set_hp(-1000);
                    drainee->do_die(drainer);
                    
                    return;
                }
                
                int vamp_rank = VAMPIRES_MAPPINGS->query_vampires_rank(drainer->query_name());
                int new_vamp_rank = vamp_rank + 1;
                
                int immortal_points = VAMPIRES_MAPPINGS->query_vampires_resilience(drainer->query_name());               
                int immortal_newvalue = immortal_points - 2;
                
                // Should never happen
                if (immortal_newvalue < 0)
                {
                    immortal_newvalue = 0;                
                }        
                
                VAMPIRES_MAPPINGS->set_vampires_resilience(drainer->query_name(), immortal_newvalue);
                VAMPIRES_MAPPINGS->set_vampires_rank(drainer->query_name(), new_vamp_rank);
                
                object turnie;
                
                turnie = clone_object(VAMPIRES_OBJ_DIR + "turn_paralyze");
                turnie->set_turner(drainer);
                turnie->move(drainee, 1);
                
                release_vamp_drainee(0);
                
                return;
            }
        }
        
        drainee->set_hp(-1000);
        drainee->do_die(drainer);
    }
}


public void
desc_vamp_drink()
{
    object drainer = QSW;
    string blood_desc;

    switch (drainee->query_hp() / 30)
    {
        case 0:
            blood_desc = "barely trickles onto your tongue";
            break;
        case 1..2:
            blood_desc = "flows slowly into your mouth";
            break;
        case 3..5:
            blood_desc = "streams steadily into your mouth";
            break;
        default:
            blood_desc = "gushes in a torrent down your throat";
            break;
    }
      
    drainee->catch_tell(({
        "Your vision fades, and you are momentarily plunged " +
            "into darkness.\nYour vision suddenly returns " +
            "with perfect clarity.\n",
        "Bright colors swirl before your eyes.\n",
        "The sound of " + drainer->query_the_name(drainee) +
            "'s heart beating in sync with your own echos " +
            "through your mind.\n",
        "You feel " + drainer->query_the_name(drainee) + 
            "'s hot breath blasting against your neck like " +
            "flames licking at your skin.\n",
        "Your skin tingles with energy.\n",
        "With each slowing heartbeat you are tossed from " +
            "perfect clarity of mind to an utter stupor..." + 
            "from " +
            "extreme to extreme with seemingly no median.\n",
        "Adrenaline pumps through your body, electrifying " +
            "and exhilarating you.\n",
        "Violent chills race through your bones.\n",
        "You break out in a sweat as you are ravaged by " +
            "intense hot flashes.\n",
        "Images pass through your thoughts...memories dear " +
            "and long forgotten.\n",
        })[random(10)]);
    tell_room(({
        "A thin stream of blood trickles down " + QTNAME(drainee) +
            "'s neck.\n",
        QCTNAME(drainer) + " looks up for a moment, licks the blood " +
            "from his lips, and continues to feed on " + QTNAME(drainee) + 
            ".\n",
        QCTNAME(drainee) + " lets out a soft moan of ecstacy.\n",
        QCTNAME(drainee) + " clutches at " + QTNAME(drainer) + "'s " +
            "clothing, pulling " + POSS(drainer) + " closer.\n",
        QCTNAME(drainee) + " opens " + POSS(drainee) + " eyes for a "+
        "moment, apparently lost in overwhelming sensations.\n",
        QCTNAME(drainee) + "'s eyelids flutter.\n",
        })[random(6)], ({ drainer, drainee }));

    drainer->catch_tell(LANG_POSS(drainee->query_The_name(drainer)) +
        " blood " + blood_desc + ".\n");
}


void
release_vamp_drainee(int silent)
{
    object ob, drainer = QSW;

    drainer->remove_subloc(DRAINER_SUBLOC);
    
    while (ob = present("_vamp_biter_paralysis", drainer))
    {
        ob->remove_object();
    }

    if (drainee)
    {
        drainee->remove_prop(LIVE_O_VAMP_DRAINER);
        drainee->remove_subloc(DRAINEE_SUBLOC);
    
        while (ob = present("_vamp_bitten_paralysis", drainee))
        {
            ob->remove_object();
        }
    }

    remove_alarm(drain_alarm);
    drain_alarm = 0;

    if (!silent && drainee)
    {
        set_this_player(drainer);
        actor("You release", ({ drainee }), " from your embrace.");
        target(" releases you from " + POSS(drainer) + " embrace.", 
            ({ drainee }));
       
        all2actbb(" releases", ({ drainee }), " from " + POSS(drainer) + 
                " embrace.");
        
        object shadow=clone_object(VAMPIRES_OBJ_DIR+"blood_shadow");
        
        shadow->shadow_me(drainee);
        
        int neck=drainee->query_id_for_hitloc_name("head");
        if (neck>=0)
        {
            drainee->bite_location(neck);
        }
    }
    drainer->hook_drainer_released(drainee);
    if (drainee)
    {
        drainee->hook_drainee_released(drainer);
    }
    
    drainee=0;    
}


void
desc_vamp_drain()
{
    object drainer = QSW;
    string blood_desc;

    switch (drainee->query_hp() / 30)
    {
        case 0:
            blood_desc = "barely trickles onto your tongue";
            break;
        case 1..2:
            blood_desc = "flows slowly into your mouth";
            break;
        case 3..5:
            blood_desc = "streams steadily into your mouth";
            break;
        default:
            blood_desc = "gushes in a torrent down your throat";
            break;
    }
      
    drainee->catch_tell(({
        "You break out in a sweat as you are ravaged by " +
            "intense hot flashes.\n",
        "You feel " + drainer->query_the_name(drainee) + 
            "'s hot breath blasting against your neck like " +
            "flames licking at your skin.\n",
        "Violent chills race through your bones.\n",
        })[random(3)]);
    drainer->tell_watcher(({
        "A thin stream of blood trickles down " + QTNAME(drainee) +
            "'s neck.\n",
        QCTNAME(drainee) + " struggles to break free from " + 
            QTNAME(drainer) + "'s embrace, but is unable to free " +
            OBJ(drainee) + "self.\n",
        QCTNAME(drainee) + " lets out a barely audible whimper.\n",
        QCTNAME(drainer) + " looks up for a moment, licks the blood " +
            "from " + POSS(drainer) + " lips, and tears back into " +
            QTNAME(drainee) + ".\n",
        "You hear a low, weak moan from " + QTNAME(drainee) + ".\n",
        QCTNAME(drainee) + "'s eyelids flutter.\n",
        QCTNAME(drainee) + " gasps for air.\n",
        })[random(7)], drainee);
    
    drainer->catch_tell(LANG_POSS(drainee->query_The_name(drainer)) +
        " blood " + blood_desc + ".\n");
}


public mixed
query_guild_skill_name(int type)
{
    if (type == SS_ANATOMY)
    {
        return "anatomy";
    }
    return 0;
}


string
query_sire()
{
    setuid();
    seteuid(getuid());
  
    return lower_case(SIRE_MANAGER->query_sire(SW));
}


string
query_thrall()
{
    setuid();
    seteuid(getuid());
  
    return lower_case(THRALL_MANAGER->query_thrall(SW));
}


public void
add_soul_lay()
{
    setuid();
    seteuid(getuid());

    int i;

    object *member;

    object expel_obj;

    member = users();

    shadow_who->add_cmdsoul(VAMPIRES_GUILD_DIR 
    + "souls/vampires_guild_soul_lay");
    
    object mana_shadow = clone_object("/d/Genesis/specials/guilds/shadows/mana_shadow");

    mana_shadow->shadow_me(shadow_who);

    shadow_who->add_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");

    shadow_who->add_cmdsoul(VAMPIRES_GUILD_DIR + "spells/lay_guild_magic");

    shadow_who->update_hooks();
}


public string *query_spells()
{
    object spell_obj;

    if (!objectp(spell_obj = present(VAMPIRES_SPELL_OBJECT, shadow_who)))
    {
        return 0;
    }

    return m_indexes(spell_obj->query_spell_map()) + ({});
}


int
query_guild_level_lay()
{
    return VAMPIRES_MAPPINGS->query_vampires_rank_lay(query_shadow_who()->query_name());
}


int
query_vampires_rank_gauge_level_lay()
{
    return VAMPIRES_MAPPINGS->query_vampires_rank_gauge_lay(query_shadow_who()->query_name());
}


string
query_guild_title_lay()
{
    return "";
}


public string
query_guild_name_lay()
{
    return LAY_VAMPIRES_GUILD_NAME;
}


public string
query_guild_style_lay()
{
    return TYPE_LAY;
}


public int
query_guild_tax_lay()
{
    return TAX_LAY;
}


public mixed
query_guild_trainer_lay()
{
    return ({ VAMPIRES_GUILD_DIR + "rooms/layrace_train",
           });
}


public int
query_guild_not_allow_join_lay(object player, string type, 
string style, string name)
{
    if (::query_guild_not_allow_join_lay(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


void
add_regeneration_ob_base()
{
    setuid();
    seteuid(getuid());
    
    object regen_obj_base, defended, top_shadow;

    top_shadow = query_top_shadow();
    
    defended = top_shadow->query_shadow_who();  
    regen_obj_base = clone_object("/d/Faerun/guilds/vampires/specials/obj/vampires_regeneration_obj");
    regen_obj_base->set_effect_caster(defended);
    regen_obj_base->set_effect_target(defended);
    regen_obj_base->move(defended, 1);
    regen_obj_base->start();
}


void
move_vampire()
{
    if (shadow_who->query_ghost())
    {
        return;
    }

    // Turned vampires remains where they are turned.
    if (shadow_who->query_prop(REMAIN_STATIONARY))
    {
        return;
    }

    shadow_who->move_living("M", VAMPIRES_GUILD_DIR + "rooms/coffin", 1);
    
    shadow_who->add_prop(REMAIN_STATIONARY, 1);

    return;
}


void
add_undead_shadow()
{
    object undead_shadow = clone_object(GLOBAL_UNDEAD_SHADOW);
    undead_shadow->shadow_me(shadow_who);
    
    shadow_who->add_prop(LIVE_M_NO_SCRY, "A dark room.\n");
    shadow_who->add_prop(LIVE_I_NO_CORPSE, 1);
    shadow_who->add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    
    return;
}


public int query_vampires_gauge_level()
{
    return VAMPIRES_MAPPINGS->query_vampires_gauge(query_shadow_who()->query_real_name());
}


void
check_vampire_ascension_premises()
{
    if (VAMPIRES_MASTER->is_occ_vampires(shadow_who->query_name()))
    {
        return;
    }
    
    // Premise 1. Must be of minimum size.
    if (this_player()->query_average() < REQ_AVG_OCC)
    {
        return;        
    }
    
    // Premise 2. Must have aged 2 months.
    if (query_vampires_gauge_level() < 1450)
    {
        return;
    }
    
    // Premise 3. Can't have an occ guild.
    if (shadow_who->query_guild_name_occ())
    {
        write("You feel a surge of power going through your "
        +"blood as if you are ready to <evolve into "
        +"a full vampire>!\nYou must leave your occupational "
        +"guild before you can evolve.\n");
            
        return;
    }
    
    write("You feel a surge of power going through your "
        +"blood as if you are ready to <evolve to "
        +"full vampire>!\n");
    
    return;
}


void
check_vampirespawn_kickwarning()
{
    if (VAMPIRES_MASTER->is_occ_vampires(shadow_who->query_name()))
    {
        return;
    }
 
    int vampirespawn_age = VAMPIRES_MAPPINGS->query_vampires_gauge(shadow_who->query_name());   
    int vampirespawn_cd = VAMPIRES_MAPPINGS->query_vampirespawn_timer(shadow_who->query_name());
    
    // 12 hours buffer until kicked.
    int buffer = vampirespawn_cd + 9;
    
    if (buffer > vampirespawn_age)
    {
        if (interactive(shadow_who))
        {
            shadow_who->catch_tell("You feel that your laziness has catched "
            +"up to you. A projected image of a shadowy figure haunts "
            +"you in your mind, reminding you that unless you step "
            +"it up, you will be Destroyed!\n");   
        }    
    }
    
    return;
}


public string
customize_guild_spell_effect_messages(object *effects, string message_text)
{
    mixed active_effect_spells = map(all_inventory(this_player()),
        &->query_spell_names()) - ({ 0 });
    if (!sizeof(active_effect_spells)) return 0;

    string *possible_spells = ({ });
    foreach(string *spell : active_effect_spells)
    {
        possible_spells -= spell;
        possible_spells += spell;
    }

    return "\n                     Currently Active Spells \n"
        + "                     ======================== \n\n"
        + break_string("You can cast " 
        + COMPOSITE_WORDS(sort_array(possible_spells))
        + ".", 71) + "\n";
}


/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       object killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{   
    // We check if we have immportality points.   
    int imm_point_us = VAMPIRES_MAPPINGS->query_vampires_resilience(shadow_who->query_name());
    int imm_points_killer = VAMPIRES_MAPPINGS->query_vampires_resilience(killer->query_name());
    
    // If the killer is an occ vampire
    if (VAMPIRES_MASTER->is_occ_vampires(killer->query_name()) == 1)
    {   
        // Must have 2 points of immortality or more. The last
        // point can never be drained by a vampire.
        if (imm_point_us > 1)
        {
            imm_point_us = imm_point_us - 1;
            imm_points_killer = imm_points_killer + 1;
            
            // Killer gets his point.
            VAMPIRES_MAPPINGS->set_vampires_resilience(killer->query_name(), imm_points_killer);
            
            // Quickly correct if cap is met.
            killer->do_vampthirst_announce();
            
            // We loses our point.
            VAMPIRES_MAPPINGS->set_vampires_resilience(shadow_who->query_name(), imm_point_us);
            
            VAMP_VS_VAMP_LOG("vamp_vs_vamp_log",
            "The Vampire " +shadow_who->query_name()+" was slain "
            +"by "+killer->query_name()+" and 1 imm_point transfered.\n");
            
            killer->catch_tell("\nYou drain a point of Immortality from your victim!\n");
            shadow_who->catch_tell("\nYour killer drains for a point of Immortality from you!\n");
        }
    }
        
    shadow_who->do_die(killer);
    
    return;
}


public void
init_lay_shadow(string str)
{
    object who = query_shadow_who();
    
    string weaknessmessage;
    
    int who_avg;
    int who_avg_ex;    
    int difference;        
    int recalculatedstat;
    
    int stat_adjustment_str = 0;
    int stat_adjustment_dex = 0;
    int stat_adjustment_con = 0;
    int stat_adjustment_int = 0;
    int stat_adjustment_dis = 0;
    int stat_adjustment_wis = 0;
    
    int who_stat_str;
    int who_stat_dex;
    int who_stat_con;
    int who_stat_int;
    int who_stat_dis;
    int who_stat_wis;
    
    who_stat_str = who->query_stat(SS_STR);
    who_stat_dex = who->query_stat(SS_DEX);
    who_stat_con = who->query_stat(SS_CON);
    who_stat_int = who->query_stat(SS_INT);
    who_stat_dis = who->query_stat(SS_DIS);
    who_stat_wis = who->query_stat(SS_WIS);
    
    int vampire_age = VAMPIRES_MAPPINGS->query_vampires_gauge(who->query_real_name());
    
    switch(vampire_age)
    {
        case 0..72:
        stat_adjustment_str = -80;
        stat_adjustment_dex = -80;
        stat_adjustment_con = -80;
        stat_adjustment_int = -80;
        stat_adjustment_dis = -80;
        stat_adjustment_wis = -80;

        if (who_stat_str < 130)
        {
            stat_adjustment_str = -40;
        }
        
        if (who_stat_dex < 130)
        {
            stat_adjustment_dex = -40;
        }
        
        if (who_stat_con < 130)
        {
            stat_adjustment_con = -40;
        }
        
        if (who_stat_int < 130)
        {
            stat_adjustment_int = -40;
        }
        
        if (who_stat_dis < 130)
        {
            stat_adjustment_dis = -40;
        }
        
        if (who_stat_wis < 130)
        {
            stat_adjustment_wis = -40;
        }  
        
        weaknessmessage = "\n\nBeing a fresh Vampire Spawn, all your stats are "
        +"greatly reduced!\n\n";
        break;
        
        case 73..120:
        stat_adjustment_str = -60;
        stat_adjustment_dex = -60;
        stat_adjustment_con = -60;
        stat_adjustment_int = -60;
        stat_adjustment_dis = -60;
        stat_adjustment_wis = -60;
        
        if (who_stat_str < 130)
        {
            stat_adjustment_str = -40;
        }
        
        if (who_stat_dex < 130)
        {
            stat_adjustment_dex = -40;
        }
        
        if (who_stat_con < 130)
        {
            stat_adjustment_con = -40;
        }
        
        if (who_stat_int < 130)
        {
            stat_adjustment_int = -40;
        }
        
        if (who_stat_dis < 130)
        {
            stat_adjustment_dis = -40;
        }
        
        if (who_stat_wis < 130)
        {
            stat_adjustment_wis = -40;
        }  
        
        weaknessmessage = "\n\nBeing a new Vampire Spawn, all your stats are "
        +"very reduced!\n\n";
        break;
        
        case 121..500:
        stat_adjustment_str = -30;
        stat_adjustment_dex = -30;
        stat_adjustment_con = -30;
        stat_adjustment_int = -30;
        stat_adjustment_dis = -30;
        stat_adjustment_wis = -30;
        
        if (who_stat_str < 130)
        {
            stat_adjustment_str = -40;
        }
        
        if (who_stat_dex < 130)
        {
            stat_adjustment_dex = -40;
        }
        
        if (who_stat_con < 130)
        {
            stat_adjustment_con = -40;
        }
        
        if (who_stat_int < 130)
        {
            stat_adjustment_int = -40;
        }
        
        if (who_stat_dis < 130)
        {
            stat_adjustment_dis = -40;
        }
        
        if (who_stat_wis < 130)
        {
            stat_adjustment_wis = -40;
        }  
        
        weaknessmessage = "\n\nBeing a young Vampire Spawn, all your stats are "
        +"quite reduced!\n\n";
        break;
        
        case 501..65000:
        stat_adjustment_str = -0;
        stat_adjustment_dex = -0;
        stat_adjustment_con = -0;
        stat_adjustment_int = -0;
        stat_adjustment_dis = -0;
        stat_adjustment_wis = -0;
        weaknessmessage = "\n";
        break;
    }
    
    
    
    
    
    setuid();
    seteuid(getuid());

    ::init_lay_shadow();
    
    ethereal = 0;
       
    set_alarm(0.0, 0.0, add_soul_lay);
    
    set_alarm(0.0, 0.0, move_vampire);
    
    set_alarm(0.0, 0.0, add_regeneration_ob_base);
    
    set_alarm(0.5, 0.0, add_undead_shadow);
    
    set_alarm(10.0, 120.0, do_vampthirst_announce);
    
    // TEMPORARY DAYWALKER PROPERTY - FOR EVENTS
    //who->add_prop(VAMPIRE_IS_DAYWALKER, 1);
        
    who->add_prop(LIVE_M_NO_INGEST, "Eating has no effect on your undead body.\n");
    
    who->add_prop(LIVE_M_NO_DRINK, "Unless it's blood, drinking has no "
    +"effect on your undead body.\n");
    
    // Check_sunlight-function also checks for autokick premises
    // and skill adjustments for vampires
    set_alarm(5.0,5.0, check_sunlight);
    
    who->set_default_start_location(VAMPIRES_GUILD_DIR + "rooms/coffin");
    
    who->set_temp_start_location(VAMPIRES_GUILD_DIR + "rooms/coffin");
    
    who->set_stat_extra(SS_STR, stat_adjustment_str);
    who->set_stat_extra(SS_CON, stat_adjustment_dex);
    who->set_stat_extra(SS_DEX, stat_adjustment_con);
    who->set_stat_extra(SS_INT, stat_adjustment_int);
    who->set_stat_extra(SS_DIS, stat_adjustment_dis);
    who->set_stat_extra(SS_WIS, stat_adjustment_wis); 
    
    if (!shadow_who->query_prop(NO_VAMP_WEAK_MESSAGE))
    {
        shadow_who->catch_tell(weaknessmessage);
    }

    shadow_who->catch_tell("\nTo access vampire help, type 'vhelp'.\n");
    
    clone_object(VAMPIRES_GUILD_DIR + "obj/expel_obj")->move(who, 1);
    set_alarm(1.0, 0.0, &expel_vampire());
    
    set_alarm(3600.0, 3600.0, check_vampire_ascension_premises);   
    
    set_alarm(10.0, 600.0, check_vampirespawn_kickwarning);
}


public void set_intoxicated(int i)
{
    //Do not set it
}


public int query_intoxicated()
{
    return 0;
}


/*
 * Function name:   query_appearance
 * Description:     Gives the current value of the appearance variable.
 * Returns:         The appearance value
 */
public int
query_appearance()
{
    return 0;
}


/*
 * Function name:   query_scar
 * Description:     Gives the scar bitmask of the living
 * Returns:         The scar bitmask
 */
public int
query_scar()
{
    return 0;
}



public string query_default_start_location()
{
    return VAMPIRES_GUILD_DIR + "rooms/coffin";
}


public void remove_shadow()
{
    object emblem, who = query_shadow_who();

    shadow_who->remove_cmdsoul(VAMPIRES_GUILD_DIR 
    + "souls/vampires_guild_soul_lay");
    
    who->remove_mana_shadow();

    shadow_who->remove_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");

    shadow_who->update_hooks();
    
    shadow_who->set_default_start_location(VAMPIRES_GUILD_DIR + "rooms/coffin");
    
    who->set_temp_start_location(VAMPIRES_GUILD_DIR + "rooms/coffin");

    ::remove_shadow();
}


int query_vampires_lay()
{
    return 1;
}