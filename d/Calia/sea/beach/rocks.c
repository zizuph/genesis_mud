
 /* Rocks leading to Worshippers Guild */
 /* By Jaacar 04.27.96 */

#pragma save_binary

inherit "/std/room";
inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("On the rocks");
    set_long("You are climbing on some rocks above the "+
        "village on the beach.  There is sand strewn about "+
        "across the ground and rocks, probably unconsciously tracked up here "+
        "from the villagers that sit up here to collect their "+
        "thoughts.  Travel to the west is cut short by a steep cliff, "+
        "below which you can see many scattered outcroppings that would "+
        "make falling or jumping suicidal.  To the east a steep hillside "+
        "climbs up, covered in large rocks, preventing further progress in "+
        "that direction.  From here you may climb over the "+
        "rocks to the south, or head back down into the village.\n");

    add_item("sand","It is very fine sand that has been tracked up here "+
        "by villagers who come up here to relax away from the hustle and "+
        "bustle of the village below.\n");

    add_item("ground","The ground here is very uneven, covered mostly "+
        "by rocks, and small patches of sand.\n");

    add_item(({"sea","water"}),"The water looks very beautiful from "+
        "here.  You can now see why some villagers come up here to "+
        "get away from everything, and relax while watching the "+
        "sea.\n");

    add_item("outcroppings","The outcroppings look very sharp, and "+
        "make you feel very queasy about looking over the edge.\n");

    add_item(({"cliff","steep cliff"}),"The cliff overlooks the sea "+
        "out to your west.  It is quite far down to the water below, "+
        "probably over three rods distance.  You decide that it's "+
        "probably not a good idea to jump over or climb down the "+
        "cliff as it would be very detrimental to your health.\n");

    add_item(({"hillside","steep hillside"}),"The hillside leads upwards "+
        "to the east and is covered in large, unclimbable rocks.  Further "+
        "passage this way is not possible.\n");

    add_item("beach","You see the beach down below you, a few villagers "+
        "going about their daily business.  It appears that it would "+
        "be an easy climb down to reach it.\n");

    add_item("rocks","The rocks to the south are fairly large, but "+
        "easy enough to climb over and around as you "+
        "need to.\n");

    add_item("village","The small fishing village is just a "+
        "small climb down the rocks north of you.  You feel you "+
        "could descend down them easily.\n");

    set_tell_time(80);

    add_tell("A gentle breeze blows on your face.\n");
    add_tell("Clouds pass briefly over the sun, blocking it from view.\n");
    add_tell("Bright rays of sunshine pour over you as clouds that were "+
        "blocking the sun pass by.\n");

    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_exit(BEACH+"village7","down",0,1);
    add_exit("/d/Calia/guilds/elementalists/temple/newpath","south",0,1);
}
