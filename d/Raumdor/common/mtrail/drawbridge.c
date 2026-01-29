/* Mountain trail room, credit to Sarr and Nerull */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

#define THEORDER_DIR "/d/Raumdor/guilds/the_order/rooms/"


int block_player()
{
    if (this_player()->query_wiz_level())
    {
        write("The massive portcullis rises and let your "
        +"through.\nYou step into the castle and the darkness "
        +"enshrouds you completely.\n");
        
        tell_room(environment(this_player()), "The massive portcullis "
        +"opens.\n"+QCTNAME(this_player())+" steps into the castle.\nThe massive "
        +"portcullis drops down with a bank, closing the entrance.\n", this_player());
        return 0;
    }
    
    write("You bump into the closed massive portcullis, but nothing happens. "
    +"The iron bars are there for a reason. Nothing larger "
    +"than a mouse can pass through the massive portcullis "
    +"blocking the entrance.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" bumps into the massive closed portcullis.\n", this_player());

    return 1;
}


void
create_room()
{
    ::create_room();
    
    set_short("At the drawbridge of Castle Gylar");
    
    set_long("You stand in the middle of the drawbridge with nothing "
    +"but sheer vertical drops on both sides. Despite visible wear "
    +"and tear, the bridge itself seems very sturdy. Glancing over "
    +"the edge you can clearly see skeletal remains and rusted armours "
    +"littered on and between the sharp rocks at the bottom. Straight "
    +"ahead towards the east you "
    +"see a closed portcullis leading to the inside of the "
    +"castle and you get a sinking feeling you might not receive a "
    +"warm welcome. The only known safe route is west, back to the road "
    +"leading away from this terrifying location.\n");
        
    add_item(({"portcullis"}),"Made entirely out of rusted metal bars "
    +"nailed together it is shaped like a massive door covering the "
    +"castle entrance. It is closed.\n");
    
    add_item("castle","The urge to flee this place increases relative "
    +"to your proximity to the castle. The stench of death and rotting "
    +"flesh grows stronger by the minute. Being this close the spires "
    +"are no longer visible from the ground, but despite the panic "
    +"inducing surroundings you notice that what looked like pristine "
    +"castle walls from afar, was but an optical illusion. The castle "
    +"reveals a dire need of the attention of a mason. The portcullis "
    +"that makes out the entrance at the other end of the bridge "
    +"is closed.\n");
    
    add_item(({"bridge","drawbridge"}),"Made entirely or iron, the "
    +"bridge rests on a ledge connecting the end of the road and the "
    +"bridge itself smoothly. You can vaguely make out the massive hinges "
    +"underneath on the other side. Once upon a time it might have had some "
    +"sort of railing to prevent accidents, but all you can see are iron "
    +"stumps confirming your deepest fear – fighting someone on the bridge "
    +"may end up a brief affair. There is only one chain connecting the "
    +"bridge to the castle itself, and a vacant hole in the castle wall "
    +"suggest there once were two. Considering the girth of the remaining "
    +"chain though, you start to contemplate whether or not it can be "
    +"raised with just one..\n");
    
    add_item("bottom","As step towards the edge and look closer at your "
    +"own potential fate you refrain from any attempt at counting how "
    +"many victims claimed by gravity. As you shift your focus upwards "
    +"and move towards the relative safety of the middle you contemplate "
    +"whether or not you’ve just found the source of the stench that is "
    +"now doing a real number on both mind and stomach.\n");
    
    add_item("cliffs","As you glance over the side you feel your "
    +"stomach turn as you think about tumbling down.\n");
    
    add_item(({"mountain", "mountains"}),"The mountain landscape is both "
    +"pretty and scary at the same time. The tops are sporadically clad in "
    +"snow and ice, sprinkled with boulders and deep crevisses, comforted "
    +"by large steep drops into various abysses of sharp rocks.\n");
    
    add_exit(THEORDER_DIR + "21", "east", block_player);
    add_exit(MTRAIL_DIR + "mtrail_path5", "west");
}