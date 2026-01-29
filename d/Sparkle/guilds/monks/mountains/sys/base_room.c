/*******************************************************************\
| BASE_ROOM.C                                                       |
+-------------------------------------------------------------------+
| Base room module for everything in the mountain area.             |
\*******************************************************************/

/*
 * 04/03/13 Arandir     Added medium height mountain items
 * 03/09/14 Arandir     Fixed a double space typo
 * 02/11/09 Arandir     Added items
 * 02/09/29 Arandir     Added items
 * 02/07/20 Arandir	Created
 *
 */

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

#include "../defs.h"

inherit DG_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

/*
 * Function name : mt_blocked_exit
 * Description   : Used to block an exit to an unfinished area.
 *
 */

int mt_blocked_exit ()
{
  object oMe = this_player ();

  oMe->catch_msg (
    "A silhouette of a robed monk appears in front of you. With a " +
    "gesture of regret, the monk stops you from passing into the " +
    "area that is not yet finished, and disappears again.\n");
  tell_room (
    this_object (), "A silhouette of a robed monk briefly appears " +
    "in the air before " + QTNAME (oMe) + ".\n", oMe);

  return (EXIT_DELAY_DISABLED);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Items A-F                                                         |
\*******************************************************************/

void mt_item_bridge ()
{
  add_item (({ "bridge" }),
    "A narrow rope bridge slowly sways in the wind." +
    dg_embed_when_winter (" Some of the ropes are covered with a thin sheet of ice.") +
    dg_embed_when_not_winter (" The ropes and planks of the bridge look sturdy enough to carry you.") +
    "\n" +
    dg_embed_action ("stares at the bridge with an expression of distrust."));
  add_item (({ "rope", "ropes" }),
    "The bridge is made of sturdy hemp ropes, somewhat worn but otherwise in perfect shape." +
    dg_embed_when_winter (" Ice covers some of the ropes.") +
    "\n");
  add_item (({ "plank", "planks" }),
    "The wooden planks of the bridge are light and strong." +
    dg_embed_when_winter (" Icicles form underneath some of them.") +
    "\n");
}


void mt_item_cliffs_meadows ()
{
  add_item (({ "cliff", "cliffs", "cliffside", "cliff face", "edge", "cliff edge" }),
    dg_embed_when_winter ("The rock of the cliffs is withered and slippery. The numerous cracks and chimneys that scar the cliffs will not make climbing down much easier in the wet winter weather.") +
    dg_embed_when_not_winter ("The rock of the cliffs is withered but thankfully dry. The cracks and chimneys that line the cliffs make climbing down reasonably safe.") +
    "\n" +
    dg_embed_action ("leans over the edge of the cliff."));

  add_item (({ "rock", "rocks", "crack", "cracks", "chimney", "chimneys", "slope", "slide", "rockslide", "rockslides" }),
    "Wide cracks in the weathered rock form chimneys and rockslides, " +
    "in places turning the impassable cliffside into a steep rocky " +
    "slope.\n");

  add_item (({ "lowlands" }),
    "The green forest of the lowlands is visible down below the cliff.\n");
}


void mt_item_cliffs_valley ()
{
  add_item (({ "cliff", "cliffs" }),
    "The side of the valley is formed by steep cliffs, higher and " +
    "steeper on the eastern side than on the western one.\n");
}


void mt_item_crest_flat ()
{
  add_item (({ "crest" }),
    "The wide mountain crest slowly rises from south to north. Mostly " +
    "rocky, the inhospitable soil is still home to shrubs of mountain " +
    "pine.\n");
  add_item (({ "tuft", "tufts", "shrub", "shrubs" }),
    "Shrubs of mountain pine grow where few other trees would, " +
    "exploring every niche for whatever feeble protection it " +
    "can give from the bruising winds.\n");
}


void mt_item_crest_ridged ()
{
  add_item (({ "crest" }),
    "The wide mountain crest is ridged with four tall spires. There " +
    "is little vegetation around, but the conditions are still not " +
    "harsh enough to discourage the sturdy tufts of mountain pine " +
    "from seeking refuge here.\n");
  add_item (({ "tuft", "tufts", "shrub", "shrubs" }),
    "The withered mountain pine shrubs cover the rocky ground, " +
    "clinching to whatever bits of soil offer themselves. If it " +
    "were not for the fact that they actually survive here, you " +
    "would be almost fooled by their deceptively feeble look.\n");
}


void mt_item_forest_low ()
{
  add_item (({ "forest", "tree", "trees", "evergreens", "deciduous trees", "evergreen trees" }),
    "The forest is both below you under the cliff and further up the hill. Nearest to you, pine and larch trees prevail.\n");
  add_item (({ "pine", "pines", "pine tree", "pine trees" }),
    "Pines are evergreen trees with slender elongated needles. " +
    "Their wood is straight grained, white or yellow, usually " +
    "durable and resinous. It can vary from extreme softness " +
    "in the white pine to hardness in the longleaf pine.\n");
  add_item (({ "larch", "larches", "larch tree", "larch trees" }),
    "Being of the same family, larch trees are similar to pine trees. " +
    "They sport short fascicled needles that get shed seasonally.\n");
}


void mt_item_forest_medium ()
{
  add_item (({ "forest", "tree", "trees", "greenery" }),
    "Few trees manage to survive at this height, desperately " +
    "clinging to the rocky soil that does not seem to provide " +
    "nearly enough nourishment.\n");
  add_item (({ "pine", "pines", "pine tree", "pine trees" }),
    "Pines here are twisted and stunted, probably due to " +
    "the harsh mountain conditions.\n");
  add_item (({ "alder", "alders", "alder tree", "alder trees" }),
    "Alders here are twisted and stunted, more shrubs than trees. " +
    "Their toothed leaves move to the occasional gusts of wind.\n");
  add_item (({ "soil", "rocky soil", "patch", "patch of soil", "ground" }),
    "The ground is rather rocky this high in the mountains, for " +
    "whatever soil was here got swept away by the elements.\n");
  add_item (({ "rock", "rocks", "boulder", "boulders" }),
    "The ground is more rock than soil, withered and cracked " +
    "by the repetitive assaults of the elements.\n");
}


/*******************************************************************\
| Items G-L                                                         |
\*******************************************************************/

void mt_item_lake_far ()
{
  add_item (({ "lake", "tarn", "water" }),
    dg_embed_when_winter (
      "Partially frozen over, the mountain lake glitters in the distance " +
      "like a tiny jewel made of ice.") +
    dg_embed_when_not_winter (
      "The blue surface of the mountain lake is visible in the distance, " +
      "resembling a teary eye staring towards the sky.") +
    "\n");
}

void mt_item_lake_near ()
{
  add_item (({ "lake", "tarn", "water" }),
    "Its surface undisturbed, the mountain lake mirrors" +
    dg_embed_when_night (" the brightest stars of the night sky.") +
    dg_embed_when_not_night (" the white clouds and the blue sky.") +
    "\n");
}

/*******************************************************************\
| Items M-R                                                         |
\*******************************************************************/

void mt_item_mountains_low ()
{
  add_item (({ "mountain", "mountains", "hill", "hills" }),
    dg_embed_when_night ("Even this low in the mountains, you can smell the fresh mountain air, which comes as a welcome change from the stuffy atmosphere of the lowlands.") +
    dg_embed_when_not_night ("Standing at the very feet of the mountains, you see the majestic peaks to your north tower over you.") +
    "\n");
  add_item (({ "peak", "peaks" }),
    "Tall jagged peaks line the mountains to your north.\n");
}


void mt_item_mountains_medium ()
{
  add_item (({ "mountain", "mountains", "hill", "hills", "view" }),
    dg_embed_when_night ("In the dark of night, the cold and fresh mountain air is telling of the mountains around you.") +
    dg_embed_when_not_night ("The majestic peaks to your north are the most imposing but definitely " +
                             "not the only part of the mountain scenery. A wide crest stretches " +
                             "across most of the visible horizon, set off by a strip of a " +
                             "forest in the valley below.") +
    "\n");
  add_item (({ "peak", "peaks" }),
    "Tall jagged peaks line the mountains to your north.\n");
  add_item (({ "crest" }),
    "A wide crest cuts across the northern horizon like a monstrous wing.\n");
}


void mt_item_path_barely ()
{
  add_item (({ "path", "road", "trail" }),
    "The path is difficult to follow, at times barely visible " +
    "on the hard and inhospitable ground.\n");
}


void mt_item_path_trodden ()
{
  add_item (({ "path", "road", "trail" }),
    "Although not always easy to follow, the path you are on " +
    "is in fact well trodden, as if it was used regularly.\n");
}


/*******************************************************************\
| Items S-Z                                                         |
\*******************************************************************/

string mt_desc_serpent_tail_west ()
{
  string sDesc;
  object oMe = this_player ();

  if (dg_is_night ()) sDesc =
    "The dark of night prevents you from seeing pretty much " +
    "anything that is not real close.";
  else
  {
    sDesc = "To your west, a tall peak pierces the clouds. It " +
            "has unusually steep sides and a pointed tip.";
    if (oMe->resolve_task (DG_DIFFICULTY_KNOWNAME_HARD, DG_SKILLS_KNOWNAME))
    {
      sDesc += " You recognize the peak as Serpent Tail, the highest " +
               "point of the southern part of the mountains.";
    };
  };

  sDesc += "\n";
  return (sDesc);
}


void mt_item_serpent_tail_west ()
{
  add_item (({ "peak", "hill" }), &mt_desc_serpent_tail_west ());
}


void mt_item_spires_far ()
{
  add_item (({ "spire", "spires" }),
    "Four tall spires rise out of the mountain crest to the north. " +
    "Their rather steep sides suggest a seismic origin, even though " +
    "it is hard to tell for sure, for their tops disappear in clouds.\n");
}


void mt_item_spire_near_climbable ()
{
  add_item (({ "spire", "cliff" }),
    "The steep side of the spire towers above you, a silent witness " +
    "to violent eruptions that formed this part of the mountains. " +
    "At first glance, the side appears difficult to climb.\n");
  add_item (({ "side", "crack", "cracks", "notch", "notches" }),
    "The side of the spire is rather steep, but creased with " +
    "many small cracks and notches. The climber in you starts " +
    "looking for holds that would support you.\n");
  add_item (({ "support", "hold", "holds", "foothold", "footholds", "handhold", "handholds" }),
    "Even though the steep side of the spire appears difficult " +
    "to climb at first glance, you soon recognize numerous " +
    "holds that can support even a layman climber. You " +
    "realize that some of the holds are man made.\n");
}


void mt_item_spire_near_unclimbable ()
{
  add_item (({ "spire", "cliff", "side" }),
    "The steep side of the spire towers above you, a mute reminder " +
    "of the volcanic eruptions that appear to have given birth to " +
    "this part of the mountains. Lack of any decent holds quells " +
    "any thought of climbing you might have had.\n");
}


void mt_item_stream_deep ()
{
  add_item (({ "spring", "stream", "brook", "water" }),
    dg_embed_when_night ("The quiet of night carries the gurgling of the stream up to your ears from the valley below.") +
    dg_embed_when_not_night ("The silvery thread of the mountain stream is visible below you, hurrying towards the lowlands in the south.") +
    "\n");
}


void mt_item_valley_below ()
{
  add_item (({ "gorge", "valley", "canyon" }),
    "Gaping right below you, the valley appears even bigger than " +
    "it did from the path. The sides of the valley are creased " +
    "with tracks of rockslides. A silvery brook winds its way " +
    "on the bottom.\n");
  add_item (({ "rockslide", "rockslides", "tracks of rockslides" }),
    "Tracks of rockslides are visible in many places along the " +
    "steep sides of the valley. Further down, where the rocks " +
    "stopped in their fall, bizzare formations can be seen.\n");
  add_item (({ "shapes", "formation", "formations", "rock formation", "rock formations" }),
    "From tiny to huge, from unremarkable to bizzare, rock formations " +
    "line the bottom of the canyon. Some of them obstruct the stream " +
    "that rushes through the valley on its way south, waging a long " +
    "but ultimately futile battle with the water erosion.\n");
}


void mt_item_valley_far ()
{
  add_item (({ "valley", "gorge", "canyon" }),
    "The steep valley was carved into the hard rock by the stream that runs down from the mountains.\n");
}


void mt_item_valley_near_east ()
{
  add_item (({ "valley", "gorge", "canyon" }),
    dg_embed_when_night ("Occasional wafts of cold air remind you of the depth of the valley to your east, otherwise invisible in the dark of night.") +
    dg_embed_when_not_night ("The gorge to your east is grand in its dimensions, stretching from south to north as far as eye can see. Few trees manage to cling to its sides, partially obscuring the silvery thread of a stream visible on the very bottom.") +
    "\n");
}


void mt_item_valley_near_west ()
{
  add_item (({ "valley", "gorge", "canyon" }),
    dg_embed_when_night ("Occasional wafts of cold air remind you of the depth of the valley to your west, otherwise invisible in the dark of night.") +
    dg_embed_when_not_night ("The gorge to your west is grand in its dimensions, stretching from south to north as far as eye can see. Few trees manage to cling to its sides, partially obscuring the silvery thread of a stream visible on the very bottom.") +
    "\n");
}


string mt_desc_valley_heart_north ()
{
  string sDesc;
  object oMe = this_player ();

  if (dg_is_night ()) sDesc =
    "The dark of night prevents you from seeing pretty much " +
    "anything that is not real close.";
  else
  {
    sDesc = "Far to your north, a large canyon opens up between the tall " +
            "ridges of the mountains.";

    switch (dg_get_stime_season ())
    {
      case "spring":
        sDesc += " Its sides are the bright green of spring, as the " +
                 "trees that line the slopes welcome the first warmth " +
                 "of sun.";
        break;
      case "summer":
        sDesc += " The sides of the canyon are the lush green of trees " +
                 "that hurry to catch whatever sun the short mountain " +
                 "summer provides.";
        break;
      case "autumn":
        sDesc += " Its sides are the colors of gold and brass, the many " +
                 "deciduous trees that protect the slopes from erosion " +
                 "preparing for the coming winter.";
        break;
      case "winter":
        sDesc += " The brownish slopes are decorated with green spots " +
                 "of conifers, sprinkled with bits of snow brought by " +
                 "the wind from the higher parts of the mountains.";
        break;
    }

    if (oMe->resolve_task (DG_DIFFICULTY_KNOWNAME_HARD, DG_SKILLS_KNOWNAME))
    {
      sDesc += " Dubbed the Heart Canyon, it feels calm and tranquil.";
    }
    else
    {
      sDesc += " The canyon feels calm and tranquil.";
    }
  }

  sDesc += "\n";
  return (sDesc);
}


void mt_item_valley_heart_north ()
{
  add_item (({ "valley", "gorge", "canyon" }), &mt_desc_valley_heart_north ());
}


//-------------------------------------------------------------------

