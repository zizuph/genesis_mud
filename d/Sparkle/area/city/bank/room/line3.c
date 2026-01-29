/*
 * /d/Sparkle/area/city/bank/room/line3.c
 *
 * This room is in the main hall of the Sparkle bank.
 * It connects to the vent shaft, main banking room and the back room.
 * 
 *
 * Created February 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard"; /* inherit basic bank file */

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */

public void
create_bank_room()
{
    set_short("Bank of Sparkle central hall, northeast");
    set_long("The northeast section of the central hall of the Bank of "
        + "Sparkle could simply be described as majestic. The "
        + "walls and pillars appear to be made of a coarse white marble, "
        + "while the marble of the floor is polished and is semi-"
        + "reflective. A "
        + "semi-circular teller stand is centrally located against the "
        + "northern wall and provides service to three fenced-off, "
        + "haphazardly arranged queues.\n\n"); 

    
    /* Add_Items */
    add_item( ({ "room", "hall", "main hall", "bank", "area", "building",
                 "main branch", "giant room" }),
          "At a distance, the main exit can be seen to the south. It has a "
        + "marble archway, that leads south to bronze double-doors. The "
        + "walls and pillars appear to be made of a coarse white marble, "
        + "while the marble of the floor is polished and is semi-"
        + "reflective. The ceiling is high and paneled in a dark, red "
        + "wood. The windows are positioned close to the ceiling and "
        + "nearly extend the entire width of each wall. They provide "
        + "ample light to make the marble shine. A "
        + "semi-circular teller stand is centrally located against the "
        + "northern wall and provides service to three fenced-off, "
        + "haphazardly arranged queues. You notice a service door to the "
        + "east.\n"); 
        
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
                
    add_item( ({ "service door", "simple door", "wooden door", "east door",
                 "eastern door" }),
          "This door is a simply made of wood. You cleverly figure that "
        + "it must be a service door, because there is a sign on it that "
        + "reads:\n"
        + "+-------------------+\n"
        + "| ServiceDoorToVent |\n"
        + "+-------------------+\n");
        
    add_item( ({ "doors", "door" }),
          "You can see multiple doors from this spot. Which door would you "
        + "like to inspect? Bronze doors or the east door?\n");
        
    add_item( ({ "bronze door", "doors", "bronze doors",
                 "main exit", "exit", "entrance", "main entrace",
                 "heavy bronze doors" }),
          "Far to the southwest, you see that thick bronze doors grant "
        + "access to the street. They are perfectly "
        + "centered on the southern wall, beneath a white marble arch. "
        + "The doors look very thick and very heavy. A large lever is "
        + "attached to one of the doors.\n");
        
    add_item( ({ "lever", "large lever" }),
          "You are too far away from the lever to see any details about it. "
        + "Perhaps you should travel to the southwest and look again?\n");
        
    add_item( ({ "archway", "arch", "white marble arch" }),
          "You are too far away from the archway to properly inspect it. "
        + "Perhaps you should travel southwest to investigate further?\n");
    
    add_item( ({ "citizenry" }),
          "The citizenry are people who use the bank, of course.\n");
       
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
          "The vine in the rooster's beak appears to be gnarled and woody.\n");
        
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
        + "be used for heating and cooling the main hall. Being close "
        + "to the wall, you see a service door leading east.\n");
        
    add_item( ({ "giant fan", "fan" }),
          "This fan is quite large and is spinning very quickly.\n");
          
    add_item( ({ "stand", "semi-circular stand", "teller stand" }),
          "The stand seems perfectly centred on the northern wall. "
        + "It is semi-circular and the tellers behind the glass help "
        + "patrons through little windows. Behind the tellers are "
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
          "+---------------+\n"
        + "|     Locals    |\n"
        + "+---------------+\n");
        
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
        + "down the left tube by a screw turning counter clockwise.\n");
        
    add_item( ({ "screw" }),
          "The screws inside the tubes are the cause for the upward movement "
        + "of coins into the upper vaults, and the slowed descent of the "
        + "withdrawls from the upper vaults. Every couple minutes, the "
        + "screws come to a screeching halt, but return to their steady "
        + "pace after an awkward pause in banking services.\n");
        
    add_item( ({ "coin", "coins" }),
          "Coins are moving up and down in the tubes.\n");

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
		

/* cmd_items */

    add_cmd_item( ({ "bank", "gnomes", "gnome", "strongroom" }),
               "rob", "@@rob");
			   
    add_cmd_item( ({ "sign" }), "read", "@@read_sign");
		
    /* Properties */
    add_prop(ROOM_I_LIGHT, 3); /* Well-lit room */

    /* Exits */
    add_exit(BANK_ROOM + "vent_shaft_1", "east", 0); /* Vent shaft */
    add_exit(BANK_ROOM + "line2", "southwest", 0); /* First floor line 2 */
    
} /* create_bank_room */

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

public int
read_sign()
{
	write("+---------------+\n"
        + "|     Locals    |\n"
        + "+---------------+\n");
	return 1;
} /* read sign */