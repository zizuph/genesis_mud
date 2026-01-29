/* /d/Raumdor/common/npc/spy.c
 * 
 * Nerull, 2021
 *
 * This npc serves as the questgiver for the spyquest
 * that ultimately give access to the Bountiful.
 *
 */


#include "defs.h"
inherit "/d/Raumdor/std/monster";
inherit "/d/Raumdor/lib/intro";
inherit "/d/Genesis/specials/resist.c";
inherit "/lib/unique.c";

#define SPY_QUEST_LOG(x,y)  write_file("/d/Raumdor/log/" + x, extract(ctime(time()), \
                                             4, 15) +" "+ y )
                                             
#define SPY_QUEST     "_spy_quest"

int dialogue;
int do_aid1_int;


int
do_aid1()
{
    if (this_player()->query_average() < 190)
    {
        this_object()->command("say Well, I have an important task, but it's for "
        +"the most mythical of heroes due to the dangers involved. Maybe you "
        +"should return later at some point?\n");
        
        return 1;
    }
    
    switch(do_aid1_int)
    {
        case 0:
        this_object()->command("say Very well. The lich Gylar, currently residing "
        +"in his castle somewhere at the mountainrange, is busy stocking up on supplies of "
        +"war. The holy order of the Purging Blade recently travelled to the mountains "
        +"to besiege the castle and with the determination in penetrating its defenses "
        +"and to purge all undeath within...\n");
        break;
        
        case 1:
        this_object()->command("say ..But, as with any lich, the defenses are "
        +"formidable, and are growing stronger for every day with the aid of valuable shipments "
        +"brought to the sandy banks by the frigate Bountiful.\n");
        break;
        
        case 2:
        this_object()->command("say According to the latest intelligence reports, "
        +"Bountiful are sailing, plundering and gathering weapons and supplies of war all "
        +"over the realms. It is currently anchored at a swimming distance right west of "
        +"the beach. There are rumours however...\n");
        break;
        
        case 3:
        this_object()->command("say ..that lich Gylar blessed this ship and its crew "
        +"with a powerful ward. The ship is not easily boarded due to this encompassing "
        +"protection, and the crew operating witin this ward is also rumoured to be "
        +"enhanced. The ward is impassable and the crew unkillable...\n");
        break;
        
        case 4:
        this_object()->command("say ..However...sages of the Holy order have found a "
        +"way to permanently weaken the barrier for certain individuals who have consumed a "
        +"special elixir. It would certainly be welcomed if adventurers such as you could "
        +"engage in the quest of crippling the defenses of Gylar. Now, I have this elixir "
        +"already and if you want it, it's yours, provided can offer me a certain item in return.");
        break;
        
        case 5:
        this_object()->command("say Some of the crew of the Bountiful are secretly "
        +"bringing supplies and possibly reports of intelligence to lich Gylar. Bring me any "
        +"such reports you can find, and you shall have the elixir as reward, adventurer.");
        
        this_player()->add_prop(SPY_QUEST, 1);
        break;
        

    }
    
    // Finished talking
    if (do_aid1_int == 6)
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
    
    if (this_player()->test_bit("Raumdor", 3, 7))
    {
       this_object()->command("say You have helped me before on this.\n");
        
        return 1;
    }
      
    // Initial help / taskresponse
    set_alarm(2.0, 0.0, &do_aid1());
    
    return 1;
}


