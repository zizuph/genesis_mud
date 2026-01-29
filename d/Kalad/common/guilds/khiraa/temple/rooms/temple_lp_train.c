/*      /d/Kalad/common/guilds/khiraa/temple/rooms/temple_lp_train
 *      Created by:     Sarr   
 *      Purpose:        
 *      Modified:       Toby, 971009 (fixed typos, plus indents)
 */



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
    set_short("The Lich's Shrine");
    set_long("\n   You have entered a small and comfortable looking "+
    "room. There are tables lining the walls here. In the center of "+
    "the room you see a large dais, upon which sits a giant sculpture "+
    "of a grim looking skull, all made in solid onyx and pure platinum. "+
    "Small sacrifices of herbs and bones are placed around the shrine.\n"+
    "   You belive that this is the worship room of the Khiraa. Here, "+
    "magic powers are learned and gained by Him. The room has an "+
    "aura of great magic surrounding it.\n\n");

    add_item(({"sculpture","skull","shrine","dais"}),"Upon a black "+
    "stone dais stands this mighty shrine dedicated to Him, Lord of "+
    "the Netherworld, Master of the Dead, He whos name is unspeakable. "+
    "The platinum in the skull is focus on the bottom, and rises to "+
    "the top to look like blazing flames burning under the skull. The "+
    "skull is made of pure black onyx. The eyes of the are made of "+
    "pure emerald, and look to be the biggest emeralds you have ever "+
    "seen. The whole shrine stands about 5 feet tall. You feel like "+
    "you could stare into the eyes of the sculpture.\n");

    add_cmd_item(({"into eyes","into eyes of skull"}),"stare","As "+
    "you stare into "+
    "the eyes of the skull a vision enters your mind. You see "+
    "a bleak landscape and in the background, an eerie green glow "+
    "pulses. Along the edges of the landscape, you see what look "+
    "like black, jagged structures. Surrounding the jagged black "+
    "structures you see swarms of strange creatures, both horrifying "+
    "and wonderful. In the center of the swarms, a black "+
    "grim-looking skull with emerald eyes floats. A dark portal, "+
    "blacker than black, stands before it.....the vision then fades.\n");

    add_item("tables","The tables are bare except for a few scraps of "+
    "bones and dried herbs.\n");
    
    create_guild_support();   
    create_skill_raise();
    set_up_skills();

    clone_object(KHIRAA_DIR(temple/doors/shrinedoor2))->move(TO); 
    clone_object(KHIRAA_DIR(temple/obj/stand))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/cauldron))->move(TO);
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
        case SS_SPELLCRAFT:
            what="work with magic better";
        break;
        case SS_ELEMENT_DEATH:
            what="work with death magic better";
        break;
        case SS_ELEMENT_FIRE:
            what="work with fire magic better";
        break;
        case SS_ELEMENT_EARTH:
            what="work with earth magic better";
        break;
        case SS_FORM_ILLUSION:
            what="create illusions better";
        break;
        case SS_FORM_TRANSMUTATION:
            what="transmute magic better";
        break;
        case SS_FORM_ENCHANTMENT:
            what="enchant magic better";
        break;
        case SS_FORM_CONJURATION:
            what="conjure magic better";
        break;
        case SS_FORM_DIVINATION:
            what="see with magic better";
        break;
        case SS_LANGUAGE:
            what ="speak languages better";
        break;
        case SS_HERBALISM:
            what = "work with herbs better";
        break;
        case SS_ALCHEMY:
            what = "work with potions better";
        break;
        default:
            what="do nothing. THIS IS A BUG";
    }
    return what;
}

void
set_up_skills() 
{
    sk_add_train(SS_SPELLCRAFT, train_text(SS_SPELLCRAFT), 0,0,90);
    sk_add_train(SS_ELEMENT_DEATH, train_text(SS_ELEMENT_DEATH), 0,0,90);
    sk_add_train(SS_ELEMENT_FIRE, train_text(SS_ELEMENT_FIRE), 0,0,30);
    sk_add_train(SS_FORM_ILLUSION,train_text(SS_FORM_ILLUSION),0,0,50);    
    sk_add_train(SS_FORM_TRANSMUTATION,train_text(SS_FORM_TRANSMUTATION),0,0,90);
    sk_add_train(SS_FORM_ENCHANTMENT,train_text(SS_FORM_ENCHANTMENT),0,0,50);
    sk_add_train(SS_FORM_CONJURATION,train_text(SS_FORM_CONJURATION),0,0,90);
    sk_add_train(SS_FORM_DIVINATION,train_text(SS_FORM_DIVINATION),0,0,30);
    sk_add_train(SS_HERBALISM,train_text(SS_HERBALISM),0,0,80);
    sk_add_train(SS_LANGUAGE,train_text(SS_LANGUAGE),0,0,80);
    sk_add_train(SS_ALCHEMY,train_text(SS_ALCHEMY),0,0,50);
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
 
    if (!mappingp(sk_default))
        return 0;
    skval = sk_trains[snum];
    if(IS_DK(TP))
    {
        if(snum == SS_SPELLCRAFT)
            return 50;
        if(snum == SS_ELEMENT_DEATH)
            return 50;
        if(snum == SS_FORM_TRANSMUTATION)
            return 50;
        if(snum == SS_HERBALISM)
            return 50;
        if(snum == SS_LANGUAGE)
            return 65;
        if(snum == SS_FORM_CONJURATION)
            return 0;
        if(snum == SS_FORM_DIVINATION)
            return 0;
        if(snum == SS_FORM_ILLUSION)
            return 0;
        if(snum == SS_ALCHEMY)
            return 20;
    }
    if(IS_LP(TP) && snum == SS_FORM_ENCHANTMENT)
        return 0; 
    if(snum == SS_ELEMENT_FIRE)
        return 20;

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
    if (this_level >= sk_query_max(snum))
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
          "                                    _ "+
          "_\n"+
          "-----------------------------------//-"+
          "\\\\------------------------------------\n"+
          "                                   \\\\-"+
          "//\n\n");
}
         
void
sk_hook_skillisting()
{
    write("Here follows all skills we teach, and your next level in " +
          "those skills:\n");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "                                    _ "+
          "_\n"+
          "-----------------------------------//-"+
          "\\\\------------------------------------\n"+
          "                                   \\\\-"+
          "//\n\n");
}
