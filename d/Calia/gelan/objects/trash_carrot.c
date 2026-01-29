

/*      This is an object in a Gelan trash heap

    coder(s):  Maniac 
    history:
                12/4/98    rabbit -> gopheroo                Maniac
                24.1.95    Modified on quest change          Maniac
                19.9.94    Created                           Maniac

    quests:     This object is a carrot that can be used to make 
                the gopheroo in the Gelan gopheroo catching quest
                docile enough to pick up for a short while. 

    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "object.h"
#include GOPHEROO_QUEST


int condition;   /* 0 for bad, 1 for good */

void
set_good_condition()
{
    condition = 1;
}


int
query_condition()
{ 
    return condition;
}


string
long_desc()
{
    string str1, str2;

    str1 =
      "An old, bedraggled looking carrot that nobody wanted to eat.";

   if (this_player()->query_skill(SS_AWARENESS) >= 25) 
     if (condition)
        str2 = " It seems to be in reasonable condition.. for trash.\n";
     else
        str2 = " It is in bad condition, it looks rotten in fact.\n";
   else
        str2 = "\n";

   return (str1 + str2); 
}


string
fail_catch()
{
  return "The gopheroo sniffs tentatively at the carrot and " 
       + "wrinkles its little nose, apparently in disgust. " 
       + "Oh dear, that carrot must have been rotten.\n"; 
}



void
special_effect(int num)
{
  this_player()->catch_msg("Eating carrots from a trash heap? " +
                          "You're sick!\n");
}


void
create_food()
{
    set_name("carrot");
    add_name(CARROT_NAME);
    set_adj(({"old", "bedraggled" }) );
    set_short("old bedraggled carrot");
    set_pshort("old bedraggled carrots"); 
    set_long("@@long_desc");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(1);
    condition = 0;
}

