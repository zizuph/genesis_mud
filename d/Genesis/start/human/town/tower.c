// /d/Genesis/start/human/town/tower.c

/* 
 * This place is now connected to the tower of realms and has support 
 * for adding new rooms to the tower (see the wizinfo when you stat it). 
 * Updated by Maniac, 18/12/96 
 */ 

#pragma save_binary
#pragma strict_types
#pragma no_inherit

inherit "/std/room";

#undef TOWER_BLOCKED

#include <stdproperties.h>
#include <std.h>

#include "../defs.h"
#include "tower.h"

#define AOE_OFFICE "/d/Genesis/ateam/aoe/office/aoe_office"
static object fix_board();
static string *max_offices = MAX_OFFICES; 
static string *floor_names = FLOOR_NAMES;

mapping domains = ([ ]); 

int
query_prevent_shadow()
{
    return 1;
}

void
create_room()
{
    object ob;

    set_short("In the tower of realms");

    set_long("This is the lobby of the Tower of Realms. The " +
       "floor and walls are made of polished marble, reflecting your " +
       "image as you look around in wonder. This is where the different " +
       "Domain Lieges have their information offices. On the floors above, " +
       "each domain has a room where information about that realm can be " +
       "obtained. Broad stairs lead up to the first floor of the tower. " +
       "The exit 'common' will take you to the common board.\n");

    add_item(({"floor", "ground" }),"Apart from being highly polished and very " +
                          "shiny, you see nothing special.\n"); 
    add_item(({"walls", "wall", "cieling" }),"Very shiny indeed.\n");
    add_item(({"stair" }),"Very shiny indeed.\n");
    add_item(({"lobby","room" }),"It's quite luxurious.\n");
    add_item(({"door" }),"It is a brown wooden door with a golden " +
                         "sign which says, Administration.\n");

    add_exit("/d/Sparkle/area/city/rooms/streets/center_g", "north");
    add_exit(AOE_OFFICE, "down");
    add_exit(TOWN_DIR + "common", "common");
    add_exit(TOWN_DIR + "admin", "south");
    add_exit(TOWN_DIR + "wizapp", "east");
    add_exit(TOWN_DIR + "commtower", "west", "@@nonewbie");
//    add_exit(TOWN_DIR + "immortal", "west", "@@immortal");
//    add_exit(TOWN_DIR + "basement", "down");
    add_exit(TOWN_DIR + "tfloor1", "up", "@@up"); 

    add_prop(ROOM_I_INSIDE, 1);
//    add_prop(ROOM_M_NO_ATTACK, "This is a room for writing, " +
//        "not fighting.\n");
//    add_prop(ROOM_M_NO_STEAL, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");    
    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");

    if (!(ob = fix_board()))
        write("Board could not be created");
    else
        add_my_desc("Next to the door is a bulletin board. " +
        "It is intended for notes of general interest and all topics of " +
        "general interest can be discussed on this board. However, as goes " +
        "for most boards, use courteous language and use your common " +
        "sense.\n");

    restore_object(TOWER_SAVE); 
    reset_room();
}


int
up(string str)
{
#ifdef TOWER_BLOCKED 
    if (!this_player()->query_wiz_level()) { 
        write("The stairs feel unsafe so you decide not to continue up.\n"); 
        return 1;
    } 
    write("The tower is currently blocked to mortals but you may ascend.\n"); 
    return 0;
#else 
    write("You walk up the stairs of the majestic tower.\n"); 
    /* Don't want to be noisy here as there's a board */ 
    return 0;
#endif
}


int
immortal()
{
    if (SECURITY->query_wiz_level(this_player()->query_real_name()) == 0 &&
        TP->query_average_stat() < 120)
    {
	write("You feel unworthy to enter here.\n");
	return 1;
    }
    return 0;
}

int
nonewbie()
{
    if (SECURITY->query_wiz_level(this_player()->query_real_name()) == 0 &&
        TP->query_average_stat() < 35)
    {
	write("You are not quite ready to enter here.\n");
	return 1;
    }
    return 0;
}


