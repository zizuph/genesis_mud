/* room2.c
   Mort 911004 
   Added Herbs  -- Tomas Dec 1999
*/


#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";


#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

string frm;

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {

    set_short("path along the moor");
    set_long("This path leads between the main road and the "+
        "desolate highland moor. "+ 
	    "It cuts down through the bushes and heather " +
        "into the rocky moors whose edge is marked by a tall "+
        "black obelisk to the southeast. You can glimpse icy "+
        "hills and blizard-like conditions uphill to the northwest. " +
		"@@long_desc@@");
    add_exit("/d/Terel/common/road/road10", "northwest",0);
    add_exit("moor_edge", "southeast", 0);
 
   add_item(("heather"),"The ground is covered in it.\n");
   add_item(({"shrubs","bushes"}),"Small bushes and shrubs litter the area.\n");
   add_item(({"hill","hills","moor"}),"Rolling hills covered in mist.\n");
   add_item(({"obelisk"}), "It is located southeast of here.\n");

   set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                    ONE_OF_LIST(FROST_HERBS),
                    ONE_OF_LIST(FROST_HERBS),
                 }),
                 ({"bushes","shrubs"}) , 
                     3 );
 
  reset_room();



}

/*
 * Function name:
 * Description  :
 */

long_desc()
{
    if (frm == "/d/Terel/common/moor/main/moor_edge")
        return "You feel glad to be leaving the trolls behind!\n";
    return "The trolls live further southeast, so " +
                "maybe you should turn back!\n";
}

enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (living(ob))  {
             frm = file_name(from);
         }
}
