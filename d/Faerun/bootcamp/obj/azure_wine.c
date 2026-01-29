/*
*
* Clyptas 2017 Azure wine
*
*/

#pragma strict_types

inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>


#define BS(message)     break_string(message, 75)
#define TP              this_player()
#define wineskin        this_object()
#define QPO       		query_possessive()


void
create_drink()
{
    set_name("wineskin");
	set_adj("full");
	
	add_cmd_item(({ "skin" }), ({ "wine" }), ({ "You hold the wineskin.\n" }));	
	  

set_long("A container made of cured rothe skin, that is corked. It appears " + 
     "to be full of azure wine, a glowing blue drink favoured among the drow.\n");
	 
(OBJ_S_SEARCH_FUN, "search_for_wineskin","search_for_wine");

set_drink_msg(" You uncork the wineskin and peer curiously at the glowing " +
       "blue liquid within. You lift the skin to your lips and take a  " +
	   "drink.\n");
 /* say(" drinks " +TP->QPO+ "You close your eyes at the sweet, crisp taste of " +
     "wine as it slides down your throat. You open your eyes and you see " +
	 "things more vivid than they were before.\n"); */
	 
}