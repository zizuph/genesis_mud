/*
 *  Filename:       w_merchant.c
 *  Description:    This is a wagon for a typical caravan transport.
 *
 *  Copyright (c) Sep. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"


/* Item code, as we're dealing with items that will change on the
   different state of a burning wagon, they're made into functions
   that are called from the appropriate item */

string
wheels()
{

    string str;

    switch (BurnStep)
    {
        case 0..3:
        {
            str = "The big spoked iron wheels looks sturdy and able of long " +
                  "travels. They are running smoothly around, in a steady " +
                  "lulling speed.\n ";
            break;
        }
        case 4:
        {
            str = "The spoked iron wheels have collapsed " +
                  "beneath the burned frame of the wagon.\n";

            break;
        }
        case 5..100:
        {
            str = "Two sets of spoked iron wheels are lying in the remains " +
                  "of a what used to be a wagon.\n";
            break;
        }
    }

    return str;
}

string
canvas()
{

    string str;

    switch (BurnStep)
    {
        case 0:
        {
            str = "A dirty canvas is stretched tight over the top of the " +
                  "wagon, sheltering most of the inside against the weather " +
                  ".\n ";
            break;
        }
        case 1:
        {
            str = "A burning canvas is stretched tight over the top of the " +
                  "wagon, sheltering most of the inside against the weather" +
                  "is is on fire in the front end.\n";

            break;
        }
        case 2:
        {
            str = "A flaming canvas is stretched tight over the top of the " +
                  "wagon, burning heavily.\n";
            break;
        }
        case 3..100:
        {
            str = "You find no canvas.\n";
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
driver()
{

    string str;

    switch (BurnStep)
    {
        case 0..1:
        {
            str = "The merchant sits on top of the wagon, steering the wagon." +
                  "\n. He looks determined.\n";
            break;
        }
        case 2:
        {
            str = "The driver are desperatly trying to put out the fire.\n";
            break;
        }
        case 3:
        {
            str = "The driver engulfed in the flames, are screaming in pain.\n";
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
        return "heavy broad-wheeled wagon";

    return BurnMsg[BurnStep][1];

}

public string
carriage_long()
{
    int     s;
    string  long_descf;

   if (BurnStep == 0)
       long_descf =
        "It's a heavy, broad-wheeled wagon, looking more like a huge " +
        "rectangular box. The sturdy wooden conveyance rolling on four " +
        "spoked iron wheels that are as tall as the cargo box between " +
        "them, at least six feet off the ground. The cargo box has " +
        "wooden sides reinforced with thick bands of iron. There is a "+
        "dirty canvas stretched tight over the top of the wagon.\n";


    if (BurnStep > 0)
        long_descf = BurnMsg[BurnStep][2];

   return long_descf;
}

void
create_krynn_wagon()
{

    add_name( ({ "heavy broad-wheeled wagon" }) );
    set_adj(({ "heavy","broad-wheeled", "merchant" }));
    set_pshort("heavy broad-wheeled wagons");

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_merchant", 0 } )) );

    //remove the wagon from the caravan at step 4
    BurnDamageTooMuch = 4;

    //and here is the burn messages,
    add_burn_msg( (( { "As You touch the dirty canvas with the burning torch" +
                       ", the canvas starts to burn slowly.\n",
                       "burning " + TO->short(),
        "It's a heavy, broad-wheeled wagon, looking more like a huge " +
        "rectangular box. The sturdy wooden conveyance rolling on four " +
        "spoked iron wheels that are as tall as the cargo box between " +
        "them, at least six feet off the ground. The cargo box has " +
        "wooden sides reinforced with thick bands of iron. There is a "+
        "slightly burning dirty canvas stretched tight over the top of the " +
        "wagon.\n",
        " touches the dirty canvas with the burning torch and " +
                       "the canvas starts to burn slowly.\n"        } )));
    add_burn_msg( (( { "With a loud crackling noise, the fire spreads " +
                       "to the rest of the stretched out canvas on top of "+
                       "the wagon.\n",
                       "burning " + TO->short(),
        "It's a heavy, broad-wheeled wagon, looking more like a huge " +
        "rectangular box. The sturdy wooden conveyance rolling on four " +
        "spoked iron wheels that are as tall as the cargo box between " +
        "them, at least six feet off the ground. The cargo box has " +
        "wooden sides reinforced with thick bands of iron. There is a "+
        "burning dirty canvas stretched tight over the top of the " +
        "wagon, billowing dark clouds of smoke behind the wagon.\n"} )));
    add_burn_msg( (( { "A small explosion on top of the wagon makes the " +
                       "fire spread more rapidly up and down the cargo box " +
                       "to the wooden boxes on top of it.\n",
                       "flame-engulfed wagon",
              "A blazing fire on top of the wagon spreads everywhere on top " +
              "of it, giving a huge billowing smoke trailing behind the " +
              "wagon.\n The cargo box are sending out small explosions, each "+
              "time a new box gets burned through.\n "} )));
    add_burn_msg( (( { "The painful screams from the front of the wagon " +
                       "sounds like someone got caught in the fire, that " +
                       "engulfs the wagon.\n",
                       "inferno-engulfed broad-wheeled wagon",
              "The fire engulfing the wagon is peaking, " +
              "the wheels have collapsed beneath the wagon, burning " +
              "wildly.\n The once so fine cargo box, are now burnt through, " +
              "littering the ground with burning boxes.\n" } )));
    add_burn_msg( (( { "The flames starts to dwindle, at the lack of more " +
                       "to burn.\n" ,
                       "remains of a burnt out heavy broad-wheeled wagon",
              "The remains of this wagon, two sets of spoked iron wheels,  " +
              "some halfburned boxes, and the skeleton of someone in what " +
              "used to be the driver seat on top of it.\n " } )));
}

public int
add_room_items()
{
    /* global items are added in left,right,front,back,rooms.
     items can be added to one of those instead with add_left_item */

    add_global_item( "driver" , driver );
    add_global_item(({ "wheels", "wheel", "iron wheels"}), wheels);
    add_global_item("canvas", canvas);
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

