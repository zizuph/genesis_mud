/*
 * vale.c
 * By Skippern
 * 
 * Functions thats common for the Vale of Erech
 */
inherit "/d/Gondor/common/lib/area_room";

#include "../erech.h"
#include "/d/Gondor/defs.h"
#include <ss_types.h>

string          herbarea,
                *herbs;

public void
white_mountains()
{
    add_item(({"mountains", "white mountains", "White Mountains",
        "distant mountains", "towering mountains", "snow-capped peaks",
        "peaks", "towering white mountains", "towering White Mountains"}),
        "The White Mountains rise to the north, their snow-capped peaks "
        + "towering majestically over Erech.\n");
}


/*
 * Function name:    hill_items()
 * Description  :    Adds some items connected to the hill.
 */
public void
hill_items()
{
    add_item(({"ridge", "steep ridge"}), "A steep ridge rises from the "
        + "field to a plateau further up. At the end of the ridge lies "
        + "an unusual hill.\n");
    add_item(({"hill", "unusual hill", "strange hill"}), "This is an "
        + "unusual hill, somewhat rounded in shape with a large black "
        + "rock on top. The sides of the hill are tinted green.\n");
    add_item(({"rock", "large rock", "black rock", "large black rock",
        "plateau"}), "It is too far away to make out more detail from "
        + "here.\n");
    
}

/*
 * Function name:    time_sky()
 * Description  :    Returns the VBFC for examening the sky.
 */
public string
time_sky()
{
    string sky;
    object clock = find_object(CLOCK);
    string time = clock->query_time_of_day();

    switch(time)
    {
    case "night":
    case "early morning":
      sky = "Elbereth's clear, twinkling stars fill the sky.";
      break;
    case "morning":
      sky = "The sun is on its way up over Erech.";
      break;
    case "noon":
      sky = "The sun is almost at its peak on its way across the sky.";
      break;
    case "afternoon":
      sky = "The sun has passed its peak, and afternoon has set in.";
      break;
    case "evening":
      sky = "The sky is filled with the colours of sunset as the last " +
          "rays of the evening sun shine over the horizon.";
      break;
    }

    sky += "\n";

    return sky;
}

/*
 * Function name:    vale_items()
 * Description  :    Adds a list of standard items which is common
 *                   for the whole Vale of Erech.
 */
public void
vale_items()
{
    add_item(({"hill", "hills", "small hill", "small hills"}), "Small hills "
        + "lie around in every direction.\n");
    add_item( ({"mountain", "mountains", "large mountain", 
        "large mountains"}), "To the north large mountains "
        + "tower up into the sky. They are a light blue so pale it is "
        + "almost white, and are decked on top with snow.\n");
    add_item(({"snow"}), "Snow decks the large mountains to the north.\n");
    add_item("sky", &time_sky());
    add_item(({"muddy water", "water", "river"}), "The river flows "
        + "smoothly here.\n");
    add_item(({"mist"}), "Mist hangs low over the muddy water.\n");
    add_item(({"tree", "trees", "willow tree", "willow trees"}), "Willow "
        + "trees poke their heads above the dark muddy water.\n");
    add_item(({"ground", "damp ground"}), "The ground is damp.\n");

}

public void
add_item_field()
{
    add_item(({"field", "dark green field"}), "The field is dark green with "
        + "a few trees and bushes scattered across it.\n");
    add_item(({"tree", "trees", "bush", "bushes"}), "Bushes and trees "
        + "grow here and there in the field.\n");
}

/*
 * Function name:    path_items()
 * Description  :    Adds items connected to the paths.
 */
public void
path_items()
{
    add_item(({"path", "dusty path", "road", "dusty road"}), "You are on a "
        + "dusty road in Gondor, but you cannot see where it leads.\n");
}

/*
 * Function name:    field_items();
 * Description  :    Adds items connected to the fields.
 *
 */
public void
field_items()
{
    add_item(({"path", "tracks", "track"}), "There appear to be some "
        + "small tracks on the ground, but it is almost impossible to "
        + "figure out where they lead.\n");
    add_item_field();
    add_item(({"bush", "bushes", "thicket"}), "Some bushes of various " +
        "sizes are scattered across the field. A few are packed close " +
        "together, while others grow in solitude.\n");
    add_item(({"tree","trees"}), "The field is spotted with birch and oak " +
        "trees here and there.\n");
}


