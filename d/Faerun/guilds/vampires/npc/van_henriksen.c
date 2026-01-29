/*  /d/Faerun/guilds/vampires/npc/van_henriksen.c
*
*   Questnpc for the Vampire guild.
*
*   Nerull 2021
* 
*/
inherit "/d/Faerun/std/faerun_npc";
inherit "/d/Faerun/lib/assist_friend";

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "../guild.h"



#define BLOODSAMPLE  "_hunting_for_bloodsample"

int dialogue;
int do_aid1_int;
int do_aid2_int;

int do_vorador_int;
int do_moebius_int;
int do_nupraptor_int;

int dice = 0;

int
do_vorador()
{
    switch(do_vorador_int)
    {
        case 0:
        this_object()->command("emote says: The ancient vampire Vorador...\n");
        break;
        
        case 1:
        this_object()->command("emote says: This vampire is known to be "
        +"very paranoid and a very talented artist. He is of human origin, "
        +"but his appearance is unknown. He is still active, recruiting "
        +"and stalking the living throughout the lands of Genesis...\n");
        break;
        
        case 2:
        this_object()->command("emote says: He is the creator of several "
        +"pieces of art, particularly paintings, that are also magically "
        +"enchanted to only reveal their true meaning to the right "
        +"individual and that only at auspicious moments. For others, "
        +"the paintings will look like some "
        +"abstract art that is not understandable. A peasant "
        +"may have such a painting on his wall, displaying its "
        +"content for years without ever knowing its true purpose...\n");
        break;
        
        case 3:
        this_object()->command("emote says: One thing is certain: that this is the "
        +"hidden way in which Vorador selects new candidates to turn into "
        +"vampires or vampire familiars under his domination. The academics "
        +"are surely uncertain of this hypothesis, but most agree "
        +"that everyone who supposedly managed to interpret the "
        +"meaning of his art has ended up missing, dead, or possibly "
        +"even worse...\n");
        break;
        
        case 4:
        this_object()->command("emote says: Vorador must be found and "
        +"destroyed. Though, due to his paranoid nature, it is speculated "
        +"that to ever have a chance to find him, one must follow every "
        +"possible clue to reveal his whereabouts. However, this is not an "
        +"endeavor I would want you to pursue...\n");
        break;
        
        case 5:
        this_object()->command("emote says: ...unless you are absolutely "
        +"sure you are strong and competent enough. Be warned though, "
        +"this is an extremely hard task that would almost certain end "
        +"with your demise, or worse. I have sent several seasoned "
        +"adventurers, knights and cutthroats alike to track down "
        +"Vorador, but none has returned so far. They are most likely "
        +"no longer among the living...\n");
        break;
        
        case 6:
        this_object()->command("emote says: ...But, I will let you "
        +"decide, and I need the help. The realms needs every help "
        +"it can get to get rid of these abominations and to ensure "
        +"the safety of our people.\n");
        
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 0)
        {       
            VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), 1);
            
            if (!present("_seekercleanse_countdown_ob", this_player()))
            {
                clone_object(VAMPIRES_GUILD_DIR +"obj/seekercleanse_countdown_ob")->move(this_player(), 1);
            }
        }
        
        break;
    }
    
    // Finished talking
    if (do_vorador_int == 7)
    {
        dialogue = 0;
        do_vorador_int = 0;
        
        return 1;
    }
    
    do_vorador_int = do_vorador_int + 1;
    
    set_alarm(7.0, 0.0, &do_vorador());
    
    return 1;
}


int
do_aid2()
{
    switch(do_aid2_int)
    {
        case 0:
        this_object()->command("emote says: I am hunting various abominations "
        +"in the realms, but some are way more dangerous than others...\n");
        break;
        
        case 1:
        this_object()->command("emote says: There is one vampire in particular "
        +"that I would like to put out of misery once and for all...\n");
        break;
        
        case 2:
        this_object()->command("emote says: ..the vampire Vorador. Are "
        +"you interested?\n");
        
        break;
    }
    
    // Finished talking
    if (do_aid2_int == 3)
    {
        dialogue = 0;
        do_aid2_int = 0;
        
        return 1;
    }
    
    do_aid2_int = do_aid2_int + 1;
    
    set_alarm(3.0, 0.0, &do_aid2());
    
    return 1;
}


