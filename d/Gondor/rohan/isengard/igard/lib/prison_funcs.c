/*
 *  IGARD_LIB + "prison_funcs.c"
 *
 *  Various functions common to Isengard prison rooms.
 *
 *  Last modified by Alto, 10 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../igard_defs.h"

inherit IGARD_LIB + "deep_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/sys/formulas.h"

/* GLOBAL VARIABLES */

string               *handle    =({});
string               *extradesc =({});
string               Exline, Vehicle;
static object *Htroop   = allocate(1);
static object *Dtroop   = allocate(1);
static object *Etroop   = allocate(1);


/* PROTOTYPES */

public int           prison_add_items();
public string        hallway_long_desc();
public int           hallway_add_items();
public void          add_hallway_tells();
public string        cell_extraline();
public void          cell_add_items();
public string        cell_long_desc();
public void          add_human_prisoners();
public void          add_elf_prisoners();
public void          add_dwarf_prisoners();


public int
prison_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"rock", "black rock", "stone"}), "This area is delved "
        + "into the black rock of Isengard, which is in places natural and "
        + "in others carved by the hands of Men.\n");
    add_item(({"isengard", "fortification"}), "You are somewhere below "
        + "the fortification of Isengard.\n");
    add_item(({"plain", "great plain", "plain of isengard", 
        "great plain of isengard"}), "It is somewhere above you.\n");
    add_item(({"wall", "walls"}), "The walls are delved from black rock "
        + "beneath the plain of Isengard. The rock glistens in the guttering "
        + "torchlight.\n");
    add_item(({"ceiling", "roof"}), "The ceiling is smooth and solid "
        + "black rock. It seems unbreakable and timeless.\n");
    add_item(({"floor", "ground"}), "The floor here is made from black "
        + "rock and worn smooth by tens of thousands of booted feet over "
        + "many long years.\n");
    add_item(({"torch", "torches"}), "Torches are mounted in iron "
        + "brackets set into the walls. They gutter and "
        + "hiss as the wind of your passing stirs them.\n");
    add_item(({"bracket", "iron bracket", "brackets", "iron brackets"}), 
        "Set into the walls, iron brackets bear torches "
        + "that gutter and hiss in the wind of your passing.\n");
    add_item(({"depths", "depths of isengard"}), "All around you the "
        + "depths of Isengard creak and groan.\n"); 

    return 1;
}


string
hallway_long_desc()
{
    return "The sounds of your breathing and the stride of your feet "
    + "are muffled in the close air of this dank corridor. The black rock "
    + "of the walls and floor are damp to the touch and small rivulets of "
    + "condensation pool here and there about the passage. Light from the "
    + "guttering torches mounted on the walls gleams and sparkles as it "
    + "is reflected in the pools and droplets of water. ";
}


public int
hallway_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"rivulets", "condensation", "pool", "pools"}), "The cool "
        + "walls give rise to rivulets of condensation. The water pooling "
        + "on the floor makes passage treacherous in places.\n");
    add_item(({"water", "pool", "pools", "droplet", "droplets"}), 
        "Pools of water are condensed here and there on the floor.\n");
    add_item(({"doorway", "doorways"}), "The doors show evidence of "
        + "violence and attack. The wood is scarred by numerous scratches "
        + "and gouges, and the locks are mangled beyond use.\n");
    add_item(({"scratch", "scratches", "gouge", "gouges"}), "The wood of "
        + "the doors is marked heavily with scratches and gouges, made by "
        + "the repeated bashing of a heavy blunt object.\n");
    add_item(({"bar", "bars", "iron bars", "iron bar"}), "Set into the "
        + "doors are rusted iron bars. You notice several bars appear to "
        + "be missing from their sockets.\n");
    add_item(({"socket", "sockets"}), "The iron bars in the doors are mounted "
        + "sturdy sockets. Some of the sockets are empty, suggesting that some "
        + "bars have been recently removed.\n");
    add_item(({"lock", "locks"}), "The locks on the doors are smashed beyond "
        + "use.\n");
    add_item(({"hinge", "hinges"}), "The doors swing freely upon their "
        + "hinges, which are made from sturdy yet rusted iron set squarely "
        + "into the walls.\n");

    return 1;
}


