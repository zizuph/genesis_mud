/* 
 * mpparaise.h
 *
 * Cirion, May 10, 1998
 *
 * Monk ability to appraise different armour coverings.
 *
 * This ability allows the monk to appraise the protection
 * of an enemy, and is meant to be used in conjunction with
 * their ability to strike at a certain hitloc. If the monk
 * is able to discern which body parts are the least protected,
 * then they will better be able to judge where to strike. The
 * command works differently when used on humanoids or
 * non-humanoids:
 *
 * humanoids: this command will go over all the armours the
 *     target is wearing and evaluate their strengths (the
 *     ac of the armours), and give a textual description
 *     of the the strength.
 *
 * non-humanoids: the command will go over all the available
 *     hitlocs on the target and evaluate their strengths
 *     (the ac of the hitloc itself).
 *
 * Appraisals are done in a way similiar to the appraise_object()
 * function in /std/object.c. When appraising an armour, the
 * player's SS_APPR_OBJ skills is used to determine success.
 * When appraising an ememy's hitloc, SS_APPR_MON skill is used.
 * Appraisals will be pseudo-random based on these skills, but
 * will always remain constant for an instance of a given
 * object (using the object's OB_NUM as the seed). Thus, a
 * player will not be able to appraise multiple times and
 * take the average of the appraisals to get the exact value.
 */

#include <ss_types.h>
#include <composite.h>
#include "/std/combat/combat.h"

/******************************************************
 *        Function Prototypes
 */
varargs nomask private string
appraise_hitloc_strength(int hit_ac, object mon, object for_who = this_player());
varargs nomask private string
appraise_armour_strength(object arm, object for_who = this_player());


/*
 * Function name: mappraise
 * Description:   command that allows a monk to appraise
 *                the different hitlocs and armour coverings
 *                of an enemy.
 * Arguments:     str - the command arguments
 * Returns:       1 if successful
 */
public int
mappraise (string str)
{
    object *oblist, target, arm, cobj;
    string msg, nat_desc, hitloc_desc, *unarmoured_areas = ({});
    int    app_obj, app_enemy, *hit_ids, i, humanoid, has_arm, natural_str, plural;
    mixed  * hit_data;

    msg = "";

    if (!strlen(str))
    {
        write ("Appraise the defences of who?\n");
    	return 1;
    }

    oblist = parse_this(str, "[the] / [a] %l");

    if (!sizeof(oblist))
    {
        write ("Appraise the defences of who?\n");
    	return 1;
    }

    target = oblist[0];
    app_obj = this_player()->query_skill(SS_APPR_OBJ);

    if (app_obj <= 2)
    {
        write ("You would first need to improve your skills in "
            + "object appraisal.\n");
        return 1;
    }

    app_enemy = this_player()->query_skill(SS_APPR_MON);
    humanoid = target->query_humanoid();
    has_arm = sizeof(target->query_armour(-1));

    if (app_enemy <= 2)
    {
        write ("You would first need to improve your ability "
            + "to appraise other creatures.\n");
        return 1;
    }

    /* Get the target's hitlocs.    */
    cobj = target->query_combat_object();
    hit_ids = cobj->query_hitloc_id();

    if (!sizeof(hit_ids))
    {
        write ("Your sensitive mind notices that something is "
            + "awry.\n");
        return 1;
    }

    for (i=0;i<sizeof(hit_ids);i++)
    {
        hit_data = cobj->query_hitloc(hit_ids[i]);

        if (sizeof(hit_data) < 3)
        {
            write ("Your sensitive mind notices that something is "
                + "awry.\n");
            return 1;
        }

        arm = target->query_armour(hit_ids[i]);

        hitloc_desc = hit_data[HIT_DESC];

        plural = (extract(hitloc_desc, strlen(hitloc_desc) - 1) == "s");


        /* Describe things differently if the target is humanoid    */
        /* or non-hunanoid:                                         */
        /* Humanoids: go over all the amrours the target is wearing */
        /*    and appraise their strengths.                         */
        /* Non-humanoids: appraise the strengths of the hitlocs     */
        /*    themselves of the target.                             */
        if (humanoid)
        {
            /* standard humanoid hitlocs have a very low natural    */
            /* hitloc value, so we will ignore it if it is          */
            /* less than a certain number (4). Otherwise,           */
            /* describe the strength of the hitloc.                 */
            natural_str = m_average_array(hit_data[HIT_AC]);

            if (natural_str <= 4)
                nat_desc = "";
            else
                nat_desc = appraise_hitloc_strength(natural_str, target) + " ";


            /* Enemy is wearing armour on the hit desc. */
            if (objectp(arm))
            {
                msg = msg + "The " + arm->short(this_player()) + " covering "
                    + target->query_possessive() + " " + nat_desc
                    + hitloc_desc
                    + " appears to offer " + appraise_armour_strength(arm)
                    + " protection.\n";
            }
            else
            {
                unarmoured_areas += ({ (nat_desc + hitloc_desc) });
            }
        }
        else // non-humanoid target: give different description
        {
            msg = msg + capitalize(target->query_possessive()) + " "
                + (has_arm ? "unprotected " : "")
                + hitloc_desc + (plural ? " appear " : " appears ")
                + appraise_hitloc_strength(m_average_array(hit_data[HIT_AC]), target)
                + ".\n";
        }

    }

    if (i = sizeof (unarmoured_areas))
    {
        msg = msg + capitalize(target->query_possessive()) + " "
            + COMPOSITE_WORDS(unarmoured_areas) + (i > 1 ? " are" : " is")
            + " unprotected by armour.\n";
    }

    write(msg);

    SOULDESC("concentrating deeply on something");
    return 1;
}



