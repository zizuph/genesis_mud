/*
 *  Include file for the BREWCRAFT daemon
 *  for the Iron Delving Brewery serving
 *  Ansalon and Krynn and anywhere else
 *  /d/Ansalon/common/brewcraft/brewcraft.c
 *  /d/Ansalon/common/brewcraft/brewcraft.h
 *
 *  Vitwitch 01/2021
 */

#ifndef _BREWCRAFT_
#define _BREWCRAFT_

#ifndef BREWCRAFT
#define BREWCRAFT "/d/Ansalon/common/brewcraft/brewcraft"
#endif

#define BEERTASTES ({ "hops and malted barley", \
                      "bitterness", \
                      "smoky flavour", \
                      "tangy tones", \
                      "juniper notes", \
                      "wheat and salt besides", \
                      "malted full body", \
                      "thickness on the palate" })

#define BEERTYPES ({ "ale", "bitter", "rauchbier", "dunkel", \
                     "sahti", "gose", "porter", "stout" })

#define BEERCOLOURS ({ "amber", "brown", "dark brown", "brown", \
                       "light brown", "red", "dark brown", "black" })

/* FUNCTIONS for calling by brewcrafter, venues and objects */

// Defaults calls to be used by all general venues and drinks

#define BREWCRAFT_MENU (BREWCRAFT->brewcraft_menuentry())
#define BREWCRAFT_SHORT (BREWCRAFT->brewcraft_short())
#define BREWCRAFT_LONG (BREWCRAFT->brewcraft_long())
#define BREWCRAFT_SMELL (BREWCRAFT->brewcraft_beer_smell())
#define BREWCRAFT_ALIGN (BREWCRAFT->brewcraft_brewer_align())
#define BREWCRAFT_SCORE (BREWCRAFT->brewcraft_brew_score())
#define BREWCRAFT_STYLE (BREWCRAFT->brewcraft_brew_type())
#define BREWCRAFT_TASTE (BREWCRAFT->brewcraft_beer_taste())
#define BREWCRAFT_AFTERTASTE (BREWCRAFT->brewcraft_beer_aftertaste())

#define BREWCRAFT_EXP_ROYALTY(x) (BREWCRAFT->brewcraft_export_royalty(x))
#define BREWCRAFT_CHP_ROYALTY(x) (BREWCRAFT->brewcraft_champions_royalty(x))

#define BREWCRAFT_TIERLIST (BREWCRAFT->brew_list())
#define BREWCRAFT_STYLELIST (BREWCRAFT->type_list())
#define BREWCRAFT_BREWERLIST (BREWCRAFT->brewer_list())

#define BREWCRAFT_NAME (BREWCRAFT->brewcraft_brewer_name())
#define BREWCRAFT_QUESTER (BREWCRAFT->brewcraft_export_quester())

// Other calls

#define BREWCRAFT_MENUG (BREWCRAFT->brewcraft_menuentry(1))
#define BREWCRAFT_SHORTG (BREWCRAFT->brewcraft_short(1))
#define BREWCRAFT_LONGG (BREWCRAFT->brewcraft_long(1))
#define BREWCRAFT_SMELLG (BREWCRAFT->brewcraft_beer_smell(1))
#define BREWCRAFT_ALIGNG (BREWCRAFT->brewcraft_brewer_align(1))
#define BREWCRAFT_SCOREG (BREWCRAFT->brewcraft_brew_score(1))
#define BREWCRAFT_STYLEG (BREWCRAFT->brewcraft_brew_type(1))
#define BREWCRAFT_TASTEG (BREWCRAFT->brewcraft_beer_taste(1))
#define BREWCRAFT_AFTERTASTEG (BREWCRAFT->brewcraft_beer_aftertaste(1))
#define BREWCRAFT_NAMEG (BREWCRAFT->brewcraft_brewer_name(1))
#define BREWCRAFT_RACEG (BREWCRAFT->brewcraft_brewer_race(1))
#define BREWCRAFT_COLOURG (BREWCRAFT->brewcraft_beer_colour(1))

#define BREWCRAFT_MENUB (BREWCRAFT->brewcraft_menuentry(2))
#define BREWCRAFT_SHORTB (BREWCRAFT->brewcraft_short(2))
#define BREWCRAFT_LONGB (BREWCRAFT->brewcraft_long(2))
#define BREWCRAFT_SMELLB (BREWCRAFT->brewcraft_beer_smell(2))
#define BREWCRAFT_ALIGNB (BREWCRAFT->brewcraft_brewer_align(2))
#define BREWCRAFT_SCOREB (BREWCRAFT->brewcraft_brew_score(2))
#define BREWCRAFT_STYLEB (BREWCRAFT->brewcraft_brew_type(2))
#define BREWCRAFT_TASTEB (BREWCRAFT->brewcraft_beer_taste(2))
#define BREWCRAFT_AFTERTASTEB (BREWCRAFT->brewcraft_beer_aftertaste(2))

#define BREWCRAFT_MENUZ (BREWCRAFT->brewcraft_menuentry(3))
#define BREWCRAFT_SHORTZ (BREWCRAFT->brewcraft_short(3))
#define BREWCRAFT_LONGZ (BREWCRAFT->brewcraft_long(3))
#define BREWCRAFT_SMELLZ (BREWCRAFT->brewcraft_beer_smell(3))
#define BREWCRAFT_ALIGNZ (BREWCRAFT->brewcraft_brewer_align(3))
#define BREWCRAFT_SCOREZ (BREWCRAFT->brewcraft_brew_score(3))
#define BREWCRAFT_STYLEZ (BREWCRAFT->brewcraft_brew_type(3))
#define BREWCRAFT_TASTEZ (BREWCRAFT->brewcraft_beer_taste(3))
#define BREWCRAFT_AFTERTASTEZ (BREWCRAFT->brewcraft_beer_aftertaste(3))
#define BREWCRAFT_NAMEZ (BREWCRAFT->brewcraft_brewer_name(3))

#endif _BREWCRAFT_
