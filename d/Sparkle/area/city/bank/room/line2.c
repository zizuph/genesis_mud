/*
 * /d/Sparkle/area/city/bank/room/line2.c
 *
 * This is the actual banking room of the Bank of Sparkle.
 * Banking functions are done here.
 * 
 *
 * Created January 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard"; /* inherit basic bank file */

/* prototypes */
public void             tube_action(int *coins, int going_up);

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */

public void
create_bank_room()
{
    set_short("Bank of Sparkle central hall, south");
    set_long("The main hall of the Main Branch of the Gnomes of Genesis "
        + "could simply be described as majestic. The "
        + "walls and pillars appear to be made of a coarse white marble, "
        + "while the marble of the floor is polished and is semi-"
        + "reflective. A "
        + "semi-circular teller stand is centrally located against the "
        + "northern wall and provides service to three fenced-off, "
        + "haphazardly arranged queues.\n\n"); 

    
    /* Add_Items */
    add_item( ({ "room", "hall", "main hall", "bank", "area", "building",
                 "main branch", "giant room" }),
          "The main exit is a "
        + "marble archway, that leads south to bronze double-doors. The "
        + "walls and pillars appear to be made of a coarse white marble, "
        + "while the marble of the floor is polished and is semi-"
        + "reflective. The ceiling is high and paneled in a dark, red "
        + "wood. The windows are positioned close to the ceiling and "
        + "nearly extend the entire width of each wall. They provide "
        + "ample light to make the marble shine. A "
        + "semi-circular teller stand is centrally located against the "
        + "northern wall and provides service to three fenced-off, "
        + "haphazardly arranged queues.\n"); 
        
    add_item( ({ "floor", "ground", "marble floor", "polished floor",
                 "polished marble" }),
          "The floor is made of polished marble that shines in the light. "
        + "It appears to be very well maintained.\n");
        
    add_item( ({ "light" }),
          "The large windows let light into the hall allowing all inside "
        + "the privilege of sight.\n");
        
    add_item( ({ "ceiling", "wooden ceiling", "wood ceiling", "red wood",
                 "redwood", "dark wood", "darkwood" }),
          "The ceiling must be two stories up and is made of dark, red "
        + "wood.\n");
        
    add_item( ({ "windows", "window", "large windows", "large window",
                 "giant windows", "giant window", "long windows",
                 "long window" }),
          "The windows extend the length of each wall, which creates a "
        + "strange sense that the ceiling is floating above. This is clearly "
        + "not the case, but the optical illusion is quite deceptive. The "
        + "windows appear to be a handful of feet high and let in a lot "
        + "of light.\n");
                       
    add_item( ({ "door", "bronze door", "doors", "bronze doors",
                 "main exit", "exit", "entrance", "main entrace",
                 "heavy bronze doors" }),
          "Thick bronze doors grant access to the south. They are perfectly "
        + "centered on the southern wall, beneath a white marble arch. "
        + "The doors look very thick and very heavy. A large lever is "
        + "attached to one of the doors.\n");
        
    add_item( ({ "lever", "large lever" }),
          "A large lever is used to latch the heavy bronze doors shut "
        + "during times when the bank is closed.\n");
        
    add_item( ({ "archway", "arch", "white marble arch" }),
          "It appears that the gnomes created "
        + "this archway for two purposes; to ease the citizenry into the "
        + "giant room and to block the unsightly door mechanism from the "
        + "queues.\n");
    
    add_item( ({ "citizenry" }),
          "The citizenry are people who use the bank, of course.\n");
        
    add_item( ({ "door mechanism", "mechanism", "unsightly mechanism" }),
          "The mechanism consists of classic gnomish parts: Wheels, gears, "
        + "bells, beams, levers, balances, pins, rods and many other "
        + "unidentifiable parts. It appears to be "
        + "the way that the gnomes are able to move the heavy bronze "
        + "doors.\n");
        
    add_item( ({ "wheels", "wheel", "gears", "gear", "bells", "bell", 
                 "beams", "beam", "levers", "balances", "balance",
                 "pins", "pin", "rods", "rod", "other unidentifiable parts",
                 "parts", "unidentifiable parts", "other parts", 
                 "gnomish parts" }),
          "Most, if not all, gnomish contraptions contain those. "
        + "It is unlikely that a gnome would create a machine without at "
        + "least one!\n");
                
    add_item( ({ "walls", "pillars", "blocks", "wall", "pillar", }),
          "The walls and pillars are made of coarse white marble. They are "
        + "cool to the touch and allow for reasonable illumination from the "
        + "windows. The north wall is the most interesting of them all.\n");
                 
    add_item( ({ "wood", "marble" }),
          "There is a lot of wood and marble in this room. You will have to "
        + "be more specific.\n");
        
    add_item( ({ "north wall", "north walls", "northern wall" }),
          "The northern wall looks quite impressive. A large mural "
        + "covers the wall.\n");
        
    add_item( ({ "mural" }),
          "The mural depicts the skyline of the city of Sparkle. You can see "
        + "prominent buildings and the harbour.\n");
        
    add_item( ({ "buildings", "sparkle", "Sparkle", "prominent buildings" }),
          "The buildings in the mural appear to show the proper "
        + "arrangement of the buildings in Sparkle. Of course, the "
        + "bank is in the centre of the mural.\n");
        
    add_item( ({ "harbour", "harbor" }),
          "A harbour is painted into the eastern part of the mural. "
        + "The harbour appears to be an exact replica of the Sparkle "
        + "harbour. You can see a single dhow at anchor in the harbour.\n");
        
    add_item( ({ "dhow", "boat", "ship" }),
          "A traditional dhow sits docked in the harbour of the mural. "
        + "It has a single lateen sail.\n");
        
    add_item( ({ "sail", "single sail", "lateen sail", "triangular sail" }),
          "The sail on the dhow is triangular and has a black silhouette "
        + "of a rooster on it's centre.\n");
         
    add_item( ({ "rooster", "silhouette" }),
          "The rooster on the sail has his beak pointed away from the city "
        + "and seems to stare at you through a shiny jadestone eye.\n");
        
    add_item( ({ "beak" }),
          "The beak of the rooster appears be clenching a gnarled vine.\n");
     
    add_item( ({ "gnarled vine", "vine" }),
          "The vine in the rooster's beak appears to be gnarled. What might "
        + "be the meaning of this vine?\n");
        
    add_item( ({ "jade eye", "jadestone eye", "jadestone", "eye" }),
          "The rooster's eye is a deep green colour and is "
        + "semi-translucent. It looks like the eye follows your every "
        + "movement. This discovery would make the average person "
        + "unsettled, to say the least.\n");
        
    add_item( ({ "west wall", "west walls", "south wall", "south walls",
                 "western wall", "southern wall", }),
          "Compared to the north wall, this wall is unremarkable and "
        + "rather mundane.\n");
          
    add_item( ({ "east wall", "eastern wall" }),
          "The eastern wall is rather mundane, except for a giant "
        + "fan that is positioned just below the window. The fan must "
        + "be used for heating and cooling the main hall.\n");
        
    add_item( ({ "giant fan", "fan" }),
          "This fan is quite large and is spinning very quickly.\n");
          
    add_item( ({ "stand", "semi-circular stand", "teller stand" }),
          "The stand seems perfectly centred on the northern wall. "
        + "It is semi-circular and the tellers behind the glass help "
        + "patrons through little windows. Behind the tellers is a "
		+ "gnomish strongbox and "
        + "glass tubes that run diagonally up towards the ceiling.\n");
        
    add_item( ({ "glass", "glass wall" }),
          "The tellers work from behind a glass wall.\n");
          
    add_item( ({ "little windows", "tellers", "teller" }),
          "The tellers work from behind the little windows in the "
        + "glass. There are iron bars protecting the tellers from any "
        + "dangers that may face them through the window.\n");
	    
    add_item( ({ "iron bars", "bars" }),
          "Iron bars span the distance from the top to the bottom of "
        + "the little windows. They protect the tellers from the "
        + "general public.\n");
        
    add_item( ({ "haphazard queues", "queue", "queues", "fences", "fence" }),
          "Three haphazardly arranged queues lead toward the semi-circular "
        + "teller stand. They are simply made (which is odd for gnomes), by "
        + "attaching iron posts with lengths of ribbon. The queue closest "
        + "to you is labelled by a sign.\n");
        
    add_item( ({ "sign" }),
          "This is a lovely sign!\n");
        
    add_item( ({ "closest queue" }),
          "The closest queue is labelled with a sign.\n");
      
    add_item( ({ "posts", "iron posts", "lengths", "ribbon", "post",
                  "iron post" }),
          "The iron posts and ribbons form the queues. They seem haphazardly "
        + "placed.\n");
        
    add_item( ({ "tubes", "glass tubes" }),
          "The tubes extend from behind the teller stand to the ceiling. "
        + "They are angled so that the base is mounted behind the teller "
        + "stand and the top goes into the ceiling in the northern two "
        + "corners of the room. Inside the tubes, what appears to be a "
        + "screw spins. You can see coin deposits being pushed up the "
        + "right tube by the screw turning clockwise and withdrawls coming "
        + "down the left tube by a screw turning counter clockwise. "
		+ "The left tube feeds a gnomish strongbox, from which the "
		+ "tellers retrieve coins.\n");
	
    add_item( ({ "left tube" }),
          "The left tube allows for the descent of coins and gems from "
        + "the central vaults. A screw (if not broken) continuously "
        + "turns counter clockwise to slow the descent of the coins "
        + "and gems. The bottom of the tube connects directly to the "
        + "gnomish strongbox, behind the teller stand.\n");
	
    add_item ( ({ "right tube" }),
          "The right tube allows for the ascent of coins and gems from "
        + "the teller stand to the central vaults. A screw (if not "
        + "broken) continuously turns clockwise to provide upward "
        + "movement for coins and gems.\n");

    add_item( ({ "gnomish strongbox", "strongbox" }),
          "Coins are "
        + "secured behind the teller stand. It is clear that "
        + "few coins and gems are kept here, because deposits and "
        + "withdrawals "
        + "can be seen travelling to and from the central vaults in "
        + "the glass tubes above. The left tube is connected directly "
        + "to the strongbox.\n");
        
    add_item( ({ "screw", "screws" }),
          "The screws inside the tubes are the cause for the upward movement "
        + "of coins into the gnomish vault system, and the slowed descent of "
        + "the withdrawals. Every couple minutes, the "
        + "screws come to a screeching halt, but return to their steady "
        + "pace after an awkward pause in banking services.\n");
        
    add_item( ({ "coin", "coins", "gem", "gems" }),
          "Coins and gems are moving up and down in the tubes.\n");
		  
/* Add_tells */
	int x,y,z;
    string *coin, *gem, *size;
    
    coin    = ({"copper", "silver", "gold", "platinum"});
    gem     = ({"vivid alexandrites", "red beryls", "pink tourmalines",
                "glittering diamonds", "lucent emeralds", "red rubies", 
                "black pearls", "blue sapphires", "yellow topazes",
                "green jades", "lapis lazulis", "iridescent opals",
                "white pearls", "blue-green aquamarines",
                "green peridots", "blue spinels", "red spinels",
                "purple amethysts", "shining bloodstones",
                "banded tourmalines", "lambent moonstones", "black onyxes",
                "blue topazes", "red carnelians", "green chrysoprases",
                "orange-red garnets", "red spinels", "yellow ambers",
                "striped chalcedonies", "oval turquoises", "pink corals",
                "red jaspers", "marbled agates", "golden pyrites",
                "rose quartzes" });
    size	= ({"A few", "Several", "Many", "A heap of"	});		
                
    x = random(sizeof(coin));
    y = random(sizeof(gem));
    z = random(sizeof(size));
	
    add_tell( size[z] + " " + coin[x] + " coins slowly begin ascending "
        + "the screw in the right tube.\n");
	
    add_tell( size[z] + " " + gem[y] + " slowly begin ascending the screw "
        + "in the right tube.\n");
		
    add_tell( size[z] + " " + gem[y] + " begin descending the left tube "
        + "towards the gnomish strongbox.\n");
		
    add_tell( size[z] + " " + coin[x] + " coins begin descending the left "
        + "tube towards the gnomish strongbox.\n");
		
/* General tells */
    add_tell("A band of adventurers enter and wait in the appropriate "
        + "line.\n");
    add_tell("A woman enters the bank and leaves northeast.\n");
    add_tell("A pair of travelling merchants enter the bank and leave "
        + "northwest.\n");
	
/* cmd_items */

    add_cmd_item( ({ "bank", "gnomes", "gnome", "strongroom" }),
               "rob", "@@rob");
    
    add_cmd_item( ({ "terms of usage" }), "read", "@@read_usage");
    add_cmd_item( ({ "instructions" }), "read", "@@read_instructions");
    add_cmd_item( ({ "sign" }), "read", "@@read_sign");
	
/* Properties */
    add_prop(ROOM_I_LIGHT, 3); /* Well-lit room */

/* Exits */
    add_exit
    ("/d/Genesis/start/human/town/bank", "south", 0); /* Bank */ 
    add_exit(BANK_ROOM + "line3", "northeast", 0); /* first floor line 3 */
    add_exit(BANK_ROOM + "line1", "northwest", 0); /* first floor line 1 */
    
} /* create_bank_room */

