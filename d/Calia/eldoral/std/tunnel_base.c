
/* 
 *
 *  Undead tunnel base
 *
 *  (c) Jaacar (Mike Phipps), October 2003
 *
 *  Based on a baseroom by Baldacin
 *  Fixed typo - Jaacar, May 2016
 *
 */

inherit "/std/room";

#include <composite.h>
#include "../defs.h"
#include  "tells.c"

                              ///////////////////////////////
int gRoom_type;               // The area type.
string gExtra_desc;           // The extra description.

                              //////////////////////////////////////////////////
void set_area_type(int type); // Set the area type. 
                              // 1 - Intersection (type a).  
                              // 2 - Tunnel (type b).
                              // 3 - Tunnel (type c).
                              // 4 - Tunnel (type d).
                              // 5 - Dead end (type e).
                              // 6 - Dead end (flooded pool).
                              // 7 - Banshee Lair.
                              // 8 - Heucuva Lair.

void clone_undead(string race, int level);
void add_items(int type);
string query_short_desc();    // Sets the short desc.
string query_long_desc();     // Sets the long desc.

void
create_tunnel_room() 
{ 
}

nomask void
create_room()
{
    set_short("@@query_short_desc");
    set_long("@@query_long_desc");
    gRoom_type = 1;
    create_tunnel_room();
}

string
extra_desc()
{
    return gExtra_desc;
}

void
set_extra_desc(string desc)
{
    gExtra_desc = desc;
}

void
set_area_type(int type)
{
    gRoom_type = type;
    add_tells("tunnel");
    add_items(type);
}

void 
add_items(int type)
{
    switch(type)
    {
        case 1: // 1 - Intersection (type a).
            add_item(({"skeletons", "bones", "leftovers"}),"They seem to be some "+
                "humanoid bones. Perhaps you should turn back!\n");
            break;
        
        case 2: // 2 - Tunnel (type b).
            add_item("","");
            break;
        
        case 3: // 3 - Tunnel (type c).
            add_item(({"skeletons", "bones", "leftovers"}),"They seem to be some "+
                "humanoid bones. Perhaps you should turn back!\n");
            break;
        
        case 4: // 4 - Tunnel (type d).
            add_item(({"stream","streams","puddle", "pool"}),"Small streams of "+
                "water run down the walls, forming a small, shallow pool of "+
                "water on the ground.\n");
            break;
        
        case 5: // 5 - dead end (type e).
            add_item("","");
            break;

        case 6: // 6 - dead end (flooded pool).
            add_item(({"pool","flooded pool"}),"This flooded pool seems to lead "+
                "deep into the ground and leads off to the northeast. The pool "+
                "is too small for you to attempt to enter.\n");
            break;

        case 7: // 7 - Banshee Lair.
            add_item(({"ruins","ancient ruins","ancient looking ruins"}),
                "There are many ruined columns and what appears to be the "+
                "remains of some type of altar.\n");
            add_item("columns","The columns are all collapsing on one another "+
                "and have many chips and cracks in them.\n");
            add_item(({"bones","many bones"}),"There are many bones strewn "+
                "throughout the ruins here in this cave. They appear to be "+
                "humanoid mostly.\n");
            add_item("altar","You can make nothing out about this ruined altar "+
                "except that it was once an altar.\n");
            break;

        case 8: // 8 - Heucuva Lair.
            add_item("corpses","The corpses are all decaying humanoid figures "+
                "set into a position as though they are praying.\n");
            break;
    }
    
    add_item("moss","It is a dark-green slimy plant that "+
        "grows almost like a mat on the walls.\n");
    add_item(({"wall", "walls"}), "The small spaces of the wall "+
        "that are not covered with a fusty smelling moss are dark, "+
        "almost pitch-black, in colour.\n");
    
    return;    
}
	
