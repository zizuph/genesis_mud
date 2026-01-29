/* The army which will attack Que Kiri. */

/* Aridor 07/95 */


inherit "/d/Krynn/common/army/army";



void
create_army()
{
    set_start_rooms(({"/d/Krynn/que/camp/camp01",
			/*"/d/Krynn/que/camp/camp02",
			"/d/Krynn/que/camp/camp03"*/}));
    set_target_rooms(({"/d/Krynn/que/kiri/room/arena",
			 "/d/Krynn/que/kiri/room/well"}));
    set_army_soldiers(({"/d/Krynn/que/living/aurak",
			  "/d/Krynn/que/living/baaz",
			  "/d/Krynn/que/living/bozak",
			  "/d/Krynn/que/living/sivak",
			  "/d/Krynn/que/living/kapak",
			  "/d/Krynn/que/living/goblin",
			  "/d/Krynn/que/living/hobgoblin",
			  "/d/Krynn/que/living/mercenary"}));

    set_command_interval(1);
    /* do some internal stuff in the army (create platoon) every `12 hours */
    set_platoon_file("/d/Krynn/que/army/platoon");
    set_platoon_data_dir("/d/Krynn/que/army/save_data");
    set_max_platoons(5);

    set_alarm(4.0,0.0,"start_army");
}
