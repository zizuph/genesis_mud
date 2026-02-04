/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * sheriff of Ribos
 *
 * Vader
 * Modified by Sorgum 950707
 *
 *  Modified: 11 June 2003, by Bleys
 *      - altered the logfile entry to be a little more explicit.
 *
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/quest_bits.h"
inherit STDMONSTER;
inherit "/d/Terel/open/scripter";

public int do_accuse(string str);

/*
 * Function name: init_living
 * Description:   Add the 'command items' of this object. 
 */
public void
init_living()
{
    ::init_living();
    add_action(do_accuse, "accuse");
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("sheriff");
    set_race_name("human");
    set_short("Sheriff of Ribos");
    set_long("This man oversees law and order within the domain " +
             "of the Kingdom.  If something shady is being done, he " +
             "probably knows about it.  But on occasion there may " +
             "be something he cannot solve.  Maybe you can " +
             "be of help....\n");

    set_stats(({80 + random(10), 80 + random(10), 80 + random(10), 
                    80, 80, 80}));
    set_all_hitloc_unarmed(25);

    SET_MAX_HP;
    set_act_time(1);
    add_act("@@fortune_chat");
    add_act("@@job_chat");
    add_act("@@frown_act");
   
    set_alignment(200);

    set_default_answer("say I don't know.", 1);
    add_ask(({"case", "for case", "about case", "job", "about job",
                  "for job", "task", "for task"}), "@@ask_case", 1);
}

public string
shrug()
{
    if (!query_busy_npc()) {
        command("shrug");
        command("say I don't know about that.");
    }
    return "";
}
        
fortune_chat()
{
    if (!query_busy_npc())
        command("say The King went to a fortune teller.  She told " +
                "him he would be killed this week.  He wants me to " +
                "find out who!  I haven't a clue!");
}


job_chat()
{
    if (!query_busy_npc())
        command("say Do you have some spare time?  I need all the eyes " +
                "I can get around here.  Why not ask me about this job " +
                "I have available.");
}

case_chat()
{
    if (!query_busy_npc())
        command("say Are you interested in a case?");
}

frown_act()
{
    if (!query_busy_npc())
        command("frown");
}

public string
ask_case()
{
    string name = TP->query_real_name();
    
    if (!query_busy_npc()) {
        set_who_name(name);
        start_script(RIBOS_DIR + "castle/script/tell_quest.script");
        return "peer " + name;    
    }
    return "say to " + name + " Just a minute. I'm busy right now.";
}

punt_me()
{
    (TO->who_ob())->catch_msg("You feel a little more experienced.\n");
    remove_object();
}

do_accuse(string str)
{   
    int expnum; 
   
    string name = TP->query_real_name(); 

    if (TP->query_npc())
        return 0; 

    notify_fail("Accuse who?\n");
    if (!str)
        return 0;

    if (TP->test_bit("Terel", QUEST_CRIME_GROUP, QUEST_CRIME_BIT)) {
        if (lower_case(str) == "alexander") {
            command("say I understood you the first time, it's already been " +
                "taken care of.");
        } else {
            command("stare " + name);
        }
        return 1;
    }  

    if (present("clue1_bag", TP) && present("kingdom_index", TP)
        && lower_case(str) == "alexander")
    {
        TP->set_bit(QUEST_CRIME_GROUP, QUEST_CRIME_BIT);
        
        expnum = TP->query_exp(); 
        if (expnum > QUEST_CRIME_EXP) 
            expnum = QUEST_CRIME_EXP;

        TP->add_exp(expnum, 0);

        FIX_EUID;

        set_who_name(name);
        set_who_ob(TP);
        start_script(RIBOS_DIR + "castle/script/thank_player.script");
        
        write_file(QUEST_LOG, TP->query_name() + " solved " +
            "the Ribos murder quest (CRIME_quest) (" +
            ctime(time()) + ")\n");
    }
    else
    {
        set_who_name(name);
        start_script(RIBOS_DIR + "castle/script/scold_player.script");
    }

    return 1;
} 
