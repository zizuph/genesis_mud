/*
 *  Filename:       w_cattle.c
 *  Description:    This is a wagon for a typical caravan transport.
 *
 *  Copyright (c) Aug. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"


/* Item code, as we're dealing with items that will change on the
   different state of a burning wagon, they're made into functions
   that are called from the appropriate item */

string
cattle()
{

    string str;

    switch (BurnStep)
    {
        case 0..1:
        {
            str = "Fifteen strong looking cows are dragged behind " +
                  "the wagon they seem extremely healthy and fit for " +
                  "the journey.\n";
            break;
        }
        case 2:
        {
            str = "The cattle looks extremely uneasy and are mooing " +
                  "constantly in fear.\n";
            break;
        }
        case 3:
        {
            str = "The cattle are in a frenzy! the white showing in " +
                  "their eyes, foaming heavily trying to avoid the " +
                  "rising fire.\n";
                  break;
        }
        case 4:
        {
            str = "Some of the cattle are on fire, mooing in pain " +
                  "while others have managed to break free of their " +
                  "bindings, and are running away from the wagon in "+
                  "a wild stampede.\n ";
                  break;
        }
        case 5..100:
        {
            str = "There is some remains of smoking burned cattle.\n";
            break;
        }
    }

    return str;
}

string
hay()
{

    string str;

    switch (BurnStep)
    {
        case 0:
        {
            str = "The hay looks dried and fresh, perfect food for cattle.\n";
            break;
        }
        case 1..4:
        {
            str = "The hay on top of the wagon are burning, billowing heavy " +
                  "smoke after the wagon.\n";
                  break;
        }
        case 5..100:
        {
            str = "You find no hay.\n.";
            break;
        }
    }

    return str;
}

string
oxes()
{

    string str;

    switch (BurnStep)
    {
        case 0..2:
        {
            str = "Two strong oxes are pulling the wagon, they seem pretty  " +
                  "exhausted by the weight, foaming heavily around their " +
                  "mouths.\n ";
            break;
        }
        case 3:
        {
            str = "The strong oxes have sensed the heat from behind, and are " +
                  "trying to get out of their harness, thereby pulling the " +
                  " wagon harder and faster.\n";
                  break;
        }
        case 4:
        {
            str = "One of the oxes have caught fire, and are roaring in pain" +
                  ", the other are desperatly trying to break free of the " +
                  "harness.\n";
                  break;
        }
        case 5..100:
        {
            str = "In front of what used to be a wagon, lies the remains of " +
                  "two oxes.\n";
            break;
        }
    }

    return str;
}

string
skeleton()
{
    string str;

    switch (BurnStep)
    {
        case 0..4:
        {
            str = "You find no skeleton.\n";
            break;
        }
        case 5:
        {
            str = "This is the skeleton of what used to be the one driving " +
                  "the wagon.\n";
            break;
        }

    }

    return str;
}

string
wheels()
{

    string str;

    switch (BurnStep)
    {
        case 0..3:
        {
            str = "The big round wheels look sturdy and uncomfortable for " +
                  "the driver, as they bump over the road with big snaps " +
                  "into the wagon chassis. They are caked with dried mud, " +
                  "making it clear that the wagon has been used in the " +
                  "fields.\n";
            break;
        }
        case 4:
        {
            str = "The big round wheels look sturdy and uncomfortable for " +
                  "the driver, as they bump over the road with big snaps " +
                  "into the burning wagon chassis.\n";
            break;
        }
        case 5..100:
        {
            str = "Two stone wheels are lying in the remains of a what used " +
                  "to be a wagon.\n";
            break;
        }
    }

    return str;
}

string
farmer()
{

    string str;

    switch (BurnStep)
    {
        case 0..1:
        {
            str = "The farmer sits on top of the wagon, steering the wagon.  " +
                  "He looks strong and sunburned, from hard labouring in the " +
                  "fields.\n";
            break;
        }
        case 2:
        {
            str = "The driver are desperatly trying to put out the fire.\n";
            break;
        }
        case 3:
        {
            str = "The driver are screaming in pain, as the fire has leapt " +
                  "onto him.\n";
            break;
        }
        case 4:
        {
            str = "The driver have fallen on top of the wagon, in the " +
                  "middle of the flames, seemingly dead.\n";

            break;
        }
        case 5..100:
        {
            str = skeleton();
            break;
        }
    }

    return str;
}


string
remains()
{
    string str;

    switch (BurnStep)
    {
        case 0..4:
        {
            str = "You find no remains.\n";
            break;
        }
        case 5:
        {
            str = BurnMsg[BurnStep][WAGON_LONG];
            break;
        }

    }

    return str;
}