void
add_hallway_tells()
{
    set_tell_time(120);

    add_tell("Someone shouts in the distance.\n");
    add_tell("You hear water dripping.\n");
    add_tell("A droplet of water splashes into one of the pools.\n");
    add_tell("Metal clatters on the floor somewhere down the corridor.\n");
    add_tell("Hushed voices echo down the passage.\n");
    add_tell("A droplet of water falls into your hair.\n");
    add_tell("The ground rumbles beneath your feet.\n");
    add_tell("The low rumbling of machinery can be heard from behind the "
        + "walls.\n");
    add_tell("Someone screams in pain!\n");
    add_tell("Moisture condenses upon your brow.\n");
    add_tell("Angry voices can be heard down the corridor.\n");
    add_tell("A rat scurries away into the shadows.\n");
    add_tell("Tortured machinery squeals and rattles from above.\n");
    add_tell("The scents of blood and urine assault your nose.\n");
    add_tell("The stench of death wafts up the passage.\n");
    add_tell("Metal clangs against metal in the distance.\n");
}


string
cell_extraline()
{
    int position;

    string *extradesc =
/*1*/   ({"The walls are covered with mold and grime, and the floor is "
               + "slick with something best left unexplored. From the "
               + "moment you entered the room, the "
               + "stench of mildew has assaulted your nostrils. The prisoners "
               + "for whom this cell is home must lead unimaginably "
               + "miserable lives.", 
/*2*/     "The air is thick with the cloying stench of offal and blood. "
               + "Splattered on the walls and floor are countless droplets "
               + "of gore. Someone recently died a tremendously violent "
               + "death in this room.", 
/*3*/     "This appears to be one of the cleaner cells in the prison, "
               + "suggesting that its occupants are recent enough arrivals "
               + "to yet maintain some sense of pride and hope. Beyond "
               + "a single pile of filth in the corner, there is little "
               + "evidence that the room lacks even the most rudimentary "
               + "sanitation facilities.",
/*4*/     "The floor is covered with a thin layer of soiled and moldy "
               + "straw. Rats scurry away at your approach, darting "
               + "beneath the larger clumps of straw in the corners.",
/*5*/     "The sound of your steps echo off the bare walls, ceiling and "
               + "floor. The cell is entirely devoid of even the most "
               + "basic needs of the prisoners housed within.",
/*6*/     "Great cobwebs stream down from the ceiling and brush the "
               + "top of your head. Everything is covered in a fine layer "
               + "of dust, suggesting that this room sat long vacant "
               + "until recently being opened to house prisoners. Perhaps "
               + "the number of lost souls housed below the plain of "
               + "Isengard is expanding.",
/*7*/     "The straw scattered across the stone floor is wet, mildewed "
               + "and infested with lice, fleas and other vermin. A basin "
               + "of filthy water stands in one corner.",
/*8*/     "The air in the room is damp and uncomfortably cold. Water drips "
               + "from numerous cracks in the walls and ceiling, completely "
               + "saturating the sticky clumps of straw scattered about "
               + "the stone floor."});


    string *handle =
/*1*/     ({"lone", 
/*2*/       "ltwo", 
/*3*/       "lthree",
/*4*/       "lfour",
/*5*/       "lfive",
/*6*/       "lsix",
/*7*/       "lseven",
/*8*/       "leight"});


    Exline = ONE_OF_LIST(extradesc);

    position = member_array(Exline, extradesc);

    Vehicle = handle[position];

    return Vehicle;

}


