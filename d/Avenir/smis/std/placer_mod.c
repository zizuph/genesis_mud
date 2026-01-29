// file name:        /d/Avenir/smis/std/placer_mod.c
// creator(s):       Denis, May'96
// revision history: Denis, Nov'96: Made possible to clone more than one
//				    object and more than one npc per room.
// purpose:          Inheritable module, which takes care of various
//		     object cloning/resetting.
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include "../smis.h"
# include <macros.h>
inherit SMIS_MODULE;

static private mapping	gObjects_to_clone,
			gNpcs_to_clone,
			gRemote_commands,

			gObjects_cloned,
			gNpcs_cloned;

static private int	short_alarm,
			long_alarm,
			notifications_autoset;

void
create_placer()
{
}

nomask
void create_module()
{
    object *rooms;

    gObjects_to_clone = ([ ]);
    gNpcs_to_clone = ([ ]);
    gRemote_commands = ([ ]);
    gObjects_cloned = ([ ]);
    gNpcs_cloned = ([ ]);

    set_module_types(0);

    enable_module_reset();
    notifications_autoset = 1;

    create_placer();

    rooms = m_indexes(gNpcs_to_clone);
    rooms = (m_indexes(gObjects_to_clone) - rooms) + rooms;

    if (notifications_autoset)
        set_create_notification((internal_query_create_notification() - rooms) +
				rooms);

    if (query_module_types())
        set_module_types((query_module_types()-({ "placer" }))+ ({ "placer" }));
    else
	set_module_types(({ "placer" }));
}

/*
 * Function name: set_location_npc
 * Description:   Sets up cloning npc in room 'location'. One such npc per room.
 * Arguments:     
 */
void
set_location_npc(string location, string filename)
{
    gNpcs_to_clone[location] = filename;
}

/*
 * Function name: set_location_npcs
 * Description:   Sets up cloning npcs in room 'location'.
 * Arguments:     
 */
void
set_location_npcs(string location, string *filenames)
{
    gNpcs_to_clone[location] = filenames;
}

/*
 * Function name: set_location_object
 * Description:   
 * Arguments:     
 */
void
set_location_object(string location, string filename)
{
    gObjects_to_clone[location] = filename;
}

/*
 * Function name: set_location_objects
 * Description:   
 * Arguments:     
 */
void
set_location_objects(string location, string *filenames)
{
    gObjects_to_clone[location] = filenames;
}

/*
 * Function name: set_remote_commands
 * Description:   Adds the command
 * Arguments:     
 * Returns:       
 */
void
set_location_commands(string location, string *values)
{
    gRemote_commands[location] = values;
}