public string
carriage_short()
{
    if (BurnStep == 0)
        return "dirty farmer wagon";

    return BurnMsg[BurnStep][WAGON_SHORT];

}

public string
carriage_long()
{
    int     s;
    string  long_descf;

   if (BurnStep == 0)
       long_descf = "The dirty wagon is covered in mud, from long travels " +
                 "through the farm fields, cakes of old mud are being pulled " +
                 "around by big stone wheels. The wagon is being dragged by " +
                 "two strong oxes and some cattle are bound to the rear of it. " +
                 "On top of the wagon are some tools and a heap of " +
                 "bundled hay to feed the cattle with on long journeys.\n";

    if (BurnStep > 0)
        long_descf = BurnMsg[BurnStep][WAGON_LONG];

   return long_descf;
}

void
create_krynn_wagon()
{

    add_name( ({ "dirty farmer wagon" }) );
    set_adj(({ "dirty","farmer" }));
    set_pshort( "dirty farmer wagons"  );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_cattle", 0 } )) );

    //remove the wagon from the caravan at step 4
    BurnDamageTooMuch = 4;

    //and here is the burn messages,
    /* element 0 : Descriptions to say on each fire step, except if first
                   in mapping then ignition  message to player who does it only
       element 1 : wagon short
       element 2 : wagon long description
       element 3 : if first mapping then description of ignition to others
                   in the rooms
    */

    add_burn_msg( (( { "You touch the hay with the burning torch " +
                       "and it bursts into a heavily smoking fire.\n",
                       "burning " + TO->short(),
              "The dirty wagon is covered in mud, from long travels " +
              "through the farm fields, cakes of old mud are being pulled " +
              "around by big stone wheels. The wagon is being dragged by " +
              "two strong oxes and some cattle are bound to the rear of it. " +
              "On top of the wagon are some tools and a heap of " +
              "hay that are smoking somewhat.\n" ,
              " touches the hay with the burning torch " +
                       "and it bursts into a heavily smoking fire.\n" } )));
    add_burn_msg( (( { "With a loud crackling noise, the fire spreads " +
                       "to the rest of the hay on top of the wagon.\n",
                       "burning " + TO->short(),
              "The dirty wagon is covered in mud, from long travels " +
              "through the farm fields, cakes of old mud are being pulled " +
              "around by big stone wheels. The wagon is being dragged by " +
              "two strong oxes and some cattle are bound to the rear of it. " +
              "On top of the wagon a fire is spreading rapidly from hay" +
              "stack to haystack, trailing the wagon with a billowing heavy " +
              "smoke.\n" } )));
    add_burn_msg( (( { "The cattle behind the wagon starts panicking, " +
                       "trying to get loose from their ropes, while the " +
                       "fire consumes the wagon.\n",
                       "blazing farmer wagon",
              "The wagon is blazing with fire everywhere on top of it, " +
              "giving a huge billowing smoke trailing behind the wagon, " +
              "The wagon is being dragged by two strong oxes that are " +
              "starting to panick to get away from the fire. " +
              "The cattles bound behind the wagon are pulling in the other " +
              "direction trying to get out of their bindings.\n" } )));
    add_burn_msg( (( { "The painful moos from the cattle sounds in the air " +
                       "while some managed to escape, others are now engulfed " +
                       "in the flames that are burning down the wagon.\n",
                       "nearly burnt out farmer wagon",
              "The fire engulfing the wagon is starting to dwindle, " +
              "as it have already consumed most wooden parts of the wagon. " +
              "Behind the wagon, several corpses of burnt out cattles are " +
              "lying, smoking.\n" } )));
    add_burn_msg( (( { "The flames starts to dwindle, at the lack of more " +
                       "to burn.\n" ,
                       "remains of a burnt out farmer wagon",
              "The remains of this wagon, two stone wheels some metal ends " +
              "of farmer tools, and the skeleton of someone in what used to " +
              "be the driver seat on top of it " +
              "indicates this once was a farmer wagon.\n " } )));
}



public int
add_room_items()

{

    /* global items are added in left,right,front,back,rooms.
     items can be added to one of those instead with add_xxx_item */

    add_global_item(({ "cattle", "cows", "cow" }), cattle);
    add_global_item(({ "oxe", "oxes"}), oxes);
    add_global_item(({ "driver", "farmer"}), farmer );
    add_global_item(({ "hay", "bundles"}), hay);
    add_global_item(({ "wheels", "wheel", "stone wheels"}), wheels);
    add_global_item("skeleton", skeleton);
    add_global_item("remains", remains);

    /* add an item to the wagon */
    add_item("remains", remains);

}

void
init()
{
    ::init();
}

