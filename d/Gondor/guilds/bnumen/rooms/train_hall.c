/*
 * Train hall of the Black Numenoreans
 * 
 * Olorin, 14-nov-1994
 * Modified from dunedains for use with Black 
 *    Numenorean guild: Aug. 2006
 * Black Numenorean Skills/Tax computation					
 * Adv. Guild       Max.		        multiplier		
 * SS_SNEAK  20    (50 levels)  20  30  1.00    30.000  0.50
 * SS_HIDE  20     (50 levels)  20  30  1.00    30.000  0.50
 * SS_BACKSTAB  0  (50 levels)   0  50  1.50    75.000  1.25
 * SS_WEP_KNIFE 30 (50 levels)  30  20  1.00    20.000  0.33
 * SS_AWARENESS 30 (50 levels)  30  20  1.00    20.000  0.33
 *                                 150                  2.92

 * Some additional Adventurer level skills              0.00
 * 
 * Special dock for Numenorean ship                     1.00
 * Total                                                3.92
 *
 * Adventurer's guild level skills                      0.00
 * (see below)
 * 
 * Weapon skills  
 *   SS_WEP_SWORD:      30 
 *   SS_WEP_POLEARM:    30 
 *   SS_WEP_AXE:        30 
 *   SS_WEP_KNIFE:      30 
 *   SS_WEP_CLUB:       30 
 *   SS_WEP_MISSILE:    30 
 * General fighting skills 
 *   SS_UNARM_COMBAT:   30 
 *   SS_DEFENCE:        30 
 * Magic skills
 *   SS_BLIND_COMBAT:   20 
 *   SS_SPELLCRAFT:     20 
 *   SS_HERBALISM:      20 
 *   SS_ALCHEMY:        20 
 *   SS_ELEMENT_FIRE:   20 
 *   SS_ELEMENT_AIR:    20 
 *   SS_ELEMENT_EARTH:  20 
 *   SS_ELEMENT_WATER:  20 
 *   SS_ELEMENT_LIFE:   20 
 *   SS_ELEMENT_DEATH:  20 
 * Thief skills 
 *   SS_OPEN_LOCK:      20 
 *   SS_PICK_POCKET:    20 
 *   SS_ACROBAT:        20 
 *   SS_FR_TRAP:        20 
 * General skills 
 *   SS_APPR_MON:       30 
 *   SS_APPR_OBJ:       30 
 *   SS_APPR_VAL:       30 
 *   SS_SWIM:           30 
 *   SS_CLIMB:          30 
 *   SS_HUNTING:        30 
 *   SS_LANGUAGE:       30 
 *   SS_TRADING:        30 
 *
 */


#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";
inherit "/d/Shire/lib/training";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"
#define HIS(x)  ((x)->query_possessive())

public void set_up_skills();
public string exa_poster();

public void
create_cabin() 
{ 
    set_short("Training chamber of the Black Numenoreans");
    set_long( "In this chamber members of the " +
        "Houses of the Black Numenoreans can meditate and train. " +
        long_cabin_level_1(0) + "In a corner there is a thick " +
        "carpet where they can sit down while " +
        "meditating. The rest of the floor is cleared for " +
        "purposes of training. Members may <list guilds> and improve their " +
        "skills here. There is a poster tacked to the wall.\n");

    add_item(({"carpet", }), 
        "A thick and valuable carpet. The Black Numenoreans use it to "
      + "sit down upon it while meditating.\n");
    floor(0);
    walls(0); 
    ceiling(0);
    add_exit(BNUMEN_DIR + "ship/ncabin_hall1", "port", check_exit());
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    FIX_EUID;
    create_skill_raise();
    set_up_skills();
    add_item( ({"poster", "skill list", "skill-list", "list"}),
	exa_poster());
    add_cmd_item( ({"poster", "skill list", "skill-list", "list"}),
	"read", exa_poster());
}


public void
init() 
{
    ::init();
    init_guild_support();
    init_skill_raise();
}

int
gs_hook_already_meditate()
{
    write("You are already meditating. If you wish to finish "+
        "your meditation, simply 'rise' from the floor.\n");
    return 1;
}

void
gs_hook_start_meditate()
{ 
    write("You sit down on the thick carpet and close your eyes. "
      + "Your spirit disentangles itself from the confines of the "
      + "material world. You find yourself able to <estimate> your "
      + "different preferences and <set> them at your own desire. "
      + "Just <rise> when you want your spirit to return to your body.\n");
    say(QCTNAME(TP) + " sits down on the carpet and closes "+HIS(TP)+" eyes.\n");
}

void
gs_hook_rise() 
{
    write("As you decide to return to the material world, your "
      + "spirit enters your body again and you feel a new sense of "
      + "power and control.\n");
    say(QCTNAME(TP) + " rises from the carpet.\n");
}

public int
sk_query_max(int skill, int silent)
{    
    object tp = this_player();

    switch(skill)
    {
        case SS_SNEAK:
        case SS_HIDE:
        case SS_BACKSTAB:
        case SS_WEP_KNIFE:
        case SS_AWARENESS:
            return 50;
            break;
        case SS_WEP_SWORD:
        case SS_UNARM_COMBAT: 
        case SS_DEFENCE:
        case SS_APPR_MON:
        case SS_APPR_OBJ:  
        case SS_APPR_VAL: 
        case SS_SWIM: 
        case SS_CLIMB: 
        case SS_HUNTING: 
        case SS_LANGUAGE: 
        case SS_TRADING: 
            return 30;
            break;
        case SS_BLIND_COMBAT:  
        case SS_SPELLCRAFT:
        case SS_HERBALISM: 
        case SS_OPEN_LOCK:  
        case SS_PICK_POCKET:  
        case SS_ACROBAT:     
        case SS_FR_TRAP:    
            return 20;
            break;
        default:
            return 0;
            break;
    }
}

