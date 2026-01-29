/*     Vingaard Keep, coded by Percy
 *     Boardroom by Grace, 04/06/94 
 * modified for the New VK, Dec 7 1996 by Teth
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

/*prototype*/
void load_board();


void
create_vin_room()
{
    string str;
    set_short("Office of Vingaard Keep");
    set_long("This is the office of Vingaard Keep. A bulletin board " +
        "is available for people to post their concerns. A sign " +
        "is placed on one wall. Near the sign, a picture is hanging. " +
        "An exit leads back to the streets of Vingaard Keep to the " +
        "west.\n");
    AI(({"floor","wall","ceiling"}),"It is composed of solid and " +
        "sturdy volcanic rock, much like the rest of Vingaard Keep.\n");
    AI("walls","They are made of solid and sturdy volcanic rock.\n");
    AI(({"volcanic rock","rock","sturdy rock","solid rock"}),
        "It is most likely diorite or granite.\n");
    AI("picture","The picture is a painting of several faces. It " +
        "is obviously a masterpiece. A caption can be read below " +
        "the body of the picture.\n");
    ACI("caption","read","The caption reads:\n\n" +
        "This painting is dedicated to the builders of Vingaard Keep.\n" +
        "\nPictured here are:\n\n" +
        "Percy, Nick, Aridor, Grace, Morrigan and Teth.\n");
    AI(({"sign","whitened sign"}),"You can read this whitened sign.\n");
    ACI(({"sign","whitened sign"}),"read","The sign reads:\n\n" +
        "Visitors to Vingaard Keep are encouraged to place " +
        "<idea>s, <typo>s, <bug>s, and <praise>s. While in this " +
        "office, conversation should be kept to a minimum when " +
        "others are posting notes. Enjoy your stay in Vingaard " +
        "Keep.\n");
    
    AE(VROOM + "ws3", "west", 0);
    
    seteuid(getuid(TO));
    load_board();
    
}

/* This loads the main guild bulletin board */
void  
load_board()   
{ 
    clone_object(VOBJ + "off_board")->move(TO);
}   
 