string
wizinfo()
{
    return 
   ("This is the point of access to the info offices of Genesis " +
    "domains. Offices must be added here by use of the `addoffice' " +
    "command, which you can use if you are a liege or arch. " +  
    "The syntax is: `addoffice <domain> <floor> <path>' where the " +    
    "first argument is the domain name, the second argument is the " +
    "number of the floor in the tower (currently it must be between " +
    "1 and " + (sizeof(max_offices)-1) + " inclusive) and the third " +
    "argument is the room path e.g. /d/Calia/info_office. Arches and lieges " +
    "can use `remoffice' to remove an office. The syntax is: " + 
    "`remoffice <domain>' If you would like to list office details, " + 
    "you may use `listoffice [floor]'.\n");  
}

object
fix_board()
{
    object hub;

    hub = clone_object("/std/board");
    if (hub) {
        hub->set_board_name("/d/Genesis/start/human/town/hub_save");
        hub->set_num_notes(50);
        hub->set_anonymous(0);
        hub->set_silent(1);
        hub->set_show_lvl(1);
	hub->set_remove_rank(WIZ_NORMAL);
        hub->set_remove_str("Sorry, mortals are not allowed to remove notes.");
	hub->set_err_log("/d/Genesis/start/human/town/hub_err");

	hub->move(this_object());
	return hub;
    }
    return 0;
}


string *
query_domain_arr()
{
   return m_indexes(domains); 
}


mixed
query_office_floor(string dom)
{
    mixed e;

    dom = capitalize(lower_case(dom)); 
    e = domains[dom]; 

    if (!pointerp(e)) 
        return 0;

    return (TOWN_DIR + floor_names[e[0]]); 
}


mixed
query_office_path(string dom)
{
    mixed e;

    dom = capitalize(lower_case(dom)); 
    e = domains[dom]; 

    if (!pointerp(e)) 
        return 0;

    return e[1]; 
}

string *
query_floor_exits(int floor)
{
    string *ind, *ex;
    int i;

    ind = m_indexes(domains); 

    if (!sizeof(ind)) 
        return ({ }); 

    ex = ({ }); 

    for (i = 0; i < sizeof(ind); i++)  
        if (domains[ind[i]][0] == floor) 
             ex += ({ domains[ind[i]][1], lower_case(ind[i]), 0 });  

    return ex;
}


string *
query_floor_domains(int floor)
{
    string *ind, *dm;
    int i;

    ind = m_indexes(domains); 

    if (!sizeof(ind)) 
        return ({ }); 

    dm = ({ }); 

    for (i = 0; i < sizeof(ind); i++)  
        if ((domains[ind[i]])[0] == floor) 
             dm += ({ ind[i] });  

    return dm;
}


varargs int
tower_rights(object tp, string dom, int remove)
{
    string pn;
    int r;

    if (!objectp(tp) || !stringp(dom)) 
         return 0;

    dom = capitalize(lower_case(dom)); 

    pn = tp->query_real_name(); 

    if (member_array(dom, SECURITY->query_domain_list()) == -1) {  
         if (remove) /* someone removing defunct domain's office? */ 
             return 1;

         notify_fail("No such domain!\n"); 
         return 0;
    } 

    r = SECURITY->query_wiz_rank(pn); 

    if ((r < WIZ_LORD) || 
        ((member_array(pn, SECURITY->query_domain_members(dom)) == -1) &&  
         (r < WIZ_ARCH))) { 
        notify_fail("You do not have the authority to do that!\n"); 
        return 0;
    } 

    return 1;
}