/*
 * Function name:	set_up_skills
 * Description	:	add all the BN skills
 */
public void 
set_up_skills()
{
    string me;
    object tp = this_player();
    
    me = "sneak and move stealthily about";
    sk_add_train(SS_SNEAK, ({ me, me }), 0, 0, 50, -1, 0);
    me = "hide and conceal";
    sk_add_train(SS_HIDE,	({ me, me }), 0, 0, 50, -1, 0);
    me = "attack your enemy with treachery";
    sk_add_train(SS_BACKSTAB,	({ me, me }), 0, 0, 50, -1, 0);
    me = "use a knife or dagger";
    sk_add_train(SS_WEP_KNIFE,({ me, me }), 0, 0, 50, -1, 0);
    me = "be aware of the surroundings";
    sk_add_train(SS_AWARENESS, ({ me, me }), 0,0 , 50, -1, 0);
    me = "use a sword effectively";
    sk_add_train(SS_WEP_SWORD, ({ me, me }), 0, 0 , 30, -1, 0);
    me = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT, ({ me, me }), 0, 0, 30, -1, 0);
    me = "defend oneself";
    sk_add_train(SS_DEFENCE, ({ me, me }), 0, 0, 30, -1, 0);
    me = "appraise the enemy";
    sk_add_train(SS_APPR_MON, ({ me, me }), 0, 0, 30, -1, 0);
    me = "appraise objects";
    sk_add_train(SS_APPR_OBJ, ({ me, me }), 0, 0, 30, -1, 0);    
    me = "appraise value";
    sk_add_train(SS_APPR_VAL, ({ me, me }), 0, 0, 30, -1, 0);
    me = "swim";
    sk_add_train(SS_SWIM, ({ me, me }), 0, 0, 30, -1, 0);
    me = "climb with agility";
    sk_add_train(SS_CLIMB, ({ me, me }), 0, 0, 30, -1, 0);
    me = "hunt an enemy";
    sk_add_train(SS_HUNTING, ({ me, me }), 0, 0, 30, -1, 0);
    me = "learn languages";
    sk_add_train(SS_LANGUAGE, ({ me, me }), 0, 0, 30, -1, 0);
    me = "trade with merchants";
    sk_add_train(SS_TRADING, ({ me, me }), 0, 0 , 30, -1, 0);
    me = "fight in the dark";
    sk_add_train(SS_TRADING, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "fight in the dark";
    sk_add_train(SS_TRADING, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "cast spells";
    sk_add_train(SS_SPELLCRAFT, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "identify and find herbs";
    sk_add_train(SS_HERBALISM, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "pick locks";
    sk_add_train(SS_OPEN_LOCK, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "pick pockets";
    sk_add_train(SS_PICK_POCKET, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "move with the agility of an acrobat";
    sk_add_train(SS_ACROBAT, ({ me, me }), 0, 0 , 20, -1, 0);
    me = "find and remove traps";
    sk_add_train(SS_FR_TRAP, ({ me, me }), 0, 0 , 20, -1, 0);     
    return;

}
/*
 * Function name: sk_do_train
 * Description:   Let a player train a skill a certain number of levels
 * Arguments:     snum:   Skill number
 *		  pl:     Player to train
 *		  to_lev: To which level to train the player in the skill
 * Returns:       True if success
 */
public int
sk_do_train(int snum, object pl, int to_lev)
{
    object  tp = TP;

    if (!IS_MEMBER(tp))
    {
	write("Only members of the Black Numenorean guild may train here!\n");
	return 0;
    }

    return ::sk_do_train(snum, pl, to_lev);
}
int
sk_improve(string str)
{
    if (!IS_MEMBER(TP))
    {
	write("Only members of the Black Numenorean guild may train here!\n");
	return 1;
    }

    return ::sk_improve(str);
}

void
sk_hook_write_header(int steps)
{
    if (!steps)
	steps = 1;

    write("  Skill:                Cost:      "+
      "Next level:           Max level:\n"+
      "--------------------------------------"+
      "--------------------------------------\n");
}

void
sk_hook_skillisting()
{

    write("  Skill:                Cost:      "+
      "Next level:          Max level:\n"+
      "--------------------------------------"+
      "--------------------------------------\n");
}

/*
 * Function name: exa_poster
 * Description	: general text for the poster - displays the skills for
 *                the guild
 * Returns	: string - the description
 */
public string 
exa_poster()
{
    int i, size, snum, smax, *guild_sk = sk_query_train();
    string list;

    list = "These are the skills you can train here if you are a " +
        "member of the Black Numenoreans:\n\n";

    guild_sk = sort_array(guild_sk);
    for (i = 0, size = sizeof(guild_sk); i < size; i++)
    {
        snum = guild_sk[i];
        smax = ::sk_query_max(snum, 0);
        if (smax)
        {
            list += sprintf("  %-25s  %-25s\n", sk_trains[snum][0],
                sk_rank(smax));
        }
    }

    return list + "\n";
}
