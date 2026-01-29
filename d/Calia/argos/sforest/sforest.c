/*********************************************************************
 * - sforest.c                                                     - *
 * - Base file for the silent forest rooms in Calia                - *
 * - Created by Damaris@Genesis 10/2008                            - *
 *********************************************************************/

#pragma no_clone
#pragma save_binary
#pragma strict_types

#include "basic.h"
#include "sforest.h"
inherit "/d/Calia/std/room";
inherit "/d/Calia/lib/herbsearch";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Variables to hold our descrip lines to choose from (randomly).
 */
private static string *shorts = ({
  "the %s portion of a dark silent forest", });

private static string *desc1 = ({
  "   Soft shadows dancing together join, forming a smooth "+
  "dimness blanketing this %s portion of forest.",
  "   Velvety shadows spin inward with shimmering particles of "+
  "light forming an enchanting shadow that covers this %s portion "+
  "of forest.",
  "   Soft strands of light filtering in high above the canopy "+
  "mingles with shadows forming a silent darkness that covers this "+
  "%s portion of forest.",
  "   Remaining shadows with strands of light filter from the "+
  "canopy to cast a silent glow in this %s portion of the forest.",
  "   Darkness clings to the shadows as strands of radiant light "+
  "disperse from above the canopy to cast a sanguine glow in this "+
  "%s portion of the forest.",
  "   Ethereal shadows glide through the darkness as slender shards "+
  "of light circulate from above the canopy to cast an unearthly "+
  "glow in this %s portion of the forest.",
  "   A labyrinth of flickering light cascades through the denseness "+
  "to cast a heavenly glow in this %s portion of the forest.",
  "   Flowing strands of light penetrate the canopy falling within the "+
  "darkness forming a soft glow that covers this %s portion of forest.",
  "   Streaming fragments of light break through the canopy diminishing "+
  "within shadows forming a dimness that covers this %s portion of "+
  "forest.",});

private static string *desc2 = ({
 "Tall trees shoot upwards forming a dark canopy. Twisted branches "+
 "stretching inward and outward create mangled images within the "+
 "shadows.",
 "Colossal trees burst upwards forming a thick canopy. Crooked branches "+
 "expanding inward and outward create odd images within the shadows.",
 "Enormous trees surround the area forming a huge canopy above. Deformed "+
 "branches groping inward and outward create distorted images within the "+
 "shadows.",
 "Monumental trees cluster upwards forming a huge canopy. Twisted "+
 "branches manipulating inward and outward create mysterious images "+
 "within the shadows.",
 "Giant trees shoot upwards forming a colossal canopy. Bent branches "+
 "tangling inward and outward create strange images within the shadows.",
 "Grand trees line the area forming a grand canopy above. Disfigured "+
 "branches knot together inward and outward create dire images within "+
 "the shadows.",
 "Big trees burst upwards forming a thick canopy. Contorted branches "+
 "snare together inward and outward create ghostly images within the "+
 "shadows.",
 "Large trees cluster upwards forming a huge canopy. Damaged "+
 "branches web together inward and outward create twisted images "+
 "within the shadows.",
 "Outstretched trees cluster upwards forming a huge canopy. Large "+
 "branches twisting inward and outward create ominous images within "+
 "the shadows.",
 "Massive trees surround the area forming a huge canopy above. "+
 "Misshapen branches growing inward and outward create intriguiing "+
 "images within the shadows.", });

private static string *desc3 = ({
 "The air is filled with the scent of wildflowers.",
 "The air cool and slightly humid.",
 "The cool crisp wind blows brings with it the sweet scent of "+
 "wildflowers.",
 "The wind whispers through the tress bringing the soft scent of "+
 "wildflowers.",
 "The air is cool with the sweet scent of wildflowers.",
 "The cool wind whispers through the trees bringing the sweet scent "+
 "of wildflowers.",
 "The crisp cool air is filled the wildflowers.",
 "The cool air is crisp with the smell of wildflowers.",
 "The air is cool and a sweet scent of wilderflowers linger.",
 "The air is filled with the sweet scent of wildflowers.",});