void
create_monster()
{
    ::create_monster();
    set_name("bjarne");
    add_name("spy");
    set_adj("shady");
    add_adj("conteplating");
    set_short("shady contemplating spy");
    set_race_name("human");
    set_long(
      "This individual seems to be sneaking about, tracking the "
      +"movement of someone, or somebody. Dark muddy clothes blends "
      +"quite nicely with the shadows and the ground, making him "
      +"harder to spot.\n");
           
    set_gender(G_MALE);

    set_stats(STAT_ARRAY(120));

    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 60);
    
    set_alignment(300);
    
    add_ask( ({ "quest", "task", "help", "aid" }), do_aid, 1);
    
    add_ask( ({ "holy order", "order of the purging blade",
        "purging blade"    }), "say The Order of the Purging Blade is a rather "
        +"new one, recenty originating from the city of Vallaki. Similar to "
        +"Drakmere and other cities, the undead scourge caused by lich Gylar "
        +"and his other undead orders have plagued the lands for ages. As "
        +"a counter to this almost endless threat, this new order of holy "
        +"crudaders rose from the ashes like a Phoenix. With strong "
        +"military command and training imported from afar, these fanatical "
        +"holy warriors recently marched from Vallaki and all the way to the "
        +"outskirts of Castle Gylar stationed the northern mountain peaks, "
        +"keeping it under siege.", 1);
        
    add_ask( ({ "gylar", "lich gylar"  }), "say The lich Gylar is among the "
    +"chosen ones of the Nameless One. It is rumoured that Gylar is residing "
    +"in his castle stationed north of the mountain range. He and his cursed "
    +"unholy cults such as Khiraa and the Eternal Order have ravaged "
    +"these lands with horded of the undead.", 1);
    
    add_ask( ({ "castle", "castle gylar"  }), "say Castle Gylar is near the top "
    +"of the mountain range, north of the pass. It is currently under siege "
    +"of the holy order of the purging blade.", 1);
    
    add_ask( ({ "frigate", "bountiful"  }), "say The Bountiful was last "
    +"spotted near the docks, and should still be there.", 1);
    
    add_ask( ({ "khiraa", "cult of the dead"  }), "say Khiraa, the Cult of the "
    +"Dead - an organization of lichpriests and death knights that "
    +"is currently occupying some ruins hidden in the forests of "
    +"shadows.", 1);
    
    add_ask( ({ "eternal order"  }), "say The Eternal Order is an order "
    +"consisting of living beings prospecting to become "
    +"liches and death knights at Castle Gylar. This is a rather "
    +"new order created by the initiative of lich Gylar himself.", 1);
    
    add_ask( ({ "elixir"  }), "say The elixir is a magical concoction that "
    +"will somewhat immunize you from the effects that is protecting "
    +"the magical ward surrounding the frigate Bountiful near the "
    +"harbour. Normally, the ward is so strong that it will either "
    +"repel or kill those who tries to pass it. Furthermore, it also "
    +"weakens the affected crew, who is due to its effect, pretty "
    +"much undefeatable. You still need a team of mythical heroes "
    +"to even defeat a single one of them, but atleast the effect of "
    +"the elixir makes it possible.", 1);
    
    add_ask( ({ "vallaki"  }), "say Vallaki is a larger, more organized "
    +"city some distance southeast from Drakmere. The order of the purging "
    +"blade originates from that city.", 1);

    set_act_time(8);
    add_act("peer curiously");
    add_act("emote searches the ground for tracks and movement.");
    add_act("emote contemplates something.");
    add_act("emote is taking notes of something.");

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    equip(({
      COMMON_WEP_DIR + "silv_sword",
    }));

    MONEY_MAKE_GC(random(1))->move(TO, 1);

    update_hooks();
}


/*
 * Function name: reward_task()
 * Description  : Determines the reward for various tasks
 */
int
give_questtoken(string str)
{
    object report;
    object elixir;
    
    if (str == "report to spy" || str == "report to human"
     || str == "report to shady spy" || str == "report to shady human"
     || str == "intelligence report to shady spy" || str == "intelligence report to shady human"
     || str == "intelligence report to spy" || str == "intelligence report to shady human")
    {
        if (objectp(report = present("_spy_intelligence_report", 
        this_player())))
        {
            if (this_player()->query_average() < 190)
            {
                write("The "+short()+" isn't interested in what "
                +"you have to offer.\n");
                
                return 1;
            }
            
            // If the player has done this quest.
            if(this_player()->test_bit("Raumdor", 3, 7))
            {
                write("You give the intelligence report to the "
                +short()+".\n");
                
                command("say Thank you for the aid. Fortunetly, "
                +"you don't need more elixirs.\n");
                                    
                report->remove_object();
                
                this_player()->remove_prop(SPY_QUEST);
                
                dialogue = 0;
                
                return 1;
            }
            
            if (this_player()->query_average() < 190)
            {
                write("The "+short()+" isn't interested in what "
                +"you have to offer.\n");
                
                return 1;
            }
            
            write("You give the intelligence report to the "+short()+".\n");
                
            command("says Splendid.\n");
                
            this_player()->catch_msg("The "+short()+" nods "
            +"thankfully to you for your efforts.\nYou are given a small glowing phial that "
            +"contains some clear, almost blue-tinted liquid. You quickly drink its "
            +"content.\nSuddenly, you feel a strong sensation of being amplified and "
            +"better protected.\nYou feel more experienced!\n");
            
            tell_room(environment(this_player()), this_player()->query_name() + " hands over something to "
            +"the "+short()+" and receives something in return, which "
            +this_player()->query_pronoun()+" rapidly consumes.\n", this_player());
                      
            
            report->remove_object();
            
            this_player()->remove_prop(SPY_QUEST);
            
            this_player()->set_bit(3, 7);
            
            this_player()->add_exp_quest(10000);
            
            SPY_QUEST_LOG("spy_quest_log", "The player "+this_player()->query_name()
            +" completed the spy quest.\n");
                       
            dialogue = 0;
            
            return 1;
        }
         
        return 0;
    } 
    
    return 0;
}


void
init_living()
{
    ::init_living();
    add_action(give_questtoken, "give");
}