/*
 * Function name: cut_sig_fig
 * Description:   Will reduce the number given to a new number with two
 *                significant numbers.
 * Arguments:     fig - the number to correct.
 * Returns:       the number with two significant numbers
 */
public int
cut_sig_fig(int fig)
{
    int fac;
    fac = 1;

    while(fig > 100)
    {
        fac = fac * 10;
        fig = fig / 10;
    }
    return fig * fac;
}


/*
 * Function name: appraise_armour_strength
 * Description:   appraise the strength of the piece of armour
 *                on an enemy. This is done using the same
 *                formula in /std/object that prevents
 *                a player from doing this multiple
 *                times and taking an average of the
 *                results: it will always give back the
 *                same result for a certain instance of
 *                an object.
 * Arguments:     arm: the armour to appraise
 *                who: who is arrpaising (default this_player())
 * Returns:       the string description of the amrour's strength
 */
varargs nomask private string
appraise_armour_strength(object arm, object for_who = this_player())
{
    int ac, skill, seed;
    string str;

    skill = for_who->query_skill(SS_APPR_OBJ);

    skill = 1000 / (skill + 1);
    ac = arm->query_ac();

    sscanf(OB_NUM(arm), "%d", seed);
    skill = random(skill, seed);

    // write("Old ac: " + ac + "\n");
    // write("Adjusted skill: " + skill + "\n");

    ac = cut_sig_fig(ac + (skill % 2 ? -skill % 70 : skill) *
        ac / 100);

    // write("New ac: " + ac + "\n");

    // sanity check
    if (ac < 0)
        ac = 0;

    switch(ac)
    {
        case 0 .. 2:
            str = "flimsy";        
            break;
        case 3 .. 5:
            str = "feeble";        
            break;
        case 6 .. 8:
            str = "little";        
            break;
        case 9 .. 12:
            str = "some";        
            break;
        case 13 .. 18:
            str = "a bit of";        
            break;
        case 19 .. 24:
            str = "fair";
            break;
        case 25 .. 28:
            str = "good";        
            break;
        case 29 .. 33:
            str = "considerable";        
            break;
        case 34 .. 37:
            str = "very good";        
            break;
        case 38 .. 41:
            str = "excellent";        
            break;
        case 42 .. 47:
            str = "fantastic";        
            break;
        default:
            str = "impenetrable";        
            break;
        
    }

    // write("Sending back: " + str + "\n");

    return str;
}


/*
 * Function name: appraise_hitloc_strength
 * Description:   appraise the strength of a certain hitloc
 *                on an enemy. This is done using the same
 *                formula in /std/object that prevents
 *                a player from doing this multiple
 *                times and taking an average of the
 *                results: it will always give back the
 *                same result for a certain instance of
 *                an object.
 * Arguments:     hit_ac: the ac of the hitloc to appraise
 *                mon: the monster on whom we are appraising
 *                who: who is appraising (default this_player())
 * Returns:       the string description of the amrour's strength
 */
varargs nomask private string
appraise_hitloc_strength(int hit_ac, object mon, object for_who = this_player())
{
    int skill, seed;
    string str;

    skill = for_who->query_skill(SS_APPR_MON);

    skill = 1000 / (skill + 1);

    sscanf(OB_NUM(mon), "%d", seed);
    skill = random(skill, seed);

    // write("Old ac: " + hit_ac + "\n");
    // write("Adjusted skill: " + skill + "\n");


    hit_ac = cut_sig_fig(hit_ac + (skill % 2 ? -skill % 70 : skill) *
        hit_ac / 100);

    // write("New ac: " + hit_ac + "\n");

    // sanity check
    if (hit_ac < 0)
        hit_ac = 0;

    switch(hit_ac)
    {
        case 0 .. 1:
            str = "very fragile";
            break;
        case 2 .. 2:
            str = "fragile";
            break;
        case 3 .. 3:
            str = "rather frail";        
            break;
        case 4 .. 4:
            str = "frail";        
            break;
        case 5 .. 5:
            str = "delicate";        
            break;
        case 6 .. 8:
            str = "weak";        
            break;
        case 9 .. 12:
            str = "sturdy";        
            break;
        case 13 .. 18:
            str = "strong";        
            break;
        case 19 .. 24:
            str = "tough";
            break;
       case 25 .. 28:
            str = "robust";  
            break;
        case 29 .. 34:
            str = "rugged";        
            break;
        case 35 .. 46:
            str = "very rugged";        
            break;
        default:
            str = "invincible";        
            break;
    }

    // write("Sending back: " + str + "\n");

    return str;
}