string
query_short_desc()
{
    switch(gRoom_type)
    {
        case 1: // 1 - Intersection (type a).
            return "In a tunnel intersection";
            break;
        
        case 2: // 2 - Tunnel (type b).
            return "Along a narrow tunnel";
            break;
    
        case 3: // 3 - Tunnel (type c).
            return "In a narrow tunnel";
            break;
    
        case 4: // 4 - Tunnel (type d).
            return "A bend in the tunnel";
            break;
    
        case 5: // 5 - Dead end (type e).
            return "Dead end";
            break;
        
        case 6: // 6 - Dead end (flooded pool).
            return "Dead end";
            break;

        case 7: // 7 - Banshee lair.
            return "Ruins";
            break;

        case 8: // 8 - Heucuva lair.
            return "Ruined temple";
            break;
    }
}


string
query_long_desc()
{
    int *exits = TO->query_obvious_exits();
    string desc = "";

    switch(gRoom_type)
    {
        case 1: // 1 - Intersection (type a).
            desc = "You have arrived at an intersection in the tunnel. "+
                "Exits leads off in "+LANG_WNUM(sizeof(exits))+" directions - "+
                COMPOSITE_WORDS(exits)+". The cave walls are covered with "+
                "a dark-green, slimy moss that has a very fusty smell. Some old "+
                "bones and leftovers are lying on the ground here.";
            break;

        case 2: // 2 - Tunnel (type b).
            desc = "You are venturing along a narrow tunnel inside a big "+
                "cave system. The tunnel continues "+COMPOSITE_WORDS(exits)+
                ". The cave walls are covered with a dark-green, slimy moss. "+
                "There is a malodorous smell here but you can't really figure "+
                "out where it is coming from.";
            break;

        case 3: // 3 - Tunnel (type c).
            desc = "You have stopped at a narrow tunnel of what seems to "+
                "be a big tunnel system. It continues "+COMPOSITE_WORDS(exits)+
                ". Some old skeletons and bones are spread all over the tunnel "+
                "floor here.";
            break;
    
        case 4: // 4 - Tunnel (type d).
            desc = "You are standing in the middle of a sharp bend in the tunnel. "+
                "It leads "+COMPOSITE_WORDS(exits)+ ". A very fusty smell rises "+
                "from the mossy walls here, almost too much for you to handle. "+
                "Small streams of water run down the walls, forming a puddle on "+
                "the ground.";
            break;
    
        case 5: // 5 - Dead end (type e).
            desc = "You have arrived at a dead end. The only way out of here "+
                "is the to the "+COMPOSITE_WORDS(exits)+".";
            break;

        case 6: // 6 - Dead end (flooded pool).
            desc = "You have arrived at a dead end. The only way out of here "+
                "is to the "+COMPOSITE_WORDS(exits)+". On the ground there "+
                "is a flooded pool.";
            break;

        case 7: // 7 - Banshee lair.
            desc = "You have arrived at a dead end. The only way out of here "+
                "is to the "+COMPOSITE_WORDS(exits)+". Scattered around the "+
                "area are some ancient looking ruins. Strewn throughout the "+
                "ruins are the many bones of the victims of the inhabitants of "+
                "this cave.";
            break;

        case 8: // 8 - Heucuva lair.
            desc = "You have arrived at a dead end. The only way out of here "+
                "is to the "+COMPOSITE_WORDS(exits)+". This appears to be a "+
                "grotesque mockery of an old temple. There are many corpses "+
                "lining the walls, set into positions resembling those praying "+
                "in a chapel.";
            break;
    }
    
    return desc + (strlen(extra_desc()) ? " "+extra_desc() : "")+"\n";
}

void
clone_undead(string race, int level)
{
    object undead;
    object *undeads = filter(all_inventory(TO), &->id("undead"));

	if (sizeof(undeads) > 4)
		return;

	undead = clone_object(STD + "undead_std");
    undead->setup_undead(race, level);
    undead->move(TO);
}
