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
               "/d/Gondor/common/guild2/potions/arhal"}), \
    "berichelkh" : ({ 10, 150, ({"/d/Gondor/common/herbs/frostheal",}), \
               ({}), ({}), \
               "/d/Gondor/common/guild2/potions/berichelkh"}), \
    "bragollach" : ({ 30, 50, ({"/d/Gondor/common/herbs/thyme", \
                                "/d/Gondor/common/herbs/tyelka", }), \
               ({ }), ({"snake meat"}), \
               "/d/Gondor/common/guild2/potions/bragollach"}), \
    "corcosunk" :  ({ 10,  20, ({"/d/Gondor/common/herbs/tuo", \
	                         "/d/Gondor/common/herbs/myrtle", }), \
               ({ }), ({ "eye" }), \
	       "/d/Gondor/common/guild2/potions/corcosunk"}), \
    "dollost" :    ({ 25,  50, ({"/d/Gondor/common/herbs/madwort",}), \
               ({}), ({}), \
               "/d/Gondor/common/guild2/potions/dollost_potion"}), \
    "lominen" :    ({ 10, 50, ({"/d/Gondor/common/herbs/coccinea", \
	                        "/d/Gondor/common/herbs/curugwath", }), \
	       ({ }), ({ }), \
	       "/d/Gondor/common/guild2/potions/lominen"}), \
    "morgurth" :   ({ 40,  40, ({"/d/Gondor/common/herbs/angurth", }), \
	       ({ "/std/leftover", }), ({}), \
	       "/d/Gondor/common/guild2/potions/morgurth"}), \
    "nenamarth" :  ({ 40,  40, ({"/d/Gondor/common/herbs/morgurth", }), \
	       ({ "/std/leftover", }), ({}), \
	       "/d/Gondor/common/guild2/potions/nenamarth"}), \
    "nennaur" :    ({ 44,  44, ({"/d/Gondor/common/herbs/red_pepper", }), \
	       ({}), ({"ashes"}), \
	       "/d/Gondor/common/guild2/potions/nennaur"}), \
    "avarywalme" : ({ 10,  50, ({"/d/Gondor/common/herbs/foxglove", \
                                 "/d/Gondor/common/herbs/alfirin", }), \
               ({ }), ({ }), \
               "/d/Gondor/guilds/rangers/potions/avarywalme"}), \
    "este" :       ({  0,  50, ({"/d/Gondor/common/herbs/athelas",}), \
               ({}), ({}), \
               "/d/Gondor/guilds/rangers/potions/este" }), \
    "wenya" :      ({ 25,  50, ({"/d/Gondor/common/herbs/tuo", \
                                 "/d/Gondor/common/herbs/suranie",}), \
	       ({}), ({}), \
               "/d/Gondor/guilds/rangers/potions/wenya"}), \
    ])
