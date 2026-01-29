/*
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include "missile_functions.c"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"

#include "../guild.h"
      
// Global Variables

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(65);
    set_tohit(90); // 82% hit chance
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_WEIGHT, 60, TS_DEX, SKILL_WEIGHT, 25, TS_WIS, 
                  SKILL_WEIGHT, 15, TS_INT }) );
    set_skills( ({ SS_WEP_MISSILE }) );
    set_ability_prep_time(5);
    set_ability_cooldown_time(15);
    set_ability_name("quickshot");
    
    set_guild_stat_modifier(SS_OCCUP, 50, 150);
} /* config_ability */


/*
 * Function name:   query_guild_stat_type
 * Description:     Returns the guild type of the player using the special. This
 *                  has been masked to allow for occupational and layman sharing
 *                  the special.
 * Arguments:       (object) actor - The player using the special
 * Returns:         (int) The guild type
 */
public int
query_guild_stat_type(object actor)
{
    if (actor->query_guild_name_occ() != GUILD_NAME)
        return SS_LAYMAN;
    
    return SS_OCCUP;
} /* query_guild_stat_type */

/*
 * Function name: report_resolve_ability
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
public void
report_resolve_ability(int pen, int dt, int damage)
{
    string name, logfile;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }
    
    logfile = FILE_PATH(MASTER_OB(this_object()));
    logfile += short() + "_damage";
    logfile = implode(explode(logfile, " "), "");
    
    send_debug_message(short(), name + " hits with Pen of "
        + pen + ", " + "Damage of " + damage, logfile);
} /* report_resolve_ability */

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 *                items - 
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    object  bow, cmbt, arrow, gArrow, archer;
    string *archer_msg, *enemy_msg, *others_msg, *rnd_desc;
    int     loaded = 0, attack_location, hitsuc, pen, hit;
    mixed   hitres;
    
    archer = this_player();
    
    if (!filter_bow(bow = items[0]))
        return;
    
    /* Adds an additional hit to the target if the bow is already loaded, 
     * This is to prevent loss of caid.
     */
    if (objectp(bow->query_projectile()) &&
        objectp(cmbt = archer->query_combat_object()))
    {
        hit = bow->query_hit();
        
        attack_location = filter(cmbt->query_attack_id(),
                                &operator(==)(, bow) @
                                &operator([])(, 6) @
                                &cmbt->query_attack())[0];
        
        if ((cmbt->cb_try_hit(attack_location) > 0) &&
            (enemy->query_not_attack_me(archer, attack_location) <= 0) &&
            (hitsuc = cmbt->cb_tohit(attack_location, hit, enemy)) > 0)
        {
            pen = cmbt->query_attack(attack_location)[ATT_M_PEN][0];
            
            if (!random(10000))
                pen *= 5;
            
            hitres = enemy->hit_me(pen, dt, archer, attack_location);
        }
        else
        {
             hitres = enemy->hit_me(hitsuc, 0, archer, attack_location);
        }
            
        if (hitsuc > 0)
        {
            hitsuc = bow->query_pen();
            if (hitsuc > 0)
            {
                hitsuc = 100 * hitres[2] / hitsuc;
            }
            else
            {
                hitsuc = 0;
            }
        }
            
        if (hitres[1])
        {
            cmbt->cb_did_hit(attack_location, hitres[1], hitres[4],
                            hitres[0], enemy, dt, hitsuc, hitres[3]);
        }
        
        loaded = 1;
    }
        
    /* Handles the arrow stacks */
    if (phurt < 5)
        arrow = reduce_and_miss(enemy, bow, items[1]);
    else
        arrow = reduce_and_hit(enemy, bow, items[1]);
    
    /* Makes the arrow retrievable */
    arrow->add_prop(OBJ_O_BELONGS_TO_ARCHER, archer);
    
    switch(phurt)
    {
        case -2..-1:
        archer_msg = ({
            "You hurriedly nock " + LANG_ADDART(arrow->singular_short()) + " "
            + "and shoot at " + QTNAME(enemy) + ", but it misses the target "
            + "badly",
            
            "You hurriedly nock and fire "
            + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + ". It flies past your target, missing "
            + enemy->query_objective(),
            
            "You hurriedly nock and shoot "
            + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + ", but it hisses past, missing "
            + enemy->query_objective(),
        });

        enemy_msg = ({
            QCTNAME(archer) + " hurriedly nocks and shoots "
            + LANG_ADDART(arrow->singular_short())
            + " at you, but it misses you badly",
            
            QCTNAME(archer) + " hurriedly nocks and fires "
            + LANG_ADDART(arrow->singular_short())
            + " at you, but it just flies past, missing you",
            
            "You hear the hiss of an arrow flying through the air as "
            + QTNAME(archer) + " hurriedly shoots "
            + LANG_ADDART(arrow->singular_short()) + " at you"
        });
        
        others_msg = ({
            QCTNAME(archer) + " hurriedly nocks and shoots "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", but it misses " +
            enemy->query_objective() + " badly",
                             
            QCTNAME(archer) + " hurriedly nocks and shoots "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", but it just flies past "
            + enemy->query_objective() + ", barely missing the target",
            
            "You hear the hiss of an arrow flying through the air as "
            + QTNAME(archer) + " hurriedly nocks and shoots "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy)
        });
        
            break;
        case 0..2:
        
        archer_msg = ({ 
            "You nock and shoot " + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", but it merely glances off "
            + enemy->query_possessive() + " " + hdesc + ", just nicking "
            + enemy->query_possessive() + " skin",

            "You load your " + bow->short() + " with "
            + LANG_ADDART(arrow->singular_short())
            + " and almost without aiming shoot at " + QTNAME(enemy) + ", but "
            + "the arrow merely glances off " + enemy->query_possessive() + " "
            + hdesc + ", just nicking " + enemy->query_possessive() + " skin"
        });

        enemy_msg = ({
            QCTNAME(archer) + " nocks and shoots "
            + LANG_ADDART(arrow->singular_short()) + " at "
            + "you, but it merely glances off your " + hdesc + ", just nicking "
            + "your skin",
            
            QCTNAME(archer) + " loads " + archer->query_possessive() + " "
            + bow->short() + " with " + LANG_ADDART(arrow->singular_short())
            + " and almost without "
            + "aiming shoots at you, but the arrow merely glances off your "
            + hdesc + ", just nicking your skin"
        });

        others_msg = ({
            QCTNAME(archer) + " nocks and shoots "
            + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + ", but it merely glances off "
            + enemy->query_possessive() + " " + hdesc + ", just nicking "
            + enemy->query_possessive() + " skin",
            
            QCTNAME(archer) + " loads " + archer->query_possessive() + " "
            + bow->short() + " with " + LANG_ADDART(arrow->singular_short())
            + " and almost without aiming shoots at " + QTNAME(enemy)
            + ", but the arrow merely glances " + enemy->query_possessive()
            + " " + hdesc + ", just nicking " + enemy->query_possessive()
            + " skin"
        });

            break;
        case 3..5:
        
        archer_msg = ({
            "You nock " + LANG_ADDART(arrow->singular_short())
            + " and shoot wildly at " + QTNAME(enemy) + ", with the arrow "
            + "just grazing " + enemy->query_possessive() + " " + hdesc + " "
            + "and falling to the ground",

            "You tilt your " + bow->short() + " and hurriedly fit "
            + LANG_ADDART(arrow->singular_short()) + " to the string. You "
            + "shoot wildly at " + QTNAME(enemy) + ", with the arrow just "
            + "grazing " + enemy->query_possessive() + " " + hdesc + " and "
            + "falling to the ground"
        });

        enemy_msg = ({
            QCTNAME(archer) + " nocks " + LANG_ADDART(arrow->singular_short())
            + " and shoots wildly at you, but the arrow just grazes your "
            + hdesc + " and falls to the ground",

            QCTNAME(archer) + " tilts " + archer->query_possessive() + " "
            + bow->short() + " and hurriedly fits "
            + LANG_ADDART(arrow->singular_short()) + " to "
            + "the string. Then " + archer->query_pronoun() + " shoots wildly "
            + "at you, but the arrow just grazes your " + hdesc + " and falls "
            + "to the ground"
        });

        others_msg = ({ 
            QCTNAME(archer) + " nocks " + LANG_ADDART(arrow->singular_short())
            + " and shoots wildly at " + QTNAME(enemy) + ", but the arrow just "
            + "grazes " + enemy->query_possessive() + " " + hdesc + " and "
            + "falls to the ground",

            QCTNAME(archer) + " tilts " + archer->query_possessive() + " "
            + bow->short() + " and hurriedly fits "
            + LANG_ADDART(arrow->singular_short()) + " to "
            + "the string. Then " + archer->query_pronoun() + " shoots wildly "
            + "at " + QTNAME(enemy) + ", but the arrow just grazes "
            + enemy->query_possessive() + " " + hdesc + " and falls to the "
            + "ground"
        });

            break;
        case 6..15:
    
        rnd_desc = one_of_list( ({
                                "opening a nasty wound",
                                "causing significant damage",
                                "leaving a minor wound",
                            }) );
                            
        archer_msg = ({
            "You swiftly nock " + LANG_ADDART(arrow->singular_short())
            + " and fire accurately at " + QTNAME(enemy) + ", the arrow "
            + "pierces " + enemy->query_possessive() + " " + hdesc + ", "
            + rnd_desc,
            
            "You quickly set " + LANG_ADDART(arrow->singular_short()) + " to "
            + "the string and fire accurately at " + QTNAME(enemy) + ". The "
            + "arrow pierces " + enemy->query_possessive() + " " + hdesc + ", "
            + rnd_desc
        });
            
        enemy_msg = ({ 
            QCTNAME(archer) + " swiftly nocks "
            + LANG_ADDART(arrow->singular_short()) + " and fires "
            + "accurately at you, the arrow pierces your " + hdesc + ", "
            + rnd_desc,
            
            QCTNAME(archer) + " quickly sets "
            + LANG_ADDART(arrow->singular_short()) + " to the "
            + "string and fires accurately at you. The arrow pierces your "
            + hdesc + ", " + rnd_desc
        });
            
        others_msg = ({ 
            QCTNAME(archer) + " swiftly nocks "
            + LANG_ADDART(arrow->singular_short()) + " and "
            + "fires " + "accurately at " + QTNAME(enemy) + ". The arrow "
            + "pierces " + enemy->query_possessive() + " " + hdesc + ", "
            + rnd_desc,
            
            QCTNAME(archer) + " quickly sets "
            + LANG_ADDART(arrow->singular_short()) + " to the "
            + "string and fires accurately at " + QTNAME(enemy) + ". The arrow "
            + "pierces " + enemy->query_possessive() + " " + hdesc + ", "
            + rnd_desc
        });

            break;
        case 16..27:

        archer_msg = ({
            "You fall back several steps, trying to gain some distance while "
            + "nocking " + LANG_ADDART(arrow->singular_short()) + " and then "
            + "shoot at " + QTNAME(enemy) + ". The arrow stabs deeply into "
            + enemy->query_possessive() + " " + hdesc,
            
            "You fall back several steps, load your bow with "
            + LANG_ADDART(arrow->singular_short()) + " " + "and shoot at "
            + QTNAME(enemy) + ". The arrow stabs deeply into "
            + enemy->query_possessive() + " " + hdesc
        });
            
        enemy_msg = ({
            QCTNAME(archer) + " falls back several steps, trying to gain some "
            + "distance while nocking " + LANG_ADDART(arrow->singular_short())
            + " and then shoots at you. The arrow stabs deeply into your "
            + hdesc,
            
            QCTNAME(archer) + " falls back several steps, loads "
            + archer->query_possessive() + " " + bow->short() + " and shoots "
            + LANG_ADDART(arrow->singular_short()) + " at you. The arrows "
            + "stabs deeply into your " + hdesc
        });
            
        others_msg = ({ 
            QCTNAME(archer) + " falls back several steps, trying to gain some "
            + "distance while nocking " + LANG_ADDART(arrow->singular_short())
            + " and then shoots at " + QTNAME(enemy) + ". The arrow stabs "
            + "deeply into " + enemy->query_possessive() + " " + hdesc,
           
            QCTNAME(archer) + " falls back several steps, loads "
            + archer->query_possessive() + " " + bow->short() + " and shoots "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ". The arrow stabs deeply into " + enemy->query_possessive()
            + " " + hdesc
        });
        
            break;
        case 28..43:

        rnd_desc = one_of_list( ({  "deeply", 
                                    "badly", 
                                    "easily",
                                    "forcefully",
                                    "accurately",
                                    "solidly"
                                }) );
                            
        archer_msg = ({
            "You swiftly load your " + bow->short() + " with "
            + LANG_ADDART(arrow->singular_short())
            + ", focus intently on " + QTNAME(enemy) + " and then shoot, "
            + "sending the arrow in " + enemy->query_possessive()
            + " direction. It " + rnd_desc + " impales "
            + enemy->query_possessive() + " " + hdesc,
            
            "You swiftly re-nock and focus intently on " + QTNAME(enemy)
            + " and then shoot, sending " + LANG_ADDART(arrow->singular_short())
            + " in " + enemy->query_possessive() + " direction. It " + rnd_desc
            + " impales " + enemy->query_possessive() + " " + hdesc,
        });

        enemy_msg = ({
            QCTNAME(archer) + " loads " + archer->query_possessive() + " "
            + bow->short() + " with " + LANG_ADDART(arrow->singular_short())
            + " and shoots, sending it rapidly in your direction. It "
            + rnd_desc + " impales your " + hdesc,
            
            QCTNAME(archer) + " swiftly re-nocks and shoots, sending "
            + LANG_ADDART(arrow->singular_short()) + " in your direction. It "
            + rnd_desc + " impales your " + hdesc,
        });
         
        others_msg = ({
            QCTNAME(archer) + " loads " + archer->query_possessive() + " "
            + bow->short() + " with " + LANG_ADDART(arrow->singular_short())
            + " and shoots at " + QTNAME(enemy) + ", sending it rapidly in "
            + enemy->query_possessive() + " direction. It " + rnd_desc
            + " impales " + enemy->query_possessive() + " " + hdesc,
            
            QCTNAME(archer) + " swiftly re-nocks and shoots at " + QTNAME(enemy)
            + ", sending an arrow in " + enemy->query_possessive()
            + " direction. It " + rnd_desc + " impales "
            + enemy->query_possessive() + " " + hdesc,
        });

            break;
        case 44..65:

        if (enemy->query_humanoid())
        {
            archer_msg = ({
                "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                + " and shoot " + QTNAME(enemy) + " with great precision. "
                + capitalize(enemy->query_pronoun()) + " grasps "
                + enemy->query_possessive() + " " + hdesc + ", which is deeply "
                + "punctured by the arrow",
            
                "You swiftly re-nock your " + bow->short() + " and shoot "
                + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
                + " with great precision. " + capitalize(enemy->query_pronoun())
                + " grasps " + enemy->query_possessive() + " " + hdesc
                + ", which is deeply punctured by the arrow"
            });
            
            enemy_msg = ({
                QCTNAME(archer) + " rapidly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoots at you with great precision. You grasp your " + hdesc
                + ", which is deeply punctured by the arrow",
            
                QCTNAME(archer) + " swiftly re-nocks "
                + archer->query_possessive() + " " + bow->short() + " and "
                + "shoots " + LANG_ADDART(arrow->singular_short()) + " at you "
                + "with great precision. You grasp your " + hdesc + ", which "
                + "is deeply punctured by the arrow"
            });
            
            others_msg = ({
                QCTNAME(archer) + " rapidly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoots at " + QTNAME(enemy) + " with great precision. "
                + capitalize(enemy->query_pronoun()) + " grasps "
                + enemy->query_possessive() + " " + hdesc + ", which is deeply "
                + "punctured by the arrow",
         
                QCTNAME(archer) + " swiftly re-nocks "
                + archer->query_possessive() + " " + bow->short() + " and "
                + "shoots " + LANG_ADDART(arrow->singular_short()) + " at "
                + QTNAME(enemy) + " with great precision. "
                + capitalize(enemy->query_pronoun()) + " "
                + "grasps " + enemy->query_possessive() + " " + hdesc
                + ", which is deeply punctured by the arrow"
            });
        }
        else
        {
            archer_msg = ({
                "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                + " and shoot at " + QTNAME(enemy) + " with great precision. "
                + "The arrow deeply punctures " + enemy->query_possessive()
                + " " + hdesc,
                
                "You swiftly re-nock your " + bow->short() + " and shoot "
                + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
                + " with great precision. The arrow deeply punctures "
                + enemy->query_possessive() + " " + hdesc
            });
            
            enemy_msg = ({
                QCTNAME(archer) + " rapidly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoots at you with great precision. The arrow deeply "
                + "punctures your " + hdesc,
                
                QCTNAME(archer) + " swiftly re-nocks "
                + archer->query_possessive() + " " + bow->short() + " and "
                + "shoots " + LANG_ADDART(arrow->singular_short()) + " at you "
                + "with great precision. The arrow deeply punctures your "
                + hdesc
            });
            
            others_msg = ({
                QCTNAME(archer) + " rapidly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoots at " + QTNAME(enemy) + " with great precision. The "
                + "arrow deeply punctures " + enemy->query_possessive() + " "
                + hdesc,
                
                QCTNAME(archer) + " swiftly re-nocks " +
                archer->query_possessive() + " " + bow->short() + " and "
                + "shoots " + LANG_ADDART(arrow->singular_short()) + " at "
                + QTNAME(enemy) + " with " + "great precision. The arrow "
                + "deeply punctures " + enemy->query_possessive() + " " + hdesc
            });
        }
        
            break;
        case 66..99:
        
        archer_msg = ({
            "You rapidly nock " + LANG_ADDART(arrow->singular_short()) + " and "
            + "shoot accurately at " + QTNAME(enemy) + ", who staggers when "
            + "the arrow lances through " + enemy->query_possessive() + " "
            + hdesc + ", opening a heavily bleeding wound",
            
            "You rapidly draw " + LANG_ADDART(arrow->singular_short()) + " to "
            + "your " + bow->short() + " and shoot accurately at "
            + QTNAME(enemy) + ", who staggers when the arrow lances through "
            + enemy->query_possessive() + " " + hdesc + ", opening a heavily "
            + "bleeding wound"
        });

        enemy_msg = ({ 
            QCTNAME(archer) + " rapidly nocks "
            + LANG_ADDART(arrow->singular_short()) + " and "
            + "shoots accurately at you. You stagger when the arrow lances "
            + "through your " + hdesc + ", opening a heavily bleeding wound",
            
            QCTNAME(archer) + " rapidly draws "
            + LANG_ADDART(arrow->singular_short()) + " to "
            + archer->query_possessive() + " " + bow->short() + " and shoots "
            + "accurately at you. You stagger when the arrow lances through "
            + "your " + hdesc + ", opening a heavily bleeding wound"
        });
            
        others_msg = ({
            QCTNAME(archer) + " rapidly nocks "
            + LANG_ADDART(arrow->singular_short()) + " and "
            + "shoots accurately at " + QTNAME(enemy) +", who staggers when "
            + "the arrow lances through " + enemy->query_possessive() + " "
            + hdesc + ", opening a heavily bleeding wound",
            
            QCTNAME(archer) + " rapidly draws "
            + LANG_ADDART(arrow->singular_short()) + " to "
            + archer->query_possessive() + " " + bow->short() + " and shoots "
            + "accurately at " + QTNAME(enemy) + ", who staggers when the "
            + "arrow lances through " + enemy->query_possessive() + " " + hdesc
            + ", opening a heavily bleeding wound"
        });
        
            break;
        default:

        if (enemy->query_humanoid()
            && IN_ARRAY(hdesc, ({ "head", "body", "legs" })))
        {
            switch(hdesc)
            {
                case "head":
                archer_msg = ({ 
                    "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot " + QTNAME(enemy) + " through the neck who "
                    + "falls to the ground, desperately clutching "
                    + enemy->query_possessive() + " throat",
            
                    "You rapidly re-nock your bow and shoot " + QTNAME(enemy)
                    + " through the neck. " + capitalize(enemy->query_pronoun())
                    + " falls to the ground, desperately clutching "
                    + enemy->query_possessive() + " throat" 
                });
            
                enemy_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " and "
                    + "shoots you through the neck and you fall to the ground, "
                    + "desperately clutching your throat",
            
                    QCTNAME(archer) + " rapidly re-nocks "
                    + archer->query_possessive() + " " + bow->short() + " and "
                    + "shoots you through the neck. You fall to the ground, "
                    + "desperately clutching your throat"
                });
            
                others_msg = ({ 
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " and "
                    + "shoots " +  QTNAME(enemy) + " through the neck. "
                    + capitalize(enemy->query_pronoun()) + " falls to the "
                    + "ground, desperately clutching "
                    + enemy->query_possessive() + " throat",
            
                    QCTNAME(archer) + " rapidly re-nocks "
                    + archer->query_possessive() + " " + bow->short() + " and "
                    + "shoots " + QTNAME(enemy) + " through the neck. "
                    + capitalize(enemy->query_pronoun()) + " falls to the "
                    + "ground, desperately clutching "
                    + enemy->query_possessive() + " throat"
                });
                    break;
                case "body":
                archer_msg = ({ 
                    "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot " + QTNAME(enemy) + " through the heart, "
                    + "killing " + enemy->query_objective() + " instantly",
            
                    "You rapidly re-nock your bow and shoot " + QTNAME(enemy)
                    + " through the heart, killing " + enemy->query_objective()
                    + " instantly",
                });
            
                enemy_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " and shoots you "
                    + "through the chest. The arrow lodging itself into your "
                    + "heart and killing you instantly",
            
                    QCTNAME(archer) + " rapidly re-nocks "
                    + archer->query_possessive() + " " + bow->short() + " and "
                    + "shoots you through the chest. The arrow lodging itself "
                    + "into your heart and killing you instantly"
                });
            
                others_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " and shoots "
                    + QTNAME(enemy) + " through the chest. The arrow having "
                    + "lodged itself into " + enemy->query_possessive() + " "
                    + "heart and killing " + enemy->query_pronoun() + " "
                    + "instantly",
            
                    QCTNAME(archer) + " rapidly re-nocks "
                    + archer->query_possessive() + " " + bow->short() + " and "
                    + "shoots " + QTNAME(enemy) + " through the chest. The "
                    + "arrow having lodged itself into "
                    + enemy->query_possessive() + " heart and killing "
                    + enemy->query_pronoun() + " instantly",
                });
                    break;
                case "legs":
                string leg_desc = one_of_list(({ "left leg", "right leg" }));
                archer_msg = ({ 
                    "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot " + QTNAME(enemy) + " through the " + leg_desc
                    + ", perforating " + enemy->query_possessive() + " femoral "
                    + "artery, rapidly bleeding " + enemy->query_objective()
                    + " dry",
            
                    "You rapidly re-nock your bow and shoot " + QTNAME(enemy)
                    + " through the " + leg_desc + ", perforating "
                    + enemy->query_possessive() + " femoral artery, rapidly "
                    + "bleeding " + enemy->query_objective() + " dry",
                });
            
                enemy_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " and shoots your "
                    + leg_desc + ", perforating your femoral artery, rapidly "
                    + "bleeding you dry",
            
                    QCTNAME(archer) + " rapidly re-nocks "
                    + archer->query_possessive() + " " + bow->short() + " and "
                    + "shoots your " + leg_desc + ", perforating your femoral "
                    + "artery, rapidly bleeding you dry"
                });
            
                others_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " and shoots "
                    + QTNAME(enemy) + " through the " + leg_desc + ". The "
                    + "arrow having perforated the femoral artery, rapidly "
                    + "bleeding " + enemy->query_objective() + " dry",
            
                    QCTNAME(archer) + " rapidly re-nocks "
                    + archer->query_possessive() + " " + bow->short() + " and "
                    + "shoots " + QTNAME(enemy) + " through the " + leg_desc
                    + ". The arrow having perforated the femoral artery, "
                    + "rapidly bleeding " + enemy->query_objective() + " dry",
                });
                    break;
            }
        }
        else
        {
            archer_msg = ({
                "You swiftly nock " + LANG_ADDART(arrow->singular_short())
                + " and shoot at " + QTNAME(enemy) + " with devastating "
                + "precision. " + capitalize(enemy->query_pronoun()) + " falls "
                + "to the ground, with an arrow sticking from a mortal wound "
                + "in " + enemy->query_possessive() + " " + hdesc,
                
                "You swiftly re-nock your bow with "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoot at " + QTNAME(enemy) + " with devastating precision. "
                + capitalize(enemy->query_pronoun()) + " falls to the ground, "
                + "with an arrow sticking from a mortal wound in "
                + enemy->query_possessive() + " " + hdesc
            });

            enemy_msg = ({
                QCTNAME(archer) + " swiftly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoots at you with devastating precision. You fall to the "
                + "ground, with an arrow sticking from a mortal wound in your "
                + hdesc,
                
                QCTNAME(archer) + " swiftly re-nocks "
                + archer->query_possessive() + " " + bow->short() + " with "
                + LANG_ADDART(arrow->singular_short()) + " and shoots at you "
                + "with devastating precision. You fall to the ground, with an "
                + "arrow sticking from a mortal wound in your " + hdesc
            });
                
            others_msg = ({
                QCTNAME(archer) + " swiftly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoots at " + QTNAME(enemy) + " with devastating precision. "
                + capitalize(enemy->query_pronoun()) + " falls to the ground, "
                + "with an arrow sticking from a mortal wound in "
                + enemy->query_possessive() + " " + hdesc,
                
                QCTNAME(archer) + " swiftly re-nocks "
                + archer->query_possessive() + " " + bow->short() + " with "
                + LANG_ADDART(arrow->singular_short()) + " and shoots at "
                + QTNAME(enemy) + " with devastating precision. "
                + capitalize(enemy->query_pronoun()) + " falls to the ground, "
                + "with an arrow sticking from a mortal wound in "
                + enemy->query_possessive() + " " + hdesc
            });
        
        }
    }
    
    if (phurt < 0)
        loaded = random(sizeof(archer_msg));
    
    archer->catch_msg(archer_msg[loaded] + ".\n");
    enemy->catch_msg(enemy_msg[loaded] + ".\n");
    archer->tell_watcher(others_msg[loaded] + ".\n", enemy);
    
    /* Calls the hit in the arrow */
    if (dam > 0)
    {
        if (objectp(arrow))
        {
            int max_dmg, prc_dmg, wep_dmg, wep_pen, wep_lev;
        
            /*
             * This damage is calculated from the percentual success of the 
             * special and the F_PENMOD on weapons and bow skill. Keep in mind,
             * this does not add damage unless the arrow itself has a special
             * that is applied in such a way. 
             */
        
            max_dmg = calculate_damage(archer, enemy, items, 0, result);
            prc_dmg = dam * 100 / max_dmg;
            wep_pen = calc_base_pen(items);
            wep_lev = archer->query_skill(SS_WEP_MISSILE);
            wep_dmg = F_PENMOD(wep_pen, wep_lev) * prc_dmg / 100;
        
            arrow->projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt,
                                         phit, wep_dmg, hid);
        }
        if (enemy->query_hp() <= 0)
            enemy->do_die(archer);
    }
}