void
cell_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    switch (Vehicle)
    {
    case "lone":
        add_item(({"mold", "patches", "fuzzy patches"}), "Dark mold grows "
            + "in fuzzy patches here and there on the walls.\n");
        add_item(({"grime"}), "The walls are covered with grime.\n");
        break;

    case "ltwo":
        add_item(({"droplet", "droplets", "gore"}), "Droplets of gore "
            + "are spattered everywhere in the room. Only a battle of "
            + "great violence would produce such a spray.\n");
        break;

    case "lthree":
        add_item(({"filth", "pile", "pile of filth"}), "In one corner "
            + "of the room lies a stinking pile of filth. The stench "
            + "rising from it makes the nature of its contents clear.\n");
        break;

    case "lfour":
        add_item(({"straw", "filthy straw"}), "Filthy straw is scattered "
            + "about the floor. It seems to be the home for a number of "
            + "squeaking rodents.\n");
        add_item(({"clump", "clumps", "corner"}), "The straw is pushed "
            + "into the corners in large clumps.\n");
        add_item(({"rat", "rats", "rodent", "rodents"}), "Out of the "
            + "corner of your eye, you occasionaly catch a glimpse of a "
            + "rat scurrying about in the straw.\n");
        break;

    case "lfive":
        break;

    case "lsix":
        add_item(({"cobweb", "cobwebs", "great cobweb", "great cobwebs"}), 
            "Great dusty cobwebs dangle from the ceiling, brushing your "
            + "face as you move about the room.\n");
        add_item(({"dust", "layer", "fine layer of dust", 
            "layer of dust"}), "A fine layer of dust coats everything "
            + "in the room. You kick up small clouds of it as you move "
            + "about the room.\n");
        break;

    case "lseven":
        add_item(({"straw"}), "The straw beneath your feet is covered "
            + "in mildew and looks entirely unsavoury.\n");
        add_item(({"lice", "louse", "fleas", "flea", "vermin"}), "The "
            + "damp straw is literally crawling with a revolting "
            + "array of lice and fleas.\n");
        add_item(({"basin"}), "The basin is bolted down and filled with "
            + "water that looks and smells disgusting.\n");
        add_item(({"water"}), "The water in the basin is covered with "
            + "a revolting film of muck.\n");
        add_item(({"film", "muck"}), "It covers the water in the bucket.\n");
        break;

    case "leight":
        add_item(({"water"}), "Water runs down the walls and seeps into "
            + "the sticky clumps of straw on the floor.\n");
        add_item(({"cracks", "crack"}), "Water drips through numerous "
            + "cracks in the walls.\n");
        add_item(({"clump", "clumps", "sticky clump", "sticky clumps",
            "straw", "clumps of straw"}), "The straw is sticky and bunched "
            + "up into sticky clumps here and there upon the floor.\n");
        break;

    default:
        write("This is one of those wrongness in space and time messages, "
            + "which means you should probably file a bugreport in this "
            + "room.\n");
        break;
    }
}


string
cell_long_desc()
{
    string extra;

    extra = Exline;

    return "You have entered a small cramped prison cell. " + extra + "\n";
}


void
add_human_prisoners()
{
        clone_npcs(Htroop,  IGARD_NPC + "igard_human_prisoner.c",  -1.0);
        Htroop->set_restrain_path(IGARD_DEEP_PRISON);
        Htroop->arm_me();
        Htroop->move_living("M", TO);
        Htroop->add_2_friends(2);
}


void
add_elf_prisoners()
{
        clone_npcs(Etroop,  IGARD_NPC + "igard_elf_prisoner.c",  -1.0);
        Etroop->set_restrain_path(IGARD_DEEP_PRISON);
        Etroop->arm_me();
        Etroop->move_living("M", TO);
        Etroop->add_2_friends(2);
}


void
add_dwarf_prisoners()
{
        clone_npcs(Dtroop,  IGARD_NPC + "igard_dwarf_prisoner.c",  -1.0);
        Dtroop->set_restrain_path(IGARD_DEEP_PRISON);
        Dtroop->arm_me();
        Dtroop->move_living("M", TO);
        Dtroop->add_2_friends(2);
}




