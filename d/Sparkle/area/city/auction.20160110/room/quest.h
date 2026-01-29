/*
 *  /w/novo/open/auction/quest.h
 *
 *  This is the quest support for the auction house.
 *  All add_actions, variables, and timers are here.
 *  This file is inherited by auction_house
 *  
 *
 *  Created March 2008, by Novo
 */


#define AUCTIONEER_NO_GREET         "_auctioneer_no_greet"

#include <composite.h>;
#include "/d/Sparkle/sys/quests.h";
#include "../defs.h";

//Auction related variables
object Auctioneer;

string *DESC1 = ({ "patient", "shifty", "quiet", "dour", "handsome" });
string *DESC2 = ({ "short", "blue-eyed", "tall", 
                "long-legged", "short-armed", "lanky" });
string *RACE = ({ "dwarf", "gnome", "ogre", "elf", "human" });

string *paddles = ({ " raises a paddle.", 
                     " leaps up with paddle in hand.",
                     " gives a slight nod, indicating a bid.",
                     " swings a paddle quickly." });

//Quest related variables
object Temporary_auctioneer;
object Fake_item;
object * Bidders;
int * Bidder_ids;
int Bidder_count;
int High_bidder;
int * Waiting_bidders;
int Auction_started;
int Auction_index;
int Expected_action;
int Auction_price;
int Number_of_calls;
int Auction_alarm_id;
int Lost_bidders;

//Prototypes

//Start the auction
public int start(string text);

//Stand at the podium
public int stand(string text);

//Call out the current price
public int call(string text);

//Exchange the money for the auction item
public int exchange(string text);

//Accept a bid
public int accept(string text);

//Located in auction_house.c
private int get_new_auction_number();
public void add_platinum_due(string name,int count);

public string benchdesc()
{
      return 
      "These benches are designed to accomodate the bidders. Solid and " +
      "made of oak, many both rich and poor have sat here. "+
      (Bidder_count>0 ? "There "+ (Bidder_count>1 ? "are " : "is ") +
      LANG_NUM2WORD(Bidder_count) + " sitting on the benches.\n"
      :" They are empty at present.\n");
}


/*
 * Function name:        start
 * Description  :        the "start auction" command
 *                       
 *
 */
public int start(string text)
{
    
    if (TP!=Temporary_auctioneer)
    {
        return 0;
    }
    
    notify_fail("Start the auction?\n");
    
    if (!strlen(text))
    {
        return 0;
    }

    if (!parse_command(text,({ }),"[the] 'auction'"))
    {
        return 0;
    }

    if (Auction_started)
    {
        write("You have already started this auction.\n");
        return 1;
    }
    
    if (!Expected_action)
    {
        write("But the auction house is not full yet!\n");
        return 1;
    }
    
    Auction_started=1;
    Expected_action=Auction_index;
    
    write("You start the auction.\n");
    
    Fake_item=clone_object(OBJ_DIR+"fake_item");
    Fake_item->configure_for_player(TP);
    tell_room(TO,"A spindly old gnome enters the tent, " +
    "pushing a marble pedestal with a large glass case on top. "+
    "Inside the case you can see "+
    LANG_ADDART(Fake_item->query_short()) + 
    ".\n",
    ({ }), Temporary_auctioneer);
    object container=clone_object(OBJ_DIR+"auction_container");
    container->move(TO);
    Fake_item->move(container,1);
    container->set_auction(get_new_auction_number());
    Fake_item=container;

    return 1;
}


/*
 * Function name:        stand
 * Description  :        the "stand podium" command
 *
 */
public int stand(string text)
{
    notify_fail("Stand where?\n");
    
    if (!strlen(text))
    {
        return 0;
    }

    if (!parse_command(text,({ }),"[at] / [on] / [behind] 'podium'"))
    {
        return 0;
    }
    
    if (!objectp(Temporary_auctioneer))
    {
        write("You stand behind the podium for a moment, "+
          "pretending to be an auctioneer.\n");
        say(QNAME(TP)+" steps up behind of the podium.\n",TP);
        if (objectp(Auctioneer) &&
            !TP->query_prop(AUCTIONEER_NO_GREET))
        {
            set_alarm(2.0,0.0,&Auctioneer->react_stand(TP));
        }
        return 1;
    }
    
    if (TP!=Temporary_auctioneer && objectp(Temporary_auctioneer))
    {
        write("You decide not to interrupt the current auction.\n");
        return 1;
    }
    
    write("You are already in front of the podium.\n");
    return 1;
}