/*
 * Function name:       reset_room
 * Description  :       restore npcs and signs as needed
 */
public void
reset_room()
{
   
    object otbus;
    object deposit;

    if (!present("deposit"))
    {
        deposit = clone_object("/d/Sparkle/area/city/bank/obj/deposit");
        /* deposit->set_bank_id( , "New Sparkle"); */
        deposit->set_no_show_composite(1);
        deposit->move(this_object());
    }
    
    if (!present("otbus"))
    {
        otbus = clone_object("/d/Sparkle/area/city/bank/npc/otbus");
        otbus->move(this_object());
    }
    
} /* reset_room */

public int
rob()
{
    write("You approach the teller stand with the intent to rob the bank.\n"
        + "The gnomish teller presses a large red button and guards "
        + "appear at every exit!\nYou feel a sting and a shock on your back "
        + "and your next cognitive thought is from the gutter on the "
        + "street.\n\n");
    this_player()->move_living("incapacitated, with a regiment of gnomish "
        + "guards, after attempting to rob the bank", 
          "/d/Sparkle/area/city/rooms/streets/center_g" );	
    return 1;
} /* rob */

/*
 * Function name:           read_sign()
 * Description  :           Contains the sign information
 * Arguments    :           
 * Returns      :           1 - Success
 *                          0 - Failure
 */
