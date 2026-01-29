/*
 * Elemental Garden of Calia
 *
 * This room will contain the base elements that will be a part of
 * every room in the Elemental Garden outside the Elemental Temple
 * of the Elementalists guild.
 *
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include "../defs.h"

inherit ROOM_OBJECT;
inherit "/d/Calia/lib/try_item";
inherit "/d/Calia/lib/room_tell";
inherit "/d/Krynn/std/herbsearch";

#define ONE_OF(x)     ((x)[random(sizeof(x))])

// Prototypes
public void create_garden_room();
public void set_garden_health(int health);

// Global Variables
public int              Garden_health = 0; // should range from 0-100.
public string *         Herb_group1 = ({
    "/d/Krynn/common/herbs/raspberry",
    "/d/Krynn/common/herbs/cranberry",
    "/d/Krynn/common/herbs/blk_currant",
    "/d/Krynn/common/herbs/saskatoon",
    "/d/Kalad/common/herbs/blade",
    "/d/Kalad/common/herbs/lore",
    });
    
/*
 * Function:    create_room
 * Description: Set up defaults for the garden room
 */
public nomask void
create_room()
{
    // Put default properties here before calling create_garden_room
    // so that create_garden_room can override any defaults
    set_short("Inside a walled garden");
    set_long("@@describe_long"); 
               
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_ATTACK, "This garden is a peaceful place! There will "
        + "be no combat in the sanctity of this location.\n");
        
    // Call each room's create_garden_room
    create_garden_room();
    
    try_item( ({ "garden", "walled garden" }),
        "@@describe_garden");
    
    try_item( ({ "path" }),
        "@@describe_path");
   
    try_item( ({ "wall", "walls" }),
        "The walls of the garden are approximately 20 feet high. Bricks made "
      + "of a grey rock material are laid in interleaving fashion to make "
      + "the wall rather sturdy. Despite the height of the wall, sufficient "
      + "light reflects off the crystalline Temple, and gives the plants "
      + "here plenty to thrive.\n");
      
    try_item( ({ "flora", "plant life", "plants", "fauna" }),
        "The garden is full of flora and fauna.\n");
    
    try_item( ({ "ground" }),
        "The ground is mostly dirt right now. Someone has take the time to "
      + "carefully till the soil and it looks almost primed for seeds to be "
      + "planted.\n");
    
    try_item( ({ "tools", "gardening tools", "tool", "gardening tool",
        "trowels", "shovels", "scoops", "shears", "watering cans" }),
        "Various tools are carefully laid against the walls. Among them, you "
      + "see trowels, shovels, scoops, shears, and watering cans.\n");

    try_item( ({ "temple", "crystalline temple", "crystalline",
        "elemental temple" }),
        "This garden surrounds the domed crystalline Elemental Temple of "
      + "Calia. The Temple reflects an enormous amount of light and looks "
      + "quite beautiful with the array of dazzling colors that are "
      + "refracted.\n");

    try_item( ({ "ceiling" }),
        "You are outside! There is no ceiling here. You see above you "
      + "only the clear blue skies of Calia.\n");

    try_item( ({ "sky", "skies", "clear blue skies", "blue skies",
        "blue sky", "clear sky" }),
        "There is not a single cloud in the sky above. The sky is a "
      + "deeply rich blue. Occasionally, you see a bird swooping "
      + "lazily across the horizon.\n");
    
    enable_reset(200); // set the default reset interval to 45 minutes
    // By default, the garden room will start at a random point in the
    // health spectrum. Part of this implementation is poor laziness so that
    // we don't need to store the health values over Armageddon. The other
    // part is so that there introduces some randomness and the ability for
    // there be some semblence of life if no one is tending, and something
    // for people to do if it's constantly tended.
    set_garden_health(random(100));
    set_up_herbs( ({ONE_OF(Herb_group1), ONE_OF(Herb_group1),
        ONE_OF(Herb_group1), ONE_OF(Herb_group1) }), ({"here","garden",}), 2);
}

/*
 * Function:    create_garden_room
 * Description: This method should be masked and defined in each
 *              garden room to override defaults set in create_room
 */
public void
create_garden_room()
{
    // Define this in your own room
}

/*
 * Function:    reset_room
 * Description: We create a reset_room in all garden rooms so that
 *              the reset interval will activate.
 */
