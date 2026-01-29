
/*  

    The hall of war, start room for Cadets of Gelan

    Coded by Maniac@Genesis, March 1997

    Modified by Maniac, April 1998, August 1998

    Copyright (C) Miguel Leith 1997

    Thanks to "man weapon_guide" for most of the lists 
    of weapons in the wall descriptions. 

*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <money.h>
#include "cadet.h"

#define YSNS "It looks like a decent quality weapon, " + \
             "fixed firmly to the wall.\n"

int
gc_query_private_room()
{
    return 1;
}


void
create_room()
{
    set_short("The hall of war");
    set_long("A hexagonal hall with oak panelled walls " +
         "extends around you, each wall exhibiting a collection " +
         "of a particular class of weapon or armour. Numerous swords, " +
         "polearms, axes, knives, clubs and gauntlets are on " +
         "display. The walls also have boards " +
         "displaying pictures of cadets and graduates. " +
         "Six broad stone columns support the tiled ceiling, " +
         "surrounding a ladder at the centre of the hall that " +
         "leads up to another chamber through a hexagonal aperture. " +
         "An arched doorway in each wall leads to one of the " +
         "guild's rooms. It is possible to <start here> if you wish.\n"); 

    add_item(({"aperture", "hexagonal aperture"}), 
              "Through the hexagonal aperture in the ceiling you see " +
              "a gentle light.\n"); 

    add_item(({"ladder"}), 
              "A simple wooden ladder leads up to another chamber " +
              "through a hexagonal aperture in the ceiling.\n"); 

    add_item(({"column", "columns", "stone column", "stone columns" }), 
              "The stone columns are broad, dark grey and smooth.\n"); 

    add_item(({"panels", "oak panels", "panel", "oak panel", 
               "wall panels"}), 
             "The wall panels are made of oak and have a matt varnish.\n"); 

    add_item(({"doorway", "doorways", "arched doorway", "arched doorways", 
               "first doorway", "second doorway", "third doorway", 
               "fourth doorway", "fifth doorway", "sixth doorway" }), 
             "There are six arched doorways leading out from the room, " +
             "one in each wall. Above each doorway are two picture boards.\n");  

    add_item(({"ceiling", "tiles", "red tiles", "red ceiling" }), 
         "The ceiling is covered with red hexagonal tiles.\n"); 

    add_item(({"walls", "wall", "oak-panelled wall", "oak-panelled walls",
               "collection", "collections" }), 
         "Specify which wall you wish to look at (first wall, " +
         "second wall etc.)\n"); 

    add_item(({"board", "boards", "picture board", "picture boards", 
              "pictures", "picture", "cadets", "graduates", 
              "pictures of cadets", "pictures of graduates" }), 
         "There are two sets of picture boards here, one for cadets " + 
         "and one for graduates. You can see what a particular cadet " +
         "or graduate looks like if you:\n" +
         "  examine picture of <cadet name/graduate name>\n\n" + 
         "Different cadets and graduates are distinguished by various " +
         "attributes (e.g. \"race\", \"gender\", \"gamelevel\"), each " +
         "of which has various possible values (e.g. for the attribute " +
         "\"race\" the possible values would be \"dwarf\", \"elf\", " +
         "\"goblin\", \"gnome\", \"hobbit\" and \"human\".) You can " +
         "list attributes and their possible values if you:\n" +
         "  list attributes\n" + 
         "  list values of <attribute>\n\n" + 
         "You can list all cadets/graduates sorted by " +
         "the values of a specified attribute if you:\n" +
         "  list cadets sorted by <attribute>\n" + 
         "  list graduates sorted by <attribute>\n\n" + 
         "You can list a _subset_ of cadets/graduates sorted " +
         "by the values of a specified attribute if you:\n" +
         "  list cadets of <attribute> <value> sorted by <attribute>\n" + 
         "  list graduates of <attribute> <value> sorted by <attribute>\n"); 

    add_item(({"sword", "swords", "first wall", "sword wall", 
               "wall of swords", "collection of swords", 
               "sword collection" }), 
             "A range of swords is mounted on the first wall. " +
             "There is a falchion, a scimitar, a gladius, a longsword, " + 
             "a bastard sword, a two-handed sword, a broadsword and a " +
             "rapier.\n"); 

    add_item(({"falchion", "scimitar", "gladius", "longsword", 
               "bastard sword", "two-handed sword", "broadsword",  
               "rapier" }), YSNS); 

    add_item(({"polearm", "polearms", "second wall", "polearm wall", 
               "wall of polearms", "collection of polearms", 
               "polearm collection" }), 
             "A range of polearms is mounted on the second wall. " +
             "You see a quarterstaff, a spear, a glaive, a fauchard, " +
             "a guisarme, a halberd, a luzern hammer, a partisan " +
             "and a trident.\n"); 

    add_item(({"quarterstaff", "spear", "glaive", "fauchard", "guisarme", 
               "halberd", "luzern hammer", "partisan", "trident" }), 
               YSNS); 

    add_item(({"axe", "axes", "third wall", "axe wall", "wall of axes", 
               "collection of axes", "axe collection" }), 
             "A range of axes is mounted on the third wall. " +
             "You see a hand axe, a beard axe, several battle axes, " +
             "a number of broad axes, a bardiche and a lochaber axe.\n"); 

    add_item(({"axe", "hand axe", "beard axe", "battle axe", "broad axe", 
               "bardiche", "lochaber axe"}), 
             YSNS); 

    add_item(({"knife", "knives", "fourth wall", "knife wall", 
               "wall of knives", "collection of knives", 
               "knife collection" }), 
             "A range of knives is mounted on the fourth wall. " +
             "You see an ordinary knife, a ballock knife, a dagger, a " +
             "rondel dagger, a dirk, a main gauche, a stiletto, a " +
             "misericord and a bodkin.\n"); 

    add_item(({"ordinary knife", "ballock knife", "dagger", 
               "rondel dagger", "dirk", "main gauche", "stiletto", 
               "misericord", "bodkin" }), YSNS); 

    add_item(({"club", "clubs", "fifth wall", "club wall", 
               "wall of clubs", "collection of clubs",  
               "club collection" }), 
             "A range of clubs is mounted on the fifth wall. " +
             "You see a wooden club, a spiked club, a flail, a " +
             "morningstar, a mace, a warhammer, a two-handed spiked club, " +
             "a two-handed flail and a two-handed morningstar.\n");  

    add_item(({"wooden club", "spiked club", "fiail", "warhammer", 
               "morningstar", "mace", 
               "two-handed spiked club", "two-handed flail", 
               "two handed morningstar" }), YSNS); 

    add_item(({"gauntlet", "gauntlets", "sixth wall", "gauntlet wall", 
               "wall of gauntlets", "gauntlet collection", 
               "collection of gauntlets" }), 
             "A range of gauntlets is mounted on the sixth wall. " +
             "You see gauntlets of various materials including brass, " +
             "leather, silver, gold and steel, each with blades or studs " + 
             "to maximise damage.\n"); 

    add_prop(OBJ_S_WIZINFO, "This is a default start location.\n");
    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_HIDE, 35); 

    add_exit(GC_TRAINROOM, "north"); 
    add_exit(GC_BOARDROOM, "east"); 
    add_exit(GC_POSTROOM, "south"); 
    add_exit(GC_COMMONROOM, "common"); 
    add_exit(GC_MESSROOM, "southwest"); 
    add_exit(GC_DROPROOM, "west"); 
}


void
check_reset_start_location(object player)
{
    if (!objectp(player)) 
        return; 

    if (GC_TRAINROOM->is_unworthy(player->query_real_name())) { 
        tell_object(player, "You may no longer start here as you " + 
                            "have a bad reputation.\n"); 
        player->set_default_start_location(player->query_def_start()); 
        return; 
    } 
    if (!IS_GELAN_CADET(player) && !IS_GRADUATE(player)) { 
        tell_object(player, 
            "You may no longer start here as you are not a graduate.\n"); 
        player->set_default_start_location(player->query_def_start()); 
        return; 
    } 
    if (player->query_guild_member_occ()) { 
        tell_object(player, "You may no longer start here as you are " + 
            "a member of an occupational guild.\n"); 
        player->set_default_start_location(player->query_def_start()); 
        return; 
    } 
}


void 
enter_inv(object ob, object from) 
{ 
    ::enter_inv(ob, from); 

    if (interactive(ob) && 
        (!objectp(from) || 
        (from->query_domain() != query_domain())) && 
        ob->query_default_start_location() == GC_STARTROOM) 
        set_alarm(15.0, 0.0, &check_reset_start_location(ob)); 
} 


int 
start(string str)
{
    object tp = this_player(); 

    if (str != "here")
	  return 0; 

    if (GC_TRAINROOM->is_unworthy(tp->query_real_name())) { 
        notify_fail("You have a bad reputation so you may not " + 
                    "start here.\n"); 
        return 0; 
    } 

    if (tp->query_default_start_location() == GC_STARTROOM) { 
        notify_fail("You already start here.\n"); 
        return 0; 
    } 

    if (!IS_GELAN_CADET(tp))  { 
        if (!IS_GRADUATE(tp)) { 
            notify_fail("You are not a Graduate or a Cadet of Gelan!\n"); 
            return 0; 
        } 
        if (tp->query_guild_member_occ()) { 
            notify_fail("You are a member of an occupational guild " + 
                        "so you may not start here.\n"); 
            return 0; 
        } 
    } 

    tp->set_default_start_location(GC_STARTROOM); 
    write("Ok, you start here now.\n"); 
    return 1; 
}


int
examine_picture(string str)
{
    string f, pl, pic; 

    if (!stringp(str) || !strlen(str))
        return 0; 

    if ((sscanf(str, "picture of %s", pl) != 1) && 
        (sscanf(str, "at picture of %s", pl) != 1))
        return 0;

    pl = lower_case(pl); 

    if (file_size(f = GC_GRADUATE_PICTURE(pl)) == -1 &&  
        file_size(f = GC_CADET_PICTURE(pl)) == -1)  
        return 0;

    pic = read_file(f); 
    if (!stringp(pic)) 
        return 0;

    this_player()->more(pic); 
    return 1;
}


int
list_membership(string str)
{
    return GC_TRAINROOM->list_membership(str); 
}


int
up_ladder(string str)
{
    return (GC_DIR + "hall_of_peace")->up_ladder(str, this_object()); 
}


int
do_meditate(string str)
{
    notify_fail("You will have to ascend the ladder to meditate.\n"); 
    return 0; 
}


/*
 * Function:     do_store
 * Description:  Action function, try to store weapons in order
 *               to enter the hall of peace. 
 */ 
int
do_store(string str)
{
    return (GC_DIR + "hall_of_peace")->store(str); 

}


/*
 * Function:     do_claim
 * Description:  Action function, try to claim weapons after
 *               entering the hall of peace. 
 */ 
int
do_claim(string str)
{
    return (GC_DIR + "hall_of_peace")->claim(str); 
}


void
init()
{
    ::init();
    add_action(start, "start");
    add_action(list_membership, "list"); 
    add_action(examine_picture, "exa"); 
    add_action(examine_picture, "examine"); 
    add_action(examine_picture, "look"); 
    add_action(do_meditate, "meditate"); 
    add_action(do_store, "cstore"); 
    add_action(do_claim, "cclaim"); 
    add_action(up_ladder, "climb"); 
    add_action(up_ladder, "up"); 
    add_action(up_ladder, "ascend"); 
}