static void
disable_notifications_autoset()
{
    notifications_autoset = 0;
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
public object
query_cloned_npc(string loc)
{
    return gNpcs_cloned[loc];
}

/*****************************************************************************
 * Clone upon creation and reset logic.
 */

object profile_clone_object(string file) { return clone_object(file); }

/*
 * Function name: place_objects
 * Description:   Places the apropriate object at location o_where.
 * Arguments:     o_where - the objectpointer to location;
 *		  s_where - the file name of location.
 */
void
place_objects(object o_where, string s_where)
{
    object ob;
    string *obs_to_clone;
    int i;

    if (pointerp(gObjects_to_clone[s_where]))
    {
	obs_to_clone = gObjects_to_clone[s_where];
	if (!sizeof(gObjects_cloned[s_where]))
	    gObjects_cloned[s_where] = allocate(sizeof(obs_to_clone));
	i = -1;
	while (++i < sizeof(obs_to_clone))
	{
	    ob = gObjects_cloned[s_where][i];

	    // Note that ob is checked twice in this if.
	    // Ob could have been removed in reset_placed_functions().
	    if ((ob && ob->reset_placed_functions()) ||
		(ob && environment(ob) == o_where))
	    {
		continue;
	    }
	    (ob = profile_clone_object(obs_to_clone[i]))->startup();
	    gObjects_cloned[s_where][i] = ob;
	    ob->move(o_where);
	}
    }
    else
    {
	ob = gObjects_cloned[s_where];

	// reset_placed_functions is supposed to remove the object
	// or do the reset stuff and return 1.
	// The object is also supposed to be where it should be cloned.

	// if the function returns 0, then a new instance of object
	// will be cloned.
	if ((ob && ob->reset_placed_functions()) ||
	    (ob && environment(ob) == o_where))
	{
	    return;
	}

	(ob = profile_clone_object(gObjects_to_clone[s_where]))->startup();
	gObjects_cloned[s_where] = ob;
	ob->move(o_where);
    }
}

/*
 * Function name: place_npcs
 * Description:   
 * Arguments:     
 */
void
place_npcs(object o_where, string s_where)
{
    object ob = gNpcs_cloned[s_where];
    string *obs_to_clone;
    object *just_cloned = ({ });
    int i;

    if (pointerp(gNpcs_to_clone[s_where]))
    {
	    obs_to_clone = gNpcs_to_clone[s_where];
	    if (!sizeof(gNpcs_cloned[s_where]))
	        gNpcs_cloned[s_where] = allocate(sizeof(obs_to_clone));
	    i = -1;
	    while (++i < sizeof(obs_to_clone))
	    {
    	    ob = gNpcs_cloned[s_where][i];

    	    if (ob)
	        {
		        ob->reset_placed_functions();
		        continue;
	        }

	        (ob = profile_clone_object(obs_to_clone[i]))->equip_me();
	        gNpcs_cloned[s_where][i] = ob;
	        ob->move(o_where, 1);
	        just_cloned += ({ ob });
	        just_cloned[sizeof(just_cloned) - 1]->arrive(({ just_cloned }));
	    }
    }
    else
    {
	    ob = gNpcs_cloned[s_where];

	    if (ob)
	    {
    	    ob->reset_placed_functions();
	        return;
	    }

	    (ob = profile_clone_object(gNpcs_to_clone[s_where]))->equip_me();
	    gNpcs_cloned[s_where] = ob;
	    ob->move(o_where, 1);
	    ob->arrive(({ ob }));
    }
}

/*
 * Function name: delayed_place_objects
 * Description:   Places objects in rooms with filenames listed
 *		  in room_file_names [recursively].
 * Arguments:     room_file_names - The list of filenames where to place the
 *				    objects.
 */
void
delayed_place_objects(string *room_file_names)
{
    int rooms_num;

    while (sizeof(room_file_names) &&
	  !find_object(room_file_names[0]))
	room_file_names -= ({ room_file_names[0] });

    rooms_num = sizeof(room_file_names);
    if (rooms_num)
    {
	place_objects(find_object(room_file_names[0]), room_file_names[0]);
	if (rooms_num - 1)
	    short_alarm = set_alarm(30.0, 0.0,
				    &delayed_place_objects(room_file_names - 
					          ({ room_file_names[0] })));
	else
	    short_alarm = 0;
    }
}

/*
 * Function name: delayed_place_npcs
 * Description:   
 * Arguments:     
 */
void
delayed_place_npcs(string *room_file_names)
{
    int rooms_num;

    long_alarm = 0;

    while (sizeof(room_file_names) &&
	   !find_object(room_file_names[0]))
	room_file_names -= ({ room_file_names[0] });

    rooms_num = sizeof(room_file_names);
    if (rooms_num)
    {
	place_npcs(find_object(room_file_names[0]), room_file_names[0]);
	if (rooms_num - 1)
	    short_alarm = set_alarm(30.0, 0.0,
				    &delayed_place_npcs(room_file_names - 
					          ({ room_file_names[0] })));
	else
	    short_alarm = 0;
    }
}

/*
 * Function name: notify_object_created
 * Description:   
 * Arguments:     
 */
public void
notify_object_created(object o_where, string s_where,
		      string area, string *obj_roles)
{
    ::notify_object_created(o_where, s_where, area, obj_roles);

    if (!query_module_enabled())
	return;

    if (gObjects_to_clone[s_where])
	place_objects(o_where, s_where);

    if (gNpcs_to_clone[s_where])
	place_npcs(o_where, s_where);

    if (gRemote_commands[s_where])
	o_where->add_remote_cmds(gRemote_commands[s_where]);
}

/*
 * Function name: reset_placer
 * Description:   
 */
void
reset_placer()
{
}

/*
 * Function name: reset_module
 * Description:   
 */
nomask void
reset_module()
{
    if (!query_module_enabled())
	return;

    reset_placer();

    delayed_place_objects(m_indexes(gObjects_to_clone));
    long_alarm = set_alarm(itof(30 * m_sizeof(gObjects_to_clone) + 30), 0.0,
	                   &delayed_place_npcs(m_indexes(gNpcs_to_clone)));
}

/*
 * Function name: restart_placer
 * Description:   
 */
static void
restart_placer()
{
}

/*
 * Function name: restart_place_location_commands
 * Description:   
 * Arguments:     where - The location to place the commands.
 */
static void
restart_place_location_commands(string where)
{
    object ob = find_object(where);

    if (ob)
	ob->add_remote_cmds(gRemote_commands[where]);
}

/*
 * Function name: restart_module
 * Description:   Clones the apropriate monsters/npcs and adds remote
 *		  commands to already loaded rooms.
 */
nomask static void
restart_module()
{
    restart_placer();
    reset_module();
    map(m_indexes(gRemote_commands), restart_place_location_commands);
}

/*
 * Function name: shutdown_placer
 * Description:   To be overrided to provide cleanup at module disabling/
 *		  unloading.
 */
static void
shutdown_placer()
{
}

/*
 * Function name: shutdown_module
 * Description:   Is called when one unloads or disables the module.
 *		  Removes cloned npcs/objects as well as remote commands from
 *		  loaded rooms.
 */
nomask static void
shutdown_module()
{
    shutdown_placer();
    (m_values(gNpcs_cloned) - ({ 0 }))->remove_placed_object();
    (m_values(gObjects_cloned) - ({ 0 }))->remove_placed_object();
    (map(m_indexes(gRemote_commands), find_object) - ({ 0 }))->
	remove_remote_cmds(MASTER);
    if (long_alarm)
	remove_alarm(long_alarm);
    if (short_alarm)
	remove_alarm(short_alarm);
}

static string
desc_placer()
{
    return "";
}

nomask static string
desc_module()
{
    return desc_placer();
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
