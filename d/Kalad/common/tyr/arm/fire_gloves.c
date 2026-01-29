/* fire_gloves.c created by Shiva@Genesis. */

inherit "/std/armour";
inherit "/lib/keep";

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>

#define FLAMES_SHADOW (TYR_ARM + "fire_glove_sh")
#define MIN_FIRE_SKILL 15

string flame_short();
string flame_adj();
string no_steal();

static int flames, flames_attack_id;

void
create_armour()
{
    set_name("gloves");
    set_pname("gloves");
  
    set_adj(flame_adj);
    add_adj("gold");
    add_adj("pair of");
  
    set_short(flame_short);
    set_pshort(flame_short);
  
    set_at(A_HANDS);
    set_ac(20);
    set_am(({ -2, 0, 2 }));
    set_af(this_object());
  
    set_long("A heavy pair of gloves with thin threads of real gold " +
	"woven into them.\n@@flame_long@@");
  
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "fire" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The gloves are apparently enchanted with fire magic.\n", 5,
	"When worn, the gloves spontaneously produce flames.\n", 15,
	}));
    add_prop(OBJ_S_WIZINFO, "When worn, each glove produces flames, " +
	"which cause extra MAGIC_DT damage and produce 1 level of " +
	"light for each hand.  If a weapon is used, flames will " +
	"be extinguished for the appropriate hand(s).\n");
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_M_NO_STEAL, no_steal);
}

/* Can't steal flaming gloves! */
string
no_steal()
{
    if (flames)
    {
        return "The gloves are covered with flames...you can't steal them!\n";
    }
  
    return 0;
}

/* Give a special short desc when the gloves are flaming. */
string
flame_short()
{
    if (flames)
    {
        return "pair of flaming gold gloves";
    }
  
    return "pair of gold gloves";
}

/* add the "flaming" adj when they're flaming. */
string
flame_adj()
{
    if (flames)
    {
        return "flaming";
    }
  
    return "";
}

/* Special long when flaming. */
string
flame_long()
{
    if (!flames)
    {
        return "";
    }
  
    if ((flames & A_HANDS) == A_HANDS)
    { 
        return "Flames surround the gloves.\n";
    }
  
    if (flames & A_L_HAND)
    {
        return "Flames surround the left glove.\n";
    }
  
    return "Flames surround the right glove.\n";
}

/* set the flame level for the gloves...the value
 * should correspond to the hitloc ids of the hands
 * for which the flames are active...i.e.
 * 0 - flames off on both hands
 * A_L_HAND - flames on on left hand
 * A_R_HAND - flames on on right hand
 * A_L_HAND | A_R_HAND - flames on on both hands
 */
int
set_flames(int i)
{
    int old_flames;
    int flame_change;
    object wearer;
  
    old_flames = flames;
    flames = i;
  
    if (!(wearer = query_worn()))
    {
        i = 0;
    }

    /* We designate flame level using hitloc ids, but when we want to
     * do damange, we'll need to know which attack ids the gloves
     * use.
     */
    flames_attack_id = flames << 2;
  
    flame_change = old_flames ^ flames;
  
    if (flame_change & A_L_HAND)
    {
    	if (old_flames & A_L_HAND)
    	{
	    if (wearer)
	    {
	        wearer->catch_tell("The flames on the left glove die out.\n");
	    }
      
	    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - 1);
    	}
    	else
    	{
	    if (wearer)
	    {
	        wearer->catch_tell("Flames surround the left glove.\n");
                wearer->reveal_me();
	    }
      
	    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + 1);
    	}
    }
  
    if (flame_change & A_R_HAND)
    {
    	if (old_flames & A_R_HAND)
    	{
	    if (wearer)
	    {
	        wearer->catch_tell("The flames on the right glove die out.\n");
	    }
      
	    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - 1);
    	}
    	else
    	{
	    if (wearer) 
	    {
	        wearer->catch_tell("Flames surround the right glove.\n");
                wearer->reveal_me();
	    }
      
	    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + 1);
    	}
    }
  
    if (flames)
    {
        add_prop(OBJ_I_HAS_FIRE, 1);
    }
    else
    {
        remove_prop(OBJ_I_HAS_FIRE);
    }

    return i;
}

