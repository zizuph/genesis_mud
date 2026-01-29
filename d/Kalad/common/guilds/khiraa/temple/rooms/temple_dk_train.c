inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <money.h>

void set_up_skills();

void
create_room() 
{
    ::create_room();
    INSIDE;
    set_short("The Death Warrior's Room");
    set_long("\n   You have entered a dark and gloomy room. The room "+
    "is quite large, and you can see by the light cast by the large "+
    "braziers in the center of the room. The stench of rotting "+
    "flesh is strong here.\n"+
    "   Many wooden poles dot the "+
    "room, and they are covered with blood. A rack of old iron "+
    "weapons stands against one wall. In the far corner, you see "+
    "a cage of prisoners.\n\n");
    add_item("cage","The cage is filled with dirty, downtrodden "+
    "prisoners. Captured by the Khiraa from the lands, they are "+
    "used as practice for Death Knights. Then their corpses are "+
    "taken to the Priesthood's Sacrifice chamber, where experiments "+
    "are done on them.\n");
    add_item("poles","They are strong sturdy wooden poles covered "+
    "with what looks like blood.\n");
    add_item("prisoners","They are huddled together on the dirty "+
    "cage floor.\n");
    add_item("rack","The rack contains old iron weapons for "+
    "training.\n");
    add_item("braziers","The braziers burn an eerie purple-black "+
    "flame, casting some light in the room.\n");
    create_guild_support();   
    create_skill_raise();
    set_up_skills();
    clone_object(KHIRAA_DIR(temple/doors/traindoor2))->move(TO);
}

void
init() 
{
    init_guild_support();
    init_skill_raise();
    ::init();
}


string
train_text(int skill) 
{
    string what;
    switch(skill) 
    {
        case SS_WEP_SWORD:
            what="fight with swords better";
        break;
        case SS_WEP_POLEARM:
            what="fight with polearms better";
        break;
        case SS_DEFENSE:
            what="defend against general attacks better";
        break;
        case SS_PARRY:
            what="defend with weapons better";
        break;
        case SS_2H_COMBAT:
            what="fight with two weapons better";
        break;
        case SS_WHIRLWIND:
            what="preform the whirlwind of death attack better";
        break;
        case SS_BASHSTUN:
            what="preform the stunbash attack better";
        break;
        case SS_APPR_MON:
            what="judge the powers of opponents better";
        break;
        case SS_TRACKING:
            what="to hunt and track people better";
        break;
        default:
            what="do nothing. THIS IS A BUG";
    }
    return what;
}

void
set_up_skills() 
{
    sk_add_train(SS_WEP_SWORD, train_text(SS_WEP_SWORD), 0,0,100);
    sk_add_train(SS_DEFENSE, train_text(SS_DEFENSE), 0,0,80);
    sk_add_train(SS_2H_COMBAT, train_text(SS_2H_COMBAT), 0,0,80);
    sk_add_train(SS_PARRY, train_text(SS_PARRY), 0,0,90);
    sk_add_train(SS_WHIRLWIND,train_text(SS_WHIRLWIND),"whirlwind",80,100);
    sk_add_train(SS_BASHSTUN, train_text(SS_BASHSTUN),"stunbash",80,100);
    sk_add_train(SS_APPR_MON, train_text(SS_APPR_MON), 0,0,65);
    sk_add_train(SS_TRACKING,train_text(SS_TRACKING),0,0,55);
    sk_add_train(SS_WEP_POLEARM,train_text(SS_WEP_POLEARM),0,0,65);
    sk_add_train(SS_GOUGE,"preform the gouging attack better","gouge",80,100);
    sk_add_train(SS_WEP_KNIFE,"fight with knives better",0,0,50);
    sk_add_train(SS_AWARENESS,"be aware better",0,0,60);
    sk_add_train(SS_APPR_VAL,"appraise object values better",0,0,70);
}


/*
 * Function name: sk_filter_improve
 * Description:   Filter out what skills this player can improve
 * Arguments:     sk    - The skill
 *                steps - The number of steps player wants to improve
 * Returns:       1 if play can improve skill
 */

int
sk_filter_improve(int sk, int steps)
{
    if(IS_DK(TP) || IS_LP(TP))
        return 1; /* Show all skills */
    return 0;
}

int
sk_filter_learn(int sk, int steps)
{
    if(IS_DK(TP) || IS_LP(TP))
        return 1; /* Show all skills */
    return 0;
}

int
sk_find_skill(string skname)
{
    if(IS_DK(TP) || IS_LP(TP))
        return ::sk_find_skill(skname);
    return -1;
}

/*
 * Function name: sk_query_max
 * Description  : Give the max skill we can teach to for a skill.
 * Arguments    : int snum - the skill-number to check.
 *                int silent - don't tell anything to the player if true.
 * Returns      : int - the maximum you can train the skill to.
 */