/* Action to add an office entry */ 
int
addoffice(string str)
{
    object tp, r; 
    string *args;
    int f;
    mixed e;

    tp = this_player(); 
    if (!tp->query_wiz_level())  
        return 0;

    notify_fail("addoffice <domain> <floor> <path>\n"); 

    if (!stringp(str))  
        return 0;

    args = explode(str, " "); 

    if (sizeof(args) != 3) 
        return 0;

    args[0] = capitalize(lower_case(args[0])); 
    if (!tower_rights(tp, args[0]))  
         return 0;

    if (sscanf(args[1], "%d", f) != 1) {  
         notify_fail("The floor must be an integer.\n"); 
         return 0;
    } 

    e = domains[args[0]];  
    if (pointerp(e)) { 
        notify_fail("You must do `remoffice " + args[0] + "' first.\n"); 
        return 0;
    } 

    if ((f < 1) || (f >= sizeof(max_offices))) {  
        notify_fail("The floor must be in the range: " +
                    "1-" + (sizeof(max_offices)-1) + ".\n"); 
        return 0;
    } 

    if (sizeof(query_floor_domains(f)) >= max_offices[f]) {  
        notify_fail("Floor " + f + " already has its maximum number " +
                    "of offices!\n"); 
        return 0; 
    } 

    if (!wildmatch("/d/" + args[0] + "/*", args[2])) { 
        notify_fail("The office directory must begin: " + 
                    "/d/" + args[0] + "/\n"); 
        return 0;
    } 

    domains += ([ args[0] : ({ f, args[2] }) ]); 

    save_object(TOWER_SAVE); 

    if (objectp(r = find_object(query_office_floor(args[0]))))  
        r->add_exit(args[2], lower_case(args[0]), 0); 
    /* otherwise all the exits are set up when the room loads */ 

    tell_object(tp, "Ok.\n"); 
    return 1;
}


/* Action to remove an office entry */ 
int
remoffice(string str)
{
    object tp, r; 
    mixed e;

    tp = this_player(); 
    if (!tp->query_wiz_level())  
        return 0;

    notify_fail("remoffice <domain>\n"); 

    if (!stringp(str))  
        return 0;

    str = capitalize(lower_case(str)); 

    if (!tower_rights(tp, str, 1))  
         return 0;

    e = domains[str];  
    if (!pointerp(e)) { 
        notify_fail("No office has been added for " + str + "!\n"); 
        return 0;
    } 

    if (objectp(r = find_object(query_office_floor(str))))  
        r->remove_exit(lower_case(str)); 
    /* otherwise all the exits are set up when the room loads */ 

    domains = m_delete(domains, str); 
    save_object(TOWER_SAVE); 

    tell_object(tp, "Ok.\n"); 
    return 1;
}


/* Action to list offices for each floor, or a given floor */ 
int
listoffice(string str)
{
    int i, j, k, l;
    string o, *e;
    object tp;

    o = ""; 

    tp = this_player(); 
    if (!tp->query_wiz_level())  
        return 0;

    if (!stringp(str)) {  
        j = 0; 
        k = sizeof(max_offices); 
    } 
    else { 
        if (sscanf(str, "%d", j) != 1) { 
            notify_fail("You must give the floor number as an integer.\n"); 
            return 0; 
        } 
        else if ((j < 1) || (j > sizeof(max_offices)-1)) { 
            notify_fail("That floor number is not in the correct range.\n"); 
            return 0;
        } 
        k = j+1; 
    } 

    o = sprintf("%-7s %-16s %-53s\n", "Floor", "Domain", "Office"); 
    for (i = j; i < k; i++) {  
        e = query_floor_exits(i); 
        for (l = 0; l < sizeof(e); l += 3) 
             o += sprintf("%-7d %-16s %-53s\n", i, capitalize(e[l+1]), e[l]); 
    } 

    this_player()->more(o);  
    return 1;
}


/* old stuff
void
make_exits()
{
    int domains;
    string *domain_arr;
    
    domain_arr = call_other("/d/Genesis/start/human/town/tower", "query_domain_arr");
    domains = sizeof(domain_arr);
}
*/ 


void
init()
{
    ::init(); 

    if (!this_interactive()->query_wiz_level())  
         return;

    add_action(remoffice, "remoffice"); 
    add_action(addoffice, "addoffice"); 
    add_action(listoffice, "listoffice"); 
}

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
    object quest_orb;
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Sparkle");
        quest_orb->set_extra_line("The orb floats gently in the air.");
        quest_orb->move(this_object(), 1);
    }    
}
