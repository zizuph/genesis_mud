/* Mountain trail room, credit to Sarr and Nerull */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    ::create_room();
    
    set_short("On a mountaintrail overlooking Castle Gylar");
    
    set_long("You stand overlooking the castle entrance, but as the stench "
    +"of death and decay assaults your nostrils and your life choices "
    +"once again come into question, you get the distinct feeling nothing "
    +"is going to improve by increasing your proximity to the castle. "
    +"Straight ahead you see a dilapidated bridge, and you begin to "
    +"wonder if it will actually hold your weight. You can vaguely "
    +"spot remnants of chains and some mechanisms in the distance, "
    +"which leads you to believe that it's a drawbridge, but one "
    +"stuck in the down position. As you glance over the edges of "
    +"the cliff that separates the road and the castle you realize "
    +"that not only is there a vertical drop, but sharp rocky peaks "
    +"ready to welcome you to the afterlife if you care to investigate "
    +"whether you have developed wings. Looking eastwards you notice a "
    +"short pillar on the right side where the path ends and the bridge "
    +"begins. You can continue east to cross the bridge and proceed "
    +"towards the castle gate or follow the path westward to leave the "
    +"area.\n");
        
    add_item(({"bridge","drawbridge"}),"Made entirely or iron, the "
    +"bridge rests on a ledge connecting the end of the road and the "
    +"bridge itself smoothly. You can vaguely make out the massive hinges "
    +"underneath on the other side. Once upon a time it might have had some "
    +"sort of railing to prevent accidents, but all you can see are iron "
    +"stumps confirming your deepest fear - fighting someone on the bridge "
    +"may end up a brief affair. There is only one chain connecting the "
    +"bridge to the castle itself, and a vacant hole in the castle wall "
    +"suggest there once were two. Considering the girth of the remaining "
    +"chain though, you start to contemplate whether or not it can be "
    +"raised with just one.\n");
    
    add_item(({"pillar"}),"The pillar looks like it has been carved "
    +"right out of the mountain. On the side you see the grim skull of "
    +"Khiraa roughtly carted into it.\n");
    
    add_item("castle","The urge to flee this place increases relative "
    +"to your proximity to the castle. The stench of death and rotting "
    +"flesh grows stronger by the minute. Being this close the spires "
    +"are no longer visible from the ground, but despite the panic "
    +"inducing surroundings you notice that what looked like pristine "
    +"castle walls from afar, was but an optical illusion. The castle "
    +"reveals a dire need of the attention of a mason. The portcullis "
    +"that makes out the entrance at the other end of the bridge "
    +"is closed.\n");
    
    add_item(({"portcullis"}),"Made entirely out of rusted metal bars "
    +"nailed together it is shaped like a massive door covering the "
    +"castle entrance.\n");
    
    add_item("cliffs","As you glance over the side you feel your "
    +"stomach turn as you think about tumbling down.\n");
        
    add_item(({"ground", "groves", "large groves"}),"The ground here looks "
    +"rather well travelled judging by the groves and marks in the "
    +"mud all around "
    +"the area. Horses, carriages, and machines of war and boots probably.\n");
    
    add_item(({"rock", "rocks", "boulder", "boulders"}),"Littered "
    +"everywhere in this area, in different sizes and shapes, befitting the "
    +"natural environment.\n");
       
    add_item(({"mountain", "mountains"}),"The mountain landscape is both "
    +"pretty and scary at the same time. The tops are sporadically clad in "
    +"snow and ice, sprinkled with boulders and deep crevisses, comforted "
    +"by large steep drops into various abysses of sharp rocks.\n");
       
    add_item(({"mud"}),"While it's higher up in the mountains, melted "
    +"water mixed "
    +"with dust and other particules have created a thin slurry covering much "
    +"of the ground.\n");
    
    add_exit(MTRAIL_DIR + "drawbridge", "east");
    add_exit(MTRAIL_DIR + "mtrail_path4", "west");
}