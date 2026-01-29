/*************************************************************************
 * - Cavern room                                                       - *
 * - Created by Damaris 03/2001                                        - *
 * - Recoded by Damaris 02/2002                                        - *
 *************************************************************************/
#pragma no_clone
#pragma save_binary
#pragma strict_types

#include "../defs.h"
#include "/d/Khalakhor/sys/basic.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/herbsearch";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Variables to hold our descrip lines to choose from (randomly).
 */
private static string *shorts = ({
  "in the %s section of the Cavern of Woes", });

private static string *desc1 = ({
  "   This is the %s section of the dreaded Cavern of Woes.",
  "   This is the %s section of the feared Cavern of Woes.",
  "   This is the %s section of the unholy Forest of shadows.",
  "   This is the %s section of the mysterious Cavern of Woes.",
  "   This is the %s section of the mystifying Cavern of Woes.",
  "   This is the %s section of the bewildering Cavern of Woes.",
  "   This is the %s section of the puzzling Cavern of Woes.",
  "   This is the %s section of the arcane Cavern of Woes.",
  "   This is the %s section of the fabled Cavern of Woes.",
  "   This is the %s section of the great Cavern of Woes in the "+
  "cursed lands of Chaos.",
  "   This is the %s section of the Cavern of Woes in the dark "+
  "lands of Chaos.",
  "   This is the %s section of the Cavern of Woes in the "+
  "unholy lands of Chaos.",
  "   This is the %s section of the vast Cavern of Woes in the "+
  "sanctified lands of Chaos.",
  "   This is the %s section of the imposing Cavern of Woes in the "+
  "ruin lands of Chaos.",
  "   This is the %s section of the abundant Cavern of Woes in the "+
  "doomed lands of Chaos.",
  "   This is the %s section of the solid Cavern of Woes in the "+
  "murky lands of Chaos.", });

private static string *desc2 = ({
  "There are large old trees mingled within the cavern walls. "+
  "They are with gnarled branches that stretch "+
  "outward in a haunting way.",
  "There are gnarled trees mingled within the cavern walls "+
  "that cast doomed shadows everywhere, "+
  "extending the aura of dread.",
  "There are large trees mingled within the cavern walls "+
  "that cast a gnarled appearance upon the area.",
  "There are huge dark trees mingled within the cavern walls "+
  "that stretch their branches like claws "+
  "scratching.",
  "There are colossal trees mingled within the cavern walls "+
  "that seem to emanate darkness.",
  "There are mystifying trees mingled within the cavern walls "+
  "that appear reach out from an unholy "+
  "darkness toward the ceiling.",
  "There are mysterious trees mingled within the cavern walls "+
  "that appear to be dead and yet are "+
  "thriving in this vast area.", });

private static string *desc3 = ({
  "The air is filled with the sickening stench of death and decay.",
  "The air is cold, damp, and filled with the stench of death and decay.",
  "The damp, cold air is chilling.",
  "The wind whispers the soft promise of death.",
  "The air is filled with unholy dread.",
  "The wind blows softly bringing with it the stench of blood and death.",
  "The air is filled with an intoxicating smell of death and blood.", });

private static string *extra_long, section = "middle";

/*********************************************************************
 * - This will get added to the end of the compiled long desc.     - *
 *********************************************************************/
public void
set_xlong(mixed arg)
{
    if (stringp(arg))
        arg = ({ arg });

    extra_long = arg;
}

public string *
query_xlong()           { return extra_long; }

/*********************************************************************
 * - Compile the associated items to go with a room description.   - *
 *********************************************************************/
static varargs void
config_items(int x, int y, int z)
{
    set_add_item(0);


    add_item(({"cavern"}),
      "This is the Cavern of Woes. It is shrouded with "+
      "mystery embedded in death.\n");
    add_item(({"tree", "trees"}),
      "There are large gnarled trees embedded in the walls "+
      "in every direction. "+
      "Each gives off an unholy feeling of death.\n");
    add_item(({"ground"}),
      "The ground is covered in moss, lichen and "+
      "dried up twigs and fallen leaves.\n");
    add_item(({"leaf", "leaves"}),
      "There are many dried leaves upon the ground along "+
      "with those hanging in the trees.\n");

}

/*************************************************************************
 * - Compile the associated room tells to go with the room description.- *
 *************************************************************************/
static varargs void
config_tells(int x, int y, int z)
{
    clear_tells();

    set_tell_time(350 + random(50));

    add_tell("From the distance, you hear screeching of bats.");
    add_tell("Shadows flutter past catching the corner of your eye.");
}

/*********************************************************************
 * - Compile a random room description with associated items.      - *
 *********************************************************************/
static varargs void
config_room(string str, string extra = "")
{
    mixed *arr = allocate(3);

    if (strlen(str))
        section = str;

    arr[0] = random(sizeof(desc1));
    arr[1] = random(sizeof(desc2));
    arr[2] = random(sizeof(desc3));

    config_items(arr[0], arr[1], arr[2]);
    config_tells(arr[0], arr[1], arr[2]);

    arr[0] = desc1[arr[0]];
    arr[1] = desc2[arr[1]];
    arr[2] = desc3[arr[2]];
    
    set_short(sprintf(one_of_list(shorts), section));
    set_long(sprintf("%s %s %s %s %s\n",
      sprintf(arr[0], section), arr[1], arr[2],
      (pointerp(extra_long) ? one_of_list(extra_long) : one_of_list(({
          "The cavern continues on in all directions.",
          "The cavern leads onwards in all directions." }))), extra));
}


/*********************************************************************
 * - Basic room stuff.                                             - *
 *********************************************************************/
static void
create_khalakhor_room()
{

    set_name("cavern");
}
