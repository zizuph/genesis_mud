/*
 * Inner Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>

inherit TEMPLE_ROOM_BASE;

// Defines
#define ROUNDABOUT  "/d/Calia/mountain/road/road19"
#define THALASSIA   "/d/Calia/sea/thalassia/obelisk"
#define WORSHIPPERS "/d/Calia/guilds/elementalists/temple/old_entrance"
#define CALIANS     "/d/Calia/mountain/croad/croad27"
#define WATERFALL   "/d/Calia/argos/nwterr/rooms/wfcave"
#define HE   TP->query_pronoun()
#define HIS  TP->query_possessive()
#define HIM  TP->query_objective()

// Prototypes
int destination = 1;

public void
create_temple_room()
{
    set_short("Elemental Temple Pool Room");                   
    set_long("This room is part of the third and innermost circle "
             + "of the Elemental Temple. The circular wall surrounding this "
             + "tall chamber is made from grey stone and pure crystalline. "
             + "Looking up, you see that the walls reach high up and form a "
             + "vast dome. Just underneath the domed area you can see small "
             + "windows that let in a small amount of light. On the inner "
             + "side of this room, you see the shrouded crystalline walls "
             + "that make up the inner sanctum of the Temple. At the base "
             + "of the wall is a semi-circular reflective pool.\n\n");

    try_item( ({ "wall", "walls" }),
              "Which wall? The circular wall or the shrouded crystalline wall?\n");

    try_item( ({ "circular wall" }),
              "The circular wall of the Inner Circle is hewn from a grey rock "
              + "material, with crystalline veins tightening the structure and "
              + "covering the surface of the rock wall. The surface is very "
              + "smooth to the touch and you can see your own partial reflection "
              + "upon the grey surface. The wall continues all the way up to "
              + "form a massive dome.\n");
    try_item( ({ "shrouded wall", "shrouded crystalline wall", "crystalline wall" }),
              "The shrouded crystalline wall on the northern part of the statue room "
              + "doesn't have the typical clear radiance of crystalline. Instead, the "
              + "material is shrouded, making it impossible to view the inner sanctum "
              + "of the Temple.\n");

    try_item( ({ "dome", "massive dome", "ceiling" }),
              "A dome of massive proportions looms over you, covering the entire Inner "
              + "Circle, which includes the inner sanctum. The dome consists of countless "
              + "glass and crystalline pieces in every possible color of the rainbow. "
              + "When light shines through from above, the entire Inner Circle is bathed "
              + "in a formidable mosaic that coalesces into an eternal dance of colours.\n");

    try_item( ({ "windows", "small windows", "window", "small window", "mosaic" }),
              "The small windows sit beneath the beginning of the massive dome. A small "
              + "amount of light streams through them, hitting the dome and creating "
              + "a beautiful mosaic that coalesces into an eternal dance of colours.\n");
     
    try_item( ({ "floor", "ground", }),
        "The floor beneath you is made of pure shiny crystalline material. "
      + "You can see a faint reflection of yourself among the rainbow colors "
      + "of the refracted ambient light.\n");
    
    try_item( ({ "crystalline", "webbing", "crystalline webbing",
        "green crystalline webbing", "coating", "crystalline coating" }),
        "As in many other parts of the temple, crystalline is ever present "
      + "here. It forms the floor as well as the veins and coating on the "
      + "walls.\n");

    try_item( ({ "inner sanctum", "sanctum" }),
              "The inner sanctum of the Elemental Temple is the central location and "
              + "most sacred of places in this Temple. The base of the circular room "
              + "is made from a shadowy shrouded crystalline that prevents an "
              + "observer from seeing the activities inside.\n");

    try_item( ({ "pool", "reflective pool", "semi-circular pool", "semi-circular reflective pool",
                    "bottom", "pool bottom", "water", "base", "wall base" }),
              "The semicular reflective pool does not look very deep, as you can see the "
              + "bottom pretty easily. The water appears to be extremely calm. Looking "
              + "into the pool you see a reflection of your own face, but the "
              + "surroundings are not this chamber! "+
              "@@current_destination@@ You could enter the pool if "+
              "you wished, or ripple it to blur the surroundings seen within it.\n");
    
    try_item( ({"button","small button"}),"You notice a small button underneath the "+
        "outer ledge of the reflective pool. You might be able to press it.\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "inner1", "west");
    add_exit(ELEMENTALIST_TEMPLE + "inner2", "east"); 
    add_exit(ELEMENTALIST_TEMPLE + "ritual", "south");
    add_exit(ELEMENTALIST_TEMPLE + "middle2", "north");
}

string
current_destination()
{
    string current_destination;

    switch (destination)
    {
        case 1:
            current_destination = "The surroundings appear to be at the roundabout ";
            current_destination += "some distance away from here and looks as ";
            current_destination += "though you are looking into this same pool ";
            current_destination += "only from that location.";
            break;
        case 2:
            current_destination = "The surroundings appear to be at the obelisk ";
            current_destination += "in the Ancient City of Thalassia and looks as ";
            current_destination += "though you are looking into this same pool ";
            current_destination += "only from that location.";
            break;
        case 3:
            current_destination = "The surroundings appear to be at the archway ";
            current_destination += "outside of the Elemental Worshippers temple ";
            current_destination += "and looks as though you are looking into this ";
            current_destination += "same pool only from that location.";
            break;
        case 4:
            current_destination = "The surroundings appear to be at the crystal ";
            current_destination += "palace of the Calian Warriors ";
            current_destination += "and looks as though you are looking into this ";
            current_destination += "same pool only from that location.";
            break;
        default:
            current_destination = "The surroundings appear to be at the cavern behind ";
            current_destination += "the waterfall in the mountains northwest of the ";
            current_destination += "city of Argos and looks as though you are looking ";
            current_destination += "into this same pool only from that location.";
            break;
    }
    return current_destination;
}

int
do_enter(string str)
{
    if (str != "pool" && str != "the pool")
    {
        notify_fail("Enter what? The pool? <enter pool>\n");
        return 0;
    }

    write("You step into the crystal pool and stand in the centre.\n"+
        "You feel yourself sinking into the pool, though you do not "+
        "feel you are getting wet at all. As you sink to just below "+
        "your eyes, you close them.\nWhen you open your eyes you find "+
        "yourself elsewhere.\n");
    say(QCTNAME(TP)+" steps into the crystal pool and stands in the "+
        "centre. "+capitalize(HE)+" sinks into the pool, closing "+
        HIS+" eyes just before sinking totally from sight, disappearing "+
        "altogether.\n");
    GUILD_MANAGER->subtract_guild_conduit(25);
    switch (destination)
    {
        case 1:
            TP->move_living("M",ROUNDABOUT);
            break;
        case 2:
            TP->move_living("M",THALASSIA);
            break;
        case 3:
            TP->move_living("M",WORSHIPPERS);
            break;
        case 4:
            TP->move_living("M",CALIANS);
            break;
        default:
            TP->move_living("M",WATERFALL);
            break;
    }
    
    tell_room(environment(TP),"A small shadow appears on the ground.\nThe "+
        "shadow begins to grow, elongating into a humanoid type shape. "+
        "The shadow then begins to rise up off of the ground, gaining "+
        "mass and solidifying as it does so. It forms arms, legs, a torso, "+
        "and finally a head.\nIn the blink of an eye, "+QTNAME(TP)+" is "+
        "standing there and the shadow is gone.\n",TP);
    return 1;
}

int
do_ripple(string str)
{
    if (!str)
        return 0;
    if (parse_command(str, ({}),"[the] 'pool'"))
    {
        write("You place your finger into the pool, sending ripples across "+
            "the surface of it, and changing the surroundings viewed in it.\n");
        say(QCTNAME(TP)+" places "+TP->query_possessive()+" finger into the "+
            "pool, sending ripples across the surface of it.\n");
        destination += 1;
        if (destination >= 6)
            destination = 1;
        return 1;
    }
    return 0;
}

int
do_press(string str)
{
	int taskone, tasktwo, taskthree, taskfour;
	
	if (!str)
        return 0;
	
	if (parse_command(str, ({}),"[the] [small] 'button'"))
    {
		// If they aren't a Seeker, nothing will happen.
		if (!(GUILD_MANAGER->query_is_seeker(TP)))
		{
			write("Nothing happens.\n");
	        return 1;
	    }
	    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
	    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
	    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
	    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
	    
	    // If they haven't been assigned task one, nothing will happen.
	    if (!taskone)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task two, nothing will happen.
	    if (!tasktwo)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task three, nothing will happen.
	    if (!taskthree)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task four, nothing will happen.
	    if (!taskfour)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they've already completed a further part of task four, nothing will happen.
	    if (taskfour > 1)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // They are indeed a Seeker and have been assigned task four and have not
	    // yet completed it.
	    GUILD_MANAGER->set_can_do_wor_task_four(TP, 2);
	    write("When nobody is watching, you quickly press the button. An image "+
	        "of a small lever quickly fills your mind. You notice the lever is "+
	        "on a wooden beam in a room with some mats on the floor. You feel "+
	        "compelled to find this lever.\n");
	    return 1; 
	} 
	return 0;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_ripple,"ripple");
    add_action(do_press,"press");
}

