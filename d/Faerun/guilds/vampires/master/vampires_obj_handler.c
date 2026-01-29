/*
 * Guild object handler
 *
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <std.h>
#include "../guild.h";

#define PUZZLEBOX_SPAWN_FACTOR  3


int roundrobin;

int spawnrate;


// puzzlebox integers
int box1_left;
int box1_middle;
int box1_right;

int box2_left;
int box2_middle;
int box2_right;

int box3_left;
int box3_middle;
int box3_right;

int box4_left;
int box4_middle;
int box4_right;

int box5_left;
int box5_middle;
int box5_right;

int box6_left;
int box6_middle;
int box6_right;

int box1_location_identifier;
int box2_location_identifier;
int box3_location_identifier;
int box4_location_identifier;
int box5_location_identifier;
int box6_location_identifier;

int nation_location_identifier;
int anomality_location_identifier;

int active1;
int active2;
int active3;
int active4;
int active5;
int active6;

int active_nation;
int active_anomality;
int active_nation_agents;

int stop_clone_coffins = 0;

object coffin_token1;
object coffin_token2;

object puzzlebox1;
object puzzlebox2;
object puzzlebox3;
object puzzlebox4;
object puzzlebox5;
object puzzlebox6;

object vampire_snatcher;

object vampirenation_target;
object anomality_target;

object vamp_nationagent1;
object vamp_nationagent2;
object vamp_nationagent3;
object vamp_nationagent4;
object vamp_nationagent5;
object vamp_nationagent6;
object vamp_nationagent7;
object vamp_nationagent8;
object vamp_nationagent9;
object vamp_nationagent10;


int query_cloned_coffins()
{
    return stop_clone_coffins;
}


void reset_cloned_coffins()
{
    write("You reset the cloned coffin flag.\n");
    stop_clone_coffins = 0;
    return;
}


public void clone_coffins()
{
    string * coffins=COFFIN_MANAGER->query_all_coffins();
    
    set_alarm(60.0, 0.0, &clone_coffins());
      
    foreach (string owner : coffins)
    {
        string coffin_location;        
        object coffin_locatione;        
        coffin_location = COFFIN_MANAGER->query_location(owner);
        
        coffin_locatione = find_object(coffin_location);
        
        // Location must be loaded before we populate it with coffin.
        if (coffin_locatione == 0)
        {
            coffin_location->load_room();
            COFFINSPAWN_LOG("coffinspawn_log",
            "Loading "+coffin_location+".\n");
        }

        object presentcoffin;

        presentcoffin = present("coffin", coffin_locatione);
        
        if (presentcoffin->query_owner() != owner)
        {           
            COFFINSPAWN_LOG("coffinspawn_log",
            "Coffin for "+owner+" spawning at "+coffin_location+".\n");
               
            object coffin=clone_object(ROOM_DIR+"coffin");
            coffin->load_coffin(owner);
            coffin->move(coffin_location, 1);    

            object player=find_player(owner);

            if (player != 0)
            {
                player->catch_tell("Your coffin has materialized somewhere in "
                +"the world. You may use sanctuary to enter it from a distance.\n");
            }                
        }
        else
        {
        }
    }  
}


string
query_vampirenation_target_location(string str)
{    
    return MASTER_OB(environment(vampirenation_target));
}


string
query_anomality_target_location(string str)
{    
    return MASTER_OB(environment(anomality_target));
}


// Coffin token locations
string
query_coffintoken1_location(string str)
{    
    return MASTER_OB(environment(coffin_token1));
}


string
query_coffintoken2_location(string str)
{    
    return MASTER_OB(environment(coffin_token2));
}


// Puzzlebox locations
string
query_puzzlebox1_location(string str)
{    
    return MASTER_OB(environment(puzzlebox1));
}


string
query_puzzlebox2_location(string str)
{    
    return MASTER_OB(environment(puzzlebox2));
}


string
query_puzzlebox3_location(string str)
{    
    return MASTER_OB(environment(puzzlebox3));
}


string
query_puzzlebox4_location(string str)
{    
    return MASTER_OB(environment(puzzlebox4));
}


string
query_puzzlebox5_location(string str)
{    
    return MASTER_OB(environment(puzzlebox5));
}


string
query_puzzlebox6_location(string str)
{    
    return MASTER_OB(environment(puzzlebox6));
}


int
query_targetnation_location_identifier()
{    
    return nation_location_identifier;
}


int
query_anomality_location_identifier()
{    
    return anomality_location_identifier;
}

// Location identifiers
int
query_puzzlebox1_location_identifier()
{    
    return box1_location_identifier;
}


int
query_puzzlebox2_location_identifier()
{    
    return box2_location_identifier;
}


int
query_puzzlebox3_location_identifier()
{    
    return box3_location_identifier;
}


int
query_puzzlebox4_location_identifier()
{    
    return box4_location_identifier;
}


int
query_puzzlebox5_location_identifier()
{    
    return box5_location_identifier;
}


int
query_puzzlebox6_location_identifier()
{    
    return box6_location_identifier;
}


// Puzzle box 1
int
query_box1_left_value()
{
    return box1_left;
}


int
query_box1_middle_value()
{
    return box1_middle;
}


int
query_box1_right_value()
{
    return box1_right;
}


int query_box1_active()
{
    return active1;
}


// Puzzle box 2
int
query_box2_left_value()
{
    return box2_left;
}


int
query_box2_middle_value()
{
    return box2_middle;
}


int
query_box2_right_value()
{
    return box2_right;
}


int query_box2_active()
{
    return active2;
}


// Puzzle box 3
int
query_box3_left_value()
{
    return box3_left;
}


int
query_box3_middle_value()
{
    return box3_middle;
}


int
query_box3_right_value()
{
    return box3_right;
}


int query_box3_active()
{
    return active3;
}


// Puzzle box 4
int
query_box4_left_value()
{
    return box4_left;
}


int
query_box4_middle_value()
{
    return box4_middle;
}


int
query_box4_right_value()
{
    return box4_right;
}


int query_box4_active()
{
    return active4;
}


// Puzzle box 5
int
query_box5_left_value()
{
    return box5_left;
}


int
query_box5_middle_value()
{
    return box5_middle;
}


int
query_box5_right_value()
{
    return box5_right;
}


int query_box5_active()
{
    return active5;
}


// Puzzle box 6
int
query_box6_left_value()
{
    return box6_left;
}


int
query_box6_middle_value()
{
    return box6_middle;
}


int
query_box6_right_value()
{
    return box6_right;
}


int query_box6_active()
{
    return active6;
}


int nationtarget_active()
{
    return active_nation;
}


// for testing purposes
int set_nationtarget(int i)
{
    active_nation = i;
    
    return 1;
}


int anomalitytarget_active()
{
    return active_anomality;
}


int query_roundrobin()
{
    return roundrobin;
}


void
set_box1_inactive()
{
    active1 = 0;
    
    return;
}


void
set_box2_inactive()
{
    active2 = 0;
    
    return;
}


void
set_box3_inactive()
{
    active3 = 0;
    
    return;
}


void
set_box4_inactive()
{
    active4 = 0;
    
    return;
}


void
set_box5_inactive()
{
    active5 = 0;
    
    return;
}


void
set_box6_inactive()
{
    active6 = 0;
    
    return;
}


void
set_vamptarget_inactive()
{
    active_nation = 0;
    
    return;
}


void
set_anomalitytarget_inactive()
{
    active_anomality = 0;
    
    return;
}


void
vampirenation_target_populate()
{
    setuid();
    seteuid(getuid());
    
    if (vampirenation_target != 0)
    {
        vampirenation_target->remove_object();
        vampirenation_target = 0;
    }
       
    active_nation = 0;

    int randfactor_nationtarget = random(5);
    //int spawndice_nation = randfactor_nationtarget;
    
    int spawndice_nation = 1;
    
    if (spawndice_nation == 1)
    {   
        int nattarg = random(5) + 1;
    
        active_nation = nattarg;
        
        vampirenation_target = clone_object(NATION_TARGET);
        
        vampirenation_target->set_nattier(active_nation);
  
        int i = random(28);
            
        nation_location_identifier = i;
        
        switch(i)
        {
            case 0:
            vampirenation_target->move(NATIONPLACE_1, 1);
            break;
            
            case 1:
            vampirenation_target->move(NATIONPLACE_2, 1);
            break;
            
            case 2:
            vampirenation_target->move(NATIONPLACE_3, 1);
            break;
            
            case 3:
            vampirenation_target->move(NATIONPLACE_4, 1);
            break;
            
            case 4:
            vampirenation_target->move(NATIONPLACE_5, 1);
            break;
                        
            case 5:
            vampirenation_target->move(NATIONPLACE_6, 1);
            break;
            
            case 6:
            vampirenation_target->move(NATIONPLACE_7, 1);
            break;
            
            case 7:
            vampirenation_target->move(NATIONPLACE_8, 1);
            break;
            
            case 8:
            vampirenation_target->move(NATIONPLACE_9, 1);
            break;
            
            case 9:
            vampirenation_target->move(NATIONPLACE_10, 1);
            break;
                       
            case 10:
            vampirenation_target->move(NATIONPLACE_11, 1);
            break;
            
            case 11:
            vampirenation_target->move(NATIONPLACE_12, 1);
            break;
            
            case 12:
            vampirenation_target->move(NATIONPLACE_13, 1);
            break;
            
            case 13:
            vampirenation_target->move(NATIONPLACE_14, 1);
            break;
            
            case 14:
            vampirenation_target->move(NATIONPLACE_15, 1);
            break;
                        
            case 15:
            vampirenation_target->move(NATIONPLACE_16, 1);
            break;
            
            case 16:
            vampirenation_target->move(NATIONPLACE_17, 1);
            break;
            
            case 17:
            vampirenation_target->move(NATIONPLACE_18, 1);
            break;
            
            case 18:
            vampirenation_target->move(NATIONPLACE_19, 1);
            break;
            
            case 19:
            vampirenation_target->move(NATIONPLACE_20, 1);
            break;
            
            case 20:
            vampirenation_target->move(NATIONPLACE_21, 1);
            break;
            
            case 21:
            vampirenation_target->move(NATIONPLACE_22, 1);
            break;
            
            case 22:
            vampirenation_target->move(NATIONPLACE_23, 1);
            break;
            
            case 23:
            vampirenation_target->move(NATIONPLACE_24, 1);
            break;
            
            case 24:
            vampirenation_target->move(NATIONPLACE_25, 1);
            break;
                       
            case 25:
            vampirenation_target->move(NATIONPLACE_26, 1);
            break;
            
            case 26:
            vampirenation_target->move(NATIONPLACE_27, 1);
            break;
            
            case 27:
            vampirenation_target->move(NATIONPLACE_28, 1);
            break;
        }
        
        NATION_TARGET_LOG("nationtarget_log",
        "Nationtarget spawned at "+i+", tier "+active_nation+".\n");
    }
}


void
vampirenation_agent_populate()
{
    setuid();
    seteuid(getuid());
    
    if (active_nation_agents == 0)
    {
        vamp_nationagent1->remove_object();
        vamp_nationagent1 = 0;
        
        vamp_nationagent2->remove_object();
        vamp_nationagent2 = 0;
        
        vamp_nationagent3->remove_object();
        vamp_nationagent3 = 0;
        
        vamp_nationagent4->remove_object();
        vamp_nationagent4 = 0;
        
        vamp_nationagent5->remove_object();
        vamp_nationagent5 = 0;
        
        vamp_nationagent6->remove_object();
        vamp_nationagent6 = 0;
        
        vamp_nationagent7->remove_object();
        vamp_nationagent7 = 0;
        
        vamp_nationagent8->remove_object();
        vamp_nationagent8 = 0;
        
        vamp_nationagent9->remove_object();
        vamp_nationagent9 = 0;
        
        vamp_nationagent10->remove_object();
        vamp_nationagent10 = 0;
    }
       
    if (active_nation_agents == 1)
    {   
        if (vamp_nationagent1 == 0)
        {
            vamp_nationagent1 = clone_object(NATION_AGENT1);
            vamp_nationagent1->move(AGENT1_PLACE, 1);
        }
        
        if (vamp_nationagent2 == 0)
        {
            vamp_nationagent2 = clone_object(NATION_AGENT2);
            vamp_nationagent2->move(AGENT2_PLACE, 1);
        }
        
        if (vamp_nationagent3 == 0)
        {
            vamp_nationagent3 = clone_object(NATION_AGENT3);
            vamp_nationagent3->move(AGENT3_PLACE, 1);
        }
        
        if (vamp_nationagent4 == 0)
        {
            vamp_nationagent4 = clone_object(NATION_AGENT4);
            vamp_nationagent4->move(AGENT4_PLACE, 1);
        }
        
        if (vamp_nationagent5 == 0)
        {
            vamp_nationagent5 = clone_object(NATION_AGENT5);
            vamp_nationagent5->move(AGENT5_PLACE, 1);
        }
        
        if (vamp_nationagent6 == 0)
        {
            vamp_nationagent6 = clone_object(NATION_AGENT6);
            vamp_nationagent6->move(AGENT6_PLACE, 1);
        }
        
        if (vamp_nationagent7 == 0)
        {
            vamp_nationagent7 = clone_object(NATION_AGENT7);
            vamp_nationagent7->move(AGENT7_PLACE, 1);
        }
        
        if (vamp_nationagent8 == 0)
        {
            vamp_nationagent8 = clone_object(NATION_AGENT8);
            vamp_nationagent8->move(AGENT8_PLACE, 1);
        }
        
        if (vamp_nationagent9 == 0)
        {
            vamp_nationagent9 = clone_object(NATION_AGENT9);
            vamp_nationagent9->move(AGENT9_PLACE, 1);
        }
        
        if (vamp_nationagent10 == 0)
        {
            vamp_nationagent10 = clone_object(NATION_AGENT10);
            vamp_nationagent10->move(AGENT10_PLACE, 1);
        }
    }
}


void
anomality_target_populate()
{
    setuid();
    seteuid(getuid());
    
    if (anomality_target != 0)
    {
        anomality_target->remove_object();
        anomality_target = 0;
    }
       
    active_anomality = 0;

    int randfactor_anomality = random(7);
    int spawndice_anomality = randfactor_anomality;
    
    if (spawndice_anomality == 1)
    {       
        active_anomality = 1;
        
        anomality_target = clone_object(ANOMALITY);
  
        int i = random(15);
            
        anomality_location_identifier = i;
        
        switch(i)
        {
            case 0:
            anomality_target->move(ANOMALITYPLACE_1, 1);
            break;
            
            case 1:
            anomality_target->move(ANOMALITYPLACE_2, 1);
            break;
            
            case 2:
            anomality_target->move(ANOMALITYPLACE_3, 1);
            break;
            
            case 3:
            anomality_target->move(ANOMALITYPLACE_4, 1);
            break;
            
            case 4:
            anomality_target->move(ANOMALITYPLACE_5, 1);
            break;
            
            case 5:
            anomality_target->move(ANOMALITYPLACE_6, 1);
            break;
            
            case 6:
            anomality_target->move(ANOMALITYPLACE_7, 1);
            break;
            
            case 7:
            anomality_target->move(ANOMALITYPLACE_8, 1);
            break;
            
            case 8:
            anomality_target->move(ANOMALITYPLACE_9, 1);
            break;
            
            case 9:
            anomality_target->move(ANOMALITYPLACE_10, 1);
            break;
            
            case 10:
            anomality_target->move(ANOMALITYPLACE_11, 1);
            break;
            
            case 11:
            anomality_target->move(ANOMALITYPLACE_12, 1);
            break;
            
            case 12:
            anomality_target->move(ANOMALITYPLACE_13, 1);
            break;
            
            case 13:
            anomality_target->move(ANOMALITYPLACE_14, 1);
            break;
            
            case 14:
            anomality_target->move(ANOMALITYPLACE_15, 1);
            break;
        }
        
        ANOMALITY_TARGET_LOG("anomalitytarget_log",
        "Anomality placed at "+i+".\n");
    }
}


void
puzzlebox1_populate()
{
    setuid();
    seteuid(getuid());
    
    if (puzzlebox1 != 0)
    {
        puzzlebox1->remove_object();
        puzzlebox1 = 0;
    }
       
    active1 = 1;

    box1_left = random(8) + 2;
    box1_middle = random(8) + 2;
    box1_right = random(8) + 2;
    
    int spawndice1 = 1;
    
    if (spawndice1 == 1)
    {       
        active1 = 1;
        
        puzzlebox1 = clone_object(PUZZLEB1);
  
        puzzlebox1->set_correct_nr1(box1_left);
        puzzlebox1->set_correct_nr2(box1_middle);
        puzzlebox1->set_correct_nr3(box1_right);
        
        int i = random(3);
        
        box1_location_identifier = i;
        
        switch(i)
        {
            case 0:
            puzzlebox1->move(PUZZLEBOX1_1, 1);
            break;
            
            case 1:
            puzzlebox1->move(PUZZLEBOX1_2, 1);
            break;
            
            case 2:
            puzzlebox1->move(PUZZLEBOX1_3, 1);
            break;
        }
        
        BOX_LOG("box_log",
        "Box1 spawned..\n");
    }
}


void
puzzlebox2_populate()
{
    setuid();
    seteuid(getuid());
    
    if (puzzlebox2 != 0)
    {
        puzzlebox2->remove_object();
        puzzlebox2 = 0;
    }
       
    active2 = 0;

    box2_left = random(8) + 2;
    box2_middle = random(8) + 2;
    box2_right = random(8) + 2;
    
    int randfactor2 = random(spawnrate);
    int spawndice2 = randfactor2;
    
    if (spawndice2 == 1)
    {       
        active2 = 1;
        
        puzzlebox2 = clone_object(PUZZLEB2);
  
        puzzlebox2->set_correct_nr1(box2_left);
        puzzlebox2->set_correct_nr2(box2_middle);
        puzzlebox2->set_correct_nr3(box2_right);
        
        int i = random(5);
            
        box2_location_identifier = i;
        
        switch(i)
        {
            case 0:
            puzzlebox2->move(PUZZLEBOX2_1, 1);
            break;
            
            case 1:
            puzzlebox2->move(PUZZLEBOX2_2, 1);
            break;
            
            case 2:
            puzzlebox2->move(PUZZLEBOX2_3, 1);
            break;
            
            case 3:
            puzzlebox2->move(PUZZLEBOX2_4, 1);
            break;
            
            case 4:
            puzzlebox2->move(PUZZLEBOX2_5, 1);
            break;
        }
        
        BOX_LOG("box_log",
        "Box2 spawned..\n");
    }
}


void
puzzlebox3_populate()
{
    setuid();
    seteuid(getuid());
    
    if (puzzlebox3 != 0)
    {
        puzzlebox3->remove_object();
        puzzlebox3 = 0;
    }
       
    active3 = 0;

    box3_left = random(8) + 2;
    box3_middle = random(8) + 2;
    box3_right = random(8) + 2;
    
    int randfactor3 = random(spawnrate);
    int spawndice3 = randfactor3;
    
    if (spawndice3 == 1)
    {       
        active3 = 1;
        
        puzzlebox3 = clone_object(PUZZLEB3);
  
        puzzlebox3->set_correct_nr1(box3_left);
        puzzlebox3->set_correct_nr2(box3_middle);
        puzzlebox3->set_correct_nr3(box3_right);
        
        int i = random(5);
            
        box3_location_identifier = i;
        
        switch(i)
        {
            case 0:
            puzzlebox3->move(PUZZLEBOX3_1, 1);
            break;
            
            case 1:
            puzzlebox3->move(PUZZLEBOX3_2, 1);
            break;
            
            case 2:
            puzzlebox3->move(PUZZLEBOX3_3, 1);
            break;
            
            case 3:
            puzzlebox3->move(PUZZLEBOX3_4, 1);
            break;
            
            case 4:
            puzzlebox3->move(PUZZLEBOX3_5, 1);
            break;
        }
        
        BOX_LOG("box_log",
        "Box3 spawned..\n");
    }
}


void
puzzlebox4_populate()
{
    setuid();
    seteuid(getuid());
    
    if (puzzlebox4 != 0)
    {
        puzzlebox4->remove_object();
        puzzlebox4 = 0;
    }
       
    active4 = 0;

    box4_left = random(8) + 2;
    box4_middle = random(8) + 2;
    box4_right = random(8) + 2;
    
    int randfactor4 = random(spawnrate);
    int spawndice4 = randfactor4;
    
    if (spawndice4 == 1)
    {       
        active4 = 1;
        
        puzzlebox4 = clone_object(PUZZLEB4);
  
        puzzlebox4->set_correct_nr1(box4_left);
        puzzlebox4->set_correct_nr2(box4_middle);
        puzzlebox4->set_correct_nr3(box4_right);
        
        int i = random(5);
            
        box4_location_identifier = i;
        
        switch(i)
        {
            case 0:
            puzzlebox4->move(PUZZLEBOX4_1, 1);
            break;
            
            case 1:
            puzzlebox4->move(PUZZLEBOX4_2, 1);
            break;
            
            case 2:
            puzzlebox4->move(PUZZLEBOX4_3, 1);
            break;
            
            case 3:
            puzzlebox4->move(PUZZLEBOX4_4, 1);
            break;
            
            case 4:
            puzzlebox4->move(PUZZLEBOX4_5, 1);
            break;
        }
        
        BOX_LOG("box_log",
        "Box4 spawned..\n");
    }
}


void
puzzlebox5_populate()
{
    setuid();
    seteuid(getuid());
    
    if (puzzlebox5 != 0)
    {
        puzzlebox5->remove_object();
        puzzlebox5 = 0;
    }
       
    active5 = 0;

    box5_left = random(8) + 2;
    box5_middle = random(8) + 2;
    box5_right = random(8) + 2;
    
    int randfactor5 = random(spawnrate);
    int spawndice5 = randfactor5;
    
    if (spawndice5 == 1)
    {       
        active5 = 1;
        
        puzzlebox5 = clone_object(PUZZLEB5);
  
        puzzlebox5->set_correct_nr1(box5_left);
        puzzlebox5->set_correct_nr2(box5_middle);
        puzzlebox5->set_correct_nr3(box5_right);
        
        int i = random(5);
            
        box5_location_identifier = i;
        
        switch(i)
        {
            case 0:
            puzzlebox5->move(PUZZLEBOX5_1, 1);
            break;
            
            case 1:
            puzzlebox5->move(PUZZLEBOX5_2, 1);
            break;
            
            case 2:
            puzzlebox5->move(PUZZLEBOX5_3, 1);
            break;
            
            case 3:
            puzzlebox5->move(PUZZLEBOX5_4, 1);
            break;
            
            case 4:
            puzzlebox5->move(PUZZLEBOX5_5, 1);
            break;
        }
        
        BOX_LOG("box_log",
        "Box5 spawned..\n");
    }
}


void
puzzlebox6_populate()
{
    setuid();
    seteuid(getuid());
    
    if (puzzlebox6 != 0)
    {
        puzzlebox6->remove_object();
        puzzlebox6 = 0;
    }
       
    active6 = 0;

    box6_left = random(8) + 2;
    box6_middle = random(8) + 2;
    box6_right = random(8) + 2;
    
    int randfactor6 = random(spawnrate);
    int spawndice6 = randfactor6;
    
    if (spawndice6 == 1)
    {       
        active6 = 1;
        
        puzzlebox6 = clone_object(PUZZLEB6);
  
        puzzlebox6->set_correct_nr1(box6_left);
        puzzlebox6->set_correct_nr2(box6_middle);
        puzzlebox6->set_correct_nr3(box6_right);
        
        int i = random(5);
            
        box6_location_identifier = i;
        
        switch(i)
        {
            case 0:
            puzzlebox6->move(PUZZLEBOX6_1, 1);
            break;
            
            case 1:
            puzzlebox6->move(PUZZLEBOX6_2, 1);
            break;
            
            case 2:
            puzzlebox6->move(PUZZLEBOX6_3, 1);
            break;
            
            case 3:
            puzzlebox6->move(PUZZLEBOX6_4, 1);
            break;
            
            case 4:
            puzzlebox6->move(PUZZLEBOX6_5, 1);
            break;
        }
        
        BOX_LOG("box_log",
        "Box6 spawned..\n");
    }
}


void
coffin_populate()
{
    setuid();
    seteuid(getuid());
    
    coffin_token1->remove_object();
    coffin_token1 = 0;
    
    coffin_token2->remove_object();
    coffin_token2 = 0;
    
    coffin_token1 = clone_object("/d/Faerun/guilds/vampires/obj/coffin_token");
    
    TOKEN_LOG("token_log",
        "token 1 spawned.\n");
    
    int i = random(14);
    
    switch(i)
    {
        case 0:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grvw1",1);
        break;
        
        case 1:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grv1",1);
        break;
        
        case 2:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grve1",1);
        break;
                    
        case 3:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grv2",1);
        break;
        
        case 4:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grve2",1);
        break;
        
        case 5:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grvw2",1);
        break;
        
        case 6:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grv3",1);
        break;
        
        case 7:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grvpath1",1);
        break;
        
        case 8:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/g1",1);
        break;
        
        case 9:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grvpath2",1);
        break;
        
        case 10:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/g2",1);
        break;
        
        case 11:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grvpath3",1);
        break;
        
        case 12:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/g3",1);
        break;
        
        case 13:
        coffin_token1->move("/d/Terel/common/town/mansion/graveyard/grvyard1",1);
        break;           
    }
    
    coffin_token2 = clone_object("/d/Faerun/guilds/vampires/obj/coffin_token");
       
    TOKEN_LOG("token_log",
        "Token 2 spawned.\n");
    
    int x = random(28);
    
    switch(x)
    {
        case 0:
        coffin_token2->move("/d/Krynn/solace/graves/o_grave1", 1);
        break;
        
        case 1:
        coffin_token2->move("/d/Krynn/solace/graves/o_grave2", 1);
        break;
        
        case 2:
        coffin_token2->move("/d/Krynn/solace/graves/fence2", 1);
        break;
                    
        case 3:
        coffin_token2->move("/d/Krynn/solace/graves/o_grave3", 1);
        break;
        
        case 4:
        coffin_token2->move("/d/Krynn/solace/graves/o_grave5", 1);
        break;
        
        case 5:
        coffin_token2->move("/d/Krynn/solace/graves/o_grave6", 1);
        break;
        
        case 6:
        coffin_token2->move("/d/Krynn/solace/graves/o_grave4", 1);
        break;
        
        case 7:
        coffin_token2->move("/d/Krynn/solace/graves/grave19", 1);
        break;
        
        case 8:
        coffin_token2->move("/d/Krynn/solace/graves/grave18", 1);
        break;
        
        case 9:
        coffin_token2->move("/d/Krynn/solace/graves/grave13", 1);
        break;
        
        case 10:
        coffin_token2->move("/d/Krynn/solace/graves/grave8", 1);
        break;
        
        case 11:
        coffin_token2->move("/d/Krynn/solace/graves/grave12", 1);
        break;
        
        case 12:
        coffin_token2->move("/d/Krynn/solace/graves/grave16", 1);
        break;
        
        case 13:
        coffin_token2->move("/d/Krynn/solace/graves/grave15", 1);
        break;   

        case 14:
        coffin_token2->move("/d/Krynn/solace/graves/grave10", 1);
        break;

        case 15:
        coffin_token2->move("/d/Krynn/solace/graves/grave11", 1);
        break;        

        case 16:
        coffin_token2->move("/d/Krynn/solace/graves/grave6", 1);
        break;        

        case 17:
        coffin_token2->move("/d/Krynn/solace/graves/grave7", 1);
        break;        

        case 18:
        coffin_token2->move("/d/Krynn/solace/graves/grave5", 1);
        break;        

        case 19:
        coffin_token2->move("/d/Krynn/solace/graves/grave_entr", 1);
        break;        

        case 20:
        coffin_token2->move("/d/Krynn/solace/graves/grave0", 1);
        break;        

        case 21:
        coffin_token2->move("/d/Krynn/solace/graves/grave1", 1);
        break;        

        case 22:
        coffin_token2->move("/d/Krynn/solace/graves/grave2", 1);
        break;        

        case 23:
        coffin_token2->move("/d/Krynn/solace/graves/grave3", 1);
        break;        

        case 24:
        coffin_token2->move("/d/Krynn/solace/graves/grave4", 1);
        break;        

        case 25:
        coffin_token2->move("/d/Krynn/solace/graves/grave9", 1);
        break;        

        case 26:
        coffin_token2->move("/d/Krynn/solace/graves/grave14", 1);
        break;   

        case 27:
        coffin_token2->move("/d/Terel/mountains/ice7", 1);
        break;                    
    }           
}


void
vampire_snatcher_populate()
{
    setuid();
    seteuid(getuid());
    
    vampire_snatcher->remove_object();
    vampire_snatcher = 0;
    

    // Vorador spawned
    vampire_snatcher = clone_object("/d/Faerun/guilds/vampires/obj/vamp_snatch");
    
    int i = random(24);
    
    switch(i)
    {
        case 0:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grvw1", 1);
        break;
        
        case 1:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grv1", 1);
        break;
        
        case 2:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grve1", 1);
        break;
                    
        case 3:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grv2", 1);
        break;
        
        case 4:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grve2", 1);
        break;
        
        case 5:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grvw2", 1);
        break;
        
        case 6:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grv3", 1);
        break;
        
        case 7:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grvpath1", 1);
        break;
        
        case 8:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/g1", 1);
        break;
        
        case 9:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grvpath2", 1);
        break;
        
        case 10:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/g2", 1);
        break;
        
        case 11:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grvpath3", 1);
        break;
        
        case 12:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/g3", 1);
        break;
        
        case 13:
        vampire_snatcher->move("/d/Terel/common/town/mansion/graveyard/grvyard1", 1);
        break;       

        case 14:
        vampire_snatcher->move("/d/Krynn/solace/graves/o_grave2", 1);
        break;
        
        case 15:
        vampire_snatcher->move("/d/Krynn/solace/graves/fence2", 1);
        break;
                    
        case 16:
        vampire_snatcher->move("/d/Krynn/solace/graves/o_grave3", 1);
        break;
        
        case 17:
        vampire_snatcher->move("/d/Krynn/solace/graves/o_grave5", 1);
        break;
        
        case 18:
        vampire_snatcher->move("/d/Krynn/solace/graves/o_grave6", 1);
        break;
        
        case 19:
        vampire_snatcher->move("/d/Krynn/solace/graves/o_grave4", 1);
        break;
        
        case 20:
        vampire_snatcher->move("/d/Krynn/solace/graves/grave19", 1);
        break;
        
        case 21:
        vampire_snatcher->move("/d/Krynn/solace/graves/grave18", 1);
        break;
        
        case 22:
        vampire_snatcher->move("/d/Krynn/solace/graves/grave13", 1);
        break;
        
        case 23:
        vampire_snatcher->move("/d/Krynn/solace/graves/grave8", 1);
        break;
    }            
}


/*
 * Function name: monitor_dragon
 * Description  : Wizards can monitor the status of the dragon
 */
