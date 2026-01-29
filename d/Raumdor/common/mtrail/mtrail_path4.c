/* Mountain trail room, credit to Sarr and Nerull */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    ::create_room();
    
    set_long("You stand in the middle of a trail. Well, more of "
    +"the remnants of a road. You start to wonder what forces it "
    +"must have taken to carve this perilous pathway as you glance down "
    +"the sheer cliffs on both sides. The castle ever more visible as "
    +"you look to the east. The four towers making out the corners of "
    +"the building gives you the impression of impregnability, and as "
    +"details are revealed so do you begin to question your life choices. The "
    +"spires are adorned with skewered, petrified men and women. The tips "
    +"are spears large enough to warrant injury to something very "
    +"large, and seems to exit out of the corpses through the mouth. As "
    +"your eyes follow the road you make out a bridge and in the "
    +"distance, the entrance to the castle. To the northwest you spot "
    +"a rocky plateau with tents and "
    +"wagons strategically placed among boulders and rocks.\n");
    
    add_item("cliffs","As you glance over the side you feel your "
    +"stomach turn as you think about tumbling down.\n");
    
    add_item("plateau","The rocky and rather flat plateau to the "
    +"northwest are occupied with tents, soldiers and machines "
    +"of war. It appears they are preparing for sieging the "
    +"castle.\n");
    
    add_item("castle","Getting closer to the castle all of your "
    +"instincts tell you to go back the way you came as everything "
    +"seems to darken by the minute. A distinct scent fills your "
    +"nostrils, and as you think back you realize you have smelled it "
    +"before - rotting death and utter decay.\n");
    
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
    
    add_exit(MTRAIL_DIR + "siegecamp_1", "northwest");
    add_exit(MTRAIL_DIR + "mtrail_path5", "east");
    add_exit(MTRAIL_DIR + "mtrail_path3", "southwest");
}