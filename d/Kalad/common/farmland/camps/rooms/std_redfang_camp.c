/*
 *  /d/Kalad/common/farmland/camps/room/std_redfang_camp.c
 *
 *  This is the master file for rooms in the red fang camp
 *
 *  Created October 2015, by Andreas Bergstrom (Zignur)
 */
 
#pragma strict_types

inherit "/std/room";

#include </sys/macros.h>
#include </sys/stdproperties.h>
#include </sys/time.h>
#include "../defs.h"
#include <stdproperties.h>

/* Definitions */

/* Global Variables */
private int Redfang_camp_state = 1;
private int Goblin_warrior_counter = 0;


/* Prototypes */
public nomask void  create_room();
public void         create_redfang_camp_room();
public void         add_redfang_camp_items();
public string       get_camp_state_desc();
public int          burn_redfang_camp(string str);
public void         set_redfang_camp_state(int state);
public void         notify_redfang_camp_room();
public void         add_redfang_camp_subscriber();
public void         init();


/*
 * Function name:        create_room
 * Description  :        the basic constructor for rooms
 */
public nomask void
create_room()
{
    /* Map file */
    add_prop(ROOM_S_MAP_FILE, "redfang_trainingcamp.txt");
    add_name(REDFANG_CAMP_ROOM);
    add_prop(ROOM_I_LIGHT, 1);
    create_redfang_camp_room();
    enable_reset(200);  /* make resets as fast as possible for grinding */
    
} /* create_room */


/*
 * Function name:        create_redfang_camp_room
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_redfang_camp_room()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} /* create_redfang_camp_room */


/*
 * Function name:        add_redfang_camp_items
 * Description  :        Adds and removes items in the redfang camp rooms 
 *                       based on the current status of the camp
 */