int
monitor_stuff(string str)
{
    if (str != "stuff")
    {
        write("'monitor stuff' is the correct syntax.\n");
        
        return 1;
    }
    
    if (this_player()->query_name() == "Nerull")
    {
        write("\n  __________________________________________________________");
    
        if (vampire_snatcher != 0)
        {           
            write("\n - Vorador:      "+MASTER_OB(environment(vampire_snatcher)));
        }
        
        if (coffin_token1 != 0)
        {
             write("\n - Coffintoken1: "+MASTER_OB(environment(coffin_token1)));
        }
        
        if (coffin_token2 != 0)
        {
             write("\n - Coffintoken2: "+MASTER_OB(environment(coffin_token2)));
        }
           
        if (puzzlebox1 != 0)
        {
             write("\n - Puzzlebox1: "+MASTER_OB(environment(puzzlebox1)));    
        }
        
        if (puzzlebox2 != 0)
        {
              write("\n - Puzzlebox2: "+MASTER_OB(environment(puzzlebox2)));      
        }
        
        if (puzzlebox3 != 0)
        {
              write("\n - Puzzlebox3: "+MASTER_OB(environment(puzzlebox3)));       
        }
        
        if (puzzlebox4 != 0)
        {
              write("\n - Puzzlebox4: "+MASTER_OB(environment(puzzlebox4)));       
        }
        
        if (puzzlebox5 != 0)
        {
              write("\n - Puzzlebox5: "+MASTER_OB(environment(puzzlebox5)));       
        }
        
        if (puzzlebox6 != 0)
        {
              write("\n - Puzzlebox6: "+MASTER_OB(environment(puzzlebox6)));       
        }
        
        if (vampirenation_target != 0)
        {
              write("\n - Vampire target: "+MASTER_OB(environment(vampirenation_target)));      
        }
        
        if (anomality_target != 0)
        {
              write("\n - Anomality location: "+MASTER_OB(environment(anomality_target)));      
        }
               
        if (vamp_nationagent1 != 0)
        {
              write("\n - Vampire Agent 1: "+MASTER_OB(environment(vamp_nationagent1)));      
        }
        
        if (vamp_nationagent2 != 0)
        {
              write("\n - Vampire Agent 2: "+MASTER_OB(environment(vamp_nationagent2)));      
        }
        
        if (vamp_nationagent3 != 0)
        {
              write("\n - Vampire Agent 3: "+MASTER_OB(environment(vamp_nationagent3)));      
        }
        
        if (vamp_nationagent4 != 0)
        {
              write("\n - Vampire Agent 4: "+MASTER_OB(environment(vamp_nationagent4)));      
        }
        
        if (vamp_nationagent5 != 0)
        {
              write("\n - Vampire Agent 5: "+MASTER_OB(environment(vamp_nationagent5)));      
        }
        
        if (vamp_nationagent6 != 0)
        {
              write("\n - Vampire Agent 6: "+MASTER_OB(environment(vamp_nationagent6)));      
        }
        
        if (vamp_nationagent7 != 0)
        {
              write("\n - Vampire Agent 7: "+MASTER_OB(environment(vamp_nationagent7)));      
        }
        
        if (vamp_nationagent8 != 0)
        {
              write("\n - Vampire Agent 8: "+MASTER_OB(environment(vamp_nationagent8)));      
        }
        
        if (vamp_nationagent9 != 0)
        {
              write("\n - Vampire Agent 9: "+MASTER_OB(environment(vamp_nationagent9)));      
        }
        
        if (vamp_nationagent10 != 0)
        {
              write("\n - Vampire Agent 10: "+MASTER_OB(environment(vamp_nationagent10)));      
        }

        write("\n  ----------------------------------------------------------\n");
        
        return 1;
    }
    
    
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    //spawnrate = VAMPIRES_MASTER->occ_active_vamp_members_check();
    
    spawnrate = 10;
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Vampire object handler room");
    
    set_long("Vampire Control room.\nFUNCTIONS:\n---------\n"
    +" - monitor stuff.\n");
    
    // Populate realm with coffin_tokens, every 3 hours (coffin tokens
    // expire after 3 hours). 
    set_alarm(2.0, COFFINTOKENSPAWN, &coffin_populate());
    
    
    roundrobin = 1;
    
    // activate vampire nation agents for spawning.
    active_nation_agents = 1;
    
    // Populate realm with puzzle boxes, every 3 hours (puzzle boxes
    // expire after 3 hours).
    //set_alarm(2.0, PUZZLESPAWN, &puzzlebox_populate());
    
    set_alarm(5.0, 10800.0, &puzzlebox1_populate());
    set_alarm(15.0, 10800.0, &puzzlebox2_populate());
    set_alarm(25.0, 10800.0, &puzzlebox3_populate());
    set_alarm(35.0, 10800.0, &puzzlebox4_populate());
    set_alarm(45.0, 10800.0, &puzzlebox5_populate());
    set_alarm(55.0, 10800.0, &puzzlebox6_populate());
    
    // Npc targets for reputation system
    set_alarm(20.0, 20800.0, &vampirenation_target_populate());
    
    // Anomalities, places of power for vampires
    set_alarm(3.0, 50000.0, &anomality_target_populate());
    
    // Npc Vampire Vorador expires after 3600 seconds before
    // relocating.    
    set_alarm(2.0, 3600.0, &vampire_snatcher_populate());
    
    set_alarm(10.0, 10800.0, &vampirenation_agent_populate());

    //stop_clone_coffins = 0;
    
    //clone_coffins();
  
    reset_faerun_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_VAMP_LOG("wizard_entry_vamp_log",
            "The immortal " +ob->query_name() 
            +" entered the Vampires Object Handler room!\n");
           
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. "
            +"UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


int
clean_tokens(string str)
{
    write("You try to nullify the existing items.\n");
    
    puzzlebox1->remove_object();
    puzzlebox2->remove_object();
    puzzlebox3->remove_object();
    puzzlebox4->remove_object();
    puzzlebox5->remove_object();
    puzzlebox6->remove_object();
    
    vamp_nationagent1->remove_object();
    vamp_nationagent1 = 0;
    
    vamp_nationagent2->remove_object();
    vamp_nationagent2 = 0;
    
    vamp_nationagent3->remove_object();
    vamp_nationagent3 = 0;
    
    vamp_nationagent4->remove_object();
    vamp_nationagent4 = 0;
    
    vamp_nationagent5->remove_object();
    vamp_nationagent5 = 0;
    
    vamp_nationagent6->remove_object();
    vamp_nationagent6 = 0;
    
    vamp_nationagent7->remove_object();
    vamp_nationagent7 = 0;
    
    vamp_nationagent8->remove_object();
    vamp_nationagent8 = 0;
    
    vamp_nationagent9->remove_object();
    vamp_nationagent9 = 0;
    
    vamp_nationagent10->remove_object();
    vamp_nationagent10 = 0;
    
    vampire_snatcher->remove_object();
    coffin_token1->remove_object();
    coffin_token2->remove_object();
    
    vampirenation_target->remove_object();
    
    anomality_target->remove_object();
    
    active1 = 0;
    active2 = 0;
    active3 = 0;
    active4 = 0;
    active5 = 0;
    active6 = 0;
    
    active_nation = 0;
    
    active_anomality = 0;
    
    return 1;
}



/*
 * Function name: init 
 * Description  : Add functions to the room
 */
void
init()
{
    ::init();
    add_action(monitor_stuff, "monitor");
    add_action(clean_tokens, "clean");
    //add_action(clean_tokens, "respawn");
}