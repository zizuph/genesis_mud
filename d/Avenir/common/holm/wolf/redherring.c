// -*-C++-*-
// file name: redherring.c	
// creator(s): Sirra
// last update:	June 27, 1998
// purpose: found when player searches the bones in the
//		apothacary. Used as a "red-herring" for players
//		who are looking for a wolf bone.

// note:	Coding style, format, and structure were copied
//		from Lilith's /d/Avenir/common/obj/feather.c 
// bug(s):
// to-do:     

inherit "/std/object";
#include <language.h>
#include <stdproperties.h>
#include "wolf.h"


string anim;
string bon;
string randanim();
string randbone();
void set_anim(string str) {	 anim = str;   }
void set_bone(string str) {    bon = str;    }

void
init_the_bone()
{
    if (!bon) bon = randbone();
    if (!anim) anim = randanim();

    set_short(""+ anim + " bone");
    set_long("This is a "+ bon +" bone from "+
        "what was most likely " + LANG_ADDART(anim) + ".\n");
    add_name(anim +" bone");
    set_adj(({ anim }));

    return;        
}

/*************** Creation ************/
void
create_object()
{
   init_the_bone();
   add_name(({"_red_herring"}));
   set_name("bone");

   add_prop(OBJ_I_VOLUME, 50);   
   add_prop(OBJ_I_WEIGHT, 200);
}             

string
randbone()
{
    string str;

    switch(random(7))
    {   
        case 0: str="femur";       break;
        case 1: str="skull";       break;
        case 2: str="vertebra";    break;
        case 3: str="toe";         break;
        case 4: str="pelvic";      break;
        case 5: str="mandible";    break;
        case 6: str="rib";         break;
    }
    return str;                                                                               
}

string
randanim()
{
    string str;

    switch(random(10))
    {
	case 0: str="bird";		break;
	case 1: str="monkey";		break;
	case 2: str="tiger";		break;
	case 3: str="owl";		break;
	case 4: str="goblin";		break;
	case 5: str="human";		break;
	case 6: str="dwarf";		break;
	case 7: str="cat";		break;
	case 8: str="bat";		break;
	case 9: str="dog";		break;
    }

    return str;
}	