public void
add_redfang_camp_items()
{      
    /* Get the state of the redfang camp from the warrior room */
    Redfang_camp_state = RF_WAR_ROOM->get_redfang_camp_state();
        
    /* Check if the camp is burning */
    if(Redfang_camp_state == 2)
    {
        // Remove the incorrect items from the previous state
        remove_item("crate");
        remove_item("refuse");
        remove_item("barrel");
        remove_item("wind shelter");
        remove_item("hides");
        remove_item("branches");
        remove_item("goblin");
        
        // Add the new items
        add_item( ({ "camp"}),
            "The camp is burning!\n");
        add_item( ({ "barrel", "barrels", "old barrel","old barrels",
                     "broken equipment", "equipment"}),
            "Old barrels and broken equipment are being consumed by the"
          + " raging fire.\n");
        add_item( ({ "wind shelter", "wind shelters","crude wind shelter",
                     "crude wind shelters","shelter","shelters"}),
            "The crude wind shelters burn brightly, slowly being consumed"
          + " by the flames.\n");
         add_item( ({ "fire", "fires","flame","flames"}),
            "The crude wind shelters burn brightly, slowly being consumed"
          + " by the flames.\n");
        add_item( ({ "hides", "hide","animal hides","animal hide",
                     "branches","branch","wooden branch","wooden branches"}),
            "The blazing fires consume the hides and the branches on the wind"
          + " shelters.\n");  
        add_item( ({ "goblin", "goblins"}),
            "The goblins are desperately trying to extinguish the flames,"
          + " but with very little success.\n");
        return;
    }
    
    /* Check if the camp is burned down */
    if(Redfang_camp_state == 3)
    {
        // Remove the incorrect items from the previous state
        remove_item("crate");
        remove_item("barrel");
        remove_item("fire");
        remove_item("hides");
        remove_item("branches");
        remove_item("wind shelter");
        remove_item("camp");
        remove_item("goblin");
        
        // Add the correct items
        add_item( ({ "wind shelter", "wind shelters","crude wind shelter",
                     "crude wind shelters","shelter","shelters"}),
            "Only fragments and ashes remain.\n");
        add_item( ({ "ashes", "ash", "fragments","fragment"}),
            "Only ashes and fragments remain of the former camp.\n");            
        add_item( ({ "camp"}),
            "The camp is burnt down only ashes remain.\n"); 
        add_item( ({ "goblin", "goblins"}),
            "The goblins are extinguishing the the last of the burning"
          + " flames.\n");
        return;
    }
   
    /* Check if the camp is being rebuilt */
    if(Redfang_camp_state == 4)
    {
        // Remove the incorrect items from the previous state
        remove_item("ashes");
        remove_item("camp");
        remove_item("crate");
        remove_item("barrel");
        remove_item("fire");
        remove_item("hides");
        remove_item("branches");
        remove_item("wind shelter");
        remove_item("camp");
        remove_item("goblin");
        remove_item("spoils");
        
        // Add the correct items
        add_item( ({ "camp"}),
            "The camp is slowly being rebuilt.\n"); 
        add_item( ({ "goblin", "goblins"}),
            "The goblins are rebuilding the camp and bringing back spoils"
          + " in order to restore their supplies.\n");   
        add_item( ({ "wind shelter", "wind shelters","crude wind shelter",
                     "crude wind shelters","shelter","shelters"}),
            "The goblins are slowly rebuilding the crude wind shelters out"
          + " of wooden branches and animal hides.\n");
        add_item( ({ "hides", "hide","animal hides","animal hide",
                     "branches","branch","wooden branch","wooden branches"}),
            "Wooden branches and animal hides are used to rebuild the"
          + " crude wind shelters.\n");
        add_item( ({ "spoils", "supplies"}),
            "Wooden crates, barrels and equipment are being brought into"
          + " the camp by the goblins.\n");
        return;
    }
    
    /* This is the default items ( state 1 ) of the camp */
    
    /* Make certain all the old items are removed */
    remove_item("camp");
    remove_item("soil");
    remove_item("refuse");
    remove_item("barrel");
    remove_item("pike");
    remove_item("wind shelter");
    remove_item("branches");
    remove_item("hides");
    remove_item("goblin");
    
    add_item( ({ "camp"}),
       "The camp is full of activity, you hear the sounds of"
     + " goblins doing their daily tasks.\n"); 

    add_item( ({ "soil", "dark soil", "ground"}),
        "The ground is covered with a dark hardened soil.\n");   
    add_item( ({ "crate", "crates", "broken crates",
                 "broken crate", "cracked crates",
                 "equipment","old equipment"}),
        "Cracked and broken crates are scattered all over the"
      + " camp. Thanar markings indicate that these must have" 
      + " been stolen from the Thanar's within the city.\n");
    add_item( ({ "refuse", "pile of refuse", "refuse pile"}),
        "A foul stench rises from several piles of refuse that"
      + " litters the camp.\n");   
    add_item( ({ "barrel", "barrels"}),
        "Empty or half empty wooden barrels lie all over the"
      + " camp site.\n");   
    add_item( ({ "pike", "pikes", "gruesome pike", "gruesome pikes",
                 "wooden pikes","wooden pike"}),
        "Gruesome skull adorned wooden pikes have been stuck into the soil."
      + "\n");
    add_item( ({ "wind shelter", "wind shelters","crude wind shelter",
                 "crude wind shelters","shelter","shelters"}),
        "These are crude wind shelters made from wood branches and animal hides."
      + " They are built to offer protection from the weather but seem"
      + " to do a very poor job.\n");
    add_item( ({ "branches", "branch","wooden branch",
                 "wooden branches"}),
        "Wooden branches are used to support the crude wind shelters.\n");
    add_item( ({ "hides", "hide","animal hides","animal hide"}),
        "Animal hides have been crudely sewed together to function as a roof"
      + " for the wind shelters.\n");       
    add_item( ({ "goblin", "goblins"}),
        "The goblins are sparring with each other, honing their deadly"
      + " skills in the art of combat.\n");
      
} /* add_redfang_camp_items */


/*
 * Function name:        get_camp_state_desc
 * Description  :        returns a fitting description based on the state
 *                       of the camp.
 * Returns      :        a string with a fitting description
 */