int
do_aid1()
{
    switch(do_aid1_int)
    {
        case 0:
        this_object()->command("emote says: Well, since you ask...\n");
        break;
        
        case 1:
        this_object()->command("emote says: I would appreciate aid in "
        +"identifying the origins of a vampire that hunts "
        +"in Kryptgarden forest...\n");
        break;
        
        case 2:
        this_object()->command("emote says: A sample of its blood would "
        +"suffice.\n");
        break;
        
        case 3:
        this_object()->command("emote says: If you can manage to "
        +"get hold of such a sample, I would preciate it.\nAs you "
        +"probably know, such abominations are only active at night, "
        +"so searching for vampires at daytime is futile.\n");
        
        this_player()->add_prop(BLOODSAMPLE, 1);
        break;
    }
    
    // Finished talking
    if (do_aid1_int == 4)
    {
        dialogue = 0;
        do_aid1_int = 0;
        
        return 1;
    }
    
    do_aid1_int = do_aid1_int + 1;
    
    set_alarm(5.0, 0.0, &do_aid1());
    
    return 1;
}


// If asked about task/help/quest
int
do_aid()
{
    if (dialogue == 1)
    {
        this_object()->command("emote looks annoyed when being interrupted "
        +"when he is talking.\n");
        
        return 1;
    }
    
    if (this_player()->query_guild_name_lay() == LAY_VAMPIRES_GUILD_NAME)
    {
        this_object()->command("emote suddenly looks afraid while keeping "
        +"silent, eyes darting everywhere.\n");
        
        dialogue = 0;
        
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 1)
    {
        this_object()->command("emote says: Continue to track down the "
        +"Vampire Vorador through the clues hidden in his "
        +"paintings. There isn't "
        +"much else I can help you with.\n");
        
        dialogue = 0;
        
        return 1;
    }
    
    dialogue = 1;
    
    // Van Henriksen will give more detailed information if somebody 
    // helped him with his quest.
    if (this_player()->test_bit(DOMAIN, VAMP_ENTRY_QUEST_GROUP, 
    VAMP_ENTRY_QUEST_BIT))
    {
        // 170 avg requirement.
        if (this_player()->query_average() < 160)
        {
            this_object()->command("emote says: While I preciated your "
            +"help with the vampire bloodsample, I'm afraid you are too "
            +"inexperienced to further help me at this point. Feel free "
            +"to return once you have grown some more.\n");
            
            dialogue = 0;
            
            return 1;
        }
        
        set_alarm(2.0, 0.0, &do_aid2());
    
        return 1;
    }
      
    // Initial help / taskresponse
    set_alarm(2.0, 0.0, &do_aid1());
    
    return 1;
}


// If asked about task/help/quest
int
do_paintings()
{
    if (dialogue == 1)
    {
        this_object()->command("emote looks annoyed when being interrupted "
        +"when he is talking.\n");
        
        return 1;
    }
    
    if (this_player()->query_guild_name_lay() == LAY_VAMPIRES_GUILD_NAME)
    {
        this_object()->command("emote suddenly looks afraid while keeping "
        +"silent, eyes darting everywhere.\n");
        
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 1)
    {
        this_object()->command("emote says: Continue to track down the "
        +"Vampire Vorador through the clues hidden in his "
        +"paintings. There isn't "
        +"much else I can help you with.\n");
        
        return 1;
    }
    
    dialogue = 1;
    
    // Van Henriksen will give more detailed information if somebody 
    // helped him with his quest.
    if (this_player()->test_bit(DOMAIN, VAMP_ENTRY_QUEST_GROUP, 
    VAMP_ENTRY_QUEST_BIT))
    {
        // 170 avg requirement.
        if (this_player()->query_average() < 160)
        {
            this_object()->command("emote says: While I preciated your "
            +"help with the vampire bloodsample, I'm afraid you are too "
            +"inexperienced to further help me at this point. Feel free "
            +"to return once you have grown some more.\n");
            
            dialogue = 0;
            
            return 1;
        }
        
        this_object()->command("emote says: These paintings "
        +"are enchanted, and will sometimes reveal some information "
        +"relevant for "
        +"probably tracking down the vampire, or maybe something he wants "
        +"you to find for some reason. When or if they "
        +"decide to reveal something may vary by factors such as time, and other "
        +"unknown premises and conditions not known to me, so patience is "
        +"important. Supposedly, there "
        +"are under ten such paintings, and they all should be somewhere "
        +"in or near Swordcoast. Some was inherited, some bought at auctions, "
        +"and some simply given away or planted somewhere with purpose.\n");
        
        dialogue = 0;
        
        return 1;
    }
      
    this_object()->command("emote says: Before we talk about that, "
    +"I would rather like your help with something else first.\n");
    
    dialogue = 0;
            
    return 1;
}


