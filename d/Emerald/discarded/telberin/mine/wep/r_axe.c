/* /d/Emerald/mine/wep/r_axe.c is cloned by /d/Emerald/mine/npc/warlord.c  */
/* This axe was originally coded in Mylos' usual unbalanced way.           */ 
/* It has now been recoded in line with the AoB teams recommendations.     */
/* Recoded 13/06/96 by Tulix III.                                          */

/* To be able to 'smear' the axe on a corpse, the axe must have damaged    */
/* the monster before it was killed. Also, the damage done by the special  */
/* attack is greatly reduced if it is smeared on the corpses of monsters   */
/* with low stats. To get 100% of the damage, it must be smeared on        */
/* on corpses of average stat = 100. If you only smeared it on monsters    */
/* with average stat = 10, you would have to smear it on ten times as many */
/* corpses to get the full damage. #:-)                                    */

inherit "/std/weapon";

#include "/d/Emerald/tulix/t_defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <tasks.h>
 
int smeared;       /* Int for the smearing of corpses for their power.  */
int power_on;      /* Int for the regeneration of the power on the Axe. */
int damage_mod;    /* Int for reducing the damage done by the special.  */
object *enemy_arr; /* Array for logging potential corpses.              */

public int do_smear(string str);

#define SMEARS_REQUIRED 6
#define STAT_LOGGER     "/d/Emerald/mine/obj/stat_logger"

public void
create_weapon()
{
    set_name("axe");
    add_name("runed axe");
    set_short("runed axe");
    set_long("@@desc");
    add_cmd_item("runes", "read", "The runes mean nothing to you.\n" );
    add_item(({"runes","surface","blade"}), "The surface of the axe is " +
        "covered in a myriad of tiny runes which make no sense to you.\n");
    
    set_adj("runed");
 
/* This weapon is extremely heavy and so the pen value is larger than   */
/* the hit value since it's fairly easy to hit but the hit itself will  */
/* _hurt_ a lot.                                                        */

/* Tulix's note- Yeah, we've never heard that one before, Mylos...      */
    
    set_default_weapon(35, 48, W_AXE, W_SLASH, W_ANYH,  this_object());
    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(OBJ_I_VOLUME,  3000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35, 48) + random(100) );
 
    add_prop(MAGIC_AM_MAGIC, ({ 65, "enchantment" }));
 
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "This axe seems magical.\n", 0,
        "This extremely magical axe is a work of art. "+
        "It can release extreme energies in battle and must feed off "+
        "the blood of the dead.\n", 20 ,
        "Death swings with this double headed axe. "+
        "You can feel the very power it exhibits pulsing through the "+
        "blade whilst you are holding it. It can be recharged by "+
        "smearing blood onto the blade.\n", 40,
        "The axe can deliver great damage in battle "+
        "but only once until recharged with the magical powers it "+
        "harnesses. To get the powers back the blood of dead enemies "+
        "must be smeared onto the blade.\n", 60,
        "This magical axe can cause special damage "+
        "in battle by releasing magical power onto the opponent. To "+
        "get the power back once must smear the blade with blood from "+
        "a corpse.\n", 80,
        "This axe is fairly magical which you can feel "+
        "through your hand. It has an ability to cause great damage in "+
        "battle and can only release it's power once until recharged. "+
        "To recharge the weapon 'smear blade' or 'smear axe' should "+
        "work fine which needs to be performed 6 times.\n", 100 }) );
    add_prop(OBJ_S_WIZINFO,  "This is the runed axe of the "+
        "Emerald mines found on the warlord, at "+
        "/d/Emerald/room/mine/maze6 "+
        "where the warlord resides. It has a special attack, hitting "+
        "extremely hard (but not quite as hard as it used to - Tulix) "+
        "but it can only be performed once (except by npcs) until it is "+
        "recharged by 'smear blade' or 'smear axe' on corpses of "+ 
        "enemies that have been hurt by this axe.\n" );
 
    enemy_arr = ({ });
    damage_mod = 100;
    power_on = 1;
    smeared = 0;
}
 
public string
desc()
{
    string extra_str;
 
    if(power_on)
        extra_str = " The runes glow a strange blue-green colour.";
    else
        extra_str = " ";
    return  "This heavy axe feels heavy, even with your strength. "+
        "It's leather covered handle seems to grip to "+
        "your hands. The two blades of the axe look wicked with the "+
        "light sparkling in it's reflection, illuminating the runes "+
        "a little."+extra_str+"\n" ;
}
 
public int
wield(object wep)
{
    if(TP->query_stat(SS_STR) < 60)
    {
        write("The blade is too heavy for you to wield.\n");
        return -1;
    }
    
    if(TP->resolve_task(TASK_ROUTINE, ({ TS_INT, SS_SPELLCRAFT})) < 0)
    {
        write("The weapon stuns you with static!\n");
        TP->heal_hp(-60);
        if(TP->query_hp() <= 0)
            TP->do_die(this_object());
        return -1;
    }
    
    return 0;
}
 
public void
init()
{
    ::init();
    add_action(do_smear, "smear");
}
 