/* update the current flame level.  This checks to see what
 * weapons are wielded and that the gloves are actually worn.
 */
void
update_flames()
{
    object wearer;
    int left, right;
  
    if (!(wearer = query_worn()) || wearer->query_weapon(W_BOTH))
    {
        set_flames(0);
        return;
    }
  
    if (!wearer->query_npc() &&
        wearer->query_skill(SS_ELEMENT_FIRE) < MIN_FIRE_SKILL)
    {
        set_flames(0);
        return;
    }

    left = ((wearer->query_weapon(W_LEFT) || 
	wearer->query_armour(W_LEFT)) ? 0 : A_L_HAND);
    right = ((wearer->query_weapon(W_RIGHT) || 
	wearer->query_armour(W_RIGHT)) ? 0 : A_R_HAND);
  
    set_flames(left | right);
}

/* return the current flame level */
int
query_flames() { return flames; }

/* light up one (or both) of the gloves.
 * the value should correspond to the hitloc id as
 * for set_flames()
 */
int
add_flames(int i)
{
    if (flames & i)
    {
        return 0;
    }
  
    set_flames(flames | i);
    return 1;
}

/* extinguish one (or both) gloves.
 * the value should correspond to the hitloc id as
 * for set_flames().
 */
int
remove_flames(int i)
{
    if (!(flames & i))
    {  
        return 0;
    }
  
    set_flames(flames ^ i);
    return 1;
}
    
/* Called when the gloves are worn, this function
 * sets the flame level and adds a shadow which takes 
 * care of some of the gloves' functionality.
 */
int
wear()
{
    object sh;
  
    setuid();
    seteuid(getuid());
    if ((sh = clone_object(FLAMES_SHADOW)) &&
	 sh->shadow_me(this_player()))
    { 
        sh->set_gloves_ob(this_object());
        set_alarm(0.0, 0.0, update_flames);
    }
    else
    {
        sh->remove_shadow();
    }
  
    return 0;
}    

/* Called when the gloves are removed, this function
 * sets the flame level and removes the glove shadow.
 */
int
remove()
{
    set_alarm(0.0, 0.0, &set_flames(0));
    this_player()->remove_glove_shadow();
    return 0;
}

/* This called from the glove shadow to do fire damage
 * to opponents when a successful unarmed attack is made
 * while wearing the gloves.
 */