/*
 * Function name:    add_herbs(string herbarea)
 * Description  :    Adds herbs and items connected with herbs to the
 *                   room.
 * Arguments    :    herbarea: what type of herbs and items to be set.
 */
public void
add_herbs(string herbarea)
{
    switch (herbarea)
    {
    case "garden":
      herbs = HERB_MASTER->query_herbs( ({ "garden", "fruit" }) );
      herbs = ({ one_of_list(herbs), one_of_list(herbs), one_of_list(herbs) });
      set_up_herbs(herbs, ({ "ground", "garden", "trees" }) );

      if (!item_id("trees"))
        add_item("trees", "The trees are fresh and green, and some of their " +
		 "branches are laden with fruit.\n");
      break;
    case "swamp":
        /*
	 * See under default for info.
	 */
      herbs = HERB_MASTER->query_herbs( ({ "swamp" }) );
      herbs = ({ one_of_list(herbs), one_of_list(herbs), one_of_list(herbs) });
      set_up_herbs(herbs, ({ "ground", "swamp" }) );

      /*
       * Adds swamp items for rooms with herbs.
       */
      if (!item_id("dirt"))
	  add_item( ({"dirt", "dirt on ground", "dirt on the ground"}), 
	      "The dirt is dark and wet, with the texture of clay.\n");
      break;
    case "yard":
      herbs = HERB_MASTER->query_herbs( ({ "meadow", "moderate" }) );
      herbs = ({ one_of_list(herbs), one_of_list(herbs), one_of_list(herbs) });
      set_up_herbs(herbs, ({ "ground", "yard" }) );

      if (!item_id("yard"))
        add_item("yard", "Hens run across the yard and around your feet, " +
            "kicking up puffs of dust. Along the edges of the yard you can " +
            "see lines of grass and flowers.\n");
      break;
    case "field":
      herbs = HERB_MASTER->query_herbs( ({ "meadow" }) );
      herbs = ({ one_of_list(herbs), one_of_list(herbs), one_of_list(herbs) });
      set_up_herbs(herbs, ({ "ground", "field", "furrow" }) );

      break;
    default:
        /*
	 * Standard setup for herb generating.
	 * HERB_MASTER referes to what lists of herbs should be avalable.
	 * It is set up to give tree random herbs from the active lists.
	 * Second argument in set_up_herbs() is extra verbs on where to search.
	 *   Standard verb is 'here'.
	 */
      herbs = HERB_MASTER->query_herbs( ({ "plains", "middle earth"}) );
      herbs = ({ one_of_list(herbs), one_of_list(herbs), one_of_list(herbs) });
      set_up_herbs(herbs, ({ "ground", "field" }) );
    
      /*
       * Adds std items for rooms with herbs.
       */
      if (!item_id("ground"))
	  add_item("ground", "The ground is overgrown with thick grass " +
	      "so much that you cannot see an inch of dirt beneath.\n");
      if (!item_id("dirt"))
	  add_item( ({"dirt", "dirt on ground", "dirt on the ground"}), 
	      "The dirt looks rich and fertile, perfect for herbs " +
	       "and grasses to thrive.\n");
      break;
    }
}

/*
 * Function name:    blocked_river()
 * Description  :    Blockes the path.
 * Returns      :    1.
 */
int
blocked_river()
{
    write("The river is too treacherous to cross here.\n");
    return 1;
}

/*
 * Function name:    blocked_path()
 * Description  :    Blockes the path.
 * Return       :    1.
 */
int
blocked_path()
{
    write("It is too difficult to continue in that direction.\n");
    return 1;
}

int to_road() { return 0; }
int on_field() { return 0; }
int to_field() { return 0; }

int
river_pass()
{
    int swim = this_player()->query_skill(SS_SWIM);
    if (swim < 10)
    {
	write("As you try to cross the river, you are washed back by the " +
	    "current.\n");
	return 1;
    }
    write("You swim across the river.\n");
    return 0;
}
