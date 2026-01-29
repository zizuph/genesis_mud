// file name:	/d/Avenir/common/village/pale/base.c
// creator(s):	Lilith, Lucius
// revisions: 	Lucius Oct 2008
// purpose:          
// note:         Cope this file and re-name for each pale.  
//               The more frequent add_items should be placed here.
//               Change "pale" to the area name, such as merc, prax, emb.
// bug(s):           
// to-do:            
#pragma strict_types

/* Inherit the standard room object */
inherit "/std/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/* Include the local area defines, etc */
#include "../village.h"


/* Prototypes */
/* These are the add_items and add_cmd_items for 
 * (see below)
 */
public string do_wash(string);
public string do_drink(string);
static void add_cobbles(void);
static void add_source(void);
static void add_hedge(void);
static void add_fount(void);

void add_exit_views();  /* Adds directional exit views in the room files */


/*
 * Function name: create_pale_room
 * Description:   This function should be called to create rooms.
 */
static void
create_pale_room(void)	{ }

/*
 * Function name: reset_pale_room
 * Description:   This function should be called to reset pale rooms.
 */
static void
reset_pale_room(void)	{ reset_room(); }

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */
private nomask void
create_domain_room(void)
{
    setuid();
    seteuid(getuid());

   //set_area("this is for using the placer module");

    /* If an add_item will be in every room, add it here */
    add_source();
    
    add_item(({"air", "wind", "breeze", "scent", "scents"}),
	"You cannot see it, but perhaps you could use your sense of smell.\n");

    /* There is light in this area (see ~Avenir/common/common.h 
     * for this define and the one following) */
    LIGHT;

    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside', so no sunlight, etc. */
    IN;

    add_prop(ROOM_I_HIDE, 0);

    //Change the "pale" to whatever the district name is.
    create_pale_room();
	reset_pale_room();
}

public void
hook_smelled(string str)
{
    switch(str)
    {
    case "scent": case "scents":
    case "flower": case "flowers":
    case "air": case "wind": case "breeze":
	write("The warm air is perfumed with a variety of scents, "+
	    "all of them pleasant.\n");
	break;
    }
}

/* These are the add_items and add_cmd_items for the village merchs.
 * (Those used more than once in the area). If you want to add some
 * scultpures or ornamental bushes, inherit outside_decor.c
 */
static void
add_cobbles(void)
{

    add_item(({"cobbles", "cobblestones", "cobblestone"}),
        "These are rounded cobblestones made of yellow quartz. "+
        "The flecks of feldspar and other minerals in the unfinished "+
        "surfaces of the cobbles sparkle in the light of the "+
        "Source.\n");
}

static void 
add_source(void)
{
    /* Default in every room */
    add_item(({"source", "light", "illumination", "glow"}),
    "The yellow-white glow emanates from the ceiling of "+
    "this great cavern.\n");
}

static void
add_hedge(void)
{
    add_item(({"hedge","hedges","bush","bushes","ribbon"}),
	"The hedges serve both as ornamentation and barriers. "+
	"They are composed of bushes with delicate, variegated "+
	"leaves, grown closely together and to an impressive "+
	"height. These hedges have been groomed with such "+
	"precision as to present a flawless, flowing ribbon of "+
	"green that is very pleasing to the eye.\n");
}

public string
do_wash(string str)
{
    write("Wow that water is very cold!\nYou do a quick wash-up.\n");
	say(QCTNAME(TP)+" quickly washes up at the fountain.\n");
	return "";
}
	
public string 
do_drink(string str)
{
    int dr;

    dr = TP->query_prop(LIVE_I_MAX_DRINK) / 10;
    if (!dr) dr = 200;
	
    if (!TP->drink_soft(dr))
    {
        write("The water is too much for you.\n");
        return "";
    }

    write("You sip from the fountain with cupped hands.\n"+
        "The water is cold and sweet with minerals.\n");
    say(QCTNAME(TP)+" uses "+ TP->query_possessive() +" hands "+
        "to sip water from the fountain.\n");
    return "";		
}

static void
add_fount(void)
{
    add_item(({"fountain", "copper fountain", "clepsydra"}),
	"At the center of this district, a large, copper "+
	"clepsydra stands tall. Its time-telling waterworks doubles "+
	"as a communal fountain for the denizens of this area.\n");
	room_add_object("/d/Avenir/common/obj/clepsydra");
    add_cmd_item(({"in water", "in pool", "in fountain"}),
	    ({ "wash", "wash up", "clean", "bathe" }), do_wash);
    add_cmd_item(({"water", "pool", "fountain", "spring" }),
	    ({ "drink", "sip" }), do_drink);

}



public string
see_nearby(void)
{
    object room, *obs = ({});
    int idx, size = sizeof(room_exits);

    for(idx = 0; idx < size; idx += 3)
    {
	int ix, sz = sizeof(non_obvious_exits);

	if (IN_ARRAY(room_exits[idx + 1], ({"in","out","up","down"})))
	    continue;

	ix = (idx / 3);
	/* Check if exit is non-obvious. */
	if (sz > ix)
	{
	    if (non_obvious_exits[ix])
		continue;
	}

	catch(room_exits[idx]->teleledningsanka());
	if (objectp(room = find_object(room_exits[idx])))
	    obs += all_inventory(room);
    }

    if (!sizeof(obs = filter(obs, living)))
	return "";

    return " In the surroundings nearby, you see "+
	COMPOSITE_LIVE(obs) +".";
}

/*
 * Mask this to print a message for a non-exit view.
 */
static string
view_static(string str)
{
    return "You don't see anything of interest to the "+ str +".\n";
}

/*
 * Dynamic direction views.
 */
static string
view_nearby(string str)
{
    mixed room;
    object *obs;
    int idx = member_array(str, room_exits);

    if (!strlen(str))
	return "Error!";

    /* No exit in that direction. */
    if (idx == -1)
	return view_static(str);

    room = room_exits[idx - 1];
    catch(room->teleledningsanka());

    /* Did the room load? */
    if (!objectp(room = find_object(room)))
    {
	return "You have difficulty making out what is to "+
	"the "+ str +".\n";
    }

    obs = filter(all_inventory(room), living);
    str = "Off to the "+ str +" is "+ (room->short()) +".\n";

    if (sizeof(obs))
	str += "You can see "+ COMPOSITE_LIVE(obs) +" in that direction.\n";
    else
	str += "It doesn't appear that anyone is there right now.\n";

    return str;
}

/*
 * Auto adds directional view (ex. "exa north, exa south, etc")
 * To use, just do add_exit_views(); in the create_xxx_room of the
 *   room file.
 */
static void
add_exit_views(void)
{
    int idx, size = sizeof(room_exits);

    for(idx = 1; idx < size; idx += 3)
    {
	int ix, sz = sizeof(non_obvious_exits);

	if (IN_ARRAY(room_exits[idx], ({"in","out","up","down"})))
	    continue;

	ix = ((idx - 1) / 3);
	/* Check if exit is non-obvious. */
	if (sz > ix)
	{
	    if (non_obvious_exits[ix])
		continue;
	}

	add_item(({ room_exits[idx] }),
	    &view_nearby(room_exits[idx]));
    }
}

/*
 * Function name: exa_window
 * Description  : This lets people see the outside room
 *                from a window.
 * Usage: In the create_room do:
 * 	add_item( ({ "east windows", "east facing windows", "east window"}), 
 *  "@@exa_window|You look through the window.\n|" + OUTPOST +"fort2@@");
 *
 */
#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())
public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
          ".\n");

    if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
          ".\n");

    return "";
} 

	

/* Start the room tells as soon as someone enters the room */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
}
