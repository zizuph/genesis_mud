/*  /d/Faerun/alchemy/npc/pushy.c
*
*   Alchemy npc. May drop a large alchemy set.
*
*   Nerull 2021
* 
*/

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "../defs.h"

#define ALCHEMY_DIR "/d/Faerun/alchemy/"

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";

int has_alchemyset;


void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    has_alchemyset = 1;

    npc_name = "pushy";

    add_adj("hysterial");
    add_adj("nervous");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name(npc_name);
    add_name("man");
    
    set_short("hysterical nervous man");
    
    set_long("This is a bald man with many burns "
    +"decorating his barren skin. You think they are "
    +"marks of failed experiments in either magic "
    +"or unstable alchemy. He is clad in dark stained "
    +"leatherclothes and looks rather unstable judging "
    +"by his darting eyes.\n");
        
    set_gender(G_MALE);
    add_prop(CONT_I_WEIGHT,95000);
    add_prop(CONT_I_HEIGHT,190);
    
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 190 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_ACROBAT,90);
    set_skill(SS_PARRY,90);
     
    add_ask( ({"alchemy"}), "say Yes! I am an alchemist! I love "
    +"experimenting with components and recipes to create new "
    +"substances with my large alchemy set, particulary brews that alters the mind. Once "
    +"I knew many recipes, but after my overconsumption of distilled "
    +"mushrooms from the forest of Raumdor, I no longer can remember "
    +"a thing. Do I know you? You are my friend, right?", 1);
    
    add_ask( ({ "recipe", "recipes" }), "say The only recipe I "
    +"remember that I'm willing to share is...hmm...I forgot! But, it's quite "
    +"nice to know when I use my large alchemy set to create the..hmm...damn. I "
    +"even forgot the name of the brew.", 1);
    
    if (has_alchemyset == 1)
    {
        add_ask( ({ "alchemy set", "set", "large alchemy set" }), "say No! It's mine I tell you! You "
        +"can't have it! You can only pry it from my cold dead hands!", 1);
    }
    else
    {
        add_ask( ({ "alchemy set", "set", "large alchemy set" }), "say What about it? It was stolen "
        +"from me recently by some kender thief...thing! Kender, nine feet tall, bald head "
        +"and massive clubs in each hand. Seen him? Damn kenders!", 1);
    }
 
   /* Actions */
    set_act_time(5);
    set_cact_time(5);
    add_act("ponder");
    add_act("emote looks nervous at you.");
    add_act("emote mumbles about some recipe.");
    add_act("emote scratches one of his many burned marks.");
    add_act("emote picks up a glass-beaker from one of his "
    +"pockets and inspects its content "
    +"before spilling it out on the ground.");
    
    add_cact("emote screams for help!");
    add_cact("emote cries: What did I ever do to you?");
    add_cact("emote shouts: Heeelp! Heeeelp me!");
    add_cact("emote cries: Stop hurting me!");
   
    add_prop(LIVE_I_NEVERKNOWN, 1); 
}


int query_hasset()
{
    return has_alchemyset;
}


void
do_die(object killer)
{
    if (has_alchemyset == 1)
    {
        clone_object(ALCHEMY_DIR +"large_alchemy_set")->move(this_object(), 1);
    }
    
    PUSHY_DIED_LOG("pushy_log",
    "The player "+this_player()->query_name()
    +" killed pushy.\n");
    		
    ::do_die(killer);
}