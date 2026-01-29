/*
 *  Filename:       w_conestoga.c
 *  Description:    This is a wagon for a typical caravan transport.
 *                  the wagon can be altered in several ways making it,
 *                  used many times in the same caravan.
 *
 *  Copyright (c) Okt. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *
 *  Wagon is inspired from the webpage:
 *  http://www.endoftheoregontrail.org/wagons.html
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"
#include <language.h>

string *wagon_adj1 = ({ "heavy", "large", "wide", "boat-shaped",
  "huge", "big", "wooden", "impressive", "sturdy" });
string *wagon_adj2 = ({ "conestoga", "prairie", "bonnet", "cargo",
  "transport" });

string adj1,adj2;

/* between 4 and 16 steeds drags the wagon */
int amount_dragging;
/* mules, horses or oxes are dragging the wagon */
int race_steeds;

/* help functions for the wagon */

string
wagontype_label()
{
    switch (wagontype)
    {
        case WAGON_FLETCHER:
            return "The word " +
                   "'Fl tcher' are still barely readable on the side " +
                   "of the bonnet.\n";
        case WAGON_ALCHEMIST:
            return "There is painted " +
                   "'Old Grahams mixture & salt' with big black letters " +
                   "on each side of the bonnet.\n";
        case WAGON_WEAPONRY:
            return "On the side of the bonnet there is a painting of two " +
                   "swords crossing eachother.\n";
        case WAGON_ARMOURY:
            return "On each side of the bonnet there is a painting of " +
                   "a big heavily armoured soldier with each and every " +
                   "piece of armour very accurately depicted.\n";
        case WAGON_INN:
            return "In ancient types there is painted the words " +
                   "'Big Bills Booze and Liquor' with a smaller " +
                   "inscription below stating 'Booze is healthy for the " +
                   "soul'\n";
        case WAGON_BUTCHER:
            return "'We hack'n'slash your meat' is written on the side of " +
                   "the bonnet.\n";
        default:
            return "";
    }
}
string
steed_race_name()
{
    switch (race_steeds)
    {
        case 0..1:
            return "mules";
        case 2:
            return "horses";
        case 3:
            return "oxes";
        default:
            return "mules";
    }
}


public string
carriage_short()
{
    return adj1 + " " + adj2 + " wagon";
}

/* long and short descriptions */

public string
carriage_long()
{
    string long_descf;

   long_descf ="The " + adj2 + " wagon is large and heavy its bed shaped " +
      "somewhat like a boat with angled ends and a floor that slopes " +
      "to the middle so barrels won't roll out when the wagon climbs " +
      "or descends a hilltop. It has a watertight canvas bonnet that " +
      "shelters the passengers and cargo from the weather. ";

   long_descf += wagontype_label();
   long_descf +=   "The wagon is pulled by " +
      LANG_NUM2WORD(amount_dragging) + " " + steed_race_name() + ", " +
      "making it able to load ";

   switch (amount_dragging)
   {
       case 4:
       {
           long_descf += "a ton of cargo";
           break;
       }
       case 5..8:
       {
           long_descf += "a moderate amount of cargo";
           break;
       }
       case 9..12:
       {
           long_descf += "quite alot of cargo, about 4 tons";
           break;
       }
       case 13..16:
       {
           long_descf += "an impressive amount of cargo";
           break;
       }
   }

   switch (steed_race_name())
   {
       case "mules":
       {
           long_descf += ", altho it is unable of making too long journeys " +
                         "as it would kill the mules before arrival.\n";
           break;
       }
       case "horses":
       {
           long_descf += ", altho it is unwise to make too long journeys " +
                         "as it would kill some of the horses before " +
                         "arrival.\n";
           break;
       }
       case "oxes":
       {
           long_descf += ". The oxes looks strong and fit, even for the " +
                         "longest of travels.\n";
           break;
       }
   }

   return long_descf;
}

/* ITEMS ON THE WAGON */
string
cattle()
{
    string str;
    str = "Some steeds dragging the wagon.\n";
    return str;
}