public int
read_sign()
{
    write("+---------------+\n"
        + "|  Adventurers  |\n"
        + "+---------------+\n");
    return 1;
} /* read sign */

/*
 * Function name:           convert_number_to_string()
 * Description  :           Converts the numerical value into words.
 * Arguments    :           
 * Returns      :           
 */
public string
convert_number_to_string(int num)
{
    switch (num)
    {
    case 0:
        return "zero";
    
    case 1..5:
        return LANG_NUM2WORD(num);
    
    default:
        return "many";
    }
}

/*
 * Function name:           hook_deposit_coins()
 * Description  :           
 * Arguments    :           
 * Returns      :           
 */
public void 
hook_deposit_coins(int * coins) 
{ 

    set_alarm(1.0, 0.0, &tube_action(coins, 1));

} /* hook_deposit_coins() */

/*
 * Function name:           hook_withdraw_coins()
 * Description  :           
 * Arguments    :           
 * Returns      :           
 */
public void
hook_withdraw_coins(int * coins) 
{

    set_alarm(1.0, 0.0, &tube_action(coins, 0));
	
} /* hook_withdraw_coins() */

/*
 * Function name:        tube_action
 * Description  :        have the tubes move some coins around
 * Arguments    :        int coins    - array of the coin amounts
 *                       int going_up - true if the coins should go
 *                                      up rather than down the tube.
 */
public void
tube_action(int *coins, int going_up)
{
    string  *coin_types      = ({ "copper", "silver", "gold", "platinum" });
    string   coin_plural     = "";
    string   other_plural    = "s";
    int      i = 0;
    string   action_txt      = "";

    foreach(int coin_type : coins)
    {
        if (coin_type)
        {
            if (coin_type > 1)
            {
                coin_plural = "s";
                other_plural = "";
            }

            if (going_up)
            {
                action_txt += 
                    capitalize(convert_number_to_string(coin_type))
                  + " " + coin_types[i]
                  + " coin" + coin_plural + " "
                  + "begin" + other_plural + " to slowly climb the"
                  + " revolving screw in the right tube.\n";
            }
            else
            {
                action_txt += 
                    capitalize(convert_number_to_string(coin_type))
                  + " " + coin_types[i]
                  + " coin" + coin_plural + " "
                  + "begin" + other_plural + " "
                  + "descending the left tube to refill the "
                  + "gnomish strongbox.\n";
            }
        }

        coin_plural = "";
        other_plural = "s";
        i++;
    }

    tell_room(this_object(), action_txt);
} /* tube_action */