public int
do_smear(string str)
{
    object corpse, *items, stat_logger, axe;
    int i, victim_av_stats;
 
    NF("Smear what?\n");
    if(!strlen(str))
        return 0;
    
    /* Let's do it the proper way this time. */
    parse_command(str, ENV(this_player()) ,
        "[the] %o [onto] [on] [over] [the] %o", axe, corpse);
 
    NF("Smear what?\n");
    if(axe != TO && str != "blade")
        return 0;
 
    notify_fail("Perhaps you should wield it first?\n");
    if(!TO->query_wielded())
        return 0;
 
    if (!corpse)
        corpse = present("corpse", ENV(query_wielded()));
 
    NF("There is no corpse here!\n");
    if(!corpse || 
        function_exists("create_container", corpse) != "/std/corpse")
        return 0;
 
    /* Check to see if the corpse has a stat_logger. */
    items = all_inventory(corpse);
    for (i=0 ; i<sizeof(items) ; i++) 
    {
        if (items[i])
        {
            if (items[i]->query_axe_pointer() == TO)
                stat_logger=items[i];
        }
    }
    
    if (!stat_logger)
    {
        /* No dice. This axe did not help to get this corpse. */ 
        write("You hack the corpse around a bit with your axe.\n");
        say(QCTNAME(query_wielded()) + " hacks the corpse around a bit.\n"); 
        return 1;
    }

    write("You rip the corpse apart thoroughly smearing the blade with "+
        "blood.\n");
    say(QCTNAME(query_wielded()) + " smears " +
        query_wielded()->query_possessive() +
        " runed axe with blood from the corpse.\nThere is nothing left "+
        "of the corpse.\n", query_wielded());
    
    victim_av_stats = stat_logger->query_victim_av_stats();

    if (victim_av_stats > 100)
        victim_av_stats = 100;

    damage_mod += (victim_av_stats / SMEARS_REQUIRED);
    
    /* Make sure that the damage modifier does not go above 100%. */
    if (damage_mod > 100)
        damage_mod = 100;

    /* Stat_logger has now served it's purpose, so destruct it. */
    stat_logger->remove_object();
    
    smeared++;
    if (smeared >= SMEARS_REQUIRED)
    {
        smeared = 0;
        power_on = 1;
    }
    
    /* Empty stuff from the corpse before destructing it. */
    for (i=0 ; i<sizeof(items) ; i++) 
    {
        if (items[i])
            items[i]->move(environment(corpse));
    }
    
    corpse->remove_object();
    return 1;
}
 
/* Filter the people without see_blood, so they dont see the special hits */
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;
 
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
/* After we tried to hit something this function is called with the result. */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, 
        int phit, int dam)
{
    int ran;
    object stat_logger;

    ran = random(12);
 
    if (phurt == -1)
    {
        query_wielded()->catch_msg("The axe swings so close to "+
            QTNAME(enemy)+" that "+enemy->query_pronoun()+" gulps "+
            "in fright.\n");
        enemy->catch_msg("The axe swings so close to you that "+
            "you gulp in fright.\n");
        tell_watcher(QCTNAME(query_wielded())+"'s axe swings so close to "+
            QTNAME(enemy)+" that "+QTNAME(enemy)+" gulps in "+
            "fright.\n", enemy);
        return 1; /* Return 1 as message has been rewritten */
    }
    
    if (phurt == 0)
    {
        query_wielded()->catch_msg("You grin evilly as your axe just "+
            "swishes past " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(query_wielded())+"'s axe swishes "+
            "just past you.\n");
        tell_watcher(QCTNAME(query_wielded())+" grins evilly as " +
            query_wielded()->query_possessive() +
            " axe just swishes past "+QTNAME(enemy)+".\n",enemy);
        return 1;
    }
    else
    {
        /* We can smear this axe on the corpse only if we get a good hit. */
        if (phurt >= 4)
        {
            /* Only add a stat logger to an enemy once. */
            if (member_array(enemy, enemy_arr) == -1)
            {
                /* Must have valid uid and euid to clone stuff. */
                setuid();
                seteuid(getuid(TO));
                
                stat_logger=clone_object(STAT_LOGGER);
                stat_logger->move(enemy);
                stat_logger->log_stats(TO);
                enemy_arr += ({ enemy });
            }
        }
        
        if (ran == 1 && power_on)
        {
            query_wielded()->catch_msg("The runed axe discharges a blast "+
                "of static as it gouges deeply into "+QTNAME(enemy)+".\n");
            enemy->catch_msg("A blast of static rips into you from the "+
                "runed axe.\n");
            tell_watcher(QCTNAME(query_wielded())+"'s runed axe discharges "+
                "a blast of static as it gouges into "+QTNAME(enemy)+".\n",
                enemy);
            enemy->heal_hp( damage_mod * ( 200 + 
                query_wielded()->query_skill(SS_SPELLCRAFT) -
                enemy->query_skill(SS_SPELLCRAFT) +
                query_wielded()->query_stat(SS_STR)) / -100 );
            if(enemy->query_hp() <= 0)
                enemy->do_die(query_wielded());
            
            /* Npcs get to use the special attack more often. */
            if (query_wielded()->query_npc())
                return 1;
            
            damage_mod = 0;
            power_on = 0;
            smeared = 0;
            return 1;
        }
        if (ran == 2 && power_on)
        {
            query_wielded()->catch_msg("Your runed axe warms as it slices "+
                "straight through "+QTNAME(enemy)+"'s side.\n");
            enemy->catch_msg("You scream as "+QTNAME(query_wielded())+"'s "+
                "runed axe slices into your side.\n");
            tell_watcher(QCTNAME(query_wielded())+"'s runed axe glows red "+
                "as it slices into "+QCTNAME(enemy)+"'s side.\n",enemy);
            enemy->heal_hp( damage_mod * ( 100 + 
                query_wielded()->query_skill(SS_SPELLCRAFT) -
                enemy->query_skill(SS_SPELLCRAFT) +
                query_wielded()->query_stat(SS_STR)) / -100 );
            enemy->command("scream");
            if(enemy->query_hp() <= 0)
                enemy->do_die(query_wielded());
            
            /* Npcs get to use the special attack more often. */
            if (query_wielded()->query_npc())
                return 1;

            damage_mod = 0;
            power_on = 0;
            smeared = 0;
            return 1;
        }
    }
    return 0;  /* Get normal combat messages. */
}
