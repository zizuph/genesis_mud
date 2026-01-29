/*
 *  IGARD_LIB + "tapestry_funcs.c"
 *
 *  Functions for the non-quest tapestries in Isengard.
 *
 *  Last modified by Alto, 01 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

/* PROTOTYPES */

public string       tapestry_colour();
public string       tapestry_condition();
public string       tapestry_metal();
public string       tapestry_weave();
public string       tapestry_cleanliness();

public string
tapestry_colour() 
{
   string *tapcolour = ({"blue", "green", "red", "violet", "yellow"});
   return ONE_OF_LIST(tapcolour);
}


public string
tapestry_condition() 
{
   string *tapcondition = ({"faded", "dull", "bright", "fresh"});
   return ONE_OF_LIST(tapcondition);
}


public string
tapestry_metal() 
{
   string *tapmetal = ({"gold", "silver", "bronze", "copper", "yellow"});
   return ONE_OF_LIST(tapmetal);
}



public string
tapestry_weave() 
{
   string *tapweave = ({"tight", "loose", "ragged", "frayed", "wide"});
   return ONE_OF_LIST(tapweave);
}


public string
tapestry_cleanliness() 
{
   string *tapcleanliness = ({"dirty", "clean", "dusty", "tangled", "shiny"});
   return ONE_OF_LIST(tapcleanliness);
}


