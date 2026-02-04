/**vibrato**cedric**/
#pragma save_binary

inherit "/std/object";
inherit "/d/Genesis/newmagic/resist.c";

#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#define BASE_DAMAGE             10
#define BASE_CAST_TIME          5
#define BASE_MANA_COST          5
#define BASE_READ_SKILL         20
#define PURPOSE_DESC    "As you read, you realize that this Song of Power is designed to harm an opponent with a blast of discordant sound.\n"

#include "/d/Terel/cedric/guild/Power/power.h"

#define LOG(str) setuid(); seteuid(getuid()); log_file("vibrato_log", str + "\n");

/*                                *********
* A Song of Power                 * Blast *
* for the Minstrels Guild         *********
* Cedric 3/93
*/

int query_mana_cost(int result);

/*
 * Function:    do_song
 * Description: Takes info about the 'caster', processes that data, and
 *              calls resolve_task to see if the spell succeeds. If so, 
 *              harms the target and starts a fight.
 * Arguments:   performer - the minstrel attempting the song. Should be
 *                          0 if a choir is invoking the song.
 *              to_be_affected - an object or list of objects to be affected
 *                               by the song. If 0, player didn't specify..
 *                               so either it doesn't apply (area effect)
 *                               or the player meant himself/herself, or
 *                               (in this case) player means current enemy.
 *              guild - the guild stat of the performer(s)
 *              dex - the DEX of the performer(s)
 *              dis - the DIS of the performer(s)
 *              vocal - the SG_VOCAL skill of the performer(s)
 *              instrumental - the SG_INSTRUMENTAL skill of the performer(s)
 *              effect - an effectiveness multiplier..usually from choir, 
 *                       broken instrument, etc. IN PERCENT (i.e. x1 = 100%)
 * Returns:    -1 if the song fails completely;
 *             0 if the song couldn't be played;
 *             1-20 if the song succeeds somewhat but with possible 
 *                  accompanying instrument damage.
 *             >20 if the song succeeds completely.
 */