string
bonnet()
{
    string str;
    str = "Hardwood bows holds up the heavy, brown bonnet. The bows " +
          "soaked so the wood is pliable, bent into U-shapes, " +
          "and allowed to dry. They hold their shape if this is done " +
          "properly, which is important as if the wagon bows are under " +
          "too much tension, they could spring loose and tear the bonnet " +
          "while the wagon is jostled and jounced over rough terrain.\n" +
          "The bonnet itself is homespun cotton doubled over to make " +
          "it watertight. The bonnet is well-secured against the wind, " +
          "and its edges overlaps in back to keep out rain and dust. " +
          "It is also angled outward at the front and back, to lend some " +
          "additional protection to the wagon's interior.\n";
    str += wagontype_label();
    return str;
}

string
box()
{
    string str;
    str = "The wagon box, or bed, is made of hardwoods to resist " +
          "shrinking in the dry air of the plains and deserts " +
          "the wagon have to cross. It is 2 to 3 feet deep, and with " +
          "a bit of tar it is easily be rendered watertight and able to " +
          "float across slow-moving rivers. The side boards are beveled " +
          "outwards to keep rain from coming in under the edges of the " +
          "bonnet and to help keep out river water. The box sits upon " +
          "two sets of wheels of different sizes.\n";

    return str;
}

string
sideboard()
{
    string str;
    str = "The sideboards are beveled outwards to keep rain from coming " +
          "in under the bonnet.\n";
    return str;
}

string
wheel()
{
    string str;

    str = "The box sits upon two sets of wheels of different sizes, " +
          "the rear wheels are about 50 inches in diameter, while the " +
          "front wheels are about 44 inches in diameter. The smaller front " +
          "wheels allows for a little extra play, letting the wagon take " +
          "slightly sharper turns than it would otherwise have been able to " +
          "negotiate without necessitating a great deal of extra carpentry " +
          "work to keep the bed level. All four wheels have iron tires " +
          "to protect the wooden rims, and they are likewise constructed " +
          "of hardwoods to resist shrinkage.\n" +
          "The hardwood wheels are soaked in water to avoid them to shrink " +
          "in the heat, which would make the iron tires roll off.\n";

    return str;

}

string
brake()
{
    string str;
    str =  "The brake lever is located so it can be pressed by the " +
           "driver's foot or thrown by someone walking alongside the " +
           "wagon, and it is ratcheted so the brake block will remain " +
           "set against the wheel even after pressure is taken off the " +
           "lever.\n";
    return str;
}


/* wagon creation functions */


void
create_krynn_wagon()
{

    adj1 = wagon_adj1[random(sizeof(wagon_adj1))];
    adj2 = wagon_adj2[random(sizeof(wagon_adj2))];
    amount_dragging = random(16);
    if (amount_dragging < 4)
        amount_dragging = 4;

    race_steeds = random(3);
    set_wagontype(0);

    add_name( ({ adj1 + " " + adj2 +  " wagon" }) );
    set_adj(({ adj1, adj2}));
    set_pshort(adj1 + " " + adj2 + " wagons");

}

public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    switch (wagontype)
    {

        case WAGON_FLETCHER:
            add_mapping (R_WAGON, (( { WAGON + "wr_fletcher", 0 } )) );
            break;
        case WAGON_ALCHEMIST:
            add_mapping (R_WAGON, (( { WAGON + "wr_alchemist", 0 } )) );
            break;
        case WAGON_WEAPONRY:
            add_mapping (R_WAGON, (( { WAGON + "wr_weapons", 0 } )) );
            break;
        case WAGON_ARMOURY:
            add_mapping (R_WAGON, (( { WAGON + "wr_armours", 0 } )) );
            break;
        case WAGON_INN:
            add_mapping (R_WAGON, (( { WAGON + "wr_inn", 0 } )) );
            break;
        case WAGON_BUTCHER:
            add_mapping (R_WAGON, (( { WAGON + "wr_butcher", 0 } )) );
            break;
        default:
            add_mapping (R_WAGON, (( { WAGON + "wr_armours", 0 } )) );
            break;
    }
}


public int
add_room_items()
{
    add_global_item( steed_race_name() , cattle);
    add_global_item( "bonnet", bonnet);
    add_global_item(({ "box", "bed" }), box);
    add_global_item("sideboards", sideboard);
    add_global_item(({"wheel", "wheels"}), wheel);
    add_global_item(({"lever" ,"brake"}), brake);

}


void
init()
{
    ::init();
}

