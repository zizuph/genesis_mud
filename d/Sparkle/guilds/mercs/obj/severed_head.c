/* Severed head of a player, or npc.
 
 * Much of this code is based upon /std/corpse.c
 * Code (c) 2001 to Damian Horton, BKA casimir.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "std/leftover";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

//global variables
string Met_Name; //The met_name of the creature whose head this is.
string Nonmet_Name; //The nonmet_name of this head.

//prototypes
string short_func();
string pshort_func();
string long_func();

nomask void
create_leftover()
{
    Met_Name = "default";
    Nonmet_Name = "default";

    set_name("head");
    add_name("leftover");
    set_adj("severed");  
}

/* Args: object - The living being whose severed head this shall be.

   Sets various properties and variables in the severed head, as per the
   living being whose head this is.
*/
 
void
config(string metname, string nonmetname)
{ 
    Met_Name = metname;
    Nonmet_Name = nonmetname;

    // stuffed corpses retain the weight and volume of the original
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
    
    add_name("head of " + Met_Name);
    add_name("head of " + Nonmet_Name);

    set_short(&short_func());
    set_pshort(&pshort_func());
    set_long(&long_func());  
    
    leftover_init("skull", "unknown");
}

/* VBFC for the short description of the severed head.
   Essentially copied from corpse.c
*/

string
short_func()
{
    object pob;

    pob = vbfc_caller();
    if (!pob || !query_ip_number(pob) || pob == this_object())
        pob = previous_object(-1);
    if (!pob || !query_ip_number(pob))
	pob = this_player();
    if (pob && pob->query_real_name() == lower_case(Met_Name))
	return "severed head of yours truly";
    else if (pob && pob->query_met(Met_Name))
	return "severed head of " + capitalize(Met_Name);
    else
	return "severed head of " + LANG_ADDART(Nonmet_Name);
}

/* VBFC for the plural short description of severed heads.
   Again more or less copied from that in /std/corpse.c
*/
string
pshort_func()
{
    object pob;
 
    pob = vbfc_caller();
    if (!pob || !query_ip_number(pob) || pob == this_object())
        pob = previous_object(-1);
    if (!pob || !query_ip_number(pob))
	pob = this_player();
    if (pob && pob->query_real_name() == lower_case(Met_Name))
	return "severed heads of yours truly";
    else if (pob && pob->query_met(Met_Name))
	return "severed heads of "  + capitalize(Met_Name);
    else
	return "severed heads of " + LANG_PWORD(Nonmet_Name);
}

/* VBFC function for the long description of a severed head.
   More or less copied from the similiar function in
   /std/corpse.c
*/

string
long_func()
{
    object pob;

    pob = vbfc_caller();
    if (!pob || !query_ip_number(pob) || pob == this_object())
	pob = this_player();
    if (pob->query_real_name() == lower_case(Met_Name))
	return "This is your own severed head!\n"; 
    if (pob->query_met(Met_Name))
	return "This is the severed head of " + capitalize(Met_Name) +
	    ".\n";
    else
	return "This is the severed head of " + LANG_ADDART(Nonmet_Name) + 
	    ".\n";
}




