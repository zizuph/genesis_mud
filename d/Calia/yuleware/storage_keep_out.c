// OBJECT:  storage room  (KEEP OUT)

    /* Calia Domain

    HISTORY

    [2002-01-12] Created by Uhclem from [C:\CALIA\HOLIDAY.DOC].

    PURPOSE

    This room is used to store yule items which must e ket out of the hands of
    mortals.  They should also be kept out of the hands of wizards except when
    an emergency repair is necessary, so the rule is:

    STAY OUT OF THIS ROOM AND DO NOT TOUCH, MOVE, OR OTHERWISE EXERT ANY
    INFLUENCE ON THE ITEMS HERE UNLESS YOU KNOW WHAT YOU'RE DOING!

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

// FUNCTIONS

// OBJECT DEFINITION

void
create_room()

{

    set_long("CAUTION: SECURE STORAGE ROOM. DO NOT ENTER UNLESS YOU ARE" +
        " FIXING A PROBLEM WITH CALIA HOLIDAY ITEMS. ALTERING" +
        " ANYTHING HERE MAY CAUSE FAILURE OF HOLIDAY ITEMS!\n");

    set_short("STORAGE ROOM - DO NOT TOUCH ANYTHING WITHOUT AUTHORIZATION!");

    add_exit("/w/uhclem/workroom", "out", 0);

}