// If asked about task/help/quest
int
do_vorador_start()
{
    if (dialogue == 1)
    {
        this_object()->command("emote looks annoyed when being interrupted "
        +"when he is talking.\n");
        
        return 1;
    }
    
    dialogue = 1;
    
    // Van Henriksen will give more detailed information if somebody 
    // helped him with his quest.
    if (this_player()->test_bit(DOMAIN, VAMP_ENTRY_QUEST_GROUP, 
    VAMP_ENTRY_QUEST_BIT))
    {
        set_alarm(2.0, 0.0, &do_vorador());
    
        return 1;
    }
      
    this_object()->command("emote says: I'd rather ask you to help me "
    +"with something before we elaborate more on other topics.\n");
    
    dialogue = 0;
    
    return 1;
}


/*
 * Function name: reward_task()
 * Description  : Determines the reward for various tasks
 */
int
give_bloodsample(string str)
{
    object bloodsample;
    
    if (str == "blood to man" || str == "bloodsample to man"
     || str == "sample to man" || str == "bloodsample to human")
    {
        if (objectp(bloodsample = present("_quest_vampire_bloodsample", 
        this_player())))
        {
            // If the player has done this quest.
            if(this_player()->test_bit(DOMAIN, VAMP_ENTRY_QUEST_GROUP, 
            VAMP_ENTRY_QUEST_BIT))
            {
                write("You give the small sample of blood to the "
                +"fearless well-travelled man.\n");
                
                command("emote pulls out some weird contraption "
                +"and tests the "
                +"small sample of blood.\n");
                
                command("emote says: Damn...not what I hoped for! "
                +"The origin of "
                +"this vampire is of somebody else..\n");
                
                command("emote says: Anyway, thanks for the "
                +"assistance once again\n");
                                    
                bloodsample->remove_object();
                
                this_player()->remove_prop(BLOODSAMPLE);
                
                dialogue = 0;
                
                return 1;
            }
            
            write("You give the small sample of blood to the "
                +"fearless well-travelled man.\n");
                
            command("emote pulls out some weird contraption and tests the "
                +"small sample of blood.\n");
                
            command("emote says: Damn...not what I hoped for! The origin of "
                +"this vampire is of somebody else..\n");
                
            command("emote says: Anyway, thanks for the assistance.\n");
                
            this_player()->catch_msg("\nYou feel more experienced!\n");
            
            bloodsample->remove_object();
            
            this_player()->set_bit(VAMP_ENTRY_QUEST_GROUP, 
            VAMP_ENTRY_QUEST_BIT);
            
            this_player()->add_exp_quest(VAMP_ENTRY_QUEST_EXP);
            
            QUEST_LOG_FILE(VAMP_ENTRY_QUEST_LNG, VAMP_ENTRY_QUEST_EXP);
            
            this_player()->remove_prop(BLOODSAMPLE);
            
            dialogue = 0;
            
            return 1;
        }
         
        return 0;
    } 
    
    return 0;
}


void travel_elsewhere()
{    
    tell_room(environment(this_object()), "The "+query_short()
    +" bids everyone "
    +"farewell, and leaves.\n");  
    
    switch (dice)
    {
        case 0:
        this_object()->move_living("M","/d/Faerun/halflings/rooms/inn",1);       
        tell_room("/d/Faerun/halflings/rooms/inn", "A "+query_short()
        +" enters the room and buys a beer.\n");

        dice = 1;        
        break;
        
        case 1:
        this_object()->move_living("M","/d/Faerun/highroad/rooms/hut_food",1);       
        tell_room("/d/Faerun/highroad/rooms/hut_food", "A "
        +query_short()+" enters the room and buys a beer.\n");  
        
        dice = 0;
        break;
    }
    
    dialogue = 0;
    
    return;
}


