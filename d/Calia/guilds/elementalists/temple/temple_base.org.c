/*
 * Elemental Temple of Calia
 *
 * This room will contain the base elements that will be a part of
 * every room in the Elemental Temple that will house the Elementalists
 * guild. The guild will be composed of the Elemental Clerics, the
 * Elemental Worshippers, and the Elemental Seekers.
 *
 * Created by Petros, March 2010
 */

 /* TT comment removed some capital letters. Made a few descs more clear. 
  * Removed reference to East Calia (should be something the player figures
  * out through study - not inherent knowledge) Made it more clear that the 
  * outer wall is white marble. Changed the "you cant pass here desc and 
  * the you cant fight here desc" 
  */
  
 /*
  * Confirmed the coding of the room, touched up a small amount of spelling
  * and grammatical issues.
  *
  * Leia - February, 2016
  */
  
#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include "defs.h"

inherit ROOM_OBJECT;
inherit "/d/Calia/lib/try_item";
inherit "/d/Calia/lib/room_tell";

// Prototypes
public void create_temple_room();

/*
 * Function:    create_room
 * Description: Set up defaults for the temple room
 */
public nomask void
create_room()
{
    // Put default properties here before calling create_temple_room
    // so that create_temple_room can override any defaults
    set_short("Inside the Elemental Temple of Calia");
    set_long("You stand inside the Elemental Temple of Calia, an ornately "
        + "constructed building that houses those devoted to the service "
        + "of the Elementals. The walls are made from white marble, or grey stone "
		+ "while the foundation is made from crystalline. The vaulted ceiling is "
		+ "comprised of wood and supported by mighty columns.\n\n"); 
               
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_M_NO_ATTACK, "A thunderous voice echoes in your mind: "
        + "This Temple is a peaceful place! There will "
        + "be no violence in this divine sanctuary.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "A thunderous voice echoes in your mind: "
        + "This Temple is a peaceful place! There will "
        + "be no violence in this divine sanctuary.\n");

    // Call each room's create_temple_room
    create_temple_room();

    // Perform the try_item calls after the create_temple_room. This will
    // add all the undefined items.
    try_item( ({ "temple", "elementalist temple", "elemental temple",
                 "elemental temple of calia", "temple of calia" }),
                 "The Elemental Temple of Calia is a calming place where the "
               + "seekers, worshippers, and the clerics of the Elementals "
               + "find solace. The temple is made of a combination of "
               + "white marble, grey stone, shiny crystalline and petrified "
			   + "wood.\n");
                                  
    try_item( ({ "ground", "floor", "foundation", "crystalline foundation" }),
                 "The floor you stand upon is made of a pure shiny crystalline "
               + "material. You can see a faint reflection of yourself among "
               + "the rainbow colors of the refracted ambient light.\n");
    
    try_item( ({ "light", "ambient light", "refracted light", "colours" }),
                 "Light is reflected off of every crystalline surface in the "
               + "temple. Some of it is refracted by the material and creates "
               + "a beautiful display of rainbow colors that shift and "
               + "change as you move.\n");

    try_item( ({ "ceiling", "vaulted ceiling", "frames", "supporting frames",
                 "oak", "oak wood", "solid oak wood" }),
                 "The vaulted ceiling of the temple opens up the space greatly. "
               + "Angling upwards in an arch the ceiling forms a criss cross "
			   + "pattern of five supporting frames. The frames are made of solid "
			   + "oak wood. The parts in between the frames are inlaid with "
			   + "petrified wood and have been decorated with beautiful "
			   + "meticulously carved reliefs.\n");
            
    try_item( ({ "crystalline", "crystalline material", "shiny crystalline",
                 "shiny crystalline material" }),
                 "Much of the temple is made of a pure shiny crystalline "
               + "material. The entire floor and certain parts of the walls "
               + "seem to to be made of it. The crystalline is quite beautiful "
               + "and with even the most minimal of light, will shower upon "
               + "observers a dazzling rainbow display of colors from the "
               + "refracted light.\n");

    try_item( ({ "reliefs", "relief", "carvings", "carved reliefs",
                 "carved relief" }),
                 "The ceilings that house the reliefs are too high to make out "
               + "any significant detail about them. From afar, they seem to "
               + "tell a story of Creation and the involvement of the "
               + "Elementals therein. The reliefs are carved meticulously "
               + "and one can only imagine the amount of time and effort that "
               + "went into such artistic mastery.\n");

    try_item( ({ "columns", "marble columns", "marble", "white marble" }),
                 "The rich white marble from the quarries of Argos are a "
               + "stunning sight. It has been used quite heavily for all the "
               + "columns that lift the ceiling high above the ground. The "
               + "columns are smooth and cool to the touch, and brighten up "
               + "the surroundings greatly.\n");

    try_item( ({ "wood", "petrified wood" }),
                 "A dark wood has been used to lay the bulk of the vaulted "
               + "ceiling for the temple. The wood itself looks to be "
               + "petrified wood, and though it retains all the original "
               + "structure and detail of the wood, it is extremely hard "
               + "material. This could be petrified wood from East Calia.\n");

    try_item( ({ "wall", "walls", "grey rock", "rock", "stone", "inner wall", 
				"inner walls", "outer walls", "outer wall" }),
        "The outer walls are white marble while the inner ones are made up "
      +	"of a grey rock material similar to the wall surrounding the garden " 
	  + "outside. The walls have been polished to be extremely smooth to the "
      + "touch and you can even see your own partial reflection upon the grey "
      +	"surface.\n");
}