/* Random monster lists, please add in alpha order.
 * [0] == Path to npc.
 * [1] == Monster entrance message, used by move_living
 */
//private static string *monsters = ({
//   ({ MON(apparition), " slowly forms out of a swirl of mist!\n" }),
//   ({ MON(druj),  " floats out of the gloom!\n" }),
//   ({ MON(ghoul), " rips itself out of the ground!\n" }),
//   ({ MON(gskeleton), " smashes its way out of the trees!\n" }),
//   ({ MON(giskeleton), " drops out of the trees!\n" }),
//   ({ MON(gzombie), " tears itself out of the ground!\n" }),
//   ({ MON(lskeleton), " claws its way out of the trees!\n" }),
//   ({ MON(skeletal_archer), " claws its way out of the trees!\n" }),
//   ({ MON(lzombie), " rips itself out of the ground!\n" }),
//   ({ MON(odic),  " seeps in out of the trees!\n" }),
//   ({ MON(revenant), " leaps out over the hill screaming!\n" }),
//   ({ MON(shade), " pounces out of the shadows!\n" }),
//   ({ MON(spectre), " flies out from the night sky in front of you!\n" //}),
//   ({ MON(utroll), " smashes its way into your path!\n" }),
//   ({ MON(vision), " slowly forms in front of you!\n" }),
//   ({ MON(wight),  " claws its way out of the ground!\n" }),
//   ({ MON(wraith), " slowly materializes in front of you!\n" }),
//   ({ MON(eowra), " crashes out of the trees!\n"}),
//   ({ MON(death_crow), " flies out of the trees.\n"})
//	});

private static string *extra_long, portion = "middle";
private static int is_on_path = 0, summon = 0;
private static object *summoned = ({});


/*
 * Set if this room is on the path or not.
 */
public void
set_on_path(int i)      { is_on_path = i; }

public int
query_on_path()         { return is_on_path; }

/*
 * This will get added to the end of the compiled long desc.
 */
public void
set_xlong(mixed arg)
{
    if (stringp(arg))
        arg = ({ arg });

    extra_long = arg;
}

public string *
query_xlong()           { return extra_long; }

/*
 * Compile the associated items to go with a room description.
 */
static varargs void
config_items(int x, int y, int z)
{
    set_add_item(0);

    add_item(({"forest"}), query_long);
    add_item(({"tree", "trees"}),
      "There are large gnarled trees in every direction. "+
      "Each gives off an unholy feeling of death.\n");
    add_item(({"ground"}),
      "The ground is covered in moss, lichen and "+
      "dried up twigs and fallen leaves.\n");
    add_item(({"leaf", "leaves"}),
      "There are many dried leaves upon the ground along "+
      "with those hanging in the trees.\n");

    if (is_on_path)
    {
        add_item( ({"path"}),
            "It is old and worn, made of dirt and stone.\n");
    }
}

/*
 * Compile the associated room tells to go with the room description.
 */
static varargs void
config_tells(int x, int y, int z)
{
   clear_tells();

    set_tell_time(150 + random(50));

    add_tell("A leaf gently falls from a tree.");
    add_tell("The forest is deafly silent.");
    add_tell("A soft breeze barely whispers through the trees.");
    add_tell("There is a small rustle in the underbrush.");
    add_tell("You have the feeling of being watched.");

}

/*
 * Compile a random room description with associated items.
 */
static varargs void
config_room(string str, string extra = "")
{
    mixed *arr = allocate(3);

    if (strlen(str))
        portion = str;

    arr[0] = random(sizeof(desc1));
    arr[1] = random(sizeof(desc2));
    arr[2] = random(sizeof(desc3));

    config_items(arr[0], arr[1], arr[2]);
    config_tells(arr[0], arr[1], arr[2]);

    arr[0] = desc1[arr[0]];
    arr[1] = desc2[arr[1]];
    arr[2] = desc3[arr[2]];

    set_short(sprintf(one_of_list(shorts), portion));
    set_long(sprintf("%s %s %s %s %s\n",
      sprintf(arr[0], portion), arr[1], arr[2],
      (pointerp(extra_long) ? one_of_list(extra_long) : one_of_list(({
          "The forest continues on in all directions.",
          "The forest leads onwards in all directions." }))), extra));
}

