/*
 * /d/Gondor/rohan/edoras/rooms/boffice2.c
 *
 * Modification log:
 * 4-Dec-1997, Gnadnar: General revision.
 * 8-Okt-2008, Eowul: Updated remove_deleted_player to use a copy of the enemy
 *                    array, as the remove_enemy function alters the array while
 *                    it's used in the for loop.
 * 15-Nov-2009, Eowul: Altered enemy list to remove players after some time
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define EDORAS_SAVE   (EDORAS_DIR + "misc/edoras_save")
#define DELETE_TIME   (86400 * 90)

public void remove_enemy(mixed k);
public void	create_gondor();
private void	remove_deleted_players();
public void	reset_room();
public string	read_map();
static object	Marshal;
// string *Enemies = ({ });
mapping enemy_list = ([ ]);

/*
 * Function name:	remove_deleted_players
 * Description	:	Remove players from enemy list who are non-existant
 */
private void
remove_deleted_players()
{
    int i, sz;

    string *enemies_copy = m_indices(enemy_list);
    for (i = 0, sz = sizeof(enemies_copy); i < sz; i++)
    {
      if (!(SECURITY->exist_player(enemies_copy[i])))
        {
            log_file("edoras", ctime(time()) + ": " 
               + "Deleted non-existant player from enemy list " 
               + enemies_copy[i] + ".\n");
               
            remove_enemy(enemies_copy[i]);
        }
    }
}

/*
 * Function name: remove_players_after_delete_time
 * Description  : Purge the enemy list after their delete time expired
 */
private void
remove_players_after_delete_time()
{
    mapping *delete_players = ({ });
    
    foreach(string name, int kill_time : enemy_list) {
        if(kill_time + DELETE_TIME < time()) {
            delete_players += ({ name });
        }
    }
    
    foreach(string name : delete_players) {
        log_file("edoras", ctime(time()) + ": Removed "
            + name + " from enemy list.\n");
        remove_enemy(name);
    }
}

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("the office of the Captain of the King's Eored");
    set_long(
	"The office of Elfhelm the Marshal, Captain of the King's "+
	"Eored of the riders of Rohan, is rather spartan in its "+
	"furnishings. Save for the map on the northern wall, "+
	"there is nothing in the way of decoration. "+
	"A wooden door leads east into the barracks.\n");

    add_item(({"office","room"}), long);
    add_item( ({"furnishings","furniture"}), 
	"A desk, an equipment rack and a simple camp-bed comprise "+
	"the entire furnishings of the office.\n");

    add_item(({"wooden frame","frame","canvas","bed","camp-bed",
	"camp bed"}), 
	"The bed is just a wooden frame spanned with canvas and "+
    	"covered with a blanket.\n");
    add_item(({"wool blanket","blanket"}), 
	"The wool blanket is rough, but probably very warm.");
    add_item(({"wooden desk","desk"}), 
	"The desk is plain wood, unadorned by paint or carvings, "+
	"with a scarred surface and a single drawer.\n");
    add_item(({"scarred surface","desk surface","surface of desk",
	"surface"}), 
	"The surface of the desk is scratched and scarred. "+
	"It clearly gets a lot of use.\n");
    add_item(({"desk drawer","drawer"}), 
	"The desk drawer is locked.\n");
    add_item(({"slab","slabs","stone","stones","stone slab","stone slabs",
	"floor","ground"}), 
    	"The floor is made from large stone slabs.  It looks a bit "+
	"worn down.\n");
    add_item(({"wall","walls"}), 
	"The walls are unadorned bare stone, except for the map "+
	"on the northern wall.\n");
    add_item(({"north wall", "northern wall"}), 
	"A large map covers much of the northern wall.\n");
    add_item(({"stone ceiling","ceiling"}), 
	"The ceiling is just bare stone.\n");
    add_item(({"rack","equipment rack"}), 
	"The equipment rack is empty.\n");

    add_item("map", read_map);
    add_cmd_item("map", "read", read_map);

    add_cmd_item( ({"desk drawer", "drawer", "desk" }),
	({ "open", "unlock" }),
	"The desk drawer is locked, and you don't seem to have its key.\n");


    clone_object(EDORAS_DIR + "rooms/off2door")->move(TO);
    add_exit(EDORAS_DIR + "rooms/bhallway", "east", 0, 1, 1);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    FIX_EUID
    restore_object(EDORAS_SAVE);
    remove_deleted_players();
    remove_players_after_delete_time();
    reset_room();
}


