/* Rose garden's rooms coded by Shiva
 * Modified by Marisol 04/19/99
 * to be used in the Telberin's wildflower/life garden.*/


#include "../defs.h"

#include <macros.h>
#include <stdproperties.h>

inherit TELBERIN_ROOM;
inherit "/d/Emerald/lib/room_tell";

#include "/d/Emerald/sys/properties.h"
#include "/d/Emerald/sys/terrain_types.h"
  

void
create_wild_garden()
{
}

nomask void
create_telberin_room()
{
 
    set_short("A peaceful wildlife garden"); 
    add_item("garden",
        "This garden is a miracle of design and beauty. Wildflowers, "+
        "domestic flowers and several bushes are arranged artfully to "+
        "promote the presence of butterflies, hummingbirds, bees and "+
        "other fauna. The place brings a sense of peace and beauty that "+
        "inspires the soul. The garden follow the geometrical pattern "+
        "of a sextagon, with two elf-made creeks that flow to the "+
        "center of the garden. The green lawn is the perfect place for "+
        "a relaxing picnic. A hedge of rhododendron enclosed the "+
        "garden, creating a secret place away from the rest of the "+
        "city.\n");

    add_item(({"hedge", "hedge of rhododendron", "rhododendron"}),
        "This is a tall rhododendron hedge that blocks your view "+
        "outside the garden. Emerald leaves and bright pink flowers "+
        "comprise the tall hedge that surrounds the garden.\n");

    add_item(({"ground", "path", "lawn"}),
        "The path is covered with soft, sweet smelling grass. The "+
        "grass is a very pale green color, very soothing to look at. "+
        "This lawn spread its verdant sofness around the garden, "+
        "forming a sextagon. Wildflowers and bushes "+
        "enclosed the lawn, so as you walk, you can enjoy their beauty. "+
        "The lawn is a perfect place to have a picnic with "+
        "friends.\n");

    add_item("creeks", 
        "Two artificial creeks crisscross the garden. They divide the "+
        "garden in four section with its flowers. The water flows from "+
        "the south of the garden to the pond at the center. It flows "+
        "out of the pond to the north under the rhododendron. Aesthetic "+
        "boulders are placed in both sides of these little creeks and "+
        "inside on it, making the display truthful to nature. A green "+
        "weed with orange blossoms crawls around the pond, with "+
        "butterflies flapping delicately from flower to flower. The "+
        "sound of the water is soothing, making this place one of "+
        "beauty and peace.\n");
  
    add_item("pond",
        "A small pond is feed by two artificial creeks. The water is "+
        "clean and clear. The bottom of the pond is rocky "+
        "and you can see playful fishes swimming without fear inside "+
        "the peaceful water. The pond can't be reach by walking feet, "+
        "though. A healthy weed with very bright orange flowers "+
        "surround the pond, cutting it off from pedestrians.\n");


    add_item("buildings",
        "Tall and gracefull buildings from the Royal circle stand "+
        "proudly above the garden. The Royal Palace, the Keepers's "+
        "buildings and the Temple rose to the sky like a benediction "+
        "of beauty.\n");

        add_item(({"weeds", "green weeds", "orange blossoms"}),
        "These weeds are Butterfly Weed, a very charming wildflower "+
        "with its merry orange blossoms that butterflies love to "+
        "visit, together with industrious bees.\n");

    add_item(({"wildflowers", "flowers"}),
        "Many flowers from the countryside and hot house are found here "+
        "in this wonderful garden. They were selected to attract the "+
        "wildlife that live in Emerald. Their fragance is subtle and "+
        "relaxing, not at all overwhelling like the rose garden.\n");
  


    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);
    add_prop(OBJ_I_CONTAIN_WATER, 1); 

    set_tell_time(100);
    add_tell(({
        "You hear the water bubbling merrily in the creeks.\n",
        "Two playful squirrels run up and down and all around "+
        "playing tag with each other.\n",
        "You hear the happy chirping of a robin.\n",
        "A lark sings his heart out in a nearby branch.\n",
        "An emerald hummingbird flies swiftly from flower to flower.\n",
        "A bright yellow butterfly flaps her wings slowly before "+
        "taking off from one of the many flowers in the garden.\n",
        "You hear the busy buzzing of bees and flies somewhere in "+
        "the garden.\n",
        "A hairy caterpiller crawls rapidily a bush's branch before "+
        "dissapearing inside the foilage.\n",
        "A blue and black butterfly hovers over your head before flying "+
        "away.\n",
        }));

    create_wild_garden(); 
}

int
drink_it(string str)
{
    string what, where;
    int i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    /* See if syntax is "drink <something> from <something>" */
    if (sscanf(str, "%s from %s", what, where) != 2)
    {
        /* See if syntax is "drink from <something>" */
        if (!sscanf(str, "from %s", where))
        {
            /* Syntax must simply be "drink <something>" */
            what = str;
        }
    }

    if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (where && !parse_command(where, ({}), "[the] 'creek'"))
    {
        /* Technically, this isn't going to show because of the standard
         * 'drink' command.  Really, there's not much choice, though,
         * since we don't want to return 1.
         */
        notify_fail("Drink from where?\n");
        return 0;
    } 

    /* Drink small amounts up to 500 soft */
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("After scooping some water from the creek, you "+
             "drink from your cupped hands. The water tastes "+
             "weird.\n");
    }
    else
    {
        write("After scooping some water from the creek, you "+
             "drink from your cupped hands. The water tastes "+
             "weird.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the creek.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(drink_it, "drink");
} 

                                                          
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}                    


void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air is filled with the fresh scent of flowers "+ 
        "and sweet grass.\n");
        return;
    }

}
