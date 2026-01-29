/*
 *  /d/Gondor/rohan/isengard/storerm1.c
 *
 *  Opus, June 1997
 *
 *  Copyright   1997 by Robert Miller
 *
 *  Modification log:
 */

#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>

// Prototypes
string w_desc();
string a_desc();
string getweapon();
string getarmour();
string wepdesc();
string armdesc();
void   getmold();

public void
create_isengard()
{
    set_short("inside the first storeroom");
    set_long(BSN(
        "This is a rather large, damp room currently being used "+
        "for storage. A number of weapon and armour racks have been lined "+ 
        "up along the walls. An opening in the far corner opens to a "+
        "flight of stairs leading upwards."));
    add_item( ({"wall", "walls"}), BSN(
        "All of the walls are damp to the touch. They give off a musty "+
        "smell and have traces of mold growing on them."));
    add_item( ({"floor", "ground"}), BSN(
        "Amazingly, the floor is relatively smooth considering it was "+
        "carved and smoothed by hand many years ago."));
    add_item( ({"rack", "racks"}), BSN(
        "The racks are made from a fine quality of wood. There are "+
        "racks made for weapons as well as armour. The racks appear to be "+
        "locked."));
    add_item( ({"weapon rack", "weapons rack", "weapons racks",
                "weapon racks"}), w_desc());
    add_item( ({"armour rack", "armour racks"}), a_desc());
    add_item( ({"rock", "black rock", "smooth rock",        
                "smooth black rock"}), BSN(
        "This strange black rock, which makes up this entire area, "+
        "has been carved and shaped to form this storage room within the "+
        "ringwall."));
    add_item( ({"opening", "stairs"}), BSN(
        "Located in the corner, the opening appears to be the landing of "+
        "a set of stairs leading upward."));
    add_item( ({"mold", "green mold", "slimy green mold", 
                "slimy mold"}), BSN(
        "Traces of this green, slimy mold are noticable on the walls in a "+
        "couple of spots. It is letting of a faint musty odor."));
    add_item( ({"smell", "odor", "musty smell"}), BSN(
        "This smell is faint, but unpleasant none the less."));
    add_item( "ceiling", BSN(
        "High above, the ceiling of the room is perfectly "+
        "rounded making it difficult to tell where the ceiling ends and "+
        "the wall begins."));
    add_item( ({"weapons", "weapon"}), wepdesc()); 
    add_item( ({"swords", "sword"}), wepdesc());
    add_item( ({"halberds", "halberd"}), wepdesc());
    add_item( ({"armour", "armours"}), armdesc());
    add_item( ({"rohirrim sword", "rohirrim swords", "rohirrim weapon",
                "rohirrim weapons"}), wepdesc());
    add_item( ({"rohirrim armour", "rohirrim armours"}), armdesc()); 
    
    add_cmd_item( ({"armour", "armours"}), ({"get", "take"}), getarmour());
    add_cmd_item( ({"sword", "swords"}), ({"get", "take"}), getweapon());  
    add_cmd_item( ({"halberd", "halberds"}), ({"get", "take"}), getweapon()); 
    add_cmd_item( ({"weapon", "weapons"}), ({"get", "take"}), getweapon());
    add_cmd_item( "wall", ({"touch", "feel"}), BSN(
       "You notice that the walls are very damp to the touch and have bits "+
       "of mold growing in various spots on them."));
    add_cmd_item( "mold", ({"touch", "feel"}), BSN(
        "The mold feels slimy and a bit sticky."));
    add_cmd_item( ({"rack", "armour rack", "weapon rack"}), "unlock", BSN(
         "That does not seem to work."));
    add_cmd_item( "mold", ({"get", "take"}), getmold());
    add_cmd_item( ({"rack", "racks", "armour rack", "weapon rack",
                    "weapons rack", "armour racks", "weapon racks"}), 
                    ({"get", "take"}), BSN(
        "The racks seem to be firmly attacked to the wall."));

    
    add_exit(ISEN_DIR + "stair1.c", "up",   0, 3);
    add_exit(ISEN_DIR + "guardrm.c",   "southeast", 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}

/* 
 *  Function name: w_desc
 *  Description:   gives a stage dependant description of the weapons
 *                 rack based on isen_stage().
 *  Returns:       wdesc
 */
string
w_desc()
{
    string wdesc;
    int    stage;

    stage = (Master->query_isen_stage());
    
    switch (stage)
    {
    case ROHAN_STAGE_PEACE:
        wdesc = "The wooden rack is currently empty of all weapons.";
        break;
    case ROHAN_STAGE_HOSTILE:
        wdesc = "A few swords and halberds have been placed in the racks "+
           "for the guards use. All of the weapons seem to have been "+
           "made from a strange, black material.";
        break;
    case ROHAN_STAGE_WAR:
        wdesc = "The weapon racks are full of weapons for the "+ 
           "guards and army to use. All of the weapons seem "+
           "to have been made from a strange, black material.";
        break;
    case ROHAN_STAGE_BATTLE:
        wdesc = "Only a few weapons can be found in the racks. Most "+ 
           "weapons seem to have been made from a strange, black material. "+
           "A few Rohirrim swords can be identified mixed within the other "+
           "weapons in the rack.";
        break;
    case ROHAN_STAGE_DEFEAT:
        wdesc = "The weapons racks are full of blood-stained "+
           "and broken weapons. Many are made from a strange, black "+
           "material, while others are Rohirrim weapons taken from fallen "+
           "soldiers.";
        break;
    }
    return BSN(wdesc);
}

        
/* 
 *  Function name: a_desc
 *  Description:   gives a stage dependant description of the armour
 *                 rack based on isen_stage().
 *  Returns:       adesc
 */

string
a_desc()
{
    string adesc;
    int    stage;

    stage = (Master->query_isen_stage());
    
    switch (stage)
    {
    case ROHAN_STAGE_PEACE:
        adesc = "The wooden armour rack is currently empty.";
        break;
    case ROHAN_STAGE_HOSTILE:
        adesc = "A few pieces of armour have been placed in the racks "+
           "for the guards to have immediate access to if needed. Every "+
           "piece of armour seems to have a white hand painted on them.";
        break;
    case ROHAN_STAGE_WAR:
        adesc = "The rack is full of various pieces of armour. Many of "+
           "them look brand new and ready for combat. Every piece of "+
           "armour seems to have a white hand painted on them.";
        break;
    case ROHAN_STAGE_BATTLE:
        adesc = "The racks are almost bare, just a few pieces of armour "+ 
           "left behind for the guards to use. Some of the armour left "+
           "in the rack is dented up and has blood stains on them.";
        break;
    case ROHAN_STAGE_DEFEAT:
        adesc = "The armour racks are full of armour. "+
           "Many of the pieces are smeared with blood and damaged from "+
           "battle. Most of the pieces have a white hand painted on it, but "+
           "a few pieces have markings of the Rohirrim army on them.";
        break;
    }
    return BSN(adesc);
}

string
getarmour()
{
    string armourdesc;
    int    stage;

    stage = Master->query_isen_stage();

    switch (stage)
    {
    case ROHAN_STAGE_PEACE:
        armourdesc =  "There is no armour in the rack to get.";
        break;
    default:
        armourdesc = "The racks are all locked, preventing you from taking "+
           "any armour from them.";
        break;
    }
    return BSN(armourdesc);


}
string
getweapon()
{
    string weapondesc;
    int    stage;

    stage = Master->query_isen_stage();

    switch (stage)
    {
    case ROHAN_STAGE_PEACE:
        weapondesc =  "There are no weapons in the rack to get.";
        break;
    default:
        weapondesc = "The racks are all locked, preventing you from taking "+
           "any weapons from them.";
        break;
    }
    return BSN(weapondesc);
}


string
getmold()
{
   // will be used in the near future so that a player can actually
   // get the mold from the walls.

}

string
wepdesc()
{
    string wpdesc;
    int    stage;

    stage = (Master->query_isen_stage());
    
    switch (stage)
    {
    case ROHAN_STAGE_PEACE:
        wpdesc = "There are currently no weapons in the racks.";
        break;
    case ROHAN_STAGE_HOSTILE:
        wpdesc = "All of the weapons appear to be fairly new. They have "+ 
           "been forged from some strange, black material and all display "+
           "a white hand somewhere on them.";
        break;
    case ROHAN_STAGE_WAR:
        wpdesc = "All of the weapons appear to be fairly new. They have "+ 
           "been forged from some strange, black material and all display "+
           "a white hand somewhere on them.";
        break;
    case ROHAN_STAGE_BATTLE:
        wpdesc = "Most of the weapons have been forged from a strange, "+ 
           "black material. Every weapon has the markings of Saruman's "+
           "army, a white hand, except the few that bare Rohirrim markings. "+
           "The weapons are somewhat chiped and worn down from battle.";
        break;
    case ROHAN_STAGE_DEFEAT:
        wpdesc = "Every weapon in the racks are worn down and blood-stained "+
           "from battle. Some Rohirrim weapons taken from fallen soldiers "+
           "sit along side the strange, black weapons bearing the emblem of "+
           "Saruman's army.";
        break;
    }
    return BSN(wpdesc);
}


string
armdesc()
{
    string amdesc;
    int    stage;

    stage = (Master->query_isen_stage());
    
    switch (stage)
    {
    case ROHAN_STAGE_PEACE:
        amdesc = "The armour racks are currently empty."; 
        break;
    case ROHAN_STAGE_HOSTILE:
        amdesc = "What little armour you see in the racks appear to be new "+
           "and forged from some strange, black material. Every piece of "+
           "armour displays the emblem of Saruman's army, a white hand.";
        break;
    case ROHAN_STAGE_WAR:
        amdesc = "Many different pieces of armour fill the racks now. All "+ 
           "are forged from a strange, black material and bear a white hand "+
           "on them somewhere.";
        break;
    case ROHAN_STAGE_BATTLE:
        amdesc = "The armour you can see in the racks have been beat up "+ 
           "and have some blood stains on them. All display a white hand "+
           "on them except a couple that have Rohirrim markings on them.";
        break;
    case ROHAN_STAGE_DEFEAT:
        amdesc = "Every piece of armour is dented and stained with blood. "+
           "Most display the symbol of Saruman's army, a white hand, except "+
           "the armours taken from fallen Rohirrim soldiers bearing Rohirrim "+
           "markings.";
        break;
    }
    return BSN(amdesc);
}