/*
 * Function name:	reset_room
 * Description	:	clone up the marshal
 */
public void
reset_room()
{
    Marshal = clone_npc(Marshal, EDORAS_DIR + "npc/elfhelm");
}



/* Function name:	read_map
 * Description	:	describe the map
 * Returns	:	string -- the map description
 */
public string
read_map()
{
    return (
"			                 			       \n"+
"		-=-=-=- THE MARK OF ROHAN -=-=-=-		       \n"+
"			                 			       \n"+
"			                 			       \n"+
"^^^^^^^^#############################      **************    **       \n"+
"  ^^^^^^##############################****** LIMLIGHT   *******  ***  \n"+
"  ^^^^^^^#############################                        **** ** \n"+
"  ^^^^^################################                        **   **\n"+
" ^^^^^####### FANGORN #################                      ANDUIN **\n"+
"^^ *^^###############################             THE WOLD         ** \n"+
"^^+*^^^############################                               **  \n"+
"^^_*^^#########################*                                 **   \n"+
"^^_*ISEN                       ***                                **  \n"+
"^^_*       DEEPING STREAM        **                        EMYN    ** \n"+
"___=___          *******************          EAST         MUIL HH ** \n"+
"****  ____********        WEST     *                           HHH**  \n"+
"  ^^    *___              EMNET    *            EMNET          HH**   \n"+
"  ^^^^^*+  ___  WESTFOLD           *                            H**   \n"+
"  ^^^^^^^^^  ____        SNOWBOURN **                         *****   \n"+
"   ^^^^^^^^^^^  ____   *=*************                    ***** ****  \n"+
"  ^^^^^^^^^^^^^^^^^____=____         *****  ENTWASH     ***    ** **  \n"+
"  ^^^^ WHITE ^^^^^^^^^^*_  _____         *****         ** **********  \n"+
"   ^^^^^^^^ MOUNTAINS ^*+^^    _____         ************************ \n"+
" ^^^^^^  ^^^^^^^^^^^^^^* ^^^^^^    _____ EASTFOLD    * *****       ** \n"+
" ^^^^    ^^^^^ ^^ ^^^^^ EDORAS ^^^^^^^^______       *MERING********** \n"+
"  ^^^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^_____*  STREAM       ** \n"+
"                   ^^  ^^^^^^^^^^^^^^^^^^^^^^^^^  *_____     GONDOR** \n"+
"			                 			       \n");
}

public void
add_enemy(mixed k, string which)
{
    string      name;
    if (objectp(k))
    {
        name = k->query_name();
    }
    else if (stringp(k) &&
             strlen(k))
    {
        name = CAP(k);
    }
    
    if (!strlen(name)) return;
    
    enemy_list[name] = time();
    log_file("edoras",
        ctime(time()) + ": " + name + " killed " + which + ".\n");
    
    FIX_EUID
    save_object(EDORAS_SAVE);
} /* add_enemy */

/*
 * Function name:       query_enemy
 * Description  :       did this person kill in Edoras?
 * Arguments    :       mixed k -- killer name or object
 * Returns      :       int -- 1 if killer, 0 if not
 */
public int
query_enemy(mixed k)
{
    if (objectp(k)) k = k->query_name();   
    return (member_array(CAP(k), m_indices(enemy_list)) != -1);
} /* query_enemy */


/*
 * Function name:       remove_enemy
 * Description  :       clear someone from enemy list
 * Arguments    :       mixed k -- killer name or object
 */
public void
remove_enemy(mixed k)
{
    if (objectp(k)) k = k->query_name();
    m_delkey(enemy_list, k);
    FIX_EUID
    save_object(EDORAS_SAVE);
} /* remove_enemy */