public varargs int
sk_query_max(int snum, int silent)
{
    mixed skval;
    int guild_level;
 
    if (!mappingp(sk_default))
        return 0;
    skval = sk_trains[snum];
    guild_level = TP->query_guild_order();

    if(IS_LP(TP))
    {
        if(snum == SS_WEP_SWORD)
            return 50;
        if(snum == SS_DEFENSE)
            return 50;
        if(snum == SS_2H_COMBAT)
            return 0;
        if(snum == SS_WEP_POLEARM)
            return 65;
        if(snum == SS_PARRY)
            return 50;
        if(snum == SS_WHIRLWIND)
            return 0;
        if(snum == SS_BASHSTUN)
            return 0;
        if(snum == SS_APPR_MON)
            return 50;
        if(snum == SS_TRACKING)
            return 50;
    }
    if(IS_DK(TP) && snum == SS_WEP_SWORD)
    {
	if(guild_level >=10 && TP->test_bit("Kalad",3,3) )
            return 100;

        return MIN(100,(45 + (guild_level * 5) ));
    }
    if(IS_DK(TP) && snum == SS_DEFENSE)
        return MIN(80, (50 + (guild_level * 5) ));
    
    if(IS_DK(TP) && snum == SS_PARRY)
        return MIN(90, (50 + (guild_level * 5) ));
    if(IS_DK(TP) && snum == SS_2H_COMBAT)
        return MIN(80, (45 + (guild_level * 5) ));
    if(IS_DK(TP) && snum == SS_WHIRLWIND)
        return MIN(100, (60 + (guild_level * 5) ));
    if(IS_DK(TP) && snum == SS_BASHSTUN)
        return MIN(100, (60 + (guild_level * 5) ));

    if(IS_DK(TP) && snum == SS_WEP_POLEARM)
        return 30; 
    if(IS_DK(TP) && snum == SS_GOUGE)
        return 0;
    if(IS_DK(TP) && snum == SS_WEP_KNIFE)
        return 30;
    if(IS_DK(TP) && snum == SS_AWARENESS)
        return 50;
    if(IS_DK(TP) && snum == SS_APPR_VAL)
        return 30;
    if (sizeof(skval)>2)
        return skval[2];
    else
        return 0;
}

public string
sk_rank(int lev)
{
    int subl, mainl;
 
    if (!desc)
        create_skill_raise();
 
    if (!lev || lev < 0)
        return "NA";
    if (--lev > 99)
        lev = 99;
    mainl = (lev / sizeof(desc));
    if (mainl >= sizeof(desc))
        mainl = sizeof(desc) - 1;
 
    subl = (100 / sizeof(desc));
 
    subl = sizeof(subdesc) * (lev % subl) / subl;
 
    return (strlen(subdesc[subl]) ? subdesc[subl] + " " : "") +
desc[mainl];
}

string
spit_comp(int cc)
{
    int *coins;
    string str, ctype;
    int i;
    coins = MONEY_SPLIT(cc);
    str = "";
    for(i=0;i<sizeof(coins);i++)
    {
        if(coins[i] != 0)
        {
            ctype = "buggy";
            if(i == 0)
                ctype = "c";
            if(i == 1)
                ctype = "s";
            if(i == 2)
                ctype = "g";
            if(i == 3)
                ctype = "p";
            str += coins[i]+ctype+" ";
        }
    }
    return str;
}


varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max;
    string next_rank, max_rank, cost;
    this_level = this_player()->query_base_skill(snum);
    next_level = steps ? this_level + steps : this_level + 1;
    if (next_level > (max = sk_query_max(snum)))
        cost = "---";
    else
        cost = spit_comp( sk_cost(snum, this_level, next_level) );
    if (this_level >= max)
        next_rank = "maxed";
    else
        next_rank = sk_rank(next_level);
    max_rank = sk_rank(max);
    if(max_rank == "NA")
        next_rank = "NA";
    return sprintf("  %-17s %16s  %-17s %-20s\n", sk_trains[snum][0],
                cost, next_rank, max_rank);
}

void
sk_hook_write_header(int steps)
{
    if (!steps)
        steps = 1;
    write("These are the skills you are able to " + query_verb() +
        " " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
        " here.\n");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "                                   `_ "+
          " _'\n"+
          "-----------------------------------<-\\"+
          "/->-----------------------------------\n"+
          "                                   /\\|"+
          "|/\\\n\n");
}
         
void
sk_hook_skillisting()
{
    write("Here follows all skills we teach, and your next level in " +
          "those skills:\n");
    write("  Skill:                Cost:      "+
          "Next level:          Max level:\n"+
          "                                   `_ "+
          " _'\n"+
          "-----------------------------------<-\\"+
          "/->-----------------------------------\n"+
          "                                   /\\|"+
          "|/\\\n\n");
}