int
do_song(mixed performer, mixed to_be_affected, int guild, int dex, int dis, 
   int vocal, int instrumental, int effect)
{
    int old_hp,new_hp,per;
    int result, base_dmg_amount, dmg_amount, resist, mod_dex, mod_dis;
    mixed joe;
    mixed *hitres;
    
    /*
     * First make sure that attacks are allowed in the room!
     */
    
    if ((environment(performer)->query_prop(ROOM_M_NO_MAGIC_ATTACK)) ||
        (environment(performer)->query_prop(ROOM_I_NO_ATTACK))) {
        performer->catch_msg("Something about this place prevents you from "
                        + "completing your song.\n");
        return 0;       
    }

    if(performer->query_prop(LIVE_I_STUNNED))
    {
        performer->catch_msg("You are too stunned to properly play your " +
            "instrument.\n");
        return 0;
    }

    if (!to_be_affected)
        if (performer->query_attack())
            to_be_affected = performer->query_attack();
        else
        {
            performer->catch_msg("What do you wish as your target?\n");
            return 0;
        }
    if (pointerp(to_be_affected))
    {
        switch(sizeof(to_be_affected))
        {
        case 0:
             if (performer->query_attack())
                 to_be_affected = performer->query_attack();
             else
             {
                 performer->catch_msg("What do you wish as your target?\n");
                 return 0;
             }
             break;
         case 1:
             to_be_affected = to_be_affected[0];
             break;
         default:
             performer->catch_msg("You realize belatedly that you may only aim "
                             + "Vibrato at a single being.\n");
             return 0;
         }
    }
    if (!living(to_be_affected))
    {
        performer->catch_msg("Vibrato will have little enough effect on that!\n");
        return 0;
    }
    /*
     * Make sure that it's ok attack the target!
     */

    if (to_be_affected->query_prop(OBJ_M_NO_MAGIC_ATTACK)
        ||to_be_affected->query_prop(OBJ_M_NO_ATTACK))
    {
        performer->catch_msg("That being is protected by a magical force.\n");
        return 0;
    }
    
    if (!present(to_be_affected, environment(performer)))
    {
        performer->CM("The Song of Power dies in your throat when you realize "
                 + "that "+QTNAME(to_be_affected)+" is no longer here.\n");
        return 0;
    }
        
    if(!F_DARE_ATTACK(performer, to_be_affected))
    {
        performer->CM("You nearly choke at the thought of using a Song of " +
                 "Power against " + QTNAME(to_be_affected) + ".\n");
        return 0;
    }

    LOG("Vibrato (" + performer->query_real_name() + ")");
    LOG(sprintf("Dex: %3d Inst: %2d Dis: %3d Voc: %2d Guild: %3d", dex, instrumental, dis, vocal, guild));

    mod_dex = (dex > 100 ? 100 + ((dex - 100) / 2) : dex);
    mod_dis = (dis > 100 ? 100 + ((dis - 100) / 2) : dis);

    LOG(sprintf("Dex: %3d (%3d) Dis: %3d (%3d) Inst: %3d Voc: %3d Guild: %3d",
        mod_dex, dex, mod_dis, dis, instrumental, vocal, guild))

    result = performer->resolve_task(TASK_SIMPLE, ({ SKILL_VALUE, mod_dex,
                                                SKILL_VALUE, mod_dis,
                                                SKILL_VALUE, instrumental,
                                                SKILL_VALUE, vocal,
                                                SKILL_VALUE, guild * 2 }));
    LOG("Res: " + result);

    if (result<0)
        return -1;
    base_dmg_amount = ((BASE_DAMAGE + (result / 2)) * effect) / 100;
    resist = spell_resist(this_player(),
                          to_be_affected,
                          SS_ELEMENT_AIR,
                          TASK_FORMIDABLE);
    LOG("Resist: " + resist);
    dmg_amount = base_dmg_amount - base_dmg_amount * resist / 100;
    if (dmg_amount > 200)
        dmg_amount = 200; /* reasonable? */
    LOG("Pen: " + dmg_amount);
    hitres = to_be_affected->hit_me(dmg_amount, MAGIC_DT, performer, -1);
    LOG("Dam: " + hitres[3]);
    LOG("Mana: " + query_mana_cost(max(21, base_dmg_amount)));


    performer->attack_object(to_be_affected);
    if (performer)
    {
        switch(dmg_amount)
        {
        case 0..50:
            to_be_affected->catch_msg("Your ears are left ringing by a blast "
                                      + "of sound.\n");
            tell_room(environment(to_be_affected),QCTNAME(to_be_affected)
                      +" shakes "+to_be_affected->query_possessive()
                      +" head, trying to clear "
                      +to_be_affected->query_possessive()
                      +" ears of their ringing.\n",to_be_affected);
            break;
        case 51..100:
            to_be_affected->CM("You are rattled by a blast of sound.\n");
            tell_room(environment(to_be_affected),QCTNAME(to_be_affected)
                      +" is rattled by a blast of sound.\n",to_be_affected);
            break;
        case 101..150:
            to_be_affected->CM("You are hurt by a blast of discordant "
                               + "music.\n");
            tell_room(environment(to_be_affected),
                      "A blast of discordant music hurts "
                      + QTNAME(to_be_affected)+".\n",to_be_affected);
            break;
        case 151..174:
            to_be_affected->CM("You are terribly shaken by a powerful blast "
                               + "of music.\n");
            tell_room(environment(to_be_affected),
                      "A powerful blast of music leaves "
                      + QTNAME(to_be_affected)+" visibly shaken.\n",
                      to_be_affected);
            break;
        case 175..199:
            to_be_affected->CM("A powerful blast of music knocks you back "
                               + "a few steps.\n");
            tell_room(environment(to_be_affected),
                      QCTNAME(to_be_affected)+" staggers back as "
                      + to_be_affected->query_pronoun()
                      + " is crushed by a blast of music.\n",to_be_affected);
            break;
        default:
            to_be_affected->CM("You are thrown to the ground by a "
                               + "tremendous blast of music.\n");
            tell_room(environment(to_be_affected),QCTNAME(to_be_affected)
                      + " is forced to the ground by the power of "
                      + "the music.\n",to_be_affected);
            break;
        }
    }
    else /* a choir sung the song */
    {
        to_be_affected->catch_msg(BS("A crushing force of discordant sound "
                                     + "descends upon you and brings you "
                                     + "to your knees.\n"));
        tell_room(environment(to_be_affected),
                  "A crushing force of discordant sound "
                  + "decends upon "+QTNAME(to_be_affected)+" and brings "
                  + to_be_affected->query_objective()+" to "
                  + to_be_affected->query_possessive() + " knees.\n",
                  to_be_affected);
    }

    return max(21, base_dmg_amount);
}

/* How much mana does using this song drain? */
int
query_mana_cost(int result = -1)
{
    if (result == -1)
    {
        // temporary ugly hack until I can come up with a better way to handle
        // pre-cast mana checks.
        int guild,dex, dis, instrumental, vocal, mod_dex, mod_dis, processed, drm,  dmg_amount;

        dex = this_player()->query_stat(SS_DEX);
        dis = this_player()->query_stat(SS_DIS);
        instrumental = this_player()->query_skill(SG_INSTRUMENTAL);
        vocal = this_player()->query_skill(SG_VOCAL);
        guild = this_player()->query_stat(SS_LAYMAN);
        
        mod_dex = (dex > 100 ? 100 + ((dex - 100) / 2) : dex);
        mod_dis = (dis > 100 ? 100 + ((dis - 100) / 2) : dis);

        processed = (mod_dex+instrumental)+(mod_dis+vocal)+guild*2;
        drm = this_player()->find_drm(SKILL_VALUE, processed);
        result = 100 * (999 + drm - TASK_SIMPLE) / TASK_SIMPLE;
        
        if (result<0)
        {
            return query_mana_cost(21);
        }

        dmg_amount = (BASE_DAMAGE + (result / 2));

        if (dmg_amount > 200)
            dmg_amount = 200; /* reasonable? */
        return query_mana_cost(dmg_amount);

    }
    else
        return BASE_MANA_COST + result / 3;
}

public string
query_name()
{
    return "vibrato";
}
