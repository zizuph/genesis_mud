#pragma save_binary

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h";

inherit NOV_DIR +"temple/std_room";
inherit "/lib/skill_raise";

void set_up_skills();

void
create_nov_room()
{
        set_short("You are standing in the Chamber of Indoctrination");
        set_long("You are standing in the Chamber of Indoctrination. This " +
        "is where you will <learn> or <improve> a variety of skills to aid you " +
        "practicing your craft. The trainer here is an old lich who, as a " +
        "mortal, participated in one of the legendary rituals ensuring that when " +
        "he gave up his life, he would rise to continue training new " +
        "Necromancers. You can't help but admire such a devotion. The room " +
        "has several training utilities but one sand bag in particular " +
        "catches your eye, it has a label on it claiming to a true elf bag.\n");
        
        add_item(({"bag", "sand bag"}),
     "It is a sand bag used for training, the material is smooth " +
     "but strong.\n");
     
       add_item(({"label"}),
     "This bag is guarenteed to be made out of the holiest kind of elf.\n");
     

        add_exit(NOV_DIR + "temple/ncentral",   "southeast");
              
        create_skill_raise();
        set_up_skills();
}

public void 
init()
{
    init_skill_raise();
    ::init();
}


void 
set_up_skills()
{
    string to;

    
    to = "find and locate herbs";
    sk_add_train(SS_HERBALISM,              ({ to, to }),  0,0, 60);
    
     to = "mix potions and do laboratory work";
    sk_add_train(SS_ALCHEMY,                ({ to, to }),  0,0, 60);
    
    to = "understand the craft of the arcane";
    sk_add_train(SS_SPELLCRAFT,             ({ to, to }),  0,0, 60);
        
    
    //**************************************************************
    
    to = "cast conjuration magic";
    sk_add_train(SS_FORM_CONJURATION,       ({ to, to }),  0,0, 50);
    
    //**************************************************************
    
    to = "cast necromancy";
    sk_add_train(SS_ELEMENT_DEATH,          ({ to, to }),  0,0, 60);
    
     to = "cast water";
    sk_add_train(SS_ELEMENT_WATER,          ({ to, to }),  0,0, 55);
    
    //**************************************************************
        
    to = "fight unarmed";
    sk_add_train(SS_WEP_CLUB,               ({ to, to }),  0,0, 50);
        
    to = "defend yourself";
    sk_add_train(SS_DEFENCE,                ({ to, to }),  0,0, 50);
    
    to = "defend yourself";
    sk_add_train(SS_PARRY,                  ({ to, to }),  0,0, 50);
    
    //**************************************************************
    


}



void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;



    rank = sk_rank(to_lev);

    this_player()->catch_msg("You teach yourself to "+
        sk_tdesc[snum][0] + " better.\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(this_player()) + " teaches "+this_player()->query_objective()+"self to "+
        sk_tdesc[snum][1] + " and receives "+
        "the rank of " + rank + ".\n");
}

int
sk_improve(string str)
{
    if (this_player()->query_guild_name_lay() != GUILDNAME)
    {
        write("You are not allowed to train here!\n");
        return 1;
    }

    return ::sk_improve(str);
}
