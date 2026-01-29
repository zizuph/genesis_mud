/*
 * Header file for potions
 * -- Finwe, February 2007
 */

#define NOV_S_MORTAR    "_nov_potions_mortar"

 /*
  * This is the definition mapping for potions made in a mortar and 
  * used gamewide. The default mortar is /d/Genesis/std/potions/mortar.c.
  *
  * These definitions are setup in /d/Faerun/domain_link.c and used in 
  * check_potion_ingr()
  *
  * Arguments:  min alco content of drink,                
  *             min soft content of drink,                
  *             array of required herbs (file name)       
  *             array of required heaps (file name)       
  *             array of required other ingredients (name)
  *             file of potion to clone
  */

#define FAERUN_POTION_INGREDIENTS   ([ \
    "otawine"   :   ({50, 50,   ({"/d/Gondor/common/herbs/red_pepper", \
                                  "/d/Gondor/common/herbs/clove", }), \
                    ({}), ({}), \
                        "/d/Faerun/guilds/nov/obj/potion2"}), \
    "chrimin"   :   ({50, 50,   ({"/d/Gondor/common/herbs/myrtle", \
                                  "/d/Gondor/common/herbs/rosemary", }), \
                    ({}), ({}), \
                        "/d/Faerun/guilds/nov/obj/potion3"}), \
 ])