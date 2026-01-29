/* Vingaard Keep coded by Percy. */
/* redone by Teth and Morrigan Jan 97 */

#include "../../guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

void load_board();

public void
create_vin_room()
{
    set_short("Applications Den");
    set_long("This is a small den, nestled to the west of the main " +
        "entrance room of the Solamnian guild hall. A bulletin board " +
        "displays notes of persons applying for membership into the " +
        "Knights of Solamnia guild. A small sign hangs from one wall. " +
        "A lamp hanging from the ceiling lights the room.\n");
    AI(({"ceiling","floor","wall"}),"It is constructed of granite.\n");
    AI("granite","A crystalline volcanic rock.\n");
    AI("walls","They are constructed of granite.\n");
    AI(({"lamp","hanging lamp"}),"It is too high for you to reach most " +
        "likely. It illuminates the room.\n");
    ACI(({"lamp","hanging lamp"}),({"reach","get"}),"It is too high for " +
        "you to reach it.\n");
    AI(({"small sign","sign"}),"The sign has black letters on a white " +
        "background.\n");
    ACI(({"small sign","sign"}),"read","The sign reads:\n\n"+
        "If you are searching for a sponsor into the Knights of Solamnia " +
        "guild, be forewarned that the virtues of patience and loyalty " +
        "are required. Please ensure that you have read the book on the " +
        "podium in the entrance room. If you are satisfied that the " +
        "harsh life of a Solamnian Knight is for you, feel free to " +
        "write a descriptive note about yourself on this board. " +
        "It is common practice to explain who you are, and why you " +
        "feel the Knights of Solamnia guild is the one for you.\n");
    AI("entrance room","It rests to the east.\n");    
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
        "teleportation in this area... or is it something else?\n");

    AE(VROOM + "joinroom.c", "east", 0);
    
    seteuid(getuid(TO));
    load_board();
}

/* This loads the main squires bulletin board */
void
load_board()
{
  clone_object(VOBJ + "sqboard")->move(TO);
}
