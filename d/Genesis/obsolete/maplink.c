/*
   maplink.c

   Ver 1.0

   This is the object that links all parts of the Genesis domain
   to the global map.
*/
inherit "/std/map/manager";

void 
create_map_manager()
{
    /*
	Wiz|n
    */
    add_single("x0y0", "/d/Genesis/wiz/wiz_island");

    /*
	Elf start location

	It should be on the mediumsized island north of the
	middle earth continent. Inside the thick forest north
	of the southwest tip of the coast when the coastline turns north.
	    x186 y554
    */
     add_single("x183y554", "/d/Genesis/start/elf/terrain/fir_forest");
     add_single("x185y554", "/d/Genesis/start/elf/terrain/fir_forest");
    add_single("x186y554", "/d/Genesis/start/elf/elf_start");
    add_single("x57y518", "/d/Genesis/start/goblin/goblin_start");
    add_single("x314y510", "/d/Genesis/start/dwarf/level_1/map_link");

    /*

	Human start location

	It should be (temporarily) on the island north east of
	the middle earth continent. It is on the east coast in
	a bay at koord: 445,498 (%)   and  446,498 (=)

    add_single("x446y498", "/d/Genesis/start/human/map/town");
    add_single("x445y498", "/d/Genesis/start/human/map/wild");

	A few other ML's needs to be fixed in the neighbouring area.
	Theese are the ones that contains passages like the northern
	mountain pass etc.

	         m3
	      m4 m2 m1   	m1 - m5: mountains	wi - wild
	      f1 wi to - 498    f1 - f2: forest		to - town
	      f2 m5 p1		p1     : plains
		 |
		 445
    */
    add_single("x446y499", "/d/Genesis/start/human/map/mountain1");
    add_single("x445y499", "/d/Genesis/start/human/map/mountain2");
    add_single("x445y500", "/d/Genesis/start/human/map/mountain3");
    add_single("x444y499", "/d/Genesis/start/human/map/mountain4");
    add_single("x445y497", "/d/Genesis/start/human/map/mountain5");
}