void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    
    dialogue = 0;

    npc_name = "_van_henriksen";

    add_adj("fearless");
    add_adj("well-travelled");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_ATTACK , 1);
    add_prop(LIVE_I_NO_ACCEPT_GIVE, 1);

    set_race_name("human");
    add_name(npc_name);
    add_name("man");
    
    set_short("fearless well-travelled man");
    
    set_long("Grey stern eyes watches your every move while the "
    +"smoke from his black wooden pipe floats towards your "
    +"direction. This fearless individual is dressed in a "
    +"scarred brown leather armour, a dark-grey cloak, brown leather gloves "
    +"black leather trousers and a black leather hat decorated with "
    +"a metal buckle. His green leather boots are well-worn and "
    +"obviously have seen better days. You think this man is some sort "
    +"of a witchhunter, especially when you notice his crossbow armed "
    +"with silver bolts, and the ornated silvercoated shortsword hanging "
    +"from his leather belt. Witchhunters are known for their rigid stance "
    +"against abominations and often know a thing or two about "
    +"alchemical recipes.\n");
        
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

   /* Actions */
    set_act_time(5);
    set_cact_time(5);
    add_act("ponder");
    add_act("emote looks sternly at you.");
    add_act("emote smokes his black wooden pipe.");
    add_act("emote mumbles something about recipes.");
    add_act("emote coughs.");
   
    add_ask( ({ "quest", "task", "help", "aid" }), do_aid, 1);
    add_ask( ({ "vorador", "interested", "i am interested", "i am", "yes"}), 
    do_vorador_start, 1);
    
    add_ask( ({ "vampire", "vampires" }), "say Nefarious creatures that "
        +"prey on the blood of the living, and certainly undead. These "
        +"creatures are primarily active during the night, and rests in "
        +"some coffin somewhere during the day. Sunlight will usually "
        +"hurt them, and destroy them if the exposure is too long. It "
        +"is important to know that vampires are made, and not born, and "
        +"it's usually humans that are turned into these beings of the "
        +"night.", 1);
    
    add_ask( ({ "art", "painting", "paintings" }), do_paintings, 1);
    
    add_ask( ({ "abominations", "abomination", "monster", "monsters" }), 
        "say I define abominations as wicked creatures such as vampires and "
        +"other creatures of undeath, plus the living affected by "
        +"lycantrophy. These often prey on citizens and travellers "
        +"alike, making roads unsafe and the wilderness even more "
        +"dangerous. I usually travel from tavern to tavern, picking up "
        +"tasks and alchemic recipes to aid in removing these from "
        +"the lands in exchange for coin. If you "
        +"need my aid, look for me in various taverns or inns in or near "
        +"Swordcoast.", 1);
    
    add_ask( ({ "werewolf", "werewolves", "lycan", "lycans",
        "lycantrophes", "lycantrophy" }), 
        "say These are changechapers, often humans with a curse running "
        +"through their veins that forces them into beasts of nature such "
        +"as hybrid wolves, bears and similar. They prey on the living for "
        +"the meat, and kill everything that crosses their path.", 1);
    
    add_ask( ({ "recipe", "recipes", "alchemy", "alchemical recipes", 
    "alchemical recipe" }), "say Yes, as a dedicated "
        +"hunter of abominations, I know a full recipe "
        +"for alchemists "
        +"with the proper equipment, namely 'hellfire'. For other recipes, "
        +"you probably have to ask somebody else.", 1);
        
    add_ask( ({ "blood", "sample" }), "say Yes, I collect samples of blood "
        +"from many abominations in order to hopefully track their origin.", 1);
    
    add_ask( ({ "hellfire" }), "say This highly reactive powder "
        +"will ignite and burn violently when coming contact with "
        +"water. It will consume any type of "
        +"wood as long as its submerged. The recipe is as follow: The herb "
        +"named nethra, and "
        +"a lot of rust powder. Very useful for divers hunting "
        +"abominations hiding or trapped in shipwrecks and the like. It "
        +"needs to be crafted through some alchemy or "
        +"laboratory equipment though", 1);
        
    add_ask( ({ "rust powder", "powder", "rust" }), "say Rust powder? "
    +"I assume items of iron "
    +"that are particularly corroded would do the trick as the base "
    +"ingredient. It needs to be refined through some alchemy or "
    +"laboratory equipment though.", 1);
    
    add_ask( ({ "equipment", "laboratory equipment", "laboratory" }), "say usually "
    +"rare and exotic set of equipment for alchemists. There are also various "
    +"alchemy sets that float around that may be useful. I passed "
    +"some weird lunatic on the high road that possessed one of these not "
    +"too long ago.", 1);
    
    add_ask( ({ "alchemy set" }), "say These kits are more like small "
    +"mobile laboratories, perfect for use in the field and remote locations.", 1);
    
     add_ask( ({ "lunatic", "weird lunatic" }), "say yeah...passed one at the "
     +"high road. Obviously damaged due to alchemical detonations and similar. He "
     +"at the time possessed an alchemy set that he was very nervous about.", 1);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);  
    
    // Changes inn/pub every 3 hours.
    set_alarm(10800.0, 10800.0, &travel_elsewhere());
}


void
init_living()
{
    ::init_living();
    add_action(give_bloodsample, "give");
}
