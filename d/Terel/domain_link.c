/* This is the Terel preload.c file 
 *
 *  Modifications:
 *    Lilith Feb 2022: removed preloads for old guilds and grouped files.
 *
 */
 
inherit "/std/domain_link";

preload_link()
{
    /* Terel boats */
    preload("/d/Terel/dabaay/harbor/npier_1");
    preload("/d/Terel/dabaay/harbor/spier_2");
    preload("/d/Terel/dabaay/harbor/spier_3");
    preload("/d/Terel/n_port/pier1");
	
    /* Terel guilds */
    preload("/d/Terel/cedric/guild/song_index");

    /* Terel caravan */
    preload("/d/Terel/silver/road/road02");

    /* Terel npcs */
    preload("/d/Terel/dabaay/obj/jenglea_loc");
    preload("/d/Terel/dabaay/obj/dunk_man");
    preload("/d/Terel/calathin/npc/guard_manager");
	
	/* Terel tracking objects */
    preload("/d/Terel/lib/race_size_tracker");
    preload("/d/Terel/last/obj/kill_logger");
    preload("/d/Terel/calathin/obj/kill_logger");
    preload("/d/Terel/mountains/goblincave/obj/kill_logger");
	
}
