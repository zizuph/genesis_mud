#define MORGUL_S_MORTAR		"_morgul_potions_mortar"
#define RANGER_S_MORTAR         "_ranger_potions_mortar"

  /*
   * This is the definition of the mapping for the mortar which can
   * be used mudwide (/d/Genesis/std/potions/mortar.c)
   *
   * It is used in /d/Gondor/domain_link.c.
   */
#define GONDOR_POTION_INGREDIENTS ([ \
    "arhal" : ({ 10,  20, ({"/d/Gondor/common/herbs/sage",}), \
               ({}), ({}), \
               "/d/Gondor/guilds/morgulmage/potions/arhal"}), \
    "avarywalme" : ({ 10,  50, ({"/d/Gondor/common/herbs/foxglove", \
                                 "/d/Gondor/common/herbs/alfirin", }), \
               ({ }), ({ }), \
               "/d/Gondor/guilds/rangers/potions/avarywalme"}), \
    "berichelkh" : ({ 10, 100, ({"/d/Gondor/common/herbs/frostheal",}), \
               ({}), ({}), \
               "/d/Gondor/guilds/morgulmage/potions/berichelkh"}), \
    "bragollach" : ({ 30, 50, ({"/d/Gondor/common/herbs/thyme", \
                                "/d/Gondor/common/herbs/tyelka", }), \
               ({ }), ({"snake meat"}), \
               "/d/Gondor/common/guild2/potions/bragollach"}), \
    "canwa" : ({ 10, 20, ({ "/d/Gondor/common/herbs/astaldo" }), \
               ({ }), ({ }), \
               "/d/Gondor/guilds/morgulmage/potions/canwa" }), \
    "corcosunk" :  ({ 10,  20, ({"/d/Gondor/common/herbs/tuo", \
	                         "/d/Gondor/common/herbs/myrtle", }), \
               ({ }), ({ "eye" }), \
	             "/d/Gondor/guilds/morgulmage/potions/corcosunk"}), \
    "dollost" :    ({ 25,  50, ({"/d/Gondor/common/herbs/madwort",}), \
               ({}), ({}), \
               "/d/Gondor/guilds/morgulmage/potions/dollost"}), \
    "este" :       ({  0,  50, ({"/d/Gondor/common/herbs/athelas",}), \
               ({}), ({}), \
               "/d/Gondor/guilds/rangers/potions/este" }), \
    "lominen" :    ({ 10, 50, ({"/d/Gondor/common/herbs/coccinea", \
	                        "/d/Gondor/common/herbs/curugwath", }), \
	       ({ }), ({ }), \
	       "/d/Gondor/guilds/morgulmage/potions/lominen"}), \
    "mapa" : ({ 10, 20, ({ "/d/Gondor/common/herbs/handasse" }), \
         ({ }), ({ }), \
         "/d/Gondor/guilds/morgulmage/potions/mapa" }), \
    "morgurth" :   ({ 40,  40, ({"/d/Gondor/common/herbs/angurth", }), \
	       ({ "/std/leftover", }), ({}), \
	       "/d/Gondor/guilds/morgulmage/potions/morgurth"}), \
    "naicelum" : ({ 10, 20, ({ "/d/Gondor/common/herbs/sumac" }), \
         ({ }), ({ }), \
         "/d/Gondor/guilds/morgulmage/potions/naicelum" }), \
    "nenamarth" :  ({ 40,  40, ({"/d/Gondor/common/herbs/morgurth", }), \
	       ({ "/std/leftover", }), ({}), \
	       "/d/Gondor/guilds/morgulmage/potions/nenamarth"}), \
    "nennaur" :    ({ 44,  44, ({"/d/Gondor/common/herbs/red_pepper", }), \
	       ({}), ({"ashes"}), \
	       "/d/Gondor/guilds/morgulmage/potions/nennaur"}), \
    "nwalyavanta" : ({ 10, 20, ({ "/d/Gondor/common/herbs/tyelka", \
                                       "/d/Gondor/common/herbs/foxglove" }), \
         ({ }), ({ }), \
         "/d/Gondor/guilds/morgulmage/potions/nwalyavanta" }), \
    "ramal" : ({ 10, 20, ({ "/d/Gondor/common/herbs/alfirin" }), \
         ({ }), ({ "snake skin" }), \
         "/d/Gondor/guilds/morgulmage/potions/ramal" }), \
    "taltambar" : ({ 10, 20, ({ "/d/Gondor/common/herbs/tuo", \
                                     "/d/Gondor/common/herbs/hemlock" }), \
         ({ }), ({ }), \
         "/d/Gondor/guilds/morgulmage/potions/taltambar"}), \
    "wenya" :      ({ 25,  50, ({"/d/Gondor/common/herbs/tuo", \
                                 "/d/Gondor/common/herbs/suranie",}), \
	       ({}), ({}), \
               "/d/Gondor/guilds/rangers/potions/wenya"}), \
    ])