/*
 * Function name:        call
 * Description  :        the "call next bid" command
 *
 */
public int call(string text)
{
    if (TP!=Temporary_auctioneer || !Auction_started || Number_of_calls==4)
    {
        return 0;
    }
    
    notify_fail("Call out the next bid?\n");
    
    if (!strlen(text))
    {
        return 0;
    }

    if (!parse_command(text,({ }),"[out] [the] 'asking' 'price'") &&
        !parse_command(text,({ }),"[out] [the] [next] 'bid'"))
    {
        return 0;
    }

    if (sizeof(Waiting_bidders))
    {
        write("You still have a waiting bid to accept.\n");
        return 1;
    }
    
    if (Expected_action>Auction_index-4 && Number_of_calls)
    {
        write("You decide to give the bidders more time.\n");
        return 1;
    }

    write("You call out the next bid.\n");
    
    switch (Number_of_calls)
    {
        case 0:
        int asking_price=Auction_price+5;
        string short=all_inventory(Fake_item)[0]->query_short();
        switch (random(4))
        {
            case 0:
                TP->command("$say Very rare "+short+"!  A steal at " +
                asking_price + " platinum!");
            break;
            case 1:
                TP->command("$say You can't get any better " +
                "price for any "+short+" than "+ asking_price +
                " platinum!");
            break;
            case 2:
                TP->command("$say "+asking_price+" platinum for "+
                "this "+short+" is quite the deal!");
            break;
            default:
                TP->command("$say I want "+asking_price+" platinum for "+
                "this very valuable "+short+"!");
            break;
        }    
        break;
        case 1:
        TP->command("$say Going once!");
        break;
        case 2:
        TP->command("$say Going twice!");
        break;
        case 3:
        TP->command("$say Sold to the "+
        Bidders[High_bidder]->query_short()+
        " in the "+LANG_ORD2WORD(High_bidder/5+1)+" row!");
        tell_room(TO,"The losing bidders grumble and leave.\n",
        ({}),Temporary_auctioneer);
        for (int i=0;i<sizeof(Bidders);i++)
        {
            if (i!=High_bidder)
            {
                Bidders[i]->remove_object();
                Bidders[i]=0;
                Bidder_ids[i]=0;
            }
        }
        Bidder_count=1;
        break;
    }
    Number_of_calls++;
    Expected_action=Auction_index;
    return 1;
}

/*
 * Function name:        cleanup_auction
 * Description  :        cleanup at the end of success/failed auction
 *
 */
public void cleanup_auction()
{

    if (Temporary_auctioneer)
    {
        Temporary_auctioneer->remove_prop(LIVE_S_EXTRA_SHORT);
        write_file(QUEST_ATTEMPT_LOG,
        sprintf("%s %-14s completed an auction, lost %d bidders\n",
            ctime(time()),
            Temporary_auctioneer->query_real_name(),
            Lost_bidders));
    }

    Temporary_auctioneer=0;
    if (Fake_item)
    {
        tell_room(TO,"A spindly old gnome enters the tent, "+
        "and pushes the glass case back out along with him.\n", ({ }),
        TO);
        Fake_item->remove_object();
    }
    for (int i=0;i<sizeof(Bidders);i++)
    {
        if (objectp(Bidders[i]))
        {
                Bidders[i]->remove_object();
                Bidders[i]=0;
                Bidder_ids[i]=0;
        }
    }
    Bidder_count=0;

}

/*
 * Function name:        return_auctioneer
 * Description  :        Returns the auctioneer after competing the quest
 *                       
 *
 */