/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Returns:         number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    int modifier = 100;
    
    /* Maxed at 50 caid for layman members */
    if (this_player()->query_guild_name_lay() == GUILD_NAME)
    {
        modifier = 77;
    
        /* Cap the special if in darkness, due to passive nightvision. */
        if (VISION_IMPAIRED(this_player()))
            modifier = modifier * 3 / 5;
    } else if (VISION_IMPAIRED(this_player()))
        modifier = modifier * 70 / 100;
    
    return modifier;
} /* query_combat_aid_modifier */

/*
 * Function name:   query_tohit
 * Description:     Calculates the tohit for the player. Based on the missile
 *                  knowledge or fixed hitchance, this is lowered to allow the
 *                  archer to more easily raise the missile knowledge.
 * Arguments:       none
 * Returns:         input to cb_tohit function
 */
public int
query_tohit()
{
    int value = this_player()->query_skill(SS_WEP_MISSILE);
   
    if (::query_tohit() < value)
        return ::query_tohit();
    
    return max(value, 10);
} /* query_tohit */

/*
 * Function name:   check_required_items
 * Description:     Does some validation to make sure that the archer has arrows
 *                  and is wielding a bow.
 * Returns:         items that are required.
 */
static mixed * 
check_required_items(object actor, mixed *targets, string arg, int pretest)
{
    mixed   arrow,
            bow;
    
    if (!objectp(bow = query_wielded_bow(actor)))
    {
        actor->catch_msg("You are not wielding a bow.\n");
        return 0;
    }
    
    /* Find an arrow in the archers inventory, exclude loaded projectile */
    if (!objectp(arrow = find_arrows(actor, bow, bow->query_projectile())))
    {
        actor->catch_msg("You do not possess an arrow to shoot.\n");
        return 0;
    }
    
    return ({ bow, arrow });
} /* check_required_items */

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed *targets, string arg, int execute)
{
    if (!::check_valid_action(actor, targets, arg, execute))
        return 0;
    
    if (actor->query_skill(SS_WEP_MISSILE) < 1)
    {
        actor->catch_msg("You lack the required skill to perform a "
        + "quickshot.\n");
        return 0;
    }
    
    if (SNIPE->query_ability_active(actor))
    {
        actor->catch_msg("You have yet to recover from your recent "
        + "aimed shot.\n");
        return 0;
    }
    
    // If it passes everything, return success
    return 1; 
} /* check_valid_action */

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability, object player)
{
    // Don't display any messages
} /* hook_stopped_ability */

/*
 * Function name:   hook_special_in_cooldown
 * Description:     This function is called if the ability is in cooldown,
 *                  displaying a cooldown message.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    write("You're not ready to prepare for another quickshot.\n");
} /* hook_special_in_cooldown */

/*
 * Function name:   hook_special_complete
 * Description:     This gets called whenever the special is ready again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_complete()
{
    write("You feel ready to execute another quickshot.\n");
} /* hook_special_complete */

/*
 * Function name:   ability_msg
 * Description:     This function displays a message when the ability is being
 *                  activated.
 * Arguments:       None
 * Returns:         Nothing
 */
static void
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You look for an opportunity to perform a quickshot.\n");
} /* ability_msg */