/*
 * Refresh the herbs, different amounts, different variety.
 */
private varargs void
reset_herbs(int diff = 3)
{
    string *arr = FOREST_HERBS; herbs = ({});
    arr = filter(arr, not @ random @ &identity(diff));
    set_up_herbs(arr, ({"here", "ground", "trees"}), 5 + random(5));
}

/*
 * Recycle the herbs and room desc and do some cleanup.
 */
public void
reset_room()
{
    object *obs = all_inventory(TO);;

    ::reset_room();

    /* There are players, dont modify */
    if (sizeof(FILTER_PLAYERS(obs)))
        return;

    reset_herbs(3 + random(3));
    config_room();

    if (query_prop(ROOM_I_NO_CLEANUP))
        return;

    if (sizeof(obs))
    {
#ifdef DUMP
        obs->move(DUMP, 1);
#else
        obs->remove_object();
#endif
    }
}

/*
 * Basic room stuff.
 */
static void
create_room()
{
    ::create_room();
    set_name("forest");
}

/*
 * This makes sure we have a minimum tiredness value for
 * walking through the forest.
 */
#define MIN_TIRED_EXIT  2

public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired, mixed non_obv)
{
    if (intp(tired) && (tired < MIN_TIRED_EXIT))
        tired = MIN_TIRED_EXIT;

    return ::add_exit(place, cmd, efunc, tired, non_obv);
}

/*
 * Get the name of a living target in the room. (based on this_player())
 */
public varargs string
find_target(int diff)
{
    object *obs = FILTER_OTHER_LIVE(all_inventory(TO));

    if (!sizeof(obs) || (diff > 1 && !random(diff)))
        return "";
    else
        return " " + OB_NAME(one_of_list(obs));
}

/*
 * Do some stuff if a player smells the area
 */
public void
hook_smelled(string what)
{
    int tmp;

    switch(random(4))
    {
    case 0:
        write("The foul air fills your nostrils and you feel "+
          "like your going to retch...\n");
        TP->command("$puke" + find_target(2));
        break;

    case 1:
        write("The diseased air rushes into your lungs!\n");
        tmp = (1 + random(4)); while(tmp--)
        {
            switch(random(3))
            {
            case 0: TP->command("$cough");      break;
            case 1: TP->command("$choke");      break;
            case 2: TP->command("$gag");        break;
            }
        }
        break;

    default:
        write("The cold, damp air has the scent of death and decay "+
          "in it.\n");
        if (!random(3))
            TP->command("$blanch sickly");
        break;
    }
}

/*
 * Function name: summon_monster
 * Description	: Summons monsters into a room.
 * Arguments	: int force  - Disregard summon limits.
 * 		      silent - Dont print entrance message.
 * 		      ran    - How many random do we want?
 */
public varargs void
summon_monster(int force, int silent, int ran = 3)
{
    int ix, sz = sizeof(summoned -= ({ 0 }));
    summon = 0; ran = 1 + random(ran);

    if (!force && sz > 12)
	return;

    if (!sizeof(FILTER_PLAYERS(all_inventory(TO))))
	return;

    while(ran--)
    {
//	ix = random(sizeof(monsters));
//	summoned += ({ clone_move(monsters[ix][0]) });
//	tell_room(TO, capitalize(LANG_ADDART(summoned[-1..][0]->short())) +
//	    monsters[ix][1]);
    }
}

public void
init()
{
    ::init();

    if (!is_on_path && !summon && !random(4) && interactive(TP))
	summon = set_alarm(2.0, 0.0, summon_monster);
}