public void return_auctioneer()
{
    Auctioneer->move(TO);
    Auctioneer->command("emote returns to find the auction gone "+
    "well.");
    
    set_alarm(2.0,0.0,cleanup_auction);
    
    if (!Lost_bidders)
    {
        Auctioneer->command("say Flawlessly done!  Excellent work!");
        if (!Temporary_auctioneer->test_bit(getuid(), 
                SPARKLE_AUCTION_GROUP,
                SPARKLE_AUCTION_BIT))
        {
            Temporary_auctioneer->set_bit(
                     SPARKLE_AUCTION_GROUP,
                     SPARKLE_AUCTION_BIT);
            Temporary_auctioneer->
                add_exp_quest(SPARKLE_AUCTION_EXP);

            Temporary_auctioneer
                ->catch_tell("You feel more experienced!\n");

            write_file(QUEST_LOG_FILE,
            sprintf("%s %-14s completed the quest, %d exp\n",
            ctime(time()),
            Temporary_auctioneer->query_real_name(),
            SPARKLE_AUCTION_EXP));
        }
    }
    else
    {
        Auctioneer->command("say Good job, though ye did lose a few "+
        "customers.");
    }        
    //Award 1-2 platinum
   add_platinum_due(Temporary_auctioneer->query_real_name(),
   max(1,Auction_price/20));
}

/*
 * Function name:        exchange
 * Description  :        "exchange item for money" command
 *
 */
public int exchange(string text)
{
    if (TP!=Temporary_auctioneer || Number_of_calls<4 || !Expected_action)
    {
        return 0;
    }

    if (High_bidder<0 || !Bidders[High_bidder])
    {
        return 0;
    }
    
    notify_fail("Exchange the money for the auction item?\n");

    if (!stringp(text))
    {
        return 0;
    }
    

    if (!parse_command(text,({ }),
        "[the] 'money' [for] [the] [auction] 'item'"))
    {
        return 0;
    }

    string short=all_inventory(Fake_item)[0]->query_short();
    write("You exchange "+Auction_price+" platinum for the " + 
    short +" with the "+ Bidders[High_bidder]->query_short() +
    ", who takes their prize and leaves.\n");
    all_inventory(Fake_item)->remove_object();
    say(QCTNAME(TP)+" awards the "+short+" to the "+
    Bidders[High_bidder]->query_short()+
    " who skips out happily out the door.\n",TP);
    Expected_action=0;
    remove_alarm(Auction_alarm_id);
    set_alarm(2.0,0.0,return_auctioneer);
    return 1;
}

/*
 * Function name:        exchange
 * Description  :        "accept bid from XXX" command
 *
 */
public int accept(string text)
{
    if (TP!=Temporary_auctioneer || !sizeof(Waiting_bidders))
    {
        return 0;
    }
    
    notify_fail("Accept the bid from which paddle number?\n");

    int selected_bidder;
    
    if (!strlen(text))
    {
        return 0;
    }
    
    if (!parse_command(text,({ }),"[the] 'bid' [from] [paddle] %d'"
         , selected_bidder))
    {
        return 0;
    }
    
    if (!sizeof(Waiting_bidders))
    {
        return 0;
    }
    
    
    string * leaving_bidders = ({ });
    for (int i=0;i<sizeof(Waiting_bidders);i++)
    {
        int potential_bidder=Waiting_bidders[i];
        if (Bidder_ids[potential_bidder]==selected_bidder)
        {
            High_bidder=potential_bidder;
            Auction_price+=5;
            Number_of_calls=0;
            TP->command("$say I have a bid for "+Auction_price+
            " platinum from the "+
            Bidders[potential_bidder]->query_short()+" in "+
            "the "+LANG_ORD2WORD(potential_bidder/5+1)+" row!");
            if (i)
            {
                tell_room(TO,"The "+ 
                Bidders[potential_bidder]->query_short() +
                " looks excited to be chosen out of turn.\n",
                ({ }), Temporary_auctioneer);
            }
            break;
        }
        else
        {
            leaving_bidders += ({ "the " + 
                  Bidders[potential_bidder]->query_short() });
            Bidders[potential_bidder]->remove_object();
            Bidders[potential_bidder]=0;
            Bidder_ids[potential_bidder]=0;
            Bidder_count--;
            Lost_bidders++;
        }   
    }
    if (sizeof(leaving_bidders))
    {
        write("You accept the wrong bid.\n");
        tell_room(TO,capitalize(COMPOSITE_WORDS(leaving_bidders)) +
        " stand"+(sizeof(leaving_bidders)==1 ? "s" : "" ) +
        " up angry and storm"+ (sizeof(leaving_bidders)==1 ? "s" : "" ) +
        " out.\n",
        ({ }), Temporary_auctioneer);
    }
    else
    {
        write("You accept the correct bid from the "+
        Bidders[High_bidder]->query_short() +
        ".\n");
    }
    
    Waiting_bidders=({ });

    Expected_action=Auction_index;
    return 1;
}


