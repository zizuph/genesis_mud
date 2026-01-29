//-*-C++-*-
// Additional leftover for The Worm of Avenir (tm)
// Skin pieces that can be turned to armours.
//
// Made by Boriska@Genesis, Sept 1994
// Skin cut from head can be turned to helmet, skin from body makes
// body armour  etc

inherit "/std/leftover";

#include <macros.h>
#include "/d/Avenir/include/worm.h"

mapping part_num = ([	HEAD_LEFTOVER  : 0,
            			BODY_LEFTOVER  : 1,
		            	TAIL_LEFTOVER  : 2,
		             	TOOTH_LEFTOVER : 3 ]);

// all this to allow use of switch statement below ( works on ints only)
static int acid, part;

void set_acid(int i)  {  acid = i;     } 
int  query_acid()     {  return acid;  }
int  query_part()     {  return part;  }

void
create_leftover()
{
    if ( !IS_CLONE )
	return;

    ::create_leftover();
    add_name(WORM_LEFTOVER_ID);
}

void
leftover_init(string organ, string race)
{
    part = (int)part_num[organ];
    set_name(organ);

    switch (part)
    {
    case HEAD :
	set_adj("mottled");
	break;
    case BODY :
	set_adj("scaled");
	break;
    case TAIL :
	set_adj("round");
	break;
    case TOOTH:
	set_adj("white");
	break;
    default   :  // should never come here.
	set_adj("usual");
    }

    set_short(0);
    set_long("@@my_long@@");
}

string
my_long()
{
    string str;

    switch (part)
    {
    case HEAD :
	str = "Piece of mottled skin with stains of unknown liquid on it.";
	break;
    case BODY :
	str = "This skin covered with scales is unusually light for its size.";
	break;
    case TAIL :
	str = "Round-shaped fragment of patched hard skin.";
	break;
    case TOOTH:
	str = "This milk-white sharp tooth is gleaming with unearthly light.";
	break;
    default   :  // should never come here.
	str = "You cannot tell much about this strange looking piece of skin.";
	break;
    }

    if (acid)
	str += " The surface appears to be a bit corroded.";

    return str +"\n";
}