public void
reset_room()
{
    // Decrement the Garden_health variable. If this is decremented
    // an average of once every 45 minutes, it'll take approximately
    // 3 days to go from 100 to 0.
    Garden_health = max(0, Garden_health - 1);
    // In order for herbs to be reset, we need to reset the searched index
    set_searched(0);
}

/*
 * Function:    query_garden_health
 * Description: Returns the current health index of the garden.
 */
public int
query_garden_health()
{
    return Garden_health;
}

/*
 * Function:    set_garden_health
 * Description: Allows someone to set the health of the garden manually.
 *              Setting the garden health affects everything in the garden.
 */
public void
set_garden_health(int health)
{
    Garden_health = health;
}

/*
 * Function:    query_herb_search_bonus
 * Description: Depending on the health of the garden, it gets a herb search
 *              bonus so that experienced players can find more herbs.
 */
public int
query_herb_search_bonus()
{
    switch (Garden_health)
    {
    case 0..20:
        // A garden this untended actually gets a big penalty
        return -4;
        
    case 21..40:
        // A garden at this health receives a minor penalty
        return -2;
        
    case 41..60:
        // This garden is operating at normal capacity
        return 0;
    
    case 61..80:
        // This garden operates with a slight bonus
        return 2;
        
    case 81..100:
        // This garden operates with a major bonus (extra 2 herbs)
        return 4;
    }
    
    return 0;
}

/*
 * Function name: search_for_herb
 * Description:   The herbalist has searched the room, now let's see if and
 *                what he has found.
 * Arguments:     herbalist - The player searching for herbs
 *                herb_file - the file of the herb the player is looking for 
 *                            (optional)
 * Returns:       The message to write
 */
varargs string
search_for_herbs(object herbalist, string herb_file = 0)
{
    int original_searched = searched;
    // We adjust the searched variable based on the garden's health bonus
    searched = max(0, searched - query_herb_search_bonus());
    // Store the actual difference that we're applying before doing the actual search
    int difference = original_searched - searched;
    string result = ::search_for_herbs(herbalist, herb_file);
    // Return the difference back into the searched variable.
    searched += difference;
    
    return result;
}

/*
 * Function:    describe_long
 * Description: VBFC function to provide the long description
 */
public string
describe_long()
{
    string description = 
          "This is a part of the walled garden surrounding the crystalline "
        + "Elemental Temple of Calia. ";
            
    switch (Garden_health)
    {
    case 0..20:
        description += "You find yourself on an arid path winding through "
            + "the temple garden. The garden is dry and brown with a couple "
            + "droopy flowers. The fruits and vegetables look dried up "
            + "and shriveled, and you spot an herb struggling in the arid "
            + "soil.";
        break;
        
    case 21..40:
        description += "You find yourself on a very dry path winding through "
            + "the temple garden. Most of the garden is pale green and brown "
            + "with just a couple flowers blooming. You think the fruits and "
            + "vegetables may ripen soon. A single herb springs up from the "
            + "very dry soil, defying all odds.";
        break;
        
    case 41..60:
        description += "You find yourself on a dry winding path through the "
            + "temple garden. The plants here are green and brown, and there "
            + "are a few flowers blooming. The fruits and vegetables may ripen "
            + "shortly with care. A few herbs spring up from the slightly "
            + "dry soil.";
        break;
                
    case 61..80:
        description += "You find yourself on a clear path winding through "
            + "the temple garden. The plants in this garden are green and "
            + "healthy. Plenty of flowers are blooming, and the fruits and "
            + "vegetables are starting to ripen. A few herbs are springing "
            + "up from the dark well-tended soil.";
        break;
        
    case 81..100:
        description += "You find yourself on path winding through the "
            + "temple garden that is covered with overgrown plants. The "
            + "garden is full, lush, and teeming with life. The flowers "
            + "here are in full bloom aside fruits and vegetables that look "
            + "to be fully ripened. Many herbs spring up from the dark, rich, "
            + "life-giving soil.";
        break;
    }
    
    return description + "\n\n";
}

/*
 * Function:    describe_garden
 * Description: VBFC function to provide the health descriptions for the garden
 */