/*
 * Function name:        run_quest_auction
 * Description  :        This is the main loop for the quest.
 *                       This adds bidders to the room, removes them
 *                       if the quester left, bids on the auction, 
 *                       and removes them if the quester is too slow.
 *
 */
public void run_quest_auction()
{

    if (!Temporary_auctioneer || environment(Temporary_auctioneer)!=TO)
    {
         tell_room(TO,"Surprised by the missing auctioneer, the bidders "+
         "go home.\n",
        ({ }), Temporary_auctioneer);
        Auctioneer->move(TO);
        Auctioneer->command("emote returns to find the auction gone "+
        "badly.");
        if (Temporary_auctioneer)
        {
            Temporary_auctioneer->add_prop(AUCTIONEER_NO_GREET,100);         
        }
        set_alarm(2.0,0.0,cleanup_auction);
        return;
    }
    
    if (Auction_index && !Bidder_count)
    {
         tell_room(TO,"With no bidders left, the auction is over.\n",
        ({ }), Temporary_auctioneer);
        Auctioneer->move(TO);
        Auctioneer->command("emote returns to find the auction gone "+
        "badly.");
        Auctioneer->command("sigh");
        Auctioneer->command("say What a mess. I hope ye do better next "+
        "time!");
        if (Temporary_auctioneer)
        {
            Temporary_auctioneer->add_prop(AUCTIONEER_NO_GREET,100);         
        }
        set_alarm(2.0,0.0,cleanup_auction);
        return;
    }        
    
    Auction_index++;

    if (!Expected_action && !Auction_started && Bidder_count<30)
    {
        int extra=min(1+random(5),30-Bidder_count);
        Bidder_count+=extra;
        
        string * new_bidders=({ });
        //create 1-5 bidders
        for (int i=0;i<extra;i++)
        {
            int repeat=1;
            string name;
            string race;
            string desc1;
            string desc2;
            while (repeat)
            {
                repeat=0;
                race=RACE[random(sizeof(RACE))];
                desc1=DESC1[random(sizeof(DESC1))];
                desc2=DESC2[random(sizeof(DESC2))];
                name=desc1 + " " + desc2 + " " + race;
                for (int j=0;j<sizeof(Bidders);j++)
                {
                    if (Bidders[j] && name==Bidders[j]->query_short())
                    {
                        repeat=1;
                        break;
                    }
                }
            }
            new_bidders += ({ "a " +name });
            int id;
            repeat=1;
            while (repeat)
            {
                repeat=0;
                id=random(250)+50;
                for (int j=0;j<sizeof(Bidder_ids);j++)
                {
                    if (id==Bidder_ids[j])
                    {
                        repeat=1;
                        break;
                    }
                }
            }
            int pos=random(sizeof(Bidder_ids));
            while (Bidder_ids[pos])
            {
                pos=(pos+1) % sizeof(Bidder_ids);
            }
            object bidder=clone_object("/std/object");
            bidder->set_no_show_composite(1);
            bidder->add_prop(OBJ_I_NO_GET,"You can't pick up a bidder!\n");
            bidder->set_short(name);
            bidder->set_name(race);
            bidder->add_pname("people");
            bidder->set_adj(({ desc1, desc2}));
            bidder->set_long("The "+name+" is sitting on the bench in "+
            "the " + LANG_ORD2WORD(pos/5+1)+" row. The "+race+
            " is holding paddle number " + id + ".\n");
            Bidders[pos]=bidder;
            bidder->move(TO);
            Bidder_ids[pos]=id;
        }
    
        tell_room(TO,capitalize(COMPOSITE_WORDS(new_bidders)) +
        " arrive"+(sizeof(new_bidders)==1 ? "s" : "" ) +
        " and sit down on the benches.\n",
        ({ }), Temporary_auctioneer);

        if (Bidder_count==30)
        {
            Temporary_auctioneer->catch_tell("You notice the benches "
            +"are all full.\n");
            Expected_action=Auction_index;
        }        
    }
    //Give them a warning that something needs to be done
    if (Expected_action && Auction_index-Expected_action==8)
    {
        if (Number_of_calls>=4 && High_bidder>=0)
        {
            tell_room(TO,
                "The " + Bidders[High_bidder]->query_short()+
                " looks eager as if waiting for his prize.\n",
                ({ }), Temporary_auctioneer);
        }
        else    
        {
            tell_room(TO,
            "The bidders look eager as if waiting for something.\n",
            ({ }), Temporary_auctioneer);
        }
    }

    //Did they take over a minute to do an action?
    if (Expected_action && Auction_index-Expected_action>=12)
    {
        int going=min(1+random(4),Bidder_count);
        string * leaving_bidders = ({ });
        for (int i=0;i<going;i++)
        {
            int pos;
            Bidder_count--;
            Lost_bidders++;
            //High bidder is always last to go
            if (High_bidder>=0 && !Bidder_count)
            {
                pos=High_bidder;
                High_bidder=-1;
            }
            else
            if (Bidder_count<(High_bidder>=0 ? 1 : 0) 
                + sizeof(Waiting_bidders))
            {
                pos=Waiting_bidders[sizeof(Waiting_bidders)-1];
                Waiting_bidders=
                    Waiting_bidders[..sizeof(Waiting_bidders)-2];
            }
            else
            {
                pos=random(sizeof(Bidders));
                while (!Bidder_ids[pos] || pos==High_bidder ||
                    member_array(pos,Waiting_bidders)>=0)
                {
                    pos=(pos+1) % sizeof(Bidder_ids);
                }
            }
            Waiting_bidders-=({ pos });
            leaving_bidders += ({ "the "+Bidders[pos]->query_short() });
            Bidders[pos]->remove_object();
            Bidders[pos]=0;
            Bidder_ids[pos]=0;
        }    

        tell_room(TO,capitalize(COMPOSITE_WORDS(leaving_bidders)) +
        " stand"+(sizeof(leaving_bidders)==1 ? "s" : "" ) +
        " up and leave"+ (sizeof(leaving_bidders)==1 ? "s" : "" ) +
        ".\n",
        ({ }), Temporary_auctioneer);
    }
    
    //Swing a paddle if the auction allows it
    //Must be at least two that haven't bid
    //Auctineer must have called the price at least once
    if (Auction_started && 
        Bidder_count>(High_bidder>=0 ? 1 : 0)+sizeof(Waiting_bidders) &&
        Number_of_calls>0 && Number_of_calls<4 &&
        (!random(Auction_price*Auction_price/40 +
         sizeof(Waiting_bidders)*3) || 
         (!High_bidder && !sizeof(Waiting_bidders))))
    {
        int pos=random(sizeof(Bidders));
        while (!Bidder_ids[pos] || pos==High_bidder ||
            member_array(pos,Waiting_bidders)>=0)
        {
            pos=(pos+1) % sizeof(Bidders);
        }
        
        if (!sizeof(Waiting_bidders))
        {
            Expected_action=Auction_index;
        }
        Waiting_bidders+=({ pos });
        tell_room(TO,"The "+Bidders[pos]->query_short() +
        paddles[random(sizeof(paddles))] +
        "\n", ({ }), Temporary_auctioneer);
        
    }
    
    Auction_alarm_id=set_alarm(5.0,0.0,&run_quest_auction());    
}

/*
 * Function name:        start_quest_auction
 * Description  :        Called by the auctioneer, this initializes and
 *                       starts the run_quest_auction loop
 *
 */
public void start_quest_auction(object auctioneer)
{

    Temporary_auctioneer=auctioneer;
    Bidders=allocate(30);
    Bidder_ids=allocate(30);    
    Bidder_count=0;
    High_bidder=-1;
    Expected_action=0;
    Auction_started=0;
    Auction_index=0;    
    Auction_price=0;
    Number_of_calls=0;
    Fake_item=0;
    Lost_bidders=0;
    Waiting_bidders=({ });
        
    if (objectp(Temporary_auctioneer))
    {
        Temporary_auctioneer->add_prop(LIVE_S_EXTRA_SHORT,
            ", who is running an auction");
        write_file(QUEST_ATTEMPT_LOG,
        sprintf("%s %-14s started an auction\n",
            ctime(time()),
            Temporary_auctioneer->query_real_name()));
    }

    Auction_alarm_id=set_alarm(5.0,0.0,&run_quest_auction());
}
