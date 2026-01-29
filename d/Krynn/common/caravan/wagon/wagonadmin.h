

#include "wagon.h"
#include "route.h"

#define VENCAR_TEST_WAGONS  (({F_WAGON_CONESTOGA, F_WAGON_CONESTOGA, \
                               F_WAGON_SMITH, F_WAGON_FARMER,  \
                               F_WAGON_TREASURY, F_WAGON_MERCHANT, \
                               F_WAGON_PRISON}))

#define VENCAR_TEST_WAGONS_TYPES (({WAGON_ALCHEMIST, WAGON_ARMOURY, \
                                    NONSPECIFIC, NONSPECIFIC, NONSPECIFIC, \
                                    NONSPECIFIC , NONSPECIFIC}))


        /* filename,          type,         %chance,  max */
#define CARAVAN_GOOD_CIVILIAN_1 ({ \
        ({ F_WAGON_ALCHEMIST, WAGON_ALCHEMIST,  5,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_ARMOURY  ,  5,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_WEAPONRY ,  5,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_FLETCHER ,  5,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_INN      ,  5,      1 }), \
        ({ F_WAGON_CONESTOGA, NONSPECIFIC    , 40,      9 }), \
        ({ F_WAGON_CONESTOGA, WAGON_BUTCHER  ,  5,      1 }), \
        ({ F_WAGON_FARMER,    WAGON_FARMER   , 15,      3 }), \
        ({ F_WAGON_SMITH,     WAGON_SMITH    ,  5,      1 }), \
        ({ F_WAGON_MERCHANT,  WAGON_MERCHANT ,  5,      1 }), \
        ({ F_WAGON_TREASURY,  WAGON_TREASURY ,  2,      1 }), \
        ({ F_WAGON_PRISON,    WAGON_PRISON   ,  3,      1 }), \
      })

#define CARAVAN_FARMER_1 ({ \
        ({ F_WAGON_ALCHEMIST, WAGON_ALCHEMIST,  2,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_ARMOURY  ,  3,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_WEAPONRY ,  2,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_FLETCHER ,  3,      1 }), \
        ({ F_WAGON_CONESTOGA, NONSPECIFIC    , 12,      4 }), \
        ({ F_WAGON_CONESTOGA, WAGON_BUTCHER  , 16,      1 }), \
        ({ F_WAGON_FARMER,    WAGON_FARMER   , 52,      9 }), \
        ({ F_WAGON_SMITH,     WAGON_SMITH    ,  5,      1 }), \
        ({ F_WAGON_MERCHANT,  WAGON_MERCHANT ,  5,      1 }), \
      })

#define CARAVAN_TROOP_TEST_1 ({ \
        ({ F_WAGON_ALCHEMIST, WAGON_ALCHEMIST,  15,      1 }), \
        ({ F_WAGON_DWARF,     NONSPECIFIC    ,  15,      1 }), \
        ({ F_WAGON_DOFFICER,  WAGON_D_OFFICER    ,  15,      1 }), \
        ({ F_WAGON_KOFFICER,  WAGON_K_OFFICER    ,  15,      1 }), \
        ({ F_WAGON_TROOP,     WAGON_D_TROOPS    ,  15,      1 }), \
        ({ F_WAGON_CONESTOGA, WAGON_BUTCHER  ,  15,      1 }), \
        ({ F_WAGON_FARMER,    WAGON_FARMER   ,  12,      1 }), \
        ({ F_WAGON_SMITH,     WAGON_SMITH    ,  5,      1 }), \
        ({ F_WAGON_MERCHANT,  WAGON_MERCHANT ,  5,      1 }), \
      })

/*
*/

/* Look at SS_SKILL_DESC in /config/sys/ss_types2.h
   public void remove_wagon(object wagon) { MyWagons -= ({
   wagon }); }
*/

#define NPC_