public string
describe_garden()
{
    string description = 
        "You are standing in the walled garden surrounding the crystalline "
      + "Elemental Temple of Calia. ";
    
    switch (Garden_health)
    {
    case 0..20:
        description += "The garden is in disrepair. Most everything is "
            + "dry and brown. This garden needs some serious tending.\n";
        break;
        
    case 21..40:
        description += "The flora in the garden are barely hanging onto "
            + "life. Most are brown and at best pale green. The garden "
            + "needs some tending.\n";
        break;
        
    case 41..60:
        description += "The garden is doing fairly well. For the most part, "
            + "most plants look to be surviving quite nicely, but there "
            + "are patches of brown. The garden could benefit from "
            + "some tending.\n";
        break;
                
    case 61..80:
        description += "The garden is vibrant, green, and healthy. The plants "
            + "here look like they've been well cared for. Even so, you "
            + "feel it could still benefit from some tending.\n";
        break;
        
    case 81..100:
        description += "The garden is teeming with life! Everything is "
            + "vibrant, green, and healthy. You cannot spot even one plant "
            + "that is not cared for. This garden probably doesn't need to "
            + "be tended.\n";
        break;
    }
    
    return description;
}

/*
 * Function:    describe_path
 * Description: VBFC function to provide the description of the path
 */
public string
describe_path()
{
    string description = "";

    switch (Garden_health)
    {
    case 0..20:
        description += "This path is wide enough for one person to walk "
            + "upon. The ground is parched and is in desperate need of "
            + "moisture. Each step upon it leads to more dust being "
            + "added to the air, making it difficult to breathe.\n";
        break;
        
    case 21..40:
        description += "This path is wide enough for one person to walk "
            + "upon. It is very dry on the path today. Every movement upon "
            + "it produces dust, making it somewhat difficult to enjoy "
            + "the fresh air.\n";
        break;
        
    case 41..60:
        description += "This path is wide enough to walk upon. It can get "
            + "pretty dusty here, especially with the dry path. As you "
            + "tread upon the path, you see a little bit of dust being "
            + "tossed into the air.\n";
        break;
                
    case 61..80:
        description += "This path is wide enough to walk upon. It is "
            + "sometimes dusty, but today it is barely damp. As a result "
            + "you hardly see any evidence of dust at all.\n";
        break;
        
    case 81..100:
        description += "This path is just wide enough for one person to walk "
            + "upon. It is sometimes dusty, but today it is slightly damp. As "
            + "a result, the air is absent of any dust at all.\n";
        break;
    }
    
    return description;
}

public int
tend_cmd(string str)
{
    if (!strlen(str) || str != "garden")
    {
        notify_fail("Tend what? The garden?\n");
        return 0;
    }
    
    if (query_garden_health() == 100)
    {
        notify_fail("You look around you in the garden and realize that "
            + "everything looks like it has been done already. There is "
            + "nothing for you to tend.\n");
        return 0;
    }
    setuid();
    seteuid(getuid());
    clone_object(ELEMENTALIST_OBJS + "tend_paralyze_object")->move(this_player(), 1);
    
    return 1;
}


public void
init()
{
    ::init();
        
    add_action("tend_cmd", "tend");
}

public void
notify_wizard_of_restricted_access()
{
    // Give a message to wizards that they can enter because they are
    // wizards, even though normally this should not be accessible.
    if (this_player()->query_wiz_level() > 0)
    {
        write("\n=== Only members of the Elementalists of Calia can enter. However, "
            + "since you are a wizard, you are allowed entry. ===\n\n");
    }
}

public int
cannot_see_restrict_resource_banned()
{
    if (!GUILD_MANAGER->query_is_punish_resource_banned(this_player()))
    {
        // Allow access if not resource banned
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Resource banned non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_restrict_resource_banned()
{
    if (!cannot_see_restrict_resource_banned())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement. You have been banned "
          + "by the Elemental Council to enter.\n");
    return 1;
} 

/*
 * Function: enter_inv
 * Description: block unwanted people from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    // Don't allow Temple banned people from entering.
    if (GUILD_MANAGER->query_is_punish_temple_banned(ob))
    {
    	if (!from)
    		from = ob->query_def_start();
        ob->move(from);
        ob->catch_msg("You've been banned from entering the "+
            "Elemental Temple!\n");
        return;
    }
}