/*
 * Function:    create_temple_room
 * Description: This method should be masked and defined in each
 *              temple room to override defaults set in create_room
 */
public void
create_temple_room()
{
    // Define this in your own room
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
cannot_see_inner_circle()
{
    if (this_player()->query_guild_name_lay() == "Elemental Worshippers of Calia"
        || this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_lay() == "Elemental Seekers of Calia"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow seekers, worshippers and scop to enter the inner circle
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_inner_circle()
{
    if (!cannot_see_inner_circle())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }

    // Non-wizards cannot use these exits.
    write("Only those who follow the Elementals may pass here.\n");
    return 1;
}    

public int
cannot_see_middle_circle()
{
    if (this_player()->query_guild_name_lay() == "Elemental Worshippers of Calia"
        || this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_lay() == "Elemental Seekers of Calia"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow seekers, worshippers and scop to enter the middle circle
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_middle_circle()
{
    if (!cannot_see_middle_circle())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }

    // Non-wizards cannot use these exits.
    write("Only those who follow the Elementals may pass here.\n");
    return 1;    
}    

public int
cannot_see_start_locations()
{
    if (this_player()->query_guild_name_lay() == "Elemental Worshippers of Calia"
        || this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_lay() == "Elemental Seekers of Calia"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow seekers, worshippers and scop to enter the middle circle
        return 0;
    }

    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_start_locations()
{
    if (!cannot_see_start_locations())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    write("Only those who follow the Elementals may pass here.\n");
    return 1;
}

public int
cannot_see_worshipper_floor()
{
    if (this_player()->query_guild_name_lay() == "Elemental Worshippers of Calia"
        || this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_lay() == "Elemental Seekers of Calia"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow seekers, worshippers and scop to enter the worshipper floor
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_worshipper_floor()
{
    if (!cannot_see_worshipper_floor())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement. You get the sense that "
          + "you must be a servant of the Elementals to enter.\n");
    return 1;
}    

public int
cannot_see_cleric_floor()
{
	if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow scop/clerics to enter this floor
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_cleric_floor()
{
    if (!cannot_see_cleric_floor())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement. You get the sense that "
          + "you must be a Cleric of the Elementals to enter.\n");
    return 1;
}   

public int
cannot_see_restrict_seekers()
{
    if (this_player()->query_guild_name_lay() == "Elemental Worshippers of Calia"
        || this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow worshippers and scop/clerics to enter the floor, no seekers
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_restrict_seekers()
{
    if (!cannot_see_restrict_seekers())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement. You get the sense that "
          + "you must be a full servant of the Elementals to enter.\n");
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
  