int
special_damage(int aid, string hdesc, int phurt, object enemy, int phit,
    int dam)
{
    int hurt, res, fire_dam;
    object wearer;
    string with, where, how, what, owhat, burn;
  
    /* make sure we hit with a flaming glove */
    if (!(aid & flames_attack_id))
    {
        return 0;
    }
  
    if (!(wearer = query_worn()))
    {
        return 0;
    }
  
    if (environment(wearer)->query_prop(ROOM_M_NO_MAGIC) ||
        enemy->query_prop(OBJ_M_NO_MAGIC) ||
        (environment(wearer)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
    {
        return 0;
    }

    /* calculate damage, taking fire resistance into account */
    res = 100 - max(enemy->query_magic_res(MAGIC_I_RES_FIRE),
        enemy->query_magic_res(MAGIC_I_RES_MAGIC));
    fire_dam = random(45 + wearer->query_skill(SS_ELEMENT_FIRE) / 10) + 1;
    fire_dam = fire_dam * res / 100;
    hurt = enemy->hit_me(fire_dam, MAGIC_DT, wearer, -1)[2];
  
    if (hurt < 1)
    {
        return 0;
    }

    wearer->add_panic(-3 - phurt / 5);  

    /* give an attack description */
    with = (aid == W_RIGHT ? " right hand" : " left hand");
  
    where = " the " + hdesc + " of ";
  
    switch (phurt)
    {
    	case 0..4:
	    how = "";
	    what = "tickle";
	    owhat = "tickles";
	    break;
    	case 5..9:
	    how = "";
	    what = "graze";
	    owhat = "grazes";
	    break;
    	case 10..19:
	    how = "";
	    what = "hurt";
	    owhat = "hurts";
	    break;
    	case 20..29:
	    how = ", rather bad";
	    what = "hurt";
	    owhat = "hurts";
	    break;
    	case 30..49:
	    how = ", very bad";
	    what = "hurt";
	    owhat = "hurts";
	    break;
    	case 50..69:
	    how = ", very hard";
	    what = "smash";
	    owhat = "smashes";
	    break;
    	case 70..89:
	    how = ", with a bone crushing sound";
	    what = "smash";
	    owhat = "smashes";
	    where = " ";
	    break;
    	default:
	    how = "";
	    what = "massacre";
	    owhat = "massacres";
	    where = " ";
    }
  
    switch (hurt)
    {
    	case 1..10:
	    burn = " singeing ";
	    break;
    	case 11..30:
	    burn = " searing ";
	    break;
    	case 31..70:
	    burn = " blistering ";
	    break;
    	default:
	    burn = " charring ";
	    break;
    }
  
    if (interactive(wearer))
    {
        wearer->catch_tell("You " + what + where + 
            enemy->query_the_name(wearer) + " with your" + with + how +
            ", your glove" + burn + enemy->query_possessive() + " flesh.\n");
    }
  
    if (interactive(enemy))
    {
        enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
              " your " + hdesc + " with " + wearer->query_possessive() +
              with + how + ", " + wearer->query_possessive() + " glove" +
              burn + "your flesh.\n");
    }
  
    wearer->tell_watcher(QCTNAME(wearer) + " " + 
	owhat + where + QTNAME(enemy) + " with " + 
	wearer->query_possessive() + with + how + ", " +
	wearer->query_possessive() + " glove" + burn + 
	enemy->query_possessive() + " flesh.\n", enemy);
  
    return 1;
}

void
destroy_gloves()
{
    object env, *envs, *who;
    string msg;
    int i;

    if (!living(env = environment()))
    {
        /* Try to send destruct messages to the appropriate people */

        msg = "The " + short() + " bursts into flames, " +
            "incinerating immediately.\n";

        who = FILTER_IS_SEEN(this_object(),
            FILTER_CAN_SEE_IN_ROOM(FILTER_PLAYERS(all_inventory(env))));

        who->catch_tell(msg);

        envs = all_environment(this_object());

        for (i = sizeof(envs); i--;)
	{
  	    /* We've found a living among the environments.  Tell the
             * living that the gloves are destroyed.
             */
            if (living(envs[i]))
	    {
                if (CAN_SEE_IN_ROOM(envs[i]) && CAN_SEE(envs[i], this_object()))
		{
                    envs[i]->catch_tell(msg);
		}

                break;
	    }

            /* Check to see that the gloves can be seen inside the
             * containers.
             */
            if (!envs[i]->query_prop(CONT_I_ATTACH) &&
                envs[i]->query_prop(CONT_I_CLOSED) &&
                !envs[i]->query_prop(CONT_I_TRANSP))
	    {
                break;
	    }
	}
        
        remove_object();
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
  
    if (!living(env))
    {
	if (function_exists("create_container", env) == CORPSE_OBJECT)
	{
            /* Give a little extra time for corpses to be looted */
	    set_alarm(20.0, 0.0, destroy_gloves);
	    return;
	}
  
	set_alarm(1.0, 0.0, destroy_gloves);
    }
}

string query_recover()
{
    return ::query_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    ::init_recover(arg);
}