public string
get_camp_state_desc()
{
    /* Get the state of the redfang camp from the warrior room */
    Redfang_camp_state = RF_WAR_ROOM->get_redfang_camp_state();
        
    /* Check if the camp is burning */
    if(Redfang_camp_state == 2)
    {
        return "Someone has set the camp on fire, the flames consume"
          + " everything in sight. Old barrels and broken equipment are being" 
          + " consumed by the blazing hot flames. Crude wind shelters made"
          + " from wood branches and animal hides, burn brightly all over"
          + " the camp. Goblins are desperately trying to extinguish the flames,"
          + " but with very little success.";
    }
    
    /* Check if the camp is burned down */
    if(Redfang_camp_state == 3)
    {
        return "The camp is completely burned down, as a fire has consumed"
          + " everything in sight. Only fragments and ashes remain of the" 
          + " former wind shelters. The goblins are extinguishing the last"
          + " of the burning flames.";
    }
   
    /* Check if the camp is being rebuilt */
    if(Redfang_camp_state == 4)
    {
        return "The camp is slowly being rebuilt, The damage from the"
          + " recent fire is being repaired. Crude wind shelters are" 
          + " being constructed out of wooden branches and animal hides."
          + " The goblins are bringing back spoils from their recent raids"
          + " in order to restore their supplies.";
    }
    
    /* This is the default state of the camp */
    return "Old broken equipment, crates, barrels and refuse litter"
      + " the ground. Gruesome skull adorned wooden pikes have been stuck"
      + " into the soil. Crude wind shelters made from wood branches and"
      + " animal hides, provide very little protection from the weather."
      + " Goblins are sparring with each other, honing their skills in"
      + " the art of butchering followers of Thanar.";
    
} /* get_camp_state_desc */


/*
 * Function name:        burn_redfang_camp
 * Description  :        Attemps to burn the redfang camp
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
burn_redfang_camp(string str)
{
    /* Get the state of the goblin camp from the warrior room */
    Redfang_camp_state = RF_WAR_ROOM->get_redfang_camp_state();
    
    /* Get the goblin warrior counter from the war room */
    Goblin_warrior_counter = RF_WAR_ROOM->get_goblin_warrior_counter();
    
    if(!strlen(str))
    {
        notify_fail("Burn what? <burn camp>, perhaps?\n");
        return 0;
    }
   
    if (!parse_command(str, ({}),
        "[the] 'camp'"))
    {
        return 0;
    }
    
    /* Will only be able to burn it if its in its normal state 1 */
    if(Redfang_camp_state ==2)
    {
        notify_fail("The camp is already burning.\n");
        return 0;
    }
    
    if(Redfang_camp_state ==3)
    {
        notify_fail("The camp is already burning.\n");
        return 0;
    }
    
    if(Redfang_camp_state ==4)
    {
        notify_fail("There are not enough materials to burn.\n");
        return 0;
    }   
    
    if(Goblin_warrior_counter > 0)
    {
        notify_fail("You dont think that will be possible while"
         + " there are still goblin warriors left alive.\n");
        return 0;
    }    

    /* If we got this far it means we can burn the camp */
    
    write("You grab a burning log from a nearby fire and throw it" 
     + " into a wind shelter. The flames spread like wildfire,"
     + " setting the whole camp on fire!\n");
     
    tell_room(this_object(), QCTNAME(this_player()) + " grabs a burning"
     + " log from a nearby fire and throws it into a wind shelter. The" 
     + " flames spread like wildfire, setting the whole camp on"
     + " fire!\n", this_player());
    
    /* Set the prop for burning the camp */
    this_player()->add_prop(RF_CAMP_BURNED, 1);

    /* Set the state */
    set_redfang_camp_state(2);
     
    /* Initate the burn states */
    set_alarm(300.0, 0.0,&set_redfang_camp_state(3));
    set_alarm(600.0, 0.0,&set_redfang_camp_state(4));
    set_alarm(900.0, 0.0,&set_redfang_camp_state(1));
    return 1;    
   
} /* burn_redfang_camp */


/*
 * Function name:        set_redfang_camp_state
 * Description  :        returns the value of the Redfang_camp_state in 
                         the war_room
 * Arguments    :        int state - the new state on the camp
 */
public void
set_redfang_camp_state(int state)
{
    RF_WAR_ROOM->set_redfang_camp_state(state);
    RF_WAR_ROOM->notify_redfang_camp_room(file_name(this_object()));
    
} /* set_redfang_camp_state */


/*
 * Function name:        notify_redfang_camp_room
 * Description  :        Notifies the room that the state has changed
 *                       
 */
public void
notify_redfang_camp_room()
{
    // Add the correct items
    add_redfang_camp_items();
    tell_room(this_object(), "You notice that the state of the camp has changed.\n");
    
} /* notify_redfang_camp_room */


/*
 * Function name:        add_redfang_camp_subscriber
 * Description  :        Add this room to the subscriber list of the war room
 *                       
 */
public void
add_redfang_camp_subscriber()
{
    RF_WAR_ROOM->add_redfang_camp_room(file_name(this_object()));
   
    
} /* add_redfang_camp_subscriber*/


/*
 * Function name: init
 * Description  : add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(burn_redfang_camp, "burn");
} /* init */

